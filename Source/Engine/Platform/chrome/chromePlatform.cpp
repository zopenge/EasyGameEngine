//! @file     chromePlatform.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromePlatform Implementation
//----------------------------------------------------------------------------

chromePlatform::chromePlatform( )
{
}

chromePlatform::~chromePlatform( )
{
}

_ubool chromePlatform::Initialize( )
{
	if ( BaseClass::Initialize( ) == _false )
		return _false;

	GetModuleManager( )->RegisterModule( &mChromeModule, 10000 );

	return _true;
}

_void chromePlatform::Finalize( )
{
	GetModuleManager( )->UnregisterModule( &mChromeModule );
}

const PlatformDeviceInfo& chromePlatform::GetDeviceInfo( )
{
	if ( mDeviceInfo.mDeviceName.IsEmpty( ) )
	{
	}

	return BaseClass::GetDeviceInfo( );
}

WString	chromePlatform::GetIMSI( ) const
{
	return L"";
}

_qword chromePlatform::GetCurProcessMemSize( ) const
{
	return 0;
}

_qword chromePlatform::GetTotalMemSize( ) const
{
	return 0;
}

WString	chromePlatform::GetDumpDirectory( ) const
{
	return L"";
}

PointU chromePlatform::GetMainScreenSize( ) const
{
	return PointU::cZeroPoint;
}

_ubool chromePlatform::IsScreenOn( ) const
{
	return _false;
}

_void chromePlatform::OpenURL( WStringPtr url )
{
}

IStreamReaderPassRef chromePlatform::LoadSystemFont( WStringPtr name )
{
	return _null;
}

IWebViewPassRef	chromePlatform::CreateWebView( const PointI& pos, const PointI& size )
{
	chromeWebView* web_view = new chromeWebView( );
	if  ( web_view->Initialize( pos, size ) == _false )
		{ EGE_RELEASE( web_view ); return _null; }

	return web_view;
}

IEditBoxPassRef	chromePlatform::CreateEditBox( )
{
	return new chromeEditBox( );
}

IMessageBoxPassRef chromePlatform::CreateMessageBox( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const
{
	return _null;
}

IAnalyticsCenterPassRef chromePlatform::CreateDummyAnalyticsCenter( UStringPtr app_id )
{
	return new NullAnalyticsCenter( );
}

ITrackingCenterPassRef chromePlatform::CreateAppCPATrackingCenter( UStringPtr app_id )
{
	return new NullTrackingCenter( );
}

ITrackingCenterPassRef chromePlatform::CreateInMobiTrackingCenter( UStringPtr app_id )
{
	return new NullTrackingCenter( );
}

ITrackingCenterPassRef chromePlatform::CreateTapjoyTrackingCenter( UStringPtr app_id, UStringPtr app_secret_key )
{
	return new NullTrackingCenter( );
}

ITrackingCenterPassRef chromePlatform::CreateAdwordsTrackingCenter( UStringPtr conversion_id, UStringPtr label )
{
	return new NullTrackingCenter( );
}

IFlurryPassRef chromePlatform::CreateFlurry( UStringPtr app_id )
{
	return _null;
}

IHailstonePassRef chromePlatform::CreateHailstone( UStringPtr app_id, UStringPtr server, UStringPtr channel, UStringPtr accountName )
{
	return _null;
}

IFlurryPassRef chromePlatform::CreateDummyFlurry( UStringPtr app_id )
{
	return new NullFlurry;
}

IHailstonePassRef chromePlatform::CreateDummyHailstone( UStringPtr app_id, UStringPtr server, UStringPtr channel, UStringPtr accountName )
{
	return new NullHailstone;
}

IUserSystemPassRef chromePlatform::CreateDummyUserSystem( IUserSystemNotifier* notifier )
{
	return new NullUserSystem( );
}

IUserSystemPassRef chromePlatform::CreateUserSystem( IUserSystemNotifier* notifier )
{
	return new NullUserSystem( );
}

IAdViewPassRef chromePlatform::CreateAdView( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type )
{
	return _null;
}

IKeychainPassRef chromePlatform::CreateKeychain( WStringPtr identifier, WStringPtr access_group )
{
	return _null;
}

IPurchasePassRef chromePlatform::CreateTelecomSMSPurchase( )
{
	return _null;
}

IPurchasePassRef chromePlatform::CreateUnicomSMSPurchase( )
{
	return _null;
}

IPurchasePassRef chromePlatform::CreateMobileSMSPurchase( )
{
	return _null;
}

IPurchasePassRef chromePlatform::CreateNullSMSPurchase( )
{
	return new NullPurchase( );
}

_void chromePlatform::InvokeService( WStringPtr name )
{
}

_ubool chromePlatform::InvokeServiceZ( WStringPtr name )
{
	return _true;
}

_void chromePlatform::Vibrate( _dword duration )
{
}

_void chromePlatform::CancelVibrate( )
{
}

_ubool chromePlatform::RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer )
{
	return _false;
}