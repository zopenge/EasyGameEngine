//! @file     RHIStatsIndexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RHIStatsIndexBuffer Implementation
//----------------------------------------------------------------------------

RHIStatsIndexBuffer::RHIStatsIndexBuffer( IndexBufferRHI* resource ) : BaseClass( resource )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	mBufferSize = gDynamicRHI->GetIndexBufferSize( mResource );

	stats.mTotalIndexBufferNumber		++;
	stats.mTotalIndexBufferMemorySize	+= mBufferSize;
	stats.mTotalMemorySize				+= mBufferSize;
}

RHIStatsIndexBuffer::~RHIStatsIndexBuffer( )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	stats.mTotalIndexBufferNumber		--;
	stats.mTotalIndexBufferMemorySize	-= mBufferSize;
	stats.mTotalMemorySize				-= mBufferSize;
}