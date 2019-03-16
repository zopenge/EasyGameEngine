//! @file     iosTrackingCenterAppCPA.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosTrackingCenterAppCPA
//----------------------------------------------------------------------------

class iosTrackingCenterAppCPA : public TObject< ITrackingCenter >
{
public:
	iosTrackingCenterAppCPA( UStringPtr app_id );
	virtual ~iosTrackingCenterAppCPA( );
private:
	UString			mAppID;
public:
	virtual _void	Start( ) override;
};

}