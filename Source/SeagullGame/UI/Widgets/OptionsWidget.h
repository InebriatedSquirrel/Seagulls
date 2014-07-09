#pragma once
 
#include "Slate.h"
 

class SOptionsWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SOptionsWidget)
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

	FReply GraphicsClicked();

	FReply BackClicked();
 
    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};