//! @file     TPowerable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TPowerable
//----------------------------------------------------------------------------

template< typename Type >
class TPowerable : public Type
{
protected:
	//!	True indicates it's power on.
	_ubool	mIsPowerOn;

protected:
	TPowerable( );
	virtual ~TPowerable( );

// IPowerable Interface
public:
	virtual _ubool	PowerOn( ) override;
	virtual _void	PowerOff( ) override;

	virtual _ubool	IsPowerOn( ) const override;
	virtual _ubool	IsPowerOff( ) const override;
};

//----------------------------------------------------------------------------
// TPowerable Implementation
//----------------------------------------------------------------------------

template< typename Type >
TPowerable< Type >::TPowerable( )
{
	mIsPowerOn = _true;
}

template< typename Type >
TPowerable< Type >::~TPowerable( )
{
}

template< typename Type >
_ubool TPowerable< Type >::PowerOn( )
{
	mIsPowerOn = _true;

	return _true;
}

template< typename Type >
_void TPowerable< Type >::PowerOff( )
{
	mIsPowerOn = _false;
}

template< typename Type >
_ubool TPowerable< Type >::IsPowerOn( ) const
{
	return mIsPowerOn;
}

template< typename Type >
_ubool TPowerable< Type >::IsPowerOff( ) const
{
	return !mIsPowerOn;
}

}