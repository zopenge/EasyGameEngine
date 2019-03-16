//! @file     iosViewBasedApp.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// iosViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

iosViewBasedApp::iosViewBasedApp( _handle ns_app_handle ) : BaseClass( _APPLICATION_TYPE_VIEWBASED )
{
	mNSAppHandle = ns_app_handle;
}

iosViewBasedApp::~iosViewBasedApp( )
{
}

_void iosViewBasedApp::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
}

_handle iosViewBasedApp::GetApplicationHandle( ) const
{
	return mNSAppHandle;
}

_handle iosViewBasedApp::GetApplicationLayerHandle( ) const
{
	return NSViewBasedApp_GetCAEAGLLayer( mNSAppHandle );
}

_void iosViewBasedApp::Show( )
{
	NSViewBasedApp_Show( mNSAppHandle );
}

_void iosViewBasedApp::Hide( )
{
	NSViewBasedApp_Hide( mNSAppHandle );
}

_int iosViewBasedApp::Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser )
{
	// We should never call this function
	return EXIT_FAILURE;
}

_ubool iosViewBasedApp::SetIcon( _dword id, IStreamReader* stream_reader )
{
	return _true;
}

_void iosViewBasedApp::Center( )
{
	NSViewBasedApp_Center( mNSAppHandle );
}

_void iosViewBasedApp::Move( _int delta_x, _int delta_y )
{

}

_void iosViewBasedApp::SetPos( _dword x, _dword y )
{
	NSViewBasedApp_SetPos( mNSAppHandle, x, y );
}

PointI iosViewBasedApp::GetPos( ) const
{
	return PointI::cZeroPoint;
}

_void iosViewBasedApp::SetSize( _dword width, _dword height )
{
	NSViewBasedApp_SetSize( mNSAppHandle, width, height );
}

PointU iosViewBasedApp::GetSize( ) const
{
	return NSViewBasedApp_GetSize( mNSAppHandle );
}

RectI iosViewBasedApp::GetRect( ) const
{
	return NSViewBasedApp_GetRect( mNSAppHandle );
}

_void iosViewBasedApp::SetClientSize( _dword width, _dword height, _int* deltawidth, _int* deltaheight )
{
	NSViewBasedApp_SetClientSize( mNSAppHandle, width, height, deltawidth, deltaheight );
}

RectU iosViewBasedApp::GetClientRectU( ) const
{
	return NSViewBasedApp_GetClientRect( mNSAppHandle );
}

_dword iosViewBasedApp::GetAttributes( ) const
{
	return 0;
}

_void iosViewBasedApp::SetAttributes( _dword attributes )
{
}

_VIEWBASED_APP_ORIENTATION iosViewBasedApp::GetOrientation( ) const
{
	return _VIEWBASED_APP_ORIENTATION_UNKNOWN;
}

_void iosViewBasedApp::SetCapture( )
{

}

_void iosViewBasedApp::ReleaseCapture( )
{

}