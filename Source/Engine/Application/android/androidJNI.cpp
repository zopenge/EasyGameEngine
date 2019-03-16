//! @file     androidJNI.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//!	The android activity work flow
//!
//!	==================>	onCreate()
//!	||						||
//!	User navigates			||
//!	back to your			\/
//!	activity			onStart() <============================ onRestart()
//!	/\						||										/\
//!	||						\/										||
//!	||					onResume() <==============					||
//!	||						||					||					||
//!	||						\/					||					||
//!	Process is		Activity is running			|| Your activity  	||
//!	killed			(New activity is started)	|| comes to			||
//!	||						||					|| the foreground	||
//!	Other					\/					||					||
//!	applications <===== onPause() ================					|| Your activity 
//!	need memory				||										|| comes to	
//!	/\						\/										|| the foreground
//!	||				Your activity is no longer visible				||
//!	||						||										||
//!	||						\/										||
//!	=================== onStop() =====================================
//!							||
//!							\/
//!						onDestroy()
//!							||
//!							\/
//!					Activity is shut down
//!
//!	See referenced website: http://blog.csdn.net/hpoi/article/details/4629065

//----------------------------------------------------------------------------
// Export Functions Implementation
//----------------------------------------------------------------------------

extern "C"
{

_handle GetJavaVMHandle( )
{
	return androidJNI::GetInstance( ).GetJavaVM( );
}

}

//----------------------------------------------------------------------------
// Crash Functions Implementation
//----------------------------------------------------------------------------

#if (USE_GOOGLE_BREAK_PAD == 1)

//!	The dump callback function.
static bool DumpCallback( const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded )
{
	// Get the dump file path
	AStringPtr dump_filepath = descriptor.path( );

	// The temporary string buffer
	_chara tempstringbuffer[4096]; tempstringbuffer[0] = 0;

	// Output the dump file path
	if ( succeeded )
		Platform::FormatStringBuffer( tempstringbuffer, 4096, "CRASH ! The dump file path is '%s' [OK]", dump_filepath.Str( ) );
	else
		Platform::FormatStringBuffer( tempstringbuffer, 4096, "CRASH ! The dump file path is '%s' [FAILED]", dump_filepath.Str( ) );

	OUTPUT_DEBUG_STRING( tempstringbuffer );

	return succeeded;
}

#elif (USE_SIG_ACTION == 1)

static struct sigaction old_sa[NSIG];

void SigActionCallback( int signal, siginfo_t* info, void* reserved )
{
	old_sa[signal].sa_handler(signal);
}

#endif

//----------------------------------------------------------------------------
// JNI-Platform Functions Implementation
//----------------------------------------------------------------------------

//!	The external JNI-Load/Unload sound device hooker functions declaration.
extern "C" void JNI_OnLoadSoundDevice( JavaVM* vm, void* reserved );
extern "C" void JNI_OnUnloadSoundDevice( JavaVM* vm, void* reserved );

//!	When load library.
JNIEXPORT jint JNICALL JNI_OnLoad( JavaVM* vm, void* reserved )
{
	OUTPUT_DEBUG_STRING( L"JNI_OnLoad() ..." );

	// Initialize java VM
	if ( androidJNI::GetInstance( ).Initialize( vm ) == _false )
	{
		OUTPUT_DEBUG_STRING( L"JNI_OnLoad() failed due to initialize JNI failed" );
		return JNI_ERR;
	}

	// Load sound device 
	JNI_OnLoadSoundDevice( vm, reserved );

	OUTPUT_DEBUG_STRING( L"JNI_OnLoad() OK" );

	return androidJNI::_DEFAULT_JAVA_VERSION;
}

