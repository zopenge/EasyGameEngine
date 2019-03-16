//! @file     _pyHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyHelper Implementation
//----------------------------------------------------------------------------

UString _pyHelper::DumpTraceback( PyObject* tracebackobj )
{
	UString tracebackobj_string;

	if ( tracebackobj != _null )
	{
		for ( PyTracebackObject* object = (PyTracebackObject*) tracebackobj; object != _null; object = object->tb_next )
		{
			const PyCodeObject* codeobj = ((const PyFrameObject*) object->tb_frame)->f_code;

			tracebackobj_string += FORMAT_ASTRING_3( "\n\t\t%s: %s(%d)",
				GetObjectAsUString( codeobj->co_name ).Str( ),
				GetObjectAsUString( codeobj->co_filename ).Str( ),
				object->tb_lineno );
		}
	}

	return tracebackobj_string;
}

_void _pyHelper::DumpSyntaxError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj )
{
	PyErr_Fetch( &typeobj, &valueobj, &tracebackobj );

	_chara* msg = _null; PyObject* obj = _null;
	if ( !PyArg_ParseTuple( valueobj, "sO", &msg, &obj ) )
		return;

	PyObject* filename = _null;
	PyObject* err_text = _null; 
	_dword line_number = 0, offset = 0;
	if ( !PyArg_ParseTuple( obj, "OiiO", &filename, &line_number, &offset, &err_text ) )
		return;

	// Output error string
	ALOG_ERROR_5( 
		"Python syntax error occurred:\n"
		"	msg:%s\n"
		"	line:%d(%d)\n"
		"	err_text:%s\n"
		"	filename:%s\n",
		msg, line_number, offset, GetObjectAsUString( err_text ).Str( ), GetObjectAsUString( filename ).Str( ) );
}

_void _pyHelper::DumpImportError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj )
{
	PyErr_Fetch( &typeobj, &valueobj, &tracebackobj );

	// Get the import error object
	PyImportErrorObject* py_import_err_obj = (PyImportErrorObject*) valueobj;

	// Get the import error info
	UString msg		= GetObjectAsUString( py_import_err_obj->msg );
	UString name	= GetObjectAsUString( py_import_err_obj->name );
	UString path	= GetObjectAsUString( py_import_err_obj->path );

	// Collect the callstack info
	UString tracebackobj_string = DumpTraceback( tracebackobj );

	// Output error string
	ALOG_ERROR_4( 
		"Python import error occurred:\n"
		"	msg:%s\n"
		"	name:%s\n"
		"	path:%s\n"
		"	traceback:%s\n",
		msg.Str( ), name.Str( ), path.Str( ), tracebackobj_string.Str( ) );
}

_void _pyHelper::DumpRuntimeError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj )
{
	PyErr_Fetch( &typeobj, &valueobj, &tracebackobj );
	if ( tracebackobj == _null )
		return;

	// The error strings
	UString valueobj_string		= GetObjectAsUString( valueobj );
	// Collect the callstack info
	UString tracebackobj_string = DumpTraceback( tracebackobj );

	// Output error string
	ALOG_ERROR_2( 
		"Python error occurred:\n"
		"	callstack:%s\n"
		"	[err:%s]\n",
		tracebackobj_string.Str( ), valueobj_string.Str( ) );
}

_void _pyHelper::DumpUnknownError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj )
{
	PyErr_Fetch( &typeobj, &valueobj, &tracebackobj );

	// Collect the callstack info
	UString tracebackobj_string = DumpTraceback( tracebackobj );

	// Output error string
	ALOG_ERROR_3( 
		"Python unknown error occurred:\n"
		"	type:%s\n"
		"	value:%s\n"
		"	traceback:%s\n",
		GetObjectAsUString( typeobj ).Str( ), GetObjectAsUString( valueobj ).Str( ), tracebackobj_string.Str( ) );
}

