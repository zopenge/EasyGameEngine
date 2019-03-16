//! @file     _jscModule.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscModule Helpful Functions Implementation
//----------------------------------------------------------------------------

static void InitJSInstance( JSContextRef ctx, JSObjectRef object, _ubool call_constructor )
{
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( object );
	EGE_ASSERT( jsc_module != _null );

	// Create the JS object resource
	_jscObjResource* jsc_obj_res = _jscObjResource::CreateInstance( jsc_module->GetNameObj( ) );
	EGE_ASSERT( jsc_obj_res != _null );

	// Initialize JS object resource
	jsc_obj_res->InitInstance( object, call_constructor );
}

static void OnJSObjectWithoutCreateWrappedResObjInitializeCallback( JSContextRef ctx, JSObjectRef object )
{
	InitJSInstance( ctx, object, _false );
}

static void OnJSObjectInitializeCallback( JSContextRef ctx, JSObjectRef object )
{
	InitJSInstance( ctx, object, _true );
}

static void OnJSObjectFinalizeCallback( JSObjectRef object )
{
	// Remove JS resource object
	_jscGlobal::GetInstance( ).RemoveJSObjRes( object );
}

static bool OnJSObjectHasPropertyCallback( JSContextRef ctx, JSObjectRef object, JSStringRef propertyName )
{
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( object );
	EGE_ASSERT( jsc_module != _null );

	// Check whether it's registered property
	const _jscGlobal::RegisteredPropertyInfo* registered_property = _jscGlobal::GetInstance( ).GetRegisteredPropertyInfo( object, propertyName );
	if ( registered_property != _null )
	{
		// It's registered property, let us to handle it
		return _true;
	}

	// Let the JS to handle it
	return _false;
}

static JSValueRef OnJSObjectGetPropertyCallback( JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception )
{
	// Check whether it's registered property
	const _jscGlobal::RegisteredPropertyInfo* registered_property = _jscGlobal::GetInstance( ).GetRegisteredPropertyInfo( object, propertyName );
	if ( registered_property != _null )
	{
		// Get the JS object resource
		_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( object );
		EGE_ASSERT( jsc_obj_res != _null );

		// It's registered property, now build the JS value from native property
		return _jscHelper::PackJSProperty( ctx, jsc_obj_res, registered_property->mDeclInfo, _jscHelper::GetJSCModule( object ) );
	}

	// Let the JS to handle it
	return ::JSValueMakeNull( ctx );
}

static bool OnJSObjectSetPropertyCallback( JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception )
{
	// Check whether it's registered property
	const _jscGlobal::RegisteredPropertyInfo* registered_property = _jscGlobal::GetInstance( ).GetRegisteredPropertyInfo( object, propertyName );
	if ( registered_property != _null )
	{
		// Get the JS object resource
		_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( object );
		EGE_ASSERT( jsc_obj_res != _null );

		// It's registered property, update native property
		return EGE_BOOLEAN( _jscHelper::UnpackJSProperty( ctx, jsc_obj_res, registered_property->mDeclInfo, value ) );
	}

	// Let the JS to handle it
	return _false;
}

static bool OnJSObjectDeletePropertyCallback( JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception )
{
	// Let the JS to handle it
	return _false;
}

static void OnJSObjectGetPropertyNamesCallback( JSContextRef ctx, JSObjectRef object, JSPropertyNameAccumulatorRef propertyNames )
{

}

static JSValueRef OnJSObjectCallAsFunctionCallback( JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception )
{
	return JS_MAKE_UNDEFINED( ctx );
}

static JSObjectRef OnJSObjectCallAsConstructorCallback( JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception )
{
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( constructor );
	EGE_ASSERT( jsc_module != _null );

	// We can not use any arguments
	if ( argumentCount > 0 )
		{ _jscHelper::ThrowException( ctx, "throw 'an exception'", constructor, exception ); return constructor; }

	// Create JS object
	JSObjectRef js_object = jsc_module->CreateJSObject( ctx, _null, _false );
	if ( js_object == _null )
		{ _jscHelper::ThrowException( ctx, "throw 'an exception'", constructor, exception ); return constructor; }

	return js_object;
}

