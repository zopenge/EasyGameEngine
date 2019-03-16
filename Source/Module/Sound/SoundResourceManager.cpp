//! @file     SoundResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundResourceManager Implementation
//----------------------------------------------------------------------------

SoundResourceManager::SoundResourceManager( )
{
}

SoundResourceManager::~SoundResourceManager( )
{
	Finalize( );
}

ISoundSourceRef SoundResourceManager::FindResidentSoundSource( ISoundFile* sound_file )
{
	// Get the sound file info
	const SoundHeaderInfo& sound_info = sound_file->GetHeaderInfo( );

	// Try to use the same format sound source
	for ( _dword i = 0; i < mSoundSources.Number( ); i ++ )
	{
		SoundSourceInfo* source_info = mSoundSources[i];
		EGE_ASSERT( source_info != _null );

		// Get the sound source
		ISoundSource* sound_source = source_info->mSoundSource;
		EGE_ASSERT( sound_source != _null );

		// The sound source must be not busy (stopped)
		if ( sound_source->IsStopped( ) == _false )
			continue;

		// Check audio format, frequency and channels
		if ( source_info->IsCompatible( sound_info ) )
		{
			// It's the same format sound source so we can use it directly
			sound_source->SetPitch( 1.0f );
			sound_source->ClearFadeInfo( );
			sound_source->SetSoundFile( sound_file );

			WLOG_TRACE_2( L"Find a resident sound source (slot: %d, max: %d)", i + 1, mSoundSources.Number( ) );

			return sound_source;
		}
	}

	return _null;
}

_dword SoundResourceManager::OnUpdateSoundSourcesCallback( const QwordParameters2& parameters )
{
	SoundResourceManager* sound_manager = (SoundResourceManager*) parameters[0];
	EGE_ASSERT( sound_manager != _null );

	LockOwner lock_owner( sound_manager->mLocker );
	
	if ( gDynamicSHI->HasSuspend( ) == _false )
	{
		SoundSourcePtrArray& sound_sources = sound_manager->mSoundSources;
		for ( _dword i = 0; i < sound_sources.Number( ); i ++ )
		{
			SoundSourceInfo* source_info = sound_sources[i];
			EGE_ASSERT( source_info != _null );

			ISoundSource* sound_source = source_info->mSoundSource;
			EGE_ASSERT( sound_source != _null );

			// The sound is playing
			if ( sound_source->IsPlaying( ) || sound_source->GetSoundFile( )->IsStreaming( ) )
			{
				source_info->mStoppedTime = -1;
				sound_source->ProcessInBackground( );
			}
			else if ( source_info->mStoppedTime == -1 )
			{
				source_info->mStoppedTime = Platform::GetCurrentTickCount( );
			}

			// Remove source when it's dead
			if ( source_info->IsAlive( ) == _false )
			{
				EGE_DELETE( source_info );
				sound_sources.RemoveByIndex( i -- );

				WLOG_TRACE_1( L"Remove a resident sound source (total:%d)", sound_sources.Number( ) );
			}
		}
	}

	return PersistenceThread::_ACTION_KEEP;
}

ISoundSourcePassRef SoundResourceManager::CreateSoundSource( ISoundFile* sound_file )
{
	// Create sound source
	SoundSource* sound_source = new SoundSource( );
	if ( sound_source->Initialize( sound_file ) == _false )
		{ EGE_RELEASE( sound_source ); return _null; }

	return sound_source;
}

ISoundSourceRef SoundResourceManager::CreateResidentSoundSource( ISoundFile* sound_file )
{
	LockOwner lock_owner( mLocker );

	// Find the free resident sound source
	ISoundSourceRef sound_source = FindResidentSoundSource( sound_file );
	if ( sound_source.IsNull( ) == _false )
		return sound_source;

	// Create sound source
	sound_source = CreateSoundSource( sound_file );
	if ( sound_source.IsNull( ) )
		return _null;

	mSoundSources.Append( new SoundSourceInfo( sound_source ) );

	WLOG_TRACE_1( L"Add a resident sound source (total:%d)", mSoundSources.Number( ) );

	return sound_source;
}

_ubool SoundResourceManager::Initialize( )
{
	WLOG_TRACE( L"Initializing sound resource manager ..." );

	// Create thread
	if ( mThread.Create( 1, 0, _false, 100, L"SoundResourceManager" ) == _false )
	{
		WLOG_ERROR( L"Initialize sound resource manager failed, due to create thread failed" );
		return _false;
	}

	mThread.AddUpdaterFunc( OnUpdateSoundSourcesCallback, QwordParameters2( (_qword)this, _null ) );

	WLOG_TRACE( L"Initialize sound resource manager OK" );

	return _true;
}

_void SoundResourceManager::Finalize( )
{
	WLOG_TRACE( L"Releasing sound resource manager ..." );

	// Stop all sounds first
	StopAllSounds( );

	// Close the update thread
	mThread.Close( );

	WLOG_TRACE( L"Release sound resource manager DONE" );
}

