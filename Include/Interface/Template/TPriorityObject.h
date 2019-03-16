//! @file     TPriorityObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TPriorityObject
//----------------------------------------------------------------------------

template< typename Type >
class TPriorityObject : public Type
{
protected:
	//!	The priority
	_int	mPriority;

protected:
	TPriorityObject( );
	virtual ~TPriorityObject( );

// IPriority Interface
public:
	virtual _void	SetPriority( _int priority ) override;
	virtual _int	GetPriority( ) const override;
};

//----------------------------------------------------------------------------
// TPriorityObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TPriorityObject< Type >::TPriorityObject( )
{
	mPriority = 0;
}

template< typename Type >
TPriorityObject< Type >::~TPriorityObject( )
{
}

template< typename Type >
_void TPriorityObject< Type >::SetPriority( _int priority )
{
	mPriority = priority;
}

template< typename Type >
_int TPriorityObject< Type >::GetPriority( ) const
{
	return mPriority;
}

}