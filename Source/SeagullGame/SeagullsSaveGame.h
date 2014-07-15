

#pragma once

#include "GameFramework/SaveGame.h"
#include "SeagullsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class USeagullsSaveGame : public USaveGame
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
	FString Resolution;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
	bool isFullscreen;
	
};
