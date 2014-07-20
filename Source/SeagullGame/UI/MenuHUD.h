

#pragma once

#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class AMenuHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostInitializeComponents() OVERRIDE;

	//--------Main Menu Buttons------

	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void SinglePlayerClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void MultiPlayerClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void OptionsClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void CreditsClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void QuitGameClicked();

	//----------Graphics Options Events----------

	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnResolutionSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnFullscreenSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnResScaleSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnViewDistanceSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnAASet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnPostProccessingSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnShadowsSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnTexturesSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnDetailSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnSaveSettings();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Graphics")
	void OnRevert();

	//------Options Buttons--------

	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Options")
	void GraphicsClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Options")
	void ControlsClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Options")
	void AudioClicked();

	// General buttons/functions
	UFUNCTION(BlueprintCallable, Category = "Menus|General")
	void ExitMenu();
	UFUNCTION(BlueprintCallable, Category = "Menus|General")
	void OpenLoadingScreen();
	UFUNCTION(BlueprintCallable, Category = "Menus|General")
	void ApplySettings();

	// Holds the current menu in a string
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Menus|General")
	FString CurrentMenu;

	//------User Values--------

	// Resolution value set by the user - Default is 1280x720
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserRes;
	// Fullscreen toggle set by the user - Default is true
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	bool UseFullscreen;
	// Resolution Scale set by the user - Default is 100
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserResScale;
	// View Distance set by the user - Default is 1.0
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserViewDistance;
	// Anti-Aliasing set by the user - Default is 4
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserAA;
	// Post Processing Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserPostProcessing;
	// Shadows Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserShadows;
	// Texture Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserTextures;
	// Effects Quality set by the user - Default is 3
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserEffects;
	// Detail Level set by the user - Default is 2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Saved Data")
	FString UserDetail;


	// Functions for opening new widgets/menus in slate
	void OpenOptionsMenu();
	void OpenGraphicsMenu();
	void OpenCredits();

private:
	/**
	* Reference to the Main Menu Slate UI.
	**/
	TSharedPtr<class SMainMenuWidget> MainMenuWidget; 

	TSharedPtr<class SCreditsWidget> CreditsWidget;

	TSharedPtr<class SOptionsWidget> OptionsWidget;

	TSharedPtr<class SGraphicsWidget> GraphicsWidget;

	TSharedPtr<class SLoadingScreenWidget> LoadingScreenWidget;
};
