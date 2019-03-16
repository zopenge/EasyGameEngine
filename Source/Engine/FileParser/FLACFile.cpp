//! @file     FLACFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_FLAC_FILE_

//----------------------------------------------------------------------------
// FLACFile Global Variables Implementation
//----------------------------------------------------------------------------

enum _FLAC_DECODER
{
	_FLAC_DECODER_NO_ERROR = 0,
	_FLAC_DECODER_FILE_OPEN_ERROR,
	_FLAC_DECODER_FILE_SEEK_POSITION_OUT_OF_BOUNDS,
	_FLAC_DECODER_FILESIZE_OUT_OF_BOUNDS,
	_FLAC_DECODER_NOT_VALID_FLAC_STREAM,
	_FLAC_DECODER_UNSUPPORTED_SAMPLERATE,
	_FLAC_DECODER_UNSUPPORTED_CHANNEL_NUMBER,
	_FLAC_DECODER_UNSUPPORTED_BIT_PER_SAMPLE,
	_FLAC_DECODER_MEMORY_ALLOCATION_FAIL,
	_FLAC_DECODER_NO_ID3_DATA,
	_FLAC_DECODER_SEEK_NOT_SUPPORTED_MANAGED,
	_FLAC_DECODER_SEEK_POSITION_OUT_OF_BOUNDS,
	_FLAC_DECODER_REVERSE_NOT_SUPPORTED_MANAGED,
	_FLAC_DECODER_FAIL_INITIALIZATION,

	_FLAC_DECODER_FUNCTION_NOT_SUPPORTED,
	_FLAC_DECODER_UNKNOWN_ERROR,

	_FLAC_DECODER_MAX_NUMBER
};

WStringPtr cFLACErrStringTable[_FLAC_DECODER_MAX_NUMBER] = 
{
	L"No error.",
	L"FLACDecoder: File open error.",
	L"FLACDecoder: File seek position is out of bounds.",
	L"FLACDecoder: File size is out of bounds.",
	L"FLACDecoder: This is not valid FLAC stream.",
	L"FLACDecoder: Unsupported sample rate.",
	L"FLACDecoder: Unsupported channel number.",
	L"FLACDecoder: Unsupported bits per sample.",
	L"FLACDecoder: Memory allocation fail."
	L"FLACDecoder: No ID3 data.",
	L"FLACDecoder: Seek is not supported on managed stream.",
	L"FLACDecoder: Seek position is out of bounds.",
	L"FLACDecoder: Reverse mod is not supported on managed stream.",
	L"FLACDecoder: Decoder initialization fail.",

	L"FLACDecoder: Function not supported.",
	L"FLACDecoder: Unknown error."
};

//----------------------------------------------------------------------------
// FLACFile Implementation
//----------------------------------------------------------------------------

FLACFile::FLACFile( )
{
	mIsReady					= _false;
	mLastErrID					= _FLAC_DECODER_NO_ERROR;
	mBitsPerSamples				= 0;
	mCurrentPosInSamples		= 0;
	mTotalSamples				= 0;
	mTotalSize					= 0;
	mBlockSamplesInBytes		= 0;
	mBlockSamplesBufferSize		= 0;
	mBlockSamplesBufferData		= _null;
	mBlockSamplesBufferDataPtr	= _null;

	mDecoder = ::FLAC__stream_decoder_new( );
	EGE_ASSERT( mDecoder != _null );

	::FLAC__stream_decoder_set_md5_checking( mDecoder, _true );
	::FLAC__stream_decoder_init_stream( mDecoder, 
		OnStreamDecoderReadCallback,
		OnStreamDecoderSeekCallback,
		OnStreamDecoderTellCallback,
		OnStreamDecoderLengthCallback,
		OnStreamDecoderEofCallback,
		OnStreamDecoderWriteCallback,
		OnStreamDecoderMetadataCallback,
		OnStreamDecoderErrorCallback,
		this );
}

FLACFile::~FLACFile( )
{
	if ( mDecoder != _null )
	{
		if ( mIsReady )
			::FLAC__stream_decoder_finish( mDecoder );

		::FLAC__stream_decoder_delete( mDecoder );
	}

	EGE_DELETE_ARRAY( mBlockSamplesBufferData );
}

