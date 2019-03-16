//! @file     SLDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

#if (_USE_OPENSL_ == 1)

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static _SOUND_SOURCE_STATE TranslateSourceState( SLuint32 state )
{
	switch ( state )
	{
		case SL_PLAYSTATE_INITIAL:	return _SSS_INITIAL;
		case SL_PLAYSTATE_PLAYING:	return _SSS_PLAYING;
		case SL_PLAYSTATE_PAUSED:	return _SSS_PAUSED;
		case SL_PLAYSTATE_STOPPED:	return _SSS_STOPPED;
		default: 
			return _SSS_UNKNOWN;
	}
}

//----------------------------------------------------------------------------
// SL-Drv Implementation
//----------------------------------------------------------------------------

SLDrv::SLDrv( )
{
	mHasSuspend				= _false;

	mSLLibObject			= _null;

	mSLEngine				= _null;
	mSLEngineCapabilities	= _null;
	mSLOutputMixObject		= _null;
}

SLDrv::~SLDrv( )
{
	// Destroy output mix object, and invalidate all associated interfaces
	if ( mSLOutputMixObject != _null )
		(*mSLOutputMixObject)->Destroy( mSLOutputMixObject );

	// destroy engine object, and invalidate all associated interfaces
	if ( mSLLibObject != _null )
		(*mSLLibObject)->Destroy( mSLLibObject );
}

_void SLDrv::OutputSLVersion( ) const
{
	SLint16 major = 0, minor = 0, step = 0;

	if ( mSLEngineCapabilities != _null )
	{
		SLresult result = (*mSLEngineCapabilities)->QueryAPIVersion( mSLEngineCapabilities, &major, &minor, &step );
		SL_CHECK_RESULT( "Query OpenSL API version" );
	}

	WLOG_TRACE_3( L"OpenSL API version: %d.%d.%d", major, minor, step );
}

_ubool SLDrv::Initialize( )
{
	WLOG_TRACE( L"Create OpenSL engine ... " );

	SLresult result = SL_RESULT_SUCCESS;

	// Create SL library
	const SLInterfaceID sl_lib_ids[1] = {SL_IID_ENGINECAPABILITIES}; const SLboolean sl_lib_req[1] = {SL_BOOLEAN_TRUE};
	result = slCreateEngine( &mSLLibObject, 0, _null, 0, sl_lib_ids, sl_lib_req );
	SL_CHECK_RESULT_BOOL( "Create OpenSL library object" );

	// Realize SL library
	result = (*mSLLibObject)->Realize( mSLLibObject, SL_BOOLEAN_FALSE );
	SL_CHECK_RESULT_BOOL( "Realize OpenSL library object" );
	
	// Get the engine capabilities interface
	result = (*mSLLibObject)->GetInterface( mSLLibObject, SL_IID_ENGINECAPABILITIES, &mSLEngineCapabilities );
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_WARNING_1( L"Get OpenSL engine capabilities from object failed, ret:%d", result );
	}

	// Get the engine interface, which is needed in order to create other objects
	result = (*mSLLibObject)->GetInterface( mSLLibObject, SL_IID_ENGINE, &mSLEngine );
	SL_CHECK_RESULT_BOOL( "Get OpenSL engine object" );

	// Create output mix, with environmental reverb specified as a non-required interface
	const SLInterfaceID mixer_ids[1] = {SL_IID_ENVIRONMENTALREVERB}; const SLboolean mixer_req[1] = {SL_BOOLEAN_FALSE};
	result = (*mSLEngine)->CreateOutputMix( mSLEngine, &mSLOutputMixObject, 1, mixer_ids, mixer_req );
	SL_CHECK_RESULT_BOOL( "Get OpenSL output mixer object" );

	// Realize the output mix
	result = (*mSLOutputMixObject)->Realize( mSLOutputMixObject, SL_BOOLEAN_FALSE );
	SL_CHECK_RESULT_BOOL( "Realize OpenSL output mixer object" );

	// Output the OpenSL version info
	OutputSLVersion( );

	WLOG_TRACE( L"Create OpenSL engine OK" );

	return _true;
}

