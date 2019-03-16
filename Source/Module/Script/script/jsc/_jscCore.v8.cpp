//! @file     _jscCore.v8.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

//----------------------------------------------------------------------------
// _jscCore Implementation
//----------------------------------------------------------------------------

_void _jscCore::OnRequireFuncCallback( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	JSContextRef js_context = *args.GetIsolate( )->GetCurrentContext( );

	// We only can use 1 argument
	if ( args.Length( ) != 1 )
	{
		_jscHelper::ThrowException( js_context, "Reqiure() only needs 1 argument", _null, _null );
		args.GetReturnValue( ).Set( JS_MAKE_UNDEFINED( js_context ) );
	}

	//// Get the script file name
	//JSStringRefOwner js_string( _jscHelper::CreateJSString( ctx, arguments[0], exception ) );
	//AString filename = js_string.ToStringA( );

	//// Load the script string
	//AString script_string;
	//if ( GetScriptModule( )->GetScriptCommander( )->ReadScriptString( filename, script_string ) == _false )
	//{
	//	_jscHelper::ThrowException( ctx, FORMAT_ASTRING_1( "Reqiure() Load '%s' script file failed", script_string.Str( ) ), thisObject, exception );
	//	return JS_MAKE_UNDEFINED( ctx );
	//}

	//// Convert script string to JS string
	//JSStringRefOwner js_script_string( script_string );

	//// Execute script
	//_jscHelper::EvaluateScript( ctx, js_script_string, thisObject, 0, exception );
	//if ( exception != _null && *exception != _null )
	//{
	//	UString err_string = FORMAT_ASTRING_2( "Reqiure() evaluate '%s' script file failed, err:%s", filename.Str( ), _jscHelper::GetJSStringA( ctx, *exception ).Str( ) );

	//	_jscHelper::ThrowException( ctx, err_string, thisObject, exception );
	//	return JS_MAKE_UNDEFINED( ctx );
	//}

	//return ::JSValueMakeBoolean( ctx, _true );
}

_ubool _jscCore::OnInitialize( AStringPtr js_core_name, JSContextRef js_context )
{
	//Start a context scope
	//v8::Context::Scope context_scope(context);

	////Get the context's global scope (that's where we'll put the constructor)
	//v8::Handle<v8::Object> global = context->Global();

	////create function template for our constructor
	////it will call the constructPoint function
	//v8::Handle<v8::FunctionTemplate> function = v8::FunctionTemplate::New(constructPoint);

	////set the function in the global scope -- that is, set "Point" to the constructor
	//global->Set(v8::String::New("Point"), function->GetFunction());

	return _true;
}

_void _jscCore::OnFinalize( )
{
}

#endif