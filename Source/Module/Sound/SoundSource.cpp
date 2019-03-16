//! @file     SoundSource.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundSource Implementation
//----------------------------------------------------------------------------

SoundSource::SoundSource( )
{
	mCurPitch						= 1.0f;
	mCurVolume						= 1.0f;
	mPosition						= Vector3::cOrigin;
	mVelocity						= Vector3::cOrigin;
	mAttenuationFactor				= 1.0f;
	mAttenuationReferenceDistance	= 1.0f;
	mAttenuationMaxDistance			= Math::cMaxFloat;

	mFadeSoundInfo					= _null;

	mBufferQueue					= _null;
}

SoundSource::~SoundSource( )
{
	Stop( 0 );

	EGE_DELETE( mBufferQueue );

	EGE_DELETE( mFadeSoundInfo );
}

_void SoundSource::UpdateFadeObject( _dword elapse )
{
	if ( mFadeObject.GetFadeObject( ) == _FADE_NONE )
	{
		// Fade in sound
		if ( mFadeSoundInfo != _null )
		{
			SetVolume( mCurVolume );

			Play( mFadeSoundInfo->mFadeInTime, mFadeSoundInfo->mLoop, _false );

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

_void SoundSource::FadeIn( _dword fade_time )
{
	// Start from 0 volume when it's fade in sound
	gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_GAIN, 0.0f );
	mFadeObject.FadeIn( _FADE_PLAYING, fade_time, 0 );
}

_ubool SoundSource::Initialize( ISoundFile* sound_file )
{
	if ( sound_file == _null )
		return _false;

	// Get the sound file info
	const SoundHeaderInfo& sound_info = sound_file->GetHeaderInfo( );

	// Create the sound source resource
	mSourceSHI = gDynamicSHI->CreateSource( sound_info );
	if ( mSourceSHI.IsNull( ) )
		return _false;

	// Create buffer queue
	mBufferQueue = new SoundBufferQueue( mSourceSHI );
	if ( mBufferQueue->Initialize( sound_info.mFormat ) == _false )
	{
		WLOG_ERROR( L"Initialize sound source failed, due to initialize buffer queue failed" );
		return _false;
	}

	// Save the sound file
	mSoundFile = sound_file;

	return _true;
}

_void SoundSource::Tick( _dword limited_elapse, _dword elapse )
{
	gDynamicSHI->SourceTick( mSourceSHI, limited_elapse, elapse );

	UpdateFadeObject( elapse );
}

_void SoundSource::ProcessInBackground( )
{	
	LockOwner lock_owner( mLocker );

	EGE_ASSERT( Platform::IsMainThread( ) == _false );

	if ( mBufferQueue != _null )
		mBufferQueue->Update( mSoundFile );
}

_void SoundSource::SetSoundFile( ISoundFile* sound_file )
{
	LockOwner lock_owner( mLocker );

	if ( sound_file == _null )
		return;

	mSoundFile = sound_file;
}

ISoundFileRef SoundSource::GetSoundFile( )
{
	return mSoundFile;
}

_ubool SoundSource::Play( _dword fade_in_time, _ubool loop, _ubool append )
{
	LockOwner lock_owner( mLocker );

	// Fade in
	if ( fade_in_time != 0 )
		FadeIn( fade_in_time );

	// Play sound
	if ( mBufferQueue != _null )
		mBufferQueue->Play( mSoundFile, append, loop, _true );

	return _true;
}

_void SoundSource::ClearFadeInfo( )
{
	EGE_DELETE( mFadeSoundInfo );
	mFadeObject.Clear( );
}

_void SoundSource::Stop( _dword fade_out_time )
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

	if ( fade_out_time == 0 && mBufferQueue != _null )
	{
		LockOwner lock_owner( mLocker );
		mBufferQueue->Stop( );
	}
}

_ubool SoundSource::Pause( _dword fade_out_time )
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

_ubool SoundSource::Resume( _dword fade_out_time )
{
	gDynamicSHI->SourcePlay( mSourceSHI );

	if ( fade_out_time != 0 )
		FadeIn( fade_out_time );

	return _true;
}

_SOUND_SOURCE_STATE SoundSource::GetState( ) const
{
	return gDynamicSHI->GetSourceState( mSourceSHI.GetPtr( ) );
}

_ubool SoundSource::SetVolume( _float volume )
{
	if ( gDynamicSHI->SetSourceAttributef( mSourceSHI, _SSA_GAIN, volume ) == _false )
		return _false;

	mCurVolume = volume;

	return _true;
}

_float SoundSource::GetVolume( ) const
{
	return mCurVolume;
}

_ubool SoundSource::SetPitch( _float pitch )
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

_float SoundSource::GetPitch( ) const
{
	return mCurPitch;
}

_ubool SoundSource::SetPosition( const Vector3& position )
{
	if ( mPosition.Equal( position ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributefv( mSourceSHI, _SSA_POSITION, position ) == _false )
			return _false;

		mPosition = position;
	}
	return _true;
}

const Vector3& SoundSource::GetPosition( ) const
{
	return mPosition;
}

_ubool SoundSource::SetVelocity( const Vector3& velocity )
{
	if ( mVelocity.Equal( velocity ) == _false )
	{
		if ( gDynamicSHI->SetSourceAttributefv( mSourceSHI, _SSA_VELOCITY, velocity ) == _false )
			return _false;

		mVelocity = velocity;
	}
	return _true;
}

const Vector3& SoundSource::GetVelocity( ) const
{
	return mVelocity;
}

_ubool SoundSource::SetAttenuationFactor( _float factor )
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

_float SoundSource::GetAttenuationFactor( ) const
{
	return mAttenuationFactor;
}

_ubool SoundSource::SetAttenuationReferenceDistance( _float distance )
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

_float SoundSource::GetAttenuationReferenceDistance( ) const
{
	return mAttenuationReferenceDistance;
}

_ubool SoundSource::SetAttenuationMaxDistance( _float distance )
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

_float SoundSource::GetAttenuationMaxDistance( ) const
{
	return mAttenuationMaxDistance;
}

_double SoundSource::TimeSeek( _SEEK flag, _double time )
{
	LockOwner lock_owner( mLocker );

	return mSoundFile->TimeSeek( flag, time );
}

_double SoundSource::GetCurTime( ) const
{
	LockOwner lock_owner( mLocker );

	return mSoundFile->GetCurTime( );
}

_AUDIO_FORMAT SoundSource::GetFormat( ) const
{
	const SoundHeaderInfo& sound_info = mSoundFile->GetHeaderInfo( );

	return sound_info.mFormat;
}

_dword SoundSource::GetSampleRate( ) const
{
	const SoundHeaderInfo& sound_info = mSoundFile->GetHeaderInfo( );

	return sound_info.mSampleRate;
}

_double SoundSource::GetLength( ) const
{
	const SoundHeaderInfo& sound_info = mSoundFile->GetHeaderInfo( );

	return sound_info.mLength;
}

_dword SoundSource::GetChannelsNumber( ) const
{
	const SoundHeaderInfo& sound_info = mSoundFile->GetHeaderInfo( );

	return sound_info.mChannels;
}

_ubool SoundSource::IsStopped( ) const
{
	if ( mBufferQueue != _null && mBufferQueue->IsPlaying( ) )
		return _false;

	if ( mFadeSoundInfo != _null )
		return _false;

	return GetState( ) == _SSS_STOPPED;
}

_ubool SoundSource::IsStopping( ) const
{
	if ( GetState( ) != _SSS_PLAYING )
		return _false;

	if ( mFadeObject.GetFadeObject( ) != _FADE_STOPPING )
		return _false;

	return _true;
}

_ubool SoundSource::IsPaused( ) const
{
	if ( mFadeSoundInfo != _null )
		return _false;

	return GetState( ) == _SSS_PAUSED;
}

_ubool SoundSource::IsPlaying( ) const
{
	if ( mBufferQueue != _null && mBufferQueue->IsPlaying( ) )
		return _true;

	if ( mFadeSoundInfo != _null )
		return _true;

	return GetState( ) == _SSS_PLAYING;
}

SourceSHIRef SoundSource::GetResource( )
{
	return mSourceSHI;
}
