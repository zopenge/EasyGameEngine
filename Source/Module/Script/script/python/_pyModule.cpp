//! @file     _pyModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

PyModuleDef			_pyModule::cPyNullModuleDef		= { PyModuleDef_HEAD_INIT, "", _null, 0, _null, _null, _null, _null, _null };
PyTypeObject		_pyModule::cPyNullTypeObject	= { PyObject_HEAD_INIT(NULL) };

AStringPtr			_pyModule::cPySelfKey			= "__self__";
AStringPtr			_pyModule::cPyDocKey			= "__doc__";
AStringPtr			_pyModule::cPyNewKey			= "New";

_pyTypeObjManager	_pyModule::sPyObjTypeManager;

//----------------------------------------------------------------------------
// _pyModule Implementation
//----------------------------------------------------------------------------

_pyModule::_pyModule( )
{
	mPyModuleObject	= _null;
	mPyModuleDef	= cPyNullModuleDef;
	mPyTypeObject	= cPyNullTypeObject;
}

_pyModule::~_pyModule( )
{
	// Remove it from resource manager
	sPyObjTypeManager.RemoveObjType( mName );

	// Delete python module object
	Py_XDECREF( mPyModuleObject );

	// Delete python methods def
	for ( _dword i = 0; i < mPyMethodDefs.Number( ); i ++ )
		EGE_DELETE( mPyMethodDefs[i] );
}

PyObject* _pyModule::OnNewModuleInstance( PyTypeObject* type, PyObject* args, PyObject* kw )
{
	return (PyObject*) _pyObjResource::CreateInstance( type, args, kw );
}

int _pyModule::OnInitModuleInstance( _pyObjResource* res_obj, PyObject* args, PyObject* kw )
{
	if ( res_obj->InitInstance( args, kw ) == _false )
		return -1;

	return 0;
}

_void _pyModule::OnDeallocModuleInstance( _pyObjResource* res_obj )
{
	res_obj->FreeInstance( );
}

const PyMethodInfo* _pyModule::SearchMethod( PyMethodDef* method_def ) const
{
	PyMethodInfoArray::Iterator it = mMethods.SearchAscending( method_def );
	if ( it.IsValid( ) == _false )
		return _null;

	return &(const PyMethodInfo&) it;
}

PyMethodDef* _pyModule::InsertMethodDef( const ScriptFuncDeclInfo& decl_info )
{
	PyMethodDef* py_method	= new PyMethodDef;
	py_method->ml_name		= decl_info.mName.Str( );
	py_method->ml_meth		= (PyCFunction) CallFunction;
	py_method->ml_flags		= ( decl_info.mParametersDecls.Number( ) > 0 ? METH_VARARGS : METH_NOARGS ) | METH_WITH_FUNC_PTR;
	py_method->ml_doc		= decl_info.mDesc.Str( );

	mPyMethodDefs.Append( py_method );

	return py_method;
}

PyMethodDef* _pyModule::SearchMethodDef( AStringPtr name )
{
	for ( _dword i = 0; i < mPyMethodDefs.Number( ); i ++ )
	{
		PyMethodDef* py_method = mPyMethodDefs[i];

		if ( py_method->ml_name == _null )
			break;

		if ( name != py_method->ml_name )
			continue;

		return py_method;
	}

	return _null;
}

PyObject* _pyModule::CallFunction( PyCFunctionObject* func_obj, _pyObjResource* res_obj, PyObject* args )
{
	// Get the module
	_pyModule* module = res_obj->GetModule( );
	EGE_ASSERT( module != _null );

	// Get method info
	const PyMethodInfo* method_info = module->SearchMethod( func_obj->m_ml );
	EGE_ASSERT( method_info != _null );

	// Call method
	return res_obj->InvokeMethod( method_info, args );
}

_ubool _pyModule::Initialize( AStringPtr name, AStringPtr desc )
{
	if ( name.IsEmpty( ) )
		return _false;

	// Copy the basic info
	mName = name;
	mDesc = desc;

	// Initialize python module definition
	mPyModuleDef.m_name	= mName.Str( );
	mPyModuleDef.m_doc	= mDesc.Str( );

	// Initialize python type definition
	mPyTypeObject.tp_name		= EGE_GLOBAL_STR( name + "." + cPyNewKey );
	mPyTypeObject.tp_basicsize	= sizeof( _pyObjResource );
	mPyTypeObject.tp_dealloc	= (destructor) OnDeallocModuleInstance;
	mPyTypeObject.tp_flags		= Py_TPFLAGS_DEFAULT;
	mPyTypeObject.tp_doc		= EGE_GLOBAL_STR( name + "'s Constructor" );
	mPyTypeObject.tp_init		= (initproc) OnInitModuleInstance;
	mPyTypeObject.tp_new		= OnNewModuleInstance;

	// Initialize type object info
	if ( PyType_Ready( &mPyTypeObject ) < 0 )
		return _false;

	// Create module object
	mPyModuleObject = PyModule_Create( &mPyModuleDef );
	if ( mPyModuleObject == _null )
		return _false;

	// Update the module dictionary
	if ( _pyHelper::SetDictItem( PyImport_GetModuleDict( ), mPyModuleDef.m_name, mPyModuleObject ) == _false )
		return _false;

	// Set module description
	if ( _pyHelper::AddObject( mPyModuleObject, cPyDocKey, mDesc.Str( ) ) == _false )
		return _false;

	// Bind self with object info
	if ( _pyHelper::SetDictItem( mPyTypeObject.tp_dict, cPySelfKey, (_dword) this ) == _false )
		return _false;

	// Set module type object constructor
	if ( _pyHelper::AddObject( mPyModuleObject, cPyNewKey, (PyObject*) &mPyTypeObject ) == _false )
		return _false;

	// Add python type object
	sPyObjTypeManager.AddObjType( mName, &mPyTypeObject );

	return _true;
}

AStringPtr _pyModule::GetName( ) const
{
	return mName.Str( );
}

const AStringObj& _pyModule::GetNameObj( ) const
{
	return mName;
}

_ubool _pyModule::RegisterEnumValue( AStringPtr name, _dword value )
{
	return _false;
}

_ubool _pyModule::RegisterProperty( const ScriptPropertyDeclInfo& decl_info )
{
	return _true;
}

_ubool _pyModule::RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info )
{
	// Insert python methods
	PyMethodDef* py_method = InsertMethodDef( decl_info );
	if ( py_method == _null )
		return _false;

	// Create method
	PyObject* method = PyDescr_NewMethod( &mPyTypeObject, py_method );
	if ( method == _null )
		return _false;

	// Insert as method by python function object
	mMethods.InsertAscending( PyMethodInfo( (PyMethodDescrObject*) (PyObject*) method, decl_info, native_func_info ) );

	return _true;
}

#endif