//! @file     _jscCore.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscCore Helpful Functions Implementation
//----------------------------------------------------------------------------

#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_

static JSBool OnAddJSProperty( JSContext* js_context, JSObject* js_object, jsid js_id, jsval* js_value )
{
	return _true;
}

static JSBool OnDelJSProperty( JSContext* js_context, JSObject* js_object, jsid js_id, jsval* js_value )
{
	return _true;
}

static JSBool OnGetJSProperty( JSContext* js_context, JSObject* js_object, jsid js_id, jsval* js_value )
{
	return _true;
}

static JSBool OnSetJSProperty( JSContext* js_context, JSObject* js_object, jsid js_id, JSBool js_strict, jsval* js_value )
{
	return _true;
}

static JSBool OnJSEnumerate( JSContext* js_context, JSObject* js_object )
{
	return _true;
}

static JSBool OnJSResolve( JSContext* js_context, JSObject* js_object, jsid js_id )
{
	return _true;
}

static JSBool OnJSConvert( JSContext* js_context, JSObject* js_object, JSType js_type, jsval* js_value )
{
	return _true;
}

static void OnJSFinalize( JSContext* js_context, JSObject* js_object )
{

}

#else

static JSBool OnAddJSProperty( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JS::MutableHandle<JS::Value> vp )
{
	return _true;
}

static JSBool OnDelJSProperty( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool *succeeded )
{
	return _true;
}

static JSBool OnGetJSProperty( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JS::MutableHandle<JS::Value> vp )
{
	return _true;
}

static JSBool OnSetJSProperty( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool strict, JS::MutableHandle<JS::Value> vp )
{
	return _true;
}

static JSBool OnJSEnumerate( JSContext *cx, JS::Handle<JSObject*> obj )
{
	return _true;
}

static JSBool OnJSResolve( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id )
{
	return _true;
}

static JSBool OnJSConvert( JSContext *cx, JS::Handle<JSObject*> obj, JSType type, JS::MutableHandle<JS::Value> vp )
{
	return _true;
}

static void OnJSFinalize( JSFreeOp *fop, JSObject *obj )
{

}

#endif

//----------------------------------------------------------------------------
// _jscCore Implementation
//----------------------------------------------------------------------------

JSBool _jscCore::OnRequireFuncCallback( JSContext* js_context, unsigned argc, jsval* vp )
{
	if ( argc != 1 )
	{
		_jscHelper::ThrowException( js_context, "Reqiure() only needs 1 argument", gGlobalJSObject, _null );
		return JS_FALSE;
	}

	// Get the script file name
	JSStringRef js_script_filename;
	if ( ::JS_ConvertArguments( js_context, argc, JS_ARGV( js_context, vp ), "S", &js_script_filename ) == _false )
		return JS_FALSE;

	// Get the script file name
	AString filename = JSStringRefOwner( js_script_filename ).ToStringA( );

	// Load the script string
	AString script_string;
	if ( GetScriptModule( )->GetScriptCommander( )->ReadScriptString( filename, script_string ) == _false )
	{
		_jscHelper::ThrowException( js_context, FORMAT_ASTRING_1( "Reqiure() Load '%s' script file failed", script_string.Str( ) ), gGlobalJSObject, _null );
		return JS_FALSE;
	}

	// Convert script string to JS string
	JSStringRefOwner js_script_string( script_string );

	// Execute script
	JSValueRef js_exception;
	if ( _jscHelper::EvaluateScript( js_context, js_script_string, gGlobalJSObject, 0, filename, _null, &js_exception ) == _false )
	{
		_jscException jsc_exception( js_exception );

		WLOG_ERROR_2( L"Evaluate script failed when process Require() command:\n\t(%d)%s", jsc_exception.GetLineNumber( ), jsc_exception.GetMessage( ).Str( ) );

		return JS_FALSE;
	}

	return JS_TRUE;
}

_ubool _jscCore::OnInitialize( AStringPtr js_core_name, JSContextRef js_context )
{
	// Create JS class
	mJSClass = new JSClass;
	EGE_MEM_SET( mJSClass, 0, sizeof( JSClass ) );

	// Initialize JS class
	mJSClass->name			= GetStringTable( )->GetRefString( js_core_name ).Str( );
	mJSClass->flags			= JSCLASS_HAS_PRIVATE | JSCLASS_HAS_RESERVED_SLOTS(2);
	mJSClass->addProperty	= OnAddJSProperty;
	mJSClass->delProperty	= OnDelJSProperty;
	mJSClass->getProperty	= OnGetJSProperty;
	mJSClass->setProperty	= OnSetJSProperty;
	mJSClass->enumerate		= OnJSEnumerate;
	mJSClass->resolve		= OnJSResolve;
	mJSClass->convert		= OnJSConvert;
	mJSClass->finalize		= OnJSFinalize;

	return _true;
}

_void _jscCore::OnFinalize( )
{
	EGE_DELETE( mJSClass );
}

#endif