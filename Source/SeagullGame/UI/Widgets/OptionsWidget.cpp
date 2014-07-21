#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "OptionsWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SOptionsWidget::Construct(const FArguments& args)
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
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Graphics"))
							.OnClicked(this, &SOptionsWidget::GraphicsClicked)
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Controls"))
							.OnClicked(this, &SOptionsWidget::ControlsClicked)
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Audio"))
							.OnClicked(this, &SOptionsWidget::AudioClicked)
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Back"))
							.OnClicked(this, &SOptionsWidget::BackClicked)
					]
                ]
        ];
}

FReply SOptionsWidget::GraphicsClicked()
{
	MenuHUD->GraphicsClicked();
	MenuHUD->OpenGraphicsMenu();

	return FReply::Handled();
}

FReply SOptionsWidget::ControlsClicked()
{
	MenuHUD->ControlsClicked();

	return FReply::Handled();
}

FReply SOptionsWidget::AudioClicked()
{
	MenuHUD->AudioClicked();
	MenuHUD->OpenAudioMenu();

	return FReply::Handled();
}

FReply SOptionsWidget::BackClicked()
{
	MenuHUD->ExitMenu();

	return FReply::Handled();
}
