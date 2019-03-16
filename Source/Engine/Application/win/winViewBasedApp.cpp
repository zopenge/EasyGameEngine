//! @file     winViewBasedApp.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// Helpful Macros
// --------------------------------------------------------------------------------------------------------------

// Get the mouse button
#define GET_MOUSE_BUTTON( wparam )	\
	( wparam == 0 ? _MB_UNKNOWN : ( ( wparam & MK_LBUTTON ) ? _MB_LEFT : ( ( wparam & MK_MBUTTON ) ? _MB_MIDDLE : _MB_RIGHT ) ) )
// Get the mouse position
#define GET_MOUSE_POS( lparam ) \
	PointI( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) )

// --------------------------------------------------------------------------------------------------------------
// winViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

winViewBasedApp::winViewBasedApp( _CREATION_FLAG flag ) 
{
	mTouchID			= 1;
	mTraceMouseFlag		= _false;

	mAppLoadingTimes	= 0;

	mWindowApp			= _null;

	mCreationFlag		= flag;
}

winViewBasedApp::~winViewBasedApp( )
{
	if ( mWindowApp != _null )
	{
		// Get the window handle
		HWND window_handle = (HWND) mWindowApp->GetApplicationHandle( );
	
		// Destroy window
		if ( window_handle != _null )
		{
			::SetWindowLong( window_handle, GWL_USERDATA, 0 );
			::DestroyWindow( window_handle );
		}

		// Unregister window class
		if ( mWindowClassName.IsEmpty( ) == _false )
			::UnregisterClassA( mWindowClassName.Str( ), ::GetModuleHandleA( _null ) );

		// Delete the window application
		EGE_DELETE( mWindowApp );
	}
}

_ubool winViewBasedApp::HandleEvent( EventBase& event )
{
	// Handle modules message
	if ( GetModuleManager( ) != _null )
		GetModuleManager( )->ProcessEvent( event );

	return event.mHandled;
}

