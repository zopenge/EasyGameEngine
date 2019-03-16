//! @file     OGGFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// OGGFileWriter
//----------------------------------------------------------------------------

class OGGFileWriter : public TSoundFileWriter< ISoundFileWriter >
{
private:
	//!	True indicates has started
	_ubool				mHasStarted;

	_dword				mSampleBitSize;

	ogg_stream_state	mStreamState;
	ogg_page			mPage;
	ogg_packet			mPacket;

	vorbis_info			mInfo;
	vorbis_comment		mComment;

	vorbis_dsp_state	mDSPState;
	vorbis_block		mBlock;

	IStreamWriterRef	mStreamWriter;

private:
	_dword EncodePCM2OGG( IStreamReader* stream_reader );
	_void FlushPacket( );

public:
	OGGFileWriter( );
	virtual ~OGGFileWriter( );

public:
	//!	Initialize.
	_ubool Initialize( _dword channels, _dword sample_rate, _dword sample_bit_size );

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
// OGGFile
//----------------------------------------------------------------------------

class OGGFile : public INTERFACE_SOUNDFILE_IMPL( IOGGFile )
{
public:
	//!	The OGG file ID
	enum { _FILE_ID = EGE_ID( 'O', 'g', 'g', 'S' ) };

private:
	typedef INTERFACE_SOUNDFILE_IMPL( IOGGFile ) BaseClass;

private:
    //! The thread locker
    Lock                mLocker;
    
	//!	The OGG buffer stream
	IStreamReaderRef	mStreamReader;

	//!	The OGG file stream
	OggVorbis_File		mVorbisStream;
	//!	The OGG file info
	vorbis_info*		mVorbisInfo;
	//!	The OGG file comment
	vorbis_comment*		mVorbisComment;

private:
	//!	The OGG file stream IO callback functions.
	static size_t OnReadCallback( void* ptr, size_t size, size_t nmemb, void* datasource );
	static int    OnSeekCallback( void* datasource, ogg_int64_t offset, int whence );
	static int    OnCloseCallback( void* datasource );
	static long   OnTellCallback( void* datasource );

private:
	//!	Get the OGG error description by error ID.
	AStringPtr GetOggErrDesc( _int err_id ) const;

public:
	OGGFile( );
	virtual ~OGGFile( );

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

// IOGGFile Interface
public:
};

}