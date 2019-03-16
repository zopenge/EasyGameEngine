//! @file     RHIStatsVertexBuffer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsVertexBuffer
//----------------------------------------------------------------------------

class RHIStatsVertexBuffer : public RHIStatsBase< VertexBufferRHI >
{
private:
	typedef RHIStatsBase< VertexBufferRHI > BaseClass;

private:
	_dword	mBufferSize;

public:
	RHIStatsVertexBuffer( VertexBufferRHI* resource );
	virtual ~RHIStatsVertexBuffer( );
};

}