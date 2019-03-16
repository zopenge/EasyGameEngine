//! @file     SoundRecognizer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundRecognizer
//----------------------------------------------------------------------------

class SoundRecognizer : public TObject< ISoundRecognizer >
{
private:
	MSCSDK::_ENDPOINT_STATUS		mEPStat;
	MSCSDK::_REC_STATUS				mRecStat;
	MSCSDK::_AUDIO_SAMPLE_STATUS	mAudioStatus;
	AString							mSessionID;

	SoundRecognizerAudioInfo		mAudioInfo;

private:
	_ubool StartQISRSession( );
	_void CloseQISRSession( );

	IWAVFilePassRef ConvertText2WAVFile( AStringPtr session_id, WStringPtr string, const SoundRecognizerText2PCMInfo& config );

public:
	SoundRecognizer( );
	virtual ~SoundRecognizer( );

// ISoundRecognizer Interface
public:
	virtual _ubool			Login( WStringPtr app_id ) override;
	virtual _ubool			Login( WStringPtr app_id, WStringPtr working_dir ) override;
	virtual _void			Logout( ) override;

	virtual _ubool			Start( const SoundRecognizerAudioInfo& audio_info ) override;
	virtual _ubool			Listen( _dword size, const _byte* buffer, WString& string ) override;
	virtual _void			Stop( WString& string ) override;

	virtual IWAVFilePassRef ConvertText2WAVFile( WStringPtr string, const SoundRecognizerText2PCMInfo& config ) override;
};

//----------------------------------------------------------------------------
// SoundRecognizer Implementation
//----------------------------------------------------------------------------

}