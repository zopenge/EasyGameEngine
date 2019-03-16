//! @file     CompressionDecoderZLIB.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// CompressionDecoderZLIB Implementation
//----------------------------------------------------------------------------

CompressionDecoderZLIB::CompressionDecoderZLIB( )
{
	EGE_INIT( mZIPStream );
}

CompressionDecoderZLIB::~CompressionDecoderZLIB( )
{
	OnEndProcessBuffer( );
}

_ubool CompressionDecoderZLIB::OnBeginProcessBuffer( )
{
	// Build inflate state
	if ( mZIPStream.mIsInited == _false )
	{
		mZIPStream.mIsInited	= _true;

		mZIPStream.avail_in		= 0;
		mZIPStream.next_in		= _null;
		mZIPStream.total_in		= 0;

		mZIPStream.avail_out	= 0;
		mZIPStream.next_out		= _null;
		mZIPStream.total_out	= 0;

		mZIPStream.msg			= _null;
		mZIPStream.state		= _null;

		mZIPStream.zalloc		= 0;
		mZIPStream.zfree		= 0;
		mZIPStream.opaque		= 0;

		mZIPStream.data_type	= 0;
		mZIPStream.adler		= 0;
		mZIPStream.reserved		= 0;

		// Initialize inflate state
		if ( ::inflateInit( &mZIPStream ) != Z_OK )
			return _false;
	}

	return _true;
}

_ubool CompressionDecoderZLIB::OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size )
{
	// Initialize inflate state
	mZIPStream.next_in	= (z_const Bytef*) input_buf;
	mZIPStream.avail_in	= (uInt)input_size;

	// Create temporary buffer data
	MemArrayPtr< _byte > temp_buf( chunk_size );

	// Start to decompress
	while ( mZIPStream.avail_in > 0 )
	{
		mZIPStream.next_out		= temp_buf;
		mZIPStream.avail_out	= (uInt)chunk_size;

		// Inflate stream
		_int ret = ::inflate( &mZIPStream, Z_NO_FLUSH );
		if ( ret < 0 )
			return _false;

		// Write decompressed buffer data
		_dword write_size = chunk_size - mZIPStream.avail_out;
		stream_writer->WriteBuffer( temp_buf, write_size );

		// Update output size
		output_size += write_size;

		// Check whether it's end of stream
		if ( ret == Z_STREAM_END )
			break;
	}

	return _true;
}

_ubool CompressionDecoderZLIB::OnEndProcessBuffer( )
{
	// End compression stream
	if ( mZIPStream.mIsInited )
		::inflateEnd( &mZIPStream );

	mZIPStream.mIsInited = _false;

	return _true;
}