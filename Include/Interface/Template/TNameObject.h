//! @file     TNameObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNameObject
//----------------------------------------------------------------------------

template< typename Type >
class TNameObject : public Type
{
protected:
	//!	The name
	WString	mName;

protected:
	TNameObject( );
	TNameObject( WStringPtr name );
	virtual ~TNameObject( );

// INameObject Interface
public:
	virtual _void		SetName( WStringPtr name ) override;
	virtual WStringPtr	GetName( ) const override;
};

//----------------------------------------------------------------------------
// TNameObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNameObject< Type >::TNameObject( )
{
}

template< typename Type >
TNameObject< Type >::TNameObject( WStringPtr name ) : mName( name )
{
}

template< typename Type >
TNameObject< Type >::~TNameObject( )
{
}

template< typename Type >
_void TNameObject< Type >::SetName( WStringPtr name )
{
	mName = name;
}

template< typename Type >
WStringPtr TNameObject< Type >::GetName( ) const
{
	return mName;
}

}