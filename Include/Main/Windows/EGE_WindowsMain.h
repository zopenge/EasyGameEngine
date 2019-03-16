//! @file     EGE_WindowsMain.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

// Skip 'msvcrt.lib' link
#ifdef _DEBUG
	#pragma comment( linker, "/nodefaultlib:MSVCRT" )
// Skip 'msvcrtd.lib' link
#else
	#pragma comment( linker, "/nodefaultlib:MSVCRTD" )
#endif

// Skip 'libcmt.lib/libcmtd.lib' link
#pragma comment( linker, "/nodefaultlib:LIBCMT" )
#pragma comment( linker, "/nodefaultlib:LIBCMTD" )

// Console Application
#ifdef _EGE_HOOK_EXCEPTION_
	#define RUN_CONSOLE_APP( x )										\
	_int wmain( _int argc, const _charw* argv[] )						\
	{																	\
		if ( EGE_Initialize( ) == _false )								\
			return EXIT_FAILURE;										\
																		\
		_int ret = EXIT_SUCCESS;										\
		_try															\
		{																\
			ret = RunApp< x >( argc, argv );							\
		}																\
		_except( HandleEGEExceptions( GetExceptionInformation( ) ) )	\
		{																\
		}																\
																		\
		EGE_Finalize( );												\
																		\
		return ret;														\
	}
#else
	#define RUN_CONSOLE_APP( x )					\
	_int wmain( _int argc, const _charw* argv[] )	\
	{												\
		if ( EGE_Initialize( ) == _false )			\
			return EXIT_FAILURE;					\
													\
		_int ret = RunApp< x >( argc, argv );		\
													\
		EGE_Finalize( );							\
													\
		return ret;									\
	}
#endif

// ViewBased Application
#ifdef _EGE_HOOK_EXCEPTION_
	#define RUN_VIEWBASED_APP( creation_flag, x )								\
	_int __stdcall WinMain( HINSTANCE, HINSTANCE, LPSTR cmdline, _int )		\
	{																			\
		_int ret = 0;															\
		_ubool initialized = _false;											\
		while ( _true )															\
		{																		\
			if ( !initialized )													\
			{																	\
				if ( EGE_Initialize( ) == _false )								\
					return EXIT_FAILURE;										\
																				\
				ret = 0;														\
				_try															\
				{																\
					ret = RunApp< x >( creation_flag, cmdline );				\
				}																\
				_except( HandleEGEExceptions( GetExceptionInformation( ) ) )	\
				{																\
				}																\
																				\
				EGE_Finalize( );												\
																				\
				if ( ret != EXIT_RESTART )										\
					break;														\
				else															\
					initialized	= _false;										\
			}																	\
		}																		\
																				\
		return ret;																\
	}
#define RUN_CLIENT_APP( creation_flag, x, client )								\
	_int __stdcall WinMain( HINSTANCE, HINSTANCE, LPSTR cmdline, _int )		\
	{																			\
		_int ret = 0;															\
		_ubool initialized = _false;											\
		while ( _true )															\
		{																		\
			if ( !initialized )													\
			{																	\
				if ( EGE_Initialize( ) == _false )								\
					return EXIT_FAILURE;										\
																				\
				ret = 0;														\
				_try															\
				{																\
					ret = RunClientApp< x, client >( creation_flag, cmdline );	\
				}																\
				_except( HandleEGEExceptions( GetExceptionInformation( ) ) )	\
				{																\
				}																\
																				\
				EGE_Finalize( );												\
																				\
				if ( ret != EXIT_RESTART )										\
					break;														\
				else															\
					initialized	= _false;										\
			}																	\
		}																		\
																				\
		return ret;																\
	}
#else
	#define RUN_VIEWBASED_APP( creation_flag, x )								\
	_int __stdcall WinMain( HINSTANCE, HINSTANCE, LPSTR cmdline, _int )		\
	{																			\
		_int ret = 0;															\
		_ubool initialized = _false;											\
		while ( _true )															\
		{																		\
			if ( !initialized )													\
			{																	\
				if ( EGE_Initialize( ) == _false )								\
					return EXIT_FAILURE;										\
																				\
				ret = RunApp< x >( creation_flag, cmdline );					\
																				\
				EGE_Finalize( );												\
																				\
				if ( ret != EXIT_RESTART )										\
					break;														\
				else															\
					initialized	= _false;										\
			}																	\
		}																		\
																				\
		return ret;																\
	}
	#define RUN_CLIENT_APP( creation_flag, x, client )							\
	_int __stdcall WinMain( HINSTANCE, HINSTANCE, LPSTR cmdline, _int )		\
	{																			\
		_int ret = 0;															\
		_ubool initialized = _false;											\
		while ( _true )															\
		{																		\
			if ( !initialized )													\
			{																	\
				if ( EGE_Initialize( ) == _false )								\
					return EXIT_FAILURE;										\
																				\
				ret = RunClientApp< x, client >( creation_flag, cmdline );		\
																				\
				EGE_Finalize( );												\
																				\
				if ( ret != EXIT_RESTART )										\
					break;														\
				else															\
					initialized	= _false;										\
			}																	\
		}																		\
																				\
		return ret;																\
	}