//!	When unload library.
JNIEXPORT void JNICALL JNI_OnUnload( JavaVM* vm, void* reserved )
{
	OUTPUT_DEBUG_STRING( L"JNI_OnUnload() ..." );

	// Unload sound device 
	JNI_OnUnloadSoundDevice( vm, reserved );

	androidJNI::GetInstance( ).Finalize( );

	OUTPUT_DEBUG_STRING( L"JNI_OnUnload() OK" );
}

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_11( void, AndroidJNILib, OnCreateActivity, jobject activity, jobject context, jobject asset_manager, jstring internal_data_path, jstring external_data_path, jstring package_name, jstring source_dir, jint sdk_version, jbyteArray saved_state, jint width, jint height )
{
	OUTPUT_DEBUG_STRING( "AndroidJNILib::OnCreateActivity ..." );

	// Initialize JNI android
	if ( androidJNI::GetInstance( ).InitializeApplication( env, activity, context, asset_manager, internal_data_path, external_data_path, package_name, source_dir, sdk_version, saved_state ) == _false )
		OUTPUT_DEBUG_STRING( L"Initialize android application failed" );

	// Initialize android application
	gAndroidViewbasedApp.InitializeAndroidApp( );

	OUTPUT_DEBUG_STRING( "AndroidJNILib::OnCreateActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnDestroyActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnDestroyActivity ..." );

	gAndroidViewbasedApp.FinalizeAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnDestroyActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnPauseActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnPauseActivity ..." );

	gAndroidViewbasedApp.PauseAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnPauseActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnResumeActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnResumeActivity ..." );

	gAndroidViewbasedApp.ResumeAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnResumeActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnStopActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnStopActivity ..." );

	gAndroidViewbasedApp.StopAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnStopActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnRestartActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnRestartActivity ..." );

	gAndroidViewbasedApp.RestartAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnRestartActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnStartActivity )
{
	ALOG_TRACE( "AndroidJNILib::OnStartActivity ..." );

	gAndroidViewbasedApp.StartAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnStartActivity OK" );
}

JNI_FUNC( void, AndroidJNILib, OnCreateSurface )
{
	ALOG_TRACE( "AndroidJNILib::OnCreateSurface ..." );

	// Set the current window
	gAndroidViewbasedApp.CreateSurfaceAndroidApp( );

	// Re-Initialize android platform ( in order to get the main thread ID )
	Platform::Initialize( );

	ALOG_TRACE( "AndroidJNILib::OnCreateSurface OK" );
}

JNI_FUNC_2( void, AndroidJNILib, OnResizeSurface, jint width, jint height )
{
	ALOG_TRACE_2( "AndroidJNILib::OnResizeSurface (%dx%d) ...", width, height );

	gAndroidViewbasedApp.ResizeSurfaceAndroidApp( width, height );

	ALOG_TRACE( "AndroidJNILib::OnResizeSurface OK" );
}

JNI_FUNC_1( void, AndroidJNILib, OnConfigureChanged, jobject config )
{
	ALOG_TRACE( "AndroidJNILib::OnConfigureChanged ..." );

	androidJNI::GetInstance( ).FlushConfiguration( );

	gAndroidViewbasedApp.ChangeAndroidAppConfig( androidJNI::GetInstance( ).GetConfiguration( ) );

	ALOG_TRACE( "AndroidJNILib::OnConfigureChanged OK" );
}

JNI_FUNC_1( void, AndroidJNILib, OnWindowFocusChanged, jboolean has_focus )
{
	ALOG_TRACE_1( "AndroidJNILib::OnWindowFocusChanged (%d) ...", has_focus );

	gAndroidViewbasedApp.WindowFocusChangedAndroidApp( has_focus );

	ALOG_TRACE( "AndroidJNILib::OnWindowFocusChanged OK" );
}

JNI_FUNC( void, AndroidJNILib, OnMemoryLow )
{
	ALOG_TRACE( "AndroidJNILib::OnMemoryLow ..." );

	gAndroidViewbasedApp.MemoryLowAndroidApp( );

	ALOG_TRACE( "AndroidJNILib::OnMemoryLow OK" );
}

JNI_FUNC( void, AndroidJNILib, OnRender )
{
	gAndroidViewbasedApp.RenderAndroidApp( );
}

JNI_FUNC_1( jboolean, AndroidJNILib, OnKeyUp, jint key_code )
{
	return gAndroidViewbasedApp.HandleKeyUpEvent( key_code );
}

JNI_FUNC_1( jboolean, AndroidJNILib, OnKeyDown, jint key_code )
{
	return gAndroidViewbasedApp.HandleKeyDownEvent( key_code );
}

