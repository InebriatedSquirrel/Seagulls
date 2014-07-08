#include "SeagullGame.h"
 
#include "MenuHUD.h"
#include "MainMenuWidget.h"
#include "GlobalMenuStyle.h"
#include "MenuStyles.h"
 
void SMainMenuWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

    ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Top)
                [
					SNew(SImage)
					.Image(&MenuStyle->LogoBrush)
                ]
            + SOverlay::Slot()
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
                    SNew(SVerticalBox)
					+ SVerticalBox::Slot().Padding(10.0f)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Single Player"))
                                .OnClicked(this, &SMainMenuWidget::SinglePlayerClicked)
                        ]
					+ SVerticalBox::Slot().Padding(10.0f)
						[
							SNew(SButton)
							.Text(FText::FromString("Multi Player"))
							.OnClicked(this, &SMainMenuWidget::MultiPlayerClicked)
						]
					+ SVerticalBox::Slot().Padding(10.0f)
						[
							SNew(SButton)
							.Text(FText::FromString("Options"))
							.OnClicked(this, &SMainMenuWidget::OptionsClicked)
						]
					+ SVerticalBox::Slot().Padding(10.0f)
						[
							SNew(SButton)
							.Text(FText::FromString("Credits"))
							.OnClicked(this, &SMainMenuWidget::CreditsClicked)
						]
					+ SVerticalBox::Slot().Padding(10.0f)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Quit Game"))
                                .OnClicked(this, &SMainMenuWidget::QuitGameClicked)
                        ]
                ]
        ];
}
 
FReply SMainMenuWidget::SinglePlayerClicked()
{
    MenuHUD->SinglePlayerClicked();
    return FReply::Handled();
}

FReply SMainMenuWidget::MultiPlayerClicked()
{
	MenuHUD->MultiPlayerClicked();
	return FReply::Handled();
}

FReply SMainMenuWidget::OptionsClicked()
{
	MenuHUD->OpenOptionsMenu();
	MenuHUD->OptionsClicked();

	return FReply::Handled();
}

FReply SMainMenuWidget::CreditsClicked()
{
	MenuHUD->CreditsClicked();
	MenuHUD->OpenCredits();

	return FReply::Handled();
}

FReply SMainMenuWidget::QuitGameClicked()
{
    MenuHUD->QuitGameClicked();
    return FReply::Handled();
}