//! @file     chromePlatform.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromePlatform
//----------------------------------------------------------------------------

class chromePlatform : public TPlatform< IChromePlatform >
{
private:
	typedef TPlatform< IChromePlatform > BaseClass;

private:
	//!	The chrome module
	chromeModule	mChromeModule;

public:
	chromePlatform( );
	virtual ~chromePlatform( );

// IPlatform Interface
public:
	virtual _ubool						Initialize( ) override;
	virtual _void						Finalize( ) override;

	virtual const PlatformDeviceInfo&	GetDeviceInfo( ) override;

	virtual WString						GetIMSI( ) const override;

	virtual _qword						GetCurProcessMemSize( ) const override;
	virtual _qword						GetTotalMemSize( ) const override;

	virtual WString						GetDumpDirectory( ) const override;

	virtual PointU						GetMainScreenSize( ) const override;
	virtual _ubool						IsScreenOn( ) const override;

	virtual _void						OpenURL( WStringPtr url ) override;

	virtual IStreamReaderPassRef		LoadSystemFont( WStringPtr name ) override;

	virtual IWebViewPassRef				CreateWebView( const PointI& pos, const PointI& size ) override;
	virtual IEditBoxPassRef				CreateEditBox( ) override;
	virtual IMessageBoxPassRef			CreateMessageBox( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const override;

	virtual IAnalyticsCenterPassRef		CreateDummyAnalyticsCenter( UStringPtr app_id ) override;
	virtual IFlurryPassRef				CreateFlurry( UStringPtr app_id ) override;
	virtual IHailstonePassRef			CreateHailstone( UStringPtr app_id, UStringPtr server, UStringPtr channel, UStringPtr accountName ) override;
	virtual IFlurryPassRef				CreateDummyFlurry( UStringPtr app_id ) override;
	virtual IHailstonePassRef			CreateDummyHailstone( UStringPtr app_id, UStringPtr server, UStringPtr channel, UStringPtr accountName ) override;
	virtual ITrackingCenterPassRef		CreateAppCPATrackingCenter( UStringPtr app_id ) override;
	virtual ITrackingCenterPassRef		CreateInMobiTrackingCenter( UStringPtr app_id ) override;
	virtual ITrackingCenterPassRef		CreateTapjoyTrackingCenter( UStringPtr app_id, UStringPtr app_secret_key ) override;
	virtual ITrackingCenterPassRef		CreateAdwordsTrackingCenter( UStringPtr conversion_id, UStringPtr label ) override;
	virtual IUserSystemPassRef			CreateDummyUserSystem( IUserSystemNotifier* notifier ) override;
	virtual IUserSystemPassRef			CreateUserSystem( IUserSystemNotifier* notifier ) override;
	virtual IAdViewPassRef				CreateAdView( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type ) override;

	virtual IKeychainPassRef			CreateKeychain( WStringPtr identifier, WStringPtr access_group ) override;

	virtual IPurchasePassRef			CreateTelecomSMSPurchase( ) override;
	virtual IPurchasePassRef			CreateUnicomSMSPurchase( ) override;
	virtual IPurchasePassRef			CreateMobileSMSPurchase( ) override;
	virtual IPurchasePassRef			CreateNullSMSPurchase( ) override;

	virtual _void						InvokeService( WStringPtr name ) override;
	virtual _ubool						InvokeServiceZ( WStringPtr name ) override;

	virtual _void						Vibrate( _dword duration ) override;
	virtual _void						CancelVibrate( ) override;

	virtual _ubool						RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer ) override;

// IChromePlatform Interface
public:
};

//----------------------------------------------------------------------------
// chromePlatform Implementation
//----------------------------------------------------------------------------

}