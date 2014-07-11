#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "GraphicsWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SGraphicsWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

	Resolutions.Add(MakeShareable(new FString("1920x1200")));
	Resolutions.Add(MakeShareable(new FString("1920x1080")));
	Resolutions.Add(MakeShareable(new FString("1680x1050")));
	Resolutions.Add(MakeShareable(new FString("1600x900")));
	Resolutions.Add(MakeShareable(new FString("1280x720")));

	SelectedRes = Resolutions[4];

	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, *Resolutions[0] );
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, *Resolutions[1] );


	//Use this to grab data
	//UEngine::LoadConfig();

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
	}
	else if (NewCheckedState == ESlateCheckBoxState::Unchecked)
	{
		GEngine->GameViewport->ConsoleCommand("SETRES " + *SelectedRes + "w");
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

	GEngine->GameViewport->ConsoleCommand("SETRES " + *Item);
	//ResolutionButton->SetMenuContent(SNew(STextBlock).Text(*Item));
}
