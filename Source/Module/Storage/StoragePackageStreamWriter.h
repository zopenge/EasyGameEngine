//! @file     StoragePackageStreamWriter.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePackageStreamWriter
//----------------------------------------------------------------------------

class StoragePackageStreamWriter : public INTERFACE_STREAM_WRITER_IMPL( IStreamWriter )
{
private:
	typedef INTERFACE_STREAM_WRITER_IMPL( IStreamWriter ) BaseClass;

private:
	typedef RefPtr< StoragePackageFile > PackageFileRef;

private:
	//!	The offset of item in bytes
	_dword				mOffset;

	//!	The package file
	PackageFileRef		mPackageFile;
	//£¡	The package item
	const PackageItem*	mPackageItem;

public:
	StoragePackageStreamWriter( const PackageItem* package_item, StoragePackageFile* package_file );
	virtual ~StoragePackageStreamWriter( );

public:
	//!	The storage stream interface
	#define STORAGE_STREAM_WRITER
	#include "Module/Storage/StorageStreamMethods.h"
	#undef STORAGE_STREAM_WRITER
};

//----------------------------------------------------------------------------
// StoragePackageStreamWriter Implementation
//----------------------------------------------------------------------------

}