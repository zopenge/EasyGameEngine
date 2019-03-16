//! @file     androidAccelerometer.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidAccelerometer
//----------------------------------------------------------------------------

class androidAccelerometer : public TObject< IAccelerometer >
{
private:

public:
	androidAccelerometer( );
	virtual ~androidAccelerometer( );

public:

// IAccelerometer Interface
public:
	virtual _void	Initialize( IViewBasedApp* viewbased_app, _float update_interval ) override;
	virtual _void	Enable( ) override;
	virtual _void	Disable( ) override;
};

//----------------------------------------------------------------------------
// androidAccelerometer Implementation
//----------------------------------------------------------------------------

}