#pragma once
 
#include "Slate.h"
 

class SLoadingScreenWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SLoadingScreenWidget)
        : _MenuHUD()
    {
    }
 
    SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, MenuHUD);
 
    SLATE_END_ARGS()

	

public:
	//Constructs and lays out the Main Menu UI Widget.
    void Construct(const FArguments& args);
 
private:

	const struct FGlobalStyle* MenuStyle;
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};