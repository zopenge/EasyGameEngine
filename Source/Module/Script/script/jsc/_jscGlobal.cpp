//! @file     _jscGlobal.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscGlobal Implementation
//----------------------------------------------------------------------------

_jscGlobal::_jscGlobal( )
{
}

_jscGlobal::~_jscGlobal( )
{
}

_qword _jscGlobal::BuildJSFuncHookKey( JSObjectRef js_object, JSObjectRef js_func ) const
{
	return (((_qword) js_object << 32) | ((_dword) js_func));
}

_ubool _jscGlobal::Initialize( )
{
	WLOG_TRACE( L"Initialize JS global ..." );

	// Initialize JS core
	if ( mJSCore.Initialize( gGlobalJSContext ) == _false )
	{
		WLOG_ERROR( L"Initialize JS core failed" );
		return _false;
	}

	WLOG_TRACE( L"Initialize JS global OK" );

	return _true;
}

_void _jscGlobal::Finalize( )
{
	mJSFunctionHooks.Clear( );

	// Delete all JS resource objects
	for ( _jscObjResMap::Iterator it = mJSObjResMap.GetHeadIterator( ); it.IsValid( ); ++ it )
		delete it.GetObject( );

	mJSObjResMap.Clear( );

	// Delete all registered properties and functions
	mRegisteredProperties.Clear( );
	mRegisteredFuncs.Clear( );

	// Finalize JS core
	mJSCore.Finalize( );
}

const _jscGlobal::RegisteredPropertyInfo* _jscGlobal::GetRegisteredPropertyInfo( const AStringObj& class_name, const AStringObj& property_name ) const
{
	const RegisteredPropertyInfoMap* property_map = mRegisteredProperties.Search( class_name );
	if ( property_map == _null )
		return _null;

	return property_map->Search( property_name );
}

_jscGlobal::RegisteredPropertyInfo* _jscGlobal::GetRegisteredPropertyInfo( const AStringObj& class_name, const AStringObj& property_name )
{
	RegisteredPropertyInfoMap* property_map = mRegisteredProperties.Search( class_name );
	if ( property_map == _null )
		return _null;

	return property_map->Search( property_name );
}

const _jscGlobal::RegisteredPropertyInfo* _jscGlobal::GetRegisteredPropertyInfo( JSObjectRef js_object, JSStringRef js_property_name ) const
{
	const _jscObjResource* js_obj_res = GetJSObjRes( js_object );
	if ( js_obj_res == _null )
		return _null;

	AStringObj property_name = _jscHelper::GetJSStringA( js_property_name );
	return GetRegisteredPropertyInfo( js_obj_res->GetName( ), property_name );
}

_jscGlobal::RegisteredPropertyInfo* _jscGlobal::CreateRegisteredPropertyInfo( const AStringObj& class_name, const ScriptPropertyDeclInfo& decl_info )
{
	// Add registered property if it's new
	RegisteredPropertyInfo* registered_property_info = mRegisteredProperties[ class_name ].Search( decl_info.mPropertyName );
	if ( registered_property_info == _null )
	{
		registered_property_info					= &mRegisteredProperties[ class_name ][ decl_info.mPropertyName ];
		registered_property_info->mJSPropertyName	= decl_info.mPropertyName;
		registered_property_info->mDeclInfo			= decl_info;
	}

	return registered_property_info;
}

_jscGlobal::RegisteredFuncInfo* _jscGlobal::GetRegisteredFuncInfo( const AStringObj& class_name, const AStringObj& func_name )
{
	RegisteredFuncInfoMap* func_map = mRegisteredFuncs.Search( class_name );
	if ( func_map == _null )
		return _null;

	return func_map->Search( func_name );
}

const _jscGlobal::RegisteredFuncInfo* _jscGlobal::GetRegisteredFuncInfo( const AStringObj& class_name, const AStringObj& func_name ) const
{
	const RegisteredFuncInfoMap* func_map = mRegisteredFuncs.Search( class_name );
	if ( func_map == _null )
		return _null;

	return func_map->Search( func_name );
}

_jscGlobal::RegisteredFuncInfo* _jscGlobal::CreateRegisteredFuncInfo( JSContextRef js_context, const AStringObj& class_name, JSObjectCallAsFunctionCallback js_callback_func, const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info )
{
	// Find the existing register function by name
	RegisteredFuncInfo* registered_func_info = GetRegisteredFuncInfo( class_name, decl_info.mName );

	// Create registered function if it's new
	if ( registered_func_info == _null )
	{
		// Create JS embedded function by name
		JSObjectRef js_func = _jscHelper::CreateJSFunction( js_context, decl_info.mName.Str( ), js_callback_func );
		if ( JS_IS_NULL( js_func ) )
			return _null;

		// Add registered functions
		registered_func_info					= &mRegisteredFuncs[ class_name ][ decl_info.mName ];
		registered_func_info->mJSFuncName		= decl_info.mName;
		registered_func_info->mJSFunc			= js_func;
		registered_func_info->mDeclInfo			= decl_info;
		registered_func_info->mNativeFuncInfo	= native_func_info;
	}

	return registered_func_info;
}