_void _pyHelper::TraceException( )
{
	// Fetch error object
	PyObject* typeobj		= _null;
	PyObject* valueobj		= _null;
	PyObject* tracebackobj	= _null;

	// Syntax error
	if ( PyErr_ExceptionMatches( PyExc_SyntaxError ) )
		DumpSyntaxError( typeobj, valueobj, tracebackobj );
	// Import error
	else if ( PyErr_ExceptionMatches( PyExc_ImportError ) )
		DumpImportError( typeobj, valueobj, tracebackobj );
	// Runtime/Type/System error
	else if ( PyErr_ExceptionMatches( PyExc_RuntimeError ) || PyErr_ExceptionMatches( PyExc_TypeError ) || PyErr_ExceptionMatches( PyExc_SystemError ) )
		DumpRuntimeError( typeobj, valueobj, tracebackobj );
	// Unknown error
	else
		DumpUnknownError( typeobj, valueobj, tracebackobj );

	// Release object
	Py_XDECREF( typeobj ); 
	Py_XDECREF( valueobj );  
	Py_XDECREF( tracebackobj );
}

UString _pyHelper::GetObjectAsUString( PyObject* object )
{
	if ( object == _null )
		return UString( "" );

	// Check object type
	if ( PyUnicode_Check( object ) == _false )
		return UString( "" );

	// Get return string ( UTF8 )
	return UString( _PyUnicode_AsString( object ) );
}

WString _pyHelper::GetObjectAsWString( PyObject* object )
{
	if ( object == _null )
		return WString( L"" );

	// Check object type
	if ( PyUnicode_Check( object ) == _false )
		return WString( L"" );

	// Get return string ( UTF8 )
	const _chara* utf8string = _PyUnicode_AsString( object );
	if ( utf8string == _null )
		return WString( L"" );

	return WString( ).FromString( _ENCODING_UTF8, utf8string );
}

_ubool _pyHelper::AddObject( PyObject* module, AStringPtr key, AStringPtr value )
{
	if ( PyModule_AddStringConstant( module, key.Str( ), value.Str( ) ) != 0 )
		return _false;

	return _true;
}

_ubool _pyHelper::AddObject( PyObject* module, AStringPtr key, _dword value )
{
	if ( PyModule_AddIntConstant( module, key.Str( ), value ) != 0 )
		return _false;

	return _true;
}

_ubool _pyHelper::AddObject( PyObject* module, AStringPtr key, PyObject* object )
{
	Py_INCREF( object );
	if ( PyModule_AddObject( module, key.Str( ), object ) != 0 )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	return _true;
}

AString _pyHelper::GetObjectAsString( PyObject* module, AStringPtr key )
{
	PyObject* value_object = GetObject( module, key );
	if ( value_object == _null )
		return AString( "" );

	return AString( (const _chara*) PyLong_AsVoidPtr( value_object ) );
}

_int _pyHelper::GetObjectAsLong( PyObject* module, AStringPtr key )
{
	PyObject* value_object = GetObject( module, key );
	if ( value_object == _null )
		return 0;

	_int value = PyLong_AsLong( value_object );
	if ( value == -1 )
	{
		_pyHelper::TraceException( );
		return 0;
	}

	return value;
}

PyObject* _pyHelper::GetObject( PyObject* module, AStringPtr key )
{
	PyObject* dict_object = PyModule_GetDict( module );
	if ( dict_object == _null )
		return _null;

	PyObject* key_object = PyUnicode_FromString( key.Str( ) );
	if ( key_object == _null )
		return _null;

	return PyDict_GetItem( dict_object, key_object );
}

_ubool _pyHelper::SetDictItem( PyObject* dict, AStringPtr key, _dword value )
{
	PyObjectOwner value_obj = PyLong_FromUnsignedLong( value );
	if ( value_obj.IsNull( ) )
		return _false;

	return SetDictItem( dict, key, value_obj );
}

_ubool _pyHelper::SetDictItem( PyObject* dict, AStringPtr key, PyObject* object )
{
	if ( object == _null )
		return _false;

	if ( PyDict_SetItemString( dict, key.Str( ), object ) == -1 )
		return _false;

	return _true;
}

_dword _pyHelper::GetDictItemAsUnsignedLong( PyObject* dict, AStringPtr key )
{
	PyObject* value_obj = PyDict_GetItemString( dict, key.Str( ) );
	if ( value_obj == _null )
		return 0;

	return PyLong_AsUnsignedLong( value_obj );
}

