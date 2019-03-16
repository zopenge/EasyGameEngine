//! @file     OGGDecoder.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// OGGDecoder
//----------------------------------------------------------------------------

//!	Thanks for https://bluishcoder.co.nz/2009/06/24/reading-ogg-files-using-libogg.html
class OGGDecoder : public TObject< IAudioDecoder >
{
private:
	_dword				mPacketCount;

	vorbis_info			mVorbisInfo;
	vorbis_comment		mVorbisComment;
	vorbis_dsp_state	mVorbisState;
	vorbis_block		mVorbisBlock;

	ogg_packet			mWorkPacket;

	IStreamWriterRef	mStreamWriter;

private:
	_ubool DecodeBuffer( _dword size, const _byte* buffer );

public:
	OGGDecoder( );
	virtual ~OGGDecoder( );

public:
	_ubool Initialize( const SoundVorbisFormatInfo* info );

// IDecoder Interface
public:
	virtual _ubool					ProcessBuffer( _dword size, const _byte* buffer ) override;

	virtual _dword					GetProcessedBufferSize( ) const override;
	virtual const _byte*			GetProcessedBufferData( ) const override;
	virtual IStreamReaderPassRef	GetProcessedStreamReader( ) const override;

// IMediaDecoder Interface
public:
	virtual _ubool					ProcessBlockEntry( const IMediaFileBlockEntry* block_entry ) override;
};

}
