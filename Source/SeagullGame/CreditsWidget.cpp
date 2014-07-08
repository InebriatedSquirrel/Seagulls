#include "SeagullGame.h"
 
#include "MenuHUD.h"
#include "CreditsWidget.h"
#include "GlobalMenuStyle.h"
#include "MenuStyles.h"
 
void SCreditsWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

    ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
                .HAlign(HAlign_Left)
                .VAlign(VAlign_Top)
                [
					SNew(SImage)
					.Image(&MenuStyle->CreditsBrush)
                ]
        ];
}