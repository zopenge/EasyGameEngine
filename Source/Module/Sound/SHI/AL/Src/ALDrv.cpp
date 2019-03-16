//! @file     ALDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

#if (_USE_OPENAL_ == 1)

//!	The max buffer number of source in queue
enum { _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE = 32 };

//----------------------------------------------------------------------------
// AL-Error Check Implementation
//----------------------------------------------------------------------------

_void EGE::ALCheckError( WStringPtr string )
{
	// Get the last OpenAL error ID
	ALenum error = ::alGetError( );
	if ( error == AL_NO_ERROR )
		return;

	// Get the error type string
	WStringPtr error_id_string;
	switch ( error )
	{
		case AL_INVALID_NAME:		error_id_string = L"Invalid Name"; break;
		case AL_INVALID_ENUM:		error_id_string = L"Invalid Enum"; break;
		case AL_INVALID_VALUE:		error_id_string = L"Invalid Value"; break;
		case AL_INVALID_OPERATION:	error_id_string = L"Invalid Operation"; break;
		case AL_OUT_OF_MEMORY:		error_id_string = L"Out Of Memory"; break;
		default:
			error_id_string = L"Error";
			break;
	}

	// Output the error string
	WLOG_ERROR_3( L"AL error code: 0x%x[%s] when execute '%s'", (_dword) error, error_id_string.Str( ), string.Str( ) );
	EGE_ASSERT( 0 );
}

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static ALenum TranslateAudioFormat( _AUDIO_FORMAT format )
{
	switch ( format )
	{
		case _AF_MONO8:		return AL_FORMAT_MONO8;
		case _AF_MONO16:	return AL_FORMAT_MONO16;
		case _AF_STEREO8:	return AL_FORMAT_STEREO8;
		case _AF_STEREO16:	return AL_FORMAT_STEREO16;
		default: 
			return AL_NONE;
	}
}

static ALenum TranslateSourceAttribute( _SOUND_SOURCE_ATTRIBUTE attribute )
{
	switch ( attribute )
	{
		case _SSA_PITCH:							return AL_PITCH;
		case _SSA_GAIN:								return AL_GAIN;
		case _SSA_POSITION:							return AL_POSITION;
		case _SSA_VELOCITY:							return AL_VELOCITY;
		case _SSA_ORIENTATION:						return AL_ORIENTATION;
		case _SSA_LOOPING:							return AL_LOOPING;
		case _SSA_BUFFERS_QUEUED:					return AL_BUFFERS_QUEUED;
		case _SSA_BUFFERS_PROCESSED:				return AL_BUFFERS_PROCESSED;
		case _SSA_ATTENUATION_FACTOR:				return AL_ROLLOFF_FACTOR;
		case _SSA_ATTENUATION_REFERENCE_DISTANCE:	return AL_REFERENCE_DISTANCE;
		case _SSA_ATTENUATION_MAX_DISTANCE:			return AL_MAX_DISTANCE;
		default: 
			return AL_NONE;
	}
}

static _SOUND_SOURCE_STATE TranslateSourceState( ALint state )
{
	switch ( state )
	{
		case AL_INITIAL:	return _SSS_INITIAL;
		case AL_PLAYING:	return _SSS_PLAYING;
		case AL_PAUSED:		return _SSS_PAUSED;
		case AL_STOPPED:	return _SSS_STOPPED;
		default: 
			return _SSS_UNKNOWN;
	}
}

#if (_USE_OPENAL_EXT_ == 1)

static ALenum TranslateEffectEchoParameter( _SOUND_EFFCT_ECHO_PARAMETER par )
{
	switch ( par )
	{
		case _SEEP_DELAY:		return AL_ECHO_DELAY;
		case _SEEP_LRDELAY:		return AL_ECHO_LRDELAY;
		case _SEEP_DAMPING:		return AL_ECHO_DAMPING;
		case _SEEP_FEEDBACK:	return AL_ECHO_FEEDBACK;
		case _SEEP_SPREAD:		return AL_ECHO_SPREAD;
		default: 
			return 0;
	}
}

