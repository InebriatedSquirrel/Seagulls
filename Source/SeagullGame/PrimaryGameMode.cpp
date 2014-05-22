

#include "SeagullGame.h"
#include "PrimaryGameMode.h"
#include "BirdPawn.h"

APrimaryGameMode::APrimaryGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultPawnClass = ABirdPawn::StaticClass();
}

void APrimaryGameMode::BeginPlay()
{
	Super::BeginPlay();


}

