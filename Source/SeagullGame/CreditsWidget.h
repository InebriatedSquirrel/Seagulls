#pragma once
 
#include "Slate.h"
 

class SCreditsWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SCreditsWidget)
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

	FReply SinglePlayerClicked();

	FReply MultiPlayerClicked();

	FReply OptionsClicked();

	FReply CreditsClicked();
 
    //Click handler for the Quit Game button - Calls MenuHUD's QuitGameClicked() event.
    FReply QuitGameClicked();
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};