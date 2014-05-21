

#pragma once

#include "GameFramework/GameMode.h"
#include "PrimaryGameMode.generated.h"

/**
 * 
 */
UCLASS()
class APrimaryGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() OVERRIDE;
	
};
