//! @file     TSoundSource.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSoundSource
//----------------------------------------------------------------------------

template< typename Type >
class TSoundSource : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The fade state
	enum _FADE_STATE
	{
		_FADE_NONE,
		_FADE_PLAYING,
		_FADE_STOPPING,
		_FADE_PAUSING,
	};

protected:
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

protected:
	//!	The current pitch
	_float			mCurPitch;
	//!	The current volume
	_float			mCurVolume;
	//! The current position.
	Vector3			mPosition;
	//! The current velocity.
	Vector3			mVelocity;
	_float			mAttenuationFactor;
	_float			mAttenuationReferenceDistance;
	_float			mAttenuationMaxDistance;
	//!	The source resource
	SourceSHIRef	mSourceSHI;

	//!	The sound file
	ISoundFileRef	mSoundFile;

	//!	The fade sound info
	FadeSoundInfo*	mFadeSoundInfo;

	//!	The fade object
	DwordFadeObject	mFadeObject;

protected:
	//!	When fade in sound.
	virtual _void OnFadeInSound( const FadeSoundInfo& sound_info ) PURE;

protected:
	//!	Update fade object.
	_void UpdateFadeObject( _dword elapse );
	//!	Fade in.
	_void FadeIn( _dword fade_time );

protected:
	TSoundSource( );
	virtual ~TSoundSource( );

// IObject Interface
public:
	virtual _void				Tick( _time_t tick, _dword elapse ) override;

// ISoundSource Interface
public:
	virtual _void				UpdateSoundFile( ISoundFile* sound_file ) override;

	virtual _ubool				Play( _dword fade_in_time, _ubool loop, _ubool append ) override;

	virtual _void				ClearFadeInfo( ) override;

	virtual _void				Stop( _dword fade_out_time ) override;
	virtual _ubool				Pause( _dword fade_out_time ) override;
	virtual _ubool				Resume( _dword fade_out_time ) override;

	virtual _SOUND_SOURCE_STATE GetState( ) const override;

	virtual _ubool				SetVolume( _float volume ) override;
	virtual _float				GetVolume( ) const override;

	virtual _ubool				SetPitch( _float pitch ) override;
	virtual _float				GetPitch( ) const override;

	virtual _ubool				SetPosition( const Vector3& position ) override;
	virtual const Vector3&		GetPosition( ) const override;
	virtual _ubool				SetVelocity( const Vector3& velocity ) override;
	virtual const Vector3&		GetVelocity( ) const override;

	virtual _ubool				SetAttenuationFactor( _float factor ) override;
	virtual _float				GetAttenuationFactor( ) const override;
	virtual _ubool				SetAttenuationReferenceDistance( _float distance ) override;
	virtual _float				GetAttenuationReferenceDistance( ) const override;
	virtual _ubool				SetAttenuationMaxDistance( _float distance ) override;
	virtual _float				GetAttenuationMaxDistance( ) const override;

	virtual _ubool				IsStopped( ) const override;
	virtual _ubool				IsStopping( ) const override;
	virtual _ubool				IsPaused( ) const override;
	virtual _ubool				IsPlaying( ) const override;

	virtual SourceSHIRef		GetResource( ) override;
};

//----------------------------------------------------------------------------
// TSoundSource Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSoundSource< Type >::TSoundSource( )
{
	mCurPitch						= 1.0f;
	mCurVolume						= 1.0f;
	mPosition						= Vector3::cOrigin;
	mVelocity						= Vector3::cOrigin;
	mAttenuationFactor				= 1.0f;
	mAttenuationReferenceDistance	= 1.0f;
	mAttenuationMaxDistance			= Math::cMaxFloat;

	mFadeSoundInfo					= _null;
}

template< typename Type >
TSoundSource< Type >::~TSoundSource( )
{
	EGE_DELETE( mFadeSoundInfo );
}

