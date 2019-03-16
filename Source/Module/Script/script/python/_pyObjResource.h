//! @file     _pyObjResource.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class _pyModule;
struct PyMethodInfo;

//----------------------------------------------------------------------------
// _pyObjResource
//----------------------------------------------------------------------------

class _pyObjResource
{
public:
	//!	In order to use as python object
	PyObject_HEAD

private:
	//!	The python module
	_pyModule*	mModule;
	//!	The class name
	AStringObj	mName;

	//!	The class not inherit from IObject, use new/delete to allocate and free
	_byte*		mWrapClass;
	//!	The class inherit from IObject, use new/Release() to allocate and free
	IObjectRef	mWrapObject;

private:
	//!	Build python return value.
	PyObject* BuildRetValue( const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers );

public:
	_pyObjResource( );
	~_pyObjResource( );

public:
	//!	Get the python module.
	EGE_GET_ACCESSOR( _pyModule*, Module )
	//!	Get the wrap class.
	EGE_GET_ACCESSOR( _byte*, WrapClass )
	//!	Get the wrap object.
	EGE_GET_ACCESSOR( IObject*, WrapObject )

public:
	//!	Create resource instance.
	static _pyObjResource* CreateInstance( PyTypeObject* type, PyObject* args, PyObject* kw );

	//!	Get the wrap object.
	_void* GetWrappedObject( );

	//! Initialize resource instance.
	_ubool InitInstance( PyObject* args, PyObject* kw );
	//!	Free resource instance.
	_void FreeInstance( );

	//!	Create class resource.
	_ubool CreateClassResource( );

	//!	Invoke python method.
	PyObject* InvokeMethod( const PyMethodInfo* method_info, PyObject* args );
};

//----------------------------------------------------------------------------
// _pyObjResource Implementation
//----------------------------------------------------------------------------

inline _void* _pyObjResource::GetWrappedObject( )
{
	return mWrapClass ? mWrapClass : (_byte*) mWrapObject.GetPtr( );
}

}