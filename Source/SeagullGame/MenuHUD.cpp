

#include "SeagullGame.h"
#include "MenuHUD.h"
#include "MainMenuWidget.h"


AMenuHUD::AMenuHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

/*void AMenuHUD::ReceiveDrawHUD(int32 SizeX, int32 SizeY)
{
	
}*/

void AMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Make sure the engine and viewport are valid
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		SAssignNew(MainMenuWidget, SMainMenuWidget)
			.MenuHUD(TWeakObjectPtr<AMenuHUD>(this));

		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(MainMenuWidget.ToSharedRef())
			);
	}
}

