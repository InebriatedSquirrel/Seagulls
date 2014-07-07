#pragma once
 
#include "Slate.h"
 

//Lays out and controls the Main Menu UI for our tutorial.

class SMainMenuWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SMainMenuWidget)
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

     //Click handler for the Play Game! button - Calls MenuHUD's PlayGameClicked() event.
    FReply PlayGameClicked();
 
    //Click handler for the Quit Game button - Calls MenuHUD's QuitGameClicked() event.
    FReply QuitGameClicked();
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};