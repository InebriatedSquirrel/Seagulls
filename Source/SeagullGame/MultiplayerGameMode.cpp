

#include "SeagullGame.h"
#include "MultiplayerGameMode.h"



AMultiplayerGameMode::AMultiplayerGameMode(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	
}

APlayerController* AMultiplayerGameMode::SpawnSplitscreenPlayer(APlayerStart* StartPoint)
{
	if (StartPoint != NULL)
	{
		FString Error;
		int32 PlayerIndex = -1;
		ULocalPlayer* TempPlayer = GEngine->GameViewport->CreatePlayer(PlayerIndex, Error, true);

		// Move the player to their start point
		TempPlayer->PlayerController->GetPawn()->SetActorLocation(StartPoint->GetActorLocation());

		return TempPlayer->PlayerController;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("No player start set - Not spawning"));

		return NULL;
	}	
}

void AMultiplayerGameMode::RemoveSplitscreenPlayers()
{
	/*int32 MaxPlayers = 5;
	ULocalPlayer* TempPlayer;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Players: ") + FString::FromInt(MaxPlayers));

	for (int32 i = 1; i <= MaxPlayers; i++)
	{

		TempPlayer = GEngine->GetLocalPlayerFromControllerId(GEngine->GetWorld(), i);
		if (TempPlayer && !TempPlayer->PlayerController->IsPrimaryPlayer()){
			GEngine->GameViewport->RemovePlayer(TempPlayer);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Removing Player ") + FString::FromInt(i));
		}
	}*/

	// if we had been split screen, toss the extra players now
	// @todo: I couldn't find a great way/place to make the main menu not be split screen - so treat this as temporary
	const int MaxSplitScreenPlayers = 4;
	ULocalPlayer* PlayersToRemove[MaxSplitScreenPlayers];
	int RemIndex = 0;

	for (FConstPlayerControllerIterator Iterator = GEngine->GameViewport->GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		// only remove local split screen controllers, so that the later loop still sends good messages to any remote controllers.
		APlayerController* Controller = *Iterator;
		if (Controller && Controller->IsLocalController() && !Controller->IsPrimaryPlayer())
		{
			
			ULocalPlayer* ExPlayer = Cast<ULocalPlayer>(Controller->Player);
			if (ExPlayer)
			{
				// don't actually remove players here because it affects our iterator.
				PlayersToRemove[RemIndex++] = ExPlayer;
				Controller->PawnPendingDestroy(Controller->GetPawn());
			}
		}
	}

	// safe cached remove
	for (int i = 0; i < RemIndex; ++i)
	{
		
		GEngine->GameViewport->RemovePlayer(PlayersToRemove[i]);
	}
	
}
