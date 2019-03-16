//! @file     chromePlatformEnvironment.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Environment Implementation
//----------------------------------------------------------------------------

_ubool Platform::GetSystemPath( _charw* path, _dword length )
{
	return _true;
}

_ubool Platform::GetSystemFontPath( _charw* path, _dword length )
{
	return _true;
}

_ubool Platform::GetSystemTempPath( _charw* path, _dword length )
{
	return _true;
}

_ubool Platform::SetEnvironment( const _charw* name, const _charw* value )
{
	return _false;
}

_ubool Platform::SetEnvironment( const _charw* name, _dword value )
{
	_charw value_string[1024];

	return SetEnvironment( name, Platform::ConvertDwordToString( value, 10, value_string, 1024 ) );
}

_ubool Platform::SetEnvironment( const _charw* name, _void* value )
{
	_charw value_string[1024];

	return SetEnvironment( name, Platform::ConvertDwordToString( (_dword) value, 10, value_string, 1024 ) );
}

_ubool Platform::GetEnvironment( const _charw* name, _charw* value, _dword length )
{
	return _true;
}

_ubool Platform::GetEnvironment( const _charw* name, _dword& value )
{
	return _true;
}

_ubool Platform::GetEnvironment( const _charw* name, _void*& value )
{
	return _true;
}