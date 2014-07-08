

#include "SeagullGame.h"
#include "MenuHUD.h"
#include "MainMenuWidget.h"
#include "CreditsWidget.h"

AMenuHUD::AMenuHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}


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
	CurrentMenu = "MainMenu";
}

void AMenuHUD::OpenOptionsMenu()
{
	GEngine->GameViewport->RemoveAllViewportWidgets();

	CurrentMenu = "Options";
}

void AMenuHUD::OpenCredits()
{
	GEngine->GameViewport->RemoveAllViewportWidgets();

	// Make sure the engine and viewport are valid
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		SAssignNew(CreditsWidget, SCreditsWidget)
			.MenuHUD(TWeakObjectPtr<AMenuHUD>(this));

		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(CreditsWidget.ToSharedRef())
			);
	}
	CurrentMenu = "Credits";
}

void AMenuHUD::ExitMenu()
{
	if (CurrentMenu != "MainMenu")
	{
		GEngine->GameViewport->RemoveAllViewportWidgets();

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
		CurrentMenu = "MainMenu";
	}
}

