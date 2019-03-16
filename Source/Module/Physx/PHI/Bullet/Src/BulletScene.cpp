//! @file     BulletScene.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv-Scene Implementation
//----------------------------------------------------------------------------

ScenePHIPassRef BulletDrv::CreateScene( const Vector3& gravity )
{
	BulletScene* scene = new BulletScene( );
	if ( scene->Initialize( gravity ) == _false )
		{ EGE_RELEASE( scene ); return _null; }

	return scene;
}

_void BulletDrv::UpdateScene( ScenePHI* scene, _dword elapse )
{
	DYNAMIC_CAST_BULLET_RESOURCE( Scene, scene );

	bt_scene->GetBTDynamicsWorld( )->stepSimulation( EGE_RATIO( elapse, 1000 ) );
}

_void BulletDrv::DrawScene( ScenePHI* scene, IPhysxRenderer* renderer )
{
	DYNAMIC_CAST_BULLET_RESOURCE( Scene, scene );

	bt_scene->DrawWorld( renderer );
}

_void BulletDrv::AddBody( ScenePHI* scene, BodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( Scene, scene );

	switch ( body->GetResourceType( ) )
	{
		case _PRT_RIGID_BODY:
			bt_scene->GetBTDynamicsWorld( )->addRigidBody( BulletHelper::GetBTRigidBody( (RigidBodyPHI*) body ) );
			break;

		case _PRT_SOFT_BODY:
			bt_scene->GetBTDynamicsWorld( )->addSoftBody( BulletHelper::GetBTSoftBody( (SoftBodyPHI*) body ) );
			break;

		default:
			break;
	}
}

_void BulletDrv::RemoveBody( ScenePHI* scene, BodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( Scene, scene );

	bt_scene->GetBTDynamicsWorld( )->removeCollisionObject( BulletHelper::GetBTCollisionObject( body ) );
}

//----------------------------------------------------------------------------
// BulletScene Implementation
//----------------------------------------------------------------------------

BulletScene::BulletScene( )
{
	mBTBroadPhase				= _null;
	mBTCollisionConfiguration	= _null;
	mBTDispatcher				= _null;
	mBTSolver					= _null;

	mBTDynamicsWorld			= _null;
}

BulletScene::~BulletScene( )
{
	EGE_DELETE( mBTDynamicsWorld );

	EGE_DELETE( mBTSolver );
	EGE_DELETE( mBTDispatcher );
	EGE_DELETE( mBTCollisionConfiguration );
	EGE_DELETE( mBTBroadPhase );
}

_ubool BulletScene::Initialize( const Vector3& gravity )
{
	// Build the broadphase
	mBTBroadPhase = new btDbvtBroadphase( );

	// Set up the collision configuration and dispatcher
	mBTCollisionConfiguration	= new btSoftBodyRigidBodyCollisionConfiguration( );
	mBTDispatcher				= new btCollisionDispatcher( mBTCollisionConfiguration );

	// The actual physics solver
	mBTSolver = new btSequentialImpulseConstraintSolver( );

	// The world
	mBTDynamicsWorld = new btSoftRigidDynamicsWorld( mBTDispatcher, mBTBroadPhase, mBTSolver, mBTCollisionConfiguration );
	mBTDynamicsWorld->setGravity( btVector3( gravity.x, gravity.y, gravity.z ) );

	return _true;
}

_void BulletScene::DrawWorld( IPhysxRenderer* renderer )
{
	mBTDebguDrawer.SetRenderer( renderer );

	GetBTDynamicsWorld( )->setDebugDrawer( &mBTDebguDrawer );
	GetBTDynamicsWorld( )->debugDrawWorld( );
}

#endif