#pragma managed(push, off)
PyObject* _pyHelper::CallMethod( PyObject* method, _chara* format, ... )
{
	// Build arguments
	PyObjectOwner args = PyTuple_New( 0 ); 
	if ( args.IsNull( ) )
		return _null;

	// Build keywords
	va_list va; 
	va_start( va, format ); 
	PyObjectOwner kwds = Py_VaBuildValue( format, va );
	va_end( va ); 

	if ( kwds.IsNull( ) )
		return _null;

	// Call method
	PyObject* ret = PyObject_Call( method, args, kwds ); 
	if ( ret == _null )
		return _null;

	return ret; 
}
#pragma managed(pop)

AString _pyHelper::BuildArgFormatString( const ScriptVarDeclInfoArray& vars )
{
	AString arg_format;

	for ( _dword i = 0; i < vars.Number( ); i ++ )
	{
		const ScriptVarDeclInfo& var_info = vars[i];

		switch ( var_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:	
			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:	
			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:	
				arg_format += "s"; 
				break;

			case ScriptVarDeclInfo::_TYPE_INT8:
			case ScriptVarDeclInfo::_TYPE_INT16:
			case ScriptVarDeclInfo::_TYPE_INT32:
			case ScriptVarDeclInfo::_TYPE_UINT8:
			case ScriptVarDeclInfo::_TYPE_UINT16:
			case ScriptVarDeclInfo::_TYPE_UINT32:
			case ScriptVarDeclInfo::_TYPE_FLOAT:
			case ScriptVarDeclInfo::_TYPE_DOUBLE:
				arg_format += "i"; 
				break;

			case ScriptVarDeclInfo::_TYPE_CLASS:	
				arg_format += "O"; 
				break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	return arg_format;
}

PyObject* _pyHelper::BuildArgs( const VariableArray& vars )
{
	PyObject* py_arg = PyTuple_New( vars.Number( ) );

	for ( _dword i = 0; i < vars.Number( ); i ++ )
	{
		const Variable& var = vars[i];

		switch ( var.GetType( ) )
		{
			case Variable::_TYPE_ID_INT8:	
			case Variable::_TYPE_ID_INT16:	
			case Variable::_TYPE_ID_INT32:	
			{
				PyTuple_SetItem( py_arg, i, Py_BuildValue( "i", (_int) var ) );
			}
			break;

			case Variable::_TYPE_ID_UINT8:	
			case Variable::_TYPE_ID_UINT16:	
			case Variable::_TYPE_ID_UINT32:	
			{
				PyTuple_SetItem( py_arg, i, Py_BuildValue( "i", (_dword) var ) );
			}
			break;

			case Variable::_TYPE_ID_FLOAT:	
			case Variable::_TYPE_ID_DOUBLE:	
			{
				PyTuple_SetItem( py_arg, i, Py_BuildValue( "f", (_float) var ) );
			}
			break;

			case Variable::_TYPE_ID_WSTRING:	
			{
				PyTuple_SetItem( py_arg, i, Py_BuildValue( "u", (const _charw*) var ) );
			}
			break;

			case Variable::_TYPE_ID_POINTER:	
			{
				PyTuple_SetItem( py_arg, i, Py_BuildValue( "O", (_void*) var ) );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	return py_arg;
}

_ubool _pyHelper::ParseArgTuple( PyObject* args, const ScriptVarDeclInfoArray& vars, _dword* args_buffer )
{
	// Check the number of arguments 
#ifdef _DEBUG
	if ( args != _null )
	{
		EGE_ASSERT( PyTuple_Size( args ) == vars.Number( ) );
	}
#endif

	// Parse arguments
	switch ( vars.Number( ) )
	{
		case 0:
			break;

		case 1:
			return ParseArgTupleT( args, vars, args_buffer[0] );

		case 2:
			return ParseArgTupleT( args, vars, args_buffer[0], args_buffer[1] );

		case 3:
			return ParseArgTupleT( args, vars, args_buffer[0], args_buffer[1], args_buffer[2] );

		case 4:
			return ParseArgTupleT( args, vars, args_buffer[0], args_buffer[1], args_buffer[2], args_buffer[3] );

		case 5:
			return ParseArgTupleT( args, vars, args_buffer[0], args_buffer[1], args_buffer[2], args_buffer[3], args_buffer[4] );

		default:
			return _false;
	}

	return _true;
}

#endif