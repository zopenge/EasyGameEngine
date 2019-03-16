//! @file     NSViewBasedApp.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NS-ViewBasedApp Implementation
//----------------------------------------------------------------------------

_handle NSViewBasedApp_GetCAEAGLLayer( _handle app )
{
	NSApplication* ns_app = (__bridge NSApplication*) app;

	return (__bridge _handle)[[ns_app view] layer];
}

_void NSViewBasedApp_Show( _handle app )
{
}

_void NSViewBasedApp_Hide( _handle app )
{
}

_void NSViewBasedApp_Center( _handle app )
{
}

_void NSViewBasedApp_SetPos( _handle app, _dword x, _dword y )
{
}

_void NSViewBasedApp_SetSize( _handle app, _dword width, _dword height )
{
}

PointU NSViewBasedApp_GetSize( _handle app )
{
	// Get the NS-Application
	NSApplication* ns_app = (__bridge NSApplication*) app;
	EGE_ASSERT( ns_app != _null );
	
	// Get the NS-UIView
	NSUIView* ns_view = [ns_app view];//[[ns_app ViewController] UIView];
	EGE_ASSERT( ns_view != _null );

	// Get the UI view frame size
	CGSize frame_size = [ns_view getSize];

	return PointU( frame_size.width, frame_size.height );
}

RectI NSViewBasedApp_GetRect( _handle app )
{
	// Get the size
	PointU size = NSViewBasedApp_GetSize( app );

	// Feedback the screen rectangle
	return RectI( ).InitWithSize( 0, 0, (_int) size.x, (_int) size.y );
}

_void NSViewBasedApp_SetClientSize( _handle app, _dword width, _dword height, _int* deltawidth, _int* deltaheight )
{
}

RectU NSViewBasedApp_GetClientRect( _handle app )
{
	RectI rect = NSViewBasedApp_GetRect( app );
    return RectU( rect.l, rect.t, rect.r, rect.b );
}
