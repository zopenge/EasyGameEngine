//! @file     _jscValue.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscValue
//----------------------------------------------------------------------------

class _jscValue : public TObject< _scriptValue >
{
private:
	//!	The JS value
	JSValueRef	mJSValue;

public:
	_jscValue( JSValueRef js_value );
	virtual ~_jscValue( );

// _scriptValue Interface
public:
	virtual const _void*	GetPointer( ) const override;

	virtual _double			GetDouble( ) const override;

	virtual WString			GetStringW( ) const override;
};

}