static ALenum TranslateEffectType( _SOUND_EFFECT_TYPE type )
{
	switch ( type )
	{
		case _SET_REVERB:				return AL_EFFECT_REVERB;
		case _SET_CHORUS:				return AL_EFFECT_CHORUS;
		case _SET_DISTORTION:			return AL_EFFECT_DISTORTION;
		case _SET_ECHO:					return AL_EFFECT_ECHO;
		case _SET_FLANGER:				return AL_EFFECT_FLANGER;
		case _SET_FREQUENCY_SHIFTER:	return AL_EFFECT_FREQUENCY_SHIFTER;
		case _SET_VOCAL_MORPHER:		return AL_EFFECT_VOCAL_MORPHER;
		case _SET_PITCH_SHIFTER:		return AL_EFFECT_PITCH_SHIFTER;
		case _SET_RING_MODULATOR:		return AL_EFFECT_RING_MODULATOR;
		case _SET_AUTOWAH:				return AL_EFFECT_AUTOWAH;
		case _SET_COMPRESSOR:			return AL_EFFECT_COMPRESSOR;
		case _SET_EQUALIZER:			return AL_EFFECT_EQUALIZER;
		case _SET_EAXREVERB:			return AL_EFFECT_EAXREVERB;
		default: 
			return 0;
	}
}

#endif

//!	Build the buffer ID table.
static _void BuildBufferIDTable( ALuint resource_id[ _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE ], _dword number, BufferSHI** buffers )
{
	EGE_ASSERT( number <= _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE );

	// Get the resource ID
	for ( _dword i = 0; i < number; i ++ )
	{
		ALBuffer* al_buffer = static_cast< ALBuffer* >( buffers[i] );
		EGE_ASSERT( al_buffer != _null );

		resource_id[i] = al_buffer->GetResource( );
	}
}

//----------------------------------------------------------------------------
// AL-Drv Implementation
//----------------------------------------------------------------------------

ALDrv::ALDrv( )
{
	mHasSuspend	= _false;

#if (_USE_OPENAL_EXT_ == 1)
	mEffectSlot	= -1;
#endif
    
	mDevice		= _null;
	mContext	= _null;
}

ALDrv::~ALDrv( )
{
	ALResourceManager::GetInstance( ).Finalize( );

#if (_USE_OPENAL_EXT_ == 1)
	if ( mEffectSlot != -1 )
		::alDeleteAuxiliaryEffectSlots( 1, &mEffectSlot );
#endif

	if ( mContext != _null )
		::alcDestroyContext( mContext );

	if ( mDevice != _null )
		::alcCloseDevice( mDevice );
}

_void ALDrv::OutputALVersion( ) const
{
	// Get OpenAL version string
	ALCint major_version = 0, minor_version = 0;
	::alcGetIntegerv( mDevice, ALC_MAJOR_VERSION, sizeof( major_version ), (ALCint*) &major_version );
	::alcGetIntegerv( mDevice, ALC_MINOR_VERSION, sizeof( minor_version ), (ALCint*) &minor_version );
	ALOG_TRACE_2( "OpenAL version: %d.%d", major_version, minor_version );

	// Get OpenAL device specifier
	const _chara* al_device_specifier = (const _chara*) ::alcGetString( mDevice, ALC_DEVICE_SPECIFIER );
	if ( al_device_specifier != _null )
	{
		ALOG_TRACE_1( "OpenAL device specifier: %s", al_device_specifier );
	}
}

_void ALDrv::SourceUnqueueBuffers( SourceSHI* source, _dword& number, ALuint resource_id[] )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	// Get the actual processed number of sound buffer's number
	_dword processed_number = 0;
	AL_CHECK_ERROR( ::alGetSourcei( al_source->GetResource( ), AL_BUFFERS_PROCESSED, (ALint*) &processed_number ) );

	// Fixed the process number
	number = Math::Clamp< _dword >( number, 0, processed_number );

	// Unqueue buffers
	if ( number > 0 )
		AL_CHECK_ERROR( ::alSourceUnqueueBuffers( al_source->GetResource( ), number, resource_id ) );
}

_ubool ALDrv::Initialize( )
{
	WLOG_TRACE( L"Initialize OpenAL ..." );

	// Create device
	mDevice	= ::alcOpenDevice( _null );
	if ( mDevice == _null )
	{
		// We allow to create failed
		WLOG_WARNING_1( L"Create OpenAL device failed, err: %d", ::alcGetError( _null ) );
		return _false;
	}

	WLOG_TRACE_1( L"Create OpenAL device (0x%.8x)", (_qword)mDevice );

	// Create context
	mContext = ::alcCreateContext( mDevice, _null );
	if ( mContext == _null )
	{
		WLOG_ERROR_2( L"Create OpenAL context with '0x%x' device failed, err: %d", (_dword) (size_t)mDevice, ::alcGetError( _null ) );
		return _false;
	}

	WLOG_TRACE_1( L"Create OpenAL context (0x%.8x)", (_qword)mContext );

	// Active the context
	if ( !::alcMakeContextCurrent( mContext ) )
	{
		WLOG_ERROR_3( L"Make OpenAL '0x%x' context with '0x%x' device failed, err: %d", (_dword) (size_t)mContext, (_dword) (size_t)mDevice, ::alcGetError( _null ) );
		return _false;
	}

	// Initialize resource manager
	if ( ALResourceManager::GetInstance( ).Initialize( ) == _false )
	{
		WLOG_ERROR( L"Initialize OpenAL resource manager failed" );
		return _false;
	}

    // Create effect slot
#if (_USE_OPENAL_EXT_ == 1)
	AL_CHECK_ERROR( ::alGenAuxiliaryEffectSlots( 1, &mEffectSlot ) );
#endif

	// Output the OpenAL version info
	OutputALVersion( );

	WLOG_TRACE( L"Initialize OpenAL OK" );

	return _true;
}

