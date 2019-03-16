//! @file     TArchive.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TArchive
//----------------------------------------------------------------------------

template< typename Type >
class TArchive : public Type
{
protected:
	//!	The enum-resource file info.
	struct EnumResFileInfo
	{
		WString	mResName;
		WString	mAbsoluteFileName;
	};

	//!	The patch archive info
	struct PatchArchiveInfo
	{
		_dword		mID;
		_dword		mManifestFileID;
		IArchiveRef	mArchive;

		//!	Use version as key.
		operator Version( ) const
			{ return mArchive->GetVersion( ); }
		
		PatchArchiveInfo( )
		{
			mID				= 0;
			mManifestFileID	= -1;
		}
	};
	//!	Use the version as key from high to low
	typedef Array< PatchArchiveInfo > ArchiveArray;

protected:
	//!	The thread lock
	Lock					mLock;

	//!	The patch archives
	ArchiveArray			mPatchArchives;

	//!	The manifest file manager
	IManifestFileManagerRef	mManifestFileManager;

protected:
	//!	When enumerate resource file.
	static _ubool OnEnumResFileCallback( const FileInfo& item_info, const QwordParameters2& parameters );

protected:
	//!	Check whether have patch archive or not.
	const PatchArchiveInfo* GetPatchArchive( IArchive* archive ) const;

protected:
	TArchive( );
	virtual ~TArchive( );

// IArchive Interface
public:
	virtual const MD5Code&				GetMD5Code( ) const override;
	virtual const Version&				GetVersion( ) const override;

	virtual const IManifestFile*		GetManifestFile( ) const override;

	virtual WStringR					GetResourceAbsolutePath( WStringPtr res_name ) const override;
	virtual WStringR					GetResourceRelativePath( WStringPtr res_name ) const override;
	virtual const MD5Code&				GetResourceMD5Code( WStringPtr res_name ) const override;

	virtual _ubool						HasResourceByName( WStringPtr res_name ) const override;
	virtual IStreamReaderPassRef		LoadResourceByName( WStringPtr res_name ) override;
	virtual IMarkupLangFilePassRef		LoadMarkupLangFileByName( WStringPtr res_name ) override;
	virtual ISerializableNodePassRef	LoadSerializableNodeByName( WStringPtr res_name, _ubool locate_at_first_child ) override;
	virtual IImageFilePassRef			LoadImageFileByName( WStringPtr res_name, _dword flags = 0 ) override;

	virtual _ubool						HasResourceByPath( WStringPtr file_name ) const PURE;
	virtual IStreamReaderPassRef		LoadResourceByPath( WStringPtr file_name ) override;
	virtual IMarkupLangFilePassRef		LoadMarkupLangFileByPath( WStringPtr file_name ) override;
	virtual ISerializableNodePassRef	LoadSerializableNodeByPath( WStringPtr file_name, _ubool locate_at_first_child ) override;
	virtual IImageFilePassRef			LoadImageFileByPath( WStringPtr file_name, _dword flags = 0 ) override;

	virtual _dword						AddPatchArchive( WStringPtr res_name, WStringPtr password ) override;
	virtual _dword						AddPatchArchive( WStringPtr res_name, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) override;
	virtual _dword						AddPatchArchive( IArchive* archive ) override;
	virtual _void						RemovePatchArchive( _dword id ) override;
	virtual _void						RemovePatchArchive( IArchive* archive ) override;
	virtual _void						RemovePatchArchive( WStringPtr path ) override;
	virtual IArchive*					GetPatchArchive( _dword id ) override;

	virtual _void						ClearCaches( ) override;

	virtual _ubool						EnumResources( IArchive::OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) const override;
};

//----------------------------------------------------------------------------
// TArchive Implementation
//----------------------------------------------------------------------------

template< typename Type >
TArchive< Type >::TArchive( )
{
}

template< typename Type >
TArchive< Type >::~TArchive( )
{
}

template< typename Type >
_ubool TArchive< Type >::OnEnumResFileCallback( const FileInfo& item_info, const QwordParameters2& parameters )
{
	EnumResFileInfo* info = (EnumResFileInfo*)parameters[0];
	EGE_ASSERT( info != _null );

	// Check whether find it
	if ( info->mResName == item_info.mFileName )
	{
		// Found it, break the enumerating procession
		info->mAbsoluteFileName = item_info.mAbsolutePath;
		return _false;
	}

	return _true;
}

