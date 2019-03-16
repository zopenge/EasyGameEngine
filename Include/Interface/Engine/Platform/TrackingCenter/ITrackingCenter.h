//! @file     ITrackingCenter.h
//! @author   foreven
//! @version  1.0.0.522
//! @date     2013/10/09

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITrackingCenter
//----------------------------------------------------------------------------

class ITrackingCenter : public IObject
{
public:
	virtual _void	Start( ) PURE;
};

}