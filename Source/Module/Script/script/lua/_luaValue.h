//! @file     _luaValue.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaValue
//----------------------------------------------------------------------------

class _luaValue : public TObject< _scriptValue >
{
private:
	Variable	mValue;
	WString		mValueString;

public:
	_luaValue( );
	virtual ~_luaValue( );

public:
	//!	Initialize by return value.
	_ubool InitByRetValue( );

// _scriptValue Interface
public:
	virtual const _void*	GetPointer( ) const override;

	virtual _double			GetDouble( ) const override;

	virtual WStringR		GetStringW( ) const override;
};

}