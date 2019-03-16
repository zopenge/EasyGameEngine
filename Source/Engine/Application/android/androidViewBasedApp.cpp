//! @file     androidViewBasedApp.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// The Android Activity Global Variables And Functions
// --------------------------------------------------------------------------------------------------------------

//!	The application delegate what be implemented by user
extern "C" IViewBasedAppDelegate* CreateAndroidAppDelegate( );

//----------------------------------------------------------------------------
// JNI-Platform Extern Functions Implementation
//----------------------------------------------------------------------------

extern "C"
{

void QuitAndroidCurProcess( )
{
	androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticVoidMethod( "quitApp", "()V" );
}

bool restartAndroidCurProcess( )
{
	return gAndroidViewbasedApp.RestartApp( );
}

EGE_INTERNAL int GetAndroidSDKVersion( )
{
	return gAndroidViewbasedApp.GetAndroidAppInfo( ).mSDKVersion;
}

EGE_INTERNAL const char* GetAndroidInternalPath( )
{
	return gAndroidViewbasedApp.GetAndroidAppInfo( ).mInternalDataPath.Str( );
}

EGE_INTERNAL const char* GetAndroidExternalPath( )
{
	return gAndroidViewbasedApp.GetAndroidAppInfo( ).mExternalDataPath.Str( );
}

EGE_INTERNAL const char* GetAndroidPackageName( )
{
	return gAndroidViewbasedApp.GetAndroidAppInfo( ).mPackageName.Str( );
}

EGE_INTERNAL AAssetManager* GetAndroidAssetManager( )
{
	return gAndroidViewbasedApp.GetAndroidAppInfo( ).mAssetManager;
}

EGE_INTERNAL bool IsAndroidDebuggerPresent( )
{
	return androidJNI::GetInstance( ).GetAndroidOSDebugObj( ).CallStaticBooleanMethod( "isDebuggerConnected", "()Z" );
}

EGE_INTERNAL bool EnumAndroidResFiles( const wchar_t* sub_dir_name, void* funcpointer, void* parameter )
{
	EventEnumResFile enum_res_file_event;
	enum_res_file_event.mEnumResNameProc	= (Platform::OnEnumResNameProc)funcpointer;
	enum_res_file_event.mParameter			= parameter;

	C2JString js_sub_dir_name( sub_dir_name );

	return androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticBooleanMethod( "listAssetFiles", "(Ljava/lang/String;J)Z", js_sub_dir_name.ToJString( ), (jlong)&enum_res_file_event );
}

}

// --------------------------------------------------------------------------------------------------------------
// androidViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

androidViewBasedApp::androidViewBasedApp( ) : BaseClass( _APPLICATION_TYPE_VIEWBASED )
{
	ResetInfo( );

	mRestartInfo = _null;
}

androidViewBasedApp::~androidViewBasedApp( )
{
	EGE_DELETE( mRestartInfo );
}

_void androidViewBasedApp::ResetInfo( )
{
	mAppStatus			= _APP_STATUS_INITIALIZING;
	mInitedWindowSize	= PointU::cZeroPoint;
	mWindowSize			= PointU::cZeroPoint;

	mAppLoadingTimes	= 0;

	mChannelIDCounter	= 1;
	EGE_INIT_ARRAY( mChannelIDTable );
	EGE_INIT_ARRAY( mPrevTouchPositions );
	EGE_INIT_ARRAY( mPrevFixedTouchPositions );
}

_void androidViewBasedApp::InitAppInfo( )
{
	// Initialize app XML info
	mAndroidAppXML.Initialize( );

	// Update android application info
	mAndroidAppInfo.mAssetManager		= androidJNI::GetInstance( ).GetAssetManager( );
	mAndroidAppInfo.mConfiguration		= androidJNI::GetInstance( ).GetConfiguration( );
	mAndroidAppInfo.mSDKVersion			= androidJNI::GetInstance( ).GetSDKVersion( );
	mAndroidAppInfo.mInternalDataPath	= androidJNI::GetInstance( ).GetInternalDataPath( );
	mAndroidAppInfo.mExternalDataPath	= androidJNI::GetInstance( ).GetExternalDataPath( );
	mAndroidAppInfo.mPackageName		= androidJNI::GetInstance( ).GetPackageName( );
	mAndroidAppInfo.mSourceDir			= androidJNI::GetInstance( ).GetSourceDir( );
}

