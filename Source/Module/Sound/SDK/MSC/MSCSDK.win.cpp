//! @file     MSCSDK.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// MSCSDK Helpful Functions Implementation
//----------------------------------------------------------------------------

_int ToMSCAudioSampleStatus( MSCSDK::_AUDIO_SAMPLE_STATUS status )
{
	switch ( status )
	{
		case MSCSDK::_AUDIO_SAMPLE_INIT:		return MSP_AUDIO_SAMPLE_INIT;
		case MSCSDK::_AUDIO_SAMPLE_FIRST:		return MSP_AUDIO_SAMPLE_FIRST;
		case MSCSDK::_AUDIO_SAMPLE_CONTINUE:	return MSP_AUDIO_SAMPLE_CONTINUE;
		case MSCSDK::_AUDIO_SAMPLE_LAST:		return MSP_AUDIO_SAMPLE_LAST;
		default:
			return 0;
	}
}

MSCSDK::_AUDIO_SAMPLE_STATUS ToAudioSampleStatus( _int status )
{
	switch ( status )
	{
		case MSP_AUDIO_SAMPLE_INIT:		return MSCSDK::_AUDIO_SAMPLE_INIT;
		case MSP_AUDIO_SAMPLE_FIRST:	return MSCSDK::_AUDIO_SAMPLE_FIRST;
		case MSP_AUDIO_SAMPLE_CONTINUE:	return MSCSDK::_AUDIO_SAMPLE_CONTINUE;
		case MSP_AUDIO_SAMPLE_LAST:		return MSCSDK::_AUDIO_SAMPLE_LAST;
		default:
			return MSCSDK::_AUDIO_SAMPLE_INIT;
	}
}

_int ToMSCEPStatus( MSCSDK::_ENDPOINT_STATUS status )
{
	switch ( status )
	{
		case MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH: return MSP_EP_LOOKING_FOR_SPEECH;
		case MSCSDK::_EP_STATUS_AFTER_SPEECH:		return MSP_EP_AFTER_SPEECH;
		default:
			return 0;
	}
}

MSCSDK::_ENDPOINT_STATUS ToEPStatus( _int status )
{
	switch ( status )
	{
		case MSP_EP_LOOKING_FOR_SPEECH: return MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH;
		case MSP_EP_AFTER_SPEECH:		return MSCSDK::_EP_STATUS_AFTER_SPEECH;
		default:
			return MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH;
	}
}

_int ToMSCRECStatus( MSCSDK::_REC_STATUS status )
{
	switch ( status )
	{
		case MSCSDK::_REC_STATUS_SUCCESS:	return MSP_REC_STATUS_SUCCESS;
		case MSCSDK::_REC_STATUS_COMPLETE:	return MSP_REC_STATUS_COMPLETE;
		default:
			return 0;
	}
}

MSCSDK::_REC_STATUS ToRECStatus( _int status )
{
	switch ( status )
	{
		case MSP_REC_STATUS_SUCCESS:	return MSCSDK::_REC_STATUS_SUCCESS;
		case MSP_REC_STATUS_COMPLETE:	return MSCSDK::_REC_STATUS_COMPLETE;
		default:
			return MSCSDK::_REC_STATUS_SUCCESS;
	}
}

_int ToMSCTTSStatus( MSCSDK::_TTS_FLAG flag )
{
	switch ( flag )
	{
		case MSCSDK::_TTS_FLAG_STILL_HAVE_DATA:	return MSP_TTS_FLAG_STILL_HAVE_DATA;
		case MSCSDK::_TTS_FLAG_DATA_END:		return MSP_TTS_FLAG_DATA_END;
		default:
			return 0;
	}
}

MSCSDK::_TTS_FLAG ToTTSStatus( _int flag )
{
	switch ( flag )
	{
		case MSP_TTS_FLAG_STILL_HAVE_DATA:	return MSCSDK::_TTS_FLAG_STILL_HAVE_DATA;
		case MSP_TTS_FLAG_DATA_END:			return MSCSDK::_TTS_FLAG_DATA_END;
		default:
			return MSCSDK::_TTS_FLAG_STILL_HAVE_DATA;
	}
}

//----------------------------------------------------------------------------
// MSCSDK Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( MSCSDK )
	// The MSC library
	Library mMSCLibrary;

	// The MSC functions
	#define FUNC_DECL( n ) Proc_##n m##n##Func
	// MSP
	FUNC_DECL( MSPLogin );
	FUNC_DECL( MSPLogout );
	// QISR
	FUNC_DECL( QISRSessionBegin );
	FUNC_DECL( QISRSessionEnd );
	FUNC_DECL( QISRAudioWrite );
	FUNC_DECL( QISRGetResult );
	// QTTS, Text To Speech
	FUNC_DECL( QTTSSessionBegin );
	FUNC_DECL( QTTSSessionEnd );
	FUNC_DECL( QTTSTextPut );
	FUNC_DECL( QTTSAudioGet );

	// The MSC function
	#define MSC_FUNC( n ) INTERNAL_HANDLER( )->m##n##Func
INTERNAL_HANDLER_IMPL_END( )

//----------------------------------------------------------------------------
// MSCSDK Implementation
//----------------------------------------------------------------------------

MSCSDK::MSCSDK( )
{
	INTERNAL_HANDLER_CREATE( );
}

