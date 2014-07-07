#include "SeagullGame.h"
 
#include "MenuHUD.h"
#include "MainMenuWidget.h"
#include "GlobalMenuStyle.h"
#include "MenuStyles.h"
 
void SMainMenuWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");

    ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Top)
                [
                    SNew(STextBlock)
                        .ColorAndOpacity(FLinearColor::White)
                        .ShadowColorAndOpacity(FLinearColor::Black)
                        .ShadowOffset(FIntPoint(-1, 1))
                        .Font(FSlateFontInfo("Arial", 26))
                        .Text(FText::FromString("Main Menu"))
                ]
            + SOverlay::Slot()
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot()
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Play Game!"))
                                .OnClicked(this, &SMainMenuWidget::PlayGameClicked)
                        ]
                    + SVerticalBox::Slot()
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Quit Game"))
                                .OnClicked(this, &SMainMenuWidget::QuitGameClicked)
                        ]
                ]
        ];
}
 
FReply SMainMenuWidget::PlayGameClicked()
{
    MenuHUD->PlayGameClicked();
    return FReply::Handled();
}
 
FReply SMainMenuWidget::QuitGameClicked()
{
    MenuHUD->QuitGameClicked();
    return FReply::Handled();
}