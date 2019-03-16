//! @file     PPBDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

#if (_USE_PPB_ == 1)

//----------------------------------------------------------------------------
// PPB-Drv Implementation
//----------------------------------------------------------------------------

PPBDrv::PPBDrv( )
{

}

PPBDrv::~PPBDrv( )
{
}

_ubool PPBDrv::Initialize( )
{
	return _true;
}

_void PPBDrv::Suspend( )
{
}

_void PPBDrv::Resume( )
{
}

_ubool PPBDrv::HasSuspend( )
{
	return _false;
}

//----------------------------------------------------------------------------
// AL-Listener Implementation
//----------------------------------------------------------------------------

_ubool PPBDrv::SetListenerPosition( const Vector3& position )
{
	return _true;
}

_ubool PPBDrv::SetListenerVelocity( const Vector3& velocity )
{
	return _true;
}

_ubool PPBDrv::SetListenerOrientation( const Vector3& up, const Vector3& look )
{
	return _true;
}

//----------------------------------------------------------------------------
// AL-Buffer Implementation
//----------------------------------------------------------------------------

BufferSHIPassRef PPBDrv::CreateBuffer( )
{
	return _null;
}

_ubool PPBDrv::SetBufferData( BufferSHI* buffer, const _void* data, _dword size, _AUDIO_FORMAT format, _dword frequency )
{
	return _true;
}

//----------------------------------------------------------------------------
// AL-Effect management
//----------------------------------------------------------------------------

EffectSHIPassRef PPBDrv::CreateEffect( _SOUND_EFFECT_TYPE effect_type )
{
    return _null;
}

_ubool PPBDrv::SetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par, _float value )
{
    return _false;
}

_float PPBDrv::GetEffectEchoParameterf( EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par )
{
    return 0.0f;
}

//----------------------------------------------------------------------------
// AL-Source Implementation
//----------------------------------------------------------------------------

SourceSHIPassRef PPBDrv::CreateSource( const SoundHeaderInfo& info )
{
	return _null;
}

SourceSHIPassRef PPBDrv::CreateMIDISource( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return _null;

	return _null;
}

_void PPBDrv::SourceTick( SourceSHI* source, _time_t tick, _dword elapse )
{
}

_void PPBDrv::SourceQueueBuffer( SourceSHI* source, BufferSHI* buffer, _ubool is_sync )
{
}

_void PPBDrv::SourceQueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers, _ubool is_sync )
{
}

_void PPBDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number, BufferSHI** buffers )
{
}

_void PPBDrv::SourceUnqueueBuffers( SourceSHI* source, _dword number )
{
}

_SOUND_SOURCE_STATE PPBDrv::GetSourceState( SourceSHI* source )
{
	return _SSS_UNKNOWN;
}

_long PPBDrv::GetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	return 0;
}

_float PPBDrv::GetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	return 0.0f;
}

Vector3 PPBDrv::GetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	Vector3 value = Vector3::cOrigin;
	return value;
}

_ubool PPBDrv::SetSourceAttributei( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _long value )
{
	return _true;
}

_ubool PPBDrv::SetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _float value )
{
	return _true;
}

_ubool PPBDrv::SetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, const Vector3& value )
{
	return _true;
}

_void PPBDrv::SourcePlay( SourceSHI* source )
{
}

_void PPBDrv::SourceStop( SourceSHI* source )
{
}

_void PPBDrv::SourcePause( SourceSHI* source )
{
}

_ubool PPBDrv::AttachEffect( SourceSHI* source, _dword index, EffectSHI* effect )
{
    return _false;
}

_void PPBDrv::DetachEffect( SourceSHI* source, _dword index )
{
}

#endif