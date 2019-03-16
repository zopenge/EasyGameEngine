//! @file     MSCSDK.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// MSCSDK Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( MSCSDK )
	//!	The MSC interface
	IInvokerRef	mMSC;
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
	// Create MSC interface
	INTERNAL_HANDLER( )->mMSC = GetPlatform( )->CreateJNIObject( EGE_OBFUSCATE_STR( "com/ege/android/AndroidMSC" ) );
	if ( INTERNAL_HANDLER( )->mMSC.IsNull( ) )
		return _false;

	INTERNAL_HANDLER( )->mMSC->CallVoidMethod( "init", "(J)V", (jlong)this );

	return _true;
}

_void MSCSDK::Unload( )
{
}

_ubool MSCSDK::MSP_Login( WStringPtr login_params )
{
	IC2JStringRef jparam = GetPlatform( )->CreateC2JString( login_params );
	INTERNAL_HANDLER( )->mMSC->CallVoidMethod( "login", "(Ljava/lang/String;)V", jparam->ToJString( ) );

	return _true;
}

_void MSCSDK::MSP_Logout( )
{
	INTERNAL_HANDLER( )->mMSC->CallVoidMethod( "logout", "()V" );
}

AString MSCSDK::QISR_SessionBegin( const SoundRecognizerAudioInfo& audio_info )
{
	IC2JStringRef language_param	= GetPlatform( )->CreateC2JString( audio_info.mLanguage );
	IC2JStringRef accent_param		= GetPlatform( )->CreateC2JString( audio_info.mAccent );
	jstring js_session = (jstring) INTERNAL_HANDLER( )->mMSC->CallObjectMethod( "QISRSessionBegin", 
		"(ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;", 
		audio_info.mSampleRate,
		language_param->ToJString( ),
		accent_param->ToJString( ) );

	return GetPlatform( )->ToStringA( js_session );
}

_void MSCSDK::QISR_SessionEnd( AStringPtr session_id )
{
	IC2JStringRef session_param = GetPlatform( )->CreateC2JString( session_id );
	INTERNAL_HANDLER( )->mMSC->CallVoidMethod( "QISRSessionEnd", "(Ljava/lang/String;)V", session_param->ToJString( ) );
}

_ubool MSCSDK::QISR_AudioWrite( AStringPtr session_id, const _byte* buffer, _dword size, _AUDIO_SAMPLE_STATUS audio_status, _ENDPOINT_STATUS& ep_stat, _REC_STATUS& rec_stat )
{
	IC2JStringRef	session_param	= GetPlatform( )->CreateC2JString( session_id );
	IC2JArrayRef	buffer_param	= GetPlatform( )->CreateC2JArray( size, buffer );
	_boolean		is_last			= audio_status == _AUDIO_SAMPLE_LAST;
	if ( INTERNAL_HANDLER( )->mMSC->CallBooleanMethod( "QISRAudioWrite", "(Ljava/lang/String;[BZ)Z", session_param->ToJString( ), buffer_param->ToJArray( ), audio_status, is_last ) == _false )
		return _false;

	ep_stat		= (_ENDPOINT_STATUS)INTERNAL_HANDLER( )->mMSC->CallIntMethod( "getQISRAudioWriteEPStatus", "(Ljava/lang/String;)I", session_param->ToJString( ) );
	rec_stat	= (_REC_STATUS)INTERNAL_HANDLER( )->mMSC->CallIntMethod( "getQISRAudioWriteRECStatus", "(Ljava/lang/String;)I", session_param->ToJString( ) );

	return _true;
}

_ubool MSCSDK::QISR_GetResult( AStringPtr session_id, _REC_STATUS& rec_stat, _int wait_time, WString& string )
{
	IC2JStringRef session_param = GetPlatform( )->CreateC2JString( session_id );
	if ( INTERNAL_HANDLER( )->mMSC->CallBooleanMethod( "QISRGetResult", "(Ljava/lang/String;I)Z", session_param->ToJString( ), wait_time ) == _false )
		return _false;

	rec_stat	= (_REC_STATUS)INTERNAL_HANDLER( )->mMSC->CallIntMethod( "QISRGetResultRECStatus", "(Ljava/lang/String;)I", session_param->ToJString( ) );
	string		= GetPlatform( )->ToStringW( (jstring) INTERNAL_HANDLER( )->mMSC->CallObjectMethod( "QISRGetResultString", "(Ljava/lang/String;)Ljava/lang/String;", session_param->ToJString( ) ) );

	return _true;
}

AString MSCSDK::QTTS_SessionBegin( const SoundRecognizerText2PCMInfo& config )
{
	IC2JStringRef voice_name_param = GetPlatform( )->CreateC2JString( config.mVoiceName );
	jstring js_session = (jstring)INTERNAL_HANDLER( )->mMSC->CallObjectMethod( "QTTSSessionBegin",
		"(IIIIILjava/lang/String;)Ljava/lang/String;",
		config.mVolume, config.mSpeed, config.mPitch, config.mSampleRate, config.mSampleBitSize,
		voice_name_param->ToJString( ) );

	return GetPlatform( )->ToStringA( js_session );
}

_void MSCSDK::QTTS_SessionEnd( AStringPtr session_id )
{
	IC2JStringRef session_param = GetPlatform( )->CreateC2JString( session_id );
	INTERNAL_HANDLER( )->mMSC->CallVoidMethod( "QTTSSessionEnd", "(Ljava/lang/String;)V", session_param->ToJString( ) );
}

_ubool MSCSDK::QTTS_TextPut( AStringPtr session_id, WStringPtr string )
{
	IC2JStringRef session_param = GetPlatform( )->CreateC2JString( session_id );
	IC2JStringRef string_param = GetPlatform( )->CreateC2JString( string );
	return INTERNAL_HANDLER( )->mMSC->CallBooleanMethod( "QTTSTextPut", "(Ljava/lang/String;Ljava/lang/String;)Z", 
		session_param->ToJString( ), string_param->ToJString( ) );
}

_ubool MSCSDK::QTTS_AudioGet( AStringPtr session_id, const _byte*& buffer, _dword& size, _TTS_FLAG& synth_status )
{
	IC2JStringRef session_param	= GetPlatform( )->CreateC2JString( session_id );
	jbyteArray jbuffer = (jbyteArray)INTERNAL_HANDLER( )->mMSC->CallObjectMethod( "QTTSAudioGet", "(Ljava/lang/String;)[B", session_param->ToJString( ) );
	if ( buffer == _null )
		return _false;

	IJ2CArrayRef audio_buffer = GetPlatform( )->CreateJ2CArray( jbuffer );
	if ( audio_buffer.IsNull( ) )
		return _false;

	buffer			= audio_buffer->GetBuffer( );
	size			= audio_buffer->GetSize( );
	synth_status	= (_TTS_FLAG)INTERNAL_HANDLER( )->mMSC->CallIntMethod( "QTTSAudioGetFlag", "(Ljava/lang/String;)I", session_param->ToJString( ) );

	return _true;
}
