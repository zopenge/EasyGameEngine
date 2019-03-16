//! @file     IWebView.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IWebViewNotifier
//----------------------------------------------------------------------------

class IWebViewNotifier : public IObject
{
public:
	//!	When page key up.
	//!	@param		key_id		The key ID, @see _KEY.
	//!	@return		none.
	virtual _void OnPageKeyUp( _dword key_id ) PURE;
	//!	When page key down.
	//!	@param		key_id		The key ID, @see _KEY.
	//!	@return		none.
	virtual _void OnPageKeyDown( _dword key_id ) PURE;

	//!	When page finished.
	//!	@param		url			The URL address.
	//!	@return		none.
	virtual _void OnPageFinished( WStringPtr url ) PURE;
	//!	When page progress changed.
	//!	@param		progress	The progress [0, 100].
	//!	@return		none.
	virtual _void OnProgressChanged( _dword progress ) PURE;
	//!	When page receive error.
	//!	@param		err_code	The error code.
	//!	@param		description	The error description.
	//!	@param		url			The URL address.
	//!	@return		none.
	virtual _void OnReceivedError( _dword err_code, WStringPtr description, WStringPtr url ) PURE;
};

//----------------------------------------------------------------------------
// IWebView
//----------------------------------------------------------------------------

class IWebView : public ITScrollableObject< ITShowableObject< IObject > >
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IWebViewNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IWebViewNotifierRef GetNotifier( ) PURE;

	//!	Set the region.
	//!	@param		region	The region.
	//!	@return		none.
	virtual _void SetRegion( const RectI& region ) PURE;
	//!	Get the region.
	//!	@param		none.
	//!	@return		The region.
	virtual RectI GetRegion( ) const PURE;

	//!	Get the position.
	//!	@param		none.
	//!	@return		The position.
	virtual const PointI& GetPosition( ) const PURE;
	//!	Get the size.
	//!	@param		none.
	//!	@return		The size.
	virtual const PointI& GetSize( ) const PURE;

	//!	Open URL.
	//!	@param		url_address	The URL address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool OpenURL( WStringPtr url_address ) PURE;
    //! Get opened URL address.
    //! @param      none.
    //! @return     The URL address.
    virtual WStringPtr GetURLAddress( ) const PURE;

	//!	Refresh.
	//!	@param		none.
	//!	@return		none.
	virtual _void Refresh( ) PURE;
};

}