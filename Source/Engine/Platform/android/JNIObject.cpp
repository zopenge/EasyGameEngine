//! @file     JNIObject.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNIObject Implementation
//----------------------------------------------------------------------------

JNIObject::JNIObject( )
{
	mJSObject	= _null;
	mJSClass	= _null;
}

JNIObject::~JNIObject( )
{
	Finalize( );
}

_ubool JNIObject::Initialize( AStringPtr path, _ubool static_only )
{
	if ( static_only )
	{
		androidJNIEnv jni_env = androidJNI::GetInstance( ).GetJNIEnv( );

		// Update info
		mPath = path;

		// Get object's class
		mJSClass = jni_env->FindClass( mPath.Str( ) );
		if ( mJSClass == _null )
		{
			ALOG_ERROR_1( "The '%s' java class is not existing", mPath.Str( ) );
			return _false;
		}

		// Keep the JS class alive
		mJSClass = (jclass) jni_env->NewGlobalRef( (jobject) mJSClass );
		if ( mJSClass == _null )
		{
			ALOG_ERROR_1( "The '%s' java class new global operation failed", mPath.Str( ) );
			return _false;
		}
	}
	else
	{
		// Get the JS object
		jobject js_object = androidJNI::GetInstance( ).CreateJObject( path.Str( ) );
		if ( js_object == _null )
		{
			ALOG_ERROR_1( "The '%s' java interface is not existing", path.Str( ) );
			return _false;
		}

		if ( Initialize( _false, path, js_object ) == _false )
			return _false;
	}

	return _true;
}

_ubool JNIObject::Initialize( _ubool local, AStringPtr path, jobject js_object )
{
	ALOG_TRACE_2( "Initializing java object from '%s' path (local:%d) ...", path.Str( ), (_boolean) local );

	// Get the JNI env
	androidJNIEnv jni_env = androidJNI::GetInstance( ).GetJNIEnv( );

	// Convert to global object if it's local object
	if ( local )
	{
		mJSObject = jni_env->NewGlobalRef( js_object );
		if ( mJSObject == _null )
		{
			ALOG_ERROR_1( "New global '%s' java object from local object failed", path.Str( ) );
			return _false;
		}
	}
	// It's global JS object
	else
	{
		mJSObject = js_object;
		if ( mJSObject == _null )
		{
			ALOG_ERROR_1( "The global '%s' java object is null", path.Str( ) );
			return _false;
		}
	}

	// Update info
	mPath = path;

	// Get object's class
	mJSClass = jni_env->GetObjectClass( mJSObject );
	if ( mJSClass == _null )
	{
		ALOG_ERROR_1( "The '%s' java class is not existing", mPath.Str( ) );
		return _false;
	}

	// Keep the JS class alive
	mJSClass = (jclass) jni_env->NewGlobalRef( (jobject) mJSClass );
	if ( mJSClass == _null )
	{
		ALOG_ERROR_1( "The '%s' java class new global operation failed", mPath.Str( ) );
		return _false;
	}

	ALOG_TRACE_2( "Initialize java object from '%s' path (local:%d) OK", path.Str( ), (_boolean) local );

	return _true;
}

_void JNIObject::Finalize( )
{
	androidJNIEnv jni_env = androidJNI::GetInstance( ).GetJNIEnv( );

	// Release JS object
	if ( mJSObject != _null )
	{
		ALOG_TRACE_2( "Delete (Path: '%s', Object: '0x%.16llx') JS global object", mPath.Str( ), (_qword) mJSObject );
		jni_env->DeleteGlobalRef( mJSObject );

		mJSObject = _null;
	}

	// Release JS class
	if ( mJSClass != _null )
	{
		jni_env->DeleteGlobalRef( mJSClass );
		mJSClass = _null;
	}
}

AStringPtr JNIObject::GetPath( ) const
{
	return mPath;
}

_void JNIObject::CallVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		androidJNI::GetInstance( ).CallVoidMethod( mJSClass, mJSObject, func_name, parameters_decl, args );
	END_VA_LIST( args );
}

_ubool JNIObject::CallBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		_ubool ret = androidJNI::GetInstance( ).CallBooleanMethod( mJSClass, mJSObject, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_int JNIObject::CallIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		_int ret = androidJNI::GetInstance( ).CallIntMethod( mJSClass, mJSObject, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_large JNIObject::CallLongMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		_large ret = androidJNI::GetInstance( ).CallLongMethod( mJSClass, mJSObject, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_void* JNIObject::CallObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		jobject ret =androidJNI::GetInstance( ).CallObjectMethod( mJSClass, mJSObject, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_void JNIObject::CallStaticVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		androidJNI::GetInstance( ).CallStaticVoidMethod( mJSClass, func_name, parameters_decl, args );
	END_VA_LIST( args );
}

_ubool JNIObject::CallStaticBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const 
{
	BEGIN_VA_LIST( args, parameters_decl );
		_ubool ret = androidJNI::GetInstance( ).CallStaticBooleanMethod( mJSClass, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_int JNIObject::CallStaticIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		_int ret = androidJNI::GetInstance( ).CallStaticIntMethod( mJSClass, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}

_void* JNIObject::CallStaticObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const
{
	BEGIN_VA_LIST( args, parameters_decl );
		jobject ret = androidJNI::GetInstance( ).CallStaticObjectMethod( mJSClass, func_name, parameters_decl, args );
	END_VA_LIST( args );

	return ret;
}
