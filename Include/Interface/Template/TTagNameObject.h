//! @file     TTagNameObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TTagNameObject
//----------------------------------------------------------------------------

template< typename Type >
class TTagNameObject : public Type
{
protected:
	//!	The tag name
	WString	mTagName;

protected:
	TTagNameObject( );
	TTagNameObject( WStringPtr name );
	virtual ~TTagNameObject( );

// INameObject Interface
public:
	virtual _void		SetTagName( WStringPtr name ) override;
	virtual WStringPtr	GetTagName( ) const override;
};

//----------------------------------------------------------------------------
// TTagNameObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TTagNameObject< Type >::TTagNameObject( )
{
}

template< typename Type >
TTagNameObject< Type >::TTagNameObject( WStringPtr name ) : mTagName( name )
{
}

template< typename Type >
TTagNameObject< Type >::~TTagNameObject( )
{
}

template< typename Type >
_void TTagNameObject< Type >::SetTagName( WStringPtr name )
{
	mTagName = name;
}

template< typename Type >
WStringPtr TTagNameObject< Type >::GetTagName( ) const
{
	return mTagName;
}

}