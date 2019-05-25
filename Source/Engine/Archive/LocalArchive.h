//! @file     LocalArchive.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LocalArchive
//----------------------------------------------------------------------------

class LocalArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
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
	WString GetAbsoluteFileName( WStringPtr res_name ) const;
	//!	Get relative file name.
	WString GetRelativeFileName( WStringPtr res_name ) const;

public:
	LocalArchive( );
	virtual ~LocalArchive( );

public:
	_ubool AddPatchDir( WStringPtr path );
	_ubool RemovePatchDir( WStringPtr path );
	_ubool RefreshWorkingDir( );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;

	virtual WString				GetResourceAbsolutePath( WStringPtr res_name ) const override;
	virtual WString				GetResourceRelativePath( WStringPtr res_name ) const override;

	virtual IStreamReaderPassRef	LoadResourceByName( WStringPtr res_name ) override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
};

//----------------------------------------------------------------------------
// LocalArchive Implementation
//----------------------------------------------------------------------------

}