//! @file     TInterpolator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TInterpolator
//----------------------------------------------------------------------------

template< class Type >
class TInterpolator : public TSerializablePropertiesNotifier< IProperties, TNameObject< Type > >
{
protected:
	typedef TSerializablePropertiesNotifier< IProperties, TNameObject< Type > > TBaseClass;

protected:
	TInterpolator( WStringPtr name, IProperties* properties );
	virtual ~TInterpolator( );

// IInterpolator Interface
public:
};

//----------------------------------------------------------------------------
// TInterpolator Implementation
//----------------------------------------------------------------------------

template< class Type >
TInterpolator< Type >::TInterpolator( WStringPtr name, IProperties* properties ) 
	: TBaseClass( properties )
{
	this->mName = name;
}

template< class Type >
TInterpolator< Type >::~TInterpolator( )
{
}

}