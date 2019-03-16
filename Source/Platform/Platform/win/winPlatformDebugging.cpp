//! @file     winPlatformDebugging.cpp
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
#if (_SHOW_SKIP_ASSERT_DIALOG == 1)
	// Check whether to skip it
	if ( gAssertSkipSrcFileLines.Search( WSrcFileLineInfo( 0, filename, linenumber ) ).IsValid( ) )
		return;
#endif

	// Build the error string
	_charw information[2048];
	Platform::FormatStringBuffer( information, 2048, L"Build Date : %s\r\nFatal : %s\r\n%s:%d\r\n\r\n", 
		_BUILDDATE_W, error, filename, linenumber );

	// Update the information string
	const _charw* instruction = L"\r\n\r\nThe clipboard now contains this text above.\r\n\r\n"
		L"Press ABORT to exit the program immediately.\r\n"
		L"Press RETRY to break if under debugger and abort otherwise.\r\n"
		L"Press IGNORE to ignore the assertion and continue program execution.";

	Platform::AppendString( information, instruction );

	// Show the error dialog
	_int retval = ::MessageBoxW( _null, information, L"EasyGameEngine Diagnose System",
		MB_ABORTRETRYIGNORE | MB_SETFOREGROUND | MB_DEFAULT_DESKTOP_ONLY );

	if ( retval == IDRETRY )
	{
		DebuggerBreak( );
	}
	else if ( retval == IDIGNORE )
	{
		// Show the skip dialog
		_int skip_retval = ::MessageBoxW( _null, L"Do you want to skip it always ?", L"EasyGameEngine Diagnose System",
			MB_OKCANCEL | MB_SETFOREGROUND | MB_DEFAULT_DESKTOP_ONLY );

		if ( skip_retval == IDOK )
		{
#if (_SHOW_SKIP_ASSERT_DIALOG == 1)
			if ( gAssertSkipSrcFileLines.Number( ) == gAssertSkipSrcFileLines.MaxSize( ) - 1 )
				gAssertSkipSrcFileLines.Clear( );

			gAssertSkipSrcFileLines.Append( WSrcFileLineInfo( 0, filename, linenumber ) );
#endif
		}

		return;
	}
	else
	{
		Platform::TerminateProcess( Platform::GetCurrentProcessHandle( ), -1 );
	}
}

_void Platform::OutputDebugString( const _chara* string )
{
	::OutputDebugStringA( string );
}

_void Platform::OutputDebugStringInLine( const _chara* string )
{
	::OutputDebugStringA( string );
	::OutputDebugStringA( "\n" );
}

_void Platform::OutputDebugString( const _charw* string )
{
	::OutputDebugStringW( string );
}

_void Platform::OutputDebugStringInLine( const _charw* string )
{
	::OutputDebugStringW( string );
	::OutputDebugStringW( L"\n" );
}

_ubool Platform::IsDebuggerPresent( )
{
	return ::IsDebuggerPresent( ) != 0;
}

_void Platform::DebuggerBreak( )
{
	__asm int 3
}

_void Platform::WaitForAttach( _dword time )
{
	_dword last_tickcount = Platform::GetCurrentTickCount( );

	while ( _true )
	{
		if ( Platform::IsDebuggerPresent( ) )
		{
			Platform::DebuggerBreak( );
			break;
		}

		if ( time != -1 )
		{
			if ( Platform::GetCurrentTickCount( ) - last_tickcount >= time )
				break;
		}

		Platform::Sleep( 100 );
	}
}
