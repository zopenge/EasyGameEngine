//! @file     RHIStatsVertexShader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsVertexShader
//----------------------------------------------------------------------------

class RHIStatsVertexShader : public RHIStatsBase< VertexShaderRHI >
{
private:
	typedef RHIStatsBase< VertexShaderRHI > BaseClass;

public:
	RHIStatsVertexShader( VertexShaderRHI* resource );
	virtual ~RHIStatsVertexShader( );
};

}