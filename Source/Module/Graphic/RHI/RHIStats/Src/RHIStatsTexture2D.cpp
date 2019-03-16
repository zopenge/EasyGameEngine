//! @file     RHIStatsTexture2D.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RHIStatsTexture2D Implementation
//----------------------------------------------------------------------------

RHIStatsTexture2D::RHIStatsTexture2D( Texture2DRHI* resource ) : BaseClass( resource )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	mIsCompressedTexture	= gDynamicRHI->IsTexture2DCompressed( mResource );
	mTextureSizeInBytes		= gDynamicRHI->GetTexture2DSizeInBytes( mResource );

	if ( mIsCompressedTexture )
		stats.mTotalCompressedTexture2DNumber ++;

	stats.mTotalTexture2DNumber		++;
	stats.mTotalTexture2DMemorySize	+= mTextureSizeInBytes;
	stats.mTotalMemorySize			+= mTextureSizeInBytes;
}

RHIStatsTexture2D::~RHIStatsTexture2D( )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	if ( mIsCompressedTexture )
		stats.mTotalCompressedTexture2DNumber --;

	stats.mTotalTexture2DNumber		--;
	stats.mTotalTexture2DMemorySize	-= mTextureSizeInBytes;
	stats.mTotalMemorySize			-= mTextureSizeInBytes;
}