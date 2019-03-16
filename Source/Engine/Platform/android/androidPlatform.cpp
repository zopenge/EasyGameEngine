//! @file     androidPlatform.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidPlatform Implementation
//----------------------------------------------------------------------------

androidPlatform::androidPlatform( )
{
}

androidPlatform::~androidPlatform( )
{
}

_ubool androidPlatform::OnCopyResourcesFromAssetDirCallback( const _charw* res_name, _void* parameter )
{
	CopyResInfo* copy_res_info = (CopyResInfo*) parameter;
	EGE_ASSERT( copy_res_info != _null );

	// Build the source and target file name in asset directory
	WString src_file_name = Path::BuildFilePath( copy_res_info->mSourceDirName, res_name );
	WString des_file_name = Path::BuildFilePath( copy_res_info->mTargetDirName, res_name );

	// Open the resource
	AAsset* asset = AAssetManager_open( androidJNI::GetInstance( ).GetAssetManager( ), AString( ).FromString( src_file_name ).Str( ), AASSET_MODE_STREAMING );
	if ( asset == _null )
		return _false;

	// Get file info ( if it's empty file then the buffer and size could be null or zero )
	const _byte*	buffer	= (const _byte*) AAsset_getBuffer( asset );
	_dword			size	= (_dword) AAsset_getLength( asset );

	// Create file
	_ubool ret = FileSystem::CreateFile( des_file_name, size, buffer );
	if ( ret )
	{
		WLOG_TRACE_2( L"Copy '%s' to '%s' from asset directory OK", src_file_name.Str( ), des_file_name.Str( ) );
	}
	else
	{
		WLOG_ERROR_2( L"Copy '%s' to '%s' from asset directory failed", src_file_name.Str( ), des_file_name.Str( ) );
	}

	// Close the resource
	AAsset_close( asset );

	return ret;
}

_void androidPlatform::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	switch ( event.mEventID )
	{
		case _EVENT_BEGIN_RESET_RESOURCES:
		{
			androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticVoidMethod( "showLoadingUI", "()V" );
		}
		break;

		case _EVENT_END_RESET_RESOURCES:
		{
			androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticVoidMethod( "hideLoadingUI", "()V" );
		}
		break;

		default:
			break;
	}
}

_ubool androidPlatform::Initialize( )
{
	if ( BaseClass::Initialize( ) == _false )
		return _false;

	return _true;
}

_void androidPlatform::Finalize( )
{
	BaseClass::Finalize( );
}

const PlatformDeviceInfo& androidPlatform::GetDeviceInfo( )
{
	if ( mDeviceInfo.mDeviceName.IsEmpty( ) )
	{
		JNIObject& activity_obj	= androidJNI::GetInstance( ).GetBaseActivityObj( );
		JNIObject& utils_obj		= androidJNI::GetInstance( ).GetUtilsObj( );

		jobject	js_context		= androidJNI::GetInstance( ).GetContextObj( );
		jstring	js_device		= (jstring) utils_obj.CallStaticObjectMethod( "getOSBuildDeviceString", "()Ljava/lang/String;" );
		jstring	js_model		= (jstring) utils_obj.CallStaticObjectMethod( "getOSBuildModelString", "()Ljava/lang/String;" );
		jstring	js_hardware_id	= (jstring) utils_obj.CallStaticObjectMethod( "getHardwareID", "(Landroid/content/Context;)Ljava/lang/String;", js_context );
		jstring	js_version_name	= (jstring) activity_obj.CallStaticObjectMethod( "getVersion", "()Ljava/lang/String;" );

		mDeviceInfo.mIdentifierForVendor	= L"Android";
		mDeviceInfo.mDeviceName				= J2CString( js_device ).ToStringW( );
		mDeviceInfo.mModelName				= J2CString( js_model ).ToStringW( );
		mDeviceInfo.mSystemVersion			= J2CString( js_version_name ).ToStringW( );
		mDeviceInfo.mHardwareIDv2			= J2CString( js_hardware_id ).ToStringW( );
	}

	return BaseClass::GetDeviceInfo( );
}

