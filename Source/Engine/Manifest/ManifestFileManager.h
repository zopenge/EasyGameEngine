//! @file     ManifestFileManager.h
//! @author   foreven
//! @version  
//! @date     2012/05/15

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ManifestFileManager
//----------------------------------------------------------------------------

class ManifestFileManager : public INTERFACE_OBJECT_IMPL( IManifestFileManager )
{
private:
	//!	The item info
	struct ItemInfo
	{
		MD5Code		mMD5Code;
		WStringObj	mDirectory;
		WStringObj	mResName;

		ItemInfo( )
		{
			mMD5Code = MD5Code::cNull;
		}
	};
	//!	Use resource name as key.
	typedef Map< ItemInfo, WStringObj > ItemInfoMap;
	//!	Use resource extension as key.
	typedef Map< ItemInfoMap, WStringObj > ItemInfoWithExtMap;

	//!	The manifest file info
	struct ManifestFileInfo
	{
		_dword				mID;
		Version				mVersion;
		ItemInfoWithExtMap	mItems;

		//!	Use version as key.
		operator const Version&( ) const
			{ return mVersion; }

		ManifestFileInfo( )
		{
			mID			= -1;
			mVersion	= Version::cZero;
		}
	};
	//!	We use the manifest from high version to low version.
	typedef Array< ManifestFileInfo > ManifestFileInfoArray;

private:
	//!	The manifest files
	ManifestFileInfoArray	mManifestFiles;

private:
	//!	Get item info by resource name.
	const ItemInfo* GetItemInfo( WStringPtr res_name, Version* version ) const;

public:
	ManifestFileManager( );
	virtual ~ManifestFileManager( );

// IManifestFileManager Interface
public:
	virtual const Version&	GetManifestVersion( ) const override;

	virtual _void			ClearManifestFile( ) override;
	virtual _ubool			HasManifestFile( ) const override;
	virtual _dword			LoadManifestFile( const IManifestFile* manifest_file ) override;
	virtual _void			UnloadManifestFile( _dword id ) override;

	virtual _ubool			HasResource( WStringPtr res_name ) const override;

	virtual WStringR		GetRelativePath( WStringPtr res_name ) const override;
	virtual WStringR		GetRelativePath( WStringPtr res_name, Version& version ) const override;
	virtual WStringR		GetRelativePath( WStringPtr res_name, Version& version, MD5Code& md5_code ) const override;

	virtual const MD5Code&	GetMD5Code( WStringPtr res_name ) const override;
};

}