_int winViewBasedApp::WndProc( _handle window_handle, _dword msgid, _dword wparam, _dword lparam )
{
	// Get the user data of view-based application ( it could be null )
	winViewBasedApp* view_app = (winViewBasedApp*) ::GetWindowLong( (HWND) window_handle, GWL_USERDATA );

	// Handle message
	switch ( msgid )
	{
		// When we create the window, the WM_CREATE will be send and we can bind 'this' pointer with window handle
		case WM_CREATE:
		{
			const CREATESTRUCT* createstruct = (const CREATESTRUCT*) lparam;
			EGE_ASSERT( createstruct != _null );

			// Get the self pointer
			::SetWindowLong( (HWND) window_handle, GWL_USERDATA, (LONG) createstruct->lpCreateParams );
		}
		break;

		// Quit the window application
		case WM_CLOSE:
		{
			EventExitApplication exit_app_msg;
			HandleEvent( exit_app_msg );

			if ( exit_app_msg.mHandled )
				return 0; // The application has handle it

			// Post the 'Quit' message to window
			view_app->Quit( );
		}
		break;

		// The client size changed
		case WM_SIZE:
		{
			EventClientSizeChanged message;
			message.mClientSize.x = LOWORD( lparam );
			message.mClientSize.y = HIWORD( lparam );
			message.mRatio.Init( (_float)message.mClientSize.x, (_float)message.mClientSize.y );

			if ( HandleEvent( message ) )
				return 0; // If an application processes this message, it should return zero.
		}
		break;

		// The client size is changing
		case WM_SIZING:
		{
			EventClientSizeChanging message;
			message.mType			= (EventClientSizeChanging::_TYPE) wparam;
			message.mClientRegion	= (RectI*) lparam;
			EGE_ASSERT( message.mClientRegion != _null );

			// Lock size
			if ( view_app->mIsLockSize )
			{
				message.mClientRegion->SetWidth( view_app->mLockedSize.x );
				message.mClientRegion->SetHeight( view_app->mLockedSize.y );
			}

			if ( HandleEvent( message ) )
				return TRUE; // An application should return TRUE if it processes this message.
		}
		break;

		case WM_KILLFOCUS:
		{
			EventEnterBackground message;
			if ( HandleEvent( message ) )
				return 0;
		}
		break;	

		case WM_SETFOCUS:
		{
			view_app->mKeyDownDeferredProcessor.Reset( );

			EventEnterForeground message;
			if ( HandleEvent( message ) )
				return 0;
		}
		break;	

		// Activate/Deactivate application
		case WM_ACTIVATE:
		{
			if ( wparam )
			{
				if ( HandleEvent( EventActivityResume( ) ) )
					return 0;
			}
			else
			{
				if ( HandleEvent( EventActivityPause( ) ) )
					return 0;
			}
		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			::BeginPaint( (HWND) window_handle, &ps );
			::EndPaint( (HWND) window_handle, &ps );

			return 0;
		}
		break;

		// When erase background of windows
		case WM_ERASEBKGND:
		{
			// An application should return nonzero if it erases the background; otherwise, it should return zero.
			return 1;
		}
		break;

		// Key up
		case WM_KEYUP:
		{
			EventKeyUp message;
			message.mKeyCode = wparam;

			// Reset the key down deferred processor
			view_app->mKeyDownDeferredProcessor.Reset( );

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Key down
		case WM_KEYDOWN:
		{
			// Check the key down deferred processor
			if ( view_app->mKeyDownDeferredProcessor.Update( ) == _false )
				return 0;

			EventKeyDown message;
			message.mKeyCode = wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// IME char
		case WM_IME_CHAR:
		{
			if ( wparam > 0x7F )
				view_app->mIMEInputBytes.Push( 2 );
			else
				view_app->mIMEInputBytes.Push( 0 );
		}
		break;

		// Char
		case WM_CHAR:
		{
			// Check the key down deferred processor
			if ( view_app->mKeyDownDeferredProcessor.Update( ) == _false )
				return 0;

			// Check IME character
			if ( view_app->mIMEInputBytes.Number( ) != 0 )
			{
				// The UTF-16 info
				static _chara high_utf16 = 0, low_utf16 = 0;

				// Get the current IME input bytes
				_dword& bytes = view_app->mIMEInputBytes.Top( );

				// UTF-16 (HIGH)
				if ( bytes == 2 )
				{
					high_utf16 = (_chara)wparam;
					bytes --;
				}
				// UTF-16 (LOW)
				else if ( bytes == 1 )
				{
					// UTF-16 Completed
					low_utf16 = (_chara)wparam;
					view_app->mIMEInputBytes.Pop( );

					// Build the UTF-16 code
					_chara code_ansi[] = { high_utf16, low_utf16, 0 }; _charw code_utf16[2];
					Platform::AnsiToUtf16( code_utf16, sizeof( code_utf16 ), code_ansi );

					// Send char message
					EventChar message;
					message.mKeyCode = code_utf16[0];

					if ( HandleEvent( message ) )
						return 0;
				}
			}
			// It's normal character
			else
			{
				EventChar message;
				message.mKeyCode = wparam;

				if ( HandleEvent( message ) )
					return 0;
			}
		}
		break;

		// Mouse move
		case WM_MOUSEMOVE:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Enable mouse trace event
			if ( view_app->mTraceMouseFlag == _false )
			{
				TRACKMOUSEEVENT track_mouse_event;
				track_mouse_event.cbSize	= sizeof( track_mouse_event ); 
				track_mouse_event.dwFlags	= TME_LEAVE; 
				track_mouse_event.hwndTrack = (HWND) window_handle; 
				::TrackMouseEvent( &track_mouse_event ); 

				view_app->mTraceMouseFlag = _true;
			}

			EventMouseMove message;
			message.mButton			= GET_MOUSE_BUTTON( wparam );
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position = message.mPosition;

			// Mouse move message
			HandleEvent( message );

			// Convert to touch pad message
			if ( message.mButton == _MB_LEFT )
			{
				EventTouch touch_msg;
				touch_msg.mEvent		= EventTouch::_EVENT_MOVED;
				touch_msg.mIndex		= 0;
				touch_msg.mTouchID		= view_app->mTouchID;
				touch_msg.mLocation		= PointF( _float( message.mPosition.x ), _float( message.mPosition.y ) );
				touch_msg.mPrevLocation = PointF( _float( message.mPosition.x ) - _float( message.mDeltaPosition.x ), _float( message.mPosition.y ) - _float( message.mDeltaPosition.y ) );
				touch_msg.mTimestamp	= Platform::GetCurrentTickCount( );					
				HandleEvent( touch_msg );
			}
		}
		break;

		// Mouse button up
		case WM_LBUTTONUP:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Release capture of the mouse
			::ReleaseCapture( );

			// Build button up message
			EventMouseButtonUp message;
			message.mButton			= _MB_LEFT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position = message.mPosition;

			// Handle mouse left button up message
			HandleEvent( message );

			// Convert to touch pad message
			EventTouch touch_msg;
			touch_msg.mEvent		= EventTouch::_EVENT_ENDED;
			touch_msg.mIndex		= 0;
			touch_msg.mTouchID		= view_app->mTouchID;
			touch_msg.mLocation		= PointF( _float( message.mPosition.x ), _float( message.mPosition.y ) );
			touch_msg.mPrevLocation = touch_msg.mLocation;
			touch_msg.mTimestamp	= Platform::GetCurrentTickCount( );					
			HandleEvent( touch_msg );
		}
		break;

		case WM_MBUTTONUP:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Release capture of the mouse
			::ReleaseCapture( );

			EventMouseButtonUp message;
			message.mButton			= _MB_MIDDLE;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position = message.mPosition;

			HandleEvent( message );
		}
		break;

		case WM_RBUTTONUP:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Release capture of the mouse
			::ReleaseCapture( );

			EventMouseButtonUp message;
			message.mButton			= _MB_RIGHT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		// Mouse button down
		case WM_LBUTTONDOWN:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Set capture of the mouse
			::SetCapture( (HWND) window_handle );

			// Build button down message
			EventMouseButtonDown message;
			message.mButton			= _MB_LEFT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			// Handle mouse left button down message
			HandleEvent( message );

			// Convert to touch pad message
			EventTouch touch_msg;
			touch_msg.mEvent		= EventTouch::_EVENT_BEGAN;
			touch_msg.mIndex		= 0;
			touch_msg.mTouchID		= ++ view_app->mTouchID;
			touch_msg.mLocation		= PointF( _float( message.mPosition.x ), _float( message.mPosition.y ) );
			touch_msg.mPrevLocation = touch_msg.mLocation;
			touch_msg.mTimestamp	= Platform::GetCurrentTickCount( );					
			HandleEvent( touch_msg );
		}
		break;

		case WM_MBUTTONDOWN:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Set capture of the mouse
			::SetCapture( (HWND) window_handle );

			EventMouseButtonDown message;
			message.mButton			= _MB_MIDDLE;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		case WM_RBUTTONDOWN:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			// Set capture of the mouse
			::SetCapture( (HWND) window_handle );

			EventMouseButtonDown message;
			message.mButton			= _MB_RIGHT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		// Mouse double click
		case WM_LBUTTONDBLCLK:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			EventMouseButtonDoubleClick message;
			message.mButton			= _MB_LEFT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		case WM_RBUTTONDBLCLK:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			EventMouseButtonDoubleClick message;
			message.mButton			= _MB_MIDDLE;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		case WM_MBUTTONDBLCLK:
		{
			static PointI old_position( (_short)LOWORD( lparam ), (_short)HIWORD( lparam ) );

			EventMouseButtonDoubleClick message;
			message.mButton			= _MB_RIGHT;
			message.mPosition		= GET_MOUSE_POS( lparam );
			message.mDeltaPosition	= message.mPosition - old_position;

			old_position			= message.mPosition;

			HandleEvent( message );
		}
		break;

		// Mouse wheel
		case WM_MOUSEWHEEL:
		{
			EventMouseWheel message;
			message.mWheel = GET_WHEEL_DELTA_WPARAM( wparam ) / WHEEL_DELTA;

			HandleEvent( message );
		}
		break;

		// Mouse leave
		case WM_MOUSELEAVE:
		{
			// Let the mouse trace event work
			view_app->mTraceMouseFlag = _false;
		}
		break;

		// Command
		case WM_COMMAND:
		{
			EventCommand message;
			message.wParam	= wparam;
			message.lParam	= lparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Tray icon
		case _EVENT_TRAY:
		{
			EventTray message;
			message.mEvent	= (EventTray::_NOTIFICATION_EVENT) lparam;
			message.mIconID = wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-1 Move
		case MM_JOY1MOVE:
		{
			EventJoystickMove message;
			message.mID			= 0;
			message.mPosition.x = LOWORD( lparam ); 
			message.mPosition.y = HIWORD( lparam );

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-2 Move
		case MM_JOY2MOVE:
		{
			EventJoystickMove message;
			message.mID			= 1;
			message.mPosition.x = LOWORD( lparam ); 
			message.mPosition.y = HIWORD( lparam );

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-1 ZMove
		case MM_JOY1ZMOVE:
		{
			EventJoystickZMove message;
			message.mID			= 0;
			message.mZPosition = LOWORD( lparam ); 

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-2 ZMove
		case MM_JOY2ZMOVE:
		{
			EventJoystickZMove message;
			message.mID			= 1;
			message.mZPosition = LOWORD( lparam ); 

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-1 Button Down
		case MM_JOY1BUTTONDOWN:
		{
			EventJoystickButtonDown message;
			message.mID		= 0;
			message.mFlags	= wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-2 Button Down
		case MM_JOY2BUTTONDOWN:
		{
			EventJoystickButtonDown message;
			message.mID		= 1;
			message.mFlags	= wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-1 Button Up
		case MM_JOY1BUTTONUP:
		{
			EventJoystickButtonUp message;
			message.mID		= 0;
			message.mFlags	= wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Joystick-2 Button Up
		case MM_JOY2BUTTONUP:
		{
			EventJoystickButtonUp message;
			message.mID		= 1;
			message.mFlags	= wparam;

			if ( HandleEvent( message ) )
				return 0;
		}
		break;

		// Unknown message
		default:
			break;
	}

	// Process the default window_app message handle function
	return (_int) ::DefWindowProc( (HWND) window_handle, msgid, wparam, lparam );
}

_void winViewBasedApp::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	mWindowApp->Notify( event, object, generator );
}

_ubool winViewBasedApp::Initialize( )
{
	// Generate unique ID to build class name
	mWindowClassName = UID::CreateUUID( ).ToStringA( );

	// Register window class
	WNDCLASSEXA windowclass		= { sizeof( WNDCLASSEXA ) };
	windowclass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
	windowclass.lpfnWndProc		= (WNDPROC) WndProc;
	windowclass.hInstance		= ::GetModuleHandleA( _null );
	windowclass.hIcon			= ::LoadIcon( _null, IDI_WINLOGO );
	windowclass.hCursor			= ::LoadCursor( _null, IDC_ARROW );
	windowclass.lpszClassName	= mWindowClassName.Str( );
	if ( !::RegisterClassExA( &windowclass ) )
		return _false;

	// Get the window style by creation flag
	_dword style = WS_OVERLAPPED;
	if ( mCreationFlag == _CF_OVERLAPPED )
		style = WS_OVERLAPPEDWINDOW;
	else if ( mCreationFlag == _CF_POPUP )
		style = WS_POPUP;

	style |= WS_CLIPCHILDREN;

	// Create window
	HWND window_handle = ::CreateWindowExA( 0, mWindowClassName.Str( ), "", style, 0, 0, 1, 1, _null, _null, _null, this );
	if ( window_handle == _null )
		return _false;

	// Create window application with handle
	mWindowApp = new winApp( window_handle );

	// Make the window to the center position
	Center( );

	// Set the main viewbased application
	SetMainViewBasedApp( this );

	return _true;
}

_handle winViewBasedApp::GetApplicationHandle( ) const
{
	return mWindowApp->GetApplicationHandle( );
}

_handle winViewBasedApp::GetApplicationLayerHandle( ) const
{
	return mWindowApp->GetApplicationHandle( );
}

_void winViewBasedApp::Show( )
{
	mWindowApp->Show( );
}

_void winViewBasedApp::Hide( )
{
	mWindowApp->Hide( );
}

_void winViewBasedApp::SetTitle( WStringPtr title )
{
	BaseClass::SetTitle( title );

	mWindowApp->SetTitle( title );
}

_void winViewBasedApp::EnableAlwaysOnTop( _ubool enable )
{
	BaseClass::EnableAlwaysOnTop( enable );

	mWindowApp->EnableAlwaysOnTop( enable );
}

_int winViewBasedApp::Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser )
{
	if ( app_delegate == _null )
		return EXIT_FAILURE;

	// Register application as observer
	GetModuleManager( )->RegisterObserver( this );

	// Launch the application
	GetModuleManager( )->ProcessEvent( EventBeforeLaunchApp( ) );
	{
		if ( app_delegate->OnLaunch( this, cmd_parser ) == _false )
			return EXIT_FAILURE;
	}
	GetModuleManager( )->ProcessEvent( EventAfterLaunchApp( ) );

	// Load the application
	EventBeforeLoadApp before_load_app_event;
	GetModuleManager( )->ProcessEvent( before_load_app_event );
	while ( _true )
	{
		_ubool keep_loading = _false;
		if ( app_delegate->OnLoad( this, mAppLoadingTimes ++, keep_loading ) == _false )
		{
			app_delegate->OnUnload( );
			return EXIT_FAILURE;
		}

		if ( keep_loading == _false )
			break;
	}
	EventAfterLoadApp after_load_app_event;
	GetModuleManager( )->ProcessEvent( after_load_app_event );

	// Run the window
	while ( IsQuit( ) == _false )
	{
		// Peek message from queue
		MSG message = {0};
		if ( ::PeekMessage( &message, _null, 0, 0, PM_REMOVE ) )
		{
			::TranslateMessage( &message );
			::DispatchMessage( &message );
		}
		else
		{
			// Get the start tickcount
			if ( mLastTickcount == 0 )
				mLastTickcount = Platform::GetCurrentTickCount( );

			_dword currtickcount	= Platform::GetCurrentTickCount( );
			_dword elapse			= currtickcount - mLastTickcount;

			if ( elapse != 0 )
			{
				// Enlarge the elapse when we are in the low power mode
				if ( IsEnableOptions( _OPTION_LOW_POWER_MODE ) )
				{
					if ( elapse < Random::Gen( 150U, 330U ) )
						continue;
				}

				// Use the slow motion mode to slow down ...
				if ( IsEnableOptions( _OPTION_SLOW_MOTION_MODE ) )
					elapse = 2;

				// Get the limited elapsed time
				_dword limited_elapse = Math::Min( mMaxLimitedElapsedTime, elapse );

				// Process delay messages
				GetModuleManager( )->ProcessDelayEvents( );

				// Update the engine
				EGE_Tick( limited_elapse, elapse );

				// Update the application
				Tick( limited_elapse, elapse );

				// Tell the application delegate to update
				app_delegate->OnTick( limited_elapse, elapse );

				// Clear temporary info
				Memory::GetInstance( ).ClearCurAllocNumber( );

				// Check whether it restart soon
				if ( IsRestart( ) )
					Quit( );
			}

			// Update the last tickcount
			mLastTickcount = currtickcount;

			// Sleep a while
			if ( mSleepTime != -1 )
				Platform::Sleep( mSleepTime );
		}
	}

	// All modules power off
	GetModuleManager( )->PowerOff( );

	// Unload the application
	app_delegate->OnUnload( );

	// Post quit message to window
	::PostQuitMessage( 0 );

	// Check whether need to restart application
	if ( IsRestart( ) )
		return EXIT_RESTART;

	return EXIT_SUCCESS;
}

_void winViewBasedApp::Center( )
{
	mWindowApp->Center( );
}

_void winViewBasedApp::Move( _int delta_x, _int delta_y )
{
	mWindowApp->Move( delta_x, delta_y );
}

_void winViewBasedApp::LockSize( )
{
	BaseClass::LockSize( );
}

_void winViewBasedApp::UnlockSize( )
{
	BaseClass::UnlockSize( );
}

_void winViewBasedApp::SetPos( _dword x, _dword y )
{
	mWindowApp->SetPos( x, y );
}

PointI winViewBasedApp::GetPos( ) const
{
	return mWindowApp->GetPos( );
}

_void winViewBasedApp::SetSize( _dword width, _dword height )
{
	mWindowApp->SetSize( width, height );
}

PointU winViewBasedApp::GetSize( ) const
{
	return mWindowApp->GetSize( );
}

RectI winViewBasedApp::GetRect( ) const
{
	return mWindowApp->GetRect( );
}

_void winViewBasedApp::SetClientSize( _dword width, _dword height, _int* deltawidth, _int* deltaheight )
{
	mWindowApp->SetClientSize( width, height, deltawidth, deltaheight );
}

RectU winViewBasedApp::GetClientRectU( ) const
{
	return mWindowApp->GetClientRectU( );
}

IViewBasedApp::_ORIENTATION winViewBasedApp::GetOrientation( ) const
{
	return mWindowApp->GetOrientation( );
}

_void winViewBasedApp::SetCapture( )
{
	mWindowApp->SetCapture( );
}

_void winViewBasedApp::ReleaseCapture( )
{
	mWindowApp->ReleaseCapture( );
}