WStringR androidPlatform::GetIMSI( ) const
{
	// Call method
	_void* js_imsi_string = androidJNI::GetInstance( ).GetUtilsObj( ).CallStaticObjectMethod( "getIMSI", "(Landroid/content/Context;)Ljava/lang/String;", androidJNI::GetInstance( ).GetContextObj( ) );
	EGE_ASSERT( js_imsi_string != _null );

	// Get the JNI env
	androidJNIEnv jni_env = androidJNI::GetInstance( ).GetJNIEnv( );

	// Get the IMSI string in UTF8
	const _chara* imsi_string = jni_env->GetStringUTFChars( (jstring) js_imsi_string, _null );
	EGE_ASSERT( imsi_string != _null );

	// We use the IMSI string as UTF-16 format
	return WString( ).FromString( _ENCODING_UTF8, imsi_string );
}

_qword androidPlatform::GetCurProcessMemSize( ) const
{
	JNIObject& utils_obj = androidJNI::GetInstance( ).GetUtilsObj( );

	_qword mem_size = utils_obj.CallStaticIntMethod( "getProcessMemSize", "(Landroid/content/Context;)I", androidJNI::GetInstance( ).GetContextObj( ) );
	return mem_size;
}

_qword androidPlatform::GetTotalMemSize( ) const
{
	static _qword total_mem_size = 0;
	if ( total_mem_size == 0 )
	{
		JNIObject& utils_obj = androidJNI::GetInstance( ).GetUtilsObj( );

		total_mem_size = utils_obj.CallStaticIntMethod( "getTotalMemSize", "(Landroid/content/Context;)I", androidJNI::GetInstance( ).GetContextObj( ) );
	}

	return total_mem_size;
}

_void androidPlatform::SetSurfaceFixedSize( const PointU& size )
{
	androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticVoidMethod( "setFixedSize", "(II)V", size.x, size.y );
}

PointU androidPlatform::GetMainScreenSize( ) const
{
	_dword width	= (_dword) androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticIntMethod( "getDisplayWidth", "()I" );
	_dword height	= (_dword) androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticIntMethod( "getDisplayHeight", "()I" );

	return PointU( width, height );
}

_ubool androidPlatform::IsScreenOn( ) const
{
	jobject	js_context = androidJNI::GetInstance( ).GetContextObj( );

	return androidJNI::GetInstance( ).GetUtilsObj( ).CallStaticBooleanMethod( "isScreenOn", "(Landroid/content/Context;)Z", js_context );
}

_void androidPlatform::OpenURL( WStringPtr url )
{
	C2JString j_url( url );
	androidJNI::GetInstance( ).GetBaseActivityObj( ).CallStaticVoidMethod( "openURL", "(Ljava/lang/String;)V", j_url.ToJString( ) );
}

IStreamReaderPassRef androidPlatform::LoadSystemFont( WStringPtr name )
{
	_charw font_path[1024];
	if ( Platform::GetSystemFontPath( font_path, 1024 ) == _false )
		return _null;

	// Get the font full path in system folder
	WString font_fullpath = Path::BuildFilePath( font_path, name );

	// Load font file
	IStreamReaderPassRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( font_fullpath );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"The '%s' font is not existing in system", font_fullpath.Str( ) );
		return _null;
	}

	WLOG_TRACE_1( L"Load the '%s' font resource from system", font_fullpath.Str( ) );

	return stream_reader;
}

IWebViewPassRef	androidPlatform::CreateWebView( const PointI& pos, const PointI& size )
{
	androidWebView* web_view = new androidWebView( );
	if  ( web_view->Initialize( pos, size ) == _false )
		{ EGE_RELEASE( web_view ); return _null; }

	return web_view;
}

IEditBoxPassRef	androidPlatform::CreateEditBox( )
{
	return new androidEditBox( );
}