_void ALDrv::Suspend( )
{
#ifdef _PLATFORM_IOS_
	NS_ALDeviceSuspend( );
#endif

	::alcSuspendContext( mContext );
	::alcMakeContextCurrent( _null );

	mHasSuspend = _true;
}

_void ALDrv::Resume( )
{
#ifdef _PLATFORM_IOS_
	NS_ALDeviceResume( );
#endif

	::alcMakeContextCurrent( mContext );
	::alcProcessContext( mContext );

	mHasSuspend = _false;
}

_ubool ALDrv::HasSuspend( )
{
	return mHasSuspend;
}

//----------------------------------------------------------------------------
// AL-Listener Implementation
//----------------------------------------------------------------------------

_ubool ALDrv::SetListenerPosition( const Vector3& position )
{
	AL_CHECK_ERROR( ::alListenerfv( AL_POSITION, (const ALfloat*) &position ) );

	return _true;
}

_ubool ALDrv::SetListenerVelocity( const Vector3& velocity )
{
	AL_CHECK_ERROR( ::alListenerfv( AL_VELOCITY, (const ALfloat*) &velocity ) );

	return _true;
}

_ubool ALDrv::SetListenerOrientation( const Vector3& up, const Vector3& look )
{
	_float v[] = { up.x, up.y, up.z, look.x, look.y, look.z };
	AL_CHECK_ERROR( ::alListenerfv( AL_ORIENTATION, v ) );

	return _true;
}

//----------------------------------------------------------------------------
// AL-Buffer Implementation
//----------------------------------------------------------------------------

BufferSHIPassRef ALDrv::CreateBuffer( )
{
	return new ALBuffer( );
}

_ubool ALDrv::SetBufferData( BufferSHI* buffer, const _void* data, _dword size, _AUDIO_FORMAT format, _dword sample_rate )
{
	DYNAMIC_CAST_ALRESOURCE( Buffer, buffer );

	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return _false;

	AL_CHECK_ERROR( ::alBufferData( al_buffer->GetResource( ), TranslateAudioFormat( format ), data, size, sample_rate ) );

	return _true;
}

//----------------------------------------------------------------------------
// AL-Effect management
//----------------------------------------------------------------------------

EffectSHIPassRef ALDrv::CreateEffect( _SOUND_EFFECT_TYPE effect_type )
{
#if (_USE_OPENAL_EXT_ == 1)
	ALEffect* al_effect = new ALEffect( );

	AL_CHECK_ERROR( ::alEffecti( al_effect->GetResource( ), AL_EFFECT_TYPE, TranslateEffectType( effect_type ) ) );

	ALuint effect_slot = static_cast< ALDrv* >( gDynamicSHI )->GetEffectSlot( );
	AL_CHECK_ERROR( ::alAuxiliaryEffectSloti( effect_slot, AL_EFFECTSLOT_EFFECT, al_effect->GetResource( ) ) );	

	return al_effect;
#else
    return _null;
#endif
}

_ubool ALDrv::SetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par, _float value )
{
#if (_USE_OPENAL_EXT_ == 1)
	DYNAMIC_CAST_ALRESOURCE( Effect, effect );

	AL_CHECK_ERROR( ::alEffectf( al_effect->GetResource( ), TranslateEffectEchoParameter( par ), value ) );

	return _true;
#else
    return _false;
#endif
}

_float ALDrv::GetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par )
{
#if (_USE_OPENAL_EXT_ == 1)
	DYNAMIC_CAST_ALRESOURCE( Effect, effect );

	_float value = 0.0f;
	AL_CHECK_ERROR( ::alGetEffectf( al_effect->GetResource( ), TranslateEffectEchoParameter( par ), &value ) );

	return value;
#else
    return 0.0f;
#endif
}

