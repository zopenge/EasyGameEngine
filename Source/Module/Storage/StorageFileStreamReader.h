//! @file     StorageFileStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageFileStreamReader
//----------------------------------------------------------------------------

class StorageFileStreamReader : public TObject< IFileStreamReader >
{
private:
	//!	The file stream reader
	IFileStreamReaderRef	mStreamReader;

public:
	StorageFileStreamReader( );
	virtual ~StorageFileStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr root_path, WStringPtr relative_file_name );

// IObject Interface
public:
	virtual _void		Uninitialize( ) override;

// IFileStream Interface
public:
	virtual WStringPtr	GetFileName( ) const override;

public:
	//!	The storage stream interface
	#define STORAGE_STREAM_READER
	#include "Module/Storage/StorageStreamMethods.h"
	#undef STORAGE_STREAM_READER
};

//----------------------------------------------------------------------------
// StorageFileStreamReader Implementation
//----------------------------------------------------------------------------

}