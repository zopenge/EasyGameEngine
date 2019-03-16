//! @file     iosAdView.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosAdView
//----------------------------------------------------------------------------

class iosAdView : public TObject< IAdView >
{
private:
	IAdWebBrowserDelegateRef	mWebBrowserDelegate;

	_handle						mAdViewHandle;

public:
	iosAdView( );
	virtual ~iosAdView( );

public:
	_ubool Initialize( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type );

// IAdView Interface
public:
	virtual _void                       SetWebBrowserDelegate( IAdWebBrowserDelegate* delegate ) override;
	virtual IAdWebBrowserDelegateRef    GetWebBrowserDelegate( ) override;

	virtual _void						Show( _ubool show ) override;
};

//----------------------------------------------------------------------------
// iosAdView Implementation
//----------------------------------------------------------------------------

}