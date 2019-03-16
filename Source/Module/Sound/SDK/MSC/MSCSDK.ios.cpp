//! @file     MSCSDK.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// MSCSDK Implementation
//----------------------------------------------------------------------------

MSCSDK::MSCSDK( )
{
}

MSCSDK::~MSCSDK( )
{
}

_ubool MSCSDK::Load( )
{
	return _true;
}

_void MSCSDK::Unload( )
{
}

_ubool MSCSDK::MSP_Login( WStringPtr login_params )
{
	return _true;
}

_void MSCSDK::MSP_Logout( )
{
}

AString MSCSDK::QISR_SessionBegin( const SoundRecognizerAudioInfo& audio_info )
{
	AString session_id;
	return session_id;
}

_void MSCSDK::QISR_SessionEnd( AStringPtr session_id )
{
}

_ubool MSCSDK::QISR_AudioWrite( AStringPtr session_id, const _byte* buffer, _dword size, _AUDIO_SAMPLE_STATUS audio_status, _ENDPOINT_STATUS& ep_stat, _REC_STATUS& rec_stat )
{
	return _true;
}

_ubool MSCSDK::QISR_GetResult( AStringPtr session_id, _REC_STATUS& rec_stat, _int wait_time, WString& string )
{
	return _true;
}

AString MSCSDK::QTTS_SessionBegin( const SoundRecognizerText2PCMInfo& config )
{
	AString session_id;
	return session_id;
}

_void MSCSDK::QTTS_SessionEnd( AStringPtr session_id )
{
}

_ubool MSCSDK::QTTS_TextPut( AStringPtr session_id, WStringPtr string )
{
	return _true;
}

_ubool MSCSDK::QTTS_AudioGet( AStringPtr session_id, const _byte*& buffer, _dword& size, _TTS_FLAG& synth_status )
{
	return _true;
}
