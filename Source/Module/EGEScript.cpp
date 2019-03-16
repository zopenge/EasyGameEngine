//! @file     EGEScript.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEScript.h"

IScriptResourceManager*	gScriptResourceManager	= _null;
IScriptModule*			gScriptModule			= _null;

_scriptSystem*			gInternalScriptSystem	= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetScriptResourceManager
EGE_INTERNAL IScriptResourceManager* GetScriptResourceManager( )
{
	return gScriptResourceManager;
}

#undef GetScriptModule
EGE_INTERNAL IScriptModule* GetScriptModule( )
{
	return gScriptModule;
}

#undef CreateScriptModule
EGE_INTERNAL _boolean CreateScriptModule( _SCRIPT type )
{
	// Create module
	typedef PassRefPtr< ScriptModule > ScriptModulePassRef;
	ScriptModulePassRef module = new ScriptModule( );

	// Update the global module
	gScriptModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_SCRIPT_MODULE_PRIORITY );

	// Initialize
	_boolean ret = EGE_BOOLEAN( module->Initialize( type ) );
	return ret;
}