_void SoundResourceManager::Pause( )
{
	LockOwner lock_owner( mLocker );

	if ( gDynamicSHI->HasSuspend( ) )
		return;

	WLOG_TRACE( L"Pausing sound resource manager ..." );
	{
		for ( _dword i = 0; i < mSoundSources.Number( ); i ++ )
		{
			// Get the sound source
			ISoundSource* sound_source = mSoundSources[i]->mSoundSource;
			EGE_ASSERT( sound_source != _null );

			sound_source->Pause( 0 );
		}

		gDynamicSHI->Suspend( );

		mThread.Suspend( );
	}
	WLOG_TRACE( L"Pause sound resource manager DONE" );
}

_void SoundResourceManager::Resume( )
{
	LockOwner lock_owner( mLocker );

	if ( gDynamicSHI->HasSuspend( ) == _false )
		return;

	WLOG_TRACE( L"Resuming sound resource manager ..." );
	{
		gDynamicSHI->Resume( );

		for ( _dword i = 0; i < mSoundSources.Number( ); i ++ )
		{
			// Get the sound source
			ISoundSource* sound_source = mSoundSources[i]->mSoundSource;
			EGE_ASSERT( sound_source != _null );

			if ( sound_source->IsStopped( ) == _false )
				sound_source->Resume( 0 );
		}

		mThread.Resume( );
	}
	WLOG_TRACE( L"Resume sound resource manager DONE" );
}

_void SoundResourceManager::Tick( _dword limited_elapse, _dword elapse )
{
	if ( gDynamicSHI->HasSuspend( ) )
		return;

	// Update sound sources
	for ( _dword i = 0; i < mSoundSources.Number( ); i ++ )
	{
		// Get the sound source
		ISoundSource* sound_source = mSoundSources[i]->mSoundSource;
		EGE_ASSERT( sound_source != _null );

		// Keep playing sound, some operations will let the sound to stop(etc. big elapse), so we need to resume it here
		//if ( sound_source->IsPlaying( ) )
		//	sound_source->Resume( 0 );

		// Update sound
		sound_source->Tick( limited_elapse, elapse );
	}
}

_dword SoundResourceManager::GetSoundsNumber( ) const
{
	return mSoundSources.Number( );
}

ISoundSourceRef SoundResourceManager::GetSoundByIndex( _dword index )
{
	LockOwner lock_owner( mLocker );

	if ( index >= mSoundSources.Number( ) )
		return _null;

	return mSoundSources[index]->mSoundSource;
}

_void SoundResourceManager::StopAllSounds( )
{
	LockOwner lock_owner( mLocker );

	WLOG_TRACE( L"Stop all sounds ..." );

	// Delete sources
	for ( _dword i = 0; i < mSoundSources.Number( ); i ++ )
		EGE_DELETE( mSoundSources[i] );

	mSoundSources.Clear( _true );

	WLOG_TRACE( L"Stop all sounds done" );
}

ISoundSourceRef SoundResourceManager::PlaySoundFromStream( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword fade_in_time, _ubool loop, _float volume )
{
	if ( gDynamicSHI->HasSuspend( ) )
	{
		WLOG_ERROR( L"Skip to play sound due to it's suspend" );
		return _null;
	}

	// Parse sound file
	ISoundFileRef sound_file = GetInterfaceFactory( )->ParseSoundFile( stream_reader, file_format );
	if ( sound_file.IsNull( ) )
	{
		WLOG_ERROR( L"Play sound failed due to parse invalid sound file" );
		return _null;
	}

	return PlaySoundFromFile( sound_file, fade_in_time, loop, volume );
}

ISoundSourceRef	SoundResourceManager::PlaySoundFromFile( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _float volume )
{
	// Create resident sound source
	ISoundSourceRef sound_source = CreateResidentSoundSource( sound_file );
	if ( sound_source.IsNull( ) )
	{
		WLOG_ERROR( L"Play sound failed due to create resident sound source failed" );
		return _null;
	}

	// Set the volume
	sound_source->SetVolume( volume );

	// Play it
	sound_source->Play( fade_in_time, loop, _false );

	return sound_source;

}

ISoundRecorderPassRef SoundResourceManager::CreateSoundRecorder( ISoundRecorderNotifier* notifier )
{
#ifdef _PLATFORM_WINDOWS_
	winSoundRecorder* recorder = new winSoundRecorder( );
#elif _PLATFORM_ANDROID_
	androidSoundRecorder* recorder = new androidSoundRecorder( );
#elif _PLATFORM_IOS_
	iosSoundRecorder* recorder = new iosSoundRecorder( );
#endif

	// Initialize recorder
	if ( recorder->Initialize( notifier ) == _false )
		{ EGE_RELEASE( recorder ); return _null; }

	return recorder;
}

ISoundRecognizerPassRef SoundResourceManager::CreateSoundRecognizer( )
{
	SoundRecognizer* recognizer = new SoundRecognizer( );

	return recognizer;
}
