//! @file     KeyboardDevice.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEInput.h"

//----------------------------------------------------------------------------
// KeyboardDevice Implementation
//----------------------------------------------------------------------------

KeyboardDevice::KeyboardDevice( ) : BaseClass( _DEVICE_KEYBOARD )
{
}

KeyboardDevice::~KeyboardDevice( )
{
}

_ubool KeyboardDevice::Initialize( )
{
	return _true;
}

_void KeyboardDevice::Tick( _time_t tick, _dword elapse )
{
}

_void KeyboardDevice::HandleMessage( const MessageBase& message )
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

_ubool KeyboardDevice::IsKeyDown( _dword keycode ) const
{
	return _false;
}