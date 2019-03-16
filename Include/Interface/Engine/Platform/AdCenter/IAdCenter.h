//! @file     IAdCenter.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAdWebBrowserDelegate
//----------------------------------------------------------------------------

class IAdWebBrowserDelegate : public IObject
{
public:
	//!	When web browser will appear something.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnWillAppear( ) PURE;
	//!	When web browser did appear something.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnDidAppear( ) PURE;

	//!	When web browser will closed.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnWillClosed( ) PURE;
	//!	When web browser did closed.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnDidClosed( ) PURE;

	//!	When web browser share URL.
	//!	@param		url		The URL address.
	//!	@return		none.
	virtual _void OnShare( WStringPtr url ) PURE;
};

//----------------------------------------------------------------------------
// IAdView
//----------------------------------------------------------------------------

class IAdView : public IObject
{
public:
	//!	The type of view.
	enum _TYPE
	{
	    _TYPE_UNKNOWN,				//! error
	    _TYPE_NORMAL_BANNER,		//! e.g. 320 * 50 ; 320 * 48  iphone banner
	    _TYPE_LARGE_BANNER,			//! e.g. 728 * 90 ; 768 * 110 ipad only
	    _TYPE_MEDIUM_BANNER,		//! e.g. 468 * 60 ; 508 * 80  ipad only
	    _TYPE_RECTANGLE,			//! e.g. 300 * 250; 320 * 270 ipad only
	    _TYPE_FULL_SCREEN,			//! iphone full screen ad
	    _TYPE_IPAD_NORMAL_BANNER,	//! ipad use iphone banner
	};

public:
	//!	Set the web browser delegate.
	//!	@param		delegate	The delegate.
	//!	@return     none.
    virtual _void SetWebBrowserDelegate( IAdWebBrowserDelegate* delegate ) PURE;
	//!	Get the web browser delegate.
	//!	@param		none.
	//!	@return		The delegate.
	virtual IAdWebBrowserDelegateRef GetWebBrowserDelegate( ) PURE;
	
	//!	Show/Hide view.
	//!	@param		show		True indicates show it.
	//!	@return		none.
	virtual _void Show( _ubool show ) PURE;
};

}