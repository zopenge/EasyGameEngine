//! @file     _pyModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pyModule
//----------------------------------------------------------------------------

class _pyModule : public TObject< _scriptModule >
{
public:
	static PyModuleDef			cPyNullModuleDef;
	static PyTypeObject			cPyNullTypeObject;

	static AStringPtr			cPySelfKey;
	static AStringPtr			cPyDocKey;
	static AStringPtr			cPyNewKey;

	//!	The python type objects manager
	static _pyTypeObjManager	sPyObjTypeManager;

private:
	//!	The python method definition array
	typedef Array< PyMethodDef* > PyMethodDefArray;

private:
	//!	The module name
	AStringObj			mName;
	//!	The module description
	AStringObj			mDesc;

	//!	The methods
	PyMethodInfoArray	mMethods;
	//!	The module's methods
	PyMethodDefArray	mPyMethodDefs;

	//!	The python module object
	PyObject*			mPyModuleObject;
	//!	The python module definition
	PyModuleDef			mPyModuleDef;
	//!	The python module type object definition
	PyTypeObject		mPyTypeObject;

private:
	//!	New python module instance.
	static PyObject* OnNewModuleInstance( PyTypeObject* type, PyObject* args, PyObject* kw );
	//! Initialize python module instance.
	static int OnInitModuleInstance( _pyObjResource* res_obj, PyObject* args, PyObject* kw );
	//!	Free python module instance.
	static _void OnDeallocModuleInstance( _pyObjResource* res_obj );

private:
	//!	Search method by python function object.
	const PyMethodInfo* SearchMethod( PyMethodDef* method_def ) const;

	//!	Build module's methods.
	PyMethodDef* InsertMethodDef( const ScriptFuncDeclInfo& decl_info );
	//!	Search module's method.
	PyMethodDef* SearchMethodDef( AStringPtr name );

public:
	_pyModule( );
	virtual ~_pyModule( );

public:
	//!	Get the methods array.
	EGE_GET_ACCESSOR( const PyMethodInfoArray&, Methods )
	//!	Get the python type object.
	EGE_GET_ADDR_ACCESSOR( PyTypeObject, PyTypeObject );

public:
	//!	Python call function.
	static PyObject* CallFunction( PyCFunctionObject* func_obj, _pyObjResource* res_obj, PyObject* args );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr name, AStringPtr desc );

// _scriptModule Interface
public:
	virtual AStringPtr			GetName( ) const override;
	virtual const AStringObj&	GetNameObj( ) const override;

	virtual _ubool				RegisterEnumValue( AStringPtr name, _dword value ) override;
	virtual _ubool				RegisterProperty( const ScriptPropertyDeclInfo& decl_info ) override;
	virtual _ubool				RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info ) override;
};

}