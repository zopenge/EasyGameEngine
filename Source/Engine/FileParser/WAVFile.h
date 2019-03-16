//! @file     WAVFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// WAVFile Helper Structure
//----------------------------------------------------------------------------

//!	See referenced website: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/

//!	The WAV desc header
struct WaveDescHeader
{
	_dword	mRIFF;
	_dword	mSize;
	_dword	mFormat;
};

//!	The WAV format header
struct WaveFormatHeader
{
	_dword	mID;
	_dword	mSize;
	_word	mAudioFormat;
	_word	mChannels;		// Mono = 1, Stereo = 2, etc.
	_dword	mSampleRate;	// 8000, 44100, etc.
	_dword	mByteRate;		// == mSampleRate * mChannels * mSampleBitSize/8
	_word	mBlockAlign;	// == NumChannels * BitsPerSample/8 (The number of bytes for one sample including all channels).
	_word	mSampleBitSize;	// 8 bits = 8, 16 bits = 16, etc.
};

//----------------------------------------------------------------------------
// WAVFileWriter
//----------------------------------------------------------------------------

class WAVFileWriter : public TSoundFileWriter< ISoundFileWriter >
{
private:
	//!	True indicates has started
	_ubool				mHasStarted;

	//!	The WAV description header
	WaveDescHeader		mWAVDescHeaader;
	//!	The WAV format header
	WaveFormatHeader	mWAVFormatHeader;

	//!	The WAV buffer stream to write
	IStreamWriterRef	mStreamWriter;

public:
	WAVFileWriter( );
	virtual ~WAVFileWriter( );

// IFileWriter Interface
public:
	virtual _ubool	LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _ubool	SaveToStream( IStreamWriter* stream_writer ) const override;

// ISoundFileWriter Interface
public:
	virtual _ubool	Start( _dword channels, _dword sample_rate, _dword sample_bit_size ) override;
	virtual _void	Stop( ) override;

	virtual _dword	Encode( const _byte* buffer, _dword size ) override;
};

//----------------------------------------------------------------------------
// WAVFile
//----------------------------------------------------------------------------

class WAVFile : public INTERFACE_SOUNDFILE_IMPL( IWAVFile )
{
public:
	//!	The WAV file ID
	enum { _FILE_ID = EGE_ID( 'R', 'I', 'F', 'F' ) };

private:
	typedef INTERFACE_SOUNDFILE_IMPL( IWAVFile ) BaseClass;

private:
	//!	The data chunk info
	struct WaveDataChunkHeader
	{
		//!	The offset of PCM data buffer
		_dword	mOffsetOfPCM;
		//!	The offset in bytes of file
		_dword	mOffsetOfFile;
		//!	The chunk size
		_dword	mSize;

		//!	Use offset of PCM to sort.
		operator _dword( ) const
			{ return mOffsetOfPCM; }

		WaveDataChunkHeader( )
		{
			mOffsetOfPCM	= -1;
			mOffsetOfFile	= -1;
			mSize			= 0;
		}
		WaveDataChunkHeader( _dword offset_of_pcm, _dword offset_of_file, _dword size )
		{
			mOffsetOfPCM	= offset_of_pcm;
			mOffsetOfFile	= offset_of_file;
			mSize			= size;
		}
	};
	typedef Array< WaveDataChunkHeader > WaveDataChunkHeaderArray;

private:
	//!	The WAV buffer stream to read
	IStreamReaderRef			mStreamReader;

	//!	The WAV description header
	WaveDescHeader				mWAVDescHeaader;
	//!	The WAV format header
	WaveFormatHeader			mWAVFormatHeader;
	//!	The data chunks
	WaveDataChunkHeaderArray	mWAVDataChunks;

	//!	The current WAV PCM buffer data position in bytes
	_dword						mCurPCMBufferOffset;
	//!	The WAV PCM buffer size
	_dword						mPCMBufferSize;

private:
	//!	Syn header info.
	_void SynHeaderInfo( );

	//!	Build data chunks.
	_ubool BuildDataChunks( IStreamReader* stream_reader );

public:
	WAVFile( );
	virtual ~WAVFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

	virtual _ubool			SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IBinaryFile Interface
public:

// ISoundFile Interface
public:
	virtual _double			TimeSeek( _SEEK flag, _double time ) override;
	virtual _double			GetCurTime( ) const override;

	virtual _dword			Decode( _byte* buffer, _dword size ) override;

// IWAVFile Interface
public:
};

}