JNI_FUNC_1( jboolean, AndroidJNILib, OnKeyLongPress, jint key_code )
{
	return gAndroidViewbasedApp.HandleKeyLongPressEvent( key_code );
}

JNI_FUNC_1( jboolean, AndroidJNILib, OnDispatchKeyEvent, jobject event )
{
	return gAndroidViewbasedApp.HandleDispatchedKeyEvent( event );
}

JNI_FUNC_1( jboolean, AndroidJNILib, OnDispatchGenericMotionEvent, jobject event )
{
	return gAndroidViewbasedApp.HandleDispatchedGenericMotionEvent( event );
}

JNI_FUNC_3( void, AndroidJNILib, OnHandleTouchBegin, jint x, jint y, jint touch_id )
{
//	ALOG_TRACE_3( "AndroidJNILib::OnHandleTouchBegin(x: %d, y: %d, id: %d)", x, y, touch_id );

	gAndroidViewbasedApp.HandleTouchEvent( EventTouch::_EVENT_BEGAN, touch_id, x, y );
}

JNI_FUNC_3( void, AndroidJNILib, OnHandleTouchMove, jint x, jint y, jint touch_id )
{
	gAndroidViewbasedApp.HandleTouchEvent( EventTouch::_EVENT_MOVED, touch_id, x, y );
}

JNI_FUNC_3( void, AndroidJNILib, OnHandleTouchEnd, jint x, jint y, jint touch_id )
{
//	ALOG_TRACE_3( "AndroidJNILib::OnHandleTouchEnd(x: %d, y: %d, id: %d)", x, y, touch_id );

	gAndroidViewbasedApp.HandleTouchEvent( EventTouch::_EVENT_ENDED, touch_id, x, y );
}

JNI_FUNC( void, AndroidJNILib, OnShake )
{
	//	ALOG_DEBUG_3( "AndroidJNILib::OnShake()" );

	gAndroidViewbasedApp.HandleShakeEvent( );
}

JNI_FUNC_3( void, AndroidJNILib, OnAccelerometerSensorChanged, jfloat x, jfloat y, jfloat z )
{
	//	ALOG_DEBUG_3( "AndroidJNILib::OnAccelerometerSensorChanged(x:%f, y:%f, z:%f)", x, y, z );

	gAndroidViewbasedApp.HandleAccelerometerSensorChangedEvent( x, y, z );
}

JNI_FUNC_3( void, AndroidJNILib, OnGyroscopeSensorChanged, jfloat x, jfloat y, jfloat z )
{
//	ALOG_DEBUG_3( "AndroidJNILib::OnGyroscopeSensorChanged(x:%f, y:%f, z:%f)", x, y, z );

	gAndroidViewbasedApp.HandleGyroscopeSensorChangedEvent( x, y, z );
}

JNI_FUNC_3( void, AndroidJNILib, OnOrientationSensorChanged, jfloat x, jfloat y, jfloat z )
{
//	ALOG_DEBUG_3( "AndroidJNILib::OnOrientationSensorChanged(x:%f, y:%f, z:%f)", x, y, z );

	gAndroidViewbasedApp.HandleOrientationSensorChangedEvent( x, y, z );
}

JNI_FUNC( jboolean, AndroidJNILib, OnBackPressed )
{
	return gAndroidViewbasedApp.HandleKeyDownEvent( AKEYCODE_BACK );
}

JNI_FUNC_2( jboolean, AndroidJNILib, OnEnumResFile, jstring path, jlong userData )
{
	return gAndroidViewbasedApp.HandleEnumResFileEvent( path, userData );
}

//----------------------------------------------------------------------------
// androidJNIEnv Implementation
//----------------------------------------------------------------------------

androidJNIEnv::androidJNIEnv( )
{
	mIsAttached = _false;
	mEnv		= _null;
}

androidJNIEnv::androidJNIEnv( _ubool is_attached, JNIEnv* env )
{
	mIsAttached = is_attached;
	mEnv		= env;
}

androidJNIEnv::~androidJNIEnv( )
{
	if ( mIsAttached )
		androidJNI::GetInstance( ).GetJavaVM( )->DetachCurrentThread( );
}

