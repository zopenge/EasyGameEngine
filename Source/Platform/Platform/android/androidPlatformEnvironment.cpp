//! @file     androidPlatformEnvironment.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Environment Implementation
//----------------------------------------------------------------------------

_ubool Platform::GetSystemPath( _charw* path, _dword length )
{
	Platform::CopyString( path, L"/system", length );

	return _true;
}

_ubool Platform::GetSystemFontPath( _charw* path, _dword length )
{
	Platform::CopyString( path, L"/system/fonts", length );

	return _true;
}

_ubool Platform::GetSystemTempPath( _charw* path, _dword length )
{
	Platform::CopyString( path, L"/system/temp", length );

	return _true;
}