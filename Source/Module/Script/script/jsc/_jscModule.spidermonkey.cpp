//! @file     _jscModule.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscModule Helpful Functions Implementation
//----------------------------------------------------------------------------

#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
static JSBool OnGetJSPropertyCallback( JSContext* cx, JSObject* obj, jsid id, jsval* vp )
#else
static JSBool OnGetJSPropertyCallback( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JS::MutableHandle<JS::Value> vp )
#endif
{
	// Get the property name
	JSStringRef js_property_name = JSID_TO_STRING( id );

	// Check whether it's registered property
	const _jscGlobal::RegisteredPropertyInfo* registered_property = _jscGlobal::GetInstance( ).GetRegisteredPropertyInfo( obj, js_property_name );
	if ( registered_property != _null )
	{
		// Get the JS object resource
		_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( obj );
		EGE_ASSERT( jsc_obj_res != _null );

		// It's registered property, now build the JS value from native property
		JSValueRef js_value = _jscHelper::PackJSProperty( cx, jsc_obj_res, registered_property->mDeclInfo, _jscHelper::GetJSCModule( obj ) );

		// Set the return value
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
		JS_SET_RVAL( cx, vp, js_value );
#else
		JS_SET_RVAL( cx, vp.address( ), js_value );
#endif
	}

	// Let the JS to handle it
	return JS_TRUE;
}

#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
static JSBool OnSetJSPropertyCallback( JSContext* cx, JSObject* obj, jsid id, JSBool strict, jsval* vp )
#else
static JSBool OnSetJSPropertyCallback( JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool strict, JS::MutableHandle<JS::Value> vp )
#endif
{
	// Get the property name
	JSStringRef js_property_name = JSID_TO_STRING( id );
	// Get the property value
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	JSValueRef js_value = JS_RVAL( cx, vp );
#else
	JSValueRef js_value = JS_RVAL( cx, &vp );
#endif

	// Check whether it's registered property
	const _jscGlobal::RegisteredPropertyInfo* registered_property = _jscGlobal::GetInstance( ).GetRegisteredPropertyInfo( obj, js_property_name );
	if ( registered_property != _null )
	{
		// Get the JS object resource
		_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( obj );
		EGE_ASSERT( jsc_obj_res != _null );

		// It's registered property, update native property
		if ( _jscHelper::UnpackJSProperty( cx, jsc_obj_res, registered_property->mDeclInfo, js_value ) == _false )
			return JS_FALSE;
	}

	// Let the JS to handle it
	return JS_TRUE;
}

static JSBool OnCallJSFunctionCallback( JSContext* js_context, unsigned argc, jsval* vp )
{
	// Get the JS object callee
	JSObjectRef js_object_callee = JS_VALUE_TO_OBJECT( JS_CALLEE( js_context, vp ) );
	EGE_ASSERT( js_object_callee != _null );

	// Get the JS object
	JSObjectRef js_object = JS_THIS_OBJECT( js_context, vp );
	EGE_ASSERT( js_object != _null );

	// Get the JS module
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( js_object );
	EGE_ASSERT( jsc_module != _null );

	// Get the JS object resource
	_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( js_object );
	EGE_ASSERT( jsc_obj_res != _null );

	// Get the allocator
	IStackAllocator* stack_allocator = static_cast< _jscSystem* >( gInternalScriptSystem )->GetAllocator( );
	EGE_ASSERT( stack_allocator != _null );

	// Invoke method
	_dword offset_of_allocator = stack_allocator->GetOffset( );
	JSValueRef js_ret_value = jsc_obj_res->InvokeMethod( stack_allocator, js_context, js_object_callee, js_object, argc, JS_ARGV( js_context, vp ), _null );
	stack_allocator->SetOffset( offset_of_allocator );

	// Set the return value
	JS_SET_RVAL( js_context, vp, js_ret_value );

	return JS_TRUE;
}

//----------------------------------------------------------------------------
// _jscModule Constructor Functions Implementation
//----------------------------------------------------------------------------

