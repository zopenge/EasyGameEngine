//! @file     androidEditBox.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_2( void, AndroidEditBox, OnHideEditBox, jstring text, jint user_data )
{
	Platform::OutputDebugString( "JNI_FUNC_2( void, AndroidEditBox, OnHideEditBox, jstring text, jint user_data )" );

	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_HIDE, JNIString( env, text ).ToUString( ) );
	WLOG_TRACE_1( L"androidEditBox::OnHideEditBox( )(env:0x%x)", (_dword) env );
}

JNI_FUNC_2( void, AndroidEditBox, OnReturnEditBox, jstring text, jint user_data )
{
	Platform::OutputDebugString( "JNI_FUNC_2( void, AndroidEditBox, OnReturnEditBox, jstring text, jint user_data )" );

	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_RETURN, JNIString( env, text ).ToUString( ) );
	WLOG_TRACE_1( L"androidEditBox::OnReturnEditBox( )(env:0x%x)", (_dword) env );
}

JNI_FUNC_2( void, AndroidEditBox, OnCancelEditBox, jstring text, jint user_data )
{
	Platform::OutputDebugString( "JNI_FUNC_2( void, AndroidEditBox, OnCancelEditBox, jstring text, jint user_data )" );

	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_CANCEL, JNIString( env, text ).ToUString( ) );
	WLOG_TRACE_1( L"androidEditBox::OnCancelEditBox( )(env:0x%x)", (_dword) env );
}

//----------------------------------------------------------------------------
// androidEditBox Implementation
//----------------------------------------------------------------------------

androidEditBox::androidEditBox( )
{
}

androidEditBox::~androidEditBox( )
{
}

_ubool androidEditBox::BuildParameters( UString& parameters, _INPUT_TYPE input_type, _ubool is_password, UStringPtr text )
{
	ENABLE_STRINGBUFFER_MACROS_ANSI( );

	_dword jni_input_type = 0;
	switch ( input_type )
	{
		case _INPUT_TYPE_NORMAL: break;
		case _INPUT_TYPE_URL: jni_input_type = 3; break;
		case _INPUT_TYPE_NUMBER_PAD: jni_input_type = 4; break;
		case _INPUT_TYPE_PHONE_PAD: jni_input_type = 6; break;
		case _INPUT_TYPE_EMAIL_ADDRESS: jni_input_type = 7; break;
		default:
			return _false;
	}

	if ( jni_input_type != 0 )
		parameters += FORMAT_ASTRING_1( "keyboardType:%d\n", jni_input_type );

	parameters += FORMAT_ASTRING_1( "haveOkButton:%d\n", 1 );
	parameters += FORMAT_ASTRING_1( "haveCancelButton:%d\n", 1 );
	parameters += FORMAT_ASTRING_1( "userData:%d\n", (_dword) this );
	parameters += FORMAT_ASTRING_1( "isPassword:%d\n", !!is_password );
	parameters += FORMAT_ASTRING_1( "text:%s", text.Str( ) );

	return _true;
}

_ubool androidEditBox::Open( _INPUT_TYPE input_type, _ubool is_password, UStringPtr text )
{
	androidJNIEnv jni_env = androidJNI::GetJNIEnv( );

	// Find edit box class
	jclass jni_edit_box_class = jni_env->GetObjectClass( androidJNI::sEditBoxInterfaceObject );
	if ( jni_edit_box_class == _null )
	{
		ALOG_ERROR( "The AndroidEditBox java class is not existing" );
		return _false;
	}

	// Build parameters
	UString params;
	if ( BuildParameters( params, input_type, is_password, text ) == _false )
		return _false;

	// Build JNI parameters string
	jstring jparam = jni_env->NewStringUTF(params.Str( ));
	EGE_ASSERT( jparam != _null );

	// Get the method
	jmethodID jmid = jni_env->GetStaticMethodID(jni_edit_box_class, "popupTextInput", "(Ljava/lang/String;)V");
	EGE_ASSERT( jmid != _null );

	// Call method
	jni_env->CallStaticVoidMethod(jni_edit_box_class, jmid, jparam);

	// Release parameters
	jni_env->ReleaseStringUTFChars(jparam, jni_env->GetStringUTFChars(jparam, 0));
	jni_env->DeleteLocalRef(jparam);

	return _true;
}

_void androidEditBox::Close( )
{

}