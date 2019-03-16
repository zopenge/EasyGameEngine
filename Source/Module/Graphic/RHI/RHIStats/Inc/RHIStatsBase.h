//! @file     RHIStatsBase.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsBase
//----------------------------------------------------------------------------

template< typename Type >
class RHIStatsBase : public Type
{
protected:
	Type*	mResource;

protected:
	RHIStatsBase( Type* resource ) 
	{
		EGE_ASSERT( resource != _null );

		mResource = resource;
	}
	virtual ~RHIStatsBase( ) 
	{
	}
};

}