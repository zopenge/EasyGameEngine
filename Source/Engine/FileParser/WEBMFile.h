//! @file     WEBMFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// WEBMMkvReader Implementation
//----------------------------------------------------------------------------

class WEBMMkvReader : public mkvparser::IMkvReader
{
private:
	IStreamReaderRef	mStreamReader;

public:
	WEBMMkvReader( IStreamReader* stream_reader );
	virtual ~WEBMMkvReader( );

// mkvparser::IMkvReader Interface
public:
	virtual int Read( long long pos, long len, unsigned char* buf ) override;
	virtual int Length( long long* total, long long* available ) override;
};

//----------------------------------------------------------------------------
// WEBMFileBlockEntry Implementation
//----------------------------------------------------------------------------

class WEBMFileBlockEntry : public TObject< IMediaFileBlockEntry >
{
private:
	const mkvparser::Track*			mTrack;
	const mkvparser::BlockEntry*	mCurBlockEntry;
	const mkvparser::BlockEntry*	mNextBlockEntry;
	const mkvparser::BlockEntry*	mStopBlockEntry;

	_qword							mBaseTimeNS;

private:
	_ubool InitCurBlock( );

public:
	WEBMFileBlockEntry( const mkvparser::Track* track );
	virtual ~WEBMFileBlockEntry( );

public:
	_void Reset( );

	_ubool BeginPopulateSample( );
	_void EndPopulateSample( );

// IMediaFileBlockEntry Interface
public:
	virtual _qword	GetCurTime( ) const override;
	virtual _qword	GetStopTime( ) const override;
	virtual _qword	GetDuration( _qword& start_reftime ) const override;

	virtual _dword	GetFrameNumber( ) const override;
	virtual _dword	GetFrameSizeByIndex( _dword index ) const override;
	virtual _dword	GetFrameDataByIndex( _dword index, _byte* buffer ) const override;
};

//----------------------------------------------------------------------------
// WEBMFileTrack Implementation
//----------------------------------------------------------------------------

class WEBMFileTrack : public TObject< IMediaFileTrack >
{
private:
	const mkvparser::Track*	mTrack;

	WEBMFileBlockEntry*		mBlockEntry;

public:
	WEBMFileTrack( const mkvparser::Track* track );
	virtual ~WEBMFileTrack( );

public:
	const mkvparser::Track*	GetMKVTrack( ) const;

// IMediaFileTrack Interface
public:
	virtual _MEDIA_TYPE	GetType( ) const override;
	virtual WStringR	GetName( ) const override;

	virtual WStringR	GetCodecName( ) const override;
	virtual WStringR	GetCodecID( ) const override;

	virtual _void		Reset( ) override;
	virtual _ubool		PopulateSample( IMediaFileNotifier* notifier ) override;
};

//----------------------------------------------------------------------------
// WEBMFileBaseTrack Implementation
//----------------------------------------------------------------------------

template< typename Type >
class WEBMFileBaseTrack : public TObject< Type >
{
protected:
	WEBMFileTrack*	mTrack;

protected:
	WEBMFileBaseTrack( WEBMFileTrack* track )
	{
		mTrack = track;
	}
	virtual ~WEBMFileBaseTrack( )
	{

	}

protected:
	//!	Get the MKV track
	template< typename TrackType >
	const TrackType* GetTrack( ) const
	{
		return static_cast<const TrackType*>(mTrack->GetMKVTrack( ));
	}

// IMediaFileTrack Interface
public:
	virtual _MEDIA_TYPE	GetType( ) const { return mTrack->GetType( ); }
	virtual WStringR	GetName( ) const { return mTrack->GetName( ); }

	virtual WStringR	GetCodecName( ) const { return mTrack->GetCodecName( ); }
	virtual WStringR	GetCodecID( ) const { return mTrack->GetCodecID( ); }

	virtual _void		Reset( ) { mTrack->Reset( ); }
	virtual _ubool		PopulateSample( IMediaFileNotifier* notifier ) { return mTrack->PopulateSample( notifier ); }
};

//----------------------------------------------------------------------------
// WEBMFileVideoTrack Implementation
//----------------------------------------------------------------------------

class WEBMFileVideoTrack : public WEBMFileBaseTrack< IMediaFileVideoTrack >
{
private:
	typedef WEBMFileBaseTrack< IMediaFileVideoTrack > BaseClass;

public:
	WEBMFileVideoTrack( WEBMFileTrack* track );
	virtual ~WEBMFileVideoTrack( );

// IMediaFileVideoTrack Interface
public:
	virtual _dword GetWidth( ) const override;
	virtual _dword GetHeight( ) const override;
	virtual _float GetFrameRate( ) const override;
};

//----------------------------------------------------------------------------
// WEBMFileAudioTrack Implementation
//----------------------------------------------------------------------------

class WEBMFileAudioTrack : public WEBMFileBaseTrack< IMediaFileAudioTrack >
{
private:
	typedef WEBMFileBaseTrack< IMediaFileAudioTrack > BaseClass;

private:
	SoundVorbisFormatInfo*	mVorbisFormatInfo;

private:
	//!	Build vorbis format info.
	_void BuildVorbisFormatInfo( );

public:
	WEBMFileAudioTrack( WEBMFileTrack* track );
	virtual ~WEBMFileAudioTrack( );

// IMediaFileAudioTrack Interface
public:
	virtual _AUDIO_FORMAT					GetFormat( ) const override;
	virtual _dword							GetChannels( ) const override;
	virtual _dword							GetSampleBitSize( ) const override;
	virtual _dword							GetSampleRate( ) const override;

	virtual const SoundVorbisFormatInfo*	GetVorbisFormatInfo( ) const override;
};

//----------------------------------------------------------------------------
// WEBMFile
//----------------------------------------------------------------------------

class WEBMFile : public INTERFACE_MEDIAFILE_IMPL( IWEBMFile )
{
private:
	typedef INTERFACE_MEDIAFILE_IMPL( IWEBMFile ) BaseClass;

public:
	//!	The WEBM file ID
	enum { _FILE_ID = EGE_ID( 0x1A, 0x45, 0xDF, 0xA3 ) };

private:
	typedef Array< WEBMFileTrack* > WEBMFileTrackArray;

private:
	WEBMFileTrackArray	mTracks;

	mkvparser::Segment*	mSegment;

	WEBMMkvReader*		mReader;

private:
	_ubool InitTracks( );

public:
	WEBMFile( );
	virtual ~WEBMFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT		GetFileID( ) const override;

	virtual _ubool 				LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 				Unload( ) override;

// IMediaFile Interface
public:
	virtual _dword				GetTrackNumber( ) const override;
	virtual IMediaFileTrack*	GetTrackByIndex( _dword index ) const override;

// IWEBMFile Interface
public:
};

}