//! @file     _jscObjResource.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscObjResource
//----------------------------------------------------------------------------

class _jscObjResource
{
private:
	//!	The name
	AStringObj	mName;
	//!	The JS object
	JSObjectRef	mJSObject;

	//!	The class not inherit from IObject, use new/delete to allocate and free
	_byte*		mWrapClass;
	//!	The class inherit from IObject, use new/Release() to allocate and free
	IObjectRef	mWrapObject;

private:
	//!	Build JS return value.
	JSValueRef BuildRetValue( JSContextRef js_context, const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers );

public:
	_jscObjResource( const AStringObj& name );
	~_jscObjResource( );

public:
	//!	Get the name.
	EGE_GET_ACCESSOR_CONST( const AStringObj&, Name )
	//!	Get the JS object.
	EGE_GET_ACCESSOR_CONST( JSObjectRef, JSObject )
	//!	Get the wrap class.
	EGE_GET_SET_ACCESSOR( _byte*, WrapClass )
	//!	Get the wrap object.
	EGE_GET_SET_ACCESSOR( IObject*, WrapObject )

public:
	//!	Create resource instance.
	static _jscObjResource* CreateInstance( const AStringObj& name );

public:
	//!	Get the wrap object.
	_void* GetWrappedObject( ) const;

	//! Initialize resource instance.
	_ubool InitInstance( JSObjectRef js_object, _ubool call_constructor );
	//!	Free resource instance.
	_void FreeInstance( _ubool all );

	//!	Invoke python method.
	JSValueRef InvokeMethod( IStackAllocator* allocator, JSContextRef js_context, JSObjectRef js_func, JSObjectRef js_object, _dword args_number, const JSValueRef js_args[], JSValueRef* js_exception );
};

//----------------------------------------------------------------------------
// _jscObjResource Implementation
//----------------------------------------------------------------------------

inline _void* _jscObjResource::GetWrappedObject( ) const
{
	return mWrapClass ? mWrapClass : (_byte*) mWrapObject.GetPtr( );
}

}