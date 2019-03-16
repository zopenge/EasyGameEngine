//! @file     TClassXSHI.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TClassXSHI
//----------------------------------------------------------------------------

template< class Type >
class TClassXSHI : public Type
{
protected:
	//!	The behaviour functions
	FuncPtrXSHI	mBehaviourFuncs[ _XB_MAXNUMBER ];

protected:
	TClassXSHI( );
	virtual ~TClassXSHI( );

public:
	//!	Set the behaviour function.
	_void SetBehaviourFunc( _XSCRIPT_BEHAVIOUR behaviour, const FuncPtrXSHI& func );
	//!	Get the behaviour function.
	const FuncPtrXSHI* GetBehaviourFunc( _XSCRIPT_BEHAVIOUR behaviour ) const;
};

//----------------------------------------------------------------------------
// TClassXSHI Implementation
//----------------------------------------------------------------------------

template< class Type >
TClassXSHI< Type >::TClassXSHI( )
{
	EGE_INIT_ARRAY( mBehaviourFuncs );
}

template< class Type >
TClassXSHI< Type >::~TClassXSHI( )
{
}

template< class Type >
_void TClassXSHI< Type >::SetBehaviourFunc( _XSCRIPT_BEHAVIOUR behaviour, const FuncPtrXSHI& func )
{
	EGE_ASSERT( behaviour < _XB_MAXNUMBER );

	mBehaviourFuncs[ behaviour ] = func;
}

template< class Type >
const FuncPtrXSHI* TClassXSHI< Type >::GetBehaviourFunc( _XSCRIPT_BEHAVIOUR behaviour ) const
{
	EGE_ASSERT( behaviour < _XB_MAXNUMBER );

	const FuncPtrXSHI* func = &mBehaviourFuncs[ behaviour ];
	if ( func->type == 0 )
		return _null;

	return func;
}

}