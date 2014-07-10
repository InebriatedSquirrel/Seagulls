#pragma once
 
#include "Slate.h"
 

class SGraphicsWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SGraphicsWidget)
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

	TArray<TSharedPtr<FString>> Resolutions;

	TSharedPtr<SComboBox<TSharedPtr<FString>>> ResolutionButton;

	FReply BackClicked();

	TSharedRef<SWidget> SGraphicsWidget::OnGenerateWidget(TSharedPtr<FString> Item);

	void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};