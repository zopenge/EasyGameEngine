//! @file     BulletScene.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletScene
//----------------------------------------------------------------------------

class BulletScene : public ScenePHI
{
private:
	//!	The bullet scene components
	btBroadphaseInterface*					mBTBroadPhase;
	btDefaultCollisionConfiguration*		mBTCollisionConfiguration;
	btCollisionDispatcher*					mBTDispatcher;
	btSequentialImpulseConstraintSolver*	mBTSolver;

	btSoftRigidDynamicsWorld*				mBTDynamicsWorld;

	//!	The bullet scene drawer
	BulletDebugDrawer						mBTDebguDrawer;

public:
	BulletScene( );
	virtual ~BulletScene( );

public:
	EGE_GET_ACCESSOR( btBroadphaseInterface*, BTBroadPhase )
	EGE_GET_ACCESSOR( btDefaultCollisionConfiguration*, BTCollisionConfiguration )
	EGE_GET_ACCESSOR( btCollisionDispatcher*, BTDispatcher )
	EGE_GET_ACCESSOR( btSequentialImpulseConstraintSolver*, BTSolver )
	EGE_GET_ACCESSOR( btSoftRigidDynamicsWorld*, BTDynamicsWorld )

public:
	//!	Initialize.
	_ubool Initialize( const Vector3& gravity );

	//!	Draw world.
	_void DrawWorld( IPhysxRenderer* renderer );
};

}