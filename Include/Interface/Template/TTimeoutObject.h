//! @file     TTimeoutObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TTimeoutObject
//----------------------------------------------------------------------------

template< typename Type >
class TTimeoutObject : public Type
{
protected:
	//!	The timeout of task
	_dword	mTimeout;

protected:
	TTimeoutObject( );
	virtual ~TTimeoutObject( );

// ITimeoutObject Interface
public:
	virtual _void	SetTimeout( _dword timeout ) override;
	virtual _dword	GetTimeout( ) const override;
};

//----------------------------------------------------------------------------
// TTimeoutObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TTimeoutObject< Type >::TTimeoutObject( )
{
	mTimeout = -1;
}

template< typename Type >
TTimeoutObject< Type >::~TTimeoutObject( )
{
}

template< typename Type >
_void TTimeoutObject< Type >::SetTimeout( _dword timeout )
{
	mTimeout = timeout;
}

template< typename Type >
_dword TTimeoutObject< Type >::GetTimeout( ) const
{
	return mTimeout;
}

}