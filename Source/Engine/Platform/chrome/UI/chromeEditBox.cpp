//! @file     chromeEditBox.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromeEditBox Implementation
//----------------------------------------------------------------------------

chromeEditBox::chromeEditBox( )
{
	
}

chromeEditBox::~chromeEditBox( )
{
}

_ubool chromeEditBox::Open( _INPUT_TYPE input_type, _ubool is_password, UStringPtr text, UStringPtr default_text, _dword max_length )
{
	return _true;
}

_ubool chromeEditBox::Open( _INPUT_TYPE input_type, _ubool is_password, WStringPtr text, WStringPtr default_text, _dword max_length )
{
	return _true;
}

_void chromeEditBox::Close( )
{

}