//! @file     androidMessageBox.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidMessageBox Helpful Functions Implementation
//----------------------------------------------------------------------------

static _MESSAGE_BOX_BUTTON_ID TranslateAndroidMessageBoxButtonID( _dword id )
{
	const _dword BUTTON_NEGATIVE	= 0xFFFFFFFE;
	const _dword BUTTON_NEUTRAL		= 0xFFFFFFFD;
	const _dword BUTTON_POSITIVE	= 0xFFFFFFFF;

	switch ( id )
	{
		case BUTTON_NEGATIVE:	return _MBB_ID_NO;
		case BUTTON_NEUTRAL:	return _MBB_ID_CANCEL;
		case BUTTON_POSITIVE:	return _MBB_ID_YES;
		default:
			return _MBB_ID_OK;
	}
}

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_1( void, AndroidUtils, OnDismissMessageBox, jlong user_data )
{
	IMessageBox* message_box = (IMessageBox*) user_data;
	EGE_ASSERT( message_box != _null );

	message_box->GetNotifier( )->OnClickButton( _MBB_ID_NO );
	message_box->Release( );
}

JNI_FUNC_2( void, AndroidUtils, OnClickMessageBoxButton, jint button_id, jlong user_data )
{
	IMessageBox* message_box = (IMessageBox*) user_data;
	EGE_ASSERT( message_box != _null );

	message_box->GetNotifier( )->OnClickButton( TranslateAndroidMessageBoxButtonID( (_dword)button_id ) );
	message_box->Release( );
}

//----------------------------------------------------------------------------
// androidMessageBox Implementation
//----------------------------------------------------------------------------

androidMessageBox::androidMessageBox( )
{
}

androidMessageBox::~androidMessageBox( )
{
}

_void androidMessageBox::Show( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type )
{
	// Let the callback function to release it, so need to increase referenced counter
	this->AddRef( );

	// Get the java utils interface object
	JNIObject& utils = androidJNI::GetInstance( ).GetUtilsObj( );

	// Call method
	C2JString j_title( title );
	C2JString j_content( content );
	C2JString j_yes_text( yes_text );
	C2JString j_no_text( no_text );
	utils.CallStaticVoidMethod( "showDialog", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IJ)V", 
		androidJNI::GetInstance( ).GetContextObj( ), j_title.ToJString( ), j_content.ToJString( ), j_yes_text.ToJString( ), j_no_text.ToJString( ), (jint) type, (jlong) this );
}
