//! @file     SoundNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullSoundResourceManager
//----------------------------------------------------------------------------

class NullSoundResourceManager : public INTERFACE_OBJECT_IMPL( ISoundResourceManager )
{
public:
	NullSoundResourceManager( ) { }
	virtual ~NullSoundResourceManager( ) { }

// ISoundResourceManager Interface
public:
	virtual _dword					GetSoundsNumber( ) const { return 0; }
	virtual ISoundSourceRef			GetSoundByIndex( _dword index ) { return _null; }

	virtual _void					StopAllSounds( ) { }
	virtual ISoundSourceRef			CreateSoundSource( _AUDIO_FORMAT format, _dword channels, _dword sample_rate, _dword sample_bit_size ) { return _null; }
	virtual ISoundSourceRef			PlaySoundFromStream( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) { return _null; }
	virtual ISoundSourceRef			PlaySoundFromFile( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) { return _null; }

	virtual ISoundRecorderPassRef	CreateSoundRecorder( ISoundRecorderNotifier* notifier ) { return _null; }

	virtual ISoundRecognizerPassRef CreateSoundRecognizer( ) { return _null; }
};

//----------------------------------------------------------------------------
// NullSoundModule
//----------------------------------------------------------------------------

class NullSoundModule : public INTERFACE_MODULE_IMPL( ISoundModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( ISoundModule ) BaseClass;

public:
	NullSoundModule( ) : BaseClass( L"", Version::cZero ) { }
	virtual ~NullSoundModule( ) { }

// ISoundModule Interface
public:
	virtual _void	EnableOptions( _dword options, _ubool enable ) { }
	virtual _ubool	IsEnableOptions( _dword options ) const { return _false; }
};

//----------------------------------------------------------------------------
// NullSound
//----------------------------------------------------------------------------

class NullSound
{
	SINGLETON( NullSound )

private:
	NullDynamicSHI				mDynamicSHI;
	NullSoundResourceManager	mSoundResourceManager;
	NullSoundModule				mSoundModule;

public:
	EGE_GETR_ACCESSOR( NullDynamicSHI, DynamicSHI )
	EGE_GETR_ACCESSOR( NullSoundResourceManager, SoundResourceManager )
	EGE_GETR_ACCESSOR( NullSoundModule, SoundModule )
};

}