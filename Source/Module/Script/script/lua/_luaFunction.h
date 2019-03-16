//! @file     _luaFunction.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaFunction
//----------------------------------------------------------------------------

class _luaFunction : public TObject< _scriptFunction >
{
private:
	//!	The function name
	AStringObj	mFuncName;

public:
	_luaFunction( );
	virtual ~_luaFunction( );

public:
	_ubool Initialize( AStringPtr func_name );

// _scriptFunction Interface
public:
	virtual AStringPtr			GetName( ) const override;

	virtual _scriptValuePassRef	Invoke( ) override;
	virtual _scriptValuePassRef Invoke( const VariableArray& vars ) override;
};

//----------------------------------------------------------------------------
// _luaFunction Implementation
//----------------------------------------------------------------------------

}