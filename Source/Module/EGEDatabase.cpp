//! @file     EGEDatabase.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEDatabase.h"

IDatabaseModule* gDatabaseModule = &sNullDatabaseModule;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetDatabaseModule
EGE_INTERNAL IDatabaseModule* GetDatabaseModule( )
{
	return gDatabaseModule;
}

#undef CreateDatabaseModule
EGE_INTERNAL _boolean CreateDatabaseModule( )
{
#ifdef _PLATFORM_IOS_
	return _false;
#else
	// Create module
	typedef PassRefPtr< DatabaseModule > DatabaseModulePassRef;
	DatabaseModulePassRef module = new DatabaseModule( );

	// Update the global module
	gDatabaseModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_DATABASE_MODULE_PRIORITY );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( ) );
	return ret;
#endif
}