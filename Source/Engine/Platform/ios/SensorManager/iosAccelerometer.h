//! @file     iosAccelerometer.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/12/27

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosAccelerometer
//----------------------------------------------------------------------------

class iosAccelerometer : public TObject< IAccelerometer >
{
private:
	struct AccDelegateHandle;

private:
	AccDelegateHandle*	mAccDelegateHandle;

public:
	iosAccelerometer( );
	virtual ~iosAccelerometer( );

// IAccelerometer Interface
public:
	virtual _void	Initialize( IViewBasedApp* viewbased_app, _float update_interval ) override;
	virtual _void	Enable( ) override;
	virtual _void	Disable( ) override;
};

}