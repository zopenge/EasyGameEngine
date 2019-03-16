//! @file     _jscCore.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscCore Implementation
//----------------------------------------------------------------------------

JSValueRef _jscCore::OnRequireFuncCallback( JSContextRef js_context, JSObjectRef js_function, JSObjectRef js_object, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception )
{
	if ( argumentCount != 1 )
	{
		_jscHelper::ThrowException( js_context, "Reqiure() only needs 1 argument", js_object, exception );
		return JS_MAKE_UNDEFINED( js_context );
	}

	// Get the script file name
	JSStringRefOwner js_string( _jscHelper::CreateJSString( js_context, arguments[0], exception ) );
	AString filename = js_string.ToStringA( );

	// Load the script string
	AString script_string;
	if ( GetScriptModule( )->GetScriptCommander( )->ReadScriptString( filename, script_string ) == _false )
	{
		_jscHelper::ThrowException( js_context, FORMAT_ASTRING_1( "Reqiure() Load '%s' script file failed", script_string.Str( ) ), js_object, exception );
		return JS_MAKE_UNDEFINED( js_context );
	}

	// Convert script string to JS string
	JSStringRefOwner js_script_string( script_string );

	// Execute script
	if ( _jscHelper::EvaluateScript( js_context, js_script_string, js_object, 0, filename.Str( ), _null, exception ) == _false )
	{
		UString err_string = FORMAT_ASTRING_2( "Reqiure() evaluate '%s' script file failed, err:%s", filename.Str( ), _jscHelper::GetJSStringA( js_context, *exception ).Str( ) );

		_jscHelper::ThrowException( js_context, err_string, js_object, exception );
		return JS_MAKE_UNDEFINED( js_context );
	}

	return ::JSValueMakeBoolean( js_context, _true );
}

_ubool _jscCore::OnInitialize( AStringPtr js_core_name, JSContextRef js_context )
{
	JSClassDefinition js_core_class_definition = 
	{
		0,
		kJSClassAttributeNone,

		js_core_name.Str( ),
		_null,

		_null,
		_null,

		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
		_null,
	};

	// Create JS class
	mJSClass = ::JSClassCreate( &js_core_class_definition );
	if ( mJSClass == _null )
		return _false;

	return _true;
}

_void _jscCore::OnFinalize( )
{
	// Release JS class
	if ( mJSClass != _null )
	{
		::JSClassRelease( mJSClass );
		mJSClass = _null;
	}
}

#endif