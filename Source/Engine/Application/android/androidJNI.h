//! @file     androidINC.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

class JNIObject;

//----------------------------------------------------------------------------
// androidJNIEnv
//----------------------------------------------------------------------------

class androidJNIEnv
{
private:
	_ubool	mIsAttached;
	JNIEnv*	mEnv;

public:
	JNIEnv* operator -> ( )
		{ return mEnv; }

public:
	EGE_GET_ACCESSOR( JNIEnv*, Env )

public:
	EGE_INTERNAL androidJNIEnv( );
	EGE_INTERNAL androidJNIEnv( _ubool is_attached, JNIEnv* env );
	EGE_INTERNAL ~androidJNIEnv( );
};

//----------------------------------------------------------------------------
// androidJNI
//----------------------------------------------------------------------------

//! Thanks for http://android.wooyd.org/JNIExample/#NWD1sCYeT-A to tell us how to use JNI hooker.
class androidJNI
{
	SINGLETON( androidJNI )

public:
	//!	The default JAVA version
	enum { _DEFAULT_JAVA_VERSION = JNI_VERSION_1_4 };

	//!	The JNI interface object
	enum _JNI_INTERFACE_OBJ
	{
		_JNI_OBJ_OS_DEBUG,
		_JNI_OBJ_JNILIB,
		_JNI_OBJ_WEBVIEW,
		_JNI_OBJ_SERVICE,
		_JNI_OBJ_PURCHASE,
		_JNI_OBJ_EDITBOX,
		_JNI_OBJ_RECORDER,
		_JNI_OBJ_UTILS,
		_JNI_OBJ_BASEACTIVITY,

		_JNI_OBJ_MAX_NUMBER,
	};

private:
	JavaVM*				mJavaVM;

	jobject				mAppActivity;
	jobject				mContextObj;
	jobject				mAssetManagerObj;

	AString				mInternalDataPath;
	AString				mExternalDataPath;
	AString				mPackageName;
	AString				mSourceDir;
	_dword				mSDKVersion;
	_dword				mSavedStateSize;
	_byte*				mSavedStateBuffer;
	AConfiguration*		mConfiguration;
	AAssetManager*		mAssetManager;

	JNIObject*			mJNIInterfaceObjs;

private:
	//!	Initialize dumper.
	EGE_INTERNAL _ubool InitDumper( );

	//!	Get the JS-method ID.
	EGE_INTERNAL jmethodID GetJSMethodID( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl );
	//!	Get the static JS-method ID.
	EGE_INTERNAL jmethodID GetStaticJSMethodID( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl );

public:
	EGE_GET_ACCESSOR( JavaVM*, JavaVM )

	EGE_GET_ACCESSOR( jobject, ContextObj )
	EGE_GET_ACCESSOR( jobject, AppActivity )

	EGE_GET_ACCESSOR( AStringPtr, InternalDataPath )
	EGE_GET_ACCESSOR( AStringPtr, ExternalDataPath )
	EGE_GET_ACCESSOR( AStringPtr, PackageName )
	EGE_GET_ACCESSOR( AStringPtr, SourceDir )
	EGE_GET_ACCESSOR( _dword, SDKVersion )
	EGE_GET_ACCESSOR( _dword, SavedStateSize )
	EGE_GET_ACCESSOR( const _byte*, SavedStateBuffer )
	EGE_GET_ACCESSOR( AConfiguration*, Configuration )
	EGE_GET_ACCESSOR( AAssetManager*, AssetManager )

public:
	//!	Initialize.
	EGE_INTERNAL _ubool Initialize( JavaVM* vm );
	//!	Finalize.
	EGE_INTERNAL _void Finalize( );

	//!	Flush configuration.
	EGE_INTERNAL _void FlushConfiguration( );
	//!	Initialize application.
	EGE_INTERNAL _ubool InitializeApplication( JNIEnv* env, jobject activity, jobject context, jobject asset_manager, jstring internal_data_path, jstring external_data_path, jstring package_name, jstring source_dir, jint sdk_version, jbyteArray saved_state );

	//!	Get the JAVA interface object.
	EGE_INTERNAL JNIObject& GetAndroidOSDebugObj( );
	EGE_INTERNAL JNIObject& GetAndroidJNILibObj( );
	EGE_INTERNAL JNIObject& GetWebViewObj( );
	EGE_INTERNAL JNIObject& GetServiceObj( );
	EGE_INTERNAL JNIObject& GetPurchaseObj( );
	EGE_INTERNAL JNIObject& GetEditBoxObj( );
	EGE_INTERNAL JNIObject& GetRecorderObj( );
	EGE_INTERNAL JNIObject& GetUtilsObj( );
	EGE_INTERNAL JNIObject& GetBaseActivityObj( );
	EGE_INTERNAL JNIObject& GetJNIObj( _JNI_INTERFACE_OBJ type );
	EGE_INTERNAL JNIObject* GetJNIObjByPath( AStringPtr path );
	EGE_INTERNAL JNIObject* GetJNIObjByPath( WStringPtr path );

	//!	Create JAVA object.
	EGE_INTERNAL jobject CreateJObject( const _chara* path );
	EGE_INTERNAL JNIObject* CreateJNIObject( const _chara* path );

	//!	Get the JNI env
	EGE_INTERNAL androidJNIEnv GetJNIEnv( );

	//!	Create java hash map object.
	EGE_INTERNAL jobject CreateHashMapObject( );
	EGE_INTERNAL jobject CreateHashMapObject( const Map< UString, UString >& map_object );

	//!	Call JAVA functions.
	EGE_INTERNAL _void CallVoidMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL _ubool CallBooleanMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL _int CallIntMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL _large CallLongMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL jobject CallObjectMethod( jclass j_class, jobject j_object, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	//!	Call JAVA static functions.
	EGE_INTERNAL _void CallStaticVoidMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL _ubool CallStaticBooleanMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL _int CallStaticIntMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
	EGE_INTERNAL jobject CallStaticObjectMethod( jclass j_class, AStringPtr func_name, AStringPtr parameters_decl, _va_list args );
};

//----------------------------------------------------------------------------
// androidJNI Implementation
//----------------------------------------------------------------------------

}