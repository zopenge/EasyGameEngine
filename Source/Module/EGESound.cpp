//! @file     EGESound.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGESound.h"

IDynamicSHI*			gDynamicSHI				= _null;
ISoundResourceManager*	gSoundResourceManager	= _null;
ISoundModule*			gSoundModule			= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetSoundResourceManager
EGE_INTERNAL ISoundResourceManager* GetSoundResourceManager( )
{
	return gSoundResourceManager;
}

#undef GetSoundModule
EGE_INTERNAL ISoundModule* GetSoundModule( )
{
	return gSoundModule;
}

#undef GetDynamicSHI
EGE_INTERNAL IDynamicSHI* GetDynamicSHI( )
{
	return gDynamicSHI;
}

#undef CreateSoundModule
EGE_INTERNAL _boolean CreateSoundModule( )
{
	// Create module
	typedef PassRefPtr< SoundModule > SoundModulePassRef;
	SoundModulePassRef module = new SoundModule( );

	// Update the global module
	gSoundModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_SOUND_MODULE_PRIORITY );

	// Initialize module
	if ( module->Initialize( ) == _false )
	{
		// Unregister from module manager
		GetModuleManager( )->UnregisterModule( gSoundModule );

		// Use the null device when we failed to initialize sound module ( not return failed code )
		gSoundModule = &NullSound::GetInstance( ).GetSoundModule( );
	}

	return _true;
}