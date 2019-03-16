//! @file     StoragePackageArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePackageArchive Implementation
//----------------------------------------------------------------------------

StoragePackageArchive::StoragePackageArchive( WStringPtr path, IManifestFile* manifest_file ) : BaseClass( _ARCHIVE_PACKAGE, path, manifest_file )
{
	mPackageFile = new StoragePackageFile( );
}

StoragePackageArchive::~StoragePackageArchive( )
{
	EGE_RELEASE( mPackageFile );
}

_ubool StoragePackageArchive::OnQueryResource( WStringPtr filename ) const
{
	return mPackageFile->SearchItem( filename ) != _null;
}

IStreamReaderPassRef StoragePackageArchive::OnLoadResource( WStringPtr filename )
{
	// Search for the item from package file
	const PackageItem* item = mPackageFile->SearchItem( filename );
	if ( item == _null )
		return _null;

	// Create package stream reader
	return new StoragePackageStreamReader( item, mPackageFile );
}

IStreamWriterPassRef StoragePackageArchive::OnCreateResource( WStringPtr filename, _dword size )
{
	// Add the item into package file
	const PackageItem* item = mPackageFile->AddItem( filename, size, _null );
	if ( item == _null )
	{
		WLOG_ERROR_2( L"'%s' resource is duplicate in '%s' package archive", filename.Str( ), GetPath( ).Str( ) );
		return _null;
	}

	// Create package stream writer
	return new StoragePackageStreamWriter( item, mPackageFile );
}

_ubool StoragePackageArchive::Initialize( WStringPtr module_name )
{
	// Load package file when it's existing
	if ( FileSystem::IsFileExist( mPath ) )
	{
		if ( mPackageFile->Load( mPath ) == _false )
		{
			OutputLog( _LOG_ERROR, L"Load package archive failed" );
			return _false;
		}
	}
	// If the package file is not existing then create a new one
	else
	{
		if ( mPackageFile->Create( mPath ) == _false )
		{
			OutputLog( _LOG_ERROR, L"Create package archive failed" );
			return _false;
		}
	}

	return _true;
}

_ubool StoragePackageArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const VoidParameters2& parameters )
{
	if ( walk_item_func == _null )
		return _false;

	return _true;
}