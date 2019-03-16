//! @file     IInputDevice.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInputDevice
//----------------------------------------------------------------------------

class IInputDevice : public INameObject< IObject >
{
public:
	//!	Get the device type.
	//! @param		none.
	//!	@return		The type of device.
	virtual _DEVICE GetType( ) const PURE;
};

}