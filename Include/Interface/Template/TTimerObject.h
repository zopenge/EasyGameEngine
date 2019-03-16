//! @file     TTimerObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TTimerObject
//----------------------------------------------------------------------------

template< typename Type >
class TTimerObject : public TTimeoutObject< Type >
{
protected:
	typedef TTimeoutObject< Type > TBaseClass;

protected:
	//!	The start tickcount of task
	_dword	mTickcount;

protected:
	TTimerObject( );
	virtual ~TTimerObject( );

// ITimeoutObject Interface
public:
	virtual _void	SetTimeout( _dword timeout ) override;

// ITimerObject Interface
public:
	virtual _ubool	IsTimeout( ) const override;
};

//----------------------------------------------------------------------------
// TTimerObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TTimerObject< Type >::TTimerObject( )
{
	mTickcount	= 0;
}

template< typename Type >
TTimerObject< Type >::~TTimerObject( )
{
}

template< typename Type >
_void TTimerObject< Type >::SetTimeout( _dword timeout )
{
	TBaseClass::SetTimeout( timeout );

	mTickcount	= Platform::GetCurrentTickCount( );
}

template< typename Type >
_ubool TTimerObject< Type >::IsTimeout( ) const
{
	if ( this->mTimeout == -1 )
		return _false;

	return Platform::GetCurrentTickCount( ) - mTickcount >= this->mTimeout;
}

}