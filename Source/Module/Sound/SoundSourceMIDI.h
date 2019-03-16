//! @file     SoundSourceMIDI.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundSourceMIDI
//----------------------------------------------------------------------------

class SoundSourceMIDI : public TSoundSource< ISoundSource >
{
private:
	typedef TSoundSource< ISoundSource > BaseClass;

// TSoundSource Interface
protected:
	virtual _void			OnFadeInSound( const FadeSoundInfo& sound_info ) override;

public:
	SoundSourceMIDI( );
	virtual ~SoundSourceMIDI( );

public:
	//!	Initialize.
	_ubool Initialize( const _byte* buffer, _dword size );

// ISoundSource Interface
public:
	virtual _void			Update( ) override;

	virtual _ubool			Play( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _ubool append ) override;
	virtual _ubool			Fade( ISoundFile* sound_file, _dword fade_out_time, _dword fade_in_time, _ubool loop ) override;

	virtual _ubool			AppendBuffer( _dword size, const _byte* buffer ) override;

	virtual _double			TimeSeek( _SEEK flag, _double time ) override;
	virtual _double			GetCurTime( ) const override;

	virtual _AUDIO_FORMAT	GetFormat( ) const override;
	virtual _dword			GetSampleRate( ) const override;
	virtual _double			GetLength( ) const override;
	virtual _dword			GetChannelsNumber( ) const override;
};

//----------------------------------------------------------------------------
// SoundSourceMIDI Implementation
//----------------------------------------------------------------------------

}