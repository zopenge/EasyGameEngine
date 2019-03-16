//! @file     _jscFunction.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscFunction
//----------------------------------------------------------------------------

class _jscFunction : public TObject< _scriptFunction >
{
private:
	//!	The function name
	AStringObj	mFuncName;

public:
	_jscFunction( const AStringObj& func_name );
	virtual ~_jscFunction( );

// _scriptFunction Interface
public:
	virtual AStringPtr			GetName( ) const override;

	virtual _scriptValuePassRef	Invoke( ) override;
	virtual _scriptValuePassRef Invoke( const VariableArray& vars ) override;
};

//----------------------------------------------------------------------------
// _jscFunction Implementation
//----------------------------------------------------------------------------

}