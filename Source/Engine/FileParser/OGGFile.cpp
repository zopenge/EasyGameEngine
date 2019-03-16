//! @file     OGGFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// OGGFileWriter Implementation
//----------------------------------------------------------------------------

OGGFileWriter::OGGFileWriter( )
{
	mHasStarted		= _false;

	mSampleBitSize	= 0;

	EGE_INIT( mStreamState );
	EGE_INIT( mPage );
	EGE_INIT( mPacket );

	EGE_INIT( mInfo );
	EGE_INIT( mComment );

	EGE_INIT( mDSPState );
	EGE_INIT( mBlock );
}

OGGFileWriter::~OGGFileWriter( )
{
	Stop( );
}

_dword OGGFileWriter::EncodePCM2OGG( IStreamReader* stream_reader )
{
	const _dword sReadSize = 1024;
	_tiny readbuffer[sReadSize* 4]; // Remember to use 'signed char' here, because we need to calculate with negative number

	// Read chunk data
	_dword bytes = stream_reader->ReadBuffer( readbuffer, sReadSize * 4 );
	if ( bytes == 0 )
		return 0;

	// Expose the buffer to submit data
	_float** ogg_buffer = vorbis_analysis_buffer( &mDSPState, sReadSize );
	if ( ogg_buffer == _null )
		return 0;

	// Get the OGG buffer size to write
	_dword write_bytes = bytes / 2;

	// Get the channel number
	_dword channels = mInfo.channels;

	// Start to convert PCM to OGG
	if ( channels == 1 )
	{
		for ( _dword i = 0; i < write_bytes; i++ )
			ogg_buffer[0][i] = ((readbuffer[i * 2 + 1] << 8) | (0x00ff & (int)readbuffer[i * 2])) / 32768.f;
	}

	return write_bytes;
}

_void OGGFileWriter::FlushPacket( )
{
	// Vorbis does some data preanalysis, then divvies up blocks for more involved (potentially parallel) processing.  
	// Get a single block for encoding now
	while ( vorbis_analysis_blockout( &mDSPState, &mBlock ) == 1 )
	{
		// Analysis, assume we want to use bitrate management */
		vorbis_analysis( &mBlock, _null );
		vorbis_bitrate_addblock( &mBlock );

		while ( vorbis_bitrate_flushpacket( &mDSPState, &mPacket ) )
		{
			// Weld the packet into the bitstream
			ogg_stream_packetin( &mStreamState, &mPacket );

			// Write out pages (if any)
			while ( _true ) 
			{
				_int result = ogg_stream_pageout( &mStreamState, &mPage );
				if ( result == 0 )
					break;

				mStreamWriter->WriteBuffer( mPage.header, mPage.header_len );
				mStreamWriter->WriteBuffer( mPage.body, mPage.body_len );

				// This could be set above, but for illustrative purposes, I do it here (to show that vorbis does know where the stream ends)
				if ( ogg_page_eos( &mPage ) )
					break;
			}
		}
	}
}

_ubool OGGFileWriter::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	ISoundFileRef sound_file = GetInterfaceFactory( )->ParseSoundFile( stream_reader );
	if ( sound_file.IsNull( ) )
		return _false;

	const SoundHeaderInfo& header_info = sound_file->GetHeaderInfo( );

	if ( Start( header_info.mChannels, header_info.mSampleRate, header_info.mSampleBitSize ) == _false )
		return _false;

	while ( _true )
	{
		_byte buffer[4096];
		_dword size = sound_file->Decode( buffer, 4096 );
		if ( size == 0 )
			break;

		Encode( buffer, size );
	}

	Stop( );

	return _true;
}

_ubool OGGFileWriter::SaveToStream( IStreamWriter* stream_writer ) const
{
	if ( stream_writer == _null )
		return _false;

	if ( mStreamWriter.IsNull( ) )
		return _false;

	stream_writer->WriteBuffer( mStreamWriter->GetBuffer( ), mStreamWriter->GetOffset( ) );

	return _true;
}

