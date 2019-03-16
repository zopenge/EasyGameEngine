//! @file     BulletBody.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// BulletDrv-SoftBody Implementation
//----------------------------------------------------------------------------

SoftBodyPHIPassRef BulletDrv::CreateSoftPatch( SoftWorldInfoPHI* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, _dword resx, _dword resy, _dword fixeds, _ubool gendiags )
{
	DYNAMIC_CAST_BULLET_RESOURCE( SoftWorldInfo, world_info );

	btSoftBody* bt_soft_body = btSoftBodyHelpers::CreatePatch( bt_world_info->GetBTWorldInfo( ), 
		BulletHelper::Vec3ToBTVec3( corner00 ),
		BulletHelper::Vec3ToBTVec3( corner10 ),
		BulletHelper::Vec3ToBTVec3( corner01 ),
		BulletHelper::Vec3ToBTVec3( corner11 ),
		resx, 
		resy,
		fixeds,
		EGE_BOOLEAN( gendiags ) );

	return new BulletSoftBody( bt_soft_body );
}

//----------------------------------------------------------------------------
// BulletDrv-RigidBody Implementation
//----------------------------------------------------------------------------

RigidBodyPHIPassRef BulletDrv::CreateRigidBody( _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, ShapePHI* shape )
{
	// Create motion state
	btDefaultMotionState* motion_state = new btDefaultMotionState( BulletHelper::Mat4x4ToBTTransform( start_transform ), BulletHelper::Mat4x4ToBTTransform( center_of_mass_offset ) );

	// Create rigid body
	btRigidBody::btRigidBodyConstructionInfo rigid_body_constructor( mass, motion_state, BulletHelper::GetBTCollisionShape( shape ), BulletHelper::Vec3ToBTVec3( local_inertia ) );
	btRigidBody* bullet_rigid_body = new btRigidBody( rigid_body_constructor );

	return new BulletRigidBody( motion_state, bullet_rigid_body );
}

Vector3 BulletDrv::GetRigidBodyCenter( const RigidBodyPHI* body )
{
	const btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	btTransform transform;
	rigid_body->getMotionState( )->getWorldTransform( transform );

	return BulletHelper::BTVec3ToVec3( transform.getOrigin( ) );
}

Matrix4 BulletDrv::GetRigidBodyTransform( const RigidBodyPHI* body )
{
	const btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	btTransform transform;
	rigid_body->getMotionState( )->getWorldTransform( transform );

	return BulletHelper::BtTransformToMat4x4( transform );
}

_void BulletDrv::SetRigidBodyRestitution( RigidBodyPHI* body, _float restitution )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->setRestitution( restitution );
}

_float BulletDrv::GetRigidBodyRestitution( const RigidBodyPHI* body )
{
	const btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	return rigid_body->getRestitution( );
}

_void BulletDrv::SetRigidBodyDamping( RigidBodyPHI* body, _float lin_damping, _float ang_damping )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->setDamping( lin_damping, ang_damping );
}

_void BulletDrv::SetRigidBodyLinearFactor( RigidBodyPHI* body, const Vector3& factor )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->setLinearFactor( BulletHelper::Vec3ToBTVec3( factor ) );
}

Vector3 BulletDrv::GetRigidBodyLinearFactor( const RigidBodyPHI* body )
{
	const btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	return BulletHelper::BTVec3ToVec3( rigid_body->getLinearFactor( ) );
}

_void BulletDrv::SetRigidBodyAngularFactor( RigidBodyPHI* body, const Vector3& factor )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->setAngularFactor( BulletHelper::Vec3ToBTVec3( factor ) );
}

Vector3	BulletDrv::GetRigidBodyAngularFactor( const RigidBodyPHI* body )
{
	const btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	return BulletHelper::BTVec3ToVec3( rigid_body->getAngularFactor( ) );
}

_void BulletDrv::ApplyRigidBodyCentralImpulse( RigidBodyPHI* body, const Vector3& force )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->applyCentralImpulse( BulletHelper::Vec3ToBTVec3( force ) );
}

_void BulletDrv::ApplyRigidBodyTorqueImpulse( RigidBodyPHI* body, const Vector3& force )
{
	btRigidBody* rigid_body = BulletHelper::GetBTRigidBody( body );
	EGE_ASSERT( rigid_body != _null );

	rigid_body->applyTorqueImpulse( BulletHelper::Vec3ToBTVec3( force ) );
}

//----------------------------------------------------------------------------
// BulletSoftBody Implementation
//----------------------------------------------------------------------------

BulletSoftBody::BulletSoftBody( btSoftBody* body ) : BaseClass( body )
{
}

BulletSoftBody::~BulletSoftBody( )
{
}

//----------------------------------------------------------------------------
// BulletRigidBody Implementation
//----------------------------------------------------------------------------

BulletRigidBody::BulletRigidBody( btDefaultMotionState* motion_state, btRigidBody* body ) : BaseClass( body )
{
	EGE_ASSERT( motion_state != _null ); 

	mBTMotionState = motion_state;
}

BulletRigidBody::~BulletRigidBody( )
{
	EGE_DELETE( mBTMotionState ); 
}

#endif