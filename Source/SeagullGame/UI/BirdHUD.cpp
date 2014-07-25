

#include "SeagullGame/SeagullGame.h"
#include "BirdHUD.h"
#include "SeagullGame/UI/Widgets/PauseWidget.h"

ABirdHUD::ABirdHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void ABirdHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void ABirdHUD::OpenPauseMenu()
{
	// Make sure the engine and viewport are valid
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		SAssignNew(PauseWidget, SPauseWidget)
			.BirdHUD(TWeakObjectPtr<ABirdHUD>(this));

		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(PauseWidget.ToSharedRef())
			);
	}
}

void ABirdHUD::ClosePauseMenu()
{
	GEngine->GameViewport->RemoveAllViewportWidgets();
}
