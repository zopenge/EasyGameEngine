//! @file     TClonableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TClonableObject
//----------------------------------------------------------------------------

template< class SelfType, class CloneInterfaceType, class Type = CloneInterfaceType >
class TClonableObject : public Type
{
protected:

protected:
	TClonableObject( );
	virtual ~TClonableObject( );

// IClonableObject Interface
public:
	virtual PassRefPtr< CloneInterfaceType > CloneTo( ) const override;
};

//----------------------------------------------------------------------------
// TClonableObject Implementation
//----------------------------------------------------------------------------

template< class SelfType, class CloneInterfaceType, class Type >
TClonableObject< SelfType, CloneInterfaceType, Type >::TClonableObject( )
{
}

template< class SelfType, class CloneInterfaceType, class Type >
TClonableObject< SelfType, CloneInterfaceType, Type >::~TClonableObject( )
{
}

template< class SelfType, class CloneInterfaceType, class Type >
PassRefPtr< CloneInterfaceType > TClonableObject< SelfType, CloneInterfaceType, Type >::CloneTo( ) const
{
	PassRefPtr< CloneInterfaceType > object = new SelfType( );
	if ( object->CloneFrom( this ) == _false )
		return _null;

	return object;
}

}