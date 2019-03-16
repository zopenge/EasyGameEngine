//! @file     RHIStatsSurface.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsSurface
//----------------------------------------------------------------------------

class RHIStatsSurface : public RHIStatsBase< SurfaceRHI >
{
private:
	typedef RHIStatsBase< SurfaceRHI > BaseClass;

public:
	RHIStatsSurface( SurfaceRHI* resource );
	virtual ~RHIStatsSurface( );
};

}