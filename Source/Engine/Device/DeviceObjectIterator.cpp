//! @file     DeviceObjectIterator.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DeviceObjectIterator Implementation
//----------------------------------------------------------------------------

DeviceObjectIterator::DeviceObjectIterator( _dword deviceindex, _dword deviceflags ) 
{
	mStartupDeviceObjectIndex	= deviceindex;
	mCurrentDeviceObjectIndex	= deviceindex;
	mDeviceFlags				= deviceflags;
}

DeviceObjectIterator::~DeviceObjectIterator( )
{

}

IDeviceObjectRef DeviceObjectIterator::GetObject( )
{
	//IDeviceObjectRef device_object = mDeviceModule->GetDeviceObjectByIndex( mCurrentDeviceObjectIndex );
	//if ( device_object.IsNull( ) )
	return _null;

	//	return device_object.StaticConvertTo< IObject >( );
}

_ubool DeviceObjectIterator::HasObject( ) const
{
	return mCurrentDeviceObjectIndex != -1;
}

_ubool DeviceObjectIterator::MovePrev( )
{
	return _false;
}

_ubool DeviceObjectIterator::MoveNext( )
{
	//// Find the device object by flags
	//for ( _dword i = mCurrentDeviceObjectIndex + 1; i < mDeviceModule->GetDeviceObjectNumber( ); i ++ )
	//{
	//	IDeviceObjectRef next_deviceobject = mDeviceModule->GetDeviceObjectByIndex( i );
	//	EGE_ASSERT( next_deviceobject.IsValid( ) );

	//	// Check the flags to find the desirable device
	//	if ( ( next_deviceobject->GetType( ) & mDeviceFlags ) == 0 )
	//		continue;

	//	// We found it
	//	mCurrentDeviceObjectIndex = i;
	//	return _true;
	//}

	//// Found nothing
	//mCurrentDeviceObjectIndex = -1;

	return _false;
}