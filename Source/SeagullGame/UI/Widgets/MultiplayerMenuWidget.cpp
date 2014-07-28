#include "SeagullGame/SeagullGame.h"
 
#include "SeagullGame/UI/MenuHUD.h"
#include "MultiplayerMenuWidget.h"
#include "SeagullGame/UI/GlobalMenuStyle.h"
#include "SeagullGame/UI/MenuStyles.h"
 
void SMultiplayerMenuWidget::Construct(const FArguments& args)
{
    MenuHUD = args._MenuHUD;

	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalMenuStyle");

	this->MakeMapValues();
	MapValue = MapValues[1];
	MenuHUD->UserMultiMap = *MapValue;

	this->MakePlayerNumValues();
	// Set the initial Player number value
	for (int32 i = 0; i < PlayerNumValues.Num(); i++)
	{
		if (*PlayerNumValues[i] == *MenuHUD->UserNumMultiPlayers)
		{
			PlayerNum = PlayerNumValues[i];
			break;
		}

	}

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
						SAssignNew(this->MapButton, STextComboBox)
						.OptionsSource(&MapValues)
						.OnSelectionChanged(this, &SMultiplayerMenuWidget::OnSelectedMap)
						.InitiallySelectedItem(MapValue)
						.Cursor(EMouseCursor::Hand)
					]
					+ SVerticalBox::Slot().Padding(10.0f)
					[
						SAssignNew(this->PlayerNumButton, STextComboBox)
						.OptionsSource(&PlayerNumValues)
						.OnSelectionChanged(this, &SMultiplayerMenuWidget::OnSelectedPlayerNum)
						.InitiallySelectedItem(PlayerNum)
						.Cursor(EMouseCursor::Hand)
					]
					+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Text(FText::FromString("Play"))
							.OnClicked(this, &SMultiplayerMenuWidget::PlayMultiClicked)
							.ButtonStyle(&MenuStyle->MenuButtonStyle)
							.TextStyle(&MenuStyle->MenuButtonTextStyle)
					]
					+ SVerticalBox::Slot().Padding(10.0f).FillHeight(4.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("Back"))
						.OnClicked(this, &SMultiplayerMenuWidget::BackClicked)
						.ButtonStyle(&MenuStyle->MenuButtonStyle)
						.TextStyle(&MenuStyle->MenuButtonTextStyle)
					]
                ]
        ];
}

FReply SMultiplayerMenuWidget::PlayMultiClicked()
{
	MenuHUD->OpenLoadingScreen();
	MenuHUD->PlayMultiPlayerClicked();

	return FReply::Handled();
}

FReply SMultiplayerMenuWidget::BackClicked()
{
	MenuHUD->ExitMenu();

	return FReply::Handled();
}

void SMultiplayerMenuWidget::OnSelectedMap(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	MapValue = Item;
	MenuHUD->UserMultiMap = *Item;
	MapButton->SetSelectedItem(Item);
	MapButton->RefreshOptions();
}

void SMultiplayerMenuWidget::OnSelectedPlayerNum(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	PlayerNum = Item;
	MenuHUD->UserNumMultiPlayers = *Item;
	PlayerNumButton->SetSelectedItem(Item);
	PlayerNumButton->RefreshOptions();

	MenuHUD->PlayerNumClicked();
	MenuHUD->OnSaveSettings();
}

void SMultiplayerMenuWidget::MakeMapValues()
{
	MapValues.Add(MakeShareable(new FString("MultiplayerOrphanDrop")));
	MapValues.Add(MakeShareable(new FString("MultiplayerDestruction")));
}

void SMultiplayerMenuWidget::MakePlayerNumValues()
{
	PlayerNumValues.Add(MakeShareable(new FString("2 Players")));
	PlayerNumValues.Add(MakeShareable(new FString("3 Players")));
	PlayerNumValues.Add(MakeShareable(new FString("4 Players")));
}
