#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "MainMenuWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SMainMenuWidget::Construct(const FArguments& args)
{
	MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

	ChildSlot
		[
			SNew(SOverlay)
			/*+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(&MenuStyle->LogoBrush)
			]*/
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().Padding(10.0f).AutoHeight().VAlign(VAlign_Center).HAlign(HAlign_Center)
					[
						SNew(SImage)
						.Image(&MenuStyle->LogoBrush)
					]
					+ SVerticalBox::Slot().Padding(10.0f).AutoHeight().VAlign(VAlign_Center).HAlign(HAlign_Center)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().MaxWidth(200.f)
						[
							SNew(SVerticalBox)
							
							+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
							[
								SNew(SButton)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.Text(FText::FromString("Single Player"))
									.OnClicked(this, &SMainMenuWidget::SinglePlayerClicked)
									.ButtonStyle(&MenuStyle->MenuButtonStyle)
									.TextStyle(&MenuStyle->MenuButtonTextStyle)
							]
							+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
							[
								SNew(SButton)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.Text(FText::FromString("Multi Player"))
									.OnClicked(this, &SMainMenuWidget::MultiPlayerClicked)
									.ButtonStyle(&MenuStyle->MenuButtonStyle)
									.TextStyle(&MenuStyle->MenuButtonTextStyle)
							]
							+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
							[
								SNew(SButton)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.Text(FText::FromString("Options"))
									.OnClicked(this, &SMainMenuWidget::OptionsClicked)
									.ButtonStyle(&MenuStyle->MenuButtonStyle)
									.TextStyle(&MenuStyle->MenuButtonTextStyle)
							]
							+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
							[
								SNew(SButton)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.Text(FText::FromString("Credits"))
									.OnClicked(this, &SMainMenuWidget::CreditsClicked)
									.ButtonStyle(&MenuStyle->MenuButtonStyle)
									.TextStyle(&MenuStyle->MenuButtonTextStyle)
							]
							+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
							[
								SNew(SButton)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.Text(FText::FromString("Quit Game"))
									.OnClicked(this, &SMainMenuWidget::QuitGameClicked)
									.ButtonStyle(&MenuStyle->MenuButtonStyle)
									.TextStyle(&MenuStyle->MenuButtonTextStyle)
								
							]
						]
					]
				]
        ];
}
 
FReply SMainMenuWidget::SinglePlayerClicked()
{
	MenuHUD->OpenLoadingScreen();
    MenuHUD->SinglePlayerClicked();
    return FReply::Handled();
}

FReply SMainMenuWidget::MultiPlayerClicked()
{
	MenuHUD->OpenMultiplayerMenu();
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
