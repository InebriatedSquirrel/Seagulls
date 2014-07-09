#pragma once
 
#include "SlateWidgetStyleContainerBase.h"
 
#include "GlobalMenuStyle.generated.h"
 
/**
 * Provides a group of global style settings for our game menus!
 **/
USTRUCT()
struct FGlobalStyle : public FSlateWidgetStyle
{
    GENERATED_USTRUCT_BODY()
 
    /**
     * Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
     **/
    virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const OVERRIDE;
 
    /**
     * Stores the TypeName for our widget style.
     **/
    static const FName TypeName;
 
    /**
     * Retrieves the type name for our global style, which will be used by our Style Set to load the right file.
     **/
    virtual const FName GetTypeName() const OVERRIDE;
 
    /**
     * Allows us to set default values for our various styles.
     **/
    static const FGlobalStyle& GetDefault();
 
    /**
     * Style that define the appearance of all menu buttons.
     **/
    UPROPERTY(EditAnywhere, Category = Appearance)
    FButtonStyle MenuButtonStyle;
 
    /**
     * Style that defines the text on all of our menu buttons.
     **/
    UPROPERTY(EditAnywhere, Category = Appearance)
    FTextBlockStyle MenuButtonTextStyle;
 
    /**
     * Style that defines the text for our menu title.
     **/
    UPROPERTY(EditAnywhere, Category = Appearance)
    FTextBlockStyle MenuTitleStyle;

	/**
	* The brush used to draw the logo
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush LogoBrush;
		FGlobalStyle& SetLogoBrush(const FSlateBrush& InLogoBrush) { LogoBrush = InLogoBrush; return *this; }

	/**
	* The brush used to draw the credits screen
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush CreditsBrush;
		FGlobalStyle& SetCreditsBrush(const FSlateBrush& InCreditsBrush) { CreditsBrush = InCreditsBrush; return *this; }

	/**
	* The brush used to draw the loading screen
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush LoadingScreenBrush;
		FGlobalStyle& SetLoadingScreenBrush(const FSlateBrush& InLoadingScreenBrush) { LoadingScreenBrush = InLoadingScreenBrush; return *this; }
};
 
/**
 * Provides a widget style container to allow us to edit properties in-editor.
 **/
UCLASS(hidecategories = Object, MinimalAPI)
class UGlobalMenuStyle : public USlateWidgetStyleContainerBase
{
    GENERATED_UCLASS_BODY()
 
public:
    /**
     * This is our actual Style object.
     **/
    UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
    FGlobalStyle MenuStyle;
 
    /**
     * Retrievs the style that this container manages.
     **/
    virtual const struct FSlateWidgetStyle* const GetStyle() const OVERRIDE;
};