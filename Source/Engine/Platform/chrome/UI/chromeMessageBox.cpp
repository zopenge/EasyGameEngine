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

JNI_FUNC_1( void, AndroidUtils, OnDismissMessageBox, jint user_data, _E18B025EC60A4DE790D1F0DFE20D7853 )
{
	IMessageBox* message_box = (IMessageBox*) user_data;
	EGE_ASSERT( message_box != _null );

	message_box->GetNotifier( )->OnClickButton( _MBB_ID_NO );
	message_box->Release( );
}

JNI_FUNC_2( void, AndroidUtils, OnClickMessageBoxButton, jint button_id, jint user_data, _C03E0AFA8B174F86914ADE47C207866E )
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

_void androidMessageBox::Show( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type )
{
	// Let the callback function to release it, so need to increase referenced counter
	this->AddRef( );

	// Call method
	C2JString j_title( title );
	C2JString j_content( content );
	androidJNI::GetInstance( ).GetUtilsInterfaceObj( ).CallStaticVoidMethod( "showDialog", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;II)V", 
		androidJNI::GetInstance( ).GetContextObj( ), j_title.GetJString( ), j_content.GetJString( ), (jint) type, (jint) this );
}
