//! @file     SoundResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundResourceManager
//----------------------------------------------------------------------------

class SoundResourceManager : public TObject< ISoundResourceManager >
{
private:
	typedef TObject< ISoundResourceManager > BaseClass;

private:
	//!	The sound source info
	struct SoundSourceInfo
	{
		_dword			mStoppedTime;
		ISoundSourceRef	mSoundSource;

		//! Check whether it's alive
		_ubool IsAlive( ) const
		{
			if ( mSoundSource->GetRefCount( ) != 1 )
				return _true;

			if ( mStoppedTime == -1 )
				return _true;

			// We keep it alive after stopping 10 seconds
			if ( Platform::GetCurrentTickCount( ) - mStoppedTime < 10 SEC )
				return _true;

			if ( mSoundSource->IsStopped( ) == _false )
				return _true;

			return _false;
		}

		//!	Check whether it's compatible
		_ubool IsCompatible( const SoundHeaderInfo& sound_info ) const
		{
			if ( mSoundSource->GetFormat( ) != sound_info.mFormat )
				return _false;

			if ( mSoundSource->GetSampleRate( ) != sound_info.mSampleRate )
				return _false;
			
			if ( mSoundSource->GetChannelsNumber( ) != sound_info.mChannels )
				return _false;

			return _true;
		}

		SoundSourceInfo( ISoundSource* sound_source )
		{
			mSoundSource = sound_source;
		}
	};
	typedef Array< SoundSourceInfo* > SoundSourcePtrArray;

private:
	//!	The locker
	Lock				mLocker;
	//!	The thread
	PersistenceThread	mThread;

	//!	The sound source players
	SoundSourcePtrArray	mSoundSources;

private:
	//!	The sound sources update callback function.
	static _dword OnUpdateSoundSourcesCallback( const QwordParameters2& parameters );

private:
	//!	Find the free resident resource.
	ISoundSourceRef FindResidentSoundSource( ISoundFile* sound_file );

	//!	Create sound source.
	ISoundSourcePassRef CreateSoundSource( ISoundFile* sound_file );

	//!	Create the resident sound source.
	ISoundSourceRef CreateResidentSoundSource( ISoundFile* sound_file );

public:
	SoundResourceManager( );
	virtual ~SoundResourceManager( );

public:
	//!	Initialize/Finalize.
	_ubool Initialize( );
	_void Finalize( );

	//!	Pause.
	_void Pause( );
	//!	Resume.
	_void Resume( );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;

// ISoundResourceManager Interface
public:
	virtual _dword					GetSoundsNumber( ) const override;
	virtual ISoundSourceRef			GetSoundByIndex( _dword index ) override;

	virtual _void					StopAllSounds( ) override;
	virtual ISoundSourceRef			PlaySoundFromStream( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) override;
	virtual ISoundSourceRef			PlaySoundFromFile( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) override;

	virtual ISoundRecorderPassRef	CreateSoundRecorder( ISoundRecorderNotifier* notifier ) override;

	virtual ISoundRecognizerPassRef CreateSoundRecognizer( ) override;
};

//----------------------------------------------------------------------------
// SoundResourceManager Implementation
//----------------------------------------------------------------------------

}