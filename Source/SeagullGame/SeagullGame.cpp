

#include "SeagullGame.h"
#include "MenuStyles.h"

#include "SeagullGame.generated.inl"

/**
* Custom implementation of the Default Game Module.
**/
class FSeagullGameModule : public FDefaultGameModuleImpl
{
	/**
	* Called whenever the module is starting up. In here, we unregister any style sets (which may have been added by other modules) sharing our
	* style set's name, then initialize our style set.
	**/
	virtual void StartupModule() OVERRIDE
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
		FMenuStyles::Initialize();
	}

	/**
	* Called whenever the module is shutting down. Here, we simply tell our MenuStyles to shut down.
	**/
	virtual void ShutdownModule() OVERRIDE
	{
		FMenuStyles::Shutdown();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, SeagullGame, "SeagullGame" );
