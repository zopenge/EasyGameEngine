//! @file     EGEPhysx.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPhysx.h"

IDynamicPHI*			gDynamicPHI				= _null;
IPhysxResourceManager*	gPhysxResourceManager	= _null;
IPhysxModule*			gPhysxModule			= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetPhysxModule
extern "C" IPhysxModule* GetPhysxModule( )
{
	return gPhysxModule;
}

#undef GetPhysxResourceManager
EGE_INTERNAL IPhysxResourceManager* GetPhysxResourceManager( )
{
	return gPhysxResourceManager;
}

#undef GetDynamicPHI
EGE_INTERNAL IDynamicPHI* GetDynamicPHI( )
{
	return gDynamicPHI;
}

#undef CreatePhysxModule
EGE_INTERNAL _boolean CreatePhysxModule( )
{
	// Create module
	typedef PassRefPtr< PhysxModule > PhysxModulePassRef;
	PhysxModulePassRef module = new PhysxModule( );

	// Update the global module
	gPhysxModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_PHYSX_MODULE_PRIORITY );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( ) );
	return ret;
}