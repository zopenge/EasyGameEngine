//! @file     androidLocationManager.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidLocationManager
//----------------------------------------------------------------------------

class androidLocationManager : public TObject< ILocationManager >
{
private:
	typedef TObject< ILocationManager > BaseClass;

private:
	//!	The java location manager interface object
	JNIObject mLocationManagerObject;

public:
	androidLocationManager( );
	virtual ~androidLocationManager( );

// ILocationManager Interface
public:
};

//----------------------------------------------------------------------------
// androidLocationManager Implementation
//----------------------------------------------------------------------------

}