//----------------------------------------------------------------------------
// AL-Source Implementation
//----------------------------------------------------------------------------

SourceSHIPassRef ALDrv::CreateSource( const SoundHeaderInfo& info )
{
	return new ALSource( );
}

SourceSHIPassRef ALDrv::CreateMIDISource( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return _null;

	return _null;
}

_void ALDrv::SourceTick( SourceSHI* source, _time_t tick, _dword elapse )
{
}

_void ALDrv::SourceQueueBuffer( SourceSHI* source, BufferSHI* buffer )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );
	DYNAMIC_CAST_ALRESOURCE( Buffer, buffer );

	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	// Get the resource ID
	ALuint resource_id = al_buffer->GetResource( );

	// Queue buffers
	AL_CHECK_ERROR( ::alSourceQueueBuffers( al_source->GetResource( ), 1, (const ALuint*) &resource_id ) );
}

_void ALDrv::SourceQueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	// Get the resource ID
	ALuint resource_id[ _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE ];
	BuildBufferIDTable( resource_id, number, buffers );

	// Queue buffers
	AL_CHECK_ERROR( ::alSourceQueueBuffers( al_source->GetResource( ), number, resource_id ) );
}

_void ALDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	// The resource ID of buffers what to be unqueued
	ALuint resource_id[ _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE ] = {0};

	// Unqueue buffers
	SourceUnqueueBuffers( source, number, resource_id );

	// Feedback the buffers what we have unqueue
	for ( _dword i = 0; i < number; i ++ )
		buffers[i] = FindBuffer( resource_id[i] );
}

_void ALDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	// The resource ID of buffers what to be unqueued
	ALuint resource_id[ _MAX_BUFFER_NUMBER_OF_SOURCE_IN_QUEUE ] = {0};

	// Unqueue buffers
	SourceUnqueueBuffers( source, number, resource_id );
}

_SOUND_SOURCE_STATE ALDrv::GetSourceState( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	ALint value = 0;
	AL_CHECK_ERROR( ::alGetSourcei( al_source->GetResource( ), AL_SOURCE_STATE, &value ) );

	return TranslateSourceState( value );
}

_int ALDrv::GetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	ALint value = 0;
	AL_CHECK_ERROR( ::alGetSourcei( al_source->GetResource( ), TranslateSourceAttribute( attribute ), &value ) );

	return value;
}

_float ALDrv::GetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	ALfloat value = 0.0f;
	AL_CHECK_ERROR( ::alGetSourcef( al_source->GetResource( ), TranslateSourceAttribute( attribute ), &value ) );

	return value;
}

Vector3 ALDrv::GetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	Vector3 value = Vector3::cOrigin;
	AL_CHECK_ERROR( ::alGetSourcefv( al_source->GetResource( ), TranslateSourceAttribute( attribute ), (ALfloat*) &value ) );

	return value;
}

_ubool ALDrv::SetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _int value )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourcei( al_source->GetResource( ), TranslateSourceAttribute( attribute ), value ) );

	return _true;
}

_ubool ALDrv::SetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _float value )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourcef( al_source->GetResource( ), TranslateSourceAttribute( attribute ), value ) );

	return _true;
}

_ubool ALDrv::SetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, const Vector3& value )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourcefv( al_source->GetResource( ), TranslateSourceAttribute( attribute ), (const ALfloat*) &value ) );

	return _true;
}

_void ALDrv::SourcePlay( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourcePlay( al_source->GetResource( ) ) );
}

_void ALDrv::SourceStop( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourceStop( al_source->GetResource( ) ) );
}

_void ALDrv::SourcePause( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSourcePause( al_source->GetResource( ) ) );
}

_ubool ALDrv::AttachEffect( SourceSHI* source, _dword index, EffectSHI* effect )
{
#if (_USE_OPENAL_EXT_ == 1)
	DYNAMIC_CAST_ALRESOURCE( Source, source );
	DYNAMIC_CAST_ALRESOURCE( Effect, effect );

	AL_CHECK_ERROR( ::alSource3i( al_source->GetResource( ), AL_AUXILIARY_SEND_FILTER, al_effect->GetResource( ), index, AL_FILTER_NULL ) );

	return _true;
#else
    return _false;
#endif
}

_void ALDrv::DetachEffect( SourceSHI* source, _dword index )
{
#if (_USE_OPENAL_EXT_ == 1)
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	AL_CHECK_ERROR( ::alSource3i( al_source->GetResource( ), AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, index, AL_FILTER_NULL ) );
#else
#endif
}

#endif
