//! @file     TStorageArchive.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStorageArchive
//----------------------------------------------------------------------------

template< typename Type >
class TStorageArchive : public INTERFACE_ARCHIVE_IMPL( Type )
{
protected:
	typedef INTERFACE_ARCHIVE_IMPL( Type ) BaseClass;

protected:
	//!	The patch archive info
	struct PatchArchiveInfo
	{
		_dword		mManifestFileID;
		Version		mManifestFileVersion;
		MD5Code		mMD5Code;
		IArchiveRef	mArchive;

		PatchArchiveInfo( )
		{
			mManifestFileID			= 0;
			mManifestFileVersion	= Version::cZero;
			mMD5Code				= MD5Code::cNull;
		}
	};
	typedef Array< PatchArchiveInfo > ArchiveArray;

protected:
	//!	The patch archives
	ArchiveArray	mPatchArchives;

protected:
	//!	Output log.
	_void OutputLog( _LOG log_type, WStringPtr string );

	//!	Get the patch archive by manifest file ID.
	PatchArchiveInfo* GetPatchArchiveByManifestFileID( _dword id );

protected:
	//!	When load resource.
	virtual IStreamReaderPassRef OnLoadResource( WStringPtr filename ) PURE;
	//!	When create resource.
	virtual IStreamWriterPassRef OnCreateResource( WStringPtr filename, _dword size ) PURE;

protected:
	TStorageArchive( _ARCHIVE type, WStringPtr path );
	virtual ~TStorageArchive( );

// IArchive Interface
public:
	virtual IStreamReaderPassRef	LoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	CreateResource( WStringPtr filename, _dword size ) override;

	virtual _void					ClearCaches( ) override;

// IStorageArchive Interface
public:
	virtual IManifestFilePassRef	LoadManifestFile( _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) override;

	virtual _dword					AddPatchArchive( IStorageArchive* archive, const MD5Code& md5_code, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) override;
	virtual _void					RemovePatchArchive( _dword id ) override;
	virtual Version					GetPatchArchiveManifestVersion( _dword id ) const override;
	virtual MD5Code					GetPatchArchiveMD5Code( _dword id ) const override;
};

//----------------------------------------------------------------------------
// TStorageArchive Implementation
//----------------------------------------------------------------------------

template< typename Type >
TStorageArchive< Type >::TStorageArchive( _ARCHIVE type, WStringPtr path ) 
	: BaseClass( type, path )
{
}

template< typename Type >
TStorageArchive< Type >::~TStorageArchive( )
{
	// Unload patch archives manifest
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		_dword manifest_file_id = mPatchArchives[i].mManifestFileID;
		if ( manifest_file_id != 0 )
			continue;

		StorageEventUnloadManifestFile unload_manifest_file_event;
		unload_manifest_file_event.mID = manifest_file_id;
		GetModuleManager( )->ProcessEvent( unload_manifest_file_event );
	}
}

template< typename Type >
_void TStorageArchive< Type >::OutputLog( _LOG log_type, WStringPtr string )
{
	_charw log_string[1024];
	Platform::FormatStringBuffer( log_string, 1024, L"%s[type:%s, path:%s]",  
		string.Str( ), this->GetTypeName( ).Str( ), this->mPath.Str( ) );

	switch ( log_type )
	{
		case _LOG_DEBUG:	WLOG_DEBUG( log_string ); break;
		case _LOG_TRACE:	WLOG_TRACE( log_string ); break;
		case _LOG_ERROR:	WLOG_ERROR( log_string ); break;
		case _LOG_WARNING:	WLOG_WARNING( log_string ); break;
		default:
			break;
	}
}

template< typename Type >
typename TStorageArchive< Type >::PatchArchiveInfo* TStorageArchive< Type >::GetPatchArchiveByManifestFileID( _dword id )
{
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch = mPatchArchives[i];

		if ( patch.mManifestFileID == id )
			return &patch;
	}

	return _null;
}