size_t FLACFile::OnIOCallback_Read( void *ptr, size_t size, size_t nmemb, FLAC__IOHandle handle )
{
	FLACFile* flac_file = (FLACFile*) handle;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	if ( stream_reader->ReachEnd( ) )
		return 0; // end of stream data

	_dword data_size = size * nmemb;
	_dword read_size = stream_reader->ReadBuffer( ptr, data_size );

	return read_size; 
}

int FLACFile::OnIOCallback_Seek( FLAC__IOHandle handle, FLAC__int64 offset, int whence )
{
	FLACFile* flac_file = (FLACFile*) handle;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	switch ( whence )
	{
		// SEEK_SET	
		case 0: stream_reader->Seek( _SEEK_BEGIN, (_dword)offset ); return 0;
		// SEEK_CUR
		case 1: stream_reader->Seek( _SEEK_CURRENT, (_dword)offset ); return 0;
		// SEEK_END
		case 2: stream_reader->Seek( _SEEK_END, (_dword)offset ); return 0;
		default:
			break;
	}

	return -1;
}

FLAC__int64 FLACFile::OnIOCallback_Tell( FLAC__IOHandle handle )
{
	FLACFile* flac_file = (FLACFile*) handle;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	_dword offset = stream_reader->GetOffset( );
	return offset;
}

FLAC__StreamDecoderReadStatus FLACFile::OnStreamDecoderReadCallback( const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	if ( *bytes > 0 )
	{
		if ( stream_reader->ReachEnd( ) )
		{
			*bytes = 0;
			return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
		}

		_dword read_size = stream_reader->ReadBuffer( buffer, *bytes );
		*bytes = read_size;

		return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
	}

	return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
}

FLAC__StreamDecoderSeekStatus FLACFile::OnStreamDecoderSeekCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 absolute_byte_offset, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	stream_reader->Seek( _SEEK_BEGIN, (_dword)absolute_byte_offset );

	return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
}

FLAC__StreamDecoderTellStatus FLACFile::OnStreamDecoderTellCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	*absolute_byte_offset = stream_reader->GetOffset( );

	return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}

FLAC__StreamDecoderLengthStatus FLACFile::OnStreamDecoderLengthCallback( const FLAC__StreamDecoder *decoder, FLAC__uint64 *stream_length, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	*stream_length = flac_file->mTotalSize;

	return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
}

FLAC__bool FLACFile::OnStreamDecoderEofCallback( const FLAC__StreamDecoder *decoder, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	IStreamReader* stream_reader = flac_file->mStreamReader;
	EGE_ASSERT( stream_reader != _null );

	if ( stream_reader->ReachEnd( ) )
		return _true;

	return _false;
}

