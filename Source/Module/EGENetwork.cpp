//! @file     EGENetwork.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGENetwork.h"

// The global variables
INetworkResourceManager*	gNetworkResourceManager	= _null;
INetworkModule*				gNetworkModule			= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetNetworkResourceManager
EGE_INTERNAL INetworkResourceManager* GetNetworkResourceManager( )
{
	return gNetworkResourceManager;
}

#undef GetNetworkModule
EGE_INTERNAL INetworkModule* GetNetworkModule( )
{
	return gNetworkModule;
}

#undef CreateNetworkModule
EGE_INTERNAL _boolean CreateNetworkModule( )
{
	// Create module
	typedef PassRefPtr< NetworkModule > NetworkModulePassRef;
	NetworkModulePassRef module = new NetworkModule( );

	// Update the global module
	gNetworkModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_NETWORK_MODULE_PRIORITY );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( ) );
	return ret;
}