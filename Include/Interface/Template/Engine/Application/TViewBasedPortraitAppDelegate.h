//! @file     TViewBasedPortraitAppDelegate.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TViewBasedPortraitAppDelegate
//----------------------------------------------------------------------------

template< typename Type >
class TViewBasedPortraitAppDelegate : public TAppDelegate< Type >
{
protected:
	TViewBasedPortraitAppDelegate( );
	virtual ~TViewBasedPortraitAppDelegate( );

// IViewBasedAppDelegate Interface
public:
	virtual _VIEWBASED_APP_ORIENTATION	OnGetInitialOrientation( ) const override;
};

//----------------------------------------------------------------------------
// TViewBasedPortraitAppDelegate Implementation
//----------------------------------------------------------------------------

template< typename Type >
TViewBasedPortraitAppDelegate< Type >::TViewBasedPortraitAppDelegate( )
{
}

template< typename Type >
TViewBasedPortraitAppDelegate< Type >::~TViewBasedPortraitAppDelegate( )
{
}

template< typename Type >
_VIEWBASED_APP_ORIENTATION TViewBasedPortraitAppDelegate< Type >::OnGetInitialOrientation( ) const
{
	return _VIEWBASED_APP_ORIENTATION_PORT;
}

}