//! @file     winControllerManager.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winControllerManager Implementation
//----------------------------------------------------------------------------

winControllerManager::winControllerManager( )
{
}

winControllerManager::~winControllerManager( )
{
	Pause( );
}

_ubool winControllerManager::Initialize( IViewBasedApp* application )
{
	if ( application == _null )
		return _false;

	mApplication = application;

	// Get the joysticks
	_dword number = joyGetNumDevs( );
	for ( _dword i = 0; i < number; i ++ )
	{
		JOYCAPS joy_caps;
		if ( ::joyGetDevCaps( JOYSTICKID1 + i, &joy_caps, sizeof( joy_caps ) ) != JOYERR_NOERROR )
			continue;

		// Get the x-range
		_dword jxm = ( joy_caps.wXmin + joy_caps.wXmax ) / 2;
		_dword jxl = ( joy_caps.wXmin + jxm ) / 2;
		_dword jxr = ( joy_caps.wXmax + jxm ) / 2;
		// Get the y-range
		_dword jym = ( joy_caps.wYmin + joy_caps.wYmax ) / 2;
		_dword jyt = ( joy_caps.wYmin + jym ) / 2;
		_dword jyb = ( joy_caps.wYmax + jym ) / 2;

		// Create and append joystick
		winJoystick* joystick = new winJoystick( i, DwordRange( jxl, jxr ), DwordRange( jyt, jyb ) );
		AppendJoystick( joystick );
	}

	Resume( );

	return _true;
}

_void winControllerManager::Pause( )
{
	for ( _dword i = 0; i < mJoysticks.Number( ); i ++ )
	{
		IJoystick* joystick = mJoysticks[i].GetPtr( );
		EGE_ASSERT( joystick != _null );

		::joyReleaseCapture( joystick->GetID( ) );
	}
}

_void winControllerManager::Resume( )
{
	for ( _dword i = 0; i < mJoysticks.Number( ); i ++ )
	{
		IJoystick* joystick = mJoysticks[i].GetPtr( );
		EGE_ASSERT( joystick != _null );

		::joySetCapture( (HWND) mApplication->GetApplicationHandle( ), joystick->GetID( ), 0, _false );
	}
}