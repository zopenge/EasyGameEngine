//! @file     PhysxGlobals.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The physx enumerations
//----------------------------------------------------------------------------

//!	The physx debug drawer flags
enum _PHYSX_DEBUG_DRAWER_FLAG
{
	_PHYSX_DBG_DRAW_WIRE_FRAME			= 1 << 0,
	_PHYSX_DBG_DRAW_AABB				= 1 << 1,
	_PHYSX_DBG_DRAW_FEATURES_TEXT		= 1 << 2,
	_PHYSX_DBG_DRAW_CONTACT_POINTS		= 1 << 3,
	_PHYSX_DBG_NO_DEACTIVATION			= 1 << 4,
	_PHYSX_DBG_NO_HELP_TEXT				= 1 << 5,
	_PHYSX_DBG_DRAW_TEXT				= 1 << 6,
	_PHYSX_DBG_PROFILE_TIMINGS			= 1 << 7,
	_PHYSX_DBG_ENABLE_SAT_COMPARISON	= 1 << 8,
	_PHYSX_DBG_DISABLE_BULLET_LCP		= 1 << 9,
	_PHYSX_DBG_ENABLE_CCD				= 1 << 10,
	_PHYSX_DBG_DRAW_CONSTRAINTS			= 1 << 11,
	_PHYSX_DBG_DRAW_CONSTRAINT_LIMITS	= 1 << 12,
	_PHYSX_DBG_FAST_WIREFRAME			= 1 << 13,
	_PHYSX_DBG_DRAW_NORMALS				= 1 << 14,
};

}