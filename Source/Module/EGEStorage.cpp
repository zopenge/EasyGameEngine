//! @file     EGEStorage.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEStorage.h"

IStorageModule* gStorageModule	= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef HasResourceInPEArchive
EGE_INTERNAL _boolean HasResourceInPEArchive( WStringPtr filename )
{
	// Create and initialize PE-archive
	IArchiveRef archive = GetInterfaceFactory( )->CreatePEResArchive( L"" );
	if ( archive.IsNull( ) )
		return _false;

	return EGE_BOOLEAN( archive->HasResourceByPath( filename ) );
}

#undef GetStorageWorkingArchive
EGE_INTERNAL IArchive* GetStorageWorkingArchive( )
{
	return gStorageModule->GetWorkingArchive( );
}

#undef GetStorageModule
EGE_INTERNAL IStorageModule* GetStorageModule( )
{
	return gStorageModule;
}

#undef CreateStorageModule
EGE_INTERNAL _boolean CreateStorageModule( WStringPtr working_dir )
{
	// Create module
	typedef PassRefPtr< StorageModule > StorageModulePassRef;
	StorageModulePassRef module = new StorageModule( );

	// Update the global module
	gStorageModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_STORAGE_MODULE_PRIORITY );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( working_dir ) );
	return ret;
}