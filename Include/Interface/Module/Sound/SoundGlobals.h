//! @file     SoundGlobals.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The sound enumerations
//----------------------------------------------------------------------------

//!	The sound options ( it can be changed any time )
enum _SOUND_OPTIONS
{
	//!	Indicates auto pause all sounds when application pause
	_SOUND_OPTION_PAUSE_ALL_WHEN_APP_PAUSE = 1 << 0,
};

//!	The sound recorder state
enum _SOUND_RECORDER_STATE
{
	_SOUND_RECORDER_STOPPED,
	_SOUND_RECORDER_STOPPING,
	_SOUND_RECORDER_RECORDING,
};

//----------------------------------------------------------------------------
// The sound structures
//----------------------------------------------------------------------------

struct SoundRecognizerAudioInfo
{
	_dword	mSampleRate;

	WString	mLanguage;
	WString	mAccent;

	_ubool IsValid( ) const
	{
		if ( mSampleRate == 0 )
			return _false;

		if ( mLanguage.IsEmpty( ) )
			return _false;

		if ( mAccent.IsEmpty( ) )
			return _false;

		return _true;
	}

	_void Clear( )
	{
		mSampleRate = 0;

		mLanguage	= L"";
		mAccent		= L"";
	}

	SoundRecognizerAudioInfo( )
	{
		mSampleRate = 0;
	}
};

struct SoundRecognizerText2PCMInfo
{
	_dword	mVolume;
	_dword	mSpeed;
	_dword	mPitch;
	_dword	mSampleRate;
	_dword	mSampleBitSize;

	WString	mVoiceName;

	_ubool IsValid( ) const
	{
		if ( mSampleRate == 0 )
			return _false;

		if ( mSampleBitSize == 0 )
			return _false;

		if ( mVoiceName.IsEmpty( ) )
			return _false;

		return _true;
	}

	SoundRecognizerText2PCMInfo( )
	{
		mVolume			= 0;
		mSpeed			= 0;
		mPitch			= 0;
		mSampleRate		= 0;
		mSampleBitSize	= 0;
	}
};

}