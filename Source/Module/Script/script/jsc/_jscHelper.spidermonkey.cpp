//! @file     _jscHelper.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscHelper Helpful Functions Implementation
//----------------------------------------------------------------------------

static JSStringRef BuildPrivateKey( JSStringRef js_name )
{
	return _jscHelper::CreateJSStringA( _jscHelper::GetJSStringA( js_name ) + "_private_" );
}

//----------------------------------------------------------------------------
// _jscHelper Implementation
//----------------------------------------------------------------------------

_ubool _jscHelper::SetJSObjectPrivate( JSObjectRef js_object, _void* data )
{
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	::JS_SetPrivate( gGlobalJSContext, js_object, data );
#else
	::JS_SetPrivate( js_object, data );
#endif
	return _true;
}

_void* _jscHelper::GetJSObjectPrivate( JSObjectRef js_object )
{
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	return ::JS_GetPrivate( gGlobalJSContext, js_object );
#else
	return ::JS_GetPrivate( js_object );
#endif
}

_ubool _jscHelper::SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name, JSValueRef js_value, JSPropertyAttributes attributes )
{
	JSAutoByteString name( js_context, js_name );
	return ::JS_SetProperty( js_context, js_object, name.ptr( ), &js_value );
}

JSValueRef _jscHelper::GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name )
{
	JSValueRef js_value;

	JSAutoByteString name( js_context, js_name );
	::JS_GetProperty( js_context, js_object, name.ptr( ), &js_value );

	return js_value;
}

JSStringRef _jscHelper::CreateJSStringA( AStringPtr string )
{
	return ::JS_NewStringCopyZ( gGlobalJSContext, string.Str( ) );
}

JSStringRef _jscHelper::CreateJSStringU( UStringPtr string )
{
	return _jscHelper::CreateJSStringW( WString( ).FromString( string ) );
}

JSStringRef _jscHelper::CreateJSStringW( WStringPtr string )
{
	return ::JS_NewUCStringCopyZ( gGlobalJSContext, (const jschar*) string.Str( ) );
}

JSStringRef _jscHelper::CreateJSString( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	if ( JSVAL_IS_STRING( js_value ) )
		return JSVAL_TO_STRING( js_value );
	else
		return ::JS_NewUCStringCopyZ( js_context, (const jschar*) L"" );
}

WString _jscHelper::GetJSStringW( JSStringRef js_string )
{
	return WString( (const _charw*) ::JS_GetStringCharsZ( gGlobalJSContext, js_string ) );
}

JSObjectRef _jscHelper::CreateJSFunction( JSContextRef js_context, JSStringRef js_func_name, JSObjectCallAsFunctionCallback js_callback_func )
{
	// Create JS embedded function by name
	JSAutoByteString func_name( js_context, js_func_name );
	JSObjectRef js_func = (JSObject*) ::JS_DefineFunction( js_context, gGlobalJSObject, func_name.ptr( ), (JSNative) js_callback_func, 0, 0 );
	if ( JS_IS_NULL( js_func ) )
		return JS_NULL;

	return js_func;
}

_void _jscHelper::ThrowException( JSContextRef js_context, UStringPtr err_desc, JSObjectRef js_object, JSValueRef* js_exception )
{
	JSErrorReport js_err_report = {0};
	js_err_report.errorNumber	= 1;

	::JS_ThrowReportedError( js_context, err_desc.Str( ), &js_err_report );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func )
{
	if ( JS_IS_FUNC( js_context, js_func ) == _false )
		return JS_MAKE_NULL( js_context );

	// The return value of function
	JSValueRef js_value;
	if ( ::JS_CallFunction( js_context, gGlobalJSObject, (JSFunction*) js_func, 0, _null, &js_value ) == _false )
	{
		_jscException jsc_exception( js_value );

		WLOG_ERROR_2( L"Call JS function failed:\n\t(%d)%s", jsc_exception.GetLineNumber( ), jsc_exception.GetMessage( ).Str( ) );
		return JS_MAKE_NULL( js_context );
	}

	return js_value;
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const VariableArray& args )
{
	EGE_ASSERT( js_func != _null );

	// Build JS arguments
	Array< JSValueRef > js_arguments;
	for ( _dword i = 0; i < args.Number( ); i ++ )
		js_arguments.Append( BuildJSVAlue( js_context, args[i] ) );

	// The return value of function
	JSValueRef js_value;

	// Call JS function
	if ( ::JS_CallFunction( js_context, gGlobalJSObject, (JSFunction*) js_func, js_arguments.Number( ), js_arguments.GetBuffer( ), &js_value ) == _false )
	{
		return JS_MAKE_NULL( js_context );
	}

	// Free JS arguments resources
	for ( _dword i = 0; i < js_arguments.Number( ); i ++ )
	{
		switch ( args[i].GetType( ) )
		{
			case Variable::_TYPE_ID_WSTRING:
			{
				JS_STRING_RELEASE( js_arguments[i] );
			}
			break;

			default:
				break;
		}
	}

	return js_value;
}

