//! @file     winWebView.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

class WebBrwoser2EventListener;

//----------------------------------------------------------------------------
// winWebView
//----------------------------------------------------------------------------

class winWebView : public TWebView< IWebView >
{
private:
	typedef TWebView< IWebView > BaseClass;

private:
	static CComModule	sComModule;
	static WNDCLASS		sWindowClass;
	static AStringPtr	sWindowClassName;

private:
	HWND						mWindowHandle;

	DWORD						mCookie;
	IConnectionPoint*			mConnectionPoint;
	IConnectionPointContainer*	mConnectionPointContainer;
	WebBrwoser2EventListener*	mEventListener;

	CAxWindow					mWinContainer;
	IWebBrowser2*				mWebBrowser;

	IHTMLDocument2*				mHTMLDoc;
	IHTMLBodyElement*			mHTMLBodyElement;
	IHTMLElement2*				mHTMLElement;
	IHTMLElement2*				mHTMLElement2;

private:
	//!	Create window handle.
	_void CreateWindowHandle( );

private:
	//!	The windows message process.
	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

public:
	winWebView( );
	virtual ~winWebView( );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

public:
	//!	Initialize.
	_ubool Initialize( const PointI& pos, const PointI& size );

	//!	Initialize HTML.
	_ubool InitHTML( );

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
// winWebView Implementation
//----------------------------------------------------------------------------

}