//----------------------------------------------------------------------------
// androidJNI Implementation
//----------------------------------------------------------------------------

androidJNI::androidJNI( )
{
	mJavaVM				= _null;

	mAppActivity		= _null;
	mContextObj			= _null;
	mAssetManagerObj	= _null;

	mSDKVersion			= 0;
	mSavedStateSize		= 0;
	mSavedStateBuffer	= _null;
	mConfiguration		= _null;
	mAssetManager		= _null;

	mJNIInterfaceObjs	= new JNIObject[ _JNI_OBJ_MAX_NUMBER ];
}

androidJNI::~androidJNI( )
{
	EGE_DELETE_ARRAY( mJNIInterfaceObjs );

	EGE_DELETE_ARRAY( mSavedStateBuffer );
}

_ubool androidJNI::InitDumper( )
{
	// 1. Try to use external data path
	AString dump_path = Path::BuildFilePath( mExternalDataPath, "dump" );
	if ( FileSystem::CreateDir( WString( ).FromString( dump_path ) ) )
	{
		ALOG_TRACE_1( "Use '%s' external data path as dump folder", dump_path.Str( ) );
	}
	// 2. Try to use internal data path
	else
	{
		dump_path = Path::BuildFilePath( mInternalDataPath, "dump" );
		if ( FileSystem::CreateDir( WString( ).FromString( dump_path ) ) )
		{
			ALOG_TRACE_1( "Use '%s' internal data path as dump folder", dump_path.Str( ) );
		}
		else
		{
			ALOG_ERROR( "Create dump folder failed" );
			return _false;
		}
	}

#if (USE_GOOGLE_BREAK_PAD == 1)
	// Initialize google break-pad dumper
	static google_breakpad::MinidumpDescriptor sDescriptor( dump_path.Str( ) );
	static google_breakpad::ExceptionHandler sExceptHandler( sDescriptor, _null, DumpCallback, _null, true, -1 );
#elif (USE_SIG_ACTION == 1)
	// Try to catch crashes...
	struct sigaction handler = {0};
	handler.sa_sigaction	= SigActionCallback;
	handler.sa_flags		= SA_RESETHAND;
#define CATCHSIG(X) sigaction(X, &handler, &old_sa[X])
	CATCHSIG(SIGILL);
	CATCHSIG(SIGABRT);
	CATCHSIG(SIGBUS);
	CATCHSIG(SIGFPE);
	CATCHSIG(SIGSEGV);
	CATCHSIG(SIGSTKFLT);
	CATCHSIG(SIGPIPE);
#endif

	return _true;
}

jmethodID androidJNI::GetJSMethodID( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl )
{
	// Get the method
	jmethodID j_method = GetJNIEnv( )->GetMethodID( j_class, func_name.Str( ), parameters_decl.Str( ) );
	if ( j_method == _null )
	{
		ALOG_ERROR_2( "The '%s(%s)' JS function is not existing", func_name.Str( ), parameters_decl.Str( ) );
		return _null;
	}

	return j_method;
}

jmethodID androidJNI::GetStaticJSMethodID( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl )
{
	// Get the method
	jmethodID j_method = GetJNIEnv( )->GetStaticMethodID( j_class, func_name.Str( ), parameters_decl.Str( ) );
	if ( j_method == _null )
	{
		ALOG_ERROR_2( "The '%s(%s)' static JS function is not existing", func_name.Str( ), parameters_decl.Str( ) );
		return _null;
	}

	return j_method;
}

