//! @file     _jscHooker.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscHooker Implementation
//----------------------------------------------------------------------------

_jscHooker::_jscHooker( _jscModule* jsc_module )
{
	mJSCmodule = jsc_module;
}

_jscHooker::~_jscHooker( )
{
}

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

_void _jscHooker::OnHookJSFunctionCallback( const v8::FunctionCallbackInfo< v8::Value >& args )
{

}

#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

JSValueRef _jscHooker::OnHookJSFunctionCallback( JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception )
{
	// We only accept the JS function object with its name
	if ( argumentCount != 2 )
	{  
		*exception = _jscHelper::MakeJSValueAsString( ctx, _jscHelper::CreateJSStringA( "JS function argument is invalid, you must provide 'name' and 'func' both" ) );  
		return JS_MAKE_NULL( ctx );  
	}  

	// Get the JSC module
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( thisObject );
	EGE_ASSERT( jsc_module != _null );

	// Get the JSC hooker
	_jscHooker* jsc_hooker = jsc_module->GetJSCHooker( );
	EGE_ASSERT( jsc_hooker != _null );

	// Get the JS function name
	JSStringRefOwner js_func_name( _jscHelper::CreateJSString( ctx, arguments[0], _null ) );  
	if ( js_func_name.IsNull( ) )
		return JS_MAKE_NULL( ctx );  

	// Get the JS function object
	JSObjectRef js_func_obj = (JSObjectRef) arguments[1];
	if ( JS_IS_FUNC( ctx, js_func_obj ) == _false )
		return JS_MAKE_NULL( ctx );  

	// Register JS function hooker
	jsc_hooker->mJSFuncMap[ GetStringTable( )->GetRefString( js_func_name.ToStringA( ) ) ] = js_func_obj;

	// Set JSC hooker as property of global object
	if ( _jscHelper::SetJSObjectPrivatePropertyData( ctx, thisObject, JSStringRefOwner( js_func_name.ToStringA( ) + "_Hooker" ), js_func_obj ) == _false )
		return _false;

	return JS_MAKE_NULL( ctx );
}

#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

_void _jscHooker::OnHookJSFunctionCallback( JSContext* js_context, unsigned argc, jsval* vp )
{

}

#endif

_ubool _jscHooker::Initialize( JSContextRef js_context, JSObjectRef js_object )
{
	if ( js_object == _null )
		return _false;

	if ( _jscHelper::RegisterJSFunction( js_context, js_object, "Hook", OnHookJSFunctionCallback, this ) == _false )
		return _false;

	return _true;
}

JSObjectRef _jscHooker::GetJSFunctionByName( AStringPtr name ) const
{
	const JSObjectRef* js_object = mJSFuncMap.Search( GetStringTable( )->GetRefString( name ) );
	if ( js_object == _null )
		return _null;

	return *js_object;
}

#endif