template< typename Type >
_void TSoundSource< Type >::UpdateFadeObject( _dword elapse )
{
	if ( mFadeObject.GetFadeObject( ) == _FADE_NONE )
	{
		// Fade in sound
		if ( mFadeSoundInfo != _null )
		{
			SetVolume( mCurVolume );

			OnFadeInSound( *mFadeSoundInfo );

			EGE_DELETE( mFadeSoundInfo );
		}

		return;
	}

	if ( mFadeObject.IsFinished( ) )
	{
		// Get the fade state
		_dword fade_state = mFadeObject.GetFadeObject( );

		// Update playing state
		switch ( fade_state )
		{
			case _FADE_PLAYING:
			{

			}
			break;

			case _FADE_STOPPING:
			{
				Stop( 0 );
			}
			break;

			case _FADE_PAUSING:
			{
				Pause( 0 );
			}
			break;

			default:
				break;
		}

		// Clear the fade state
		mFadeObject.Clear( );
	}
	else
	{
		// Update fade object to update volume
		mFadeObject.Tick( elapse );

		// Get the fade alpha
		_float fade_alpha = mFadeObject.GetFadeAlpha( );

		// Set the volume by fade object
		_float volume = mCurVolume * fade_alpha;
		gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_GAIN, volume );
	}
}

template< typename Type >
_void TSoundSource< Type >::FadeIn( _dword fade_time )
{
	// Start from 0 volume when it's fade in sound
	gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_GAIN, 0.0f );
	mFadeObject.FadeIn( _FADE_PLAYING, fade_time, 0 );
}

template< typename Type >
_void TSoundSource< Type >::Tick( _time_t tick, _dword elapse )
{
	gDynamicSHI->SourceTick( mSourceSHI, tick, elapse );

	UpdateFadeObject( elapse );
}

template< typename Type >
_void TSoundSource< Type >::UpdateSoundFile( ISoundFile* sound_file )
{
	if ( sound_file == _null )
		return;

	SetPitch( 1.0f );
	ClearFadeInfo( );

	mSoundFile = sound_file;
}

template< typename Type >
_ubool TSoundSource< Type >::Play( _dword fade_in_time, _ubool loop, _ubool append )
{
	// We should never call this function in this class
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_void TSoundSource< Type >::ClearFadeInfo( )
{
	EGE_DELETE( mFadeSoundInfo );
	mFadeObject.Clear( );
}

template< typename Type >
_void TSoundSource< Type >::Stop( _dword fade_out_time )
{
	if ( fade_out_time == 0 )
	{
		mFadeObject.Clear( );
		gDynamicSHI->SourceStop( mSourceSHI );
	}
	else
	{
		mFadeObject.FadeOut( _FADE_STOPPING, fade_out_time, 0 );
	}
}

template< typename Type >
_ubool TSoundSource< Type >::Pause( _dword fade_out_time )
{
	if ( fade_out_time == 0 )
	{
		mFadeObject.Clear( );
		gDynamicSHI->SourcePause( mSourceSHI );
	}
	else
	{
		mFadeObject.FadeOut( _FADE_PAUSING, fade_out_time, 0 );
	}

	return _true;
}

template< typename Type >
_ubool TSoundSource< Type >::Resume( _dword fade_out_time )
{
	gDynamicSHI->SourcePlay( mSourceSHI );

	if ( fade_out_time != 0 )
		FadeIn( fade_out_time );

	return _true;
}

template< typename Type >
_SOUND_SOURCE_STATE TSoundSource< Type >::GetState( ) const
{
	return gDynamicSHI->GetSourceState( mSourceSHI.GetPtr( ) );
}

template< typename Type >
_ubool TSoundSource< Type >::SetVolume( _float volume )
{
	if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_GAIN, volume ) == _false )
		return _false;

	mCurVolume = volume;

	return _true;
}

template< typename Type >
_float TSoundSource< Type >::GetVolume( ) const
{
	return mCurVolume;
}

