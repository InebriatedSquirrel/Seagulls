

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
	TurnSpeed = 50.f;
	Gliding = false;
	GlidingUnlocked = true;
	FlyingGravityStrength = 0.1f;
	MaxVerticalFlapVelocity = 1000.0f;
	VertFlapStrength = 500.0f;
	MaxGlideForce = 10.0f;
	GlideDragAmount = 0.1f;
	GlideMaxSpeed = 1024.0f;
	FallingMaxSpeed = 512.0f;
}

// Frame loop
void ABirdCharacter::Tick(float DeltaSeconds)
{
	/** 
	// If both wings were pressed, thrust upwards and don't rotate
	if (RightFlapped && LeftFlapped)
	{
		// Manage the length of the force using a timer
		BothTimer += DeltaSeconds;
		if (BothTimer < 0.3f){
			// Launch the player upwards at a moderate strength
			const FVector LaunchForce = FVector(0.f, 0.f, VertFlapStrength);
			// Set a max limit on vertical velocity
			if (GetVelocity().Z < MaxVerticalFlapVelocity){
				LaunchCharacter(LaunchForce, false, false);
			}
		}
	}
	else if (RightFlapped)
	{
		// Manage the length of the force using a timer
		RightTimer += DeltaSeconds;
		if (RightTimer < 0.15f){
			// Rotate the bird clockwise
			RotateBird(1.0f);
		}
	}
	else if (LeftFlapped)
	{
		// Manage the length of the force using a timer
		LeftTimer += DeltaSeconds;
		if (LeftTimer < 0.15f){
			// Rotate the bird counter-clockwise
			RotateBird(-1.0f);
		}
	}

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;
	
	// Apply the calculated rotation
	AddControllerYawInput(DeltaRotation.Yaw);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);

	*/

	// If we have forward momentum to use, decide how it should be altered
	if (LatFlapForce >= 0.0f ){
		// Make sure we don't divide by zero
		if (GlideDragAmount <= 0.0f){
			GlideDragAmount = 0.000001f;
		}
		// If looking upwards, decrease speed
		if (Controller->GetControlRotation().Vector().Z > 0.0f){
			LatFlapForce -= (GlideDragAmount / 3) * Controller->GetControlRotation().Vector().Z;
		}
		// If looking downwards, increase speed
		if (Controller->GetControlRotation().Vector().Z < 0.0f){
			LatFlapForce -= (GlideDragAmount / 2) * Controller->GetControlRotation().Vector().Z;
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

	InputComponent->BindAxis("Forward", this, &ABirdCharacter::ThrustInput);
	
	InputComponent->BindAxis("Strafe", this, &ABirdCharacter::Strafe);

	InputComponent->BindAxis("Lateral", this, &ABirdCharacter::AddControllerYawInput);
	InputComponent->BindAxis("Vertical", this, &ABirdCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("Flap", this, &ABirdCharacter::Flap);

	InputComponent->BindAxis("RightWing", this, &ABirdCharacter::OnRightFlap);
}

void ABirdCharacter::Flap(float Val){
	if (Val > 0 && !Gliding && !UpPressed){
		// Launch the player upwards at a weak strength
		const FVector LaunchForce = FVector(0.f, 0.f, VertFlapStrength);
		const FVector Direction = Controller->GetControlRotation().Vector();
		// Set a max limit on vertical velocity
		if (GetVelocity().Z < MaxVerticalFlapVelocity){
			LaunchCharacter(LaunchForce, false, false);
			if (LatFlapForce < MaxGlideForce){
				LatFlapForce += 0.5f;
			}
		}
		// If gliding is unlocked, toggle gliding and increase the Bird max speed
		if (GlidingUnlocked){
			Gliding = true;
			CharacterMovement->MaxAcceleration = GlideMaxSpeed;
		}
		UpPressed = true;
	}
	else if(UpPressed && Val == 0.0f){
		if (Gliding){
			StopGlide();
		}
		UpPressed = false;
	}
}
void ABirdCharacter::FlapForward(float Val){
	if (Val > 0 && !Gliding && !UpPressed){
		// Launch the player upwards at a weak strength
		const FVector LaunchForce = FVector(0.f, 0.f, VertFlapStrength);
		const FVector Direction = Controller->GetControlRotation().Vector();
		// Set a max limit on vertical velocity
		if (GetVelocity().Z < MaxVerticalFlapVelocity){
			LaunchCharacter(LaunchForce, false, false);
			if (LatFlapForce < MaxGlideForce){
				LatFlapForce += 0.5f;
			}
		}
		// If gliding is unlocked, toggle gliding and increase the Bird max speed
		if (GlidingUnlocked){
			Gliding = true;
			CharacterMovement->MaxAcceleration = GlideMaxSpeed;
		}
		UpPressed = true;
	}
	else if (UpPressed && Val == 0.0f){
		if (Gliding){
			StopGlide();
		}
		UpPressed = false;
	}
}

//If the glide input is let go, set the player to falling
void ABirdCharacter::StopGlide(){
	Gliding = false;
	CharacterMovement->SetMovementMode(MOVE_Falling);
	CharacterMovement->MaxAcceleration = FallingMaxSpeed;
}
void ABirdCharacter::ThrustInput(float Val)
{
	// If holding forward, allow increase in speed
	if (Val > 0.0f){
		ForwardPressed = true;
	}
	// If holding reverse, decrease speed
	else if (Val < 0.0f){
		ForwardPressed = false;
		LatFlapForce -= 0.05f;
	}
	// Toggle no input detected
	else{
		ForwardPressed = false;
	}

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
}
// Strafe the player left or right based on input
void ABirdCharacter::Strafe(float Val){
	const FVector LatDirection = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(LatDirection, (Val * LatFlapForce));
}
// Check for quick rotate input buttons
void ABirdCharacter::OnRightFlap(float Val)
{
	if (Val == -0.5f)
	{
		RightFlapped = false;
		LeftFlapped = true;
	}
	else if (Val == 1.0f)
	{
		RightFlapped = true;
		LeftFlapped = false;
	}
	else if (Val == 0.5f)
	{
		RightFlapped = true;
		LeftFlapped = true;
	}
	else if (Val == 0.0f)
	{
		RightFlapped = false;
		LeftFlapped = false;
		BothTimer = 0.0f;
		RightTimer = 0.0f;
		LeftTimer = 0.0f;
	}
	
}
void ABirdCharacter::RotateBird(float Val)
{
	//Rotate the bird based on turn speed
	float TargetYawSpeed = (TurnSpeed * Val);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

