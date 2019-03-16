//! @file     Expression.h
//! @author   fukun.yang
//! @version  1.1.0.613
//! @date     2014/05/22
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Expression
//----------------------------------------------------------------------------

class Expression
{
private:
	INTERNAL_HANDLER_DECL( );

public:
	Expression( );
	~Expression( );

public:
	_void AddVariable( WStringPtr var_name, _int value );
	_void AddVariable( WStringPtr var_name, _dword value );
	_void AddVariable( WStringPtr var_name, _float value );
	_void RemoveAllVariables( );

	_float Calculate( WStringPtr exp );
};

//----------------------------------------------------------------------------
// Expression Implementation
//----------------------------------------------------------------------------

}