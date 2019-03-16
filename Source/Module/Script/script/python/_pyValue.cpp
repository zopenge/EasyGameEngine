//! @file     _pyValue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyValue Implementation
//----------------------------------------------------------------------------

_pyValue::_pyValue( PyObject* value )
{
	mPyValue = value;
}

_pyValue::~_pyValue( )
{
}

const _void* _pyValue::GetPointer( ) const
{
	EGE_ASSERT( 0 );
	return _null;
}

_double _pyValue::GetDouble( ) const 
{
	if ( PyLong_Check( mPyValue ) )
	{
		return (_double) PyLong_AsLong( mPyValue );
	}
	else if ( PyFloat_Check( mPyValue ) )
	{
		return PyFloat_AsDouble( mPyValue );
	}

	return 0.0f;
}

WString	_pyValue::GetStringW( ) const
{
	if ( PyUnicode_Check( mPyValue ) )
	{
		return PyUnicode_AS_UNICODE( mPyValue );
	}

	return WString( L"" );
}

#endif