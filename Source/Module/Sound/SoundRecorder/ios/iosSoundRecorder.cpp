//! @file     iosSoundRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// iosSoundRecorder Implementation
//----------------------------------------------------------------------------

iosSoundRecorder::iosSoundRecorder( )
{
}

iosSoundRecorder::~iosSoundRecorder( )
{
	Stop( );
}

_ubool iosSoundRecorder::Initialize( ISoundRecorderNotifier* notifier )
{
	if ( notifier == _null )
		return _false;

	mNotifier = notifier;

	return _true;
}

_ubool iosSoundRecorder::Start( )
{
	return Start( 16000, 16 );
}

_ubool iosSoundRecorder::Start( _dword sample_rate, _dword sample_bit_size )
{
	mState = _SOUND_RECORDER_RECORDING;

	return _true;
}

_void iosSoundRecorder::Stop( )
{
	// Stopping
	mState = _SOUND_RECORDER_STOPPING;

	// Stopped
	mState = _SOUND_RECORDER_STOPPED;
}