template< typename Type >
_ubool TSoundSource< Type >::SetPitch( _float pitch )
{
	pitch = Math::Clamp( pitch, 0.5f, 2.0f );
	if ( Math::Equal( mCurPitch, pitch ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_PITCH, pitch ) == _false )
			return _false;

		mCurPitch = pitch;
	}

	return _true;
}

template< typename Type >
_float TSoundSource< Type >::GetPitch( ) const
{
	return mCurPitch;
}

template< typename Type >
_ubool TSoundSource< Type >::SetPosition( const Vector3& position )
{
	if ( mPosition.Equal( position ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributefv( mSourceSHI, _SSA_POSITION, position ) == _false )
			return _false;

		mPosition = position;
	}
	return _true;
}

template< typename Type >
const Vector3& TSoundSource< Type >::GetPosition( ) const
{
	return mPosition;
}

template< typename Type >
_ubool TSoundSource< Type >::SetVelocity( const Vector3& velocity )
{
	if ( mVelocity.Equal( velocity ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributefv( mSourceSHI, _SSA_VELOCITY, velocity ) == _false )
			return _false;

		mVelocity = velocity;
	}
	return _true;
}

template< typename Type >
const Vector3& TSoundSource< Type >::GetVelocity( ) const
{
	return mVelocity;
}

template< typename Type >
_ubool TSoundSource< Type >::SetAttenuationFactor( _float factor )
{
	factor = Math::Max( factor, 0.0f );
	if ( Math::Equal( mAttenuationFactor, factor ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_ATTENUATION_FACTOR, factor ) == _false )
			return _false;

		mAttenuationFactor = factor;
	}
	return _true;
}

template< typename Type >
_float TSoundSource< Type >::GetAttenuationFactor( ) const
{
	return mAttenuationFactor;
}

template< typename Type >
_ubool TSoundSource< Type >::SetAttenuationReferenceDistance( _float distance )
{
	distance = Math::Max( distance, 0.0f );
	if ( Math::Equal( mAttenuationReferenceDistance, distance ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_ATTENUATION_REFERENCE_DISTANCE, distance ) == _false )
			return _false;

		mAttenuationReferenceDistance = distance;
	}
	return _true;
}

template< typename Type >
_float TSoundSource< Type >::GetAttenuationReferenceDistance( ) const
{
	return mAttenuationReferenceDistance;
}

template< typename Type >
_ubool TSoundSource< Type >::SetAttenuationMaxDistance( _float distance )
{
	distance = Math::Max( distance, 0.0f );
	if ( Math::Equal( mAttenuationMaxDistance, distance ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_ATTENUATION_MAX_DISTANCE, distance ) == _false )
			return _false;

		mAttenuationMaxDistance = distance;
	}
	return _true;
}

template< typename Type >
_float TSoundSource< Type >::GetAttenuationMaxDistance( ) const
{
	return mAttenuationMaxDistance;
}

template< typename Type >
_ubool TSoundSource< Type >::IsStopping( ) const
{
	if ( GetState( ) != _SSS_PLAYING )
		return _false;

	if ( mFadeObject.GetFadeObject( ) != _FADE_STOPPING )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSoundSource< Type >::IsStopped( ) const
{
	if ( mFadeSoundInfo != _null )
		return _false;

	return GetState( ) == _SSS_STOPPED;
}

template< typename Type >
_ubool TSoundSource< Type >::IsPaused( ) const
{
	if ( mFadeSoundInfo != _null )
		return _false;

	return GetState( ) == _SSS_PAUSED;
}

template< typename Type >
_ubool TSoundSource< Type >::IsPlaying( ) const
{
	if ( mFadeSoundInfo != _null )
		return _true;

	return GetState( ) == _SSS_PLAYING;
}

template< typename Type >
SourceSHIRef TSoundSource< Type >::GetResource( )
{
	return mSourceSHI;
}

}