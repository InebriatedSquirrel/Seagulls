#pragma once
 
#include "Slate.h"
 

//Lays out and controls the Main Menu UI for our tutorial.

class SMainMenuUI : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SMainMenuUI)
        : _MenuHUD()
    {
    }
 
    SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MenuHUD);
 
    SLATE_END_ARGS()
 
public:
	//Constructs and lays out the Main Menu UI Widget.
    void Construct(const FArguments& args);
 
private:

     //Click handler for the Play Game! button - Calls MenuHUD's PlayGameClicked() event.
    FReply PlayGameClicked();
 

     //Click handler for the Quit Game button - Calls MenuHUD's QuitGameClicked() event.

    FReply QuitGameClicked();
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMainMenuHUD> MenuHUD;
};