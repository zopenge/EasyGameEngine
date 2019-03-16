//! @file     MD5ChecksumBuilder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MD5ChecksumBuilder
//----------------------------------------------------------------------------

class MD5ChecksumBuilder : public INTERFACE_OBJECT_IMPL( IMD5ChecksumBuilder )
{
private:
	//!	The temporary chunk size of reading from stream
	_dword	mChunkSize;

public:
	MD5ChecksumBuilder( _dword chunk_size );
	virtual ~MD5ChecksumBuilder( );

// IMD5ChecksumBuilder Interface
public:
	virtual _ubool	BuildFromStream( IStreamReader* stream_reader, MD5Code& md5_code ) const override;

	virtual _ubool	BuildFromFile( WStringPtr filename, MD5Code& md5_code ) const override;
};

}