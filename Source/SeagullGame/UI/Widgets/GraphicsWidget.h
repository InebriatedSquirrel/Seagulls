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
	TSharedPtr<FString> ResScaleVal;
	TSharedPtr<FString> DistanceVal;
 
private:

	const struct FGlobalStyle* MenuStyle;

	// Resolution
	TArray<TSharedPtr<FString>> Resolutions;
	void MakeResolutions();
	TSharedPtr<STextComboBox> ResolutionButton;
	void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
	
	// Resolution Scale
	TArray<TSharedPtr<FString>> ScaleValues;
	void MakeScaleValues();
	TSharedPtr<STextComboBox> ResScaleButton;
	void SGraphicsWidget::OnSelectedScale(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	// View Distance
	TArray<TSharedPtr<FString>> DistValues;
	void MakeDistValues();
	TSharedPtr<STextComboBox> ViewDistanceButton;
	void SGraphicsWidget::OnSelectedDist(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	// Fullscreen toggle
	TSharedPtr<SCheckBox> FullscreenButton;
	void FullScreenClicked(const ESlateCheckBoxState::Type NewCheckedState);
	ESlateCheckBoxState::Type CheckFullScreen();

	FReply BackClicked();
	FReply ApplyClicked();

	TSharedRef<SWidget> SGraphicsWidget::OnGenerateWidget(TSharedPtr<FString> Item);

    //Stores a weak reference to the HUD controlling this class.
    TWeakObjectPtr<class AMenuHUD> MenuHUD;
};