_ubool OGGFileWriter::Start( _dword channels, _dword sample_rate, _dword sample_bit_size )
{
	if ( channels == 0 || channels > 2 )
		return _false;

	if ( sample_rate == 0 )
		return _false;

	if ( sample_bit_size == 0 || sample_bit_size < 8 )
		return _false;

	// Stop it first
	Stop( );

	// Started
	mHasStarted		= _true;
	mSampleBitSize	= sample_bit_size;

	// Get the KBS of OGG
	_dword kbs = (sample_bit_size * sample_rate) / 8;
	 if ( kbs == 0 )
		 return _false;

	 // Initialize OGG info
	vorbis_info_init( &mInfo );

	// Initialize encoder
	_int ret = vorbis_encode_init( &mInfo, channels, sample_rate, -1, kbs, -1 );
	if ( ret < 0 )
		return _false;

	// Add a comment
	vorbis_comment_init( &mComment );
	vorbis_comment_add_tag( &mComment, "ENCODER", "EGE" );

	// Set up the analysis state and auxiliary encoding storage
	vorbis_analysis_init( &mDSPState, &mInfo );
	vorbis_block_init( &mDSPState, &mBlock );

	// Set up our packet->stream encoder
	ogg_stream_init( &mStreamState, Random::Gen( ) );

	// Initialize OGG header info
	ogg_packet header;
    ogg_packet header_comm;
    ogg_packet header_code;
    vorbis_analysis_headerout( &mDSPState, &mComment, &header, &header_comm, &header_code );
    ogg_stream_packetin( &mStreamState, &header );
    ogg_stream_packetin( &mStreamState, &header_comm );
    ogg_stream_packetin( &mStreamState, &header_code );

	// Create stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// This ensures the actual audio data will start on a new page, as per spec
    while ( _true )
	{
		_int result = ogg_stream_flush( &mStreamState, &mPage );
		if ( result == 0 )
			break;

		mStreamWriter->WriteBuffer( mPage.header, mPage.header_len );
		mStreamWriter->WriteBuffer( mPage.body, mPage.body_len );
    }

	return _true;
}

_void OGGFileWriter::Stop( )
{
	if ( mHasStarted == _false )
		return;

	// Done
	vorbis_analysis_wrote( &mDSPState, 0 );

	// Flush packet and write OGG data to stream
	FlushPacket( );

	// Clear OGG stream info
	ogg_stream_clear( &mStreamState );
	vorbis_block_clear( &mBlock );
	vorbis_dsp_clear( &mDSPState );
	vorbis_comment_clear( &mComment );
	vorbis_info_clear( &mInfo );

	mHasStarted = _false;
}

_dword OGGFileWriter::Encode( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	if ( mHasStarted == _false )
		return 0;

	// Create stream reader to get PCM audio data
	IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( buffer, size, _STREAM_SHARE_MODE_READ_ONLY );
	if ( stream_reader.IsNull( ) )
		return 0;

	// Encode PCM->OGG
	while ( _true )
	{
		_dword encode_size = EncodePCM2OGG( stream_reader );
		if ( encode_size == 0 )
			break;

		// Tell the library how much we actually submitted
		vorbis_analysis_wrote( &mDSPState, encode_size );
	}

	return size;
}

//----------------------------------------------------------------------------
// OGGFile Implementation
//----------------------------------------------------------------------------

OGGFile::OGGFile( )
{
	mVorbisInfo		= _null;
	mVorbisComment	= _null;

	EGE_INIT( mVorbisStream );
}

OGGFile::~OGGFile( )
{
	Unload( );
}

size_t OGGFile::OnReadCallback( void* ptr, size_t size, size_t nmemb, void* datasource )
{
	IStreamReader* stream_reader = (IStreamReader*) datasource;

	_dword read_bytes = stream_reader->ReadBuffer( ptr, (_dword)(size * nmemb) );
	return (size_t) read_bytes;
}

int OGGFile::OnSeekCallback( void* datasource, ogg_int64_t offset, int whence )
{
	IStreamReader* stream_reader = (IStreamReader*) datasource;

	return stream_reader->Seek( (_SEEK) whence, (_int) offset );
}

int OGGFile::OnCloseCallback( void* datasource )
{
	// The stream reader will closed in Unload( ) function, so skip to release it here
	return 0;
}

long OGGFile::OnTellCallback( void* datasource )
{
	IStreamReader* stream_reader = (IStreamReader*) datasource;

	return stream_reader->GetOffset( );
}

