//! @file     iosTrackingCenterInmobi.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosTrackingCenterInMobi
//----------------------------------------------------------------------------

class iosTrackingCenterInMobi : public TObject< ITrackingCenter >
{
public:
	iosTrackingCenterInMobi( UStringPtr app_id );
	virtual ~iosTrackingCenterInMobi( );
private:
	UString			mAppID;
public:
	virtual _void	Start( ) override;
};

}