_void androidViewBasedApp::Render( IAppDelegate* app_delegate )
{
	// Process delay messages
	GetModuleManager( )->ProcessDelayEvents( );

	// If we have quit it then skip to update it
	if ( IsQuit( ) )
		return;

	// Run application delegate
	if ( mAppStatus == _APP_STATUS_LOADED )
	{
		// Get the start tickcount
		if ( mLastTickcount == 0 )
			mLastTickcount = Platform::GetCurrentTickCount( ) - 1; // Make elapse at least 1 ms

		_dword currtickcount	= Platform::GetCurrentTickCount( );
		_dword elapse			= currtickcount - mLastTickcount;

		// Get the limited elapsed time
		_dword limited_elapse = Math::Min( mMaxLimitedElapsedTime, elapse );

		// Update the engine
		EGE_Tick( limited_elapse, elapse );

		// Update the application
		Tick( limited_elapse, elapse );

		// Update application delegate
		app_delegate->OnTick( limited_elapse, elapse );

		// Clear temporary info
		Memory::GetInstance( ).ClearCurAllocNumber( );

		// Update the last tickcount
		mLastTickcount = currtickcount;
	}
	// Load application
	else if ( mAppStatus == _APP_STATUS_LOADING )
	{
		WLOG_TRACE_1( L"Loading application ... (times: %d)", mAppLoadingTimes );

		// Load application
		_ubool keep_loading = _false;
		if ( GetAppDelegate( )->OnLoad( this, mAppLoadingTimes ++, keep_loading ) == _false )
		{
			mAppStatus = _APP_STATUS_ERROR;
			WLOG_ERROR( L"Load android application from delegate failed" );
		}

		// Check whether we need to run application delegate
		if ( keep_loading == _false )
		{
			mAppStatus = _APP_STATUS_LOADED;

			// Tell outside to hide splash image
			JNIObject& activity_obj = androidJNI::GetInstance( ).GetBaseActivityObj( );
			activity_obj.CallStaticVoidMethod( "hideSplashImage", "()V" );

			// Complete load event
			EventAfterLoadApp after_load_app_event;
			GetModuleManager( )->ProcessEvent( after_load_app_event );
		}
	}
	// Restart application complete
	else if ( mRestartInfo != _null )
	{
		mLastTickcount = 0;

		FinalizeAndroidApp( );
		InitializeAndroidApp( );

		WindowFocusChangedAndroidApp( _true );
		CreateSurfaceAndroidApp( );
		ResizeSurfaceAndroidApp( mRestartInfo->mWindowSize.x, mRestartInfo->mWindowSize.y );

		EGE_DELETE( mRestartInfo );
	}

	// Check whether need to restart application
	if ( IsRestart( ) )
		restartAndroidCurProcess( );
}

_ubool androidViewBasedApp::RestartApp( )
{
	OUTPUT_DEBUG_STRING( L"Restart application ..." );

	// Tell outside to show splash image
	JNIObject& activity_obj = androidJNI::GetInstance( ).GetBaseActivityObj( );
	activity_obj.CallStaticVoidMethod( "showSplashImage", "()V" );

	// Backup the internal info
	EGE_DELETE( mRestartInfo );
	mRestartInfo = new RestartInfo( );
	mRestartInfo->mWindowSize = mWindowSize;

	// Reset info
	ResetInfo( );

	// Clear flags to run application again
	mStatus.ClearFlags( _STATUS_IS_QUIT | _STATUS_IS_RESTART );

	OUTPUT_DEBUG_STRING( L"Restart application OK" );

	return _true;
}