FLAC__StreamDecoderWriteStatus FLACFile::OnStreamDecoderWriteCallback( const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	// Check bits per samples
	if ( flac_file->mBitsPerSamples != frame->header.bits_per_sample )
		return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE; // skip this frame	

	// Check sample rate
	if ( flac_file->mHeaderInfo.mSampleRate != frame->header.sample_rate )
		return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE; // skip this frame	

	// Check channels
	if ( flac_file->mHeaderInfo.mChannels != frame->header.channels )
		return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE; // skip this frame	

	// Calculate number of bytes from decoder
	_dword block_alloc_size = frame->header.blocksize * 4; // always use 16 bit stereo

	// Reallocate block samples buffer
	if ( block_alloc_size > flac_file->mBlockSamplesBufferSize ) 
	{
		EGE_DELETE_ARRAY( flac_file->mBlockSamplesBufferData );

		flac_file->mBlockSamplesBufferData = new _byte[ block_alloc_size ];
		if ( flac_file->mBlockSamplesBufferData == _null )
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;

		flac_file->mBlockSamplesBufferSize = block_alloc_size;
	}

	// Detect if stereo or mono
	_dword right = 0;
	switch ( frame->header.channels )
	{
		// mono
		case 1:	right = 0; break;
		// stereo
		case 2:	right = 1; break;	
		default:
			// multiple channels are not supported
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT; 
	}

	// Initialize block samples buffer
	switch ( frame->header.bits_per_sample )
	{
		case 8:
		{
			short *sample = (short*) flac_file->mBlockSamplesBufferData;
			for( _dword i = 0, j = 0; i < frame->header.blocksize; i ++, j += 2 )
			{
				sample[j]		= buffer[0][i] << 8;
				sample[j + 1]	= buffer[right][i] << 8;
			}
		}
		break;

		case 16:
		{
			short *sample = (short*) flac_file->mBlockSamplesBufferData;
			for( _dword i = 0, j = 0; i < frame->header.blocksize; i ++, j += 2 )
			{
				sample[j]		= buffer[0][i];
				sample[j + 1]	= buffer[right][i];
			}
		}
		break;

		case 24:
		{
			short *sample = (short*) flac_file->mBlockSamplesBufferData;
			for( _dword i = 0, j = 0; i < frame->header.blocksize; i ++, j += 2 )
			{
				sample[j]		= buffer[0][i] >> 8;
				sample[j + 1]	= buffer[right][i] >> 8;
			}
		}
		break;

		default:
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}

	flac_file->mBlockSamplesInBytes			= frame->header.blocksize * 4;
	flac_file->mBlockSamplesBufferDataPtr	= flac_file->mBlockSamplesBufferData;

	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void FLACFile::OnStreamDecoderMetadataCallback( const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );

	flac_file->mIsReady = _false;

	if ( metadata->type == FLAC__METADATA_TYPE_STREAMINFO )
	{
		flac_file->mHeaderInfo.mSampleRate = metadata->data.stream_info.sample_rate;
		if ( flac_file->mHeaderInfo.mSampleRate == 0)
		{
			flac_file->mLastErrID = _FLAC_DECODER_UNSUPPORTED_SAMPLERATE;
			return;
		}

		flac_file->mHeaderInfo.mChannels = metadata->data.stream_info.channels;
		if ( flac_file->mHeaderInfo.mChannels == 0 || flac_file->mHeaderInfo.mChannels > 2 )
		{
			flac_file->mLastErrID = _FLAC_DECODER_UNSUPPORTED_CHANNEL_NUMBER;
			return;
		}

		flac_file->mBitsPerSamples = metadata->data.stream_info.bits_per_sample;
		switch ( flac_file->mHeaderInfo.mChannels )
		{
			case 1:
			{
				if ( flac_file->mBitsPerSamples == 8 )
				{
					flac_file->mHeaderInfo.mFormat = _AF_MONO8;
				}
				else if ( flac_file->mBitsPerSamples == 16 )
				{
					flac_file->mHeaderInfo.mFormat = _AF_MONO16;
				}
				else
				{
					flac_file->mLastErrID = _FLAC_DECODER_UNSUPPORTED_BIT_PER_SAMPLE;
					return;
				}
			}
			break;

			case 2:
			{
				if ( flac_file->mBitsPerSamples == 8 )
				{
					flac_file->mHeaderInfo.mFormat = _AF_STEREO8;
				}
				else if ( flac_file->mBitsPerSamples == 16 )
				{
					flac_file->mHeaderInfo.mFormat = _AF_STEREO16;
				}
				else
				{
					flac_file->mLastErrID = _FLAC_DECODER_UNSUPPORTED_BIT_PER_SAMPLE;
					return;
				}
			}
			break;

			default:
				break;
		}

		flac_file->mTotalSamples		= metadata->data.stream_info.total_samples;
		flac_file->mHeaderInfo.mLength	= EGE_RATIO_DOUBLE( flac_file->mTotalSamples, flac_file->mHeaderInfo.mSampleRate );

		flac_file->mIsReady = _true;
	}
}

void FLACFile::OnStreamDecoderErrorCallback( const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data )
{
	FLACFile* flac_file = (FLACFile*) client_data;
	EGE_ASSERT( flac_file != _null );


}

