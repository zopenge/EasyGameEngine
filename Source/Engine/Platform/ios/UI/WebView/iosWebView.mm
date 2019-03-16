//! @file     iosWebView.mm
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosWebView Internal Implementation
//----------------------------------------------------------------------------

struct iosWebView::NSWebViewManager
{
    NSWebView*  mNSWebView;
    
    NSWebViewManager( )
    {
        mNSWebView = nil;
    }
    ~NSWebViewManager( )
    {
        if ( mNSWebView != nil )
        {
            [mNSWebView destroyView];
        }
        mNSWebView = nil;
    }
};

//----------------------------------------------------------------------------
// iosWebView Implementation
//----------------------------------------------------------------------------

iosWebView::iosWebView( )
{
    mNSWebViewManager = new NSWebViewManager;
}

iosWebView::~iosWebView( )
{
    EGE_DELETE( mNSWebViewManager );
}

_void iosWebView::CreateNSWebView( )
{
    if ( mNSWebViewManager->mNSWebView == nil )
    {
        NSApplication* ns_app = (__bridge NSApplication*) GetMainViewBasedApp( )->GetApplicationHandle( );
        
        mNSWebViewManager->mNSWebView = [NSWebView alloc];
        [mNSWebViewManager->mNSWebView initialize: mPos size:mSize parent_view:ns_app.view web_view:this];
    }
}

_ubool iosWebView::Initialize( const PointI& pos, const PointI& size )
{
	mPos	= pos;
	mSize	= size;
    
    return _true;
}

_void iosWebView::Show( _ubool show )
{
	if ( mIsShowableObject == show )
		return;

	BaseClass::Show( show );
    
    CreateNSWebView( );
    [mNSWebViewManager->mNSWebView show: show];
}

_void iosWebView::ScrollX( _int position )
{
}

_void iosWebView::ScrollY( _int position )
{
}

_int iosWebView::GetScrollPositionX( )
{
    return 0;
}

_int iosWebView::GetScrollPositionY( )
{
    return 0;
}

_int iosWebView::GetScrollWidth( )
{
    return 0;
}

_int iosWebView::GetScrollHeight( )
{
    return 0;
}

_void iosWebView::SetRegion( const RectI& region )
{
	if ( GetRegion( ) == region )
		return;

	BaseClass::SetRegion( region );
    
    CreateNSWebView( );
    [mNSWebViewManager->mNSWebView setRegion: region];
}

_ubool iosWebView::OpenURL( WStringPtr url_address )
{
	if ( BaseClass::OpenURL( url_address ) == _false )
		return _false;

	Refresh( );

	return _true;
}

_void iosWebView::Refresh( )
{
    CreateNSWebView( );
    [mNSWebViewManager->mNSWebView openURL: mURLAddress];
}