_ubool _jscGlobal::RegisterJSFunction( JSContextRef js_context, AStringPtr class_name, JSObjectRef js_object, AStringPtr func_name, JSObjectCallAsFunctionCallback js_callback_func, const _void* data )
{
	// Convert to the JS string of function name
	JSStringRefOwner js_func_name( func_name );

	// Create JS embedded function by name
	JSObjectRef js_func = _jscHelper::CreateJSFunction( js_context, js_func_name, js_callback_func );
	if ( JS_IS_NULL( js_func ) )
		return _false;

	// Expose a native function to the JS context
	if ( _jscHelper::SetJSObjectProperty( js_context, js_object, js_func_name, JS_OBJECT_TO_VALUE( js_func ), 0 ) == _false )
		return _false;

	// Bind hook function if we have register it
	const RegisteredFuncInfo* registered_func_info = GetRegisteredFuncInfo( class_name, func_name );
	if ( registered_func_info != _null )
		mJSFunctionHooks[ BuildJSFuncHookKey( js_object, js_func ) ] = registered_func_info;

	return _true;
}

_ubool _jscGlobal::RegisterJSFunction( JSContextRef js_context, AStringPtr class_name, JSObjectRef js_object, AStringPtr func_name, JSObjectRef js_func, const _void* data )
{
	// Convert to the JS string of function name
	JSStringRefOwner js_func_name( func_name );

	// Expose a native function to the JS context
	if ( _jscHelper::SetJSObjectProperty( js_context, js_object, js_func_name, JS_OBJECT_TO_VALUE( js_func ), 0 ) == _false )
		return _false;

	// Bind hook function if we have register it
	const RegisteredFuncInfo* registered_func_info = GetRegisteredFuncInfo( class_name, func_name );
	if ( registered_func_info != _null )
		mJSFunctionHooks[ BuildJSFuncHookKey( js_object, js_func ) ] = registered_func_info;

	return _true;
}

const _jscGlobal::RegisteredFuncInfo* _jscGlobal::GetRegisteredJSFunction( JSObjectRef js_object, JSObjectRef js_func ) const
{
	const RegisteredFuncInfo* const* registered_func_info = mJSFunctionHooks.Search( BuildJSFuncHookKey( js_object, js_func ) );
	if ( registered_func_info == _null )
		return _null;

	return *registered_func_info;
}

_ubool _jscGlobal::RegisterJSProperties( JSContextRef js_context, const AStringObj& class_name, JSObjectRef js_object )
{
	for ( RegisteredPropertyInfoMap::Iterator it = mRegisteredProperties[ class_name ].GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const RegisteredPropertyInfo& property_info = it.GetObject( );

		if ( _jscHelper::RegisterJSProperty( js_context, js_object, property_info.mDeclInfo ) == _false )
			return _false;
	}

	return _true;
}

_ubool _jscGlobal::RegisterJSFunctions( JSContextRef js_context, const AStringObj& class_name, JSObjectRef js_object )
{
	for ( RegisteredFuncInfoMap::Iterator it = mRegisteredFuncs[ class_name ].GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const RegisteredFuncInfo& func_info = it.GetObject( );

		if ( _jscGlobal::GetInstance( ).RegisterJSFunction( js_context, class_name.Str( ), js_object, func_info.mJSFuncName.Str( ), func_info.mJSFunc, (_void*) &func_info ) == _false )
			return _false;
	}

	return _true;
}

_jscGlobal::JSCModlueInfo* _jscGlobal::AddJSCModule( const AStringObj& name, _jscModule* jsc_module )
{
	if ( jsc_module == _null )
		return _null;

	JSCModlueInfo& jsc_module_info	= mJSCModlues[ name ];
	jsc_module_info.mJSCModule		= jsc_module;

	return &jsc_module_info;
}

_void _jscGlobal::RemoveJSCModule( const AStringObj& name )
{
	mJSCModlues.Remove( name );
}

_jscGlobal::JSCModlueInfo* _jscGlobal::GetJSCModule( const AStringObj& name )
{
	return mJSCModlues.Search( name );
}

const _jscGlobal::JSCModlueInfo* _jscGlobal::GetJSCModule( const AStringObj& name ) const
{
	return mJSCModlues.Search( name );
}

_void _jscGlobal::AddJSObjRes( JSObjectRef js_object, _jscObjResource* jsc_obj_res )
{
	EGE_ASSERT( JS_IS_VALID( js_object ) );
	EGE_ASSERT( jsc_obj_res != _null );

	mJSObjResMap[ js_object ] = jsc_obj_res;
}

_jscObjResource* _jscGlobal::GetJSObjRes( JSObjectRef js_object )
{
	EGE_ASSERT( JS_IS_VALID( js_object ) );

	_jscObjResource** jsc_obj_res = mJSObjResMap.Search( js_object );
	if ( jsc_obj_res == _null )
		return _null;

	return *jsc_obj_res;
}

const _jscObjResource* _jscGlobal::GetJSObjRes( JSObjectRef js_object ) const
{
	EGE_ASSERT( JS_IS_VALID( js_object ) );

	const _jscObjResource* const* jsc_obj_res = mJSObjResMap.Search( js_object );
	if ( jsc_obj_res == _null )
		return _null;

	return *jsc_obj_res;
}

_void _jscGlobal::RemoveJSObjRes( JSObjectRef js_object )
{
	if ( JS_IS_NULL( js_object ) )
		return;

	_jscObjResMap::Iterator it = mJSObjResMap.GetIterator( js_object );
	if ( it.IsValid( ) == _false )
		return;

	// Get the JSC resource object
	_jscObjResource* jsc_obj_res = it.GetObject( );
	EGE_ASSERT( jsc_obj_res != _null );

	// Free resource object
	delete jsc_obj_res;

	// Remove it from map
	mJSObjResMap.Remove( it );
}

#endif