_ubool FLACFile::GetID3TagsInfo( )
{
	FLAC__Metadata_Chain* chain = ::FLAC__metadata_chain_new( ); 
	if ( chain == _null )
		return _false;

	FLAC__IOCallbacks io_callbacks = {0};
	io_callbacks.read = OnIOCallback_Read;
	io_callbacks.seek = OnIOCallback_Seek;
	io_callbacks.tell = OnIOCallback_Tell;
	if ( !::FLAC__metadata_chain_read_with_callbacks( chain, this, io_callbacks ) )
	{
		FLAC__metadata_chain_delete( chain );
		return _false;
	}

	FLAC__Metadata_Iterator* meta_data_it = ::FLAC__metadata_iterator_new( ); 
	::FLAC__metadata_iterator_init( meta_data_it, chain );

	FLAC__StreamMetadata* data			= _null;
	FLAC__StreamMetadata* tags			= _null;
	FLAC__StreamMetadata* picture_block = _null;

	do
	{	
		data = ::FLAC__metadata_iterator_get_block( meta_data_it);
		if ( data->type == FLAC__METADATA_TYPE_VORBIS_COMMENT )
		{
			tags = data;
			if ( picture_block != _null )
				break;

		}
		else if( data->type == FLAC__METADATA_TYPE_PICTURE )
		{
			picture_block = data;
			if ( tags != _null )
				break;
		}
	}
	while ( ::FLAC__metadata_iterator_next( meta_data_it ) );

	if ( picture_block != _null )
	{
		FLAC__StreamMetadata_Picture picture = picture_block->data.picture; 

		mID3TagsInfo.mPictureMime.FromString( _ENCODING_ANSI, picture.mime_type );
		mID3TagsInfo.mPictureDescription.FromString( _ENCODING_UTF8, picture.description );
		mID3TagsInfo.mPictureType		= picture.type;
		mID3TagsInfo.mPictureDataSize	= picture.data_length;
		mID3TagsInfo.mPictureData		= new _byte[ mID3TagsInfo.mPictureDataSize ];
		EGE_MEM_CPY( mID3TagsInfo.mPictureData, picture.data, mID3TagsInfo.mPictureDataSize );
	}

	if ( tags != _null )
	{
		struct ID3Table
		{
			AStringPtr	mKey;
			_dword		mOffset; 
		};

		const _dword cOggTableSize = 16;
		static ID3Table cOggTable[ cOggTableSize ] = 
		{
			"TITLE=",		EGE_OFFSET_OF( SoundID3TagsInfo, mTitle ), 
			"ARTIST=",		EGE_OFFSET_OF( SoundID3TagsInfo, mArtist ), 
			"ALBUM=",		EGE_OFFSET_OF( SoundID3TagsInfo, mAlbum ), 
			"GENRE=",		EGE_OFFSET_OF( SoundID3TagsInfo, mGenre ), 
			"COMMENT=",		EGE_OFFSET_OF( SoundID3TagsInfo, mComment ), 
			"DESCRIPTION=", EGE_OFFSET_OF( SoundID3TagsInfo, mComment ), 
			"DATE=",		EGE_OFFSET_OF( SoundID3TagsInfo, mYear ), 
			"TRACKNUMBER=", EGE_OFFSET_OF( SoundID3TagsInfo, mTrack ), 

			"BAND=",		EGE_OFFSET_OF( SoundID3TagsInfo, mAlbumArtist ), 
			"COMPOSER=",	EGE_OFFSET_OF( SoundID3TagsInfo, mComposer ), 
			"ORIGARTIST=",	EGE_OFFSET_OF( SoundID3TagsInfo, mOriginalArtist ), 
			"COPYRIGHT=",	EGE_OFFSET_OF( SoundID3TagsInfo, mCopyright ), 
			"LOCATION=",	EGE_OFFSET_OF( SoundID3TagsInfo, mUrl ), 
			"ENCODER=",		EGE_OFFSET_OF( SoundID3TagsInfo, mEncoder ), 
			"PUBLISHER=",	EGE_OFFSET_OF( SoundID3TagsInfo, mPublisher ), 
			"BPM=",			EGE_OFFSET_OF( SoundID3TagsInfo, mBpm ), 
		};

		for ( _dword i = 0; i < tags->data.vorbis_comment.num_comments; i ++ )
		{
			for ( _dword j = 0; j < cOggTableSize; j ++ )
			{
				AStringPtr key = (const _chara*)tags->data.vorbis_comment.comments[i].entry;
				if ( key.StartsWith( cOggTable[j].mKey ) == _false )
					continue;

				const _chara*	content			= key.SubString( cOggTable[j].mKey.GetLength( ) ).Str( );
				WString&		tags_content	= (WString&)((_byte*)&mID3TagsInfo)[ cOggTable[j].mOffset ];
				tags_content.FromString( _ENCODING_UTF8, content );
				break;
			}
		}
	}

	::FLAC__metadata_iterator_delete( meta_data_it );
	::FLAC__metadata_chain_delete( chain );

	return _true;
}

