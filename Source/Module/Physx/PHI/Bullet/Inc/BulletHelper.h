//! @file     BulletHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletHelper
//----------------------------------------------------------------------------

class BulletHelper
{
public:
	//!	Get the data type size.
	static _dword GetDataTypeSize( _PHYSX_DATA_TYPE data_type );
	//!	Translate the data type.
	static PHY_ScalarType TranslateScalarType( _PHYSX_DATA_TYPE data_type );

	//!	Translate vector3 to bullet's vector type.
	static btVector3 Vec3ToBTVec3( const Vector3& vector );
	static Vector3 BTVec3ToVec3( const btVector3& vector );

	//!	Translate vector3 to bullet's color type.
	static Color BTVec3ToColor( const btVector3& color );

	//!	Translate matrix3x3 to bullet's transform type.
	static btMatrix3x3 Mat3x3ToBTMat3x3( const Matrix3& transform );
	static Matrix3 BTMat3x3ToMat3x3( const btMatrix3x3& transform );
	//!	Translate matrix4x4 to bullet's transform type.
	static btTransform Mat4x4ToBTTransform( const Matrix4& transform );
	static Matrix4 BtTransformToMat4x4( const btTransform& transform );

	//!	Get the bullet's shape resource.
	static btCollisionShape* GetBTCollisionShape( ShapePHI* shape );

	//!	Get the bullet's collision object resource.
	static btCollisionObject* GetBTCollisionObject( BodyPHI* body );
	static const btCollisionObject* GetBTCollisionObject( const BodyPHI* body );

	//!	Get the bullet's soft body resource.
	static btSoftBody* GetBTSoftBody( SoftBodyPHI* body );
	static const btSoftBody* GetBTSoftBody( const SoftBodyPHI* body );

	//!	Get the bullet's rigid body resource.
	static btRigidBody* GetBTRigidBody( RigidBodyPHI* body );
	static const btRigidBody* GetBTRigidBody( const RigidBodyPHI* body );

	//!	Build the indexed mesh.
	static btIndexedMesh BuildIndexedMesh( const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number );
};

}