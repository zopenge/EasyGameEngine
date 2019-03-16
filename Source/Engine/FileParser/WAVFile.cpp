//! @file     WAVFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// WAVFileWriter Implementation
//----------------------------------------------------------------------------

WAVFileWriter::WAVFileWriter( )
{
	mHasStarted = _false;

	EGE_INIT( mWAVDescHeaader );
	EGE_INIT( mWAVFormatHeader );
}

WAVFileWriter::~WAVFileWriter( )
{
	Stop( );
}

_ubool WAVFileWriter::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	return _true;
}

_ubool WAVFileWriter::SaveToStream( IStreamWriter* stream_writer ) const
{
	if ( stream_writer == _null )
		return _false;

	// We must have the buffer writer
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// Write header info
	stream_writer->WriteBuffer( &mWAVDescHeaader, sizeof( mWAVDescHeaader ) );
	// Write format info
	stream_writer->WriteBuffer( &mWAVFormatHeader, sizeof( mWAVFormatHeader ) );

	// Write data chunks
	stream_writer->WriteDword( EGE_ID( 'd', 'a', 't', 'a' ) );
	stream_writer->WriteDword( mStreamWriter->GetOffset( ) );
	stream_writer->WriteBuffer( mStreamWriter->GetBuffer( ), mStreamWriter->GetOffset( ) );

	return _true;
}

_ubool WAVFileWriter::Start( _dword channels, _dword sample_rate, _dword sample_bit_size )
{
	if ( channels == 0 || sample_rate == 0 || sample_bit_size == 0 )
		return _false;

	// Stop it first
	Stop( );

	// Started
	mHasStarted = _true;

	// See referenced website: http://soundfile.sapp.org/doc/WaveFormat/

	// Initialize header info
	mWAVDescHeaader.mRIFF	= WAVFile::_FILE_ID;
	mWAVDescHeaader.mSize	= sizeof( mWAVDescHeaader ) + sizeof( mWAVFormatHeader ) + sizeof( _dword ) * 2;
	mWAVDescHeaader.mFormat = EGE_ID( 'W', 'A', 'V', 'E' );

	// Initialize format info
	mWAVFormatHeader.mID			= EGE_ID( 'f', 'm', 't', ' ' );
	mWAVFormatHeader.mSize			= 16;
	mWAVFormatHeader.mAudioFormat	= 1;
	mWAVFormatHeader.mChannels		= channels;
	mWAVFormatHeader.mSampleRate	= sample_rate;
	mWAVFormatHeader.mByteRate		= sample_rate * channels * sample_bit_size / 8;
	mWAVFormatHeader.mBlockAlign	= channels * sample_bit_size / 8;
	mWAVFormatHeader.mSampleBitSize	= sample_bit_size;

	// Create the encode buffer writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( mWAVFormatHeader.mByteRate );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return _true;
}

_void WAVFileWriter::Stop( )
{
	if ( mHasStarted == _false )
		return;

	mHasStarted = _false;
}

_dword WAVFileWriter::Encode( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	if ( mHasStarted == _false )
		return 0;

	mWAVDescHeaader.mSize += size;

	// Write buffer
	return mStreamWriter->WriteBuffer( buffer, size );
}

//----------------------------------------------------------------------------
// WAVFile Implementation
//----------------------------------------------------------------------------

WAVFile::WAVFile( )
{
	mCurPCMBufferOffset	= -1;
	mPCMBufferSize		= 0;

	EGE_INIT( mWAVDescHeaader );
	EGE_INIT( mWAVFormatHeader );
}

WAVFile::~WAVFile( )
{
}

_void WAVFile::SynHeaderInfo( )
{
	mHeaderInfo.mChannels		= mWAVFormatHeader.mChannels;
	mHeaderInfo.mLength			= EGE_RATIO_DOUBLE( mPCMBufferSize, mWAVFormatHeader.mByteRate );
	mHeaderInfo.mSampleRate		= mWAVFormatHeader.mSampleRate;
	mHeaderInfo.mSampleBitSize	= mWAVFormatHeader.mSampleBitSize;
	if ( mHeaderInfo.mChannels == 1 )
		mHeaderInfo.mFormat	= mWAVFormatHeader.mSampleBitSize == 8 ? _AF_MONO8 : _AF_MONO16;
	else
		mHeaderInfo.mFormat	= mWAVFormatHeader.mSampleBitSize == 8 ? _AF_STEREO8 : _AF_STEREO16;
}

_ubool WAVFile::BuildDataChunks( IStreamReader* stream_reader )
{
	_dword offset_of_file	= stream_reader->GetOffset( );
	_dword end_of_file		= stream_reader->GetSize( );

	while ( offset_of_file < end_of_file )
	{
		// Read data chunk info
		_dword id = 0, size = 0;
		stream_reader->ReadDword( id );
		stream_reader->ReadDword( size );
		if ( size == 0 )
			break;

		// It's '.WAV' data chunk
		if ( id == EGE_ID( 'd', 'a', 't', 'a' ) )
		{
			// It's valid .WAV data chunk
			mWAVDataChunks.InsertAscending( WaveDataChunkHeader( mPCMBufferSize, stream_reader->GetOffset( ), size ) );

			// Update the PCM buffer size
			mPCMBufferSize += size;
		}

		// Jump to the next data chunk
		offset_of_file = stream_reader->Seek( _SEEK_CURRENT, (_int)size );
	}

	return _true;
}

