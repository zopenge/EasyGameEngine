//! @file     chromeJoystick.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromeJoystick Implementation
//----------------------------------------------------------------------------

chromeJoystick::chromeJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range ) 
	: BaseClass( id, x_range, y_range )
{
}

chromeJoystick::~chromeJoystick( )
{
}

_ubool chromeJoystick::OnDispatchKeyEvent( _handle key_event )
{
	return _false;
}

_ubool chromeJoystick::OnDispatchGenericMotionEvent( _handle key_event )
{
	return _false;
}

_void chromeJoystick::OnMove( const PointI& pos )
{
}

_void chromeJoystick::OnZMove( _long z_pos )
{

}

_void chromeJoystick::OnButtonUp( _dword flags )
{
}

_void chromeJoystick::OnButtonDown( _dword flags )
{
}