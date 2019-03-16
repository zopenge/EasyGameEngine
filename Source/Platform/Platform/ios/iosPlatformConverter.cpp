//! @file     iosPlatformConverter.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Converter Implementation
//----------------------------------------------------------------------------

_chara* Platform::ConvertLongToString( _int value, _dword radix, _chara* string, _dword length )
{
	return anyPlatformConverter::ConvertLongToString( value, radix, string, length );
}

_chara* Platform::ConvertDwordToString( _dword value, _dword radix, _chara* string, _dword length )
{
	return anyPlatformConverter::ConvertDwordToString( value, radix, string, length );
}

_chara* Platform::ConvertLargeToString( _large value, _dword radix, _chara* string, _dword length )
{
	return anyPlatformConverter::ConvertLargeToString( value, radix, string, length );
}

_chara* Platform::ConvertQwordToString( _qword value, _dword radix, _chara* string, _dword length )
{
	return anyPlatformConverter::ConvertQwordToString( value, radix, string, length );
}

_chara* Platform::ConvertFloatToString( _float value, _chara* string, _dword length, _dword precision )
{
	return anyPlatformConverter::ConvertFloatToString( value, string, length, precision );
}

_chara* Platform::ConvertDoubleToString( _double value, _chara* string, _dword length, _dword precision )
{
	return anyPlatformConverter::ConvertDoubleToString( value, string, length, precision );
}

_charw* Platform::ConvertLongToString( _int value, _dword radix, _charw* string, _dword length )
{
	return anyPlatformConverter::ConvertLongToString( value, radix, string, length );
}

_charw* Platform::ConvertDwordToString( _dword value, _dword radix, _charw* string, _dword length )
{
	return anyPlatformConverter::ConvertDwordToString( value, radix, string, length );
}

_charw* Platform::ConvertLargeToString( _large value, _dword radix, _charw* string, _dword length )
{
	return anyPlatformConverter::ConvertLargeToString( value, radix, string, length );
}

_charw* Platform::ConvertQwordToString( _qword value, _dword radix, _charw* string, _dword length )
{
	return anyPlatformConverter::ConvertQwordToString( value, radix, string, length );
}

_charw* Platform::ConvertFloatToString( _float value, _charw* string, _dword length, _dword precision )
{
	return anyPlatformConverter::ConvertFloatToString( value, string, length, precision );
}

_charw* Platform::ConvertDoubleToString( _double value, _charw* string, _dword length, _dword precision )
{
	return anyPlatformConverter::ConvertDoubleToString( value, string, length, precision );
}

_boolean Platform::ConvertStringToBool( const _chara* string )
{
	return anyPlatformConverter::ConvertStringToBool( string );
}

_int Platform::ConvertStringToLong( const _chara* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToLong( string, radix );
}

_dword Platform::ConvertStringToDword( const _chara* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToDword( string, radix );
}

_large Platform::ConvertStringToLarge( const _chara* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToLarge( string, radix );
}

_qword Platform::ConvertStringToQword( const _chara* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToQword( string, radix );
}

_float Platform::ConvertStringToFloat( const _chara* string )
{
	return anyPlatformConverter::ConvertStringToFloat( string );
}

_double Platform::ConvertStringToDouble( const _chara* string )
{
	return anyPlatformConverter::ConvertStringToDouble( string );
}

_boolean Platform::ConvertStringToBool( const _charw* string )
{
	return anyPlatformConverter::ConvertStringToBool( string );
}

_int Platform::ConvertStringToLong( const _charw* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToLong( string, radix );
}

_dword Platform::ConvertStringToDword( const _charw* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToDword( string, radix );
}

_large Platform::ConvertStringToLarge( const _charw* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToLarge( string, radix );
}

_qword Platform::ConvertStringToQword( const _charw* string, _dword radix )
{
	return anyPlatformConverter::ConvertStringToQword( string, radix );
}

_float Platform::ConvertStringToFloat( const _charw* string )
{
	return anyPlatformConverter::ConvertStringToFloat( string );
}

_double Platform::ConvertStringToDouble( const _charw* string )
{
	return anyPlatformConverter::ConvertStringToDouble( string );
}
