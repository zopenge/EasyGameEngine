//! @file     IKeyboardDevice.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IKeyboardDevice
//----------------------------------------------------------------------------

class IKeyboardDevice : public IInputDevice
{
public:
	//!	Is the specified key down.
	//! @param		keycode		Key code.
	//! @return		True indicates the key push down, false indicates is in up state.
	virtual _ubool IsKeyDown( _dword keycode ) const PURE;
};

}