static JSBool InitJSInstance( JSContext* js_context, uint32_t argc, jsval* vp, _ubool call_constructor )
{
	// Get the JS object callee
	JSObjectRef js_object_callee = JS_VALUE_TO_OBJECT( JS_CALLEE( js_context, vp ) );
	EGE_ASSERT( js_object_callee != _null );

	// Get the JS object
	JSObjectRef js_object = JS_THIS_OBJECT( js_context, vp );
	EGE_ASSERT( js_object != _null );

	// Get the name of type
//	WStringObj name_obj = GetStringTable( )->GetRefString( typeid( Type ).name( ) );

	// Create the JS object resource
	//_jscObjResource* jsc_obj_res = _jscObjResource::CreateInstance( name_obj );
	//EGE_ASSERT( jsc_obj_res != _null );

	// Create JS object
	//JSObjectRef js_object = ::JS_NewObject( js_context, p->jsclass, p->proto, p->parentProto);

	//// Initialize JS object resource
	//jsc_obj_res->InitInstance( object, _false );

	//Type* cobj = new Type( );
	//js_type_class_t *p;
	//uint32_t typeId = t.s_id();
	//HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	//assert(p);
	//JSObject *_tmp = JS_NewObject(js_context, p->jsclass, p->proto, p->parentProto);
	//js_proxy_t *pp;
	//JS_NEW_PROXY(pp, cobj, _tmp);
	//JS_AddObjectRoot(js_context, &pp->obj);
	//JS_SET_RVAL(js_context, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool OnJSObjectWithoutCreateWrappedResObjInitializeCallback( JSContext* js_context, uint32_t argc, jsval* vp )
{
	return InitJSInstance( js_context, argc, vp, _false );
}

static JSBool OnJSObjectInitializeCallback( JSContext* js_context, uint32_t argc, jsval* vp )
{
	return InitJSInstance( js_context, argc, vp, _true );
}

//----------------------------------------------------------------------------
// _jscModule Implementation
//----------------------------------------------------------------------------

_ubool _jscModule::OnInitialize( )
{
	// Create JS classes
	JSClassRef* js_classes[] = { &mJSClass, &mJSClassWithoutCreateWrappedResObj };
	for ( _dword i = 0; i < EGE_ARRAY_NUMBER( js_classes ); i ++ )
	{
		JSClassRef& js_class = *js_classes[i];

		// Create JS class
		js_class = new JSClass;
		EGE_MEM_SET( js_class, 0, sizeof( JSClass ) );

		// Initialize JS class
		js_class->name			= mName.Str( );
		js_class->flags			= JSCLASS_HAS_PRIVATE | JSCLASS_HAS_RESERVED_SLOTS(2);
		js_class->addProperty	= JS_PropertyStub;
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
		js_class->delProperty	= JS_PropertyStub;
#else
		js_class->delProperty	= JS_DeletePropertyStub;
#endif
		js_class->getProperty	= OnGetJSPropertyCallback;
		js_class->setProperty	= OnSetJSPropertyCallback;
		js_class->enumerate		= JS_EnumerateStub;
		js_class->resolve		= JS_ResolveStub;
		js_class->convert		= JS_ConvertStub;
		js_class->finalize		= _null;
	}

	// Initialize constructors
	mJSClass->construct								= OnJSObjectInitializeCallback;
	mJSClassWithoutCreateWrappedResObj->construct	= OnJSObjectWithoutCreateWrappedResObjInitializeCallback;

	return _true;
}

_void _jscModule::OnFinalize( )
{
	EGE_DELETE( mJSClass );
	EGE_DELETE( mJSClassWithoutCreateWrappedResObj );
}

_ubool _jscModule::OnCreateJSObject( JSObjectRef js_object )
{
	// Create the JS object resource
	_jscObjResource* jsc_obj_res = _jscObjResource::CreateInstance( mName );
	EGE_ASSERT( jsc_obj_res != _null );

	// Initialize JS object resource
	if ( jsc_obj_res->InitInstance( js_object, _false ) == _false )
		return _false;

	return _true;
}

JSObjectCallAsFunctionCallback _jscModule::OnGetJSFunctionCallbackPtr( ) const
{
	return OnCallJSFunctionCallback;
}

#endif