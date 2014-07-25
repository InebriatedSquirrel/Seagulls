#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/BirdHUD.h"
#include "PauseWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SPauseWidget::Construct(const FArguments& args)
{
    BirdHUD = args._BirdHUD;

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
						.Text(FText::FromString("Resume"))
						.OnClicked(this, &SPauseWidget::ResumeClicked)
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("Exit"))
						.OnClicked(this, &SPauseWidget::ExitClicked)
					]
					
                ]
        ];
}

FReply SPauseWidget::ResumeClicked()
{
	BirdHUD->ResumeGame();

	return FReply::Handled();
}

FReply SPauseWidget::ExitClicked()
{
	BirdHUD->QuitGame();

	return FReply::Handled();
}
