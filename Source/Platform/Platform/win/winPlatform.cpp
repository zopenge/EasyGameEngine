//! @file     winPlatform.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// pthread Library Functions Declarations
//----------------------------------------------------------------------------

#if (USE_PTHREAD == 1)

__pthread_attr_init				_pthread_attr_init				= _null;
__pthread_create				_pthread_create					= _null;
__pthread_detach				_pthread_detach					= _null;
__pthread_attr_setdetachstate	_pthread_attr_setdetachstate	= _null;
__pthread_attr_destroy			_pthread_attr_destroy			= _null;
__pthread_self					_pthread_self					= _null;
__pthread_attr_setschedpolicy	_pthread_attr_setschedpolicy	= _null;
__pthread_attr_setschedparam	_pthread_attr_setschedparam		= _null;
__pthread_kill					_pthread_kill					= _null;
__pthread_join					_pthread_join					= _null;

static Library PThreadLibrary;

static _ubool LoadPThreadLibrary( )
{
	if ( PThreadLibrary.Load( L"pthreadVC2.dll" ) == _false )
		return _false;

#define LOAD_FUNC( x ) \
	_##x = (__##x) PThreadLibrary.GetFunction( _WIDEN( #x ) ); \
	if ( _##x == _null ) \
	{ \
		ENABLE_STRING_BUFFER_MACROS_ANSI( ); \
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_BUFFER_1( "Load : '%s' from pthread library [Failed]\n", #x ) ); \
		return _false; \
	}

	LOAD_FUNC( pthread_attr_init );
	LOAD_FUNC( pthread_create );
	LOAD_FUNC( pthread_detach );
	LOAD_FUNC( pthread_attr_setdetachstate );
	LOAD_FUNC( pthread_attr_destroy );
	LOAD_FUNC( pthread_self );
	LOAD_FUNC( pthread_attr_setschedpolicy );
	LOAD_FUNC( pthread_attr_setschedparam );
	LOAD_FUNC( pthread_kill );
	LOAD_FUNC( pthread_join );

	return _true;
}

static _void UnloadPThreadLibrary( )
{
	PThreadLibrary.Free( );
}

#endif

//----------------------------------------------------------------------------
// Platform Implementation
//----------------------------------------------------------------------------

_ubool Platform::Initialize( )
{
	// Make sure some structures used by APIs what must match the size
	EGE_STATIC_ASSERT( sizeof( POINT ) == sizeof( PointI ), "We convert POINT structure by pointer, so the size must match" );

	// Initialize the CRT debug mode
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

	// Initialize COM interface
	::CoInitialize( _null );

	// Initialize window socket
	WSADATA data;
	::WSAStartup( 0x0202, &data );

	// Load pthread SDK
#if (USE_PTHREAD == 1)
	if ( LoadPThreadLibrary( ) == _false )
		return _false;
#endif

	if ( anyPlatform::Initialize( ) == _false )
		return _false;

	return _true;
}

_void Platform::Finalize( )
{
	// Finalize platform
	anyPlatform::Finalize( );

	// Unload pthread SDK
#if (USE_PTHREAD == 1)
	UnloadPThreadLibrary( );
#endif

	// Cleanup window socket
	::WSACleanup( );

	// Finalize COM interface
	::CoUninitialize( );
}
