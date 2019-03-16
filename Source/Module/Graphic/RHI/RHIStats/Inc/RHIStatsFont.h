//! @file     RHIStatsFont.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsFont
//----------------------------------------------------------------------------

class RHIStatsFont : public RHIStatsBase< FontRHI >
{
private:
	typedef RHIStatsBase< FontRHI > BaseClass;

public:
	RHIStatsFont( FontRHI* resource );
	virtual ~RHIStatsFont( );
};

}