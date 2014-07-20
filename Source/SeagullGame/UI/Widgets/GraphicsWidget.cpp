#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "GraphicsWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SGraphicsWidget::Construct(const FArguments& args)
{
	MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

	//----Get Initial values-----

	CheckFullScreen();

	this->MakeResolutions();
	// Set the initial resolution
	for (int32 i = 0; i < Resolutions.Num(); i++)
	{
		if (*Resolutions[i] == MenuHUD->UserRes)
		{
			SelectedRes = Resolutions[i];
			break;
		}
		
	}

	this->MakeScaleValues();
	// Set the initial Scale value
	for (int32 i = 0; i < ScaleValues.Num(); i++)
	{
		if (*ScaleValues[i] == *MenuHUD->UserResScale)
		{
			ResScaleVal = ScaleValues[i];
			break;
		}
		
	}

	// Slate widget building
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
				// Column 1
				+ SHorizontalBox::Slot().Padding(10.0f)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot().HAlign(HAlign_Left).AutoWidth()
						[
							SNew(STextBlock)
							.Text(FString("Resolution:"))
							.ColorAndOpacity(FLinearColor::Black)
						]
						+ SHorizontalBox::Slot().HAlign(HAlign_Right).AutoWidth()
							[
								SAssignNew(this->ResolutionButton, STextComboBox)
								.OptionsSource(&Resolutions)
								.OnSelectionChanged(this, &SGraphicsWidget::OnSelectedRes)
								.InitiallySelectedItem(SelectedRes)
								.Cursor(EMouseCursor::Hand)
							]
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot().HAlign(HAlign_Left).AutoWidth()
						[
							SNew(STextBlock)
							.Text(FString("FullScreen"))
							.ColorAndOpacity(FLinearColor::Black)
						]
						+ SHorizontalBox::Slot().HAlign(HAlign_Right)
						[
							SAssignNew(FullscreenButton, SCheckBox)
							.OnCheckStateChanged(this, &SGraphicsWidget::FullScreenClicked)
							.Cursor(EMouseCursor::Hand)
							.IsChecked(CheckFullScreen())
						]
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("Back"))
						.OnClicked(this, &SGraphicsWidget::BackClicked)
						.Cursor(EMouseCursor::Hand)
					]
				]
				// Column 2
				+ SHorizontalBox::Slot().Padding(10.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).AutoWidth()
						[
							SNew(STextBlock)
							.Text(FString("Resolution Scale"))
							.ColorAndOpacity(FLinearColor::Black)
						]
						+ SHorizontalBox::Slot().HAlign(HAlign_Right)
						[
							SAssignNew(this->ResScaleButton, STextComboBox)
							.OptionsSource(&ScaleValues)
							.OnSelectionChanged(this, &SGraphicsWidget::OnSelectedScale)
							.InitiallySelectedItem(ResScaleVal)
							.Cursor(EMouseCursor::Hand)
						]
					]
					SNew(SVerticalBox)
						+ SVerticalBox::Slot().Padding(10.0f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().HAlign(HAlign_Left).AutoWidth()
							[
								SNew(STextBlock)
								.Text(FString("Resolution Scale"))
								.ColorAndOpacity(FLinearColor::Black)
							]
							+ SHorizontalBox::Slot().HAlign(HAlign_Right)
								[
									SAssignNew(this->ResScaleButton, STextComboBox)
									.OptionsSource(&ScaleValues)
									.OnSelectionChanged(this, &SGraphicsWidget::OnSelectedScale)
									.InitiallySelectedItem(ResScaleVal)
									.Cursor(EMouseCursor::Hand)
								]
						]
						/*+ SVerticalBox::Slot().Padding(10.0f)
						[
							SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Apply"))
							.OnClicked(this, &SGraphicsWidget::ApplyClicked)
							.Cursor(EMouseCursor::Hand)
						]*/
				]
					// Column 3
					/*+ SHorizontalBox::Slot().Padding(10.0f)
					[
						
					]*/
				
				
			]
        ];
}

FReply SGraphicsWidget::BackClicked()
{
	MenuHUD->ExitMenu();
	MenuHUD->OnSaveSettings();
	return FReply::Handled();
}

FReply SGraphicsWidget::ApplyClicked()
{
	return FReply::Handled();
}

void SGraphicsWidget::FullScreenClicked(const ESlateCheckBoxState::Type NewCheckedState)
{
	if (NewCheckedState == ESlateCheckBoxState::Checked)
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *SelectedRes + "f");
		isFullscreen = true;
	}
	else if (NewCheckedState == ESlateCheckBoxState::Unchecked)
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *SelectedRes + "w");
		isFullscreen = false;
		
	}
	MenuHUD->UseFullscreen = isFullscreen;

}

void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	SelectedRes = Item;
	MenuHUD->UserRes = *Item;
	ResolutionButton->SetSelectedItem(Item);
	ResolutionButton->RefreshOptions();

	if (isFullscreen == true)
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *Item + "f");
	}
	else
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *Item + "w");
	}
	PendingChanges = true;
}

void SGraphicsWidget::OnSelectedScale(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	ResScaleVal = Item;
	MenuHUD->UserResScale = *Item;
	ResScaleButton->SetSelectedItem(Item);
	ResScaleButton->RefreshOptions();

	if (*Item == "100%")
	{
		GEngine->GameViewport->ConsoleCommand("r.ScreenPercentage 100");
	}
	else if (*Item == "75%")
	{
		GEngine->GameViewport->ConsoleCommand("r.ScreenPercentage 75");
	}
	else if (*Item == "50%")
	{
		GEngine->GameViewport->ConsoleCommand("r.ScreenPercentage 50");
	}
	PendingChanges = true;
}

void SGraphicsWidget::MakeResolutions()
{
	// Load up resolution values
	Resolutions.Add(MakeShareable(new FString("2560x1440")));
	Resolutions.Add(MakeShareable(new FString("1920x1200")));
	Resolutions.Add(MakeShareable(new FString("1920x1080")));
	Resolutions.Add(MakeShareable(new FString("1680x1050")));
	Resolutions.Add(MakeShareable(new FString("1600x900")));
	Resolutions.Add(MakeShareable(new FString("1440x900")));
	Resolutions.Add(MakeShareable(new FString("1280x1024")));
	Resolutions.Add(MakeShareable(new FString("1366x768")));
	Resolutions.Add(MakeShareable(new FString("1360x768")));
	Resolutions.Add(MakeShareable(new FString("1280x800")));
	Resolutions.Add(MakeShareable(new FString("1280x720")));
	Resolutions.Add(MakeShareable(new FString("1024x768")));
}

ESlateCheckBoxState::Type SGraphicsWidget::CheckFullScreen()
{
	if (MenuHUD->UseFullscreen)
	{
		return ESlateCheckBoxState::Checked;
		isFullscreen = true;
	}
	else
	{
		return ESlateCheckBoxState::Unchecked;
		isFullscreen = false;
	}
}

void SGraphicsWidget::MakeScaleValues()
{
	ScaleValues.Add(MakeShareable(new FString("50%")));
	ScaleValues.Add(MakeShareable(new FString("75%")));
	ScaleValues.Add(MakeShareable(new FString("100%")));
}
