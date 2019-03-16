//! @file     StoragePEResStreamWriter.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePEResStreamWriter
//----------------------------------------------------------------------------

class StoragePEResStreamWriter : public INTERFACE_STREAM_WRITER_IMPL( IStreamWriter )
{
private:
	typedef INTERFACE_STREAM_WRITER_IMPL( IStreamWriter ) BaseClass;

public:
	StoragePEResStreamWriter( );
	virtual ~StoragePEResStreamWriter( );

public:
	//!	The storage stream interface
	#define STORAGE_STREAM_WRITER
	#include "Module/Storage/StorageStreamMethods.h"
	#undef STORAGE_STREAM_WRITER
};

//----------------------------------------------------------------------------
// StoragePEResStreamWriter Implementation
//----------------------------------------------------------------------------

}