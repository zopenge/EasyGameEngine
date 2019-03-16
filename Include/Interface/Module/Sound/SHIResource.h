//! @file     SHIResource.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Common SHI definitions
//----------------------------------------------------------------------------

//!	The sound sampling rate
enum _SOUND_SAMPLING_RATE
{
	_SOUND_SAMPLING_RATE_8		= 8000,
	_SOUND_SAMPLING_RATE_11_025	= 11025,
	_SOUND_SAMPLING_RATE_12		= 12000,
	_SOUND_SAMPLING_RATE_16		= 16000,
	_SOUND_SAMPLING_RATE_22_05	= 22050,
	_SOUND_SAMPLING_RATE_24		= 24000,
	_SOUND_SAMPLING_RATE_32		= 32000,
	_SOUND_SAMPLING_RATE_44_1	= 44100,
	_SOUND_SAMPLING_RATE_48		= 48000,
	_SOUND_SAMPLING_RATE_64		= 64000,
	_SOUND_SAMPLING_RATE_88_2	= 88200,
	_SOUND_SAMPLING_RATE_96		= 96000,
	_SOUND_SAMPLING_RATE_192	= 192000,
};

//!	The sound source attribute
enum _SOUND_SOURCE_ATTRIBUTE
{
	//!	Specify the pitch to be applied at source.
	//!	Range:   [0.5-2.0]
	//!	Default: 1.0
	_SSA_PITCH,
	//!	Indicate the gain (volume amplification) applied. 
	_SSA_GAIN,
	//! Specify the current location in three dimensional space.
	_SSA_POSITION,
	//!	Specify the current velocity in three dimensional space.
	_SSA_VELOCITY,
	//! The listener direction in 3d space, first vector is look, second vector is up.
	_SSA_ORIENTATION,
	//!	Indicate whether source is looping.
	_SSA_LOOPING,
	//!	Indicate the buffers queued number
	_SSA_BUFFERS_QUEUED,
	//!	Indicate the buffers processed number
	_SSA_BUFFERS_PROCESSED,
	//! The attenuation factor
	_SSA_ATTENUATION_FACTOR,
	//! The attenuation min distance.
	_SSA_ATTENUATION_REFERENCE_DISTANCE,
	//! The attenuation max distance.
	_SSA_ATTENUATION_MAX_DISTANCE,
};

//! The sound source state
enum _SOUND_SOURCE_STATE
{
	_SSS_UNKNOWN,
	_SSS_INITIAL,
	_SSS_PLAYING,
	_SSS_PAUSED,
	_SSS_STOPPED,
};

//!	The (SRT, Sound Resource Type)
enum _SOUND_RESOURCE_TYPE
{
	_SRT_NONE,

	_SRT_RESOURCE,
	_SRT_BUFFER,
	_SRT_SOURCE,
	_SRT_EFFECT,
};

//!	The (SET, Sound Effect Type)
enum _SOUND_EFFECT_TYPE
{
	_SET_UNKNOWN,
	_SET_REVERB,
	_SET_CHORUS,
	_SET_DISTORTION,
	_SET_ECHO,
	_SET_FLANGER,
	_SET_FREQUENCY_SHIFTER,
	_SET_VOCAL_MORPHER,
	_SET_PITCH_SHIFTER,
	_SET_RING_MODULATOR,
	_SET_AUTOWAH,
	_SET_COMPRESSOR,
	_SET_EQUALIZER,
	_SET_EAXREVERB,
};

//! The (SEEP, Sound Effect Echo Parameter)
enum _SOUND_EFFCT_ECHO_PARAMETER
{
	_SEEP_UNKNOWN,

	_SEEP_DELAY,
	_SEEP_LRDELAY,
	_SEEP_DAMPING,
	_SEEP_FEEDBACK,
	_SEEP_SPREAD,
};

//----------------------------------------------------------------------------
// The SHI resource types
//----------------------------------------------------------------------------

#define ENUM_SHI_RESOURCE_TYPES(EnumerationMacro)			\
	EnumerationMacro(Resource, _SRT_RESOURCE, _SRT_NONE)	\
	EnumerationMacro(Buffer, _SRT_BUFFER, _SRT_RESOURCE)	\
	EnumerationMacro(Source, _SRT_SOURCE, _SRT_RESOURCE)	\
	EnumerationMacro(Effect, _SRT_EFFECT, _SRT_RESOURCE)

template< _SOUND_RESOURCE_TYPE ResourceType >
class TDynamicSHIResource : public TObject< IObject >
{
protected:
	TDynamicSHIResource( ) { }
	virtual ~TDynamicSHIResource( ) { }
};

#define DEFINE_DYNAMICSHI_REFERENCE_TYPE(Type, ResourceType, ParentResourceType)						\
template<> class TDynamicSHIResource< ResourceType > : public TDynamicSHIResource< ParentResourceType > \
{																										\
public:																									\
	virtual _SOUND_RESOURCE_TYPE GetResourceType( ) const { return ResourceType; }						\
};																										\
typedef TDynamicSHIResource< ResourceType > Type##SHI;													\
typedef RefPtr< Type##SHI > Type##SHIRef;																\
typedef PassRefPtr< Type##SHI > Type##SHIPassRef;
ENUM_SHI_RESOURCE_TYPES(DEFINE_DYNAMICSHI_REFERENCE_TYPE)
#undef DEFINE_DYNAMICSHI_REFERENCE_TYPE

//----------------------------------------------------------------------------
// IDynamicSHI
//----------------------------------------------------------------------------

class IDynamicSHI : public IObject
{
public:
	// The SHI methods are defined as virtual functions.
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "Interface/Module/Sound/SHIMethods.h"
	#undef DEFINE_SHIMETHOD
};

//----------------------------------------------------------------------------
// NullDynamicSHI
//----------------------------------------------------------------------------

//! A null implementation of the dynamically bound SHI.
class NullDynamicSHI : public INTERFACE_OBJECT_IMPL( IDynamicSHI )
{
public:
	// The SHI methods are defined as virtual functions.
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames { NullImplementation }
	#include "Interface/Module/Sound/SHIMethods.h"
	#undef DEFINE_SHIMETHOD
};

}