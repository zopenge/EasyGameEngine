//! @file     DeviceObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DeviceObject
//----------------------------------------------------------------------------

class DeviceObject : public INTERFACE_OBJECT_IMPL( IDeviceObject )
{
private:
	//!	The device info
	_DEVICE	mType;
	WString	mPath;
	WString	mDescription;

public:
	DeviceObject( _DEVICE type, WStringPtr path, WStringPtr description );
	virtual ~DeviceObject( );
	
// IDeviceObject Interface
public:
	virtual _DEVICE		GetType( ) const override;

	virtual WStringPtr 	GetPath( ) const override;
	virtual WStringPtr 	GetDescription( ) const override;
};

}