//! @file     TViewBasedLandscapeAppDelegate.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TViewBasedLandscapeAppDelegate
//----------------------------------------------------------------------------

template< typename Type >
class TViewBasedLandscapeAppDelegate : public TAppDelegate< Type >
{
protected:
	TViewBasedLandscapeAppDelegate( );
	virtual ~TViewBasedLandscapeAppDelegate( );

// IViewBasedAppDelegate Interface
public:
	virtual _VIEWBASED_APP_ORIENTATION	OnGetInitialOrientation( ) const override;
};

//----------------------------------------------------------------------------
// TViewBasedLandscapeAppDelegate Implementation
//----------------------------------------------------------------------------

template< typename Type >
TViewBasedLandscapeAppDelegate< Type >::TViewBasedLandscapeAppDelegate( )
{
}

template< typename Type >
TViewBasedLandscapeAppDelegate< Type >::~TViewBasedLandscapeAppDelegate( )
{
}

template< typename Type >
_VIEWBASED_APP_ORIENTATION TViewBasedLandscapeAppDelegate< Type >::OnGetInitialOrientation( ) const
{
	return _VIEWBASED_APP_ORIENTATION_LAND;
}

}