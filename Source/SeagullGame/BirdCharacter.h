

#pragma once

#include "GameFramework/Character.h"
#include "BirdCharacter.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class ABirdCharacter : public ACharacter
{
public:
	GENERATED_UCLASS_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		TSubobjectPtr<class USpringArmComponent> SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		TSubobjectPtr<class UCameraComponent> Camera;

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) OVERRIDE;
	virtual void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) OVERRIDE;
	// End AActor overrides

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Upwards force when flapping
		float FlapStrength;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Maximum velocity when travelling upwards
		float MaxVerticalFlapVelocity;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Has the player unlocked the glide ability
		bool GlidingUnlocked;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The downwards force placed on the player
		float FlyingGravityStrength;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The max speed when gliding, bigger amounts mean sustained speed when pulling up
		float MaxGlideFactor;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The acceleration when diving, bigger amounts mean sustained speed when pulling up
		float MaxDiveFactor;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The drag imparted against LatFlapForce when gliding - also increases dive speed
		float GlideDragAmount;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// the max speed when flapping or gliding
		float GlideMaxSpeed;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The max speed when not flapping or gliding
		float FallingMaxSpeed;

	UPROPERTY(Category = Bird, BlueprintReadOnly)
		// Is the player currently gliding
		bool Gliding;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The force that flapping adds to forward/sideways movement
		float LatFlapForce;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadOnly)
		// The speed which the camera rotation resets
		float CameraResetSpeed;

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE; // Allows binding actions/axes to functions
	// End APawn overrides

	// Called when the main flap button is pressed or held
	void Flap(float Val);

	// Called when the flap forward button is pressed or held
	void FlapForward(float Val);

	// Toggles a bool which controls braking
	void Brake();
	void ReleaseBrake();

	// Independant camera controls
	void RotateCameraX(float Val);
	void RotateCameraY(float Val);

	// Function which stops gliding when glide button is released
	void StopGlide();

private:

	// Were both wings just flapped
	bool ForwardPressed;
	// Was the glide button pressed
	bool UpPressed;

	// Is the player currently braking
	bool Braking;

	// Timer which counts down when the player lets go of the camera rotation input
	float RotateTimer;

	// Timer which counts down after a flap and toggles gliding
	float GlideTimer;

	// Toggles glide timer on
	bool GlideTimerActive;

	// Toggles hover
	bool Hover;

	// Timer which counts down when the camera is moving back to it's original location
	float CameraResetTimer;

	// Temporary rotation which is interpolated
	FRotator tempRotation;

	// Is the camera currently trying to reset itself
	bool CameraResetting;
	// Is the player moving the camera
	bool Rotating;
	
};