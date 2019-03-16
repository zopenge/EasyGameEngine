//! @file     RHIStatsPixelShader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsPixelShader
//----------------------------------------------------------------------------

class RHIStatsPixelShader : public RHIStatsBase< PixelShaderRHI >
{
private:
	typedef RHIStatsBase< PixelShaderRHI > BaseClass;

public:
	RHIStatsPixelShader( PixelShaderRHI* resource );
	virtual ~RHIStatsPixelShader( );
};

}