//! @file     SoundSourceMIDI.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundSourceMIDI Implementation
//----------------------------------------------------------------------------

SoundSourceMIDI::SoundSourceMIDI( )
{
}

SoundSourceMIDI::~SoundSourceMIDI( )
{
	Stop( 0 );
}

_void SoundSourceMIDI::OnFadeInSound( const FadeSoundInfo& sound_info )
{

}

_ubool SoundSourceMIDI::Initialize( const _byte* buffer, _dword size )
{
	// Create the sound source resource
	mSourceSHI = gDynamicSHI->CreateMIDISource( buffer, size );
	if ( mSourceSHI.IsNull( ) )
		return _false;

	return _true;
}

_void SoundSourceMIDI::Update( )
{	
}

_ubool SoundSourceMIDI::Play( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _ubool append )
{
	return _true;
}

_ubool SoundSourceMIDI::Fade( ISoundFile* sound_file, _dword fade_out_time, _dword fade_in_time, _ubool loop )
{
	return BaseClass::Fade( sound_file, fade_out_time, fade_in_time, loop );
}

_ubool SoundSourceMIDI::AppendBuffer( _dword size, const _byte* buffer )
{
	return _true;
}

_double SoundSourceMIDI::TimeSeek( _SEEK flag, _double time )
{
	return 0.0;
}

_double SoundSourceMIDI::GetCurTime( ) const
{
	return 0.0;
}

_AUDIO_FORMAT SoundSourceMIDI::GetFormat( ) const
{
	return _AF_UNKNOWN;
}

_dword SoundSourceMIDI::GetSampleRate( ) const
{
	return 0;
}

_double SoundSourceMIDI::GetLength( ) const
{
	return 0.0;
}

_dword SoundSourceMIDI::GetChannelsNumber( ) const
{
	return 0;
}