_void SLDrv::Suspend( )
{
	mHasSuspend = _true;
}

_void SLDrv::Resume( )
{
	mHasSuspend = _false;
}

_ubool SLDrv::HasSuspend( )
{
	return mHasSuspend;
}

//----------------------------------------------------------------------------
// SL-Listener Implementation
//----------------------------------------------------------------------------

_ubool SLDrv::SetListenerPosition( const Vector3& position )
{
	return _true;
}

_ubool SLDrv::SetListenerVelocity( const Vector3& velocity )
{
	return _true;
}

_ubool SLDrv::SetListenerOrientation( const Vector3& up, const Vector3& look )
{
	return _true;
}

//----------------------------------------------------------------------------
// SL-Buffer Implementation
//----------------------------------------------------------------------------

BufferSHIPassRef SLDrv::CreateBuffer( )
{
	return new SLBuffer( );
}

_ubool SLDrv::SetBufferData( BufferSHI* buffer, const _void* data, _dword size, _AUDIO_FORMAT format, _dword sample_rate )
{
	if ( buffer == _null || data == _null || size == 0 )
	{
		WLOG_ERROR( L"Set sound buffer data failed, due to invalid buffer data or size" );
		return _false;
	}

	DYNAMIC_CAST_SLRESOURCE( Buffer, buffer );

	return sl_buffer->Copy( data, size, format, sample_rate );
}

//----------------------------------------------------------------------------
// AL-Effect management
//----------------------------------------------------------------------------

EffectSHIPassRef SLDrv::CreateEffect( _SOUND_EFFECT_TYPE effect_type )
{
	return _null;
}

_ubool SLDrv::SetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par, _float value )
{
	return _true;
}

_float SLDrv::GetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par )
{
	return 0.0f;
}

//----------------------------------------------------------------------------
// SL-Source Implementation
//----------------------------------------------------------------------------

SourceSHIPassRef SLDrv::CreateSource( const SoundHeaderInfo& info )
{
	if ( info.mChannels == 0 || info.mSampleRate == 0 )
		return _null;

	SLSource* sl_source = new SLSource( );
	if ( sl_source->InitPCM( info, mSLEngine, mSLOutputMixObject ) == _false )
		{ EGE_RELEASE( sl_source ); return _null; }

	return sl_source;
}

SourceSHIPassRef SLDrv::CreateMIDISource( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return _null;

	SLSource* sl_source = new SLSource( );
	if ( sl_source->InitMIDI( buffer, size, mSLEngine, mSLOutputMixObject ) == _false )
		{ EGE_RELEASE( sl_source ); return _null; }

	return sl_source;
}

_void SLDrv::SourceTick( SourceSHI* source, _time_t tick, _dword elapse )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->Tick( tick, elapse );
}

_void SLDrv::SourceQueueBuffer( SourceSHI* source, BufferSHI* buffer, _ubool is_sync )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );
	DYNAMIC_CAST_SLRESOURCE( Buffer, buffer );

	BufferSHI* buffers[] = { buffer };
	sl_source->QueueBuffers( 1, buffers );
}

_void SLDrv::SourceQueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers, _ubool is_sync )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->QueueBuffers( number, buffers );
}

_void SLDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->UnqueueBuffers( number, buffers );
}

_void SLDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	BufferSHI* buffers[128] = {0};
	sl_source->UnqueueBuffers( number, buffers );
}

_SOUND_SOURCE_STATE SLDrv::GetSourceState( SourceSHI* source )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	return TranslateSourceState( sl_source->GetPlayerState( ) );
}

