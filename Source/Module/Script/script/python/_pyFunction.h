//! @file     _pyFunction.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pyFunction
//----------------------------------------------------------------------------

class _pyFunction : public TObject< _scriptFunction >
{
private:
	//!	The function name
	AStringObj	mFuncName;
	//!	The python function
	PyObject*	mPyFunction;

public:
	_pyFunction( AStringPtr func_name, PyObject* func_obj );
	virtual ~_pyFunction( );

// _scriptFunction Interface
public:
	virtual AStringPtr			GetName( ) const override;

	virtual _scriptValuePassRef	Invoke( ) override;
	virtual _scriptValuePassRef Invoke( const VariableArray& vars ) override;
};

//----------------------------------------------------------------------------
// _pyFunction Implementation
//----------------------------------------------------------------------------

}