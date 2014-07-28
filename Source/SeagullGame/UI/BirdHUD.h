

#pragma once

#include "GameFramework/HUD.h"
#include "BirdHUD.generated.h"

/**
 * 
 */
UCLASS()
class ABirdHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostInitializeComponents() OVERRIDE;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pause Menu")
	void QuitGame();
	UFUNCTION(BlueprintImplementableEvent, Category = "Pause Menu")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
	void OpenPauseMenu();

	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
	void ClosePauseMenu();

private:

	TSharedPtr<class SPauseWidget> PauseWidget;
};
