//! @file     _jscHooker.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class _jscModule;

//----------------------------------------------------------------------------
// _jscHooker
//----------------------------------------------------------------------------

class _jscHooker
{
private:
	//!	The JS function map with name.
	typedef Map< JSObjectRef, AStringObj > JSFuncMap;

private:
	//!	The module
	_jscModule* mJSCmodule;

	//!	The JS functions map
	JSFuncMap	mJSFuncMap;

private:
#if (_SCRIPT_USE_GOOGLE_V8_ == 1)
	//!	When register/hook JS function.
	static _void OnHookJSFunctionCallback( const v8::FunctionCallbackInfo< v8::Value >& args );
#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)
	//!	When register/hook JS function.
	static JSValueRef OnHookJSFunctionCallback( JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception );
#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)
	static _void OnHookJSFunctionCallback( JSContext* js_context, unsigned argc, jsval* vp );
#endif

public:
	_jscHooker( _jscModule* jsc_module );
	~_jscHooker( );

public:
	//!	Initialize.
	_ubool Initialize( JSContextRef js_context, JSObjectRef js_object );

	//!	Get the JS function by name.
	JSObjectRef GetJSFunctionByName( AStringPtr name ) const;
};

}