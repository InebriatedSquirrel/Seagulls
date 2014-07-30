#pragma once
 
#include "Slate.h"
 

class SAudioWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SAudioWidget)
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

	FReply BackClicked();
	//SVolumeControl::FArguments OnVolumeChanged();

    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};