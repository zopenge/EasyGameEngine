//! @file     TShowableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TShowableObject
//----------------------------------------------------------------------------

template< typename Type >
class TShowableObject : public Type
{
protected:
	_ubool	mIsShowableObject;

protected:
	TShowableObject( );
	virtual ~TShowableObject( );

// IShowableObject Interface
public:
	virtual _void	Show( _ubool show ) override;
	virtual _ubool	IsShow( ) const override;
};

//----------------------------------------------------------------------------
// TShowableObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TShowableObject< Type >::TShowableObject( )
{
	mIsShowableObject = _true;
}

template< typename Type >
TShowableObject< Type >::~TShowableObject( )
{
}

template< typename Type >
_void TShowableObject< Type >::Show( _ubool show )
{
	mIsShowableObject = show;
}

template< typename Type >
_ubool TShowableObject< Type >::IsShow( ) const
{
	return mIsShowableObject;
}

}