_int SLDrv::GetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	switch ( attribute )
	{
		case _SSA_PITCH:				return (_int) (sl_source->GetPitch( ) * 100.0f);
		case _SSA_GAIN:					return (_int) (sl_source->GetVolume( ) * 100.0f);
		case _SSA_POSITION:				return 0;
		case _SSA_VELOCITY:				return 0;
		case _SSA_ORIENTATION:			return 0;
		case _SSA_LOOPING:				return 0;
		case _SSA_BUFFERS_QUEUED:		return sl_source->GetUnprocessedQueueNumber( );
		case _SSA_BUFFERS_PROCESSED:	return sl_source->GetProcessedBuffersNumber( );
		case _SSA_SOURCE_TYPE:			return 0;
		case _SSA_ATTENUATION_FACTOR:	return 0;
		case _SSA_ATTENUATION_REFERENCE_DISTANCE:	return 0;
		case _SSA_ATTENUATION_MAX_DISTANCE:	return 0;
		default: 
			return 0;
	}
}

_float SLDrv::GetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	switch ( attribute )
	{
		case _SSA_PITCH:				return sl_source->GetPitch( );
		case _SSA_GAIN:					return sl_source->GetVolume( );
		case _SSA_POSITION:				return 0.0f;
		case _SSA_VELOCITY:				return 0.0f;
		case _SSA_LOOPING:				return 0.0f;
		case _SSA_BUFFERS_QUEUED:		return (_float) sl_source->GetUnprocessedQueueNumber( );
		case _SSA_BUFFERS_PROCESSED:	return (_float) sl_source->GetProcessedBuffersNumber( );
		case _SSA_SOURCE_TYPE:			return 0.0f;
		default: 
			return 0;
	}
}

Vector3 SLDrv::GetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	return Vector3::cOrigin;
}

_ubool SLDrv::SetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _int value )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	switch ( attribute )
	{
		case _SSA_PITCH:				return sl_source->SetPitch( EGE_RATIO( value, 100.0f ) );
		case _SSA_GAIN:					return sl_source->SetVolume( EGE_RATIO( value, 100.0f ) );
		case _SSA_POSITION:				return _false;
		case _SSA_VELOCITY:				return _false;
		case _SSA_LOOPING:				return _false;
		case _SSA_BUFFERS_QUEUED:		return _false;
		case _SSA_BUFFERS_PROCESSED:	return _false;
		case _SSA_SOURCE_TYPE:			return _false;
		default: 
			return _false;
	}
}

_ubool SLDrv::SetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _float value )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	switch ( attribute )
	{
		case _SSA_PITCH:				return sl_source->SetPitch( value );
		case _SSA_GAIN:					return sl_source->SetVolume( value );
		case _SSA_POSITION:				return _false;
		case _SSA_VELOCITY:				return _false;
		case _SSA_LOOPING:				return _false;
		case _SSA_BUFFERS_QUEUED:		return _false;
		case _SSA_BUFFERS_PROCESSED:	return _false;
		case _SSA_SOURCE_TYPE:			return _false;
		default: 
			return _false;
	}
}

_ubool SLDrv::SetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, const Vector3& value )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	switch ( attribute )
	{
		case _SSA_PITCH:				return _false;
		case _SSA_GAIN:					return _false;
		case _SSA_POSITION:				return _false;
		case _SSA_VELOCITY:				return _false;
		case _SSA_LOOPING:				return _false;
		case _SSA_BUFFERS_QUEUED:		return _false;
		case _SSA_BUFFERS_PROCESSED:	return _false;
		case _SSA_SOURCE_TYPE:			return _false;
		default: 
			return _false;
	}
}

_void SLDrv::SourcePlay( SourceSHI* source )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->SetPlayerState( SL_PLAYSTATE_PLAYING );
}

_void SLDrv::SourceStop( SourceSHI* source )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->SetPlayerState( SL_PLAYSTATE_STOPPED );
}

_void SLDrv::SourcePause( SourceSHI* source )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );

	sl_source->SetPlayerState( SL_PLAYSTATE_PAUSED );
}

_ubool SLDrv::AttachEffect( SourceSHI* source, _dword index, EffectSHI* effect )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );
	DYNAMIC_CAST_SLRESOURCE( Effect, effect );

	return _true;
}

_void SLDrv::DetachEffect( SourceSHI* source, _dword index )
{
	DYNAMIC_CAST_SLRESOURCE( Source, source );
}

#endif