template< typename Type >
const typename TArchive< Type >::PatchArchiveInfo* TArchive< Type >::GetPatchArchive( IArchive* archive ) const
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		const PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mArchive == archive )
			return &patch_archive_info;
	}

	return _null;
}

template< typename Type >
const MD5Code& TArchive< Type >::GetMD5Code( ) const
{
	return MD5Code::cNull;
}

template< typename Type >
const Version& TArchive< Type >::GetVersion( ) const
{
	if ( mManifestFileManager.IsNull( ) )
		return Version::cZero;

	return mManifestFileManager->GetManifestVersion( );
}

template< typename Type >
const IManifestFile* TArchive< Type >::GetManifestFile( ) const
{
	return _null;
}

template< typename Type >
WStringR TArchive< Type >::GetResourceAbsolutePath( WStringPtr res_name ) const
{
	EnumResFileInfo info;
	info.mResName = res_name;

	EnumResources( OnEnumResFileCallback, L"", L"", _FILE_FINDER_FILE_MASK, -1, QwordParameters2( (_qword)&info, (_qword)this ) );

	return info.mAbsoluteFileName;
}

template< typename Type >
WStringR TArchive< Type >::GetResourceRelativePath( WStringPtr res_name ) const
{
	if ( mManifestFileManager.IsValid( ) )
		return mManifestFileManager->GetRelativePath( res_name );

	return WString( L"" );
}

template< typename Type >
const MD5Code& TArchive< Type >::GetResourceMD5Code( WStringPtr res_name ) const
{
	if ( mManifestFileManager.IsValid( ) )
		return mManifestFileManager->GetMD5Code( res_name );

	return MD5Code::cNull;
}

template< typename Type >
_ubool TArchive< Type >::HasResourceByName( WStringPtr res_name ) const
{
	if ( mManifestFileManager.IsValid( ) && mManifestFileManager->HasResource( res_name ) )
		return _true;

	return _false;
}

template< typename Type >
IStreamReaderPassRef TArchive< Type >::LoadResourceByName( WStringPtr res_name )
{
	// Check the resource file name
	if ( res_name.IsEmpty( ) )
		return _null;

	// Try to load by manifest files
	if ( mManifestFileManager.IsValid( ) )
	{
		// The resource version
		Version res_ver = Version::cZero;

		// Get the relative path of resource
		WString res_filename = mManifestFileManager->GetRelativePath( res_name, res_ver );
		if ( res_filename.IsEmpty( ) == _false )
		{
			LockOwner lock_owner( mLock );

			// Try to load from patch archive
			typename ArchiveArray::Iterator it = mPatchArchives.template SearchDescending< Version >( res_ver );
			if ( it.IsValid( ) )
			{
				IArchive* patch_archive = it.GetObject( ).mArchive;
				EGE_ASSERT( patch_archive != _null );

				IStreamReaderPassRef stream_reader = patch_archive->LoadResourceByPath( res_filename );
				if ( stream_reader.IsValid( ) )
					return stream_reader;
			}
		}
	}

	// Load by the resource name
	return LoadResourceByPath( res_name );
}

template< typename Type >
IMarkupLangFilePassRef TArchive< Type >::LoadMarkupLangFileByName( WStringPtr res_name )
{
	IStreamReaderRef stream_reader = LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
		return _null;

	// Parse the markup file
	IMarkupLangFilePassRef markup_file = GetInterfaceFactory( )->ParseMarkupLangFile( stream_reader );
	if ( markup_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Parse markup file by '%s' resource name failed", res_name.Str( ) );
		return _null;
	}

	return markup_file;
}

template< typename Type >
ISerializableNodePassRef TArchive< Type >::LoadSerializableNodeByName( WStringPtr res_name, _ubool locate_at_first_child )
{
	IMarkupLangFileRef markup_file = LoadMarkupLangFileByName( res_name );
	if ( markup_file.IsNull( ) )
		return _null;

	ISerializableNodePassRef root_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( markup_file );
	if ( root_node.IsNull( ) )
		return _null;

	if ( locate_at_first_child )
		return root_node->GetFirstChildNode( );
	else
		return root_node;
}

