#pragma once
 
#include "Slate.h"
 

class SMultiplayerMenuWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMultiplayerMenuWidget)
        : _MenuHUD()
    {
    }
 
    SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, MenuHUD);
 
    SLATE_END_ARGS()

	

public:
	//Constructs and lays out the Main Menu UI Widget.
    void Construct(const FArguments& args);

	TSharedPtr<FString> MapValue;
	TSharedPtr<FString> PlayerNum;
 
private:

	const struct FGlobalStyle* MenuStyle;
 

	TArray<TSharedPtr<FString>> MapValues;
	void MakeMapValues();
	TSharedPtr<STextComboBox> MapButton;
	void OnSelectedMap(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	TArray<TSharedPtr<FString>> PlayerNumValues;
	void MakePlayerNumValues();
	TSharedPtr<STextComboBox> PlayerNumButton;
	void OnSelectedPlayerNum(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FReply PlayMultiClicked();
	FReply PlayerNumClicked();
	FReply BackClicked();

    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};