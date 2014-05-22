

#include "SeagullGame.h"
#include "BirdCharacter.h"


ABirdCharacter::ABirdCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{

	};
	Mesh->AddLocalRotation(FRotator(0.f,270.0f,0.f));
	// Create a spring arm component
	SpringArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm0"));
	SpringArm->AttachTo(Mesh);
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->AddLocalRotation(FRotator(0.f, 90.0f, 0.0f));
	

	// Create camera component 
	Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUseControllerViewRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	TurnSpeed = 50.f;
}

void ABirdCharacter::Tick(float DeltaSeconds)
{

	if (RightFlapped && LeftFlapped)
	{
		const FVector LaunchForce = FVector(0.f, 0.f, 50.0f);
		if (GetVelocity().Z < 500.0f){

			LaunchCharacter(LaunchForce, false, false);
		}
	}
	else if (RightFlapped){
		RotateBird(1.0f);
	//	RightFlapped = false;
		const FVector LaunchForce = FVector(0.f, 0.f, 50.0f);
		if (GetVelocity().Z < 100.0f){

			LaunchCharacter(LaunchForce, false, false);
		}
	}
	else if (LeftFlapped){
		RotateBird(-1.0f);
	//	LeftFlapped = false;
		const FVector LaunchForce = FVector(0.f, 0.f, 50.0f);
		if (GetVelocity().Z < 100.0f){

			LaunchCharacter(LaunchForce, false, false);
		}
	}

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;
	
	AddControllerYawInput(DeltaRotation.Yaw);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);

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

	// Fine up and right axes
	InputComponent->BindAxis("Forward", this, &ABirdCharacter::ThrustInput);
	//InputComponent->BindAxis("MoveUp", this, &ABirdCharacter::MoveUpInput);
	//InputComponent->BindAxis("MoveRight", this, &ABirdCharacter::MoveRightInput);

	InputComponent->BindAxis("RightWing", this, &ABirdCharacter::OnRightFlap);
//	InputComponent->BindAction("LeftWing", IE_Pressed, this, &ABirdCharacter::OnLeftFlap);
}

void ABirdCharacter::ThrustInput(float Val)
{
	ForwardPressed = true;
	// find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();

	// add movement in that direction
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Val);
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
	}
	
}
void ABirdCharacter::RotateBird(float Val)
{
	float TargetYawSpeed = (TurnSpeed * Val);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();

}

