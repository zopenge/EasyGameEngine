//! @file     GraphicVRDevice.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_ENABLE_VR_SOFTWARE == 0)

//----------------------------------------------------------------------------
// GraphicVRDevice Implementation
//----------------------------------------------------------------------------

GraphicVRDevice::GraphicVRDevice( )
{
}

GraphicVRDevice::~GraphicVRDevice( )
{
}

_ubool GraphicVRDevice::Initialize( )
{
	return _true;
}

_void GraphicVRDevice::HandleEvent( EventBase& event )
{

}

_void GraphicVRDevice::Present( )
{
}

_float GraphicVRDevice::GetEyeDistance( _dword index ) const
{
	return GetEyeInfo( index ).mTransform.mTranslate.x;
}

VREyeRHI GraphicVRDevice::GetEyeInfo( _dword index ) const
{
	return gDynamicRHI->GetVREyeInfo( index );
}

#endif