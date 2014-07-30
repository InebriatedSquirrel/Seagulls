#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "AudioWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SAudioWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

    ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().Padding(10.0f).FillHeight(2.0f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().Padding(10.0f).AutoWidth()
						[
							SNew(STextBlock)
							.Text(FString("Volume: "))
						]
						+ SHorizontalBox::Slot().FillWidth(10.0f).Padding(5.0f, 0.0f, 5.0f, 0.0f)
						[
							SNew(SVolumeControl)
							.Cursor(EMouseCursor::Hand)
							//.OnVolumeChanged(SAudioWidget::OnVolumeChanged)
							
						]

					]
					+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("Back"))
						.OnClicked(this, &SAudioWidget::BackClicked)
						.ButtonStyle(&MenuStyle->MenuButtonStyle)
						.TextStyle(&MenuStyle->MenuButtonTextStyle)
					]
					
                ]
        ];
}

FReply SAudioWidget::BackClicked()
{
	MenuHUD->ExitMenu();

	return FReply::Handled();
}

// SAudioWidget::OnVolumeChanged()
//{
//	MenuHUD->ExitMenu();
//	
//
//}
