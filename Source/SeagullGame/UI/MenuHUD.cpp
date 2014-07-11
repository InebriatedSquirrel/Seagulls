

#include "SeagullGame/SeagullGame.h"
#include "MenuHUD.h"
#include "SeagullGame/UI/Widgets/MainMenuWidget.h"
#include "SeagullGame/UI/Widgets/CreditsWidget.h"
#include "SeagullGame/UI/Widgets/OptionsWidget.h"
#include "SeagullGame/UI/Widgets/LoadingScreenWidget.h"

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

	// Make sure the engine and viewport are valid
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		SAssignNew(OptionsWidget, SOptionsWidget)
			.MenuHUD(TWeakObjectPtr<AMenuHUD>(this));

		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(OptionsWidget.ToSharedRef())
			);
	}

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
void AMenuHUD::OpenLoadingScreen()
{
	GEngine->GameViewport->RemoveAllViewportWidgets();

	// Make sure the engine and viewport are valid
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		SAssignNew(LoadingScreenWidget, SLoadingScreenWidget)
			.MenuHUD(TWeakObjectPtr<AMenuHUD>(this));

		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(LoadingScreenWidget.ToSharedRef())
			);
	}
}