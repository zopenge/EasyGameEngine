//! @file     _jscModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscModule Implementation
//----------------------------------------------------------------------------

_jscModule::_jscModule( JSGlobalContextRef js_context )
{
	mJSClass							= _null;
	mJSClassWithoutCreateWrappedResObj	= _null;
	mJSObject							= _null;
	mJSContext							= js_context;
}

_jscModule::~_jscModule( )
{
	// Finalize self
	OnFinalize( );

	// Remove JSC module from global
	_jscGlobal::GetInstance( ).RemoveJSCModule( mName );
}

_ubool _jscModule::Initialize( AStringPtr name, AStringPtr desc )
{
	if ( name.IsEmpty( ) )
		return _false;

	// Copy the basic info
	mName = name;
	mDesc = desc;

	// Initialize self
	if ( OnInitialize( ) == _false )
		return _false;

	// Create the JS object
	mJSObject = CreateJSObject( mJSContext, _null, _true );
	if ( mJSObject == _null )
	{
		WLOG_ERROR_1( L"Create '%s' JS object failed", mName.Str( ) );
		return _false;
	}

	// Set the JS object to global
	if ( _jscHelper::SetJSObjectProperty( mJSContext, gGlobalJSObject, mName.Str( ), JS_OBJECT_TO_VALUE( mJSObject ), 0 ) == _false )
		return _false;

	// Set the JSC module
	if ( _jscHelper::SetJSCModule( mJSObject, this ) == _false )
		return _false;

	// Add JSC module to global
	_jscGlobal::GetInstance( ).AddJSCModule( mName, this );

	return _true;
}

JSGlobalContextRef _jscModule::GetJSGlobalContext( )
{
	return mJSContext;
}

JSObjectRef _jscModule::GetJSGlobalObject( )
{
	return gGlobalJSObject;
}

JSObjectRef _jscModule::CreateJSObject( JSContextRef js_context, _byte* wrapped_class, _ubool skip_create_wrapped_res_obj )
{
	// Create JS object
	JSObjectRef js_object = _jscHelper::MakeJSObject( js_context, skip_create_wrapped_res_obj ? mJSClassWithoutCreateWrappedResObj : mJSClass, this );
	if ( js_object == _null )
	{
		WLOG_ERROR_1( L"Create '%s' JS object failed", mName.Str( ) );
		return _null;
	}

	// When create JS object
	if ( OnCreateJSObject( js_object ) == _false )
		return _null;

	// Register JS properties
	if ( _jscGlobal::GetInstance( ).RegisterJSProperties( mJSContext, mName, js_object ) == _false )
		return _null;

	// Register JS functions
	if ( _jscGlobal::GetInstance( ).RegisterJSFunctions( mJSContext, mName, js_object ) == _false )
		return _null;

	// Get the JS object resource ( we must bind wrapped class here to prevent the set property callback function to change C++ structure info )
	_jscObjResource* jsc_obj_res = _jscGlobal::GetInstance( ).GetJSObjRes( js_object );
	EGE_ASSERT( jsc_obj_res != _null );

	// Update the wrapped class
	jsc_obj_res->SetWrapClass( wrapped_class );

	return js_object;
}

AStringPtr _jscModule::GetName( ) const
{
	return mName.Str( );
}

const AStringObj& _jscModule::GetNameObj( ) const
{
	return mName;
}

_ubool _jscModule::RegisterEnumValue( AStringPtr name, _dword value )
{
	// Get the JS property name
	JSStringRefOwner js_property_name( name );

	// Get the JS value
	JSValueRef js_value = _jscHelper::MakeJSValueAsDword( mJSContext, value );

	// Set JS property with native info
	if ( _jscHelper::SetJSObjectProperty( mJSContext, mJSObject, js_property_name, js_value, 0 ) == _false )
		return _false;

	return _true;
}

_ubool _jscModule::RegisterProperty( const ScriptPropertyDeclInfo& decl_info )
{
	// Create registered property info
	_jscGlobal::RegisteredPropertyInfo* registered_property_info = _jscGlobal::GetInstance( ).CreateRegisteredPropertyInfo( mName, decl_info );
	if ( registered_property_info == _null )
		return _false;

	return _true;
}

_ubool _jscModule::RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info )
{
	// Create registered function
	_jscGlobal::RegisteredFuncInfo* registered_func_info = _jscGlobal::GetInstance( ).CreateRegisteredFuncInfo( mJSContext, mName, OnGetJSFunctionCallbackPtr( ), decl_info, native_func_info );
	if ( registered_func_info == _null )
		return _false;

	// Register JS function
	if ( _jscGlobal::GetInstance( ).RegisterJSFunction( mJSContext, GetName( ), mJSObject, registered_func_info->mJSFuncName.Str( ), registered_func_info->mJSFunc, registered_func_info ) == _false )
		return _false;

	return _true;
}

#endif