_ubool androidViewBasedApp::HandleTouchEvent( EventTouch::_EVENT touch_event, _dword touch_id, _float x, _float y )
{
	// The previous and current position
	PointF& prev_pos		= mPrevTouchPositions[ touch_id ];
	PointF& prev_fixed_pos	= mPrevFixedTouchPositions[ touch_id ];
	PointF  cur_pos( x, y );

	// Skip for the same position move action
	if ( mChannelIDTable[ touch_id ] != 0 )
	{
		if ( touch_event == EventTouch::_EVENT_MOVED && prev_pos == cur_pos )
			return _true;
	}

	// Fix current position
	PointF cur_fixed_pos = ConvertPos( cur_pos );

	// Update the channel ID table if it's begin touch
	if ( touch_event == EventTouch::_EVENT_BEGAN )
		mChannelIDTable[ touch_id ] = mChannelIDCounter ++;

	// Build touch message
	EventTouch touch_msg;
	touch_msg.mEvent		= touch_event;
	touch_msg.mIndex		= touch_id;
	touch_msg.mTouchID		= mChannelIDTable[ touch_id ];
	touch_msg.mLocation		= cur_fixed_pos;
	touch_msg.mPrevLocation = prev_fixed_pos;
	touch_msg.mTimestamp	= Platform::GetCurrentTickCount( );					

	// Update the previous position
	prev_pos		= cur_pos;
	prev_fixed_pos	= cur_fixed_pos;

	// Handle touch message
	GetModuleManager( )->AddDelayEvent( touch_msg );

	return _true;
}

_ubool androidViewBasedApp::HandleShakeEvent( )
{
	EventShakeMotion msg;
	msg.mEvent		= EventShakeMotion::_EVENT_BEGAN;
	msg.mTimestamp	= Platform::GetCurrentTickCount( );

	// Handle shake message
	GetModuleManager( )->AddDelayEvent( msg );

	return _true;
}

_ubool androidViewBasedApp::HandleAccelerometerSensorChangedEvent( _float x, _float y, _float z )
{
	EventAccelerometerSensor msg;
	msg.mTimestamp	= Platform::GetCurrentTickCount( );
	msg.mX			= x;
	msg.mY			= y;
	msg.mZ			= z;

	// Handle acceleration message
	GetModuleManager( )->AddDelayEvent( msg );

	return _true;
}

_ubool androidViewBasedApp::HandleGyroscopeSensorChangedEvent( _float x, _float y, _float z )
{
	EventGyroscopeSensor msg;
	msg.mTimestamp	= Platform::GetCurrentTickCount( );
	msg.mX			= x;
	msg.mY			= y;
	msg.mZ			= z;

	// Handle acceleration message
	GetModuleManager( )->AddDelayEvent( msg );

	return _true;
}

_ubool androidViewBasedApp::HandleOrientationSensorChangedEvent( _float x, _float y, _float z )
{
	EventOrientationSensor msg;
	msg.mTimestamp	= Platform::GetCurrentTickCount( );
	msg.mX			= x;
	msg.mY			= y;
	msg.mZ			= z;

	// Handle acceleration message
	GetModuleManager( )->AddDelayEvent( msg );

	return _true;
}

_ubool androidViewBasedApp::HandleKeyUpEvent( _dword key_code )
{
	EventKeyUp key_up_msg;
	key_up_msg.mKeyCode = key_code;
	GetModuleManager( )->AddDelayEvent( key_up_msg );

	mKeyDownDeferredProcessor.Reset( );

	return key_up_msg.mHandled;
}

_ubool androidViewBasedApp::HandleKeyDownEvent( _dword key_code )
{
	// Add the exit application delay message
	if ( key_code == AKEYCODE_BACK )
	{
		EventExitApplication exit_app_msg;
		GetModuleManager( )->AddDelayEvent( exit_app_msg );

		// We always let the user to handle it, break the android system procession
		return _true;
	}

	// Check The key down deferred processor
	if ( mKeyDownDeferredProcessor.Update( ) == _false )
		return _false;

	EventKeyDown key_down_msg;
	key_down_msg.mKeyCode = key_code;
	GetModuleManager( )->AddDelayEvent( key_down_msg );

	return key_down_msg.mHandled;
}

