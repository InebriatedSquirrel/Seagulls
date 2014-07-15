#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "GraphicsWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SGraphicsWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

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

	// Set the initial resolution
	SelectedRes = MakeShareable(&MenuHUD->UserRes);

	// See if the inital res is a predetermined value
	for (int32 i = 0; i < Resolutions.Num(); i++)
	{
		if (*Resolutions[i] == MenuHUD->UserRes)
		{
			SelectedRes = Resolutions[i];
		}
		break;
	}
	
	if (MenuHUD->useFullscreen)
	{
		this->FullScreenClicked(ESlateCheckBoxState::Checked);
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
					
					+ SHorizontalBox::Slot().Padding(10.0f)
					[
						SNew(SVerticalBox)

						+ SVerticalBox::Slot().Padding(10.0f)
						[
							SAssignNew(this->ResolutionButton, SComboBox<TSharedPtr<FString>>)
							.OptionsSource(&Resolutions)
							.OnGenerateWidget(this, &SGraphicsWidget::OnGenerateWidget)
							.OnSelectionChanged(this, &SGraphicsWidget::OnSelectedRes)
							.InitiallySelectedItem(SelectedRes)
							.Cursor(EMouseCursor::Hand)
							.Content()
							[
								SAssignNew(this->ResDisplay, STextBlock)
									.Text(*SelectedRes)
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
								SNew(SCheckBox)
								.OnCheckStateChanged(this, &SGraphicsWidget::FullScreenClicked)
								.Cursor(EMouseCursor::Hand)
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
                ]
        ];
}

FReply SGraphicsWidget::BackClicked()
{
	MenuHUD->ExitMenu();

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
}

TSharedRef<SWidget> SGraphicsWidget::OnGenerateWidget(TSharedPtr<FString> Item)
{
	return SNew(STextBlock).Text(*Item);

}

void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	SelectedRes = Item;
	ResolutionButton->SetSelectedItem(Item);
	ResDisplay->SetText(*SelectedRes);
	ResolutionButton->RefreshOptions();

	if (isFullscreen == true)
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *Item + "f");
	}
	else
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *Item + "w");
	}
	//ResolutionButton->SetMenuContent(SNew(STextBlock).Text(*Item));
}