_ubool _jscHelper::EvaluateScript( JSContextRef js_context, JSStringRef js_script, JSObjectRef js_object, int starting_line_number, AStringPtr script_filename, JSValueRef* js_ret_value, JSValueRef* js_exception )
{
	JSValueRef js_value = JS_MAKE_NULL( js_context );
	JSAutoByteString script( js_context, js_script );

	// Clear JS exception
	if ( js_exception != _null )
		*js_exception = JS_MAKE_NULL( js_context );

	if ( ::JS_EvaluateScript( js_context, js_object, script.ptr( ), Platform::StringLength( script.ptr( ) ), script_filename.Str( ), 1, &js_value ) == _false )
	{
		// Feedback JS exception
		if ( js_exception != _null )
			*js_exception = js_value;

		return _false;
	}

	// Feedback return value
	if ( js_ret_value != _null )
		*js_ret_value = js_value;

	return _true;
}

JSValueRef _jscHelper::MakeJSValueAsLong( JSContextRef js_context, _int value )
{
	return INT_TO_JSVAL( value );
}

JSValueRef _jscHelper::MakeJSValueAsDword( JSContextRef js_context, _dword value )
{
	return UINT_TO_JSVAL( value );
}

JSValueRef _jscHelper::MakeJSValueAsFloat( JSContextRef js_context, _float value )
{
	return DOUBLE_TO_JSVAL( (_double) value );
}

JSValueRef _jscHelper::MakeJSValueAsDouble( JSContextRef js_context, _double value )
{
	return DOUBLE_TO_JSVAL( value );
}

_double _jscHelper::JSValue2Number( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	if ( JSVAL_IS_DOUBLE( js_value ) )
		return JSVAL_TO_DOUBLE( js_value );
	else if ( JSVAL_IS_BOOLEAN( js_value ) )
		return (_double) JSVAL_TO_BOOLEAN( js_value );
	else if ( JSVAL_IS_INT( js_value ) )
		return (_double) JSVAL_TO_INT( js_value );
	else
		return 0;
}

_int _jscHelper::JSValue2Long( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	if ( JSVAL_IS_INT( js_value ) )
		return JSVAL_TO_INT( js_value );
	else if ( JSVAL_IS_BOOLEAN( js_value ) )
		return (_dword) JSVAL_TO_BOOLEAN( js_value );
	else if ( JSVAL_IS_DOUBLE( js_value ) )
		return (_dword) JSVAL_TO_DOUBLE( js_value );
	else
		return 0;
}

_dword _jscHelper::JSValue2Dword( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	if ( JSVAL_IS_INT( js_value ) )
		return JSVAL_TO_INT( js_value );
	else if ( JSVAL_IS_BOOLEAN( js_value ) )
		return (_dword) JSVAL_TO_BOOLEAN( js_value );
	else if ( JSVAL_IS_DOUBLE( js_value ) )
		return (_dword) JSVAL_TO_DOUBLE( js_value );
	else
		return 0;
}

JSValueRef _jscHelper::MakeJSValueAsString( JSContextRef js_context, JSStringRef js_string )
{
	return STRING_TO_JSVAL( js_string );
}

JSObjectRef _jscHelper::MakeJSObject( JSContextRef js_context, JSClassRef js_class, _void* data )
{
	JSObjectRef js_object = ::JS_NewObject( js_context, js_class, _null, _null );
	if ( js_object == _null )
		return _null;

	_jscHelper::SetJSObjectPrivate( js_object, data );
	
	return js_object;
}

#endif