static bool OnJSObjectHasInstanceCallback( JSContextRef ctx, JSObjectRef constructor, JSValueRef possibleInstance, JSValueRef* exception )
{
	return ::JSValueIsInstanceOfConstructor( ctx, possibleInstance, constructor, exception );
}

static JSValueRef OnJSObjectConvertToTypeCallback( JSContextRef ctx, JSObjectRef object, JSType type, JSValueRef* exception )
{
	switch ( type ) 
	{
	    case kJSTypeNumber:
	        break;

		case kJSTypeString:
			break;

		default:
			break;
    }

    // Convert failed
    return JSValueMakeNull( ctx );
}

static JSValueRef OnCallJSFunctionCallback( JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception )
{
	_jscModule* jsc_module = (_jscModule*) _jscHelper::GetJSObjectPrivate( thisObject );
	EGE_ASSERT( jsc_module != _null );

	// Get the JS object resource
	_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( thisObject );
	EGE_ASSERT( jsc_obj_res != _null );

	// Get the allocator
	IStackAllocator* stack_allocator = static_cast< _jscSystem* >( gInternalScriptSystem )->GetAllocator( );
	EGE_ASSERT( stack_allocator != _null );

	// Invoke method
	_dword offset_of_allocator = stack_allocator->GetOffset( );
	JSValueRef js_ret_value = jsc_obj_res->InvokeMethod( stack_allocator, ctx, function, thisObject, argumentCount, arguments, exception );
	stack_allocator->SetOffset( offset_of_allocator );

	return js_ret_value;
}

//----------------------------------------------------------------------------
// _jscModule Implementation
//----------------------------------------------------------------------------

_ubool _jscModule::OnInitialize( )
{
	// Initialize the JS class definition
	JSClassDefinition js_class_definition = 
	{
		0,
		kJSClassAttributeNone,

		mName.Str( ),
		_null,

		_null,
		_null,

		OnJSObjectInitializeCallback,
		OnJSObjectFinalizeCallback,
		OnJSObjectHasPropertyCallback,
		OnJSObjectGetPropertyCallback,
		OnJSObjectSetPropertyCallback,
		OnJSObjectDeletePropertyCallback,
		OnJSObjectGetPropertyNamesCallback,
		OnJSObjectCallAsFunctionCallback,
		OnJSObjectCallAsConstructorCallback,
		OnJSObjectHasInstanceCallback,
		OnJSObjectConvertToTypeCallback,
	};

	// Create the JS class
	mJSClass = ::JSClassCreate( &js_class_definition );
	if ( mJSClass == _null )
	{
		WLOG_ERROR_1( L"Create '%s' JS class failed", mName.Str( ) );
		return _false;
	}

	// Create the JS class without create wrapped resource object
	js_class_definition.initialize = OnJSObjectWithoutCreateWrappedResObjInitializeCallback;
	mJSClassWithoutCreateWrappedResObj = ::JSClassCreate( &js_class_definition );
	if ( mJSClassWithoutCreateWrappedResObj == _null )
	{
		WLOG_ERROR_1( L"Create '%s' JS class without create wrapped resource object failed", mName.Str( ) );
		return _false;
	}

	return _true;
}

_void _jscModule::OnFinalize( )
{
	// Release JS class
	if ( mJSClass != _null )
	{
		::JSClassRelease( mJSClass );
		mJSClass = _null;
	}

	// Release JS class
	if ( mJSClassWithoutCreateWrappedResObj != _null )
	{
		::JSClassRelease( mJSClassWithoutCreateWrappedResObj );
		mJSClassWithoutCreateWrappedResObj = _null;
	}
}

_ubool _jscModule::OnCreateJSObject( JSObjectRef js_object )
{
	return _true;
}

JSObjectCallAsFunctionCallback _jscModule::OnGetJSFunctionCallbackPtr( ) const
{
	return OnCallJSFunctionCallback;
}

#endif