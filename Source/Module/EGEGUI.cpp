//! @file     EGEGUI.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEGUI.h"

// Global variables
IGUIModule*				gGUIModule			= _null;
IGUIResourceManager*	gGUIResourceManager	= _null;

//----------------------------------------------------------------------------
// Global Functions Implementation
//----------------------------------------------------------------------------

extern "C" _dword OnQueryGUIStateEnumValue( WStringPtr name, const QwordParameters2& parameters )
{
	return GUIComponentUtils::OnQueryGUIStateEnumValue( name, parameters );
}

extern "C" const _charw* OnQueryGUIStateEnumName( _dword value, const QwordParameters2& parameters )
{
	return GUIComponentUtils::OnQueryGUIStateEnumName( value, parameters );
}

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetGUIModule
EGE_INTERNAL IGUIModule* GetGUIModule( )
{
	return gGUIModule;
}

#undef GetGUIResourceManager
EGE_INTERNAL IGUIResourceManager* GetGUIResourceManager( )
{
	return gGUIResourceManager;
}

#undef SetGUIResourceManager
EGE_INTERNAL _void SetGUIResourceManager( IGUIResourceManager* manager )
{
	gGUIResourceManager = manager;
}

#undef SetGUIModule
EGE_INTERNAL _void SetGUIModule( IGUIModule* module )
{
	gGUIModule = module;
}

#undef CreateGUIModule
EGE_INTERNAL _boolean CreateGUIModule( _ubool enable_stretch, const Vector2& size )
{
	// Create module
	typedef PassRefPtr< GUIModule > GUIModulePassRef;
	GUIModulePassRef module = new GUIModule( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_GUI_MODULE_PRIORITY );

	// Update the global module
	gGUIModule = module.GetPtr( );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( enable_stretch, size ) );
	return ret;
}