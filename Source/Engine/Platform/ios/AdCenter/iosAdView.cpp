//! @file     iosAdView.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosAdView Implementation
//----------------------------------------------------------------------------

iosAdView::iosAdView( )
{
    mWebBrowserDelegate = &NullEngine::GetInstance( ).GetAdWebBrowserDelegate( );

	mAdViewHandle		= _null;
}

iosAdView::~iosAdView( )
{
}

_ubool iosAdView::Initialize( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type )
{
	mAdViewHandle = NSAdView_Create( app_id, type, viewbased_app->GetApplicationHandle( ), this );
	if ( mAdViewHandle == _null )
		return _false;

	return _true;
}

_void iosAdView::SetWebBrowserDelegate( IAdWebBrowserDelegate* delegate )
{
    if ( delegate == _null )
        mWebBrowserDelegate = &NullEngine::GetInstance( ).GetAdWebBrowserDelegate( );
    else
        mWebBrowserDelegate = delegate;
}

IAdWebBrowserDelegateRef iosAdView::GetWebBrowserDelegate( )
{
    return mWebBrowserDelegate;
}

_void iosAdView::Show( _ubool show )
{
	NSAdView_Show( mAdViewHandle, show );
}