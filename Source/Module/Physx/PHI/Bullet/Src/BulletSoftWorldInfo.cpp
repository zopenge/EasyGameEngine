//! @file     BulletSoftWorldInfo.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv-SoftWorldInfo Implementation
//----------------------------------------------------------------------------

SoftWorldInfoPHIPassRef BulletDrv::CreateSoftWorldInfo( ScenePHI* scene )
{
	DYNAMIC_CAST_BULLET_RESOURCE( Scene, scene );

	BulletSoftWorldInfo* bt_world_info = new BulletSoftWorldInfo( );

	// Initialize soft world info
	btSoftBodyWorldInfo& world_info = bt_world_info->GetBTWorldInfo( );
	world_info.m_dispatcher = bt_scene->GetBTDispatcher( );
	world_info.m_broadphase = bt_scene->GetBTBroadPhase( );
	world_info.m_gravity	= bt_scene->GetBTDynamicsWorld( )->getGravity( );
	world_info.m_sparsesdf.Initialize( );

	return bt_world_info;
}

//----------------------------------------------------------------------------
// BulletSoftWorldInfo Implementation
//----------------------------------------------------------------------------

BulletSoftWorldInfo::BulletSoftWorldInfo( )
{
}

BulletSoftWorldInfo::~BulletSoftWorldInfo( )
{
}

_void BulletSoftWorldInfo::Tick( _dword limited_elapse, _dword elapse )
{
	mBTWorldInfo.m_sparsesdf.GarbageCollect( );
}

#endif