//! @file     winConsoleApp.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// winConsoleApp Implementation
// --------------------------------------------------------------------------------------------------------------

winConsoleApp::winConsoleApp( )
{
}

winConsoleApp::~winConsoleApp( )
{
}

_APPLICATION_TYPE winConsoleApp::GetApplicationType( ) const
{
	return _APPLICATION_TYPE_CONSOLE;
}

_handle winConsoleApp::GetApplicationHandle( ) const
{
	return _null;
}

_handle winConsoleApp::GetApplicationLayerHandle( ) const
{
	return _null;
}

_void winConsoleApp::Show( )
{
}

_void winConsoleApp::Hide( )
{
}

_int winConsoleApp::Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser )
{
	if ( app_delegate == _null )
		return EXIT_FAILURE;

	// Launch the application
	if ( app_delegate->OnLaunch( this, cmd_parser ) == _false )
		return EXIT_FAILURE;

	// Load the application
	_dword loading_times = 0;
	while ( _true )
	{
		_ubool keep_loading = _false;
		if ( app_delegate->OnLoad( this, loading_times, keep_loading ) == _false )
			return EXIT_FAILURE;

		if ( keep_loading == _false )
			break;
	}

	// Receive the user command and handle it
	while ( IsQuit( ) == _false )
	{
		// Receive the user command line
		_charw string[4096]; string[0] = 0;
		std::wcin.getline( string, 4095 );

		// Trim some unused characters
		_dword stringlength = Platform::StringLength( string );
		Platform::TrimStringBoth( string, stringlength, L" \t" );

		// Skip for empty command line
		if ( string[0] == 0 )
			continue;

		// Exit command
		if ( Platform::CompareString( string, L"exit", _true ) == 0 )
		{
			break;
		}
		// Print help info
		else if ( Platform::CompareString( string, L"/?", _true ) == 0 )
		{
			WString help_info = app_delegate->OnGetHelpInfo( );
			if ( help_info.IsEmpty( ) == _false )
				Platform::WriteConsole( help_info.Str( ) );

			continue;
		}

		// Handle the command
		app_delegate->OnHandleCommand( string );
	}

	// Unload the application
	app_delegate->OnUnload( );

	return EXIT_SUCCESS;
}