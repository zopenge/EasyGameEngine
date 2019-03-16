//! @file     RHIStatsVertexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RHIStatsVertexBuffer Implementation
//----------------------------------------------------------------------------

RHIStatsVertexBuffer::RHIStatsVertexBuffer( VertexBufferRHI* resource ) : BaseClass( resource )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	mBufferSize = gDynamicRHI->GetVertexBufferSize( mResource );

	stats.mTotalVertexBufferNumber		++;
	stats.mTotalVertexBufferMemorySize	+= mBufferSize;
	stats.mTotalMemorySize				+= mBufferSize;
}

RHIStatsVertexBuffer::~RHIStatsVertexBuffer( )
{
	RenderStatsRHI& stats = gDynamicRHI->GetRenderStats( );

	stats.mTotalVertexBufferNumber		--;
	stats.mTotalVertexBufferMemorySize	-= mBufferSize;
	stats.mTotalMemorySize				-= mBufferSize;
}