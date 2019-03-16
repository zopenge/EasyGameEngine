//! @file     RHIStatsTextureCube.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RHIStatsTextureCube Implementation
//----------------------------------------------------------------------------

RHIStatsTextureCube::RHIStatsTextureCube( TextureCubeRHI* resource ) : BaseClass( resource )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	mTextureSizeInBytes = gDynamicRHI->GetTextureCubeSizeInBytes( mResource );

	stats.mTotalTextureCubeNumber		++;
	stats.mTotalTextureCubeMemorySize	+= mTextureSizeInBytes;
	stats.mTotalMemorySize				+= mTextureSizeInBytes;
}

RHIStatsTextureCube::~RHIStatsTextureCube( )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	stats.mTotalTextureCubeNumber		--;
	stats.mTotalTextureCubeMemorySize	-= mTextureSizeInBytes;
	stats.mTotalMemorySize				-= mTextureSizeInBytes;
}