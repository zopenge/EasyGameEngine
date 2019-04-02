//! @file     iosPlatformDebugging.cpp
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
	
	// Show the error dialog
	__assert( information_ansi, filename_ansi, linenumber );
}

_void Platform::OutputDebugString( const _chara* string )
{
	GetIOSResourceModule( )->LogA( string );
}

_void Platform::OutputDebugString( const _charw* string )
{
	GetIOSResourceModule( )->LogW( string );
}

_ubool Platform::IsDebuggerPresent( )
{
    // We always output the log on IOS
	return _true;
}

_void Platform::DebuggerBreak( )
{
}

_void Platform::WaitForAttach( _dword time )
{
}