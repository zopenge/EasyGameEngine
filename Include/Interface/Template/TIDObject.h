//! @file     TIDObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TIDObject
//----------------------------------------------------------------------------

template< typename Type >
class TIDObject : public Type
{
protected:
	//!	The ID
	_dword	mID;

protected:
	TIDObject( );
	virtual ~TIDObject( );

// IIDObject Interface
public:
	virtual _dword	GetID( ) const override;
	virtual _void	SetID( _dword id ) override;
};

//----------------------------------------------------------------------------
// TIDObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TIDObject< Type >::TIDObject( )
{
	mID = 0;
}

template< typename Type >
TIDObject< Type >::~TIDObject( )
{
}

template< typename Type >
_dword TIDObject< Type >::GetID( ) const
{
	return mID;
}

template< typename Type >
_void TIDObject< Type >::SetID( _dword id )
{
	mID = id;
}

}