#endif

//----------------------------------------------------------------------------
// Run application
//----------------------------------------------------------------------------

namespace EGE
{

//!	Handle EGE exceptions.
inline int HandleEGEExceptions( EXCEPTION_POINTERS* exception_pointers )
{
	CallStack call_stack;
	call_stack.Create( exception_pointers );

	for ( CallStack::Iterator it = call_stack.GetHeadIterator( ); it.IsValid( ); it ++ )
	{
		const CallStackFrame& call_stack_frame = it;

		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "%s(%d)\n", call_stack_frame.mFileName, call_stack_frame.mLineNumber ) );
	}

	Platform::DebuggerBreak( );

	// Unless you decide to terminate your process, return EXCEPTION_EXECUTE_HANDLER, so that the execution
	// continues normally after the __except block.
	return EXCEPTION_EXECUTE_HANDLER;
}

//! The multi-arguments application
template< class AppDelegateClass >
_int RunApp( _int argc, const _charw* argv[] )
{
	// Create and register application delegate
	IAppDelegatePassRef app_delegate( new AppDelegateClass( ) );
	GetModuleManager( )->RegisterAppDelegate( app_delegate.GetPtr( ) );

	// Create the application
	IApplicationRef application( GetInterfaceFactory( )->CreateConsoleApplication( ) );
	if ( application.IsNull( ) )
		return EXIT_FAILURE;

	// Parse the optional arguments
	ICommandLineParserPassRef command_line_parser( GetInterfaceFactory( )->CreateCommandLineParser( argc, argv ) );
	if ( command_line_parser.IsNull( ) )
		return EXIT_FAILURE;

	// Run application with command line
	return application->Run( app_delegate.GetPtr( ), command_line_parser.GetPtr( ) );
}

//! The single command line application (ANSI)
template< class AppDelegateClass >
_int RunApp( IViewBasedApp::_CREATION_FLAG creation_flag, const _chara* cmdline )
{
	// Convert command line to UNICODE string
	_charw cmdline_unicode[1024]; cmdline_unicode[0] = 0;
	Platform::AnsiToUtf16( cmdline_unicode, 1024, cmdline );

	// Run application
	return RunApp< AppDelegateClass >( creation_flag, cmdline_unicode );
}

//! The single command line application (UNICODE)
template< class AppDelegateClass >
_int RunApp( IViewBasedApp::_CREATION_FLAG creation_flag, const _charw* cmdline )
{
	// Create and register application delegate
	PassRefPtr< AppDelegateClass > app_delegate( new AppDelegateClass( ) );
	GetModuleManager( )->RegisterAppDelegate( app_delegate.GetPtr( ) );

	// Create the application
	IViewBasedAppRef application = GetInterfaceFactory( )->CreateViewBasedApplication( creation_flag );
	if ( application.IsNull( ) )
		return EXIT_FAILURE;

	// Parse the optional arguments
	ICommandLineParserPassRef command_line_parser( GetInterfaceFactory( )->CreateCommandLineParser( cmdline ) );
	if ( command_line_parser.IsNull( ) )
		return EXIT_FAILURE;

	// Let the main viewbased application to manage it
	application.Clear( );

	// Run application with command line
	return GetMainViewBasedApp( )->Run( app_delegate.GetPtr( ), command_line_parser.GetPtr( ) );
}

//! The single command line application (ANSI)
template< class AppDelegateClass, class ClientClass >
_int RunClientApp( IViewBasedApp::_CREATION_FLAG creation_flag, const _chara* cmdline )
{
	// Convert command line to UNICODE string
	_charw cmdline_unicode[1024]; cmdline_unicode[0] = 0;
	Platform::AnsiToUtf16( cmdline_unicode, 1024, cmdline );

	// Run application
	return RunClientApp< AppDelegateClass, ClientClass >( creation_flag, cmdline_unicode );
}

//! The single command line application (UNICODE)
template< class AppDelegateClass, class ClientClass >
_int RunClientApp( IViewBasedApp::_CREATION_FLAG creation_flag, const _charw* cmdline )
{
	// Create client
	PassRefPtr< ClientClass > client( new ClientClass );

	// Create and register application delegate
	PassRefPtr< AppDelegateClass > app_delegate( new AppDelegateClass( client.GetPtr( ) ) );
	GetModuleManager( )->RegisterAppDelegate( app_delegate.GetPtr( ) );

	// Create the application
	IViewBasedAppRef application = GetInterfaceFactory( )->CreateViewBasedApplication( app_delegate->OnGetTitle( ), app_delegate->OnGetInitialSize( ), creation_flag );
	if ( application.IsNull( ) )
		return EXIT_FAILURE;

	// Parse the optional arguments
	ICommandLineParserPassRef command_line_parser( GetInterfaceFactory( )->CreateCommandLineParser( cmdline ) );
	if ( command_line_parser.IsNull( ) )
		return EXIT_FAILURE;

	// Let the main viewbased application to manage it
	application.Clear( );

	// Run application with command line
	return GetMainViewBasedApp( )->Run( app_delegate.GetPtr( ), command_line_parser.GetPtr( ) );
}

}