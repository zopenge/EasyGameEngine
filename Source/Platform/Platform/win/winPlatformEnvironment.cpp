//! @file     winPlatformEnvironment.cpp
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
 if ( !::GetSystemDirectoryW( path, length ) )
  return _false;

 return _true;
}

_ubool Platform::GetSystemFontPath( _charw* path, _dword length )
{
 _charw windows_dir[1024];
 if ( !::GetWindowsDirectoryW( windows_dir, 1024 ) )
  return _false;

 Platform::FormatStringBuffer( path, length, L"%s\\Fonts", windows_dir );

 return _true;
}

_ubool Platform::GetSystemTempPath( _charw* path, _dword length )
{
 ::GetTempPathW( length, path );

 return _true;
}

_ubool Platform::SetEnvironment( const _charw* name, const _charw* value )
{
 if ( name == _null || value == _null )
  return _false;

 return EGE_BOOLEAN( ::SetEnvironmentVariableW( name, value ) );
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
 if ( ::GetEnvironmentVariableW( name, value, length ) == 0 )
  return _false;

 return _true;
}

_ubool Platform::GetEnvironment( const _charw* name, _dword& value )
{
 _charw buffer[1024];
 if ( ::GetEnvironmentVariableW( name, buffer, 1024 ) == 0 )
  return _false;

 value = Platform::ConvertStringToLong( buffer, 10 );

 return _true;
}

_ubool Platform::GetEnvironment( const _charw* name, _void*& value )
{
 _charw buffer[1024];
 if ( ::GetEnvironmentVariableW( name, buffer, 1024 ) == 0 )
  return _false;

 value = (_void*) (_dword) Platform::ConvertStringToLong( buffer, 10 );

 return _true;
}