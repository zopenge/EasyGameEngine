//! @file     RHIStatsTexture.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsTexture
//----------------------------------------------------------------------------

class RHIStatsTexture : public RHIStatsBase< TextureRHI >
{
private:
	typedef RHIStatsBase< TextureRHI > BaseClass;

public:
	RHIStatsTexture( TextureRHI* resource );
	virtual ~RHIStatsTexture( );
};

}