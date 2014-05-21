

#include "SeagullGame.h"
#include "PrimaryGameMode.h"
#include "BirdCharacter.h"

APrimaryGameMode::APrimaryGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultPawnClass = ABirdCharacter::StaticClass();
}

void APrimaryGameMode::BeginPlay()
{
	Super::BeginPlay();


}

