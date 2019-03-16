//! @file     androidControllerManager.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidControllerManager Implementation
//----------------------------------------------------------------------------

androidControllerManager::androidControllerManager( )
{
}

androidControllerManager::~androidControllerManager( )
{
}

_ubool androidControllerManager::Initialize( IViewBasedApp* application )
{
	WLOG_TRACE( L"Initializing android controller manager ..." );

	// Get the controller JNI object
	JNIObject jni_controller;
	if ( jni_controller.Initialize( "com/ege/android/AndroidController", _false ) == _false )
	{
		WLOG_ERROR( L"Initialize JNI controller JAVA object failed" );
		return _false;
	}

	// Get the android-controller object
	jobject j_controller = (jobject) jni_controller.CallStaticObjectMethod( "getAndroidController", "()Lcom/ege/android/AndroidController;" );
	if ( j_controller == _null )
	{
		WLOG_ERROR( L"Get AndroidController object from JAVA failed" );
		return _false;
	}

	// Create the controller JNI object
	if ( mJNIController.Initialize( _false, "com/ege/android/AndroidController", j_controller ) == _false )
	{
		WLOG_ERROR( L"Initialize AndroidController object failed" );
		return _false;
	}

	// Get the joysticks number
	_dword number = mJNIController.CallIntMethod( "getDeviceNumber", "()I" );
	for ( _dword i = 0; i < number; i ++ )
	{
		// Create and append joystick
		androidJoystick* joystick = new androidJoystick( i + 1, DwordRange( 0, Math::cMaxDword ), DwordRange( 0, Math::cMaxDword ), mJNIController );
		AppendJoystick( joystick );
	}

	WLOG_TRACE( L"Initializing android controller manager OK" );

	return _true;
}

_void androidControllerManager::Pause( )
{
	mJNIController.CallVoidMethod( "pause", "()V" );
}

_void androidControllerManager::Resume( )
{
	mJNIController.CallVoidMethod( "resume", "()V" );
}