//! @file     SoundSource.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundSource
//----------------------------------------------------------------------------

class SoundSource : public TObject< ISoundSource >
{
private:
	//!	The fade state
	enum _FADE_STATE
	{
		_FADE_NONE,
		_FADE_PLAYING,
		_FADE_STOPPING,
		_FADE_PAUSING,
	};

private:
	//!	The fade sound info
	struct FadeSoundInfo
	{
		_dword	mFadeInTime;
		_ubool	mLoop;

		FadeSoundInfo( )
		{
			mFadeInTime = 0;
			mLoop		= _false;
		}
	};

private:
	//!	The thread lock
	Lock				mLocker;

	//!	The current pitch
	_float				mCurPitch;
	//!	The current volume
	_float				mCurVolume;
	//! The current position.
	Vector3				mPosition;
	//! The current velocity.
	Vector3				mVelocity;
	_float				mAttenuationFactor;
	_float				mAttenuationReferenceDistance;
	_float				mAttenuationMaxDistance;
	//!	The source resource
	SourceSHIRef		mSourceSHI;

	//!	The sound file
	ISoundFileRef		mSoundFile;

	//!	The fade sound info
	FadeSoundInfo*		mFadeSoundInfo;

	//!	The fade object
	DwordFadeObject		mFadeObject;
	
	//!	The buffer queue
	SoundBufferQueue*	mBufferQueue;

private:
	//!	Update fade object.
	_void UpdateFadeObject( _dword elapse );
	//!	Fade in.
	_void FadeIn( _dword fade_time );

public:
	SoundSource( );
	virtual ~SoundSource( );

public:
	//!	Initialize.
	_ubool Initialize( ISoundFile* sound_file );

// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// ISoundSource Interface
public:
	virtual _void				ProcessInBackground( ) override;

	virtual _void				SetSoundFile( ISoundFile* sound_file ) override;
	virtual ISoundFileRef		GetSoundFile( ) override;

	virtual _ubool				Play( _dword fade_in_time, _ubool loop, _ubool append ) override;

	virtual _void				ClearFadeInfo( ) override;

	virtual _void				Stop( _dword fade_out_time ) override;
	virtual _ubool				Pause( _dword fade_out_time ) override;
	virtual _ubool				Resume( _dword fade_out_time ) override;

	virtual _SOUND_SOURCE_STATE GetState( ) const override;

	virtual _double				TimeSeek( _SEEK flag, _double time ) override;
	virtual _double				GetCurTime( ) const override;

	virtual _ubool				SetPitch( _float pitch ) override;
	virtual _float				GetPitch( ) const override;

	virtual _ubool				SetPosition( const Vector3& position ) override;
	virtual const Vector3&		GetPosition( ) const override;
	virtual _ubool				SetVelocity( const Vector3& velocity ) override;
	virtual const Vector3&		GetVelocity( ) const override;

	virtual _ubool				SetVolume( _float volume ) override;
	virtual _float				GetVolume( ) const override;

	virtual _ubool				SetAttenuationFactor( _float factor ) override;
	virtual _float				GetAttenuationFactor( ) const override;
	virtual _ubool				SetAttenuationReferenceDistance( _float distance ) override;
	virtual _float				GetAttenuationReferenceDistance( ) const override;
	virtual _ubool				SetAttenuationMaxDistance( _float distance ) override;
	virtual _float				GetAttenuationMaxDistance( ) const override;

	virtual _AUDIO_FORMAT		GetFormat( ) const override;
	virtual _dword				GetSampleRate( ) const override;
	virtual _double				GetLength( ) const override;
	virtual _dword				GetChannelsNumber( ) const override;

	virtual _ubool				IsStopped( ) const override;
	virtual _ubool				IsStopping( ) const override;
	virtual _ubool				IsPaused( ) const override;
	virtual _ubool				IsPlaying( ) const override;

	virtual SourceSHIRef		GetResource( ) override;
};

//----------------------------------------------------------------------------
// SoundSource Implementation
//----------------------------------------------------------------------------

}