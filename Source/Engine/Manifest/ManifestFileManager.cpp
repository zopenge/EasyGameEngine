//! @file     ManifestFileManager.cpp
//! @author   foreven
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ManifestFileManager Implementation
//----------------------------------------------------------------------------

ManifestFileManager::ManifestFileManager( )
{
}

ManifestFileManager::~ManifestFileManager( )
{
}

const ManifestFileManager::ItemInfo* ManifestFileManager::GetItemInfo( WStringPtr res_name, Version* version ) const
{
	WString res_name_only	= Path::GetFileName( res_name, _false );
	WString extension_name	= Path::GetExtension( res_name );

	// Search manifest from high version to low version
	for ( _dword i = 0; i < mManifestFiles.Number( ); i ++ )
	{
		const ManifestFileInfo& manifest_file_info = mManifestFiles[i];

		// Get the items map
		const ItemInfoMap* items = manifest_file_info.mItems.Search( extension_name );
		if ( items == _null )
			continue;

		// Search for the resource
		const ItemInfo* item_info = items->Search( res_name );
		if ( item_info != _null )
		{
			if ( version != _null )
				*version = manifest_file_info.mVersion;

			return item_info;
		}
	}

	// Find nothing
	return _null;
}

const Version& ManifestFileManager::GetManifestVersion( ) const
{
	if ( mManifestFiles.Number( ) == 0 )
		return Version::cZero;

	return mManifestFiles[0].mVersion;
}

_void ManifestFileManager::ClearManifestFile( )
{
	mManifestFiles.Clear( );
}

_ubool ManifestFileManager::HasManifestFile( ) const
{
	return mManifestFiles.Number( ) != 0;
}

_dword ManifestFileManager::LoadManifestFile( const IManifestFile* manifest_file )
{
	if ( manifest_file == _null )
		return -1;

	// Create walker
	IManifestWalkerRef walker = manifest_file->CreateWalker( L"" );
	if ( walker.IsNull( ) )
		return -1;
	
	// The manifest file ID counter
	static _dword sManifestIDCounter = 1;
	
	// Add manifest file info
	ManifestFileInfo file_info;
	file_info.mID		= sManifestIDCounter ++;
	file_info.mVersion	= manifest_file->GetVersion( );
	
	// Add manifest file
	_dword index = mManifestFiles.InsertDescending< Version >( file_info );

	// Get the items
	ItemInfoWithExtMap& items = mManifestFiles[index].mItems;

	// Start to walk
	ManifestWalkerItemInfo walker_item_info;
	while ( walker->Walk( walker_item_info, L"", _FILE_FINDER_ENUMERATION_FILE_ONLY ) )
	{
		const ManifestItemInfo* manifest_item_info = walker_item_info.mItem;
		EGE_ASSERT( manifest_item_info != _null );

		// Get the resource name
		WStringObj res_name = manifest_item_info->mName;

		// Get the extension name
		WStringObj extension_name = Path::GetExtension( res_name );

		// Add item info
		ItemInfo& item_info		= items[ extension_name ][ res_name ];
		item_info.mResName		= res_name;
		item_info.mDirectory	= Path::GetDirectoryName( walker_item_info.mRelativePath );
		item_info.mMD5Code		= manifest_item_info->mMD5Code;
	}
		
	return file_info.mID;
}

_void ManifestFileManager::UnloadManifestFile( _dword id )
{
	for ( _dword i = 0; i < mManifestFiles.Number( ); i ++ )
	{
		if ( mManifestFiles[i].mID == id )
		{
			mManifestFiles.RemoveByIndex( i );
			break;
		}
	}
}

_ubool ManifestFileManager::HasResource( WStringPtr res_name ) const
{
	// Find the item info
	const ItemInfo* item_info = GetItemInfo( res_name, _null );
	if ( item_info == _null )
		return _false;

	return _true;
}

WString ManifestFileManager::GetRelativePath( WStringPtr res_name ) const
{
	// Find the item info
	const ItemInfo* item_info = GetItemInfo( res_name, _null );
	if ( item_info == _null )
		return WString( L"" );

	// Feedback relative path
	return Path::BuildFilePath( item_info->mDirectory.Str( ), item_info->mResName.Str( ) );
}

WString ManifestFileManager::GetRelativePath( WStringPtr res_name, Version& version ) const
{
	// Find the item info
	const ItemInfo* item_info = GetItemInfo( res_name, &version );
	if ( item_info == _null )
		return WString( L"" );

	// Feedback relative path
	return Path::BuildFilePath( item_info->mDirectory.Str( ), item_info->mResName.Str( ) );
}

WString ManifestFileManager::GetRelativePath( WStringPtr res_name, Version& version, MD5Code& md5_code ) const
{
	// Find the item info
	const ItemInfo* item_info = GetItemInfo( res_name, &version );
	if ( item_info == _null )
		return WString( L"" );

	// Feedback the MD5 code
	md5_code = item_info->mMD5Code;

	// Feedback relative path
	return Path::BuildFilePath( item_info->mDirectory.Str( ), item_info->mResName.Str( ) );
}

const MD5Code& ManifestFileManager::GetMD5Code( WStringPtr res_name ) const
{
	return MD5Code::cNull;
}
