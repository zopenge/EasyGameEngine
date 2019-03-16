//! @file     winMessageBox.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winMessageBox Helpful Functions Implementation
//----------------------------------------------------------------------------

static _dword TranslateMessageBoxType( _MESSAGE_BOX_TYPE type )
{
	switch ( type )
	{
		case _MBT_OK:					return MB_OK;
		case _MBT_OK_CANCEL:			return MB_OKCANCEL;
		case _MBT_ABORT_RETRY_IGNORE:	return MB_ABORTRETRYIGNORE;
		case _MBT_YES_NO_CANCEL:		return MB_YESNOCANCEL;
		case _MBT_YES_NO:				return MB_YESNO;
		case _MBT_RETRY_CANCEL:			return MB_RETRYCANCEL;
		default:
			return 0;
	}
}

static _MESSAGE_BOX_BUTTON_ID TranslateMessageBoxButtonID( _dword id )
{
	switch ( id )
	{
		case IDOK:		return _MBB_ID_OK;
		case IDCANCEL:	return _MBB_ID_CANCEL;
		case IDABORT:	return _MBB_ID_ABORT;
		case IDRETRY:	return _MBB_ID_RETRY;
		case IDIGNORE:	return _MBB_ID_IGNORE;
		case IDYES:		return _MBB_ID_YES;
		case IDNO:		return _MBB_ID_NO;
		default:
			return _MBB_ID_OK;
	}
}

//----------------------------------------------------------------------------
// winMessageBox Implementation
//----------------------------------------------------------------------------

winMessageBox::winMessageBox( )
{
}

winMessageBox::~winMessageBox( )
{
}

_void winMessageBox::Show( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type )
{
	_dword retval = ::MessageBoxW( _null, content.Str( ), title.Str( ), TranslateMessageBoxType( type ) | MB_SETFOREGROUND | MB_DEFAULT_DESKTOP_ONLY );

	mNotifier->OnClickButton( TranslateMessageBoxButtonID( retval ) );
}
