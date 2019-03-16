//! @file     NvPhysxFixture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// NvPhysx-Fixture Implementation
//----------------------------------------------------------------------------

FixturePHIPassRef NvPhysxDrv::CreateFixture( BodyPHI* body, const PhysxFixtureDef& fixture, ShapePHI* shape )
{
	return _null;	
}

_void NvPhysxDrv::SetFixtureDensity( FixturePHI* fixture, _float density )
{
}

_float NvPhysxDrv::GetFixtureDensity( FixturePHI* fixture )
{
	return 0.0f;
}

_void NvPhysxDrv::SetFixtureFriction( FixturePHI* fixture, _float friction )
{
}

_float NvPhysxDrv::GetFixtureFriction( FixturePHI* fixture )
{
	return 0.0f;
}

_void NvPhysxDrv::SetFixtureRestitution( FixturePHI* fixture, _float restitution )
{
}

_float NvPhysxDrv::GetFixtureRestitution( FixturePHI* fixture )
{
	return 0.0f;
}

//----------------------------------------------------------------------------
// NvPhysxFixture Implementation
//----------------------------------------------------------------------------

NvPhysxFixture::NvPhysxFixture( )
{
}

NvPhysxFixture::~NvPhysxFixture( )
{
}