//! @file     TEnable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TEnable
//----------------------------------------------------------------------------

template< typename Type >
class TEnable : public Type
{
protected:
	//!	True indicates it's enable.
	_ubool	mIsEnable;

protected:
	TEnable( );
	virtual ~TEnable( );

// IEnable Interface
public:
	virtual _void	Enable( _ubool enable ) override;
	virtual _ubool	IsEnable( ) const override;
};

//----------------------------------------------------------------------------
// TEnable Implementation
//----------------------------------------------------------------------------

template< typename Type >
TEnable< Type >::TEnable( )
{
	mIsEnable = _true;
}

template< typename Type >
TEnable< Type >::~TEnable( )
{
}

template< typename Type >
_void TEnable< Type >::Enable( _ubool enable )
{
	mIsEnable = enable;
}

template< typename Type >
_ubool TEnable< Type >::IsEnable( ) const
{
	return mIsEnable;
}

}