//! @file     RHIStatsTextureCube.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsTextureCube
//----------------------------------------------------------------------------

class RHIStatsTextureCube : public RHIStatsBase< TextureCubeRHI >
{
private:
	typedef RHIStatsBase< TextureCubeRHI > BaseClass;

private:
	_dword mTextureSizeInBytes;

public:
	RHIStatsTextureCube( TextureCubeRHI* resource );
	virtual ~RHIStatsTextureCube( );
};

}