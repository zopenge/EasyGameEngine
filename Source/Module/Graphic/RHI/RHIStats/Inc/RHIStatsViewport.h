//! @file     RHIStatsViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsViewport
//----------------------------------------------------------------------------

class RHIStatsViewport : public RHIStatsBase< ViewportRHI >
{
private:
	typedef RHIStatsBase< ViewportRHI > BaseClass;

public:
	RHIStatsViewport( ViewportRHI* resource );
	virtual ~RHIStatsViewport( );
};

}