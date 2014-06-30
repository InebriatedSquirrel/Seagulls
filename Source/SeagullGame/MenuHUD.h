

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

protected:
	void AMenuHUD::ReceiveDrawHUD(int SizeX, int SizeY);
};
