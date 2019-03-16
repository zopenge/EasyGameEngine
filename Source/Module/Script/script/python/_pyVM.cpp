//! @file     _pyVM.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyVM Implementation
//----------------------------------------------------------------------------

_pyVM::_pyVM( )
{
	mModuleName		= UID::CreateUUID( ).ToStringA( );

	mPyModuleObject	= _null;
	mPyCodeObject	= _null;
}

_pyVM::~_pyVM( )
{
	Py_XDECREF( mPyCodeObject );
}

_ubool _pyVM::Initialize( )
{
	mPyModuleObject = PyImport_AddModule( mModuleName.Str( ) );
	if ( mPyModuleObject == _null )
		return _false;

	return _true;
}

_scriptFunctionPassRef _pyVM::GetScriptFunction( AStringPtr func_name )
{
	PyObject* py_func_obj = _pyHelper::GetObject( mPyModuleObject, func_name.Str( ) );
	if ( py_func_obj == _null || PyCallable_Check( py_func_obj ) == _false )
		return _null;

	return new _pyFunction( func_name, py_func_obj );
}

_ubool _pyVM::LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename )
{
	if ( buffer == _null || size == 0 )
		return _false;

	// Read it as ANSI string
	AString string( (const _chara*) buffer, size );

	// Replace all '\r' to ' ' otherwise it will compile failed
	string.ReplaceAll( '\r', ' ' );

	// Compile script file as bytecode
	mPyCodeObject = Py_CompileString( string.Str( ), "", Py_file_input );
	if ( mPyCodeObject == _null )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	// Execute code
	PyObject* module = PyImport_ExecCodeModule( (_chara*) mModuleName.Str( ), mPyCodeObject );
	if ( module == _null )
	{
		_pyHelper::TraceException( );
		return _false;
	}

	Py_XDECREF( module );

	return _true;
}

#endif