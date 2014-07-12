

#pragma once

#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"


/**
 * 
 */
UCLASS()
class AMultiplayerGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

public:

	// Spawns a player at the specified start point
	UFUNCTION(BlueprintCallable, Category = "Multiplayer")
		APlayerController* SpawnSplitscreenPlayer(APlayerStart* StartPoint);

	// Removes a player
	UFUNCTION(BlueprintCallable, Category = "Multiplayer")
		void RemoveSplitscreenPlayers();
};
