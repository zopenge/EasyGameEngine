//! @file     anyPlatformConverter.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformConverter Implementation
//----------------------------------------------------------------------------

_chara* anyPlatformConverter::ConvertLongToString( _int value, _dword radix, _chara* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_)
		::_itoa_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_CHROME_)
		::itoa( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_chara* anyPlatformConverter::ConvertDwordToString( _dword value, _dword radix, _chara* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_)
		::_ultoa_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_CHROME_)
		::utoa( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_chara* anyPlatformConverter::ConvertLargeToString( _large value, _dword radix, _chara* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_i64toa_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_i64toa__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_chara* anyPlatformConverter::ConvertQwordToString( _qword value, _dword radix, _chara* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_ui64toa_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_u64toa__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_chara* anyPlatformConverter::ConvertFloatToString( _float value, _chara* string, _dword length, _dword precision )
{
	return ConvertDoubleToString( (_double) value, string, length, precision );
}

_chara* anyPlatformConverter::ConvertDoubleToString( _double value, _chara* string, _dword length, _dword precision )
{
	if ( string == _null || length == 0 )
		return _null;

#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
	// Convert floating pointer value to string
	_int decpt, sign = 0; _chara value_string[1024];
	::_fcvt_s( value_string, 1024, (_double) value, precision, &decpt, &sign );

	// Get the start address of string
	_chara* des_string = string;

	// Append sign
	if ( sign == 1 )
		(*des_string ++) = '-';

	// Get the end and source address of string
	const _chara* end_string = string + length - 1; // [string, end_string]
	const _chara* src_string = value_string;

	// If the decpt is negative number the insert '0' to the front
	if ( decpt < 0 )
	{
		*des_string ++ = '.';

		for ( _int i = decpt; i < 0; i ++ )
			*des_string ++ = '0';
	}
	else
	{
		// Append integer number
		for ( _int i = 0; i <= decpt; i ++, des_string ++ )
		{
			// Out of bound
			if ( des_string >= end_string )
			{
				*des_string = 0;
				return string;
			}

			if ( i == decpt )
			{
				// Append decimal point
				*des_string = '.';
			}
			else
			{
				*des_string = *src_string ++;
			}
		}
	}

	// Append decimals
	for ( ; ; des_string ++ )
	{
		*des_string = *src_string ++;

		// Out of bound
		if ( des_string >= end_string )
		{
			*des_string = 0;
			return string;
		}

		// Complete
		if ( *des_string == 0 )
			break;
	}
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
	Platform::FormatStringBuffer( string, length, "%lf", value );
#else
		#error "Unknown platform"
#endif

	return string;
}

_charw* anyPlatformConverter::ConvertLongToString( _int value, _dword radix, _charw* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_itow_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_itow__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_charw* anyPlatformConverter::ConvertDwordToString( _dword value, _dword radix, _charw* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_itow_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_utow__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_charw* anyPlatformConverter::ConvertLargeToString( _large value, _dword radix, _charw* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_i64tow_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_i64tow__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_charw* anyPlatformConverter::ConvertQwordToString( _qword value, _dword radix, _charw* string, _dword length )
{
	if ( string == _null || length == 0 )
		return _null;

	if ( value == 0 )
	{
		string[0] = '0';
		string[1] = 0;
	}
	else
	{
#if defined(_PLATFORM_WINDOWS_) || defined(PPAPI)
		::_ui64tow_s( value, string, length, radix );
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_) || defined(NACL)
		::__ege_u64tow__( value, string, radix );
#else
		#error "Unknown platform"
#endif
	}

	return string;
}

_charw* anyPlatformConverter::ConvertFloatToString( _float value, _charw* string, _dword length, _dword precision )
{
	_chara ansi_string_buffer[1024];
	Platform::ConvertFloatToString( value, ansi_string_buffer, length, precision );
	Platform::AnsiToUtf16( string, length, ansi_string_buffer );

	return string;
}

_charw* anyPlatformConverter::ConvertDoubleToString( _double value, _charw* string, _dword length, _dword precision )
{
	_chara ansi_string_buffer[1024];
	Platform::ConvertDoubleToString( value, ansi_string_buffer, length, precision );
	Platform::AnsiToUtf16( string, length, ansi_string_buffer );

	return string;
}

_boolean anyPlatformConverter::ConvertStringToBool( const _chara* string )
{
	if ( string == _null )
		return _false;

	if ( Platform::CompareString( string, "false", _true ) == 0 || Platform::CompareString( string, "0" ) == 0 )
		return _false;

	return _true;
}

_int anyPlatformConverter::ConvertStringToLong( const _chara* string, _dword radix )
{
	if ( string == _null )
		return 0;

	_chara* endpointer = _null;
	return strtol( string, &endpointer, radix );
}

_dword anyPlatformConverter::ConvertStringToDword( const _chara* string, _dword radix )
{
	if ( string == _null )
		return 0;

	_chara* endpointer = _null;
	return strtoul( string, &endpointer, radix );
}

_large anyPlatformConverter::ConvertStringToLarge( const _chara* string, _dword radix )
{
	if ( string == _null )
		return 0;

	_chara* endpointer = _null;
	return strtol( string, &endpointer, radix );
}

_qword anyPlatformConverter::ConvertStringToQword( const _chara* string, _dword radix )
{
	if ( string == _null )
		return 0;

	_chara* endpointer = _null;
	return strtoull( string, &endpointer, radix );
}

_float anyPlatformConverter::ConvertStringToFloat( const _chara* string )
{
	if ( string == _null )
		return 0.0f;

	return static_cast< _float >( atof( string ) );
}

_double anyPlatformConverter::ConvertStringToDouble( const _chara* string )
{
	if ( string == _null )
		return 0.0;

	return atof( string );
}

_boolean anyPlatformConverter::ConvertStringToBool( const _charw* string )
{
	if ( string == _null )
		return _false;

	if ( Platform::CompareString( string, L"false", _true ) == 0 || Platform::CompareString( string, L"0" ) == 0 )
		return _false;

	return _true;
}

_int anyPlatformConverter::ConvertStringToLong( const _charw* string, _dword radix )
{
	if ( string == _null )
		return 0;

	uchar16* endpointer = _null;
	return ::uc_tol( (const uchar16*) string, &endpointer, radix );
}

_dword anyPlatformConverter::ConvertStringToDword( const _charw* string, _dword radix )
{
	if ( string == _null )
		return 0;

	uchar16* endpointer = _null;
	return ::uc_toul( (const uchar16*) string, &endpointer, radix );
}

_large anyPlatformConverter::ConvertStringToLarge( const _charw* string, _dword radix )
{
	if ( string == _null )
		return 0;

	uchar16* endpointer = _null;
	return ::uc_toul( (const uchar16*) string, &endpointer, radix );
}

_qword anyPlatformConverter::ConvertStringToQword( const _charw* string, _dword radix )
{
#ifdef _PLATFORM_WINDOWS_
	if ( string == _null )
		return 0;

	_charw* endpointer = _null;
	return _wcstoui64( string, &endpointer, radix );
#else
	_chara string_ansi[1024];
	Platform::Utf16ToAnsi( string_ansi, 1024, string );

	return ConvertStringToQword( string_ansi, radix );
#endif
}

_float anyPlatformConverter::ConvertStringToFloat( const _charw* string )
{
	if ( string == _null )
		return 0.0f;

	uchar16* endpointer = _null;
	return uc_tof( (const uchar16*) string, &endpointer );
}

_double anyPlatformConverter::ConvertStringToDouble( const _charw* string )
{
	if ( string == _null )
		return 0.0;

	uchar16* endpointer = _null;
	return ::uc_tod( (const uchar16*) string, &endpointer );
}