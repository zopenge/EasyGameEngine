//! @file     SHIMethods.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_SHIMETHOD is used by the includer to modify the SHI method definitions.
#ifndef DEFINE_SHIMETHOD
	#error "The DEFINE_SHIMETHOD marco must be defined"
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) Type Name ParameterTypesAndNames
#endif

//----------------------------------------------------------------------------
// SHI resource management
//----------------------------------------------------------------------------

DEFINE_SHIMETHOD(
	_ubool,
	Initialize,
	(),
	return _false;
	)
DEFINE_SHIMETHOD(
	_void,
	Suspend,
	(),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	Resume,
	(),
	;
	)
DEFINE_SHIMETHOD(
	_ubool,
	HasSuspend,
	(),
	return _false;
	)

//----------------------------------------------------------------------------
// SHI listener management
//----------------------------------------------------------------------------

DEFINE_SHIMETHOD(
	_ubool,
	SetListenerPosition,
	(const Vector3& position),
	return _false;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetListenerVelocity,
	(const Vector3& velocity),
	return _false;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetListenerOrientation,
	(const Vector3& up, const Vector3& look),
	return _false;
	)

//----------------------------------------------------------------------------
// SHI buffer management
//----------------------------------------------------------------------------

DEFINE_SHIMETHOD(
	BufferSHIPassRef,
	CreateBuffer,
	(),
	return _null;
	)

DEFINE_SHIMETHOD(
	_ubool,
	SetBufferData,
	(BufferSHI* buffer, const _void* data, _dword size, _AUDIO_FORMAT format, _dword sample_rate),
	return _false;
	)

//----------------------------------------------------------------------------
// SHI effect management
//----------------------------------------------------------------------------

DEFINE_SHIMETHOD(
	EffectSHIPassRef,
	CreateEffect,
	(_SOUND_EFFECT_TYPE effect_type),
	return _null;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetEffectEchoParameterf,
	(EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par, _float value),
	return _false;
	)
DEFINE_SHIMETHOD(
	_float,
	GetEffectEchoParameterf,
	(EffectSHI* effect, _SOUND_EFFCT_ECHO_PARAMETER par),
	return 0.0f;
	)

//----------------------------------------------------------------------------
// SHI source management
//----------------------------------------------------------------------------

DEFINE_SHIMETHOD(
	SourceSHIPassRef,
	CreateSource,
	(const SoundHeaderInfo& info),
	return _null;
	)
DEFINE_SHIMETHOD(
	SourceSHIPassRef,
	CreateMIDISource,
	(const _byte* buffer, _dword size),
	return _null;
	)

DEFINE_SHIMETHOD(
	_void,
	SourceTick,
	(SourceSHI* source, _time_t tick, _dword elapse),
	;
	)

DEFINE_SHIMETHOD(
	_void,
	SourceQueueBuffer,
	(SourceSHI* source, BufferSHI* buffer),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	SourceQueueBuffers,
	(SourceSHI* source, _dword number, BufferSHI** buffers),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	SourceUnqueueBuffers,
	(SourceSHI* source, _dword number, BufferSHI** buffers),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	SourceUnqueueBuffers,
	(SourceSHI* source, _dword number),
	;
	)

DEFINE_SHIMETHOD(
	_SOUND_SOURCE_STATE,
	GetSourceState,
	(SourceSHI* source),
	return _SSS_UNKNOWN;
	)
DEFINE_SHIMETHOD(
	_int,
	GetSourceAttributei,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute),
	return 0;
	)
DEFINE_SHIMETHOD(
	_float,
	GetSourceAttributef,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute),
	return 0.0f;
	)
DEFINE_SHIMETHOD(
	Vector3,
	GetSourceAttributefv,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute),
	return Vector3::cOrigin;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetSourceAttributei,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _int value),
	return _false;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetSourceAttributef,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _float value),
	return _false;
	)
DEFINE_SHIMETHOD(
	_ubool,
	SetSourceAttributefv,
	(SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, const Vector3& value),
	return _false;
	)

DEFINE_SHIMETHOD(
	_void,
	SourcePlay,
	(SourceSHI* source),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	SourceStop,
	(SourceSHI* source),
	;
	)
DEFINE_SHIMETHOD(
	_void,
	SourcePause,
	(SourceSHI* source),
	;
	)

DEFINE_SHIMETHOD(
	_ubool,
	AttachEffect,
	(SourceSHI* source, _dword index, EffectSHI* effect),
	return _false;
	)
DEFINE_SHIMETHOD(
	_void,
	DetachEffect,
	(SourceSHI* source, _dword index),
	;
	)
