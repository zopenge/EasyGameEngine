//! @file     androidSoundRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// androidSoundRecorder JNI Implementation
//----------------------------------------------------------------------------

JNI_FUNC_3( void, AndroidRecorder, OnSoundRecorderStart, jint sample_rate, jint sample_bit_size, jlong user_data )
{
	androidSoundRecorder* recorder = (androidSoundRecorder*)user_data;
	EGE_ASSERT( recorder != _null );

	recorder->GetNotifier( )->OnStart( sample_rate, sample_bit_size );
}

JNI_FUNC_2( void, AndroidRecorder, OnSoundRecorderRecv, jbyteArray data, jlong user_data )
{
	if ( data == _null )
		return;

	androidSoundRecorder* recorder = (androidSoundRecorder*) user_data;
	EGE_ASSERT( recorder != _null );

	_dword			size	= GetPlatform( )->GetJNIEnv( )->GetArrayLength( data );
	const _byte*	buffer	= (const _byte*) GetPlatform( )->GetJNIEnv( )->GetByteArrayElements( data, _null );
	if ( size == 0 || buffer == _null )
		return;

	recorder->GetNotifier( )->OnRecv( size, buffer );
}

JNI_FUNC_1( void, AndroidRecorder, OnSoundRecorderStop, jlong user_data )
{
	androidSoundRecorder* recorder = (androidSoundRecorder*)user_data;
	EGE_ASSERT( recorder != _null );

	recorder->GetNotifier( )->OnStop( );
}
 
//----------------------------------------------------------------------------
// androidSoundRecorder Implementation
//----------------------------------------------------------------------------

androidSoundRecorder::androidSoundRecorder( )
{
}

androidSoundRecorder::~androidSoundRecorder( )
{
	Stop( );
}

_ubool androidSoundRecorder::Initialize( ISoundRecorderNotifier* notifier )
{
	if ( notifier == _null )
		return _false;

	mNotifier = notifier;

	mJNIObject = GetPlatform( )->CreateJNIObject( "com/ege/android/AndroidRecorder" );
	if ( mJNIObject.IsNull( ) )
		return _false;

	// Bind android recorder
	mJNIObject->CallVoidMethod( "init", "(J)V", (jlong)this );

	return _true;
}

_ubool androidSoundRecorder::Start( )
{
	return Start( 16000, 16 );
}

_ubool androidSoundRecorder::Start( _dword sample_rate, _dword sample_bit_size )
{
	mState = _SOUND_RECORDER_RECORDING;

	// Start android recorder
	mJNIObject->CallVoidMethod( "start", "(II)V", sample_rate, sample_bit_size );

	return _true;
}

_void androidSoundRecorder::Stop( )
{
	// Stopping
	mState = _SOUND_RECORDER_STOPPING;

	// Stop android recorder
	mJNIObject->CallVoidMethod( "stop", "()V" );

	// Stopped
	mState = _SOUND_RECORDER_STOPPED;
}
