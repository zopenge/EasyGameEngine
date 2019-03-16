//! @file     androidPlatform.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidPlatform
//----------------------------------------------------------------------------

class androidPlatform : public TPlatform< IAndroidPlatform >
{
private:
	typedef TPlatform< IAndroidPlatform > BaseClass;

private:
	//!	The copy resources info
	struct CopyResInfo
	{
		androidPlatform*	mPlatform;
		WString				mSourceDirName;
		WString				mTargetDirName;
	};

private:
	//!	When copy the resources from asset directory.
	static _ubool OnCopyResourcesFromAssetDirCallback( const _charw* res_name, _void* parameter );

public:
	androidPlatform( );
	virtual ~androidPlatform( );

// IObserver Interface
public:
	virtual _void 						Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IPlatform Interface
public:
	virtual _ubool						Initialize( ) override;
	virtual _void						Finalize( ) override;

	virtual const PlatformDeviceInfo&	GetDeviceInfo( ) override;

	virtual WStringR					GetIMSI( ) const override;

	virtual _qword						GetCurProcessMemSize( ) const override;
	virtual _qword						GetTotalMemSize( ) const override;

	virtual _void						SetSurfaceFixedSize( const PointU& size ) override;

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

	virtual _ubool						RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer ) override;

// IAndroidPlatform Interface
public:
	virtual JNIEnv*						GetJNIEnv( ) override;

	virtual AStringR					ByteArray2HexString( jbyteArray buffer ) override;

	virtual IInvokerPassRef				CreateJNIObject( AStringPtr path ) override;

	virtual IJ2CArrayPassRef			CreateJ2CArray( jbyteArray buffer ) override;

	virtual IC2JArrayPassRef			CreateC2JArray( _dword size, const _byte* buffer ) override;

	virtual AStringR					ToStringA( jstring string ) override;
	virtual UStringR					ToStringU( jstring string ) override;
	virtual WStringR					ToStringW( jstring string ) override;
	virtual IJ2CStringPassRef			CreateJ2CString( jstring string ) override;

	virtual IC2JStringPassRef			CreateC2JString( AStringPtr string ) override;
	virtual IC2JStringPassRef			CreateC2JString( UStringPtr string ) override;
	virtual IC2JStringPassRef			CreateC2JString( WStringPtr string ) override;
	virtual IC2JStringPassRef			CreateC2JString( const AStringObj& string ) override;
	virtual IC2JStringPassRef			CreateC2JString( const UStringObj& string ) override;
	virtual IC2JStringPassRef			CreateC2JString( const WStringObj& string ) override;

	virtual IC2JStringMapPassRef		CreateC2JStringMap( const Map< UString, UString >& map_object ) override;

	virtual _ubool						CopyFileFromAssetDir( WStringPtr source_file_name, WStringPtr target_file_name ) override;
	virtual _ubool						CopyDirFromAssetDir( WStringPtr source_dir_name, WStringPtr target_dir_name ) override;

	virtual AStringR					GetSignature( ) override;
};

//----------------------------------------------------------------------------
// androidPlatform Implementation
//----------------------------------------------------------------------------

}