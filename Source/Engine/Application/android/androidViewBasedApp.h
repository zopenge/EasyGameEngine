//! @file     androidViewBasedApp.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidViewBasedApp
//----------------------------------------------------------------------------

class androidViewBasedApp : public INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp )
{
private:
	typedef INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp ) BaseClass;

private:
	//!	The max touch number
	enum { _MAX_TOUCH_NUMBER = 32 };

	//!	The application status
	enum _APP_STATUS
	{
		_APP_STATUS_INITIALIZING,
		_APP_STATUS_INITIALIZED,
		_APP_STATUS_LOADING,
		_APP_STATUS_LOADED,
		_APP_STATUS_ERROR,
	};

private:
	// The android application info
	struct AndroidAppInfo
	{
		_ubool			mIsNeedResetResources;

		AAssetManager*	mAssetManager;
		AConfiguration*	mConfiguration;

		PointU			mSurfaceSize;

		_dword			mSDKVersion;

		AString			mInternalDataPath;
		AString			mExternalDataPath;
		AString			mPackageName;
		AString			mSourceDir;

		AndroidAppInfo( )
		{
			mIsNeedResetResources	= _false;

			mAssetManager			= _null;
			mConfiguration			= _null;

			mSurfaceSize			= PointU( 0, 0 );

			mSDKVersion				= 0;
		}
	};

	//!	The restart info
	struct RestartInfo
	{
		//!	The current window size
		PointU	mWindowSize;

		RestartInfo( )
		{
			mWindowSize = PointU::cZeroPoint;
		}
	};

private:
	//! The android application info
	AndroidAppInfo	mAndroidAppInfo;
	//!	The android app xml info
	androidAppXML	mAndroidAppXML;

	//!	The application status
	_APP_STATUS		mAppStatus;
	//!	The inited window size
	PointU			mInitedWindowSize;
	//!	The current window size
	PointU			mWindowSize;

	//!	The loading times of initialize application
	_dword			mAppLoadingTimes;

	//!	The channel ID counter
	_dword			mChannelIDCounter;
	//! The channels ID table
	_dword			mChannelIDTable[_MAX_TOUCH_NUMBER];
	//!	The previous mouse/touch position
	PointF			mPrevTouchPositions[_MAX_TOUCH_NUMBER];
	//!	The previous fixed mouse/touch position
	PointF			mPrevFixedTouchPositions[_MAX_TOUCH_NUMBER];

	//!	The restarting backup info to restore
	RestartInfo*	mRestartInfo;

private:
	//!	Reset info.
	EGE_INTERNAL _void ResetInfo( );

	//!	Initialize application info.
	EGE_INTERNAL _void InitAppInfo( );

	//!	Process messages.
	EGE_INTERNAL _void ProcessPauseMessage( );
	EGE_INTERNAL _void ProcessResumeMessage( );
	EGE_INTERNAL _void ProcessStopMessage( );
	EGE_INTERNAL _void ProcessRestartMessage( );
	EGE_INTERNAL _void ProcessStartMessage( );
	EGE_INTERNAL _void ProcessWindowFocusChangedMessage( const AndroidMessageWindowFocusChanged& message );
	EGE_INTERNAL _void ProcessWindowChangeConfigMessage( const AndroidMessageWindowChangeConfig& message );
	EGE_INTERNAL _void ProcessCreateSurfaceMessage( const AndroidMessageCreateSurface& message );
	EGE_INTERNAL _void ProcessResizeSurfaceMessage( const AndroidMessageResizeSurface& message );
	EGE_INTERNAL _void ProcessLowMemoryMessage( );
	EGE_INTERNAL _void ProcessQuitMessage( );

	//!	Render.
	EGE_INTERNAL _void Render( IAppDelegate* app_delegate ); 

public:
	androidViewBasedApp( );
	virtual ~androidViewBasedApp( );

public:
	EGE_GETR_ACCESSOR_CONST( AndroidAppInfo, AndroidAppInfo )

