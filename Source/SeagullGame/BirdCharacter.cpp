

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
	SpringArm->CameraLagSpeed = 30.0f;

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
	FlapStrength = 1000.0f;
	MaxGlideFactor = 0.5f;
	MaxDiveFactor = 4.0f;
	GlideDragAmount = 0.1f;
	GlideMaxSpeed = 4136.0f;
	FallingMaxSpeed = 512.0f;
	RotateTimer = 1.0f;
	CameraResetSpeed = 2.0f;
	GlideTimerActive = false;
	GlideDelay = 0.14f;
	GlideTimer = GlideDelay;
	InputDisabled = false;

	// Setting Default Values
	CharacterMovement->MaxFlySpeed = GlideMaxSpeed;
	CharacterMovement->MaxWalkSpeed = FallingMaxSpeed;
	CharacterMovement->AirControl = 0.5f;
	CharacterMovement->BrakingDecelerationFlying = 1024.0f;
	CharacterMovement->BrakingDecelerationFalling = 1200.0f;
}

// Frame loop
void ABirdCharacter::Tick(float DeltaSeconds)
{
	/*if (!InputEnabled() && !InputDisabled){
		InputDisabled = true;
	}
	else if (InputEnabled() && InputDisabled)
	{
		InputDisabled = false;
	}*/

	if (InputDisabled && !DisableToggled)
	{
		Gliding = false;
		GlideTimerActive = false;
		Hover = false;
		RotateTimer = 0.0f;
		Braking = false;
		LatFlapForce = 0.0f;
		ForwardPressed = false;
		UpPressed = false;
		DisableToggled = true;
	}
	else if (!InputDisabled && DisableToggled)
	{
		DisableToggled = false;
	}

	if (GlideTimerActive == true){
		GlideTimer -= DeltaSeconds;
		if (GlideTimer <= 0.0f){
			Gliding = true;
			Hover = false;
			GlideTimer = GlideDelay;
			GlideTimerActive = false;
		//	CharacterMovement->MaxAcceleration = GlideMaxSpeed;
		}
	}

	// If we have forward momentum to use, decide how it should be altered
	if (LatFlapForce >= 0.0f ){
		// Make sure we don't divide by zero
		if (GlideDragAmount <= 0.0f){
			GlideDragAmount = 0.000001f;
		}
		//If braking is toggled, slow down no matter what
		if (Braking){
			LatFlapForce -= (GlideDragAmount * 2.0f);
		}
		// If looking upwards, decrease speed
		if (Controller && Controller->GetControlRotation().Vector().Z > 0.0f && Gliding){
			LatFlapForce -= (GlideDragAmount / 2.0f) * Controller->GetControlRotation().Vector().Z;
		}
		// If looking downwards, increase speed
		if (Controller && Controller->GetControlRotation().Vector().Z < 0.0f && Gliding){
			LatFlapForce -= (GlideDragAmount) * Controller->GetControlRotation().Vector().Z;
		}
	}
	// If we still have force but aren't trying to move forward, or are walking, set force to zero
	if (/*LatFlapForce >= 0.0f && !ForwardPressed ||*/ LatFlapForce < 0.0f || CharacterMovement->MovementMode == MOVE_Walking){
		LatFlapForce = 0.0f;
	}
	else if (CharacterMovement->MovementMode == MOVE_Walking && LatFlapForce >= MaxGlideFactor){
		LatFlapForce = MaxGlideFactor;
	}
	// Set a max force that we can't exceed
	else if (LatFlapForce > MaxDiveFactor){
		LatFlapForce = MaxDiveFactor;
	}
	// If forward input is pressed, move the player in the direction they're facing
	if (ForwardPressed && Gliding){
		const FVector Direction = Controller->GetControlRotation().Vector();
		AddMovementInput(Direction, LatFlapForce);
	}
	// If gliding, impart fake gravity
	if (Gliding || Hover){
		AddMovementInput(FVector(0.0f, 0.0f, -1.0f), FlyingGravityStrength);
		//Make sure the movement mode is correct
		if (CharacterMovement->MovementMode != MOVE_Flying && !InputDisabled){
			CharacterMovement->SetMovementMode(MOVE_Flying);
		}
		
	}
	/** Various Debugs */
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, CharacterMovement->GetMovementName());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::SanitizeFloat(LatFlapForce));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Max Speed: " + FString::SanitizeFloat(CharacterMovement->GetMaxSpeed()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Fall Speed: " + FString::SanitizeFloat(CharacterMovement->MaxWalkSpeed));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Velocity: " + FString::SanitizeFloat(CharacterMovement->Velocity.Size()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Velocity2D: " + FString::SanitizeFloat(CharacterMovement->Velocity.Size2D()));
	
	// If already rotating, and there is time on the clock, decrease it
	if (Rotating && RotateTimer > 0.0f){
		RotateTimer -= DeltaSeconds;
		CameraResetting = false;
	}
	// If the rotate should happen, reset values and toggle it
	else if (RotateTimer <= 0.0f && Rotating){
		RotateTimer = 1.0f;
		Rotating = false;
		// Give the ease extra time
		CameraResetTimer = CameraResetSpeed * 2.5f;
		CameraResetting = true;
	}

	// If the camera needs to be moved back, interpolate it over a period of time
	if (CameraResetting){
		if (SpringArm->RelativeRotation != FRotator(0.f, 90.0f, 0.f)){
			tempRotation = FMath::RInterpTo(SpringArm->RelativeRotation, FRotator(0.f, 90.0f, 0.f), DeltaSeconds, CameraResetSpeed);
			SpringArm->SetRelativeRotation(tempRotation);
			CameraResetTimer -= DeltaSeconds;
		}
		// After interpolation, ensure that the rotation is snapped into place
		if(CameraResetTimer <= 0.0f){
			CameraResetting = false;
			CameraResetTimer = 0.0f;
			SpringArm->SetRelativeRotation(FRotator(0.f, 90.0f, 0.0f));
		}
	}

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ABirdCharacter::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	// If the bird touches an object with the ground tag, mark the player as walking
	if (Other != NULL && Other->ActorHasTag("Ground") && !InputDisabled){
		CharacterMovement->SetMovementMode(MOVE_Walking);
	}
	// If the bird hits something that isn't the ground, make it fall
	else if (!InputDisabled){
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

	InputComponent->BindAxis("CameraX", this, &ABirdCharacter::RotateCameraX);
	InputComponent->BindAxis("CameraY", this, &ABirdCharacter::RotateCameraY);

	InputComponent->BindAxis("MouseCameraX", this, &ABirdCharacter::MouseRotateCameraX);
	InputComponent->BindAxis("MouseCameraY", this, &ABirdCharacter::MouseRotateCameraY);

	InputComponent->BindAction("Brake", IE_Pressed, this, &ABirdCharacter::Brake);
	InputComponent->BindAction("Brake", IE_Released, this, &ABirdCharacter::ReleaseBrake);
}