_FILE_FORMAT WAVFile::GetFileID( ) const
{
	return _FF_WAV;
}

_ubool WAVFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Read WAV description header
	stream_reader->ReadBuffer( &mWAVDescHeaader, sizeof( mWAVDescHeaader ) );

	// Check for valid .WAV file
	if ( mWAVDescHeaader.mRIFF != _FILE_ID || mWAVDescHeaader.mFormat != EGE_ID( 'W', 'A', 'V', 'E' ) )
	{
		WLOG_ERROR( L"It's invalid *.wav file format" );
		return _false;
	}

	// Read WAV format header
	stream_reader->ReadBuffer( &mWAVFormatHeader, sizeof( mWAVFormatHeader ) );

	// Check for valid .WAV file
	// PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
	if ( mWAVFormatHeader.mID != EGE_ID( 'f', 'm', 't', ' ' ) || mWAVFormatHeader.mAudioFormat != 1 )
	{
		WLOG_ERROR( L"It's invalid *.wav audio format" );
		return _false;
	}

	// Set the PCM buffer offset_of_file in initial status ( start position )
	mCurPCMBufferOffset = 0;

	// Build data chunks
	if ( BuildDataChunks( stream_reader ) == _false )
	{
		WLOG_ERROR( L"Build *.wav data chunks failed" );
		return _false;
	}

	// Save the stream reader
	mStreamReader = stream_reader;

	// Syn the sound header info
	SynHeaderInfo( );

	return _true;
}

_void WAVFile::Unload( )
{
	mCurPCMBufferOffset = -1;
	mPCMBufferSize		= 0;

	EGE_INIT( mWAVDescHeaader );
	EGE_INIT( mWAVFormatHeader );
	mWAVDataChunks.Clear( );

	BaseClass::Unload( );
}

_ubool WAVFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	if ( stream_writer == _null )
		return _false;

	// Write header info
	stream_writer->WriteBuffer( &mWAVDescHeaader, sizeof( mWAVDescHeaader ) );
	// Write format info
	stream_writer->WriteBuffer( &mWAVFormatHeader, sizeof( mWAVFormatHeader ) );

	// Write data chunks
	for ( _dword i = 0; i < mWAVDataChunks.Number( ); i ++ )
	{
		const WaveDataChunkHeader& chunk = mWAVDataChunks[i];

		stream_writer->WriteDword( EGE_ID( 'd', 'a', 't', 'a' ) );
		stream_writer->WriteDword( chunk.mSize );
		stream_writer->WriteBuffer( mStreamReader->GetBuffer( ) + chunk.mOffsetOfFile, chunk.mSize );
	}

	return _true;
}

_double WAVFile::TimeSeek( _SEEK flag, _double time )
{
	// Change time to offset in bytes
	_dword offset = (_dword)( time * (_double) mWAVFormatHeader.mByteRate );

	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
			mCurPCMBufferOffset = offset;
		}
		break;

		case _SEEK_CURRENT:
		{
			mCurPCMBufferOffset += offset;
		}
		break;

		case _SEEK_END:
		{
			mCurPCMBufferOffset = mStreamReader->GetSize( ) - offset;
		}
		break;

		default:
			return -1.0;
	}

	return EGE_RATIO( mCurPCMBufferOffset, mWAVFormatHeader.mByteRate );
}

_double WAVFile::GetCurTime( ) const
{
	return EGE_RATIO( mCurPCMBufferOffset, mWAVFormatHeader.mByteRate );
}

_dword WAVFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	// Check whether finished decode
	if ( mCurPCMBufferOffset >= mPCMBufferSize )
		return 0;

	// Find the data chunk by PCM offset
	_dword index = mWAVDataChunks.LowerBoundAscending( mCurPCMBufferOffset );
	if ( index == -1 )
		return 0;

	// Get the start position of file
	_dword start_pos_of_file	= mWAVDataChunks[ index ].mOffsetOfFile + ( mCurPCMBufferOffset - mWAVDataChunks[ index ].mOffsetOfPCM );
	// The current read size
	_dword total_read_size		= 0;

	// Locate stream position
	mStreamReader->Seek( _SEEK_BEGIN, (_int)start_pos_of_file );

	// Start to read PCM buffer data
	_byte* buffer_ptr = buffer; _dword remain_size = size;
	for ( _dword i = index; i < mWAVDataChunks.Number( ); i ++ )
	{
		const WaveDataChunkHeader& data_chunk = mWAVDataChunks[i];

		// Get the read size in bytes
		_dword read_size = Math::Min( data_chunk.mSize - mCurPCMBufferOffset, remain_size );

		// Start to read PCM buffer data
		read_size = mStreamReader->ReadBuffer( buffer_ptr, read_size );

		// Update buffer and remain size in bytes
		buffer_ptr	+= read_size;
		remain_size	-= read_size;

		// Update the current PCM buffer offset
		mCurPCMBufferOffset += read_size;

		// Update the read size
		total_read_size += read_size;

		// Do we finished ?
		if ( remain_size == 0 )
			break;
	}

	// Feedback the decode size
	return total_read_size;
}