public:
	//!	Restart application.
	EGE_INTERNAL _ubool RestartApp( );

	//!	Handle touch event.
	EGE_INTERNAL _ubool HandleTouchEvent( EventTouch::_EVENT touch_event, _dword touch_id, _float x, _float y );
	//!	Handle sensor changed event.
	EGE_INTERNAL _ubool HandleShakeEvent( );
	EGE_INTERNAL _ubool HandleAccelerometerSensorChangedEvent( _float x, _float y, _float z );
	EGE_INTERNAL _ubool HandleGyroscopeSensorChangedEvent( _float x, _float y, _float z );
	EGE_INTERNAL _ubool HandleOrientationSensorChangedEvent( _float x, _float y, _float z );
	//!	Handle key event.
	EGE_INTERNAL _ubool HandleKeyUpEvent( _dword key_code );
	EGE_INTERNAL _ubool HandleKeyDownEvent( _dword key_code );
	EGE_INTERNAL _ubool HandleKeyLongPressEvent( _dword key_code );
	//!	Handle dispatched key event.
	EGE_INTERNAL _ubool HandleDispatchedKeyEvent( jobject event );
	//!	Handle dispatched generic motion event.
	EGE_INTERNAL _ubool HandleDispatchedGenericMotionEvent( jobject ev );
	//!	Handle enum resource file event.
	EGE_INTERNAL _ubool HandleEnumResFileEvent( jstring path, jlong userData );

	// Initialize android.
	EGE_INTERNAL _void InitializeAndroidApp( );
	// Finalize android.
	EGE_INTERNAL _void FinalizeAndroidApp( );
	// Pause android.
	EGE_INTERNAL _void PauseAndroidApp( );
	// Resume android.
	EGE_INTERNAL _void ResumeAndroidApp( );
	// Stop android.
	EGE_INTERNAL _void StopAndroidApp( );
	// Restart android.
	EGE_INTERNAL _void RestartAndroidApp( );
	// Start android.
	EGE_INTERNAL _void StartAndroidApp( );

	// Window focus changed android.
	EGE_INTERNAL _void WindowFocusChangedAndroidApp( _ubool has_focus );
	// Render android.
	EGE_INTERNAL _void RenderAndroidApp( );
	// Change android config.
	EGE_INTERNAL _void ChangeAndroidAppConfig( AConfiguration* configuration );
	// Create surface.
	EGE_INTERNAL _void CreateSurfaceAndroidApp( );
	// Resize surface.
	EGE_INTERNAL _void ResizeSurfaceAndroidApp( _int width, _int height );
	// When memory is low.
	EGE_INTERNAL _void MemoryLowAndroidApp( );

// IObserver Interface
public:
	virtual _void 						Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IApplication Interface
public:
	virtual _handle						GetApplicationHandle( ) const override;
	virtual _handle						GetApplicationLayerHandle( ) const override;

	virtual _ubool						Verify( AStringPtr key, IStreamReader* stream_reader ) override;

	virtual _void 						Show( ) override;
	virtual _void 						Hide( ) override;

	virtual _void						Quit( ) override;

	virtual _int						Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser ) override;

	virtual _ubool						OnBeforeLoadModules( ) override;
	virtual _ubool						OnAfterLoadModules( ) override;

// IViewBasedApp Interface
public:
	virtual _void 						Center( ) override;
	virtual _void						Move( _int delta_x, _int delta_y ) override;

	virtual _void 						SetPos( _dword x, _dword y ) override;
	virtual PointI						GetPos( ) const override;
	virtual _void 						SetSize( _dword width, _dword height ) override;
	virtual PointU						GetSize( ) const override;
	virtual RectI 						GetRect( ) const override;
	virtual _void 						SetClientSize( _dword width, _dword height, _int* deltawidth = _null, _int* deltaheight = _null ) override;
	virtual RectU 						GetClientRectU( ) const override;

	virtual _dword						GetAttributes( ) const override;
	virtual _void						SetAttributes( _dword attributes ) override;

	virtual _VIEWBASED_APP_ORIENTATION	GetOrientation( ) const override;

	virtual _void 						SetCapture( ) override;
	virtual _void 						ReleaseCapture( ) override;
};

// --------------------------------------------------------------------------------------------------------------
// androidViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

}