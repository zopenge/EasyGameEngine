//! @file     ALSource.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGESound.h"

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static ALenum TranslateSourceAttribute( _SOUND_SOURCE_ATTRIBUTE attribute )
{
	switch ( attribute )
	{
		case _SSA_PITCH:	return AL_PITCH;
		case _SSA_GAIN:		return AL_GAIN;
		case _SSA_POSITION:	return AL_POSITION;
		case _SSA_VELOCITY:	return AL_VELOCITY;
		case _SSA_LOOPING:	return AL_LOOPING;
		default: 
			return AL_NONE;
	}
}

//----------------------------------------------------------------------------
// AL-Source Implementation
//----------------------------------------------------------------------------

SourceSHIPassRef ALDrv::CreateSource( )
{
	return new ALSource( );
}

_ubool ALDrv::SetSourceBuffer( SourceSHI* source, BufferSHI* buffer )
{
	return _true;
}

_float ALDrv::GetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );
	
	ALfloat value = 0.0f;
	::alGetSourcef( al_source->GetResource( ), TranslateSourceAttribute( attribute ), &value );
	CheckALError( );

	return value;
}

Vector3 ALDrv::GetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );
	
	Vector3 value = Vector3::cOrigin;
	::alGetSourcefv( al_source->GetResource( ), TranslateSourceAttribute( attribute ), (ALfloat*) &value );
	CheckALError( );

	return value;
}

_ubool ALDrv::SetSourceAttributef( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, _float value )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	::alSourcef( al_source->GetResource( ), TranslateSourceAttribute( attribute ), value );

	return CheckALError( );
}

_ubool ALDrv::SetSourceAttributefv( SourceSHI* source, _SOUND_SOURCE_ATTRIBUTE attribute, const Vector3& value )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	::alSourcefv( al_source->GetResource( ), TranslateSourceAttribute( attribute ), (const ALfloat*) &value );

	return CheckALError( );
}

_void ALDrv::SourcePlay( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	::alSourcePlay( al_source->GetResource( ) );
}

_void ALDrv::SourceStop( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	::alSourceStop( al_source->GetResource( ) );
}

_void ALDrv::SourcePause( SourceSHI* source )
{
	DYNAMIC_CAST_ALRESOURCE( Source, source );

	::alSourcePause( al_source->GetResource( ) );
}