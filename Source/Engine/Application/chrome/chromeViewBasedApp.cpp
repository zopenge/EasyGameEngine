//! @file     chromeViewBasedApp.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// The Chrome Global Variables And Functions
// --------------------------------------------------------------------------------------------------------------

extern "C"
{

_void RenderBrowserApp( _handle user_data, _long result )
{
	// Continue to process events in the future
	GetPPResourceModule( )->GetPPBCore( )->CallOnMainThread( 0, PP_MakeCompletionCallback( RenderBrowserApp, _null ), 0 );
}

_boolean InitializeBrowserApp( _dword argc, const _chara* argn[], const _chara* argv[] )
{
	return gChromeViewbasedApp.Initialize( argc, argn, argv );
}

_void FinalizeBrowserApp( )
{
	gChromeViewbasedApp.Finalize( );
}

_void BrowserAppChangedView( _ubool is_visible, _ubool is_page_visible, const RectI& rect, const RectI& clip_rect, _float device_scale, _float css_scale, const PointI& scroll_offset )
{
	// Append the changed view message to load application
	ChromeMessageChangedView msg;
	msg.mIsVisible		= is_visible;
	msg.mIsPageVisible	= is_page_visible;
	msg.mRect			= rect;
	msg.mClipRect		= clip_rect;
	msg.mDeviceScale	= device_scale;
	msg.mCSSScale		= css_scale;
	msg.mScrollOffset	= scroll_offset;
	GetModuleManager( )->AddDelayMessage( msg );

	// We just call RenderBrowserApp() if we do not initialized yet
	if ( gChromeViewbasedApp.GetAppStatus( ) != chromeViewBasedApp::_APP_STATUS_INITIALIZED )
		GetPPResourceModule( )->GetPPBCore( )->CallOnMainThread( 0, PP_MakeCompletionCallback( RenderBrowserApp, _null ), 0 );
}

_void BrowserAppChangedFocus( _ubool has_focus )
{
	ChromeMessageChangedFocus msg( has_focus );
	GetModuleManager( )->AddDelayMessage( msg );
}

}

// --------------------------------------------------------------------------------------------------------------
// chromeViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

chromeViewBasedApp::chromeViewBasedApp( ) : BaseClass( _APPLICATION_TYPE_VIEWBASED )
{
	mAppStatus	= _APP_STATUS_UNKNOWN;
}

chromeViewBasedApp::~chromeViewBasedApp( )
{
}

_ubool chromeViewBasedApp::Initialize( _dword argc, const _chara* argn[], const _chara* argv[] )
{
	// Parse the command line
	mCmdLineParser = GetInterfaceFactory( )->CreateCommandLineParser( argc, argn, argv );
	if ( mCmdLineParser.IsNull( ) )
		return _false;

	// Initialize application thread
	if ( mAppThread.Initialize( ) == _false )
		return _false;

	return _true;
}

_void chromeViewBasedApp::Finalize( )
{
	// Finalize application thread
	mAppThread.Finalize( );

	// Reset the status
	SetAppStatus( _APP_STATUS_UNKNOWN );
}

_void chromeViewBasedApp::ProcessLoadMessage( )
{
	// Initialized file system -> Initialized applicatoin delegate
	if ( gChromeViewbasedApp.GetAppStatus( ) == _APP_STATUS_INITIALIZED_FILE_SYSTEM )
	{
		// Tell the delegate to load data by command line
		if ( GetAppDelegate( )->OnLoad( this, mCmdLineParser ) == _false )
		{
			WLOG_ERROR( L"Load chrome application from delegate failed" );
			return;
		}

		// We have initialized
		SetAppStatus( _APP_STATUS_INITIALIZED );
	}
}

_void chromeViewBasedApp::ProcessChangedViewMessage( const ChromeMessageChangedView& message )
{
	// 
}

_void chromeViewBasedApp::ProcessChangedFocusMessage( const ChromeMessageChangedFocus& message )
{
}

_void chromeViewBasedApp::Notify( const MessageBase& message, const IObject* object, const IObservable* generator )
{
	switch ( message.mMsgID )
	{
		case _CHROME_MESSAGE_LOAD:			ProcessLoadMessage( ); break;
		case _CHROME_MESSAGE_CHANGED_VIEW:	ProcessChangedViewMessage( (const ChromeMessageChangedView&) message ); break;
		case _CHROME_MESSAGE_CHANGED_FOCUS:	ProcessChangedFocusMessage( (const ChromeMessageChangedFocus&) message ); break;
		default:
			break;
	}
}

