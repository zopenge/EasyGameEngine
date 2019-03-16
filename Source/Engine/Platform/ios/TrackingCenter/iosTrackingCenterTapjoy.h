//! @file     iosTrackingCenterTapjoy.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosTrackingCenterTapjoy
//----------------------------------------------------------------------------

class iosTrackingCenterTapjoy : public TObject< ITrackingCenter >
{
public:
	iosTrackingCenterTapjoy( UStringPtr app_id, UStringPtr app_secret_key );
	virtual ~iosTrackingCenterTapjoy( );
private:
	UString			mAppID;
	UString			mAppSecretKey;
public:
	virtual _void	Start( ) override;
};

}