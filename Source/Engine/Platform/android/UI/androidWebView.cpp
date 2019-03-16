//! @file     androidWebView.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_2( void, AndroidWebView, OnWebViewPageFinished, jlong handle, jstring url )
{
	androidWebView* web_view = (androidWebView*) handle;
	EGE_ASSERT( web_view != _null );

	WString j_url = J2CString( url ).ToStringW( );

	web_view->GetNotifier( )->OnPageFinished( j_url );
}

JNI_FUNC_2( void, AndroidWebView, OnWebViewProgressChanged, jlong handle, jint progress )
{
	androidWebView* web_view = (androidWebView*) handle;
	EGE_ASSERT( web_view != _null );

	web_view->GetNotifier( )->OnProgressChanged( progress );
}

JNI_FUNC_4( void, AndroidWebView, OnWebViewReceivedError, jlong handle, jint error_code, jstring description, jstring failing_url )
{
	androidWebView* web_view = (androidWebView*) handle;
	EGE_ASSERT( web_view != _null );

	WString j_description = J2CString( description ).ToStringW( );
	WString j_failing_url = J2CString( failing_url ).ToStringW( );

	web_view->GetNotifier( )->OnReceivedError( error_code, j_description, j_failing_url );
}

//----------------------------------------------------------------------------
// androidWebView Implementation
//----------------------------------------------------------------------------

androidWebView::androidWebView( )
{
}

androidWebView::~androidWebView( )
{
	if ( mJNIWebView.IsValid( ) )
		mJNIWebView->CallVoidMethod( "close", "()V" );
}

_ubool androidWebView::InitJNIWebView( )
{
	if ( mJNIWebView.IsNull( ) )
	{
		// We must in main thread
		if ( Platform::IsMainThread( ) == _false )
		{
			WLOG_ERROR_1( L"Init android URL: '%s' webview failed, due to none-main thread", mURLAddress.Str( ) );
			return _false;
		}

		// Initialize JNI interface for web view
		mJNIWebView = androidJNI::GetInstance( ).CreateJNIObject( "com/ege/android/AndroidWebView" );
		if ( mJNIWebView.IsNull( ) )
		{
			WLOG_ERROR_1( L"Init android URL: '%s' webview failed, due to create JNI interface failed", mURLAddress.Str( ) );
			return _false;
		}

		// Initialize web view
		jobject	jni_context	= androidJNI::GetInstance( ).GetContextObj( );
		jobject jni_app_activity = androidJNI::GetInstance( ).GetAppActivity( );
		mJNIWebView->CallVoidMethod( "init", "(JLandroid/content/Context;Landroid/app/Activity;)V", (jlong)this, jni_context, jni_app_activity );

		WLOG_TRACE_1( L"Init android URL: '%s' webview OK", mURLAddress.Str( ) );
	}

	return _true;
}

_ubool androidWebView::Initialize( const PointI& pos, const PointI& size )
{
	mPos	= pos;
	mSize	= size;

	return _true;
}

_void androidWebView::Show( _ubool show )
{
	if ( mIsShowableObject == show )
		return;

	BaseClass::Show( show );

	if ( InitJNIWebView( ) == _false )
		return;

	mJNIWebView->CallVoidMethod( "show", "(Z)V", jboolean( show ) );
}

_void androidWebView::ScrollX( _int position )
{
	if ( InitJNIWebView( ) == _false )
		return;

	mJNIWebView->CallVoidMethod( "scrollX", "(I)V", jint( position ) );
}

_void androidWebView::ScrollY( _int position )
{
	if ( InitJNIWebView( ) == _false )
		return;

	mJNIWebView->CallVoidMethod( "scrollY", "(I)V", jint( position ) );
}

_int androidWebView::GetScrollPositionX( )
{
	if ( InitJNIWebView( ) == _false )
		return -1;

	return mJNIWebView->CallIntMethod( "getScrollX", "()I" );
}

_int androidWebView::GetScrollPositionY( )
{
	if ( InitJNIWebView( ) == _false )
		return -1;

	return mJNIWebView->CallIntMethod( "getScrollY", "()I" );
}

_int androidWebView::GetScrollWidth( )
{
	if ( InitJNIWebView( ) == _false )
		return -1;

	return mJNIWebView->CallIntMethod( "getScrollWidth", "()I" );
}

_int androidWebView::GetScrollHeight( )
{
	if ( InitJNIWebView( ) == _false )
		return -1;

	return mJNIWebView->CallIntMethod( "getScrollHeight", "()I" );
}

_void androidWebView::SetRegion( const RectI& region )
{
	// Here we skip to check old region, because the android's web view can not been see in some cases
	BaseClass::SetRegion( region );

	if ( InitJNIWebView( ) == _false )
		return;

	jint l = region.l;
	jint t = region.t;
	jint r = GetMainViewBasedApp( )->GetSize( ).x - region.r;
	jint b = GetMainViewBasedApp( )->GetSize( ).y - region.b;

	mJNIWebView->CallVoidMethod( "setMargins", "(IIII)V", l, t, r, b );
}

_ubool androidWebView::OpenURL( WStringPtr url_address )
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

_void androidWebView::Refresh( )
{
	if ( InitJNIWebView( ) == _false )
	{
		WLOG_ERROR_1( L"Init android URL: '%s' webview failed", mURLAddress.Str( ) );
		return;
	}

	C2JString js_url( mURLAddress );

	mJNIWebView->CallVoidMethod( "openURL", "(Ljava/lang/String;)V", js_url.ToJString( ) );

	WLOG_TRACE_1( L"Refresh URL: '%s'", mURLAddress.Str( ) );
}