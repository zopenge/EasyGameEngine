//! @file     _jscException.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscException Implementation
//----------------------------------------------------------------------------

_dword _jscException::GetLineNumber( ) const
{
	JSValueRef line_property = _jscHelper::GetJSObjectProperty( gGlobalJSContext, (JSObjectRef) mJSException, "line" );
	return (_dword) _jscHelper::JSValue2Number( gGlobalJSContext, line_property, _null );
}

WString _jscException::GetMessage( ) const
{
	return _jscHelper::GetJSStringW( gGlobalJSContext, mJSException );
}

#endif