//! @file     SoundRecognizer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundRecognizer Implementation
//----------------------------------------------------------------------------

SoundRecognizer::SoundRecognizer( )
{
	mEPStat			= MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH;
	mRecStat		= MSCSDK::_REC_STATUS_SUCCESS;
	mAudioStatus	= MSCSDK::_AUDIO_SAMPLE_INIT;
}

SoundRecognizer::~SoundRecognizer( )
{
	CloseQISRSession( );

	Logout( );
}

_ubool SoundRecognizer::StartQISRSession( )
{
	mSessionID = MSCSDK::GetInstance( ).QISR_SessionBegin( mAudioInfo );
	if ( mSessionID.IsEmpty( ) )
		return _false;

	mEPStat			= MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH;
	mRecStat		= MSCSDK::_REC_STATUS_SUCCESS;
	mAudioStatus	= MSCSDK::_AUDIO_SAMPLE_FIRST;

	return _true;
}

_void SoundRecognizer::CloseQISRSession( )
{
	MSCSDK::GetInstance( ).QISR_SessionEnd( mSessionID );
	mSessionID = "";

	mEPStat			= MSCSDK::_EP_STATUS_LOOKING_FOR_SPEECH;
	mRecStat		= MSCSDK::_REC_STATUS_SUCCESS;
	mAudioStatus	= MSCSDK::_AUDIO_SAMPLE_INIT;
}

IWAVFilePassRef SoundRecognizer::ConvertText2WAVFile( AStringPtr session_id, WStringPtr string, const SoundRecognizerText2PCMInfo& config )
{
	if ( MSCSDK::GetInstance( ).QTTS_TextPut( session_id, string ) == _false )
		return _null;

	ISoundFileWriterPassRef wav_file_writer = GetInterfaceFactory( )->CreateSoundFileWriter( _FF_WAV );
	if ( wav_file_writer.IsNull( ) )
		return _null;

	if ( wav_file_writer->Start( 1, config.mSampleRate, config.mSampleBitSize ) == _false )
		return _null;

	while ( _true )
	{
		const _byte* data = _null; _dword size = 0; MSCSDK::_TTS_FLAG flag = MSCSDK::_TTS_FLAG_STILL_HAVE_DATA;
		if ( MSCSDK::GetInstance( ).QTTS_AudioGet( session_id, data, size, flag ) == _false )
			return _null;

		if ( data != _null && size != 0 )
			wav_file_writer->Encode( data, size );

		if ( flag == MSCSDK::_TTS_FLAG_DATA_END )
			break;
	}

	wav_file_writer->Stop( );

	// Save to WAV file
	return wav_file_writer->SaveToBaseFile( );
}

_ubool SoundRecognizer::Login( WStringPtr app_id )
{
	return Login( app_id, L"" );
}

_ubool SoundRecognizer::Login( WStringPtr app_id, WStringPtr working_dir )
{
	if ( app_id.IsBlank( ) )
		return _false;

	// Load MSC SDK
	if ( MSCSDK::GetInstance( ).Load( ) == _false )
		return _false;

	// Build login parameters
	WString login_params = FORMAT_WSTRING_1( L"appid = %s", app_id.Str( ) );
	if ( working_dir.IsEmpty( ) == _false )
		login_params += FORMAT_WSTRING_1( L", work_dir = %s", working_dir.Str( ) );

	// Login
	if ( MSCSDK::GetInstance( ).MSP_Login( login_params ) == _false )
		return _false;

	return _true;
}

_void SoundRecognizer::Logout( )
{
	MSCSDK::GetInstance( ).MSP_Logout( );
}

_ubool SoundRecognizer::Start( const SoundRecognizerAudioInfo& audio_info )
{
	if ( audio_info.mSampleRate == 0 || audio_info.mAccent.IsEmpty( ) || audio_info.mLanguage.IsEmpty( ) )
		return _false;

	if ( mSessionID.IsEmpty( ) == _false )
		return _false;

	mAudioInfo = audio_info;

	return _true;
}

_ubool SoundRecognizer::Listen( _dword size, const _byte* buffer, WString& string )
{
	if ( size == 0 || buffer == _null )
		return _false;

	if ( mAudioInfo.IsValid( ) == _false )
		return _false;

	// Start session
	if ( mAudioStatus == MSCSDK::_AUDIO_SAMPLE_INIT )
	{
		if ( StartQISRSession( ) == _false )
			return _false;
	}

	if ( MSCSDK::GetInstance( ).QISR_AudioWrite( mSessionID, buffer, size, mAudioStatus, mEPStat, mRecStat ) == _false )
		return _false;

	mAudioStatus = MSCSDK::_AUDIO_SAMPLE_CONTINUE;

	// We have got something
	if ( mRecStat == MSCSDK::_REC_STATUS_SUCCESS )
	{
		WString result_string;
		if ( MSCSDK::GetInstance( ).QISR_GetResult( mSessionID, mRecStat, 0, result_string ) == _false )
			return _false;

		string += result_string;
	}

	// Is it then end ?
	if ( mEPStat == MSCSDK::_EP_STATUS_AFTER_SPEECH )
	{
		while ( mRecStat != MSCSDK::_REC_STATUS_COMPLETE ) 
		{
			WString result_string;
			if ( MSCSDK::GetInstance( ).QISR_GetResult( mSessionID, mRecStat, 0, result_string ) == _false )
				return _false;

			string += result_string;
		}

		CloseQISRSession( );
	}

	return _true;
}

_void SoundRecognizer::Stop( WString& string )
{
	if ( mSessionID.IsEmpty( ) )
		return;

	if ( MSCSDK::GetInstance( ).QISR_AudioWrite( mSessionID, _null, 0, MSCSDK::_AUDIO_SAMPLE_LAST, mEPStat, mRecStat ) )
	{
		while ( mRecStat != MSCSDK::_REC_STATUS_COMPLETE ) 
		{
			WString result_string;
			if ( MSCSDK::GetInstance( ).QISR_GetResult( mSessionID, mRecStat, 0, result_string ) == _false )
				break;

			string += result_string;
		}
	}

	CloseQISRSession( );

	mAudioInfo.Clear( );
}

IWAVFilePassRef SoundRecognizer::ConvertText2WAVFile( WStringPtr string, const SoundRecognizerText2PCMInfo& config )
{
	AString session_id = MSCSDK::GetInstance( ).QTTS_SessionBegin( config );
	if ( session_id.IsEmpty( ) )
		return _null;

	IWAVFilePassRef wav_file = ConvertText2WAVFile( session_id, string, config );

	MSCSDK::GetInstance( ).QTTS_SessionEnd( session_id );

	return wav_file;
}
