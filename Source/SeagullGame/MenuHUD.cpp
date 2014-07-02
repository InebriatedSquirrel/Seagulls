

#include "SeagullGame.h"
#include "MenuHUD.h"


AMenuHUD::AMenuHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void AMenuHUD::ReceiveDrawHUD(int32 SizeX, int32 SizeY)
{
	DrawRect(FLinearColor::Black, 100.f, 100.f, 50.f, 50.f);
}

void AMenuHUD::PostInitializeComponents()
{
	//Super::PostInitializeComponents();
}

