//! @file     androidPlatformDebugging.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Debugging Implementation
//----------------------------------------------------------------------------

_void Platform::AssertReport( const _charw* error, const _charw* filename, _dword linenumber )
{
	// Convert error to ANSI string
	_chara error_ansi[8192];
	Platform::Utf16ToAnsi( error_ansi, 8192, error );
	
	// Convert file name to ANSI string
	_chara filename_ansi[8192];
	Platform::Utf16ToAnsi( filename_ansi, 8192, filename );
	
	// Build the information string
	_chara information_ansi[8192];
	Platform::FormatStringBuffer( information_ansi, 8192, "Build Date : %s\r\nAssert : %s\r\n%s:%d\r\n\r\n", 
		_BUILDDATE_A, error_ansi, filename_ansi, linenumber );
	
	// Show the error message
	OutputDebugString( information_ansi );

	// Show the error dialog
	__assert( information_ansi, linenumber, filename_ansi );
}

_void Platform::OutputDebugString( const _chara* string )
{
	const _dword cMaxLengthOutputPreLine = 2048;

	// Get the string length
	_int length = Platform::StringLength( string );

	// Output log by splitting string
	if ( length > cMaxLengthOutputPreLine )
	{
		while ( length > 0 )
		{
			_chara temp_string_buf[ cMaxLengthOutputPreLine + 1 ]; temp_string_buf[ cMaxLengthOutputPreLine ] = 0;
			SafeCopyString( temp_string_buf, string );

			__android_log_write( ANDROID_LOG_INFO, "ege_android_app", temp_string_buf );

			string += cMaxLengthOutputPreLine;
			length -= cMaxLengthOutputPreLine;
		}
	}
	// Output log directly
	else
	{
		__android_log_write( ANDROID_LOG_INFO, "ege_android_app", string );
	}
}

_void Platform::OutputDebugStringInLine( const _chara* string )
{
	OutputDebugString( string );
}

_void Platform::OutputDebugString( const _charw* string )
{
	OutputDebugString( UString( ).FromString( _ENCODING_UTF16, string ).Str( ) );
}

_void Platform::OutputDebugStringInLine( const _charw* string )
{
	OutputDebugString( string );
}

_ubool Platform::IsDebuggerPresent( )
{
	return IsAndroidDebuggerPresent( );
}

_void Platform::DebuggerBreak( )
{
}

_void Platform::WaitForAttach( _dword time )
{
}