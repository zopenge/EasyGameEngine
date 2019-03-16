//! @file     _jscVM.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscVM Implementation
//----------------------------------------------------------------------------

_jscVM::_jscVM( )
{
}

_jscVM::~_jscVM( )
{
}

_ubool _jscVM::Initialize( )
{
	return _true;
}

_scriptFunctionPassRef _jscVM::GetScriptFunction( AStringPtr func_name )
{
	return new _jscFunction( func_name );
}

_ubool _jscVM::LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename )
{
	if ( buffer == _null || size == 0 )
		return _false;

	// Copy the JS script string
	JSStringRefOwner js_script_string( buffer, size );
	if ( js_script_string.IsNull( ) )
	{
		WLOG_ERROR( L"String encoding is invalid, convert to UTF-8 failed" );
		return _false;
	}

	// Execute script
	JSValueRef js_exception;
	if ( _jscHelper::EvaluateScript( gGlobalJSContext, js_script_string, gGlobalJSObject, 0, filename, &mJSResult, &js_exception ) == _false )
	{
		_jscException jsc_exception( js_exception );

		WLOG_ERROR_2( L"Evaluate script failed:\n\t(%d)%s", jsc_exception.GetLineNumber( ), jsc_exception.GetMessage( ).Str( ) );

		return _false;
	}

	return _true;
}

#endif