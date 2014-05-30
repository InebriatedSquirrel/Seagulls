

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
	gliding = false;
	MaxVerticalFlapVelocity = 500.0f;
	flapStrength = 350.0f;
}

// Frame loop
void ABirdCharacter::Tick(float DeltaSeconds)
{
	// If both wings were pressed, thrust upwards and don't rotate
	if (RightFlapped && LeftFlapped)
	{
		// Manage the length of the force using a timer
		BothTimer += DeltaSeconds;
		if (BothTimer < 0.3f){
			// Launch the player upwards at a moderate strength
			const FVector LaunchForce = FVector(0.f, 0.f, 350.0f);
			// Set a max limit on vertical velocity
			if (GetVelocity().Z < 500.0f){
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
			// Launch the player upwards at a weak strength
			const FVector LaunchForce = FVector(0.f, 0.f, 50.0f);
			// Set a max limit on vertical velocity
			if (GetVelocity().Z < 100.0f){

				LaunchCharacter(LaunchForce, false, false);
			}
		}
	}
	else if (LeftFlapped)
	{
		// Manage the length of the force using a timer
		LeftTimer += DeltaSeconds;
		if (LeftTimer < 0.15f){
			// Rotate the bird counter-clockwise
			RotateBird(-1.0f);
			// Launch the player upwards at a weak strength
			const FVector LaunchForce = FVector(0.f, 0.f, 50.0f);
			// Set a max limit on vertical velocity
			if (GetVelocity().Z < 100.0f){
				LaunchCharacter(LaunchForce, false, false);
			}
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

//	ForwardFlapForce = FMath::FInterpTo(ForwardFlapForce, 0.0f, GetWorld()->GetDeltaSeconds(), 5.0f);
	if (ForwardFlapForce > 0.0f){
		ForwardFlapForce -= 0.005f;
	}
	else if (ForwardFlapForce < 0.0f){
		ForwardFlapForce = 0.0f;
	}

	if (gliding){
		const FVector Direction = Controller->GetControlRotation().Vector();
		//AddMovementInput(Direction, 0.2f);
		AddMovementInput(FVector(0.0f,0.0f,-1.0f), 0.2f);
		if (CharacterMovement->MovementMode != MOVE_Flying){
			CharacterMovement->SetMovementMode(MOVE_Flying);
		}
		
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(ForwardFlapForce));

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ABirdCharacter::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

}

void ABirdCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &ABirdCharacter::ThrustInput);
	
	InputComponent->BindAxis("Lateral", this, &ABirdCharacter::AddControllerYawInput);
	InputComponent->BindAxis("Vertical", this, &ABirdCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Flap", IE_Pressed, this, &ABirdCharacter::Flap);
	InputComponent->BindAction("Flap", IE_Released, this, &ABirdCharacter::StopGlide);

	InputComponent->BindAxis("RightWing", this, &ABirdCharacter::OnRightFlap);
}

void ABirdCharacter::Flap(){
	// Launch the player upwards at a weak strength
	const FVector LaunchForce = FVector(0.f, 0.f, 250.0f);
	const FVector Direction = Controller->GetControlRotation().Vector();
	// Set a max limit on vertical velocity
	if (GetVelocity().Z < 100.0f){
		LaunchCharacter(LaunchForce, false, false);
		ForwardFlapForce += 0.5f;
	}

	gliding = true;
}
void ABirdCharacter::StopGlide(){
	gliding = false;
	CharacterMovement->SetMovementMode(MOVE_Falling);
}
void ABirdCharacter::ThrustInput(float Val)
{
	ForwardPressed = true;

	// find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();
	if (!gliding){
		// add movement in that direction
		//const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X, EAxis::Y, EAxis::Z);
		const FVector Direction = Controller->GetControlRotation().Vector();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Direction.ToString());
		AddMovementInput(Direction, Val);
	}
	else{
		const FVector Direction = Controller->GetControlRotation().Vector();
		AddMovementInput(Direction, ForwardFlapForce);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Flying Forward");
	}
}

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

	// find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();
}

