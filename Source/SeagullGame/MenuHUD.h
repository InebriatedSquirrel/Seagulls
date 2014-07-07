

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


protected:

	//void AMenuHUD::ReceiveDrawHUD(int SizeX, int SizeY);

private:
	/**
	* Reference to the Main Menu Slate UI.
	**/
	TSharedPtr<class SMainMenuWidget> MainMenuWidget; 
};
