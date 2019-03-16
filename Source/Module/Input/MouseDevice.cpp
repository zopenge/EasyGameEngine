//! @file     MouseDevice.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEInput.h"

//----------------------------------------------------------------------------
// MouseDevice Implementation
//----------------------------------------------------------------------------

MouseDevice::MouseDevice( _handle windowhandle ) : mWindowHandle( windowhandle ), BaseClass( _DEVICE_MOUSE )
{
	EGE_INIT( mMouseData );
}

MouseDevice::~MouseDevice( )
{
}

_ubool MouseDevice::Initialize( )
{
	return _true;
}

_void MouseDevice::Tick( _time_t tick, _dword elapse )
{
	// Backup the previous position to calculate the delta position
	PointI old_position = mMouseData.mPosition;

	// Get the cursor position
	::GetCursorPos( (POINT*) &mMouseData.mPosition );
	// Get the cursor position of window's client region
	::ScreenToClient( (HWND) mWindowHandle, (POINT*) &mMouseData.mPosition );

	// Set the delta position
	mMouseData.mDeltaPosition = mMouseData.mPosition - old_position;
}

_void MouseDevice::HandleMessage( const MessageBase& message )
{
	switch ( message.mMsgID )
	{
		// Activate application
		case _MESSAGE_ACTIVATE_APP:
		{
		}
		break;

		// Deactivate application
		case _MESSAGE_DEACTIVATE_APP:
		{
		}
		break;
	}
}

const MouseData& MouseDevice::GetMouseData( ) const
{
	return mMouseData;
}