_void chromeViewBasedApp::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
}

_void chromeViewBasedApp::Render( IAppDelegate* app_delegate )
{
	while ( _true )
	{
		// Process delay messages
		GetModuleManager( )->ProcessDelayMessages( );

		// If we have quit or paused it then skip to update it
		if ( IsQuit( ) || HasPaused( ) )
			break;

		// If we do not initialized yet then wait for it
		if ( GetAppStatus( ) != _APP_STATUS_INITIALIZED )
			continue;

		// Get the start tickcount
		static _dword lasttickcount = Platform::GetCurrentTickCount( );

		_dword currtickcount	= Platform::GetCurrentTickCount( );
		_dword elapse			= Math::Max( 1U, currtickcount - lasttickcount );

		if ( elapse != 0 )
		{
			// Update the engine
			EGE_Tick( currtickcount, elapse );

			// Update the application
			Tick( currtickcount, elapse );

			// Tell the application delegate to update
			app_delegate->OnTick( currtickcount, elapse );

			// Clear temporary info
			Memory::GetInstance( ).ClearCurAllocNumber( );
		}

		// Update the last tickcount
		lasttickcount = currtickcount;
	}
}

_handle chromeViewBasedApp::GetApplicationHandle( ) const
{
	return (_handle)GetPPResourceModule( )->GetPPInstance( );
}

_handle chromeViewBasedApp::GetApplicationLayerHandle( ) const
{
	return (_handle)GetPPResourceModule( )->GetPPInstance( );
}

_void chromeViewBasedApp::Show( )
{
}

_void chromeViewBasedApp::Hide( )
{
}

_void chromeViewBasedApp::Quit( )
{
}

_long chromeViewBasedApp::Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser )
{
	EGE_ASSERT( 0 );
	return EXIT_FAILURE;
}

_ubool chromeViewBasedApp::OnBeforeLoadModules( )
{
	return _true;
}

_ubool chromeViewBasedApp::OnAfterLoadModules( )
{
	return _true;
}

_ubool chromeViewBasedApp::SetIcon( _dword id, IStreamReader* stream_reader )
{
	return _true;
}

_void chromeViewBasedApp::Center( )
{
}

_void chromeViewBasedApp::Move( _long delta_x, _long delta_y )
{
}

_void chromeViewBasedApp::SetPos( _dword x, _dword y )
{
}

PointI chromeViewBasedApp::GetPos( ) const
{
	return PointI::cZeroPoint;
}

_void chromeViewBasedApp::SetSize( _dword width, _dword height )
{
}

PointU chromeViewBasedApp::GetSize( ) const
{
	return PointU::cZeroPoint;
}

RectI chromeViewBasedApp::GetRect( ) const
{
	return RectI::cNull;
}

_void chromeViewBasedApp::SetClientSize( _dword width, _dword height, _long* deltawidth, _long* deltaheight )
{
}

RectU chromeViewBasedApp::GetClientRectU( ) const
{
	return RectU::cNull;
}

_dword chromeViewBasedApp::GetAttributes( ) const
{
	return 0;
}

_void chromeViewBasedApp::SetAttributes( _dword attributes )
{
}

_VIEWBASED_APP_ORIENTATION chromeViewBasedApp::GetOrientation( ) const
{
	return _VIEWBASED_APP_ORIENTATION_UNKNOWN;
}

_void chromeViewBasedApp::SetCapture( )
{
}

_void chromeViewBasedApp::ReleaseCapture( )
{
}

_void chromeViewBasedApp::LoadGameCenter( AStringPtr leader_board_id )
{

}

_void chromeViewBasedApp::ShowLeaderBoardDialog( _ubool show )
{

}

_void chromeViewBasedApp::ShowAchievementDialog( _ubool show )
{

}

_void chromeViewBasedApp::LoadAdCenter( AStringPtr app_id, IAdView::_TYPE type )
{

}

IAdViewRef chromeViewBasedApp::GetAdView( )
{
	return _null;
}

_void chromeViewBasedApp::ShowAlertDialog( WStringPtr title, WStringPtr message )
{

}