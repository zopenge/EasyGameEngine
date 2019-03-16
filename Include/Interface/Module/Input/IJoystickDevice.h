//! @file     IJoystickDevice.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// JoystickData
//----------------------------------------------------------------------------

struct JoystickData
{
};

//----------------------------------------------------------------------------
// IJoystickDevice
//----------------------------------------------------------------------------

class IJoystickDevice : public IInputDevice
{
public:
	//!	Get joystick data.
	//! @param		none.
	//! @return		The joystick data.
	virtual const JoystickData& GetJoystickData( ) const PURE;
};

}