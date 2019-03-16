//! @file     winApp.cpp
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

// --------------------------------------------------------------------------------------------------------------
// winApp Implementation
// --------------------------------------------------------------------------------------------------------------

winApp::winApp( _handle app_handle )
{
	mWindowHandle = (HWND) app_handle;
}

winApp::~winApp( )
{
}

_void winApp::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	switch ( event.mEventID )
	{
		case _EVENT_SYSCOMMAND:
		{
			const EventSysCommand& sys_command = (const EventSysCommand&) event;

			::SendMessageA( mWindowHandle, WM_SYSCOMMAND, sys_command.mCommandID, sys_command.mParam );
		}
		break;

		default:
			break;
	}
}

_handle winApp::GetApplicationHandle( ) const
{
	return mWindowHandle;
}

_handle winApp::GetApplicationLayerHandle( ) const
{
	return mWindowHandle;
}

_void winApp::Show( )
{
	::ShowWindow( mWindowHandle, SW_SHOW );
}

_void winApp::Hide( )
{
	::ShowWindow( mWindowHandle, SW_HIDE );
}

_void winApp::SetTitle( WStringPtr title )
{
	::SetWindowTextW( mWindowHandle, title.Str( ) );
}

_void winApp::EnableAlwaysOnTop( _ubool enable )
{
	::SetWindowPos( mWindowHandle, enable ? HWND_TOPMOST : HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
}

_int winApp::Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser )
{
	// We can run this application, because the windows handle be provided outside, so we can't control it
	return EXIT_FAILURE;
}

_void winApp::Center( )
{
	// Get the window rect
	RECT windowrect;
	::GetWindowRect( mWindowHandle, &windowrect );

	// Get the window position
	_int x = ( ::GetSystemMetrics( SM_CXSCREEN ) - ( windowrect.right - windowrect.left ) ) / 2;
	_int y = ( ::GetSystemMetrics( SM_CYSCREEN ) - ( windowrect.bottom - windowrect.top ) ) / 2;

	// Make the window to center of the screen
	SetPos( x, y );
}

_void winApp::Move( _int delta_x, _int delta_y )
{
	PointI pos	= GetPos( );
	PointU size	= GetSize( );

	::MoveWindow( mWindowHandle, pos.x + delta_x, pos.y + delta_y, size.x, size.y, _true );
}

_void winApp::SetPos( _dword x, _dword y )
{
	::SetWindowPos( mWindowHandle, HWND_TOP, x, y, 0, 0, SWP_NOSIZE );
}

PointI winApp::GetPos( ) const
{
	RectI rect = GetRect( );

	return PointI( rect.l, rect.t );
}

_void winApp::SetSize( _dword width, _dword height )
{
	::SetWindowPos( mWindowHandle, HWND_TOP, 0, 0, width, height, SWP_NOMOVE );
}

PointU winApp::GetSize( ) const
{
	RectI rect = GetRect( );

	return PointU( rect.GetWidth( ), rect.GetHeight( ) );
}

RectI winApp::GetRect( ) const
{
	// http://msdn.microsoft.com/en-us/library/ms633519(v=vs.85).aspx
	// In conformance with conventions for the RECT structure, the bottom-right coordinates of the returned rectangle are exclusive. 
	// In other words, the pixel at (right, bottom) lies immediately outside the rectangle.
	RectI rect;
	::GetWindowRect( mWindowHandle, (RECT*) &rect );

	return rect;
}

_void winApp::SetClientSize( _dword width, _dword height, _int* deltawidth, _int* deltaheight )
{
	// Set the window size
	SetSize( width, height );

	// Get the client and window rect
	RectI clientrect, windowrect;
	::GetClientRect( mWindowHandle, (RECT*)& clientrect );
	::GetWindowRect( mWindowHandle, (RECT*)& windowrect );

	// Feedback the delta-size
	if ( deltawidth != _null )
		*deltawidth = (_int) width - clientrect.GetWidth( );
	if ( deltaheight != _null )
		*deltaheight = (_int) height - clientrect.GetHeight( );

	// Set the client size with the delta-size
	_int windowwidth	= windowrect.GetWidth( ) + ( (_int) width - clientrect.GetWidth( ) );
	_int windowheight	= windowrect.GetHeight( ) + ( (_int) height - clientrect.GetHeight( ) );
	SetSize( windowwidth, windowheight );
}

RectU winApp::GetClientRectU( ) const
{
	// http://msdn.microsoft.com/en-us/library/ms633503(v=vs.85).aspx
	// In conformance with conventions for the RECT structure, the bottom-right coordinates of the returned rectangle are exclusive. 
	// In other words, the pixel at (right, bottom) lies immediately outside the rectangle.
	RectU rect;
	::GetClientRect( mWindowHandle, (RECT*) &rect );

	return rect;
}

IViewBasedApp::_ORIENTATION winApp::GetOrientation( ) const
{
	return _ORIENTATION_UNKNOWN;
}

_void winApp::SetCapture( )
{
	::SetCapture( mWindowHandle );
}

_void winApp::ReleaseCapture( )
{
	::ReleaseCapture( );
}