void ABirdCharacter::Flap(float Val){
	if (!InputDisabled){
		if (Val > 0 && !UpPressed){
			// Launch the player upwards at a weak strength
			const FVector LaunchForce = FVector(0.f, 0.f, FlapStrength);
			const FVector Direction = Controller->GetControlRotation().Vector();
			// Set a max limit on vertical velocity
			if (GetVelocity().Z < MaxVerticalFlapVelocity){
				LaunchCharacter(LaunchForce, false, false);
			}
			// If gliding is unlocked, toggle gliding and increase the Bird max speed
			if (GlidingUnlocked && !Hover){
				Hover = true;
				//CharacterMovement->MaxAcceleration = GlideMaxSpeed;
			}
			UpPressed = true;
			this->Flapped();
		}
		else if (UpPressed && Val <= 0.0f){
			if (Hover){
				Hover = false;
				CharacterMovement->SetMovementMode(MOVE_Falling);
			}
			UpPressed = false;
		}
		
	}
}
void ABirdCharacter::FlapForward(float Val){
	if (!InputDisabled){
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

			LatFlapForce += 1.0f;
			if (CharacterMovement->Velocity.Size2D() < FallingMaxSpeed){
				LaunchCharacter(LaunchForce, false, false);
			}
			else{
				LaunchCharacter(LaunchForce / 2.0f, false, false);
			}
			if (CharacterMovement->Velocity.Z < 0.0f && Controller->GetControlRotation().Vector().Z > 0.2f){
				LaunchCharacter(GetActorUpVector() * FlapStrength / 2.0f, false, false);
			}


			// If gliding is unlocked, toggle gliding and increase the Bird max speed
			if (GlidingUnlocked && !Gliding){
				GlideTimerActive = true;
				//	CharacterMovement->MaxAcceleration = GlideMaxSpeed;
			}
			ForwardPressed = true;
			this->Flapped();
		}
		// If the button was let go...
		else if (ForwardPressed && Val <= 0){
			if (Gliding){
				StopGlide();
			}
			GlideTimerActive = false;
			ForwardPressed = false;
		}
	}
}

//If the glide input is let go, set the player to falling
void ABirdCharacter::StopGlide(){
	Gliding = false;
	if (!InputDisabled)
	{
		CharacterMovement->SetMovementMode(MOVE_Falling);
	}
	LatFlapForce = 0.0f;
	//CharacterMovement->MaxAcceleration = FallingMaxSpeed;
}

void ABirdCharacter::RotateCameraX(float Val){
	if (Val != 0.0f && !InputDisabled){
		SpringArm->AddLocalRotation(FRotator(0.f, (Val * 2.0), 0.0f));
		Rotating = true;
		RotateTimer = 1.0f;
	}
}

void ABirdCharacter::RotateCameraY(float Val){
	if (Val != 0.0f && !InputDisabled){
		SpringArm->AddLocalRotation(FRotator((Val * 2.0), 0.0f, 0.0f));
		Rotating = true;
		RotateTimer = 1.0f;
	}
}

void ABirdCharacter::MouseRotateCameraX(float Val){
	if (Val != 0.0f && MouseCameraActive && !InputDisabled){
		SpringArm->AddLocalRotation(FRotator(0.f, (Val * 2.0), 0.0f));
		Rotating = true;
		RotateTimer = 1.0f;
	}
}

void ABirdCharacter::MouseRotateCameraY(float Val){
	if (Val != 0.0f && MouseCameraActive && !InputDisabled){
		SpringArm->AddLocalRotation(FRotator((Val * 2.0), 0.0f, 0.0f));
		Rotating = true;
		RotateTimer = 1.0f;
	}
}

void ABirdCharacter::Brake(){
	if (!InputDisabled){
		Braking = true;
	}
}

void ABirdCharacter::ReleaseBrake(){
		Braking = false;
}

// If this cheat was used, pass the event to blueprints
void ABirdCharacter::SetMission(float mission){
	this->OnMissionCheat(mission);
}
