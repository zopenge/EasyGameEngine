//! @file     _jscFunction.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscFunction Implementation
//----------------------------------------------------------------------------

_jscFunction::_jscFunction( const AStringObj& func_name )
{
	mFuncName = func_name;
}

_jscFunction::~_jscFunction( )
{
}

AStringPtr _jscFunction::GetName( ) const
{
	return mFuncName.Str( );
}

_scriptValuePassRef _jscFunction::Invoke( )
{
	// Get JS function
	JSObjectRef js_func = _jscHelper::GetJSFunction( gGlobalJSContext, mFuncName.Str( ) );
	if ( js_func == _null )
	{
		ALOG_ERROR_1( "Get '%s' JS function failed", mFuncName.Str( ) );
		return _null;
	}

	// Call JS function
	JSValueRef js_value = _jscHelper::CallJSFunction( gGlobalJSContext, js_func );

	// Feedback return value
	return new _jscValue( js_value );
}

_scriptValuePassRef _jscFunction::Invoke( const VariableArray& vars )
{
	if ( vars.Number( ) == 0 )
		return Invoke( );

	// Get JS function
	JSObjectRef js_func = _jscHelper::GetJSFunction( gGlobalJSContext, mFuncName.Str( ) );
	if ( js_func == _null )
	{
		ALOG_ERROR_1( "Get '%s' JS function failed", mFuncName.Str( ) );
		return _null;
	}

	// Call JS function
	JSValueRef js_value = _jscHelper::CallJSFunction( gGlobalJSContext, js_func, vars );

	// Feedback return value
	return new _jscValue( js_value );
}

#endif