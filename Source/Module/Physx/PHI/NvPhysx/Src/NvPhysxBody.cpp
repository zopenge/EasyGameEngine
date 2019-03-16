//! @file     NvPhysxBody.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// NvPhysx-Body Implementation
//----------------------------------------------------------------------------

RigidBodyPHIPassRef NvPhysxDrv::CreateRigidBody( ScenePHI* scene, _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, ShapePHI* shape )
{
	return _null;
}

_void NvPhysxDrv::RemoveBody( ScenePHI* scene, BodyPHI* body )
{

}

Matrix4 NvPhysxDrv::GetBodyTransform( const BodyPHI* body )
{
	return Matrix4::cIdentity;
}
	
Vector3 NvPhysxDrv::GetBodyCenter( const BodyPHI* body )
{
	return Vector3::cOrigin;
}

_void NvPhysxDrv::SetBodyRestitution( BodyPHI* body, _float restitution )
{
}

_float NvPhysxDrv::GetBodyRestitution( const BodyPHI* body )
{
	return 0.0f;
}

_void NvPhysxDrv::SetBodyDamping( BodyPHI* body, _float lin_damping, _float ang_damping )
{
}

_void NvPhysxDrv::SetBodyLinearFactor( BodyPHI* body, const Vector3& factor )
{
}

Vector3 NvPhysxDrv::GetBodyLinearFactor( const BodyPHI* body )
{
	return Vector3::cOrigin;
}

_void NvPhysxDrv::SetBodyAngularFactor( BodyPHI* body, const Vector3& factor )
{
}

Vector3	NvPhysxDrv::GetBodyAngularFactor( const BodyPHI* body )
{
	return Vector3::cOrigin;
}

_void NvPhysxDrv::ApplyBodyCentralImpulse( BodyPHI* body, const Vector3& force )
{
}

_void NvPhysxDrv::ApplyBodyTorqueImpulse( BodyPHI* body, const Vector3& force )
{
}

//----------------------------------------------------------------------------
// NvPhysxBody Implementation
//----------------------------------------------------------------------------

NvPhysxBody::NvPhysxBody( )
{
}

NvPhysxBody::~NvPhysxBody( )
{
}