_ubool androidJNI::Initialize( JavaVM* vm )
{
	OUTPUT_DEBUG_STRING( "Initializing android JNI ..." );

	// Save JAVA virtual machine handle
	mJavaVM = vm;
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Get '0x%.16llx' JAVA VM handle", (_qword)vm ) );

	// Build the string table
	AString os_path		= EGE_OBFUSCATE_STR( "android/os/" );
	AString ege_path	= EGE_OBFUSCATE_STR( "com/ege/android/" );

	// The JNI interface object path table
	struct JNIObjInitInfo
	{
		AString	mPath;
		_ubool	mIsStaticOnly;
	};
	JNIObjInitInfo jni_obj_paths[ _JNI_OBJ_MAX_NUMBER ] = 
	{
		{ /* _JNI_OBJ_OS_DEBUG,		*/ os_path + EGE_OBFUSCATE_STR( "Debug" ),					_true },
		{ /* _JNI_OBJ_JNILIB,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidJNILib" ),			_true },
		{ /* _JNI_OBJ_WEBVIEW,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidWebView" ),		_true },
		{ /* _JNI_OBJ_SERVICE,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidService" ),		_true },
		{ /* _JNI_OBJ_PURCHASE,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidPurchase" ),		_true },
		{ /* _JNI_OBJ_EDITBOX,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidEditBox" ),		_false },
		{ /* _JNI_OBJ_RECORDER,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidRecorder" ),		_false },
		{ /* _JNI_OBJ_UTILS,		*/ ege_path + EGE_OBFUSCATE_STR( "AndroidUtils" ),			_true },
		{ /* _JNI_OBJ_BASEACTIVITY,	*/ ege_path + EGE_OBFUSCATE_STR( "AndroidBaseActivity" ),	_true },
	};

	// Initialize JAVA interface objects
	for ( _dword i = 0; i < _JNI_OBJ_MAX_NUMBER; i ++ )
	{
		const JNIObjInitInfo& jni_info = jni_obj_paths[i];

		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Initializing (path: '%s', static_only:%d) JAVA interface object ...", jni_info.mPath.Str( ), (_boolean)jni_info.mIsStaticOnly ) );

		if ( mJNIInterfaceObjs[i].Initialize( jni_info.mPath, jni_info.mIsStaticOnly ) == _false )
		{
			OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Initialize (path: '%s', static_only:%d) JAVA interface object failed", jni_info.mPath.Str( ), (_boolean)jni_info.mIsStaticOnly ) );
			return _false;
		}

		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Initializing (path: '%s', static_only:%d) JAVA interface object OK", jni_info.mPath.Str( ), (_boolean)jni_info.mIsStaticOnly ) );
	}

	OUTPUT_DEBUG_STRING( "Initializing android JNI OK" );

	return _true;
}

_void androidJNI::Finalize( )
{
	// Delete configuration
	if ( mConfiguration != _null )
	{
		::AConfiguration_delete( mConfiguration );
		mConfiguration = _null;
	}

	// Release asset manager object
	GetJNIEnv( )->DeleteGlobalRef( mAssetManagerObj );
}

_void androidJNI::FlushConfiguration( )
{
	// Create the configuration
	if ( mConfiguration == _null )
		mConfiguration = ::AConfiguration_new( );

	// Get the configuration from asset manager
	::AConfiguration_fromAssetManager( mConfiguration, mAssetManager );
}

_ubool androidJNI::InitializeApplication( JNIEnv* env, jobject activity, jobject context, jobject asset_manager, jstring internal_data_path, jstring external_data_path, jstring package_name, jstring source_dir, jint sdk_version, jbyteArray saved_state )
{
	// Show the activity and context and make them alive
	activity	= env->NewGlobalRef( activity );
	context		= env->NewGlobalRef( context );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Android activity: 0x%.16llx", (_qword) activity ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Android context: 0x%.16llx", (_qword) context ) );

	// Keep the asset manager alive
	asset_manager = env->NewGlobalRef( asset_manager );
	if ( asset_manager == _null )
	{
		OUTPUT_DEBUG_STRING( "Asset manager new global referenced operation failed" );
		return _false;
	}

	// Save the asset manager handle
	mAssetManager = ::AAssetManager_fromJava( env, asset_manager );
	if ( mAssetManager == _null )
	{
		OUTPUT_DEBUG_STRING( "Asset manager handle is null" );
		return _false;
	}

	// Get the new configuration
	FlushConfiguration( );

	// Save the platform info
	mAppActivity		= activity;
	mContextObj			= context;
	mAssetManagerObj	= asset_manager;
	mInternalDataPath	= J2CString( internal_data_path ).ToStringA( );
	mExternalDataPath	= J2CString( external_data_path ).ToStringA( );
	mPackageName		= J2CString( package_name ).ToStringA( );
	mSourceDir			= J2CString( source_dir ).ToStringA( );
	mSDKVersion			= sdk_version;
	mSavedStateSize		= saved_state != _null ? GetJNIEnv( )->GetArrayLength( saved_state ) : 0;
	if ( mSavedStateSize > 0 )
	{
		mSavedStateBuffer = new _byte[ mSavedStateSize ];
		EGE_MEM_CPY( mSavedStateBuffer, env->GetByteArrayElements( saved_state, _null ), mSavedStateSize );
	}

	// Show the platform info
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Asset mananger handle is 0x%.16llx", (_qword)mAssetManager ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Android configuration: 0x%.16llx", (_qword)mConfiguration ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Internal data path: '%s'", mInternalDataPath.Str( ) ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "External data path: '%s'", mExternalDataPath.Str( ) ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Package name: '%s'", mPackageName.Str( ) ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "Source dir: '%s'", mSourceDir.Str( ) ) );
	OUTPUT_DEBUG_STRING( FORMAT_ASTRING_1( "SDK version: %d", mSDKVersion ) );

	// Initialize dumper
	if ( InitDumper( ) == _false )
		return _false;

	return _true;
}

