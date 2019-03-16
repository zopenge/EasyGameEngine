//! @file     _jscGlobal.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscGlobal
//----------------------------------------------------------------------------

class _jscGlobal
{
	SINGLETON( _jscGlobal )

public:
	//!	The registered property info
	struct RegisteredPropertyInfo
	{
		JSStringRefOwner		mJSPropertyName;

		ScriptPropertyDeclInfo	mDeclInfo;

		RegisteredPropertyInfo( )
		{
		}
	};
	//!	Use the property name as key.
	typedef Map< RegisteredPropertyInfo, AStringObj > RegisteredPropertyInfoMap;
	//!	Use the class name as key.
	typedef Map< RegisteredPropertyInfoMap, AStringObj > RegisteredPropertyInClassInfoMap;

	//!	The registered function info
	struct RegisteredFuncInfo
	{
		AStringObj				mJSFuncName;
		JSObjectRef				mJSFunc;

		ScriptFuncDeclInfo		mDeclInfo;
		ScriptNativeFuncInfo	mNativeFuncInfo;

		RegisteredFuncInfo( )
		{
			JS_INIT( mJSFunc );
		}
	};
	//!	Use the function name as key.
	typedef Map< RegisteredFuncInfo, AStringObj > RegisteredFuncInfoMap;
	//!	Use the class name as key.
	typedef Map< RegisteredFuncInfoMap, AStringObj > RegisteredFuncInClassInfoMap;

	//!	The JSC module info
	struct JSCModlueInfo
	{
		_jscModule*	mJSCModule;

		JSCModlueInfo( )
		{
			mJSCModule = _null;
		}
	};
	//!	Use the module name as key.
	typedef Map< JSCModlueInfo, AStringObj > JSCModlueInfoMap;

	//!	The map of JS object resources, use pointer as key.
	typedef Map< _jscObjResource*, _void* > _jscObjResMap;

	//!	The map of JS function data ( use JS's object and function address as key ).
	typedef Map< const RegisteredFuncInfo*, _qword > JSFunctionHookMap;

private:
	//!	The JS core
	_jscCore							mJSCore;

	//!	The registered properties
	RegisteredPropertyInClassInfoMap	mRegisteredProperties;
	//!	The registered functions
	RegisteredFuncInClassInfoMap		mRegisteredFuncs;

	//!	The module info map
	JSCModlueInfoMap					mJSCModlues;

	//!	The JS object resources map
	_jscObjResMap						mJSObjResMap;

	//!	The hook registered function info
	JSFunctionHookMap					mJSFunctionHooks;

private:
	//!	Build JS function hook key.
	_qword BuildJSFuncHookKey( JSObjectRef js_object, JSObjectRef js_func ) const;

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

	//!	Get the registered property info by name.
	RegisteredPropertyInfo* GetRegisteredPropertyInfo( const AStringObj& class_name, const AStringObj& property_name );
	const RegisteredPropertyInfo* GetRegisteredPropertyInfo( const AStringObj& class_name, const AStringObj& property_name ) const;
	//!	Get the registered property info by JS object and property name.
	const RegisteredPropertyInfo* GetRegisteredPropertyInfo( JSObjectRef js_object, JSStringRef js_property_name ) const;
	//!	Create the registered property info.
	RegisteredPropertyInfo* CreateRegisteredPropertyInfo( const AStringObj& class_name, const ScriptPropertyDeclInfo& decl_info );

	//!	Get the registered function info by name.
	RegisteredFuncInfo* GetRegisteredFuncInfo( const AStringObj& class_name, const AStringObj& func_name );
	const RegisteredFuncInfo* GetRegisteredFuncInfo( const AStringObj& class_name, const AStringObj& func_name ) const;
	//!	Create the registered function info.
	RegisteredFuncInfo* CreateRegisteredFuncInfo( JSContextRef js_context, const AStringObj& class_name, JSObjectCallAsFunctionCallback js_callback_func, const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info );

	//!	Register JS function.
	_ubool RegisterJSFunction( JSContextRef js_context, AStringPtr class_name, JSObjectRef js_object, AStringPtr func_name, JSObjectCallAsFunctionCallback js_callback_func, const _void* data );
	_ubool RegisterJSFunction( JSContextRef js_context, AStringPtr class_name, JSObjectRef js_object, AStringPtr func_name, JSObjectRef js_func, const _void* data );
	//!	Get the JS function.
	const RegisteredFuncInfo* GetRegisteredJSFunction( JSObjectRef js_object, JSObjectRef js_func ) const;

	//!	Register JS properties.
	_ubool RegisterJSProperties( JSContextRef js_context, const AStringObj& class_name, JSObjectRef js_object );
	//!	Register JS functions.
	_ubool RegisterJSFunctions( JSContextRef js_context, const AStringObj& class_name, JSObjectRef js_object );

	//!	Add JSC module.
	JSCModlueInfo* AddJSCModule( const AStringObj& name, _jscModule* jsc_module );
	//!	Remove JSC module.
	_void RemoveJSCModule( const AStringObj& name );
	//!	Get JSC module.
	JSCModlueInfo* GetJSCModule( const AStringObj& name );
	const JSCModlueInfo* GetJSCModule( const AStringObj& name ) const;

	//!	Add JS object resource.
	_void AddJSObjRes( JSObjectRef js_object, _jscObjResource* jsc_obj_res );
	//!	Get JS object resource.
	_jscObjResource* GetJSObjRes( JSObjectRef js_object );
	const _jscObjResource* GetJSObjRes( JSObjectRef js_object ) const;
	//!	Remove JS object resource.
	_void RemoveJSObjRes( JSObjectRef js_object );
};

}