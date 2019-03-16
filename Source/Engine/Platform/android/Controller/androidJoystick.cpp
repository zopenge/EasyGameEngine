//! @file     androidJoystick.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Helpful Functions Implementation
//----------------------------------------------------------------------------

static _dword AndroidControllerKeyCode2JoyKeyCode( _dword key_code )
{
	switch ( key_code )
	{
		case 96:	return IJoystickNotifier::_KEYCODE_BUTTON_Y;
		case 97:	return IJoystickNotifier::_KEYCODE_BUTTON_B;
		case 98:	return IJoystickNotifier::_KEYCODE_BUTTON_X;
		case 99:	return IJoystickNotifier::_KEYCODE_BUTTON_A;
		case 102:	return IJoystickNotifier::_KEYCODE_BUTTON_L1;
		case 103:	return IJoystickNotifier::_KEYCODE_BUTTON_R1;
		case 104:	return IJoystickNotifier::_KEYCODE_BUTTON_L2;
		case 105:	return IJoystickNotifier::_KEYCODE_BUTTON_R2;
		case 108:	return IJoystickNotifier::_KEYCODE_BUTTON_START;
		case 109:	return IJoystickNotifier::_KEYCODE_BUTTON_SELECT;
		default:
			return IJoystickNotifier::_KEYCODE_UNKNOWN;
	}
}
//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_3( void, AndroidController, OnCombKeyEventStart, jstring token, int player, jobject key )
{

}

JNI_FUNC_3( void, AndroidController, OnCombKeyEventOver, jstring token, int player, jobject key )
{

}

JNI_FUNC_3( void, AndroidController, OnControllerKeyDown, int playerOrder, int keyCode, jobject event )
{
	IJoystick* joystick = GetControllerManager( )->GetJoystickByID( playerOrder );
	if ( joystick != _null )
	{
		//switch ( keyCode )
		//{
		//	case _KEY_DPAD_UP:		joystick->GetNotifier( )->OnLeftStickChanged( playerOrder, PointF( 0.0f, -1.0f ) ); break;
		//	case _KEY_DPAD_DOWN:	joystick->GetNotifier( )->OnLeftStickChanged( playerOrder, PointF( 0.0f, 1.0f ) ); break;
		//	case _KEY_DPAD_LEFT:	joystick->GetNotifier( )->OnLeftStickChanged( playerOrder, PointF( -1.0f, 0.0f ) ); break;
		//	case _KEY_DPAD_RIGHT:	joystick->GetNotifier( )->OnLeftStickChanged( playerOrder, PointF( 1.0f, 0.0f ) ); break;
		//	default:
		//		break;
		//}

		joystick->GetNotifier( )->OnKeyDown( playerOrder, AndroidControllerKeyCode2JoyKeyCode( keyCode ) );
	}
}

JNI_FUNC_3( void, AndroidController, OnControllerKeyUp, int playerOrder, int keyCode, jobject event )
{
	IJoystick* joystick = GetControllerManager( )->GetJoystickByID( playerOrder );
	if ( joystick != _null )
		joystick->GetNotifier( )->OnKeyUp( playerOrder, AndroidControllerKeyCode2JoyKeyCode( keyCode ) );
}

JNI_FUNC_2( void, AndroidController, OnControllerStickEvent, int playerOrder, jobject event )
{

}

JNI_FUNC_1( void, AndroidController, OnControllerServiceReady, jboolean isSucc )
{

}

JNI_FUNC_1( void, AndroidController, OnBluetoothStateChanged, int state )
{

}

JNI_FUNC_3( void, AndroidController, OnControllerStateChanged, int playerOrder, int state, jobject device )
{

}

JNI_FUNC_3( void, AndroidController, OnLeftStickChanged, int player, float x, float y )
{
	IJoystick* joystick = GetControllerManager( )->GetJoystickByID( player );
	if ( joystick != _null )
		joystick->GetNotifier( )->OnLeftStickChanged( player, PointF( x, y ) );
}

JNI_FUNC_3( void, AndroidController, OnRightStickChanged, int player, float x, float y )
{
	IJoystick* joystick = GetControllerManager( )->GetJoystickByID( player );
	if ( joystick != _null )
		joystick->GetNotifier( )->OnRightStickChanged( player, PointF( x, y ) );
}

//----------------------------------------------------------------------------
// androidJoystick Implementation
//----------------------------------------------------------------------------

androidJoystick::androidJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range, JNIObject& jni_controller ) 
	: BaseClass( id, x_range, y_range )
	, mJNIController( jni_controller )
{
}

androidJoystick::~androidJoystick( )
{
}

_ubool androidJoystick::OnDispatchKeyEvent( _handle key_event )
{
	_ubool handled = mJNIController.CallBooleanMethod( "dispatchKeyEvent", "(Landroid/view/KeyEvent;)Z", key_event );

	return handled;
}

_ubool androidJoystick::OnDispatchGenericMotionEvent( _handle key_event )
{
	_ubool handled = mJNIController.CallBooleanMethod( "dispatchGenericMotionEvent", "(Landroid/view/MotionEvent;)Z", key_event );

	return handled;
}

_void androidJoystick::OnMove( const PointI& pos )
{
}

_void androidJoystick::OnZMove( _int z_pos )
{

}

_void androidJoystick::OnButtonUp( _dword flags )
{
}

_void androidJoystick::OnButtonDown( _dword flags )
{
}