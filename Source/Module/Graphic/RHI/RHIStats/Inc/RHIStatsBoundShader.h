//! @file     RHIStatsBoundShader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsBoundShader
//----------------------------------------------------------------------------

class RHIStatsBoundShader : public RHIStatsBase< BoundShaderRHI >
{
private:
	typedef RHIStatsBase< BoundShaderRHI > BaseClass;

public:
	RHIStatsBoundShader( BoundShaderRHI* resource );
	virtual ~RHIStatsBoundShader( );
};

}