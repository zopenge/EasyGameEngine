//! @file     IDeviceObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDeviceObject
//----------------------------------------------------------------------------

class IDeviceObject : public IObject
{
public:
	//!	Get the device type.
	//!	@param		none.
	//!	@return		The device type.
	virtual _DEVICE GetType( ) const PURE;

	//!	Get the device path.
	//!	@param		none.
	//!	@return		The device path.
	virtual WStringPtr GetPath( ) const PURE;
	//!	Get the device description.
	//!	@param		none.
	//!	@return		The device description.
	virtual WStringPtr GetDescription( ) const PURE;
};

}