//! @file     StoragePackageStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePackageStreamReader
//----------------------------------------------------------------------------

class StoragePackageStreamReader : public INTERFACE_STREAM_READER_IMPL( IStreamReader )
{
private:
	typedef INTERFACE_STREAM_READER_IMPL( IStreamReader ) BaseClass;

private:
	typedef RefPtr< StoragePackageFile > PackageFileRef;

private:
	//!	The offset of package item
	_dword				mOffset;

	//!	The package file
	PackageFileRef		mPackageFile;
	//£¡	The package item
	const PackageItem*	mPackageItem;

public:
	StoragePackageStreamReader( const PackageItem* package_item, StoragePackageFile* package_file );
	virtual ~StoragePackageStreamReader( );

public:
	//!	The storage stream interface
	#define STORAGE_STREAM_READER
	#include "Module/Storage/StorageStreamMethods.h"
	#undef STORAGE_STREAM_READER
};

//----------------------------------------------------------------------------
// StoragePackageStreamReader Implementation
//----------------------------------------------------------------------------

}