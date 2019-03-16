//! @file     StorageCompoundArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageCompoundArchive Implementation
//----------------------------------------------------------------------------

StorageCompoundArchive::StorageCompoundArchive( WStringPtr path ) : BaseClass( _ARCHIVE_COMPOUND, path )
{
}

StorageCompoundArchive::~StorageCompoundArchive( )
{
}

IStreamReaderPassRef StorageCompoundArchive::OnLoadResource( WStringPtr filename )
{
	IStreamReaderPassRef stream_reader;

	// 1. Load PE-Resource from application
	stream_reader = mPEResArchive->LoadResource( filename );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// 2. Load resource from document archive 
	stream_reader = GetStorageDocumentArchive( )->LoadResource( filename );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// 3. Load resource by absolute path
	stream_reader = mFileArchive->LoadResource( filename );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// Find nothing at all
	return _null;
}

IStreamWriterPassRef StorageCompoundArchive::OnCreateResource( WStringPtr filename, _dword size )
{
	return _null;
}

_ubool StorageCompoundArchive::Initialize( WStringPtr password, WStringPtr module_name )
{
	// Create file archive
	mFileArchive = GetStorageModule( )->CreateArchive( _ARCHIVE_FILE, mPath, L"", L"" );
	if ( mFileArchive.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' file archive in compound archive failed", mPath.Str( ) );
		return _false;
	}

	// Create PE-Res archive
	mPEResArchive = GetStorageModule( )->CreateArchive( _ARCHIVE_PERES, mPath, L"", module_name );
	if ( mPEResArchive.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' PERes archive in compound archive failed", mPath.Str( ) );
		return _false;
	}

	return _true;
}

_ubool StorageCompoundArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParameters2& parameters )
{
	return _false;
}