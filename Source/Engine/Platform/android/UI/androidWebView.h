//! @file     androidWebView.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidWebView
//----------------------------------------------------------------------------

class androidWebView : public TWebView< IWebView >
{
private:
	typedef TWebView< IWebView > BaseClass;

private:
	IInvokerRef	mJNIWebView;

private:
	//!	Initialize JNI web-view.
	_ubool InitJNIWebView( );

public:
	androidWebView( );
	virtual ~androidWebView( );

public:
	//!	Initialize.
	_ubool Initialize( const PointI& pos, const PointI& size );

// IShowableObject Interface
public:
	virtual _void	Show( _ubool show ) override;

// IScrollableObject Interface
public:
	virtual _void	ScrollX( _int position ) override;
	virtual _void	ScrollY( _int position ) override;
	virtual _int	GetScrollPositionX( ) override;
	virtual _int	GetScrollPositionY( ) override;
	virtual _int	GetScrollWidth( ) override;
	virtual _int	GetScrollHeight( ) override;

// IWebView Interface
public:
	virtual _void	SetRegion( const RectI& region ) override;

	virtual _ubool	OpenURL( WStringPtr url_address ) override;

	virtual _void	Refresh( ) override;
};

//----------------------------------------------------------------------------
// androidWebView Implementation
//----------------------------------------------------------------------------

}