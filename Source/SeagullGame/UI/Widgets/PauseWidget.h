#pragma once
 
#include "Slate.h"
 

class SPauseWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SPauseWidget)
        : _BirdHUD()
    {
    }
 
    SLATE_ARGUMENT(TWeakObjectPtr<class ABirdHUD>, BirdHUD);
 
    SLATE_END_ARGS()

	

public:
	//Constructs and lays out the Main Menu UI Widget.
    void Construct(const FArguments& args);
 
private:

	const struct FGlobalStyle* MenuStyle;

	FReply ExitClicked();
	FReply ResumeClicked();
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class ABirdHUD> BirdHUD;
};