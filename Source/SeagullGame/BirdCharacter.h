

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

	/** How quickly pawn can steer */
	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
	float TurnSpeed;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
	float flapStrength;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
	float MaxVerticalFlapVelocity;

	UPROPERTY(Category = Bird, BlueprintReadOnly)
	bool gliding;

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the vertical axis */
	void ThrustInput(float Val);

	/** Event for Rotations*/
	void OnRightFlap(float Val);

	/** Rotates the bird around it's axis*/
	void RotateBird(float Val);

	/**  */
	void Flap();

	/**  */
	void StopGlide();

private:

	

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	/** Booleans for input tracking*/
	bool RightFlapped;

	bool LeftFlapped;

	bool ForwardPressed;

	/** Timers for wing flap spacing*/
	float RightTimer;

	float LeftTimer;

	float BothTimer;

	float ForwardFlapForce;
};