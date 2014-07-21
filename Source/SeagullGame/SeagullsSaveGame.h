

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

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
	FString Resolution;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
	bool isFullscreen;*/

	// Resolution value set by the user - Default is 1280x720
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedRes;
	// Fullscreen toggle set by the user - Default is true
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		bool SavedUseFullscreen;
	// Resolution Scale set by the user - Default is 100
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedResScale;
	// View Distance set by the user - Default is 1.0
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedViewDistance;
	// Anti-Aliasing set by the user - Default is 4
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedAA;
	// Post Processing Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedPostProcessing;
	// Shadows Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedShadows;
	// Texture Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedTextures;
	// Effects Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedEffects;
	// Detail Level set by the user - Default is 2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graphics")
		FString SavedDetail;

	// Number of Muliplayer players when loading a multiplayer map - Default is 2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
		FString NumMultiPlayers;
};
