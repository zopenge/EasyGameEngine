//! @file     _pyHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The python structures
//----------------------------------------------------------------------------

//!	The python object wrapper
struct PyObjectOwner
{
	PyObject* mPyObject;

	operator PyObject* ( )
		{ return mPyObject; }

	_ubool IsValid( ) const
	{
		return mPyObject != _null;
	}
	_ubool IsNull( ) const
	{
		return mPyObject == _null;
	}

	PyObjectOwner( PyObject* object ) : mPyObject( object ) 
	{

	}
	~PyObjectOwner( )
	{
		Py_XDECREF( mPyObject );
	}
};

//!	The python method info
struct PyMethodInfo
{
	PyMethodDescrObject*	mPyMethodObject;
	ScriptFuncDeclInfo		mDeclInfo;
	ScriptNativeFuncInfo	mNativeFuncInfo;

	operator PyMethodDef* ( ) const
		{ return mPyMethodObject->d_method; }

	PyMethodInfo( )
	{
		mPyMethodObject	= _null;
	}
	PyMethodInfo( PyMethodDescrObject* method_obj, const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info )
	{
		mPyMethodObject	= method_obj;
		mDeclInfo		= decl_info;
		mNativeFuncInfo	= native_func_info;
	}
};
typedef Array< PyMethodInfo, PyMethodDef* > PyMethodInfoArray;

// Get the wrapped resource object.
#define GET_WRAPPED_RESOURCE_OBJ( i ) \
	if ( arg_format_string[i - 1] == 'O' ) \
		p##i = (P##i) (_void*) ((_pyObjResource*) p##i)->GetWrappedObject( )

//----------------------------------------------------------------------------
// _pyHelper
//----------------------------------------------------------------------------

class _pyHelper
{
private:
	//!	Dump traceback.
	static UString DumpTraceback( PyObject* tracebackobj );

	//!	Dump python errors.
	static _void DumpSyntaxError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj );
	static _void DumpImportError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj );
	static _void DumpRuntimeError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj );
	static _void DumpUnknownError( PyObject*& typeobj, PyObject*& valueobj, PyObject*& tracebackobj );

public:
	//!	Trace python exception info.
	static _void TraceException( );

	//!	Get python object as UTF-8 string.
	static UString GetObjectAsUString( PyObject* object );
	//!	Get python object as UTF-16 string.
	static WString GetObjectAsWString( PyObject* object );

	//!	Add python object into dict.
	static _ubool AddObject( PyObject* module, AStringPtr key, AStringPtr value );
	static _ubool AddObject( PyObject* module, AStringPtr key, _dword value );
	static _ubool AddObject( PyObject* module, AStringPtr key, PyObject* object );
	//!	Get python object from dict.
	static AString GetObjectAsString( PyObject* module, AStringPtr key );
	static _int GetObjectAsLong( PyObject* module, AStringPtr key );
	static PyObject* GetObject( PyObject* module, AStringPtr key );

	//!	Set item of dictionary.
	static _ubool SetDictItem( PyObject* dict, AStringPtr key, _dword value );
	static _ubool SetDictItem( PyObject* dict, AStringPtr key, PyObject* object );
	//!	Get item from dictionary.
	static _dword GetDictItemAsUnsignedLong( PyObject* dict, AStringPtr key );

	//!	Call method.
	static PyObject* CallMethod( PyObject* method, _chara* format, ... );

	//!	Build python argument format string.
	static AString BuildArgFormatString( const ScriptVarDeclInfoArray& vars );

	//!	Build python arguments.
	static PyObject* BuildArgs( const VariableArray& vars );

	//!	Parse arguments.
	static _ubool ParseArgTuple( PyObject* args, const ScriptVarDeclInfoArray& vars, _dword* args_buffer );

	//!	Parse arguments.
	template< typename P1 >
	static _ubool ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1 );
	template< typename P1, typename P2 >
	static _ubool ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2 );
	template< typename P1, typename P2, typename P3 >
	static _ubool ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3 );
	template< typename P1, typename P2, typename P3, typename P4 >
	static _ubool ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3, P4& p4 );
	template< typename P1, typename P2, typename P3, typename P4, typename P5 >
	static _ubool ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5 );
};

//----------------------------------------------------------------------------
// _pyHelper Implementation
//----------------------------------------------------------------------------

template< typename P1 >
_ubool _pyHelper::ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1 )
{
	AString arg_format_string = _pyHelper::BuildArgFormatString( vars );

	if ( !PyArg_ParseTuple( args, arg_format_string.Str( ), &p1 ) )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	GET_WRAPPED_RESOURCE_OBJ( 1 );

	return _true;
}

template< typename P1, typename P2 >
_ubool _pyHelper::ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2 )
{
	AString arg_format_string = _pyHelper::BuildArgFormatString( vars );

	if ( !PyArg_ParseTuple( args, arg_format_string.Str( ), &p1, &p2 ) )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	GET_WRAPPED_RESOURCE_OBJ( 1 );
	GET_WRAPPED_RESOURCE_OBJ( 2 );

	return _true;
}

template< typename P1, typename P2, typename P3 >
_ubool _pyHelper::ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3 )
{
	AString arg_format_string = _pyHelper::BuildArgFormatString( vars );

	if ( !PyArg_ParseTuple( args, arg_format_string.Str( ), &p1, &p2, &p3 ) )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	GET_WRAPPED_RESOURCE_OBJ( 1 );
	GET_WRAPPED_RESOURCE_OBJ( 2 );
	GET_WRAPPED_RESOURCE_OBJ( 3 );

	return _true;
}

template< typename P1, typename P2, typename P3, typename P4 >
_ubool _pyHelper::ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3, P4& p4 )
{
	AString arg_format_string = _pyHelper::BuildArgFormatString( vars );

	if ( !PyArg_ParseTuple( args, arg_format_string.Str( ), &p1, &p2, &p3, &p4 ) )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	GET_WRAPPED_RESOURCE_OBJ( 1 );
	GET_WRAPPED_RESOURCE_OBJ( 2 );
	GET_WRAPPED_RESOURCE_OBJ( 3 );
	GET_WRAPPED_RESOURCE_OBJ( 4 );

	return _true;
}

template< typename P1, typename P2, typename P3, typename P4, typename P5 >
_ubool _pyHelper::ParseArgTupleT( PyObject* args, const ScriptVarDeclInfoArray& vars, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5 )
{
	AString arg_format_string = _pyHelper::BuildArgFormatString( vars );

	if ( !PyArg_ParseTuple( args, arg_format_string.Str( ), &p1, &p2, &p3, &p4, &p5 ) )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	GET_WRAPPED_RESOURCE_OBJ( 1 );
	GET_WRAPPED_RESOURCE_OBJ( 2 );
	GET_WRAPPED_RESOURCE_OBJ( 3 );
	GET_WRAPPED_RESOURCE_OBJ( 4 );
	GET_WRAPPED_RESOURCE_OBJ( 5 );

	return _true;
}

}