_ubool androidViewBasedApp::HandleKeyLongPressEvent( _dword key_code )
{
	EventKeyDown key_down_msg;
	key_down_msg.mKeyCode = key_code;
	GetModuleManager( )->AddDelayEvent( key_down_msg );

	return key_down_msg.mHandled;
}

_ubool androidViewBasedApp::HandleDispatchedKeyEvent( jobject event )
{
	EventDispatchedKey msg;
	msg.mEvent = event;
	GetModuleManager( )->AddDelayEvent( msg );

	return msg.mHandled;
}

_ubool androidViewBasedApp::HandleDispatchedGenericMotionEvent( jobject ev )
{
	EventDispatchedGenericMotion msg;
	msg.mEvent = ev;
	GetModuleManager( )->AddDelayEvent( msg );

	return msg.mHandled;
}

_ubool androidViewBasedApp::HandleEnumResFileEvent( jstring path, jlong userData )
{
	EventEnumResFile* enum_res_file_event = (EventEnumResFile*)userData;
	EGE_ASSERT( enum_res_file_event != _null );

	// Get the resource file name
	WString res_filename = J2CString( path ).ToStringW( );

	// Notify outside
	return (*enum_res_file_event->mEnumResNameProc)( res_filename.Str( ), enum_res_file_event->mParameter );
}

_void androidViewBasedApp::ProcessPauseMessage( )
{
	WLOG_TRACE( L"APP_CMD_PAUSE" );

	EventActivityPause activity_pause_msg;
	GetModuleManager( )->ProcessEvent( activity_pause_msg );
}

_void androidViewBasedApp::ProcessResumeMessage( )
{
	WLOG_TRACE( L"APP_CMD_RESUME" );

	EventActivityResume activity_resume_msg;
	GetModuleManager( )->ProcessEvent( activity_resume_msg );
}

_void androidViewBasedApp::ProcessStopMessage( )
{
	WLOG_TRACE( L"APP_CMD_STOP" );

	EventActivityStop message;
	GetModuleManager( )->ProcessEvent( message );
}

_void androidViewBasedApp::ProcessRestartMessage( )
{
	WLOG_TRACE( L"APP_CMD_RESTART" );

	EventActivityRestart message;
	GetModuleManager( )->ProcessEvent( message );
}

_void androidViewBasedApp::ProcessStartMessage( )
{
	WLOG_TRACE( L"APP_CMD_START" );

	EventActivityStart message;
	GetModuleManager( )->ProcessEvent( message );
}

_void androidViewBasedApp::ProcessWindowFocusChangedMessage( const AndroidMessageWindowFocusChanged& message )
{
	// Gain focus
	if ( message.mHasFocus )
	{
		WLOG_TRACE( L"APP_CMD_GAINED_FOCUS" );

		// Reset the key down deferred processor
		mKeyDownDeferredProcessor.Reset( );

		// We enter foreground
		EventEnterForeground message;
		GetModuleManager( )->AddDelayEvent( message );
	}
	// Lost focus
	else
	{
		WLOG_TRACE( L"APP_CMD_LOST_FOCUS" );

		// We enter background
		EventEnterBackground message;
		GetModuleManager( )->ProcessEvent( message );
	}
}

_void androidViewBasedApp::ProcessWindowChangeConfigMessage( const AndroidMessageWindowChangeConfig& message )
{
	mAndroidAppInfo.mConfiguration = message.mConfiguration;
}

