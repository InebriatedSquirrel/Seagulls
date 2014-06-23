

#include "SeagullGame.h"
#include "BirdCharacter.h"


ABirdCharacter::ABirdCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{

	};
	// Correct the mesh's axis - REMOVE THIS WITH NEW MESH
	Mesh->AddLocalRotation(FRotator(0.f,270.0f,0.f));

	// Create a spring arm component
	SpringArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm0"));
	SpringArm->AttachTo(Mesh);
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 15.f;

	// Further mesh axis correction
	SpringArm->AddLocalRotation(FRotator(0.f, 90.0f, 0.0f));
	

	// Create camera component 
	Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUseControllerViewRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	Gliding = false;
	GlidingUnlocked = true;
	FlyingGravityStrength = 0.1f;
	MaxVerticalFlapVelocity = 1000.0f;
	FlapStrength = 500.0f;
	MaxGlideForce = 10.0f;
	GlideDragAmount = 0.1f;
	GlideMaxSpeed = 1024.0f;
	FallingMaxSpeed = 512.0f;
}

// Frame loop
void ABirdCharacter::Tick(float DeltaSeconds)
{
	// If we have forward momentum to use, decide how it should be altered
	if (LatFlapForce >= 0.0f ){
		// Make sure we don't divide by zero
		if (GlideDragAmount <= 0.0f){
			GlideDragAmount = 0.000001f;
		}
		//If braking is toggled, slow down no matter what
		if (Braking){
			LatFlapForce -= (GlideDragAmount * 2);
		}
		// If looking upwards, decrease speed
		if (Controller->GetControlRotation().Vector().Z > 0.0f){
			LatFlapForce -= (GlideDragAmount / 4) * Controller->GetControlRotation().Vector().Z;
		}
		// If looking downwards, increase speed
		if (Controller->GetControlRotation().Vector().Z < 0.0f){
			LatFlapForce -= (GlideDragAmount * 2) * Controller->GetControlRotation().Vector().Z;
		}
	}
	// If we still have force but aren't trying to move forward, or are walking, set force to zero
	if (LatFlapForce >= 0.0f && !ForwardPressed || LatFlapForce < 0.0f || CharacterMovement->MovementMode == MOVE_Walking){
		LatFlapForce = 0.0f;
	}
	// Set a max force that we can't exceed
	else if (LatFlapForce > MaxGlideForce){
		LatFlapForce = MaxGlideForce;
	}
	// If forward input is pressed, move the player in the direction they're facing
	if (ForwardPressed){
		const FVector Direction = Controller->GetControlRotation().Vector();
		AddMovementInput(Direction, LatFlapForce);
	}
	// If gliding, impart fake gravity
	if (Gliding){
		const FVector Direction = Controller->GetControlRotation().Vector();

		AddMovementInput(FVector(0.0f, 0.0f, -1.0f), FlyingGravityStrength);
		//Make sure the movement mode is correct
		if (CharacterMovement->MovementMode != MOVE_Flying){
			CharacterMovement->SetMovementMode(MOVE_Flying);
		}
		
	}
	/** Various Debugs */
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, CharacterMovement->GetMovementName());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(LatFlapForce));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(CharacterMovement->MaxAcceleration));
	
	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ABirdCharacter::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	// If the bird touches an object with the ground tag, mark the player as walking
	if (Other != NULL && Other->ActorHasTag("Ground")){
		CharacterMovement->SetMovementMode(MOVE_Walking);
	}
	// If the bird hits something that isn't the ground, make it fall
	else{ 
		CharacterMovement->SetMovementMode(MOVE_Falling);
		LatFlapForce = 0.0f;
	}
}

void ABirdCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	
	InputComponent->BindAxis("Lateral", this, &ABirdCharacter::AddControllerYawInput);
	InputComponent->BindAxis("Vertical", this, &ABirdCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("FlapUpward", this, &ABirdCharacter::Flap);
	InputComponent->BindAxis("FlapForward", this, &ABirdCharacter::FlapForward);

	InputComponent->BindAction("Brake", IE_Pressed, this, &ABirdCharacter::Brake);
	InputComponent->BindAction("Brake", IE_Released, this, &ABirdCharacter::ReleaseBrake);
}

void ABirdCharacter::Flap(float Val){
	if (Val > 0 && !UpPressed){
		// Launch the player upwards at a weak strength
		const FVector LaunchForce = FVector(0.f, 0.f, FlapStrength);
		const FVector Direction = Controller->GetControlRotation().Vector();
		// Set a max limit on vertical velocity
		if (GetVelocity().Z < MaxVerticalFlapVelocity){
			LaunchCharacter(LaunchForce, false, false);
/*			if (LatFlapForce < MaxGlideForce){
				LatFlapForce += 0.5f;
			}*/
		}
		// If gliding is unlocked, toggle gliding and increase the Bird max speed
		if (GlidingUnlocked && !Gliding){
			Gliding = true;
			CharacterMovement->MaxAcceleration = GlideMaxSpeed;
		}
		UpPressed = true;
	}
	else if(UpPressed && Val == 0.0f){
		if (Gliding  && ForwardPressed == false){
			StopGlide();
		}
		UpPressed = false;
	}
}
void ABirdCharacter::FlapForward(float Val){

	// If any input is being pressed and the bird is on the ground, make it walk
	if (Val != 0.0f && CharacterMovement->IsMovingOnGround())
	{
		//Find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();

		// Limit pitch and walk if bird is on ground
		Rotation.Pitch = 0.0f;

		//Add movement in forward direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);

	}

	else if (Val > 0 && !Gliding && !ForwardPressed){
		// Launch the player upwards at a weak strength
		const FVector LaunchForce = GetActorForwardVector() * FlapStrength;
		const FVector Direction = Controller->GetControlRotation().Vector();
		// Set a max limit on vertical velocity
		//	if (GetVelocity().Z < MaxVerticalFlapVelocity){
		LaunchCharacter(LaunchForce, false, false);
		if (LatFlapForce < MaxGlideForce){
			LatFlapForce += 0.5f;
		}
		//	}

		// If gliding is unlocked, toggle gliding and increase the Bird max speed
		if (GlidingUnlocked && !Gliding){
			Gliding = true;
			CharacterMovement->MaxAcceleration = GlideMaxSpeed;
		}
		ForwardPressed = true;
	}
	else if (ForwardPressed && Val <= 0){
		if (Gliding){
			StopGlide();
		}
		ForwardPressed = false;
	}
}

//If the glide input is let go, set the player to falling
void ABirdCharacter::StopGlide(){
	Gliding = false;
	CharacterMovement->SetMovementMode(MOVE_Falling);
	CharacterMovement->MaxAcceleration = FallingMaxSpeed;
}

void ABirdCharacter::Brake(){
	Braking = true;
}

void ABirdCharacter::ReleaseBrake(){
	Braking = false;
}
