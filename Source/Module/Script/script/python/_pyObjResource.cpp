//! @file     _pyObjResource.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyObjResource Implementation
//----------------------------------------------------------------------------

_pyObjResource::_pyObjResource( )
{
	mModule		= _null;
	mWrapClass	= _null;
}

_pyObjResource::~_pyObjResource( )
{
	FreeInstance( );
}

PyObject* _pyObjResource::BuildRetValue( const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers )
{
	PyObject* py_object = _null;

	switch ( var_decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_VOID:
		{
			Py_RETURN_NONE;
		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_ANSI, (const _chara*) registers.mValueRegister );

			py_object = Py_BuildValue( "s", string_utf8.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
			py_object = Py_BuildValue( "s", (const _chara*) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_UTF16, (const _charw*) registers.mValueRegister );

			py_object = Py_BuildValue( "s", string_utf8.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT8:
		case ScriptVarDeclInfo::_TYPE_INT16:
		case ScriptVarDeclInfo::_TYPE_INT32:
		case ScriptVarDeclInfo::_TYPE_UINT8:
		case ScriptVarDeclInfo::_TYPE_UINT16:
		case ScriptVarDeclInfo::_TYPE_UINT32:
		case ScriptVarDeclInfo::_TYPE_FLOAT:
		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			py_object = Py_BuildValue( "i", (_dword) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		{
			// We must have object resource
			EGE_ASSERT( registers.mObjectRegister != _null );

			// Get the python type object
			PyTypeObject* type_object = _pyModule::sPyObjTypeManager.SearchObjType( var_decl_info.mTypeName );
			EGE_ASSERT( type_object != _null );

			// Call 'New' method to create python object resource ( because the class had been saved in object register, so we won't call constructor )
			_pyObjResource* res_obj = (_pyObjResource*) _pyHelper::CallMethod( (PyObject*) type_object, (_chara*) "{s:n}", (_chara*) "call_constructor", _false );
			if ( res_obj == _null )
				return _null;

			// Update the wrapped class
			EGE_ASSERT( res_obj->mWrapClass == _null );
			res_obj->mWrapClass = (_byte*) registers.mObjectRegister;

			py_object = (PyObject*) res_obj;
		}
		break;

		case ScriptVarDeclInfo::_TYPE_OBJECT:
		{
			//PyObject* new_func = _pyHelper::GetObject( mPyModuleObject, cPyNewKey );
			//if ( new_func == _null || PyCallable_Check( new_func ) == _false )
			//	return _null;

			//PyObject* object = PyObject_CallObject( new_func, _null );
			////PyObject* object = PyModule_New( var_decl_info.mName->GetString( ).Str( ) );
			//if ( object == _null )
			//	return _null;

			//module_info->mObject = (IObject*) registers.mObjectRegister;

			//return object;
		}
		break;

		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{
			_byte* buffer	= (_byte*) ((_dword) registers.mValueRegister);
			_dword size		= ((_dword) (registers.mValueRegister >> 32 ));
			EGE_ASSERT( buffer != _null && size != 0 );

			py_object = PyBytes_FromStringAndSize( (const _chara*) buffer, size );
		}
		break;

		default:
			break;
	}

	return py_object;
}

_pyObjResource* _pyObjResource::CreateInstance( PyTypeObject* type, PyObject* args, PyObject* kw )
{
	_pyObjResource* res_obj = (_pyObjResource*) type->tp_alloc( type, 0 );
	if ( res_obj == _null )
		return _null;

	res_obj->mModule		= _null;
	res_obj->mWrapClass		= _null;
	res_obj->mWrapObject	= _null;

	return res_obj;
}

_ubool _pyObjResource::InitInstance( PyObject* args, PyObject* kw )
{
	// Get the dictionary of type object
	PyObject* dict = ob_base.ob_type->tp_dict;
	EGE_ASSERT( dict != _null );

	// Initialize type object
	mModule	= (_pyModule*) _pyHelper::GetDictItemAsUnsignedLong( dict, _pyModule::cPySelfKey );
	mName	= mModule->GetName( );

	// Get the arguments and keywords number
	_dword args_number	= args != _null ? PyTuple_Size( args ) : 0;
	_dword kw_number	= kw != _null ? PyDict_Size( kw ) : 0;

	// Call constructor to initialize it
	if ( args_number == 0 && kw_number == 0 )
	{
		GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( mWrapClass, mName.Str( ) );
	}
	// Parse by keywords
	else if ( args_number == 0 && kw_number != 0 )
	{
		_ubool is_call_constructor = _false;

		// Check whether we need to call constructor or not
		static const _chara* kwlist[] = { "call_constructor", _null };
		if ( !PyArg_ParseTupleAndKeywords( args, kw, "n", (_chara**) kwlist, &is_call_constructor ) )
			return _false;

		// Call constructor if we needed
		if ( is_call_constructor )
			GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( mWrapClass, mName.Str( ) );
	}

	// Add method into dict
	for ( _dword i = 0; i < mModule->GetMethods( ).Number( ); i ++ )
	{
		const PyMethodInfo& method_info = mModule->GetMethods( )[i];

		const PyMethodDef* py_method_def = method_info.mPyMethodObject->d_method;
		EGE_ASSERT( py_method_def != _null );

		if ( _pyHelper::SetDictItem( dict, py_method_def->ml_name, (PyObject*) method_info.mPyMethodObject ) == _false )
			return _false;
	}

	return _true;
}

_void _pyObjResource::FreeInstance( )
{
	// It's class not inherit from IObject
	if ( mWrapClass != _null )
	{
		EGE_ASSERT( mWrapObject.IsNull( ) );

		// Call destructor to release it
		GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( mWrapClass, mName.Str( ) );
	}
	// It's object inherit from IObject
	else if ( mWrapObject.IsValid( ) )
	{
		EGE_ASSERT( mWrapClass == _null );

		// Call Release( ) to decrease referenced counter
		mWrapObject.Clear( );
	}
}

_ubool _pyObjResource::CreateClassResource( )
{
	FreeInstance( );

	return GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( mWrapClass, mName.Str( ) );
}

PyObject* _pyObjResource::InvokeMethod( const PyMethodInfo* method_info, PyObject* args )
{
	const ScriptFuncDeclInfo&	decl_info			= method_info->mDeclInfo;
	const ScriptNativeFuncInfo& native_func_info	= method_info->mNativeFuncInfo;

	// Prepare arguments
	_dword args_buffer[1024];
	if ( _pyHelper::ParseArgTuple( args, decl_info.mParametersDecls, args_buffer ) == _false )
		return _null;

	// Build script registers
	ScriptVMRegisters registers;
	registers.mStackPointer	= args_buffer;

	// The native function will return object class
	if ( decl_info.mRetDecl.HasObj( ) )
	{
		EGE_ASSERT( native_func_info.mHostReturnSize != 0 );

		// Create class resource for return value
		if ( GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( registers.mObjectRegister, decl_info.mRetDecl.mTypeName.Str( ) ) == _false )
			return _null;

		// Invoke method
		_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, mWrapClass );
	}
	else
	{
		if ( mWrapClass != _null )
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, mWrapClass );
		else
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info );
	}

	// Build the return object
	PyObject* ret_obj = BuildRetValue( decl_info.mRetDecl, registers );
	EGE_ASSERT( ret_obj != _null );

	return ret_obj;
}

#endif