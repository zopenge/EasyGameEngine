//! @file     chromeWebView.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromeWebView Implementation
//----------------------------------------------------------------------------

chromeWebView::chromeWebView( )
{
}

chromeWebView::~chromeWebView( )
{
}

_ubool chromeWebView::Initialize( const PointI& pos, const PointI& size )
{
	mPos	= pos;
	mSize	= size;

	return _true;
}

_void chromeWebView::Show( _ubool show )
{
	if ( mIsShowableObject == show )
		return;

	BaseClass::Show( show );
}

_void chromeWebView::ScrollX( _long position )
{
}

_void chromeWebView::ScrollY( _long position )
{
}

_long chromeWebView::GetScrollPositionX( )
{
	return -1;
}

_long chromeWebView::GetScrollPositionY( )
{
	return -1;
}

_long chromeWebView::GetScrollWidth( )
{
	return -1;
}

_long chromeWebView::GetScrollHeight( )
{
	return -1;
}

_void chromeWebView::SetRegion( const RectI& region )
{
	// Here we skip to check old region, because the chrome's web view can not been see in some cases
	BaseClass::SetRegion( region );
}

_ubool chromeWebView::OpenURL( WStringPtr url_address )
{
	WLOG_TRACE_1( L"Open URL: '%s' ...", url_address.Str( ) );

	if ( BaseClass::OpenURL( url_address ) == _false )
	{
		WLOG_ERROR_1( L"Open URL: '%s' failed", url_address.Str( ) );
		return _false;
	}

	Refresh( );

	WLOG_TRACE_1( L"Open URL: '%s' OK", url_address.Str( ) );

	return _true;
}

_void chromeWebView::Refresh( )
{
	WLOG_TRACE_1( L"Refresh URL: '%s'", mURLAddress.Str( ) );
}