

#include "SeagullGame.h"
#include "SeagullGameGameMode.h"
#include "SeagullGamePlayerController.h"

ASeagullGameGameMode::ASeagullGameGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = ASeagullGamePlayerController::StaticClass();
}


