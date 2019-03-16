//! @file     chromePlatformDevice.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Device Implementation
//----------------------------------------------------------------------------

_ubool Platform::IsKeyDown( _dword key )
{
	return _false;
}

_ubool Platform::GetCursorPos( _handle window_handle, PointI& pos )
{
	return _true;
}

_ubool Platform::GetSoundCardName( _charw* name, _dword number )
{
	return _true;
}