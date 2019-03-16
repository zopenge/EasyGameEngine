//! @file     iosPlatform.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosPlatform
//----------------------------------------------------------------------------

class iosPlatform : public TPlatform< IIOSPlatform >
{
private:
	typedef TPlatform< IIOSPlatform > BaseClass;
	
private:
    INTERNAL_HANDLER_DECL( );
    
private:
	//!	Initialize dumper.
	_ubool InitDumper( );

private:
	//!	Get the CG font data.
	static _ubool GetCGFontData( AStringPtr font_name, _byte*& font_buffer, _int& font_buffer_size );

public:
	iosPlatform( );
	virtual ~iosPlatform( );

// IPlatform Interface
public:
	virtual _ubool						Initialize( ) override;
	virtual _void						Finalize( ) override;

	virtual const PlatformDeviceInfo&	GetDeviceInfo( ) override;

	virtual _qword						GetCurProcessMemSize( ) const override;
	virtual _qword						GetTotalMemSize( ) const override;

	virtual PointU						GetMainScreenSize( ) const override;
	virtual _ubool						IsScreenOn( ) const override;

	virtual _void						OpenURL( WStringPtr url ) override;

	virtual IStreamReaderPassRef		LoadSystemFont( WStringPtr name ) override;

	virtual IWebViewPassRef				CreateWebView( const PointI& pos, const PointI& size ) override;
	virtual IEditBoxPassRef				CreateEditBox( ) override;
	virtual IMessageBoxPassRef			CreateMessageBox( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const override;
	virtual IMessageBoxPassRef			CreateMessageBox( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const override;
	
	virtual IAnalyticsCenterPassRef		CreateAnalyticsCenter( UStringPtr app_id ) override;

	virtual IAdViewPassRef				CreateAdView( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type ) override;

	virtual IKeychainPassRef			CreateKeychain( WStringPtr identifier, WStringPtr access_group ) override;

	virtual _void						InvokeService( WStringPtr name ) override;
	virtual _ubool						InvokeServiceZ( WStringPtr name ) override;

	virtual _void						Vibrate( _dword duration ) override;
	virtual _void						CancelVibrate( ) override;

// IIOSPlatform Interface
public:
	virtual IIAPManagerPassRef			CreateIAPManager( ) override;

	virtual _void						RegisterForPushNotification( ) override;
};

//----------------------------------------------------------------------------
// iosPlatform Implementation
//----------------------------------------------------------------------------

}