JNIObject& androidJNI::GetAndroidOSDebugObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_OS_DEBUG ];
}

JNIObject& androidJNI::GetAndroidJNILibObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_JNILIB ];
}

JNIObject& androidJNI::GetWebViewObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_WEBVIEW ];
}

JNIObject& androidJNI::GetServiceObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_SERVICE ];
}

JNIObject& androidJNI::GetPurchaseObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_PURCHASE ];
}

JNIObject& androidJNI::GetEditBoxObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_EDITBOX ];
}

JNIObject& androidJNI::GetRecorderObj( )
{
	return mJNIInterfaceObjs[_JNI_OBJ_RECORDER];
}

JNIObject& androidJNI::GetUtilsObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_UTILS ];
}

JNIObject& androidJNI::GetBaseActivityObj( )
{
	return mJNIInterfaceObjs[ _JNI_OBJ_BASEACTIVITY ];
}

JNIObject& androidJNI::GetJNIObj( _JNI_INTERFACE_OBJ type )
{
	return mJNIInterfaceObjs[ type ];
}

JNIObject* androidJNI::GetJNIObjByPath( AStringPtr path )
{
	for ( _dword i = 0; i < _JNI_OBJ_MAX_NUMBER; i ++ )
	{
		if ( mJNIInterfaceObjs[i].GetPath( ) == path )
			return &mJNIInterfaceObjs[i];
	}

	return _null;
}

JNIObject* androidJNI::GetJNIObjByPath( WStringPtr path )
{
	return GetJNIObjByPath( AString( ).FromString( path ) );
}

jobject androidJNI::CreateJObject( const _chara* path )
{
	ALOG_TRACE_1( "Creating the JS object from '%s' ...", path );

	// Find the JS class from path
	jclass js_cls = GetJNIEnv( )->FindClass( path );
	if ( js_cls == _null )
	{
		ALOG_ERROR_1( "Find JS class from '%s' failed", path );
		return _null;
	}

	// Get the constructor method ID
	jmethodID js_constructor = GetJNIEnv( )->GetMethodID( js_cls, "<init>", "()V" );
	if ( js_constructor == _null )
	{
		ALOG_ERROR_1( "Get the JS constructor<init> from '%s' failed", path );
		return _null;
	}

	// Create JS object
	jobject js_obj = GetJNIEnv( )->NewObject( js_cls, js_constructor );
	if ( js_obj == _null )
	{
		ALOG_ERROR_1( "Create the JS object from '%s' failed", path );
		return _null;
	}

	// Keep the JS object alive
	jobject cloned_js_obj = GetJNIEnv( )->NewGlobalRef( js_obj );
	if ( cloned_js_obj == _null )
	{
		ALOG_ERROR_1( "New global ref JS object from '%s' failed", path );
		return _null;
	}

	ALOG_TRACE_1( "Create the JS object from '%s' OK", path );

	return cloned_js_obj;
}

