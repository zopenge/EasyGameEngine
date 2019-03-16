//! @file     _jscHelper.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscHelper Implementation
//----------------------------------------------------------------------------

_ubool _jscHelper::SetJSObjectPrivate( JSObjectRef js_object, _void* data )
{
	return ::JSObjectSetPrivate( js_object, data );
}

_void* _jscHelper::GetJSObjectPrivate( JSObjectRef js_object )
{
	return ::JSObjectGetPrivate( js_object );
}

_ubool _jscHelper::SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name, JSValueRef js_value, JSPropertyAttributes attributes )
{
	JSValueRef js_exception = _null;
	::JSObjectSetProperty( js_context, js_object, js_name, js_value, attributes, &js_exception );
	if ( js_exception != _null )
	{
		WLOG_ERROR_1( L"Set JS object property failed, %s", GetJSStringW( js_context, js_exception ).Str( ) );
		return _false;
	}

	return _true;
}

JSValueRef _jscHelper::GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name )
{
	JSValueRef js_value;

	JSValueRef js_exception = _null;
	js_value = ::JSObjectGetProperty( js_context, js_object, js_name, &js_exception );
	if ( js_value == _null )
	{
		WLOG_ERROR_1( L"Set JS object property failed, %s", GetJSStringW( js_context, js_exception ).Str( ) );
		return _null;
	}

	return js_value;
}

JSStringRef _jscHelper::CreateJSStringA( AStringPtr string )
{
	return ::JSStringCreateWithUTF8CString( string.Str( ) );
}

JSStringRef _jscHelper::CreateJSStringU( UStringPtr string )
{
	return ::JSStringCreateWithUTF8CString( string.Str( ) );
}

JSStringRef _jscHelper::CreateJSStringW( WStringPtr string )
{
	return ::JSStringCreateWithCharacters( (const JSChar*) string.Str( ), string.GetLength( ) );
}

JSStringRef _jscHelper::CreateJSString( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return ::JSValueToStringCopy( js_context, js_value, js_exception );
}

WString _jscHelper::GetJSStringW( JSStringRef js_string )
{
	return WString( (const _charw*) ::JSStringGetCharactersPtr( js_string ), ::JSStringGetLength( js_string ) );
}

JSObjectRef _jscHelper::CreateJSFunction( JSContextRef js_context, JSStringRef js_func_name, JSObjectCallAsFunctionCallback js_callback_func )
{
	// Create JS embedded function by name
	JSObjectRef js_func = ::JSObjectMakeFunctionWithCallback( js_context, js_func_name, js_callback_func );
	if ( JS_IS_NULL( js_func ) )
		return JS_NULL;

	return js_func;
}

_void _jscHelper::ThrowException( JSContextRef js_context, UStringPtr err_desc, JSObjectRef js_object, JSValueRef* js_exception )
{
	_jscHelper::EvaluateScript( js_context, _jscHelper::CreateJSStringU( err_desc ), js_object, 1, "", _null, js_exception );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func )
{
	if ( JS_IS_FUNC( js_context, js_func ) == _false )
		return JS_MAKE_NULL( js_context );

	// The return value of function
	JSValueRef js_value;

	JSValueRef js_exception = _null;
	js_value = ::JSObjectCallAsFunction( js_context, js_func, _null, 0, _null, &js_exception ); 
	if ( js_exception != _null )
	{
		WLOG_ERROR_1( L"Call JS function failed, %s", GetJSStringW( js_context, js_exception ).Str( ) );
		return _null;
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
	JSValueRef js_exception = _null;
	js_value = ::JSObjectCallAsFunction( js_context, js_func, _null, js_arguments.Number( ), js_arguments.GetBuffer( ), &js_exception ); 
	if ( js_exception != _null )
	{
		WLOG_ERROR_1( L"Set JS object property failed, %s", GetJSStringW( js_context, js_exception ).Str( ) );
		return ::JSValueMakeNull( js_context );
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
	JSValueRef js_value = ::JSEvaluateScript( js_context, js_script, js_object, _jscHelper::CreateJSStringA( script_filename ), starting_line_number, js_exception );
	if ( JS_IS_VALID_VALUE( js_exception ) )
		return _false;

	// Feedback return value
	if ( js_ret_value != _null )
		*js_ret_value = js_value;

	return _true;
}

JSValueRef _jscHelper::MakeJSValueAsLong( JSContextRef js_context, _int value )
{
	return ::JSValueMakeNumber( js_context, (_double) value );
}

JSValueRef _jscHelper::MakeJSValueAsDword( JSContextRef js_context, _dword value )
{
	return ::JSValueMakeNumber( js_context, (_double) value );
}

JSValueRef _jscHelper::MakeJSValueAsFloat( JSContextRef js_context, _float value )
{
	return ::JSValueMakeNumber( js_context, (_double) value );
}

JSValueRef _jscHelper::MakeJSValueAsDouble( JSContextRef js_context, _double value )
{
	return ::JSValueMakeNumber( js_context, value );
}

_double _jscHelper::JSValue2Number( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return ::JSValueToNumber( js_context, js_value, js_exception );
}

_int _jscHelper::JSValue2Long( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return (_int) ::JSValueToNumber( js_context, js_value, js_exception );
}

_dword _jscHelper::JSValue2Dword( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return (_dword) ::JSValueToNumber( js_context, js_value, js_exception );
}

JSValueRef _jscHelper::MakeJSValueAsString( JSContextRef js_context, JSStringRef js_string )
{
	return ::JSValueMakeString( js_context, js_string );
}

JSObjectRef _jscHelper::MakeJSObject( JSContextRef js_context, JSClassRef js_class, _void* data )
{
	return ::JSObjectMake( js_context, js_class, data );
}

#endif