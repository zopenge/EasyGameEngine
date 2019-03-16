//! @file     MD5ChecksumBuilder.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MD5ChecksumBuilder Implementation
//----------------------------------------------------------------------------

MD5ChecksumBuilder::MD5ChecksumBuilder( _dword chunk_size )
{
	mChunkSize = chunk_size;
}

MD5ChecksumBuilder::~MD5ChecksumBuilder( )
{

}

_ubool MD5ChecksumBuilder::BuildFromStream( IStreamReader* stream_reader, MD5Code& md5_code ) const
{
	if ( stream_reader == _null )
		return _false;

	// Get the current stream offset
	_dword offset = stream_reader->GetOffset( );

	// Create buffer for decode
	MemArrayPtr< _byte > buffer( mChunkSize );

	// Start to build MD5 checksum
	MD5 md5;
	while ( stream_reader->GetRemainBytes( ) > 0 )
	{
		// Get the chunk size what you will read
		_dword chunk_size = Math::Min< _dword >( stream_reader->GetRemainBytes( ), mChunkSize );
		EGE_ASSERT( chunk_size != 0 );

		// Read stream buffer
		_dword read_bytes = stream_reader->ReadBuffer( buffer, chunk_size );
		if ( read_bytes == 0 )
			break;

		// Update the MD5 checksum code
		md5.AppendBuffer( buffer, read_bytes );
	}

	// Resume the stream offset
	stream_reader->Seek( _SEEK_BEGIN, (_int)offset );

	// Feedback the MD5 code
	md5.Digest( );
	md5_code = md5.GetCode( );

	return _true;
}

_ubool MD5ChecksumBuilder::BuildFromFile( WStringPtr filename, MD5Code& md5_code ) const
{
	IFileStreamReaderRef file_stream = GetInterfaceFactory( )->CreateFileStreamReader( filename );
	if ( file_stream.IsNull( ) )
		return _false;

	return BuildFromStream( file_stream, md5_code );
}