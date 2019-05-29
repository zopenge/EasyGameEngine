//! @file     PEResArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PEResArchive Implementation
//----------------------------------------------------------------------------

PEResArchive::PEResArchive( )
{
	mModule = _null;
}

PEResArchive::~PEResArchive( )
{
}

_ubool PEResArchive::OnEnumFileCallback( const _charw* type, const _charw* name, _void* parameter )
{
	PEResFileInfo* info = (PEResFileInfo*) parameter;
	EGE_ASSERT( info != _null );

	// Get the PE-Res archive
	PEResArchive* archive = info->mArchive;
	EGE_ASSERT( archive != _null );

	// Get resource name from string table
	WStringPtr res_name = GetStringTable( )->GetResourceNameByID( archive->mModuleName, (_dword)name );
	if ( res_name.IsEmpty( ) )
		return _false;

	// Build file info
	FileInfo file_info;
	file_info.mFileName	= res_name + L"." + type;

	// Notify outside
	return (*info->mWalkItemFunc)( file_info, info->mParameters );
}

_handle PEResArchive::GetResourceInfo( WStringPtr name, _dword* size ) const
{
	// Get the file name only as resource name
	WString res_name = Path::GetFileName( name, _false );

	// Get resource ID from string table
	_dword res_id = GetStringTable( )->GetResourceIDByName( mModuleName, res_name );
	if ( res_id == 0 )
		return _null;

	// Get the extension name as type
	WString type = Path::GetExtension( name );

	// Find resource by name and type
	_handle resinfo = Platform::FindResource( mModule, MAKEINTRESOURCEW( res_id ), type.Str( ) );
	if ( resinfo == _null )
		return _null;

	// Get the size of the resource if needed
	if ( size != _null )
		*size = Platform::SizeOfResource( mModule, resinfo );

	return resinfo;
}

_ubool PEResArchive::Initialize( WStringPtr module_name )
{
	mModuleName = module_name;

	// Get module handle
	mModule = Platform::GetModuleHandleW( module_name.Str( ) );
	if ( mModule == _null )
		return _false;

	return _true;
}

WStringPtr PEResArchive::GetPath( ) const
{
	return mModuleName;
}

_ubool PEResArchive::HasResourceByPath( WStringPtr file_name ) const
{
	// Get resource info handle and size
	_handle resinfo = GetResourceInfo( file_name, _null );
	if ( resinfo == _null )
		return _false;

	return _true;
}

IStreamReaderPassRef PEResArchive::LoadResourceByPath( WStringPtr file_name )
{
	// Try to load from patch archives
	IStreamReaderPassRef stream_reader = BaseClass::LoadResourceByPath( file_name );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// The resource size
	_dword size = 0;

	// Get resource info handle and size
	_handle resinfo = GetResourceInfo( file_name, &size );
	if ( resinfo == _null )
	{
		WLOG_ERROR_1( L"Load '%s' resource from PE-Res archive failed, due to get resource size failed", file_name.Str( ) );
		return _null;
	}

	// Load the resource into memory
	_handle resource = Platform::LoadResource( mModule, resinfo );
	if ( resource == _null )
	{
		WLOG_ERROR_1( L"Load '%s' resource from PE-Res archive failed, due to load resource info failed", file_name.Str( ) );
		return _null;
	}

	// Create stream reader
	PEResStreamReader* pe_res_stream_reader = new PEResStreamReader( );
	if ( pe_res_stream_reader->Initialize( resource, size ) == _false )
	{ 
		WLOG_ERROR_1( L"Load '%s' resource from PE-Res archive failed, due to create PE-Res stream reader failed", file_name.Str( ) );

		EGE_RELEASE( pe_res_stream_reader ); 
		return _null; 
	}

	return pe_res_stream_reader;
}

_ubool PEResArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParams2& params ) const
{
	// We do not support path
	if ( path.IsEmpty( ) == _false )
		return _false;

	// We do not support filter
	if ( filter.IsEmpty( ) == _false )
		return _false;

	// We do not support depth
	if ( depth != -1 )
		return _false;

	PEResFileInfo info;
	info.mWalkItemFunc	= walk_item_func;
	info.mParameters	= params;

	if ( Platform::EnumResourceNames( mModule, L"", OnEnumFileCallback, &info ) == _false )
	{
		WLOG_ERROR_1( L"Enum resources in '%s' PERes archive failed", mModuleName.Str( ) );
		return _false;
	}

	return _true;
}
