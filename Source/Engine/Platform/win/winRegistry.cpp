//! @file     winRegistry.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winRegistry Implementation
//----------------------------------------------------------------------------

winRegistry::winRegistry( ) : mRootKey( _null )
{
}

winRegistry::~winRegistry( )
{
	if ( mRootKey != _null )
		::RegCloseKey( mRootKey );
}

_ubool winRegistry::Initialize( _ROOT_KEY root, WStringPtr keyname )
{
	return ::RegOpenKeyExW( (HKEY) root, keyname.Str( ), 0, KEY_ALL_ACCESS, (HKEY*) &mRootKey ) == 0;
}

_handle winRegistry::GetRootKey( ) const
{
	return mRootKey;
}

_ubool winRegistry::DoesKeyExist( WStringPtr keyname ) const
{
	HKEY subkey = _null;
	if ( ::RegOpenKeyExW( mRootKey, keyname.Str( ), 0, KEY_ALL_ACCESS, &subkey ) != 0 )
		return _false;

	::RegCloseKey( subkey );

	return _true;
}

_handle winRegistry::CreateKey( WStringPtr keyname )
{
	HKEY subkey = _null; _dword disposition = 0;
	if ( ::RegCreateKeyExW( mRootKey, keyname.Str( ), 0, _null, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, _null, &subkey, &disposition ) != 0 )
		return _null;

	return subkey;
}

_ubool winRegistry::DeleteKey( WStringPtr keyname )
{
	return ::RegDeleteKeyW( mRootKey, keyname.Str( ) ) == 0;
}

_ubool winRegistry::DoesValueExist( _handle key, WStringPtr valuename ) const
{
	_dword size = 0;
	return ::RegQueryValueExW( (HKEY) key, valuename.Str( ), _null, _null, _null, &size ) == 0;
}

_ubool winRegistry::ReadValue( _handle key, WStringPtr valuename, _KEY_TYPE& type, _void* buffer, _dword& size ) const
{
	return ::RegQueryValueExW( (HKEY) key, valuename.Str( ), _null, (LPDWORD) &type, (_byte*) buffer, &size ) == 0;
}

_ubool winRegistry::ReadValueString( _handle key, WStringPtr valuename, WString& string ) const
{
	// Read the value string
	_KEY_TYPE type = _TYPE_STRING; _charw buffer[1024]; _dword length = 1024;
	if ( ReadValue( key, valuename.Str( ), type, buffer, length ) == _false )
		return _false;

	string = buffer;

	return _true;
}

_ubool winRegistry::WriteValue( _handle key, WStringPtr valuename, _KEY_TYPE type, const _void* buffer, _dword size )
{
	return ::RegSetValueExW( (HKEY) key, valuename.Str( ), 0, type, (const _byte*) buffer, size ) == 0;
}

_ubool winRegistry::DeleteValue( _handle key, WStringPtr valuename )
{
	return ::RegDeleteValueW( (HKEY) key, valuename.Str( ) ) == 0;
}