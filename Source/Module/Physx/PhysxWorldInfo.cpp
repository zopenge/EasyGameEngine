//! @file     PhysxWorldInfo.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxSoftWorldInfo Implementation
//----------------------------------------------------------------------------

PhysxSoftWorldInfo::PhysxSoftWorldInfo( SoftWorldInfoPHI* world_info )
{
	mWorldInfo = world_info;
}

PhysxSoftWorldInfo::~PhysxSoftWorldInfo( )
{
}

_void PhysxSoftWorldInfo::Tick( _dword limited_elapse, _dword elapse )
{
	mWorldInfo->Tick( limited_elapse, elapse );
}

SoftWorldInfoPHIRef PhysxSoftWorldInfo::GetResource( ) const
{
	return mWorldInfo;
}