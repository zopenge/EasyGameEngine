//! @file     JoystickDevice.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEInput.h"

//----------------------------------------------------------------------------
// JoystickDevice Implementation
//----------------------------------------------------------------------------

JoystickDevice::JoystickDevice( ) : BaseClass( _DEVICE_JOYSTICK )
{
	EGE_INIT( mJoystickData );
}

JoystickDevice::~JoystickDevice( )
{
}

_ubool JoystickDevice::Initialize( )
{
	return _true;
}

_void JoystickDevice::Tick( _time_t tick, _dword elapse )
{
}

_void JoystickDevice::HandleMessage( const MessageBase& message )
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

const JoystickData& JoystickDevice::GetJoystickData( ) const
{
	return mJoystickData;
}