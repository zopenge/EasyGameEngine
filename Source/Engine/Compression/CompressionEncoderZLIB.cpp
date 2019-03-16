//! @file     CompressionEncoderZLIB.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// CompressionEncoderZLIB Implementation
//----------------------------------------------------------------------------

CompressionEncoderZLIB::CompressionEncoderZLIB( )
{
	mLevel = _LEVEL_DEFAULT;

	EGE_INIT( mZIPStream );
}

CompressionEncoderZLIB::~CompressionEncoderZLIB( )
{
	OnEndProcessBuffer( );
}

void *myalloc( void *q, unsigned int n, unsigned int m )
{
	return calloc(n, m);
}

void myfree(void *q, void *p)
{
	free(p);
}

_ubool CompressionEncoderZLIB::OnBeginProcessBuffer( )
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

		mZIPStream.zalloc		= myalloc;
		mZIPStream.zfree		= myfree;
		mZIPStream.opaque		= 0;

		mZIPStream.data_type	= 0;
		mZIPStream.adler		= 0;
		mZIPStream.reserved		= 0;

		// Get the compression level
		_dword zlevel = Z_NO_COMPRESSION;
		switch ( mLevel )
		{
			case _LEVEL_DEFAULT:			zlevel = Z_DEFAULT_COMPRESSION; break;
			case _LEVEL_BEST_SPEED:			zlevel = Z_BEST_SPEED; break;
			case _LEVEL_BEST_COMPRESSION:	zlevel = Z_BEST_COMPRESSION; break;
			default:
				return _false;
		}

		// Initialize deflate state
		if ( ::deflateInit( &mZIPStream, (int)zlevel ) != Z_OK )
			return _false;
	}

	return _true;
}

_ubool CompressionEncoderZLIB::OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size )
{
	// Initialize inflate state
	mZIPStream.next_in	= (z_const Bytef*) input_buf;
	mZIPStream.avail_in	= (uInt)input_size;

	// Create temporary buffer data
	MemArrayPtr< _byte > temp_buf( chunk_size );

	// Start to decompress
	while ( mZIPStream.total_in < input_size )
	{
		mZIPStream.next_out		= temp_buf;
		mZIPStream.avail_out	= (uInt)chunk_size;

		// Deflate the stream
		_int ret = ::deflate( &mZIPStream, Z_NO_FLUSH );
		if ( ret < 0 )
			return _false;

		// Write decompressed buffer data
		_dword write_size = chunk_size - mZIPStream.avail_out;
		stream_writer->WriteBuffer( temp_buf, write_size );

		// Update output size
		output_size += write_size;
	}

	// Finish the stream, still forcing small buffers
	while ( _true )
	{
		mZIPStream.next_out		= temp_buf;
		mZIPStream.avail_out	= 1;

		_int ret = ::deflate( &mZIPStream, Z_FINISH );
		if ( ret < 0 )
			return _false;

		// Write decompressed buffer data
		stream_writer->WriteByte( temp_buf[0] );

		// Update output size
		output_size ++;

		if ( ret == Z_STREAM_END )
			break;
	}

	return _true;
}

_ubool CompressionEncoderZLIB::OnEndProcessBuffer( )
{
	// End compression stream
	if ( mZIPStream.mIsInited )
		::deflateEnd( &mZIPStream );

	mZIPStream.mIsInited = _false;

	return _true;
}

_void CompressionEncoderZLIB::SetLevel( _LEVEL level )
{
	mLevel = level;
}