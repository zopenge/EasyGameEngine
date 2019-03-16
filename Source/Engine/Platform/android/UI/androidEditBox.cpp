//! @file     androidEditBox.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_2( bool, AndroidEditBox, OnIsValidCharacter, jint code, jlong user_data )
{
	androidEditBox* edit_box = (androidEditBox*)user_data;
	EGE_ASSERT( edit_box != _null );

	if ( edit_box->mCheckCharacterFunc.IsValid( ) )	
		return edit_box->mCheckCharacterFunc.InvokeR( code );
	else
		return _true;
}

JNI_FUNC_1( void, AndroidEditBox, OnOpenEditBox, jlong user_data )
{
	androidEditBox* edit_box = (androidEditBox*)user_data;
	EGE_ASSERT( edit_box != _null );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_OPEN, "" );
}

JNI_FUNC_2( void, AndroidEditBox, OnHideEditBox, jstring text, jlong user_data )
{
	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	UString text_utf8 = J2CString( text ).ToStringU( );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_HIDE, text_utf8 );
}

JNI_FUNC_2( void, AndroidEditBox, OnReturnEditBox, jstring text, jlong user_data )
{
	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	UString text_utf8 = J2CString( text ).ToStringU( );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_RETURN, text_utf8 );
}

JNI_FUNC_2( void, AndroidEditBox, OnCancelEditBox, jstring text, jlong user_data )
{
	androidEditBox* edit_box = (androidEditBox*) user_data;
	EGE_ASSERT( edit_box != _null );

	UString text_utf8 = J2CString( text ).ToStringU( );

	edit_box->mHandleEventFunc.Invoke( IEditBox::_EVENT_CANCEL, text_utf8 );
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

_ubool androidEditBox::BuildParameters( UString& parameters, _INPUT_TYPE input_type, UStringPtr text )
{
	// AndroidEditoBox.java constant variables:
	// -------------------------------------------------------
	const _dword _KEYBOARD_DEFAULT					= 0;
	const _dword _KEYBOARD_ASCIICAPABLE				= 1;
	const _dword _KEYBOARD_NUMBER_AND_PUNCTUATION	= 2;
	const _dword _KEYBOARD_URL						= 3;
	const _dword _KEYBOARD_NUMBERPAD				= 4;
	const _dword _KEYBOARD_PHONEPAD					= 5;
	const _dword _KEYBOARD_NAMEPHONEPAD				= 6;
	const _dword _KEYBOARD_EMAILADDRESS				= 7;
	const _dword _KEYBOARD_PASSWORD					= 8;
	// -------------------------------------------------------

	_dword jni_input_type = 0;
	switch ( input_type )
	{
		case _INPUT_TYPE_NORMAL:		jni_input_type = _KEYBOARD_DEFAULT; break;
		case _INPUT_TYPE_URL:			jni_input_type = _KEYBOARD_URL; break;
		case _INPUT_TYPE_NUMBER_PAD:	jni_input_type = _KEYBOARD_NUMBERPAD; break;
		case _INPUT_TYPE_PHONE_PAD:		jni_input_type = _KEYBOARD_PHONEPAD; break;
		case _INPUT_TYPE_EMAIL_ADDRESS: jni_input_type = _KEYBOARD_EMAILADDRESS; break;
		case _INPUT_TYPE_PASSWORD:		jni_input_type = _KEYBOARD_PASSWORD; break;
		default:
			return _false;
	}

	parameters += FORMAT_ASTRING_1( "keyboardType:%d\n", jni_input_type );
	parameters += FORMAT_ASTRING_1( "haveOkButton:%d\n", 1 );
	parameters += FORMAT_ASTRING_1( "haveCancelButton:%d\n", 1 );
	parameters += FORMAT_ASTRING_1( "text:%s", text.Str( ) );

	return _true;
}

_ubool androidEditBox::Open( _INPUT_TYPE input_type, UStringPtr text, UStringPtr defaulttext, _dword max_length, const RectF& region )
{
	// Build parameters
	UString params;
	if ( BuildParameters( params, input_type, text ) == _false )
		return _false;

	// Call method
	C2JString jparam( params );
	androidJNI::GetInstance( ).GetEditBoxObj( ).CallStaticVoidMethod( "popupTextInput", "(ILjava/lang/String;J)V", max_length, jparam.ToJString( ), (jlong)this );

	return _true;
}

_ubool androidEditBox::Open( _INPUT_TYPE input_type, WStringPtr text, WStringPtr defaulttext, _dword max_length, const RectF& region )
{
	return Open( input_type, UString( ).FromString( text ), UString( ).FromString( defaulttext ), max_length, region );
}

_void androidEditBox::Close( )
{
	androidJNI::GetInstance( ).GetEditBoxObj( ).CallStaticVoidMethod( "cancelTextInput", "()V" );
}

_void androidEditBox::Commit( )
{
	androidJNI::GetInstance( ).GetEditBoxObj( ).CallStaticVoidMethod( "commitTextInput", "()V" );
}