template< typename Type >
IStreamReaderPassRef TStorageArchive< Type >::LoadResource( WStringPtr filename )
{
	// Check the resource file name
	if ( filename.IsEmpty( ) )
		return _null;

	// Load resource from patch archives
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		IArchive* patch_archive = mPatchArchives[i].mArchive;
		EGE_ASSERT( patch_archive != _null );

		IStreamReaderPassRef stream_reader = patch_archive->LoadResource( filename );
		if ( stream_reader.IsValid( ) )
			return stream_reader;
	}

	// Load resource
	IStreamReaderPassRef stream_reader = OnLoadResource( filename );
	if ( stream_reader.IsNull( ) )
		return _null;

	return stream_reader;
}

template< typename Type >
IStreamWriterPassRef TStorageArchive< Type >::CreateResource( WStringPtr filename, _dword size )
{
	// Check the resource file name
	if ( filename.IsEmpty( ) )
		return _null;

	// Create resource
	IStreamWriterPassRef stream_writer = OnCreateResource( filename, size );
	if ( stream_writer.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' resource failed", filename.Str( ) );
		return _null;
	}

	return stream_writer;
}

template< typename Type >
_void TStorageArchive< Type >::ClearCaches( )
{
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		IArchive* patch_archive = mPatchArchives[i].mArchive;
		EGE_ASSERT( patch_archive != _null );

		patch_archive->ClearCaches( );
	}
}

template< typename Type >
IManifestFilePassRef TStorageArchive< Type >::LoadManifestFile( _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	return _null;
}

template< typename Type >
_dword TStorageArchive< Type >::AddPatchArchive( IStorageArchive* archive, const MD5Code& md5_code, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	if ( archive == _null )
		return -1;

	// Load manifest file from patch archive
	IManifestFileRef manifest_file = archive->LoadManifestFile( manifest_encryption_type, manifest_encryption_key );
	if ( manifest_file.IsNull( ) )
		return -1;

	// Notify parse manifest done
	StorageEventLoadManifestFile load_manifest_file_event;
	load_manifest_file_event.mID			= 0;
	load_manifest_file_event.mManifestFile	= manifest_file;
	GetModuleManager( )->ProcessEvent( load_manifest_file_event );

	// Make sure we have the unique manifest file ID
	if ( load_manifest_file_event.mID == 0 )
	{
		WLOG_ERROR( L"The manifest file unique ID is invalid" );
		return -1;
	}
	// Check duplicated archive by manifest file ID
	else if ( GetPatchArchiveByManifestFileID( load_manifest_file_event.mID ) )
	{
		WLOG_ERROR_1( L"The manifest file (%d) unique ID has existing", load_manifest_file_event.mID );
		return -1;
	}

	// Add patch archive
	PatchArchiveInfo patch_archive_info;
	patch_archive_info.mManifestFileID		= load_manifest_file_event.mID;
	patch_archive_info.mManifestFileVersion	= manifest_file->GetVersion( );
	patch_archive_info.mMD5Code				= md5_code;
	patch_archive_info.mArchive				= archive;
	mPatchArchives.Append( patch_archive_info );

	return patch_archive_info.mManifestFileID;
}

template< typename Type >
_void TStorageArchive< Type >::RemovePatchArchive( _dword id )
{
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mManifestFileID != id )
			continue;

		StorageEventUnloadManifestFile unload_manifest_file_event;
		unload_manifest_file_event.mID = id;
		GetModuleManager( )->ProcessEvent( unload_manifest_file_event );

		mPatchArchives.RemoveByIndex( i );
		return;
	}
}

template< typename Type >
Version TStorageArchive< Type >::GetPatchArchiveManifestVersion( _dword id ) const
{
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		const PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mManifestFileID == id )
			return patch_archive_info.mManifestFileVersion;
	}

	return Version::cZero;
}

template< typename Type >
MD5Code TStorageArchive< Type >::GetPatchArchiveMD5Code( _dword id ) const
{
	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		const PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mManifestFileID == id )
			return patch_archive_info.mMD5Code;
	}

	return MD5Code::cNull;
}

}