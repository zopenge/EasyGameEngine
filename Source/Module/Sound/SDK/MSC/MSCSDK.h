//! @file     MSCSDK.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MSCSDK
//----------------------------------------------------------------------------

class MSCSDK
{
	SINGLETON( MSCSDK )

private:
	INTERNAL_HANDLER_DECL( );

public:
	//!	The audio sample status
	enum _AUDIO_SAMPLE_STATUS
	{
		_AUDIO_SAMPLE_INIT,
		_AUDIO_SAMPLE_FIRST,
		_AUDIO_SAMPLE_CONTINUE,
		_AUDIO_SAMPLE_LAST,
	};

	//!	The current endpoint status
	enum _ENDPOINT_STATUS
	{
		_EP_STATUS_LOOKING_FOR_SPEECH,
		_EP_STATUS_AFTER_SPEECH,
	};

	//! The recognizer status
	enum _REC_STATUS
	{
		_REC_STATUS_SUCCESS,
		_REC_STATUS_COMPLETE,
	};

	//!	The (TTS, Text To Speech) flag
	enum _TTS_FLAG
	{
		_TTS_FLAG_STILL_HAVE_DATA,
		_TTS_FLAG_DATA_END,
	};

public:
	_ubool Load( );
	_void Unload( );

	_ubool MSP_Login( WStringPtr login_params );
	_void MSP_Logout( );

	AString QISR_SessionBegin( const SoundRecognizerAudioInfo& audio_info );
	_void QISR_SessionEnd( AStringPtr session_id );
	_ubool QISR_AudioWrite( AStringPtr session_id, const _byte* buffer, _dword size, _AUDIO_SAMPLE_STATUS audio_status, _ENDPOINT_STATUS& ep_stat, _REC_STATUS& rec_stat );
	_ubool QISR_GetResult( AStringPtr session_id, _REC_STATUS& rec_stat, _int wait_time, WString& string );

	AString QTTS_SessionBegin( const SoundRecognizerText2PCMInfo& config );
	_void QTTS_SessionEnd( AStringPtr session_id );
	_ubool QTTS_TextPut( AStringPtr session_id, WStringPtr string );
	_ubool QTTS_AudioGet( AStringPtr session_id, const _byte*& buffer, _dword& size, _TTS_FLAG& synth_status );
};

//----------------------------------------------------------------------------
// MSCSDK Implementation
//----------------------------------------------------------------------------

}