template< typename Type >
IImageFilePassRef TArchive< Type >::LoadImageFileByName( WStringPtr res_name, _dword flags )
{
	IStreamReaderRef stream_reader = LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
		return _null;

	// Parse the image file
	IImageFilePassRef image_file = GetInterfaceFactory( )->ParseImageFile( stream_reader, _FF_UNKNOWN, flags );
	if ( image_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Parse image file by '%s' resource name failed", res_name.Str( ) );
		return _null;
	}

	return image_file;
}

template< typename Type >
_ubool TArchive< Type >::HasResourceByPath( WStringPtr file_name ) const
{
	return _false;
}

template< typename Type >
IStreamReaderPassRef TArchive< Type >::LoadResourceByPath( WStringPtr file_name )
{
	// We copy here to make thread safe
	mLock.Enter( );
	ArchiveArray patch_archives = mPatchArchives;
	mLock.Leave( );

	// Load resource from high version to low version
	for ( _dword i = 0; i < patch_archives.Number( ); i ++ )
	{
		IStreamReaderPassRef stream_reader = patch_archives[i].mArchive->LoadResourceByPath( file_name );
		if ( stream_reader.IsValid( ) )
			return stream_reader;
	}

	return _null;
}

template< typename Type >
IMarkupLangFilePassRef TArchive< Type >::LoadMarkupLangFileByPath( WStringPtr file_name )
{
	IStreamReaderRef stream_reader = LoadResourceByPath( file_name );
	if ( stream_reader.IsNull( ) )
		return _null;

	// Parse the markup file
	IMarkupLangFilePassRef markup_file = GetInterfaceFactory( )->ParseMarkupLangFile( stream_reader );
	if ( markup_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Parse '%s' markup file failed", file_name.Str( ) );
		return _null;
	}

	return markup_file;
}

template< typename Type >
ISerializableNodePassRef TArchive< Type >::LoadSerializableNodeByPath( WStringPtr file_name, _ubool locate_at_first_child )
{
	IStreamReaderRef stream_reader = LoadResourceByPath( file_name );
	if ( stream_reader.IsNull( ) )
		return _null;

	// Parse the markup language file
	IMarkupLangFileRef markup_file = GetInterfaceFactory( )->ParseMarkupLangFile( stream_reader );
	if ( markup_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Parse '%s' markup language file failed", file_name.Str( ) );
		return _null;
	}

	ISerializableNodePassRef root_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( markup_file );
	if ( root_node.IsNull( ) )
		return _null;

	if ( locate_at_first_child )
		return root_node->GetFirstChildNode( );
	else
		return root_node;
}

template< typename Type >
IImageFilePassRef TArchive< Type >::LoadImageFileByPath( WStringPtr file_name, _dword flags )
{
	IStreamReaderRef stream_reader = LoadResourceByPath( file_name );
	if ( stream_reader.IsNull( ) )
		return _null;

	// Parse the image file
	IImageFilePassRef image_file = GetInterfaceFactory( )->ParseImageFile( stream_reader );
	if ( image_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Parse '%s' image file failed", file_name.Str( ) );
		return _null;
	}

	return image_file;
}

template< typename Type >
_dword TArchive< Type >::AddPatchArchive( WStringPtr res_name, WStringPtr password )
{
	return AddPatchArchive( res_name, password, _ENCRYPTION_UNKNOWN, L"" );
}

template< typename Type >
_dword TArchive< Type >::AddPatchArchive( WStringPtr res_name, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	WLOG_TRACE_1( L"Loading '%s' patch archive ...", res_name.Str( ) );

	// Open archive
	IStreamReaderRef stream_reader = LoadResourceByPath( res_name );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load '%s' patch archive failed, due to resource is not existing", res_name.Str( ) );
		return -1;
	}

	// Get the archive name
	WString archive_name = Path::GetFileName( res_name );

	// Load patch archive
	IArchiveRef patch_archive = GetInterfaceFactory( )->CreateMemArchive( archive_name, stream_reader, password, manifest_encryption_type, manifest_encryption_key );
	if ( patch_archive.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load '%s' patch archive failed, due to invalid resource", res_name.Str( ) );
		return -1;
	}

	// Add patch archive
	_dword archive_id = AddPatchArchive( patch_archive );
	if ( archive_id == -1 )
	{
		WLOG_ERROR_1( L"Load '%s' patch archive failed, due to failed to add into working archived", res_name.Str( ) );
		return -1;
	}

	WLOG_TRACE_2( L"Load '%s' patch archive (%d) OK", res_name.Str( ), archive_id );

	return archive_id;
}