AStringPtr OGGFile::GetOggErrDesc( _int err_id ) const
{
	switch ( err_id )
	{
		case 0:				return "OV_ERR_NO";
		case OV_FALSE:		return "OV_FALSE";
		case OV_EOF:		return "OV_EOF";
		case OV_HOLE:		return "OV_HOLE";
		case OV_EREAD:		return "OV_ERR_READ";
		case OV_EFAULT:		return "OV_ERR_FAULT";
		case OV_EIMPL:		return "OV_ERR_IMPL";
		case OV_EINVAL:		return "OV_ERR_INVAL";
		case OV_ENOTVORBIS:	return "OV_ERR_NOT_VORBIS";
		case OV_EBADHEADER:	return "OV_ERR_BAD_HEADER";
		case OV_EVERSION:	return "OV_ERR_VERSION";
		case OV_ENOTAUDIO:	return "OV_ERR_NOT_AUDIO";
		case OV_EBADPACKET:	return "OV_ERR_BAD_PACKET";
		case OV_EBADLINK:	return "OV_ERR_BAD_LINK";
		case OV_ENOSEEK:	return "OV_ERR_NO_SEEK";
		default:
			return "OV_ERR_UNKNOWN";
	}
}

_FILE_FORMAT OGGFile::GetFileID( ) const
{
	return _FF_OGG;
}

_ubool OGGFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Initialize the vorbis stream
	ov_callbacks callbacks;
	callbacks.read_func		= OnReadCallback;
	callbacks.seek_func		= OnSeekCallback;
	callbacks.close_func	= OnCloseCallback;
	callbacks.tell_func		= OnTellCallback;

	// Open the data stream
	_int ret = ::ov_open_callbacks( stream_reader, &mVorbisStream, _null, 0, callbacks );
	if ( ret < 0 )
	{
		ALOG_ERROR_1( "Initialize the OGG data stream failed(err: %s)", GetOggErrDesc( ret ).Str( ) );
		return _false;
	}

	// Save the stream reader
	mStreamReader = stream_reader;

	// Read the info and comment
	mVorbisInfo		= ::ov_info( &mVorbisStream, -1 );
	mVorbisComment	= ::ov_comment( &mVorbisStream, -1 );

	// Build the sound header info
	mHeaderInfo.mChannels		= mVorbisInfo->channels;
	mHeaderInfo.mFormat			= mVorbisInfo->channels == 1 ? _AF_MONO16 : _AF_STEREO16;
	mHeaderInfo.mLength			= ::ov_time_total( &mVorbisStream, -1 );
	mHeaderInfo.mSampleRate		= (_dword)mVorbisInfo->rate;
	mHeaderInfo.mSampleBitSize	= mVorbisInfo->channels == 1 ? 16 : 32;

	return _true;
}

_void OGGFile::Unload( )
{
	::ov_clear( &mVorbisStream );

	mVorbisInfo		= _null;
	mVorbisComment	= _null;

	EGE_INIT( mVorbisStream );

	mStreamReader.Clear( );

	BaseClass::Unload( );
}

_double OGGFile::TimeSeek( _SEEK flag, _double time )
{
    LockOwner lock_owner( mLocker );
    
	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
			::ov_time_seek( &mVorbisStream, time );

			return time;
		}
		break;

		case _SEEK_CURRENT:
		{
			_double pos = ::ov_time_tell( &mVorbisStream ) + time;
			::ov_time_seek( &mVorbisStream, pos );

			return pos;
		}
		break;

		case _SEEK_END:
		{
			_double pos = mHeaderInfo.mLength - time;
			::ov_time_seek( &mVorbisStream, pos );

			return pos;
		}
		break;

		default:
			return -1;
	}
}

_double OGGFile::GetCurTime( ) const
{
	return ::ov_time_tell( (OggVorbis_File*) &mVorbisStream );
}

_dword OGGFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	LockOwner lock_owner( mLocker );

	_int section		= 0;
	_int read_bytes	= 0;

	// Decode OGG stream
	while ( read_bytes < (_int) size )
	{
		_int result = (_int)::ov_read( &mVorbisStream, (_chara*) buffer + read_bytes, (_int)size - read_bytes, 0, 2, 1, &section );
		if ( result == -1 )
			return 0;

		if ( result == 0 )
			break;

		read_bytes += result;
	}

	// Feedback the decode size in bytes
	return read_bytes;
}