//! @file     chromeAppThread.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//!	The application delegate what be implemented by user
extern "C" IViewBasedAppDelegate* CreateChromeAppDelegate( );

// --------------------------------------------------------------------------------------------------------------
// chromeAppThread Implementation
// --------------------------------------------------------------------------------------------------------------

chromeAppThread::chromeAppThread( )
{
}

chromeAppThread::~chromeAppThread( )
{
	Finalize( );
}

_void chromeAppThread::InitFileSystem( )
{
	// Initialize file system
	EventInitFileSystem event;
	GetModuleManager( )->ProcessEvent( event );
}

_dword chromeAppThread::OnRunThread( const QwordParameters2& parameters )
{
	// Attach the message loop to current thread
	if ( GetPPResourceModule( )->AttachToCurrentThread( ) == _false )
		return -1;

	// Initialize EGE core
	EGE_Initialize( );

	// Create application delegate
	IViewBasedAppDelegate* app_delegate = CreateChromeAppDelegate( );
	EGE_ASSERT( app_delegate != _null );

	// Register application delegate
	GetModuleManager( )->RegisterAppDelegate( app_delegate );

	// Register application as observer
	GetModuleManager( )->RegisterObserver( &gChromeViewbasedApp );

	// Set the main viewbased application
	SetMainViewBasedApp( &gChromeViewbasedApp );

	// Initialize file system
	InitFileSystem( );

	// Run application
	gChromeViewbasedApp.Render( GetAppDelegate( ) );

	return 0;
}

_void chromeAppThread::OnCloseThread( _dword exitcode, const QwordParameters2& parameters )
{
	// All modules power off
	GetModuleManager( )->PowerOff( );

	// Unload the application
	GetAppDelegate( )->OnUnload( );

	// Release viewbased application delegate
	GetModuleManager( )->RegisterAppDelegate( _null );

	// Release all EGE components
	EGE_Finalize( _true, _true );
}

_ubool chromeAppThread::Initialize( )
{
	// Create application background thread
	if ( Create( 0, _false, L"chromeAppThread", QwordParameters2( (_qword)this, _null ) ) == _false )
		return _false;

	return _true;
}

_void chromeAppThread::Finalize( )
{
	Close( _true );
}