JNIObject* androidJNI::CreateJNIObject( const _chara* path )
{
	// Create JS object
	jobject j_object = androidJNI::GetInstance( ).CreateJObject( path );
	if ( j_object == _null )
		return _null;

	// Bind JS object
	JNIObject* jni_object = new JNIObject( );
	if ( jni_object->Initialize( _false, path, j_object ) == _false )
		{ EGE_RELEASE( jni_object ); return _null; }

	return jni_object;
}

androidJNIEnv androidJNI::GetJNIEnv( )
{
	JNIEnv*	env			= _null; 
	_ubool	attached	= _false;

	jint status = mJavaVM->GetEnv( (_void**) &env, androidJNI::_DEFAULT_JAVA_VERSION );
	if ( status < 0 )
	{
		status = mJavaVM->AttachCurrentThread( &env, _null );
		if ( status == JNI_OK )
			attached = _true;
	}

	return androidJNIEnv( attached, env );
}

jobject androidJNI::CreateHashMapObject( )
{
	jclass		j_class			= GetJNIEnv( )->FindClass( "java/util/HashMap" );
	jmethodID	j_constructor	= GetJNIEnv( )->GetMethodID( j_class, "<init>", "()V" );

	return GetJNIEnv( )->NewObject( j_class, j_constructor );
}

jobject androidJNI::CreateHashMapObject( const Map< UString, UString >& map_object )
{
	// Thanks for sharing code : http://onegazhang.wordpress.com/2011/07/15/cpp-call-java-hashmap/

	// Get the hash map JAVA interfaces
	jclass		j_class			= GetJNIEnv( )->FindClass( "java/util/HashMap" );
	jmethodID	j_constructor	= GetJNIEnv( )->GetMethodID( j_class, "<init>", "()V" );
	jmethodID	map_put_mid		= GetJNIEnv( )->GetMethodID( j_class, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;" );
	
	// Create JAVA map object
	jobject j_map_object = GetJNIEnv( )->NewObject( j_class, j_constructor );

	// Put arguments into map object
	for ( Map< UString, UString >::Iterator it = map_object.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		C2JString j_arg( it.GetKey( ) );
		C2JString j_value( it.GetObject( ) );

		GetJNIEnv( )->CallObjectMethod( j_map_object, map_put_mid, j_arg.ToJString( ), j_value.ToJString( ) );
	}

	return j_map_object;
}

_void androidJNI::CallVoidMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return;

	// Call method
	GetJNIEnv( )->CallVoidMethodV( j_object, j_method, args );
}

_ubool androidJNI::CallBooleanMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return _false;

	// Call method
	jboolean ret = GetJNIEnv( )->CallBooleanMethodV( j_object, j_method, args );
	return ret;
}

_int androidJNI::CallIntMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return -1;

	// Call method
	jint ret = GetJNIEnv( )->CallIntMethodV( j_object, j_method, args );
	return ret;
}

_large androidJNI::CallLongMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return -1;

	// Call method
	jlong ret = GetJNIEnv( )->CallLongMethodV( j_object, j_method, args );
	return ret;
}

jobject androidJNI::CallObjectMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return _null;

	// Call method
	jobject ret = GetJNIEnv( )->CallObjectMethodV( j_object, j_method, args );
	return ret;
}

_void androidJNI::CallStaticVoidMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetStaticJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return;

	// Call method
	GetJNIEnv( )->CallStaticVoidMethodV( j_class, j_method, args );
}

_ubool androidJNI::CallStaticBooleanMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetStaticJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return _false;

	// Call method
	jboolean ret = GetJNIEnv( )->CallStaticBooleanMethodV( j_class, j_method, args );
	return ret;
}

_int androidJNI::CallStaticIntMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetStaticJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return -1;

	// Call method
	jint ret = GetJNIEnv( )->CallStaticIntMethodV( j_class, j_method, args );
	return ret;
}

jobject androidJNI::CallStaticObjectMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args )
{
	// Get the method
	jmethodID j_method = GetStaticJSMethodID( j_class, func_name, parameters_decl );
	if ( j_method == _null )
		return _null;

	// Call method
	jobject ret = GetJNIEnv( )->CallStaticObjectMethodV( j_class, j_method, args );
	return ret;
}
