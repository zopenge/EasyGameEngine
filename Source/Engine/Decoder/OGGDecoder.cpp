//! @file     OGGDecoder.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// OGGDecoder Helpful Functions Implementation
//----------------------------------------------------------------------------

static _short clip16( _int inVal ) 
{
	return (_short)((inVal > 32767) ? (32767) : ((inVal < -32768) ? (-32768) : (inVal))); 
}

//----------------------------------------------------------------------------
// OGGDecoder Implementation
//----------------------------------------------------------------------------

OGGDecoder::OGGDecoder( )
{
	mPacketCount	= 0;
}

OGGDecoder::~OGGDecoder( )
{
}

_ubool OGGDecoder::DecodeBuffer( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return _false;

	// Prepare for the packet info
	mWorkPacket.b_o_s		= 0;
	mWorkPacket.bytes		= size;
	mWorkPacket.e_o_s		= 0;
	mWorkPacket.granulepos	= 0;
	mWorkPacket.packet		= const_cast<unsigned char*>(buffer);
	mWorkPacket.packetno	= mPacketCount ++;

	// Create packet info
	if ( vorbis_synthesis( &mVorbisBlock, &mWorkPacket ) == 0 )
	{
		if ( vorbis_synthesis_blockin( &mVorbisState, &mVorbisBlock ) != 0 )
			return _false;
	}

	// Get the channels number
	_int channels = mVorbisInfo.channels;

	// Start to decode
	_float** pcm; _int samples = 0;
	while ( (samples = vorbis_synthesis_pcmout( &mVorbisState, &pcm )) > 0 )
	{
		_dword	pcm_number	= channels * samples;
		_short* pcm_samples = new _short[pcm_number];

		for ( _int ch = 0; ch < channels; ++ch )
		{
			_short* temp_buffer = pcm_samples + ch;
			const _float* const one_channel = pcm[ch];

			for ( _int i = 0; i < samples; ++i )
			{
				_int temp = static_cast<_int>(one_channel[i] * 32767.0f);
				*temp_buffer = clip16( temp );

				temp_buffer += channels;
			}
		}

		vorbis_synthesis_read( &mVorbisState, samples );

		// Write PCM buffer data
		mStreamWriter->WriteBuffer( pcm_samples, pcm_number * sizeof( _short ) );

		EGE_DELETE_ARRAY( pcm_samples );
	}

	return _true;
}

_ubool OGGDecoder::Initialize( const SoundVorbisFormatInfo* info )
{
	if ( info == _null )
		return _false;

	mPacketCount = 0;

	// Initialize info and comment section
	vorbis_info_init( &mVorbisInfo );
	vorbis_comment_init( &mVorbisComment );

	// Initialize OGG packet info
	ogg_packet ogg_pkt	= {0};
	ogg_pkt.packet		= (unsigned char*)info->GetIDSection( );
	ogg_pkt.bytes		= info->GetIDSectionSize( );
	ogg_pkt.b_o_s		= 1;
	ogg_pkt.packetno	= mPacketCount++;

	// Build the "Comment Header" packet
	ogg_packet ogg_comment	= {0};
	ogg_comment.packet		= (unsigned char*)info->GetCommentSection( );
	ogg_comment.bytes		= info->GetCommentSectionSize( );
	ogg_comment.b_o_s		= 0;
	ogg_comment.packetno	= mPacketCount++;

	// Build the "Setup Header" packet
	ogg_packet ogg_codecsetup	= {0};
	ogg_codecsetup.packet		= (unsigned char*)info->GetCodeBookSection( );
	ogg_codecsetup.bytes		= info->GetCodeBookSectionSize( );
	ogg_codecsetup.b_o_s		= 0;
	ogg_codecsetup.packetno		= mPacketCount++;

	// Create OGG headers
	if ( vorbis_synthesis_headerin( &mVorbisInfo, &mVorbisComment, &ogg_pkt ) != 0 )
		return _false;

	if ( vorbis_synthesis_headerin( &mVorbisInfo, &mVorbisComment, &ogg_comment ) != 0 )
		return _false;

	if ( vorbis_synthesis_headerin( &mVorbisInfo, &mVorbisComment, &ogg_codecsetup ) != 0 )
		return _false;

	vorbis_synthesis_init( &mVorbisState, &mVorbisInfo );
	vorbis_block_init( &mVorbisState, &mVorbisBlock );

	// Create stream to save decode buffer data
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return _true;
}

_ubool OGGDecoder::ProcessBuffer( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return _false;

	// Resume the stream writer to update decode data
	mStreamWriter->Seek( _SEEK_BEGIN, 0 );

	return DecodeBuffer( size, buffer );
}

_dword OGGDecoder::GetProcessedBufferSize( ) const
{
	return mStreamWriter->GetOffset( );
}

const _byte* OGGDecoder::GetProcessedBufferData( ) const
{
	return mStreamWriter->GetBuffer( );
}

IStreamReaderPassRef OGGDecoder::GetProcessedStreamReader( ) const
{
	return GetInterfaceFactory( )->CreateMemStreamReader( GetProcessedBufferData( ), GetProcessedBufferSize( ), _STREAM_SHARE_MODE_READ_ONLY );
}

_ubool OGGDecoder::ProcessBlockEntry( const IMediaFileBlockEntry* block_entry )
{
	if ( block_entry == _null )
		return _false;

	// Resume the stream writer to update decode data
	mStreamWriter->Seek( _SEEK_BEGIN, 0 );

	for ( _dword i = 0; i < block_entry->GetFrameNumber( ); i ++ )
	{
		_dword size = block_entry->GetFrameSizeByIndex( i );

		MemArrayPtr< _byte > buffer( size );
		_dword read_size = block_entry->GetFrameDataByIndex( i, buffer.GetPointer( ) );

		if ( DecodeBuffer( size, buffer.GetPointer( ) ) == _false )
			return _false;
	}

	return _true;
}
