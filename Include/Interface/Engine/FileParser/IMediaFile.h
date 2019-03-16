//! @file     IMediaFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{


//----------------------------------------------------------------------------
// IMediaFileBlockEntry
//----------------------------------------------------------------------------

class IMediaFileBlockEntry : public IObject
{
public:
	virtual _qword GetCurTime( ) const PURE;
	virtual _qword GetStopTime( ) const PURE;
	virtual _qword GetDuration( _qword& start_reftime ) const PURE;

	virtual _dword GetFrameNumber( ) const PURE;
	virtual _dword GetFrameSizeByIndex( _dword index ) const PURE;
	virtual _dword GetFrameDataByIndex( _dword index, _byte* buffer ) const PURE;
};

//----------------------------------------------------------------------------
// IMediaFileTrack
//----------------------------------------------------------------------------

class IMediaFileTrack : public IObject
{
public:
	virtual _MEDIA_TYPE GetType( ) const PURE;
	virtual WStringR GetName( ) const PURE;

	virtual WStringR GetCodecName( ) const PURE;
	virtual WStringR GetCodecID( ) const PURE;

	virtual _void Reset( ) PURE;
	virtual _ubool PopulateSample( IMediaFileNotifier* notifier ) PURE;
};

//----------------------------------------------------------------------------
// IMediaFileVideoTrack
//----------------------------------------------------------------------------

class IMediaFileVideoTrack : public IMediaFileTrack
{
public:
	virtual _dword GetWidth( ) const PURE;
	virtual _dword GetHeight( ) const PURE;
	virtual _float GetFrameRate( ) const PURE;
};

//----------------------------------------------------------------------------
// IMediaFileAudioTrack
//----------------------------------------------------------------------------

class IMediaFileAudioTrack : public IMediaFileTrack
{
public:
	virtual _AUDIO_FORMAT GetFormat( ) const PURE;
	virtual _dword GetChannels( ) const PURE;
	virtual _dword GetSampleBitSize( ) const PURE;
	virtual _dword GetSampleRate( ) const PURE;

	virtual const SoundVorbisFormatInfo* GetVorbisFormatInfo(  ) const PURE;
};

//----------------------------------------------------------------------------
// IMediaFileNotifier
//----------------------------------------------------------------------------

class IMediaFileNotifier : public IObject
{
public:
	virtual _void OnPopulateVideoSample( const IMediaFileVideoTrack* track, const IMediaFileBlockEntry* block_entry ) PURE;
	virtual _void OnPopulateAudioSample( const IMediaFileAudioTrack* track, const IMediaFileBlockEntry* block_entry ) PURE;
};

//----------------------------------------------------------------------------
// IMediaFile
//----------------------------------------------------------------------------

class IMediaFile : public IBaseFile
{
public:
	virtual _dword GetTrackNumber( ) const PURE;
	virtual IMediaFileTrack* GetTrackByIndex( _dword index ) const PURE;
};

}