//! @file     _pyFunction.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyFunction Implementation
//----------------------------------------------------------------------------

_pyFunction::_pyFunction( AStringPtr func_name, PyObject* func_obj )
{
	EGE_ASSERT( func_obj != _null );
	Py_XINCREF( func_obj );

	mFuncName	= func_name;
	mPyFunction	= func_obj;
}

_pyFunction::~_pyFunction( )
{
	Py_XDECREF( mPyFunction );
}

AStringPtr _pyFunction::GetName( ) const
{
	return mFuncName.Str( );
}

_scriptValuePassRef _pyFunction::Invoke( )
{
	PyObject* py_ret = PyEval_CallObject( mPyFunction, _null );
	if ( py_ret == _null )
		return _null;

	return new _pyValue( py_ret );
}

_scriptValuePassRef _pyFunction::Invoke( const VariableArray& vars )
{
	if ( vars.Number( ) == 0 )
		return Invoke( );

	// Build python value by arguments
	PyObjectOwner py_args( _pyHelper::BuildArgs( vars ) );

	// Invoke method
	PyObject* py_ret = PyEval_CallObject( mPyFunction, py_args );
	if ( py_ret == _null )
	{
		_pyHelper::TraceException( );
		return _null;
	}

	return new _pyValue( py_ret );
}

#endif