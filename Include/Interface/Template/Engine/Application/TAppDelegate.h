//! @file     TAppDelegate.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAppDelegate
//----------------------------------------------------------------------------

template< typename Type >
class TAppDelegate : public INTERFACE_OBSERVER_IMPL( Type )
{
protected:
	TAppDelegate( );
	virtual ~TAppDelegate( );

// IViewBasedAppDelegate Interface
public:
};

//----------------------------------------------------------------------------
// TAppDelegate Implementation
//----------------------------------------------------------------------------

template< typename Type >
TAppDelegate< Type >::TAppDelegate( )
{
}

template< typename Type >
TAppDelegate< Type >::~TAppDelegate( )
{
}

}