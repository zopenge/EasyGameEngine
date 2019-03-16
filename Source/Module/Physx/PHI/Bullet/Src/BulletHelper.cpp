//! @file     BulletHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletHelper Implementation
//----------------------------------------------------------------------------

_dword BulletHelper::GetDataTypeSize( _PHYSX_DATA_TYPE data_type )
{
	switch ( data_type )
	{
		case _PHYSX_DATA_TYPE_FLOAT:	return sizeof( _float );
		case _PHYSX_DATA_TYPE_DOUBLE:	return sizeof( _double );
		case _PHYSX_DATA_TYPE_INTEGER:	return sizeof( _int );
		case _PHYSX_DATA_TYPE_SHORT:	return sizeof( _short );
		case _PHYSX_DATA_TYPE_UCHAR:	return sizeof( _byte );
		default:
			EGE_ASSERT( 0 );
			return 0;
	}
}

PHY_ScalarType BulletHelper::TranslateScalarType( _PHYSX_DATA_TYPE data_type )
{
	switch ( data_type )
	{
		case _PHYSX_DATA_TYPE_FLOAT:	return PHY_FLOAT;
		case _PHYSX_DATA_TYPE_DOUBLE:	return PHY_DOUBLE;
		case _PHYSX_DATA_TYPE_INTEGER:	return PHY_INTEGER;
		case _PHYSX_DATA_TYPE_SHORT:	return PHY_SHORT;
		case _PHYSX_DATA_TYPE_UCHAR:	return PHY_UCHAR;
		default:
			EGE_ASSERT( 0 );
			return PHY_FLOAT;
	}
}

btVector3 BulletHelper::Vec3ToBTVec3( const Vector3& vector )
{
	return btVector3( vector.x, vector.y, vector.z );
}

Vector3 BulletHelper::BTVec3ToVec3( const btVector3& vector )
{
	return Vector3( vector.x( ), vector.y( ), vector.z( ) );
}

Color BulletHelper::BTVec3ToColor( const btVector3& color )
{
	return Color( color.x( ), color.y( ), color.z( ), 1.0f );
}

btMatrix3x3 BulletHelper::Mat3x3ToBTMat3x3( const Matrix3& transform )
{
	return btMatrix3x3( 
		transform.m[0][0], transform.m[0][1], transform.m[0][2], 
		transform.m[1][0], transform.m[1][1], transform.m[1][2], 
		transform.m[2][0], transform.m[2][1], transform.m[2][2] );
}

Matrix3 BulletHelper::BTMat3x3ToMat3x3( const btMatrix3x3& transform )
{
	return Matrix3( 
		transform.getRow( 0 ).x( ), transform.getRow( 0 ).y( ), transform.getRow( 0 ).z( ), 
		transform.getRow( 1 ).x( ), transform.getRow( 1 ).y( ), transform.getRow( 1 ).z( ), 
		transform.getRow( 2 ).x( ), transform.getRow( 2 ).y( ), transform.getRow( 2 ).z( ) );
}

btTransform BulletHelper::Mat4x4ToBTTransform( const Matrix4& transform )
{
	return btTransform( BulletHelper::Mat3x3ToBTMat3x3( transform.GetRotationMatrix( ) ), BulletHelper::Vec3ToBTVec3( transform.GetTranslationVector( ) ) );
}

Matrix4 BulletHelper::BtTransformToMat4x4( const btTransform& transform )
{
	return Matrix4( ).FromTranslationRotation( BulletHelper::BTVec3ToVec3( transform.getOrigin( ) ), 
		Quaternion( transform.getRotation( ).x( ), transform.getRotation( ).y( ), transform.getRotation( ).z( ), transform.getRotation( ).w( ) ) );
}

btCollisionShape* BulletHelper::GetBTCollisionShape( ShapePHI* shape )
{
	if ( shape == _null )
		return _null;

	switch ( shape->GetResourceType( ) )
	{
		case _PRT_PLANE_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( PlaneShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_BOX_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( BoxShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_CYLINDER_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( CylinderShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_CAPSULE_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( CapsuleShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_CONE_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( ConeShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_SPHERE_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( SphereShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_MULTI_SPHERE_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( MultiSphereShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_CONVEX_HULL_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( ConvexHullShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_CONVEX_TRIANGLE_MESH_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( ConvexTriangleMeshShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_HEIGHT_FIELD_TERRAIN_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( HeightFieldTerrainShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		case _PRT_COMPOUND_SHAPE:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( CompoundShape, shape ); 
			
			return bt_shape->GetBTShape( );
		}
		break;

		default:
			EGE_ASSERT( 0 );
			return _null;
	}
}

btCollisionObject* BulletHelper::GetBTCollisionObject( BodyPHI* body )
{
	if ( body == _null )
		return _null;

	switch ( body->GetResourceType( ) )
	{
		case _PRT_RIGID_BODY:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( RigidBody, body ); 
			
			return bt_body->GetBTBody( );
		}
		break;

		default:
			return _null;
	}
}

const btCollisionObject* BulletHelper::GetBTCollisionObject( const BodyPHI* body )
{
	if ( body == _null )
		return _null;

	switch ( body->GetResourceType( ) )
	{
		case _PRT_RIGID_BODY:
		{
			DYNAMIC_CAST_BULLET_RESOURCE( RigidBody, body ); 
			
			return bt_body->GetBTBody( );
		}
		break;

		default:
			return _null;
	}
}

btSoftBody* BulletHelper::GetBTSoftBody( SoftBodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( SoftBody, body ); 

	return bt_body->GetBTBody( );
}

const btSoftBody* BulletHelper::GetBTSoftBody( const SoftBodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( SoftBody, body ); 

	return bt_body->GetBTBody( );
}

btRigidBody* BulletHelper::GetBTRigidBody( RigidBodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( RigidBody, body ); 

	return bt_body->GetBTBody( );
}

const btRigidBody* BulletHelper::GetBTRigidBody( const RigidBodyPHI* body )
{
	DYNAMIC_CAST_BULLET_RESOURCE( RigidBody, body ); 
			
	return bt_body->GetBTBody( );
}

btIndexedMesh BulletHelper::BuildIndexedMesh( const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number )
{
	btIndexedMesh mesh;
	mesh.m_numTriangles			= index_number / 3;
	mesh.m_triangleIndexBase	= (const unsigned char*) index_list;
	mesh.m_triangleIndexStride	= 3 * sizeof( _word );
	mesh.m_numVertices			= vertices_number;
	mesh.m_vertexBase			= (const unsigned char*) vertices_list;
	mesh.m_vertexStride			= sizeof( Vector3 );

	return mesh;
}

#endif