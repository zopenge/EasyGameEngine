//! @file     _jscHelper.v8.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

//----------------------------------------------------------------------------
// _jscHelper Implementation
//----------------------------------------------------------------------------

_ubool _jscHelper::SetJSObjectPrivateProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name, JSValueRef js_value )
{
	return _false;
}

JSValueRef _jscHelper::GetJSObjectPrivateProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name )
{
	return JS_NULL;
}

_void _jscHelper::SetJSObjectPrivate( JSObjectRef js_object, _void* data )
{

}

_void* _jscHelper::GetJSObjectPrivate( JSObjectRef js_object )
{
	return _null;
}

_ubool _jscHelper::SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name, JSValueRef js_value, JSPropertyAttributes attributes )
{
	return _false;
}

JSValueRef _jscHelper::GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name )
{
	JSValueRef js_value;

	return js_value;
}

JSStringRef _jscHelper::CreateJSStringA( AStringPtr string )
{
	return *v8::String::New( string.Str( ) );
}

JSStringRef _jscHelper::CreateJSStringU( UStringPtr string )
{
	return *v8::String::New( string.Str( ) );
}

JSStringRef _jscHelper::CreateJSStringW( WStringPtr string )
{
	return *v8::String::New( (uint16_t*) string.Str( ), string.GetLength( ) );
}

JSStringRef _jscHelper::CreateJSString( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return JS_NULL_STRING;
}

WString _jscHelper::GetJSStringW( JSStringRef js_string )
{
	return WString( L"" );
}

JSObjectRef _jscHelper::CreateJSFunction( JSContextRef js_context, JSStringRef js_func_name, JSObjectCallAsFunctionCallback js_callback_func )
{
	// Create JS embedded function by name
	JSObjectRef js_func = _null;
	if ( JS_IS_NULL( js_func ) )
		return JS_NULL;

	return js_func;
}

_void _jscHelper::ThrowException( JSContextRef js_context, UStringPtr err_desc, JSObjectRef js_object, JSValueRef* js_exception )
{
	js_context->GetIsolate( )->ThrowException( v8::String::New( err_desc.Str( ) ) );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func )
{
	if ( JS_IS_FUNC( js_context, js_func ) == _false )
		return JS_MAKE_NULL( js_context );

	// The return value of function
	JSValueRef js_value;

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
	js_value = _null;

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
	return _false;
}

JSValueRef _jscHelper::MakeJSValueAsLong( JSContextRef js_context, _int value )
{
	return JS_MAKE_NULL( js_context );
}

JSValueRef _jscHelper::MakeJSValueAsDword( JSContextRef js_context, _dword value )
{
	return JS_MAKE_NULL( js_context );
}

JSValueRef _jscHelper::MakeJSValueAsFloat( JSContextRef js_context, _float value )
{
	return JS_MAKE_NULL( js_context );
}

JSValueRef _jscHelper::MakeJSValueAsDouble( JSContextRef js_context, _double value )
{
	return JS_MAKE_NULL( js_context );
}

_double _jscHelper::JSValue2Number( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	return 0.0;
}

JSValueRef _jscHelper::MakeJSValueAsString( JSContextRef js_context, JSStringRef js_string )
{
	return JS_NULL;
}

JSObjectRef _jscHelper::MakeJSObject( JSContextRef js_context, JSClassRef js_class, _void* data )
{
	return JS_NULL;
}

#endif