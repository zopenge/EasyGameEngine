//! @file     iosPlatformString.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform String Implementation
//----------------------------------------------------------------------------

_dword Platform::AnsiToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number )
{
	return anyPlatformString::Utf8ToUtf16( buffer, size, string, number );
}

_dword Platform::Utf16ToAnsi( _chara* buffer, _dword size, const _charw* string, _dword number )
{
	return anyPlatformString::Utf16ToUtf8( buffer, size, string, number );
}

_dword Platform::Utf8ToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number )
{
	return anyPlatformString::Utf8ToUtf16( buffer, size, string, number );
}

_dword Platform::Utf16ToUtf8( _chara* buffer, _dword size, const _charw* string, _dword number )
{
	return anyPlatformString::Utf16ToUtf8( buffer, size, string, number );
}

_chara* Platform::FormatStringByArguments( _chara* buffer, _dword size, const _chara* format, ... )
{
	BEGIN_VA_LIST( args, format );
		Platform::FormatStringByVAList( buffer, size, format, args );
	END_VA_LIST( args );

	return buffer;
}

_charw* Platform::FormatStringByArguments( _charw* buffer, _dword size, const _charw* format, ... )
{
	BEGIN_VA_LIST( args, format );
		Platform::FormatStringByVAList( buffer, size, format, args );
	END_VA_LIST( args );

	return buffer;
}

_chara* Platform::FormatStringByVAList( _chara* buffer, _dword size, const _chara* format, _va_list arguments )
{
	return anyPlatformString::FormatStringByVAList( buffer, size, format, arguments );
}

_charw* Platform::FormatStringByVAList( _charw* buffer, _dword size, const _charw* format, _va_list arguments )
{
	return anyPlatformString::FormatStringByVAList( buffer, size, format, arguments );
}

_dword Platform::GetFormatStringLength( const _chara* format, _va_list arguments )
{
	return anyPlatformString::GetFormatStringLength( format, arguments );
}

_dword Platform::GetFormatStringLength( const _charw* format, _va_list arguments )
{
	return anyPlatformString::GetFormatStringLength( format, arguments );
}