//! @file     DeviceObject.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DeviceObject Implementation
//----------------------------------------------------------------------------

DeviceObject::DeviceObject( _DEVICE type, WStringPtr path, WStringPtr description ) : mType( type ), mPath( path ), mDescription( description )
{
}

DeviceObject::~DeviceObject( )
{

}

_DEVICE DeviceObject::GetType( ) const
{
	return mType;
}

WStringPtr DeviceObject::GetPath( ) const
{
	return mPath;
}

WStringPtr DeviceObject::GetDescription( ) const
{
	return mDescription;
}