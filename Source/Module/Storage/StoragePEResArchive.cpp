//! @file     StoragePEResArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePEResArchive Implementation
//----------------------------------------------------------------------------

StoragePEResArchive::StoragePEResArchive( WStringPtr path ) : BaseClass( _ARCHIVE_PERES, path )
{
	mModule = _null;
}

StoragePEResArchive::~StoragePEResArchive( )
{
}

_handle StoragePEResArchive::GetResourceInfo( WStringPtr name, _dword* size ) const
{
	// Find resource by name and type
	_handle resinfo = Platform::FindResource( mModule, name.Str( ), mPath.Str( ) );
	if ( resinfo == _null )
		return _null;

	// Get the size of the resource if needed
	if ( size != _null )
		*size = Platform::SizeOfResource( mModule, resinfo );

	return resinfo;
}

IStreamReaderPassRef StoragePEResArchive::OnLoadResource( WStringPtr filename )
{
	// The resource size
	_dword size = 0;

	// Get resource info handle and size
	_handle resinfo = GetResourceInfo( filename, &size );
	if ( resinfo == _null )
		return _null;

	// Load the resource into memory
	_handle resource = Platform::LoadResource( mModule, resinfo );
	if ( resource == _null )
		return _null;

	// Create stream reader
	StoragePEResStreamReader* stream_reader = new StoragePEResStreamReader( );
	if ( stream_reader->Initialize( resource, size ) == _false )
		{ EGE_RELEASE( stream_reader ); return _null; }

	return stream_reader;
}

IStreamWriterPassRef StoragePEResArchive::OnCreateResource( WStringPtr filename, _dword size )
{
	return _null;
}

_ubool StoragePEResArchive::Initialize( WStringPtr password, WStringPtr module_name )
{
#ifdef _PLATFORM_WINDOWS_
	// Load library
	mModule = Platform::GetModuleHandleW( module_name.Str( ) );
	if ( mModule == _null )
		return _false;
#endif
	
	return _true;
}

_ubool StoragePEResArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParameters2& parameters )
{
	if ( walk_item_func == _null )
		return _false;

	return _true;
}