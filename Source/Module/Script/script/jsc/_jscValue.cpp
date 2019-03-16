//! @file     _jscValue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscValue Implementation
//----------------------------------------------------------------------------

_jscValue::_jscValue( JSValueRef js_value )
{
	mJSValue	= js_value;
}

_jscValue::~_jscValue( )
{
}

const _void* _jscValue::GetPointer( ) const
{
	EGE_ASSERT( 0 );
	return _null;
}

_double _jscValue::GetDouble( ) const 
{
	return _jscHelper::JSValue2Number( gGlobalJSContext, mJSValue, _null );
}

WString	_jscValue::GetStringW( ) const
{
	JSStringRefOwner js_string( _jscHelper::CreateJSString( gGlobalJSContext, mJSValue, _null ) );
	
	return js_string.ToStringW( );
}

#endif