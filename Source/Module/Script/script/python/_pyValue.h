//! @file     _pyValue.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pyValue
//----------------------------------------------------------------------------

class _pyValue : public TObject< _scriptValue >
{
private:
	//!	The python value object
	PyObject*	mPyValue;

public:
	_pyValue( PyObject* value );
	virtual ~_pyValue( );

// _scriptValue Interface
public:
	virtual const _void*	GetPointer( ) const override;

	virtual _double			GetDouble( ) const override;

	virtual WString			GetStringW( ) const override;
};

}