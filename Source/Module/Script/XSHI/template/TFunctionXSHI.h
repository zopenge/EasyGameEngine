//! @file     TFunctionXSHI.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TFunctionXSHI
//----------------------------------------------------------------------------

template< class Type >
class TFunctionXSHI : public Type
{
protected:
	//!	The function info
	NativeFunctionInfoXSHI	mFunctionInfo;

protected:
	TFunctionXSHI( );
	virtual ~TFunctionXSHI( );

public:
	//!	Get the function info.
	EGE_GETR_ACCESSOR_CONST( NativeFunctionInfoXSHI, FunctionInfo )
};

//----------------------------------------------------------------------------
// TFunctionXSHI Implementation
//----------------------------------------------------------------------------

template< class Type >
TFunctionXSHI< Type >::TFunctionXSHI( )
{
}

template< class Type >
TFunctionXSHI< Type >::~TFunctionXSHI( )
{
}

}