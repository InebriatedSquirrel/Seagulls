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

	TSharedPtr<FString> SelectedRes;
	bool isFullscreen = false;
 
private:

	const struct FGlobalStyle* MenuStyle;

	// Resolution
	TArray<TSharedPtr<FString>> Resolutions;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ResolutionButton;
	void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
	TSharedPtr<class STextBlock> ResDisplay;


	void FullScreenClicked(const ESlateCheckBoxState::Type NewCheckedState);

	FReply BackClicked();

	TSharedRef<SWidget> SGraphicsWidget::OnGenerateWidget(TSharedPtr<FString> Item);

    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};