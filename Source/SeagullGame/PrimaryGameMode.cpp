

#include "SeagullGame.h"
#include "PrimaryGameMode.h"
#include "BirdCharacter.h"

APrimaryGameMode::APrimaryGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//DefaultPawnClass = ABirdPawn::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BirdCharacterBlueprint.BirdCharacterBlueprint'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}
}

void APrimaryGameMode::BeginPlay()
{
	Super::BeginPlay();


}