_void androidViewBasedApp::ProcessCreateSurfaceMessage( const AndroidMessageCreateSurface& message )
{
	WLOG_TRACE( L"APP_CMD_CREATE_SURFACE" );

	// Load the application if we are in the initializing status ( just call it only once )
	if ( mAppStatus == _APP_STATUS_INITIALIZING )
	{
		// Initialize accelerometer
		GetAccelerometer( )->Initialize( this, 1.0f / 60.0f );

		// Build command line 
		// 'JavaVM' : it's 'JavaVM*' pointer data
		ICommandLineParserRef cmd = GetInterfaceFactory( )->CreateCommandLineParser( FORMAT_WSTRING_1( L"-JavaVM=0x%.16llx", (_qword) androidJNI::GetInstance( ).GetJavaVM( ) ) );

		// Launch application
		EventBeforeLaunchApp before_launch_app_event;
		GetModuleManager( )->ProcessEvent( before_launch_app_event );
		{
			if ( GetAppDelegate( )->OnLaunch( this, cmd ) == _false )
			{
				WLOG_ERROR( L"Launch android application from delegate failed" );
			}
		}
		EventAfterLaunchApp after_launch_app_event;
		GetModuleManager( )->ProcessEvent( after_launch_app_event );

		EventBeforeLoadApp before_load_app_event;
		GetModuleManager( )->ProcessEvent( before_load_app_event );

		// The application has initialized, then we need to load it
		mAppStatus = _APP_STATUS_LOADING;
	}
	// Reset resources
	else
	{
		WLOG_TRACE( L"Resetting android resources ..." );

		// Unload resources
		EGE_UnloadResources( );

		// Reset resources
		if ( EGE_ResetResources( ) == _false )
		{
			WLOG_ERROR( L"Reset android resources failed" );
		}					

		WLOG_TRACE( L"Resetting android resources OK" );
	}

	// Notify create surface
	EventSurfaceCreate surface_create_msg;
	GetModuleManager( )->AddDelayEvent( surface_create_msg );
}

_void androidViewBasedApp::ProcessResizeSurfaceMessage( const AndroidMessageResizeSurface& message )
{
	mRatio.UpdateSize( (_float)message.mWidth, (_float)message.mHeight );

	WLOG_TRACE_3( L"APP_CMD_WINDOW_RESIZED: (scale: %f, size: %dx%d)", mRatio.mScale, message.mWidth, message.mHeight );

	SetSize( message.mWidth, message.mHeight );

	EventClientSizeChanged size_changed_message;
	size_changed_message.mClientSize.x = message.mWidth;
	size_changed_message.mClientSize.y = message.mHeight;
	if ( IsEnableOptions( _OPTION_KEEP_RATIO ) )
		size_changed_message.mRatio = mRatio;
	else
		size_changed_message.mRatio = Ratio::cNull;

	GetModuleManager( )->AddDelayEvent( size_changed_message );
}

_void androidViewBasedApp::ProcessLowMemoryMessage( )
{
	WLOG_TRACE( L"APP_CMD_LOW_MEMORY" );

	EventLowMemory message;
	GetModuleManager( )->ProcessEvent( message );
}

_void androidViewBasedApp::ProcessQuitMessage( )
{
	WLOG_TRACE( L"APP_CMD_QUIT" );

	BaseClass::Quit( );

	// Finalize android application
	FinalizeAndroidApp( );

	// Quit application
	QuitAndroidCurProcess( );
}

_void androidViewBasedApp::InitializeAndroidApp( )
{
	// Initialize EGE core
	EGE_Initialize( );

	// Initialize application info
	InitAppInfo( );

	// Create application delegate
	IViewBasedAppDelegate* app_delegate = CreateAndroidAppDelegate( );
	EGE_ASSERT( app_delegate != _null );

	// Register application delegate
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Register application delegate : 0x%.16llx ...", (_qword) app_delegate ) );
	GetModuleManager( )->RegisterAppDelegate( app_delegate );
	OUTPUT_DEBUG_STRING( "Register application delegate OK" );

	// Register application as observer
	GetModuleManager( )->RegisterObserver( &gAndroidViewbasedApp );

	// Update application info
	mInitedWindowSize = static_cast< IViewBasedAppDelegate* >( GetAppDelegate( ) )->OnGetInitialSize( );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "The application initial window size: %dx%d", mInitedWindowSize.x, mInitedWindowSize.y ) );

	// Set the main viewbased application
	SetMainViewBasedApp( &gAndroidViewbasedApp );
}

