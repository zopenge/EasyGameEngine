//! @file     RHIStatsIndexBuffer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsIndexBuffer
//----------------------------------------------------------------------------

class RHIStatsIndexBuffer : public RHIStatsBase< IndexBufferRHI >
{
private:
	typedef RHIStatsBase< IndexBufferRHI > BaseClass;

private:
	_dword	mBufferSize;

public:
	RHIStatsIndexBuffer( IndexBufferRHI* resource );
	virtual ~RHIStatsIndexBuffer( );
};

}