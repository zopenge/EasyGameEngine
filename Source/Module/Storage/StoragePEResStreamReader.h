//! @file     StoragePEResStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePEResStreamReader
//----------------------------------------------------------------------------

class StoragePEResStreamReader : public INTERFACE_STREAM_READER_IMPL( IStreamReader )
{
private:
	typedef INTERFACE_STREAM_READER_IMPL( IStreamReader ) BaseClass;

private:
	//!	The resource handle
	_handle				mResource;
	//!	The resource data
	_byte*				mBuffer;
	//!	The resource size
	_dword				mSize;

	//!	The stream reader
	IStreamReaderRef	mStreamReader;

public:
	StoragePEResStreamReader( );
	virtual ~StoragePEResStreamReader( );

public:
	//!	Initialize.
	//!	@param		resource	The resource handle.
	//!	@param		size		The resource size.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( _handle resource, _dword size );

public:
	//!	The storage stream interface
	#define STORAGE_STREAM_READER
	#include "Module/Storage/StorageStreamMethods.h"
	#undef STORAGE_STREAM_READER
};

//----------------------------------------------------------------------------
// StoragePEResStreamReader Implementation
//----------------------------------------------------------------------------

}