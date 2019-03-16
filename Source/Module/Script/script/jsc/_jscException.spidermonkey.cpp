//! @file     _jscException.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscException Implementation
//----------------------------------------------------------------------------

_dword _jscException::GetLineNumber( ) const
{
	_dword line_number = 0;

	if ( JSVAL_IS_INT( mJSException ) )
		::JS_ValueToInt32( gGlobalJSContext, mJSException, (int32_t*) &line_number );

	return line_number;
}

WString _jscException::GetMessage( ) const
{
	if ( JSVAL_IS_STRING( mJSException ) )
	{
		JSStringRef err_string = ::JS_ValueToString( gGlobalJSContext, mJSException );
		if ( err_string == _null )
			return WString( L"" );

		return WString( ).FromString( _ENCODING_ANSI, ::JS_EncodeString( gGlobalJSContext, err_string ) );
	}

	return WString( L"" );
}

#endif