MSCSDK::~MSCSDK( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool MSCSDK::Load( )
{
	if ( INTERNAL_HANDLER( )->mMSCLibrary.IsLoaded( ) == _false && INTERNAL_HANDLER( )->mMSCLibrary.Load( L"msc.dll" ) == _false )
		return _false;

	#define GET_FUNC( n ) \
		INTERNAL_HANDLER( )->m##n##Func = (Proc_##n) INTERNAL_HANDLER( )->mMSCLibrary.GetFunction( #n ); \
		if ( INTERNAL_HANDLER( )->m##n##Func == _null ) \
			return _false

	// MSP
	GET_FUNC( MSPLogin );
	GET_FUNC( MSPLogout );
	// QISR
	GET_FUNC( QISRSessionBegin );
	GET_FUNC( QISRSessionEnd );
	GET_FUNC( QISRAudioWrite );
	GET_FUNC( QISRGetResult );
	// QTTS, Text To Speech
	GET_FUNC( QTTSSessionBegin );
	GET_FUNC( QTTSSessionEnd );
	GET_FUNC( QTTSTextPut );
	GET_FUNC( QTTSAudioGet );

	return _true;
}

_void MSCSDK::Unload( )
{
	INTERNAL_HANDLER( )->mMSCLibrary.Free( );
}

_ubool MSCSDK::MSP_Login( WStringPtr login_params )
{
	_int ret = MSC_FUNC( MSPLogin )( _null, _null, AString( ).FromString( login_params ).Str( ) );
	if ( ret != MSP_SUCCESS )
		return _false;

	return _true;
}

_void MSCSDK::MSP_Logout( )
{
	MSC_FUNC( MSPLogout )( );
}

AString MSCSDK::QISR_SessionBegin( const SoundRecognizerAudioInfo& audio_info )
{
	AString params = FORMAT_ASTRING_3( "sub = iat, domain = iat, language = %s, accent = %s, sample_rate = %d, result_type = plain, result_encoding = gb2312", 
		audio_info.mLanguage.Str( ), audio_info.mAccent.Str( ), audio_info.mSampleRate );

	_int err_code = MSP_SUCCESS;
	AString session_id = MSC_FUNC( QISRSessionBegin )( _null, params.Str( ), &err_code );
	if ( MSP_SUCCESS != err_code )
	{
		ALOG_ERROR_1( "QISRSessionBegin failed! error code:%d", err_code );
		return AString( "" );
	}

	return session_id;
}

_void MSCSDK::QISR_SessionEnd( AStringPtr session_id )
{
	MSC_FUNC( QISRSessionEnd )( session_id.Str( ), "" );
}

_ubool MSCSDK::QISR_AudioWrite( AStringPtr session_id, const _byte* buffer, _dword size, _AUDIO_SAMPLE_STATUS audio_status, _ENDPOINT_STATUS& ep_stat, _REC_STATUS& rec_stat )
{
	_int msc_audio_sample_status	= ToMSCAudioSampleStatus( audio_status );
	_int msc_ep_stat				= ToMSCEPStatus( ep_stat );
	_int msc_rec_stat				= ToMSCRECStatus( rec_stat );

	_int ret = MSC_FUNC( QISRAudioWrite )( session_id.Str( ), buffer, size, msc_audio_sample_status, &msc_ep_stat, &msc_rec_stat );
	if ( ret != MSP_SUCCESS )
		return _false;

	audio_status	= ToAudioSampleStatus( msc_audio_sample_status );
	ep_stat			= ToEPStatus( msc_ep_stat );
	rec_stat		= ToRECStatus( msc_rec_stat );

	return _true;
}

_ubool MSCSDK::QISR_GetResult( AStringPtr session_id, _REC_STATUS& rec_stat, _int wait_time, WString& string )
{
	_int msc_rec_stat = ToMSCRECStatus( rec_stat );

	int err_code = 0;
	const _chara* result_string = MSC_FUNC( QISRGetResult )( session_id.Str( ), &msc_rec_stat, wait_time, &err_code );
	if ( err_code != MSP_SUCCESS )
		return _false;

	string.FromString( _ENCODING_ANSI, result_string );

	rec_stat = ToRECStatus( msc_rec_stat );

	return _true;
}

AString MSCSDK::QTTS_SessionBegin( const SoundRecognizerText2PCMInfo& config )
{
	// Build session parameters
	AString params = FORMAT_ASTRING_5( "voice_name = %s, text_encoding = gb2312, sample_rate = %d, speed = %d, volume = %d, pitch = %d, rdn = 2",
		config.mVoiceName.Str( ), config.mSampleRate, config.mSpeed, config.mVolume, config.mPitch );

	// Create session
	_int err_code = 0;
	AString session_id = MSC_FUNC( QTTSSessionBegin )( params.Str( ), &err_code );
	if ( err_code != MSP_SUCCESS )
		return AString( "" );

	return session_id;
}

_void MSCSDK::QTTS_SessionEnd( AStringPtr session_id )
{
	MSC_FUNC( QTTSSessionEnd )( session_id.Str( ), "" );
}

_ubool MSCSDK::QTTS_TextPut( AStringPtr session_id, WStringPtr string )
{
	AString string_ansi = AString( ).FromString( string );

	_int ret = MSC_FUNC( QTTSTextPut )( session_id.Str( ), string_ansi.Str( ), string_ansi.GetLength( ), _null );
	if ( ret != MSP_SUCCESS )
		return _false;

	return _true;
}

_ubool MSCSDK::QTTS_AudioGet( AStringPtr session_id, const _byte*& buffer, _dword& size, _TTS_FLAG& synth_status )
{
	_int msc_synth_status = ToMSCTTSStatus( synth_status );

	int err_code = 0;
	buffer = (const _byte*)MSC_FUNC( QTTSAudioGet )( session_id.Str( ), &size, &msc_synth_status, &err_code );
	if ( MSP_SUCCESS != err_code )
		return _false;

	synth_status = ToTTSStatus( msc_synth_status );

	return _true;
}
