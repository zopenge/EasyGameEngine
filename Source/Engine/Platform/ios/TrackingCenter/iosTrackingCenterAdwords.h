//! @file     iosTrackingCenterAdwords.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosTrackingCenterAdwords
//----------------------------------------------------------------------------

class iosTrackingCenterAdwords : public TObject< ITrackingCenter >
{
public:
	iosTrackingCenterAdwords( UStringPtr conversion_id, UStringPtr label );
	virtual ~iosTrackingCenterAdwords( );
private:
	UString			mConversionId;
	UString			mLabel;
public:
	virtual _void	Start( ) override;
};

}