//! @file     winJoystick.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winJoystick Implementation
//----------------------------------------------------------------------------

winJoystick::winJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range ) : BaseClass( id, x_range, y_range )
{
	mLastButtonStates	= 0;
	mLastPOV			= -1;
}

winJoystick::~winJoystick( )
{
}

_void winJoystick::HandleKey( _dword buttons, _dword flag, _dword key_code )
{
	if ( buttons & flag )
		mNotifier->OnKeyDown( mID, key_code );
	else if ( mLastButtonStates & flag )
		mNotifier->OnKeyUp( mID, key_code );
}

_ubool winJoystick::OnDispatchKeyEvent( _handle key_event )
{
	return _false;
}

_ubool winJoystick::OnDispatchGenericMotionEvent( _handle key_event )
{
	return _false;
}

_void winJoystick::OnMove( const PointI& pos )
{
	JOYINFOEX ji_ex;
	ji_ex.dwSize	= sizeof( JOYINFOEX );
	ji_ex.dwFlags	= JOY_RETURNALL;
	if ( ::joyGetPosEx( mID, &ji_ex ) != JOYERR_NOERROR )
		return;

	// Handle move action
	PointF joysitck_pos;
	joysitck_pos.x = EGE_RATIO( pos.x, 0xFFFF );
	joysitck_pos.y = EGE_RATIO( pos.y, 0xFFFF );
	mNotifier->OnLeftStickChanged( mID, joysitck_pos );

	// Handle keys
	HandleKey( ji_ex.dwButtons, JOY_BUTTON1, IJoystickNotifier::_KEYCODE_BUTTON_A );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON2, IJoystickNotifier::_KEYCODE_BUTTON_B );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON3, IJoystickNotifier::_KEYCODE_BUTTON_C );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON4, IJoystickNotifier::_KEYCODE_BUTTON_X );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON5, IJoystickNotifier::_KEYCODE_BUTTON_Y );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON6, IJoystickNotifier::_KEYCODE_BUTTON_Z );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON7, IJoystickNotifier::_KEYCODE_BUTTON_L1 );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON8, IJoystickNotifier::_KEYCODE_BUTTON_R1 );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON9, IJoystickNotifier::_KEYCODE_BUTTON_L2 );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON10, IJoystickNotifier::_KEYCODE_BUTTON_R2 );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON11, IJoystickNotifier::_KEYCODE_BUTTON_SELECT );
	HandleKey( ji_ex.dwButtons, JOY_BUTTON12, IJoystickNotifier::_KEYCODE_BUTTON_START );
	if ( mLastPOV != ji_ex.dwPOV )
	{
		switch ( mLastPOV )
		{
		case JOY_POVFORWARD:
			mNotifier->OnKeyUp( mID, IJoystickNotifier::_KEYCODE_POV_FORWARD );
			break;
		case JOY_POVRIGHT:
			mNotifier->OnKeyUp( mID, IJoystickNotifier::_KEYCODE_POV_RIGHT );
			break;
		case JOY_POVBACKWARD:
			mNotifier->OnKeyUp( mID, IJoystickNotifier::_KEYCODE_POV_BACKWARD );
			break;
		case JOY_POVLEFT:
			mNotifier->OnKeyUp( mID, IJoystickNotifier::_KEYCODE_POV_LEFT );
			break;
		}
		switch ( ji_ex.dwPOV )
		{
		case JOY_POVFORWARD:
			mNotifier->OnKeyDown( mID, IJoystickNotifier::_KEYCODE_POV_FORWARD );
			break;
		case JOY_POVRIGHT:
			mNotifier->OnKeyDown( mID, IJoystickNotifier::_KEYCODE_POV_RIGHT );
			break;
		case JOY_POVBACKWARD:
			mNotifier->OnKeyDown( mID, IJoystickNotifier::_KEYCODE_POV_BACKWARD );
			break;
		case JOY_POVLEFT:
			mNotifier->OnKeyDown( mID, IJoystickNotifier::_KEYCODE_POV_LEFT );
			break;
		}
	}
	// Update button states
	mLastButtonStates = ji_ex.dwButtons;
	mLastPOV = ji_ex.dwPOV;
}

_void winJoystick::OnZMove( _int z_pos )
{
	// Handle move action
	_float pos = EGE_RATIO( z_pos, 0xFFFF );
	mNotifier->OnZMoved( mID, pos );
}

_void winJoystick::OnButtonUp( _dword flags )
{
	//if ( flags & JOY_BUTTON1CHG )
	//	mNotifier->OnKeyUp( mID, IJoystickNotifier::KEYCODE_BUTTON_A );
	//if ( flags & JOY_BUTTON2CHG )
	//	mNotifier->OnKeyUp( mID, IJoystickNotifier::KEYCODE_BUTTON_B );
	//if ( flags & JOY_BUTTON3CHG )
	//	mNotifier->OnKeyUp( mID, IJoystickNotifier::KEYCODE_BUTTON_Y );
	//if ( flags & JOY_BUTTON4CHG )
	//	mNotifier->OnKeyUp( mID, IJoystickNotifier::KEYCODE_BUTTON_X );
}

_void winJoystick::OnButtonDown( _dword flags )
{
	//if ( flags & JOY_BUTTON1CHG )
	//	mNotifier->OnKeyDown( mID, IJoystickNotifier::KEYCODE_BUTTON_A );
	//if ( flags & JOY_BUTTON2CHG )
	//	mNotifier->OnKeyDown( mID, IJoystickNotifier::KEYCODE_BUTTON_B );
	//if ( flags & JOY_BUTTON3CHG )
	//	mNotifier->OnKeyDown( mID, IJoystickNotifier::KEYCODE_BUTTON_Y );
	//if ( flags & JOY_BUTTON4CHG )
	//	mNotifier->OnKeyDown( mID, IJoystickNotifier::KEYCODE_BUTTON_X );
}