IMessageBoxPassRef androidPlatform::CreateMessageBox( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const
{
	return CreateMessageBox( title, content, L"Yes", L"No", type, notifier );
}

IMessageBoxPassRef androidPlatform::CreateMessageBox( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const
{
	androidMessageBox* message_box = new androidMessageBox( );
	message_box->SetNotifier( notifier );
	message_box->Show( title, content, yes_text, no_text, type );

	return message_box;
}

IAnalyticsCenterPassRef androidPlatform::CreateAnalyticsCenter( UStringPtr app_id )
{
	androidAnalyticsCenterFlurry* center = new androidAnalyticsCenterFlurry( );
	if ( center->Initialize( app_id ) == _false )
		{ EGE_RELEASE( center ); return _null; }

	return center;
}

IAdViewPassRef androidPlatform::CreateAdView( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type )
{
	return _null;
}

IKeychainPassRef androidPlatform::CreateKeychain( WStringPtr identifier, WStringPtr access_group )
{
	return _null;
}

_void androidPlatform::InvokeService( WStringPtr name )
{
	C2JString j_name( name );

	androidJNI::GetInstance( ).GetServiceObj( ).CallStaticVoidMethod( "invokeService", "(Ljava/lang/String;)V", j_name.ToJString( ) );
}

_ubool androidPlatform::InvokeServiceZ( WStringPtr name )
{
	C2JString j_name( name );

	return androidJNI::GetInstance( ).GetServiceObj( ).CallStaticBooleanMethod( "invokeServiceZ", "(Ljava/lang/String;)Z", j_name.ToJString( ) );
}

_void androidPlatform::Vibrate( _dword duration )
{
	androidJNI::GetInstance( ).GetUtilsObj( ).CallStaticVoidMethod( "vibrate", "(J)V", (jlong) duration );
}

_void androidPlatform::CancelVibrate( )
{
	androidJNI::GetInstance( ).GetUtilsObj( ).CallStaticVoidMethod( "cancelVibrate", "()V" );
}

_ubool androidPlatform::RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer )
{
	// Get the JNI object
	JNIObject* jni_obj = androidJNI::GetInstance( ).GetJNIObjByPath( path );
	if ( jni_obj == _null )
	{
		ALOG_ERROR_3( "The '%s' path is not existing, register '%s(%s)' function failed", path.Str( ), func_name.Str( ), func_decl.Str( ) );
		return _false;
	}

	// Find the class
	jclass j_class = jni_obj->GetJSClass( );
	if ( j_class == _null )
	{
		ALOG_ERROR_3( "The '%s' class is not existing, register '%s(%s)' function failed", path.Str( ), func_name.Str( ), func_decl.Str( ) );
		return _false;
	}

	// Initialize native method
	JNINativeMethod j_method;
	j_method.name		= func_name.Str( );
	j_method.signature	= func_decl.Str( );
	j_method.fnPtr		= func_pointer;

	// Register native method
	if ( androidJNI::GetInstance( ).GetJNIEnv( )->RegisterNatives( j_class, &j_method, 1 ) < 0 )
	{  
		ALOG_ERROR_3( "Register 'path: %s, %s(%s)' function failed", path.Str( ), func_name.Str( ), func_decl.Str( ) );
		return _false;
	}

	return _true;
}

JNIEnv* androidPlatform::GetJNIEnv( )
{
	return androidJNI::GetInstance( ).GetJNIEnv( ).GetEnv( );
}

AStringR androidPlatform::ByteArray2HexString( jbyteArray buffer )
{
	JNIEnv*	env = androidJNI::GetInstance( ).GetJNIEnv( ).GetEnv( );
	EGE_ASSERT( env != _null );

	AString hex;

	jint	length	= env->GetArrayLength( buffer );
	jbyte*	data	= env->GetByteArrayElements( buffer, _null );
	if ( data != _null ) 
	{
		for ( jint i = 0; i < length; i ++ )
		{
			hex += FORMAT_ASTRING_1( "%02X", data[i] & 0xFF );
			hex += ":";
		}
		hex.TrimRight( ":" );

		env->ReleaseByteArrayElements( buffer, data, JNI_ABORT );
	}

	return hex;
}

IInvokerPassRef androidPlatform::CreateJNIObject( AStringPtr path )
{
	JNIObject* jni_object = androidJNI::GetInstance( ).CreateJNIObject( path.Str( ) );
	if ( jni_object == _null )
		return _null;

	return jni_object;
}

IJ2CArrayPassRef androidPlatform::CreateJ2CArray( jbyteArray buffer )
{
	return new J2CArray( buffer );
}

IC2JArrayPassRef androidPlatform::CreateC2JArray( _dword size, const _byte* buffer )
{
	return new C2JArray( size, buffer );
}

AStringR androidPlatform::ToStringA( jstring string )
{
	return J2CString( string ).ToStringA( );
}

UStringR androidPlatform::ToStringU( jstring string )
{
	return J2CString( string ).ToStringU( );
}

WStringR androidPlatform::ToStringW( jstring string )
{
	return J2CString( string ).ToStringW( );
}

IJ2CStringPassRef androidPlatform::CreateJ2CString( jstring string )
{
	return new J2CString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( AStringPtr string )
{
	return new C2JString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( UStringPtr string )
{
	return new C2JString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( WStringPtr string )
{
	return new C2JString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( const AStringObj& string )
{
	return new C2JString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( const UStringObj& string )
{
	return new C2JString( string );
}

IC2JStringPassRef androidPlatform::CreateC2JString( const WStringObj& string )
{
	return new C2JString( string );
}

IC2JStringMapPassRef androidPlatform::CreateC2JStringMap( const Map< UString, UString >& map_object )
{
	return new C2JStringMap( map_object );
}

_ubool androidPlatform::CopyFileFromAssetDir( WStringPtr source_file_name, WStringPtr target_file_name )
{
	// Open the resource
	AAsset* asset = AAssetManager_open( androidJNI::GetInstance( ).GetAssetManager( ), AString( ).FromString( source_file_name ).Str( ), AASSET_MODE_STREAMING );
	if ( asset == _null )
	{
		WLOG_ERROR_1( L"Open '%s' file failed when copy it from asset directory", source_file_name.Str( ) );
		return _false;
	}

	// Get file info ( if it's empty file then the buffer and size could be null or zero )
	const _byte*	buffer	= (const _byte*) AAsset_getBuffer( asset );
	_dword			size	= (_dword) AAsset_getLength( asset );

	// Create file
	_ubool ret = FileSystem::CreateFile( target_file_name, size, buffer );
	if ( ret )
	{
		WLOG_TRACE_2( L"Copy '%s' to '%s' from asset directory OK", source_file_name.Str( ), target_file_name.Str( ) );
	}
	else
	{
		WLOG_ERROR_2( L"Copy '%s' to '%s' from asset directory failed", source_file_name.Str( ), target_file_name.Str( ) );
	}

	// Close the resource
	AAsset_close( asset );

	return _true;
}

_ubool androidPlatform::CopyDirFromAssetDir( WStringPtr source_dir_name, WStringPtr target_dir_name )
{
	if ( FileSystem::CreateDir( target_dir_name ) == _false )
	{
		WLOG_ERROR_2( L"Create '%s' target directory failed when copy resources from '%s' asset directory", target_dir_name.Str( ), source_dir_name.Str( ) );
		return _false;
	}

	CopyResInfo copy_res_info;
	copy_res_info.mPlatform			= this;
	copy_res_info.mSourceDirName	= source_dir_name;
	copy_res_info.mTargetDirName	= target_dir_name;
	if ( Platform::EnumResourceNames( _null, source_dir_name.Str( ), OnCopyResourcesFromAssetDirCallback, (_void*)&copy_res_info ) == _false )
	{
		WLOG_ERROR_2( L"Enum asset resources failed when copy '%s' to '%s'", source_dir_name.Str( ), target_dir_name.Str( ) );
		return _false;
	}

	return _true;
}

AStringR androidPlatform::GetSignature( )
{
	JNIEnv*	env = androidJNI::GetInstance( ).GetJNIEnv( ).GetEnv( );
	EGE_ASSERT( env != _null );

	jobject activity_obj = androidJNI::GetInstance( ).GetAppActivity( );
	EGE_ASSERT( activity_obj != _null );

	jclass jclass_Activity						= env->FindClass( "android/app/Activity" );
	jclass jclass_PackageManager				= env->FindClass( "android/content/pm/PackageManager" );
	jclass jclass_PackageInfo					= env->FindClass( "android/content/pm/PackageInfo" );
	jclass jclass_Signature						= env->FindClass( "android/content/pm/Signature" );
	jclass jclass_CertificateFactory			= env->FindClass( "java/security/cert/CertificateFactory" );
	jclass jclass_X509Certificate				= env->FindClass( "java/security/cert/X509Certificate" );
	jclass jclass_MessageDigest					= env->FindClass( "java/security/MessageDigest" );
	jclass jclass_ByteArrayInputStream			= env->FindClass( "java/io/ByteArrayInputStream" );

	jmethodID jmethod_getPackageManager			= env->GetMethodID( jclass_Activity, "getPackageManager", "()Landroid/content/pm/PackageManager;" );
	jmethodID jmethod_getPackageName			= env->GetMethodID( jclass_Activity, "getPackageName", "()Ljava/lang/String;" );
	jmethodID jmethod_getPackageInfo			= env->GetMethodID( jclass_PackageManager, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;" );
	jmethodID jmethod_toByteArray				= env->GetMethodID( jclass_Signature, "toByteArray", "()[B" );
	jmethodID jmethod_ByteArrayInputStream		= env->GetMethodID( jclass_ByteArrayInputStream, "<init>", "([B)V" );
	jmethodID jemthod_getInstance				= env->GetStaticMethodID( jclass_CertificateFactory, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;" );
	jmethodID jmethod_generateCertificate		= env->GetMethodID( jclass_CertificateFactory, "generateCertificate", "(Ljava/io/InputStream;)Ljava/security/cert/Certificate;" );
	jmethodID jmethod_MessageDigest_getInstance = env->GetStaticMethodID( jclass_MessageDigest, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;" );
	jmethodID jmethod_getEncoded				= env->GetMethodID( jclass_X509Certificate, "getEncoded", "()[B" );
	jmethodID jmethod_digest					= env->GetMethodID( jclass_MessageDigest, "digest", "([B)[B" );

	jfieldID jfield_GET_SIGNATURES				= env->GetStaticFieldID( jclass_PackageManager, "GET_SIGNATURES", "I" );
	jfieldID jfield_signatures					= env->GetFieldID( jclass_PackageInfo, "signatures", "[Landroid/content/pm/Signature;" );

	jobject			jobject_packageManager		= env->CallObjectMethod( activity_obj, jmethod_getPackageManager );
	jstring			jstring_packageName			= (jstring)env->CallObjectMethod( activity_obj, jmethod_getPackageName );
	jint			jint_flag					= env->GetStaticIntField( jclass_PackageManager, jfield_GET_SIGNATURES );
	jobject			jobject_packageInfo			= env->CallObjectMethod( jobject_packageManager, jmethod_getPackageInfo, jstring_packageName, jint_flag );
	jobjectArray	jobjectArray_signatures		= (jobjectArray)env->GetObjectField( jobject_packageInfo, jfield_signatures );
	jobject			jobject_signature_0			= env->GetObjectArrayElement( jobjectArray_signatures, 0 );
	jbyteArray		jbyteArray_cert				= (jbyteArray)env->CallObjectMethod( jobject_signature_0, jmethod_toByteArray );
	jobject			jobject_input				= env->NewObject( jclass_ByteArrayInputStream, jmethod_ByteArrayInputStream, jbyteArray_cert );
	jobject			jobject_cf					= env->CallStaticObjectMethod( jclass_CertificateFactory, jemthod_getInstance, env->NewStringUTF( "X509" ) );
	jobject			jobject_c					= env->CallObjectMethod( jobject_cf, jmethod_generateCertificate, jobject_input );
	jbyteArray		jbyteArray_cEncoded			= (jbyteArray)env->CallObjectMethod( jobject_c, jmethod_getEncoded );
	jobject			jobject_md					= env->CallStaticObjectMethod( jclass_MessageDigest, jmethod_MessageDigest_getInstance, env->NewStringUTF( "SHA1" ) );
	jbyteArray		jbyteArray_publicKey		= (jbyteArray)env->CallObjectMethod( jobject_md, jmethod_digest, jbyteArray_cEncoded );

	return ByteArray2HexString( jbyteArray_publicKey );
}
