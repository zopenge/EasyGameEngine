//! @file     RHIStatsVertexDeclaration.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsVertexDeclaration
//----------------------------------------------------------------------------

class RHIStatsVertexDeclaration : public RHIStatsBase< VertexDeclarationRHI >
{
private:
	typedef RHIStatsBase< VertexDeclarationRHI > BaseClass;

public:
	RHIStatsVertexDeclaration( VertexDeclarationRHI* resource );
	virtual ~RHIStatsVertexDeclaration( );
};

}