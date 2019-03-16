//! @file     StorageLocalArchive.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageLocalArchive
//----------------------------------------------------------------------------

class StorageLocalArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The file cache info
	struct FileCacheInfo
	{
		WStringObj	mRootPath;
		WStringObj	mResRelativePath;
	};

	//!	The resource name and file cache info.
	typedef Map< FileCacheInfo, WStringObj > FileCacheInfoMap;
	//!	The file caches and resource extension name.
	typedef Map< FileCacheInfoMap, WStringObj > FileCacheInfoMapWithExtMap;

private:
	//!	The patches.
	WStringArray				mPatches;

	//!	The file caches
	FileCacheInfoMapWithExtMap	mFileCaches;

private:
	//!	Refresh directory.
	_ubool RefreshDir( WStringPtr dir );
	_ubool RefreshFile( WStringPtr dir, const FileInfo& file_info );

	//!	Get absolute file name.
	WStringR GetAbsoluteFileName( WStringPtr res_name ) const;
	//!	Get relative file name.
	WStringR GetRelativeFileName( WStringPtr res_name ) const;

public:
	StorageLocalArchive( );
	virtual ~StorageLocalArchive( );

public:
	_ubool AddPatchDir( WStringPtr path, _ubool refresh_working_dir );
	_ubool RemovePatchDir( WStringPtr path );
	_ubool RefreshWorkingDir( );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;

	virtual WStringR				GetResourceAbsolutePath( WStringPtr res_name ) const override;
	virtual WStringR				GetResourceRelativePath( WStringPtr res_name ) const override;

	virtual IStreamReaderPassRef	LoadResourceByName( WStringPtr res_name ) override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
};

//----------------------------------------------------------------------------
// StorageLocalArchive Implementation
//----------------------------------------------------------------------------

}