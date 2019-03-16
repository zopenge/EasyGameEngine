//! @file     _jscCore.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscCore
//----------------------------------------------------------------------------

class _jscCore
{
private:
	//!	The JS core class
	JSClassRef	mJSClass;

private:
	//!	Require other JS file.
#if (_SCRIPT_USE_GOOGLE_V8_ == 1)
	static _void OnRequireFuncCallback( const v8::FunctionCallbackInfo< v8::Value >& args );
#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)
	static JSValueRef OnRequireFuncCallback( JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception );
#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)
	static JSBool OnRequireFuncCallback( JSContext* js_context, unsigned argc, jsval* vp );
#endif

private:
	//!	When initialize.
	_ubool OnInitialize( AStringPtr js_core_name, JSContextRef js_context );
	//!	When finalize.
	_void OnFinalize( );

public:
	_jscCore( );
	virtual ~_jscCore( );

public:
	//!	Initialize.
	_ubool Initialize( JSContextRef js_context );
	//!	Finalize.
	_void Finalize( );
};

}