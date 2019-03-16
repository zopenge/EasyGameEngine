//! @file     PhysxBody.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxSoftBody Implementation
//----------------------------------------------------------------------------

PhysxSoftBody::PhysxSoftBody( SoftBodyPHI* body ) : BaseClass( body )
{
}

PhysxSoftBody::~PhysxSoftBody( )
{
}

//----------------------------------------------------------------------------
// PhysxRigidBody Implementation
//----------------------------------------------------------------------------

PhysxRigidBody::PhysxRigidBody( RigidBodyPHI* body, IPhysxShape* shape ) : BaseClass( body )
{
	mShape = shape;
}

PhysxRigidBody::~PhysxRigidBody( )
{
}

Vector3 PhysxRigidBody::GetCenter( ) const
{
	return gDynamicPHI->GetRigidBodyCenter( mBodyRes );
}

Matrix4	PhysxRigidBody::GetTransform( ) const
{
	return gDynamicPHI->GetRigidBodyTransform( mBodyRes );
}

_void PhysxRigidBody::SetRestitution( _float restitution )
{
	gDynamicPHI->SetRigidBodyRestitution( mBodyRes, restitution );
}

_float PhysxRigidBody::GetRestitution( ) const
{
	return gDynamicPHI->GetRigidBodyRestitution( mBodyRes );
}

_void PhysxRigidBody::SetDamping( _float lin_damping, _float ang_damping )
{
	gDynamicPHI->SetRigidBodyDamping( mBodyRes, lin_damping, ang_damping );
}

_void PhysxRigidBody::SetLinearFactor( const Vector3& factor )
{
	gDynamicPHI->SetRigidBodyLinearFactor( mBodyRes, factor );
}

Vector3	PhysxRigidBody::GetLinearFactor( ) const
{
	return gDynamicPHI->GetRigidBodyLinearFactor( mBodyRes );
}

_void PhysxRigidBody::SetAngularFactor( const Vector3& factor )
{
	gDynamicPHI->SetRigidBodyAngularFactor( mBodyRes, factor );
}

Vector3	PhysxRigidBody::GetAngularFactor( ) const
{
	return gDynamicPHI->GetRigidBodyAngularFactor( mBodyRes );
}

_void PhysxRigidBody::ApplyCentralImpulse( const Vector3& force )
{
	gDynamicPHI->ApplyRigidBodyCentralImpulse( mBodyRes, force );
}

_void PhysxRigidBody::ApplyTorqueImpulse( const Vector3& force )
{
	gDynamicPHI->ApplyRigidBodyTorqueImpulse( mBodyRes, force );
}