_FILE_FORMAT FLACFile::GetFileID( ) const
{
	return _FF_FLAC;
}

_ubool FLACFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Clone the stream reader
	mStreamReader = stream_reader->CloneToPassRef< IStreamReader >( _true );
	if ( mStreamReader.IsNull( ) )
		return _false;

	// Update info
	mTotalSize = mStreamReader->GetSize( );
	if ( mTotalSize == 0 )
		return _false;

	// Get the ID3 tags info
	if ( GetID3TagsInfo( ) == _false )
		return _false;

	// Seek to begin
	mStreamReader->Seek( _SEEK_BEGIN, 0 );

	// Decode metadata
	if ( !::FLAC__stream_decoder_process_until_end_of_metadata( mDecoder ) )
		return _false;

	return _true;
}

_void FLACFile::Unload( )
{
	BaseClass::Unload( );
}

_double FLACFile::TimeSeek( _SEEK flag, _double time )
{
	if ( mIsReady == _false )
		return 0.0;

	// Change time to offset in samples
	_dword offset_in_samples = (_dword)( time * (_double) mHeaderInfo.mSampleRate );

	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
			mCurrentPosInSamples = offset_in_samples;
		}
		break;

		case _SEEK_CURRENT:
		{
			mCurrentPosInSamples += offset_in_samples;
		}
		break;

		case _SEEK_END:
		{
			mCurrentPosInSamples = mTotalSamples - offset_in_samples;
		}
		break;

		default:
			return -1.0;
	}

	if ( !::FLAC__stream_decoder_seek_absolute( mDecoder, mCurrentPosInSamples ) )
	{
		mLastErrID = _FLAC_DECODER_UNKNOWN_ERROR;
		return 0.0;
	}

	if ( ::FLAC__stream_decoder_get_state( mDecoder ) == FLAC__STREAM_DECODER_SEEK_ERROR )
	{
		if ( !::FLAC__stream_decoder_flush( mDecoder ) )
		{
			mLastErrID = _FLAC_DECODER_UNKNOWN_ERROR;
			return 0.0;
		}

		if ( !::FLAC__stream_decoder_reset( mDecoder ) )
		{
			mLastErrID = _FLAC_DECODER_UNKNOWN_ERROR;
			return 0.0;
		}
	}

	return EGE_RATIO_DOUBLE( mCurrentPosInSamples, mHeaderInfo.mSampleRate );
}

_double FLACFile::GetCurTime( ) const
{
	_double cur_time = EGE_RATIO_DOUBLE( mCurrentPosInSamples, mHeaderInfo.mSampleRate );
	return cur_time;
}

_dword FLACFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	// The processed size
	_dword processed_size = 0;

	// Start to decode
	while ( size > 0 )
	{
		// We have some data in buffer
		if ( mBlockSamplesInBytes )
		{
			// we have enough data
			if ( mBlockSamplesInBytes >= size ) 
			{
				EGE_MEM_CPY( buffer, mBlockSamplesBufferDataPtr, size );

				// Update processed size
				processed_size += size;

				// Move buffer pointer
				mBlockSamplesBufferDataPtr += size;

				// Update samples size
				mBlockSamplesInBytes -= size;
				break;
			}
			else
			{
				EGE_MEM_CPY( buffer, mBlockSamplesBufferDataPtr, mBlockSamplesInBytes );

				// Update processed size
				processed_size += mBlockSamplesInBytes;

				// Update buffer data and size
				size	-= mBlockSamplesInBytes;
				buffer	+= mBlockSamplesInBytes; // move user buffer to new position because we need more data

				// Buffer is empty
				mBlockSamplesBufferDataPtr = mBlockSamplesBufferData;
				mBlockSamplesInBytes = 0;
			}
		}
		else
		{
			// We need more data, so get data from decoder
			if ( !::FLAC__stream_decoder_process_single( mDecoder ) )
				return 0;

			if ( ::FLAC__stream_decoder_get_state( mDecoder ) == FLAC__STREAM_DECODER_END_OF_STREAM )
				break;
		}
	}

	// Update current position in samples
	EGE_ASSERT( processed_size % 4 == 0 );
	mCurrentPosInSamples += processed_size / 4;

	// Feedback decode size
	return processed_size;
}

#endif