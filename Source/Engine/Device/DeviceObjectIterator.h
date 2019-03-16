//! @file     DeviceObjectIterator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DeviceObjectIterator
//----------------------------------------------------------------------------

class DeviceObjectIterator : public INTERFACE_OBJECT_IMPL( IDeviceObjectIterator )
{
private:
	//!	The startup device object index
	_dword	mStartupDeviceObjectIndex;
	//!	The current device object index
	_dword	mCurrentDeviceObjectIndex;

	//!	The device type flags
	_dword	mDeviceFlags;

public:
	DeviceObjectIterator( _dword deviceindex, _dword deviceflags );
	virtual ~DeviceObjectIterator( );

// IIterator Interface
public:
	virtual IDeviceObjectRef	GetObject( ) override;
	virtual _ubool				HasObject( ) const override;

	virtual _ubool				MovePrev( ) override;
	virtual _ubool				MoveNext( ) override;
};

}