template< typename Type >
_dword TArchive< Type >::AddPatchArchive( IArchive* archive )
{
	if ( archive == _null )
		return -1;

	// Skip for duplicated archive
	const PatchArchiveInfo* exist_patch_info = GetPatchArchive( archive );
	if ( exist_patch_info != _null )
		return exist_patch_info->mID;

	// The patch archive ID counter
	static _dword sArchiveIDCounter = 1;

	// Get the archive version
	const Version& version = archive->GetVersion( );

	// Try to combine manifest
	if ( version != Version::cZero )
	{
		// Build patch archive info
		PatchArchiveInfo patch_archive_info;
		patch_archive_info.mID		= sArchiveIDCounter ++;
		patch_archive_info.mArchive	= archive;

		// Add patch archive from high to low version
		mLock.Enter( );
		_dword index = mPatchArchives.template InsertDescending< Version >( patch_archive_info );
		mLock.Leave( );

		if ( mManifestFileManager.IsNull( ) )
			mManifestFileManager = GetInterfaceFactory( )->CreateManifestFileManager( );

		mPatchArchives[index].mManifestFileID = mManifestFileManager->LoadManifestFile( archive->GetManifestFile( ) );
		if ( mPatchArchives[index].mManifestFileID == -1 )
			return _false;

		return patch_archive_info.mID;
	}
	else
	{
		// Build patch archive info
		PatchArchiveInfo patch_archive_info;
		patch_archive_info.mID		= sArchiveIDCounter ++;
		patch_archive_info.mArchive	= archive;

		// We insert it as the last patch archive without any version
		mLock.Enter( );
		mPatchArchives.Append( patch_archive_info );
		mLock.Leave( );

		return patch_archive_info.mID;
	}
}

template< typename Type >
_void TArchive< Type >::RemovePatchArchive( _dword id )
{
	if ( id == -1 )
		return;

	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mID != id )
			continue;

		// Remove manifest file
		if ( patch_archive_info.mManifestFileID != -1 && mManifestFileManager.IsValid( ) )
			mManifestFileManager->UnloadManifestFile( patch_archive_info.mManifestFileID );

		mPatchArchives.RemoveByIndex( i );
		return;
	}
}

template< typename Type >
_void TArchive< Type >::RemovePatchArchive( IArchive* archive )
{
	if ( archive == _null )
		return;

	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mArchive != archive )
			continue;

		// Remove manifest file
		if ( patch_archive_info.mManifestFileID != -1 && mManifestFileManager.IsValid( ) )
			mManifestFileManager->UnloadManifestFile( patch_archive_info.mManifestFileID );

		mPatchArchives.RemoveByIndex( i );
		return;
	}
}

template< typename Type >
_void TArchive< Type >::RemovePatchArchive( WStringPtr path )
{
	if ( path.IsEmpty( ) )
		return;

	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mArchive->GetPath( ) != path )
			continue;

		// Remove manifest file
		if ( patch_archive_info.mManifestFileID != -1 && mManifestFileManager.IsValid( ) )
			mManifestFileManager->UnloadManifestFile( patch_archive_info.mManifestFileID );

		mPatchArchives.RemoveByIndex( i );
		return;
	}
}

template< typename Type >
IArchive* TArchive< Type >::GetPatchArchive( _dword id )
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mPatchArchives.Number( ); i ++ )
	{
		PatchArchiveInfo& patch_archive_info = mPatchArchives[i];

		if ( patch_archive_info.mID == id )
			return patch_archive_info.mArchive;
	}

	return _null;
}

template< typename Type >
_void TArchive< Type >::ClearCaches( )
{

}

template< typename Type >
_ubool TArchive< Type >::EnumResources( IArchive::OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParameters2& parameters ) const
{
	return _true;
}

}
