//! @file     FLACFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

#ifndef _EGE_DISABLE_FLAC_FILE_

namespace EGE
{

//----------------------------------------------------------------------------
// FLACFile
//----------------------------------------------------------------------------

class FLACFile : public INTERFACE_SOUNDFILE_IMPL( IFLACFile )
{
private:
	typedef INTERFACE_SOUNDFILE_IMPL( IFLACFile ) BaseClass;

private:

private:
	//!	The FLAC buffer stream
	IStreamReaderRef		mStreamReader;

	//!	True indicates we are ready to decode
	_ubool					mIsReady;
	//!	The last error ID
	_dword					mLastErrID;
	//!	The bits per samples
	_dword					mBitsPerSamples;
	//!	The current position in samples
	_qword					mCurrentPosInSamples;
	//!	The total samples
	_qword					mTotalSamples;
	//!	The total size in bytes
	_dword					mTotalSize;
	//!	The block samples in bytes
	_dword					mBlockSamplesInBytes;
	//!	The block samples allocated size in bytes
	_dword					mBlockSamplesBufferSize;
	//!	The block samples allocated data
	_byte*					mBlockSamplesBufferData;
	//!	The block samples allocated buffer pointer
	_byte*					mBlockSamplesBufferDataPtr;
	//!	The stream decoder
	FLAC__StreamDecoder*	mDecoder;

private:
	//!	The FLAC decoder ID3 tags callback functions
	static size_t OnIOCallback_Read( void *ptr, size_t size, size_t nmemb, FLAC__IOHandle handle );
	static int OnIOCallback_Seek( FLAC__IOHandle handle, FLAC__int64 offset, int whence );
	static FLAC__int64 OnIOCallback_Tell( FLAC__IOHandle handle );

	//!	The FLAC decoder callback functions
	static FLAC__StreamDecoderReadStatus OnStreamDecoderReadCallback( const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data );
	static FLAC__StreamDecoderSeekStatus OnStreamDecoderSeekCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 absolute_byte_offset, void *client_data );
	static FLAC__StreamDecoderTellStatus OnStreamDecoderTellCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data );
	static FLAC__StreamDecoderLengthStatus OnStreamDecoderLengthCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 *stream_length, void *client_data );
	static FLAC__bool OnStreamDecoderEofCallback( const FLAC__StreamDecoder *decoder, void *client_data );
	static FLAC__StreamDecoderWriteStatus OnStreamDecoderWriteCallback( const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data );
	static void OnStreamDecoderMetadataCallback( const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data );
	static void OnStreamDecoderErrorCallback( const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data );

private:
	//!	Get ID3 tags info.
	_ubool GetID3TagsInfo( );

public:
	FLACFile( );
	virtual ~FLACFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IBinaryFile Interface
public:

// ISoundFile Interface
public:
	virtual _double			TimeSeek( _SEEK flag, _double time ) override;
	virtual _double			GetCurTime( ) const override;

	virtual _dword			Decode( _byte* buffer, _dword size ) override;

// IFLACFile Interface
public:
};

}

#endif