_void androidViewBasedApp::FinalizeAndroidApp( )
{
	OUTPUT_DEBUG_STRING( L"Going to terminate android view-based application ..." );

	// All modules power off
	GetModuleManager( )->PowerOff( );

	// Unload the application
	OUTPUT_DEBUG_STRING( L"FinalizeAndroidApp: Unloading android view-based application ..." );
	GetAppDelegate( )->OnUnload( );
	OUTPUT_DEBUG_STRING( L"FinalizeAndroidApp: Unload android view-based application OK" );

	// Release viewbased application delegate
	OUTPUT_DEBUG_STRING( L"FinalizeAndroidApp: Releasing android view-based application ..." );
	GetModuleManager( )->RegisterAppDelegate( _null );
	OUTPUT_DEBUG_STRING( L"FinalizeAndroidApp: Release android view-based application OK" );

	// Release all EGE components
	EGE_Finalize( );

	OUTPUT_DEBUG_STRING( L"Terminate android view-based application OK" );
}

_void androidViewBasedApp::PauseAndroidApp( )
{
	ProcessPauseMessage( );
}

_void androidViewBasedApp::ResumeAndroidApp( )
{
	ProcessResumeMessage( );
}

_void androidViewBasedApp::StopAndroidApp( )
{
	ProcessStopMessage( );
}

