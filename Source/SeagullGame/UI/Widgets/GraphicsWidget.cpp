#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "GraphicsWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SGraphicsWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

	Resolutions.Add(MakeShareable(new FString("1920x1080")));
	Resolutions.Add(MakeShareable(new FString("1280x720")));

	SelectedRes = *Resolutions[0];

	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, *Resolutions[0] );
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, *Resolutions[1] );

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
							SNew(SButton)
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								.Text(FText::FromString("Back"))
								.OnClicked(this, &SGraphicsWidget::BackClicked)
								.Cursor(EMouseCursor::Hand)
						]
						+ SVerticalBox::Slot().Padding(10.0f)
						[
							SAssignNew(this->ResolutionButton, SComboBox<TSharedPtr<FString>>)
							.OptionsSource(&Resolutions)
							.OnGenerateWidget(this, &SGraphicsWidget::OnGenerateWidget)
							.OnSelectionChanged(this, &SGraphicsWidget::OnSelectedRes)
							.InitiallySelectedItem(Resolutions[0])
							.Cursor(EMouseCursor::Hand)
							.Content()
							[
								SNew(STextBlock).Text(SelectedRes)
							]
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

TSharedRef<SWidget> SGraphicsWidget::OnGenerateWidget(TSharedPtr<FString> Item)
{
	return SNew(STextBlock).Text(*Item);
}

void SGraphicsWidget::OnSelectedRes(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	SelectedRes = *Item;
	ResolutionButton->SetSelectedItem(Item);
	ResolutionButton->RefreshOptions();
	//ResolutionButton->SetMenuContent(SNew(STextBlock).Text(*Item));
}