_void androidViewBasedApp::RestartAndroidApp( )
{
	AndroidMessageRestart msg;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::StartAndroidApp( )
{
	AndroidMessageStart msg;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::WindowFocusChangedAndroidApp( _ubool has_focus )
{
	AndroidMessageWindowFocusChanged msg;
	msg.mHasFocus = has_focus;

	// The application delegate could be null when this message send before create application
	if ( gAppDelegate == _null )
		GetModuleManager( )->AddDelayEvent( msg );
	else
		ProcessWindowFocusChangedMessage( msg );
}

_void androidViewBasedApp::RenderAndroidApp( )
{
	Render( GetAppDelegate( ) );
}

_void androidViewBasedApp::ChangeAndroidAppConfig( AConfiguration* configuration )
{
	AndroidMessageWindowChangeConfig msg;
	msg.mConfiguration = configuration;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::CreateSurfaceAndroidApp( )
{
	AndroidMessageCreateSurface msg;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::ResizeSurfaceAndroidApp( _int width, _int height )
{
	AndroidMessageResizeSurface msg;
	msg.mWidth	= width;
	msg.mHeight	= height;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::MemoryLowAndroidApp( )
{
	AndroidMessageMemoryLow msg;
	GetModuleManager( )->AddDelayEvent( msg );
}

_void androidViewBasedApp::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	switch ( event.mEventID )
	{
		case _ANDROID_MESSAGE_PAUSE:				ProcessPauseMessage( ); break;
		case _ANDROID_MESSAGE_RESUME:				ProcessResumeMessage( ); break;
		case _ANDROID_MESSAGE_STOP:					ProcessStopMessage( ); break;
		case _ANDROID_MESSAGE_RESTART:				ProcessRestartMessage( ); break;
		case _ANDROID_MESSAGE_START:				ProcessStartMessage( ); break;
		case _ANDROID_MESSAGE_WINDOW_FOCUS_CHANGED: ProcessWindowFocusChangedMessage( (const AndroidMessageWindowFocusChanged&) event ); break;
		case _ANDROID_MESSAGE_WINDOW_CHANGE_CONFIG: ProcessWindowChangeConfigMessage( (const AndroidMessageWindowChangeConfig&) event ); break;
		case _ANDROID_MESSAGE_CREATE_SURFACE:		ProcessCreateSurfaceMessage( (const AndroidMessageCreateSurface&) event ); break;
		case _ANDROID_MESSAGE_RESIZE_SURFACE:		ProcessResizeSurfaceMessage( (const AndroidMessageResizeSurface&) event ); break;
		case _ANDROID_MESSAGE_MEMORY_LOW:			ProcessLowMemoryMessage( ); break;
		case _ANDROID_MESSAGE_QUIT:					ProcessQuitMessage( ); break;
		default:
			break;
	}
}

_handle androidViewBasedApp::GetApplicationHandle( ) const
{
	return (_handle)this;
}

_handle androidViewBasedApp::GetApplicationLayerHandle( ) const
{
	return (_handle)this;
}

_ubool androidViewBasedApp::Verify( AStringPtr key, IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

#if (_ANDROID_SKIP_CRACKER_CHECK == 0)
	if ( mAndroidAppXML.LoadConfigure( key, stream_reader ) == _false )
		return _false;

	// Check validations
	return mAndroidAppXML.IsValid( );
#else
	// Alway pass it ...
	return _true;
#endif
}

_void androidViewBasedApp::Show( )
{
}

_void androidViewBasedApp::Hide( )
{
}

_void androidViewBasedApp::Quit( )
{
	AndroidMessageQuit msg;
	GetModuleManager( )->AddDelayEvent( msg );
}

_int androidViewBasedApp::Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser )
{
	EGE_ASSERT( 0 );
	return EXIT_FAILURE;
}

_ubool androidViewBasedApp::OnBeforeLoadModules( )
{
	// Initialize ratio if we enable to keep it
	if ( IsEnableOptions( _OPTION_KEEP_RATIO ) )
	{
		const PointU& client_size = mInitedWindowSize;

		WLOG_TRACE_2( L"Init viewbased application size by ratio(%dx%d)", client_size.x, client_size.y );
		mRatio.Init( (_float) client_size.x, (_float) client_size.y );
	}

	return _true;
}

_ubool androidViewBasedApp::OnAfterLoadModules( )
{
	return _true;
}

_void androidViewBasedApp::Center( )
{
}

_void androidViewBasedApp::Move( _int delta_x, _int delta_y )
{
}

_void androidViewBasedApp::SetPos( _dword x, _dword y )
{
}

PointI androidViewBasedApp::GetPos( ) const
{
	return PointI::cZeroPoint;
}

_void androidViewBasedApp::SetSize( _dword width, _dword height )
{
	mWindowSize.x = width;
	mWindowSize.y = height;

	WLOG_TRACE_2( L"Set viewbased application size: %d x %d", width, height );
}

PointU androidViewBasedApp::GetSize( ) const
{
	return mWindowSize;
}

RectI androidViewBasedApp::GetRect( ) const
{
	PointU size = GetSize( );

	return RectI( ).InitWithSize( 0, 0, (_int)size.x, (_int)size.y );
}

_void androidViewBasedApp::SetClientSize( _dword width, _dword height, _int* deltawidth, _int* deltaheight )
{
}

RectU androidViewBasedApp::GetClientRectU( ) const
{
	PointU size = GetSize( );

	return RectU( ).InitWithSize( 0, 0, size.x, size.y );
}

_dword androidViewBasedApp::GetAttributes( ) const
{
	return 0;
}

_void androidViewBasedApp::SetAttributes( _dword attributes )
{
}

_VIEWBASED_APP_ORIENTATION androidViewBasedApp::GetOrientation( ) const
{
	int orientation = AConfiguration_getOrientation( mAndroidAppInfo.mConfiguration );
	switch ( orientation )
	{
		case ACONFIGURATION_ORIENTATION_ANY:	return _VIEWBASED_APP_ORIENTATION_ANY;
		case ACONFIGURATION_ORIENTATION_PORT:	return _VIEWBASED_APP_ORIENTATION_PORT;
		case ACONFIGURATION_ORIENTATION_LAND:	return _VIEWBASED_APP_ORIENTATION_LAND;
		case ACONFIGURATION_ORIENTATION_SQUARE:	return _VIEWBASED_APP_ORIENTATION_SQUARE;
		default:
			return _VIEWBASED_APP_ORIENTATION_UNKNOWN;
	}
}

_void androidViewBasedApp::SetCapture( )
{
}

_void androidViewBasedApp::ReleaseCapture( )
{
}