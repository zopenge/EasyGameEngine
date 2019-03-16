//! @file     BulletShape.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv-Shape Implementation
//----------------------------------------------------------------------------

ShapePHIPassRef BulletDrv::CloneShape( const ShapePHI* shape )
{
	return _null;
}

ChainShapePHIPassRef BulletDrv::CreateChainShape( )
{
	return _null;
}

CircleShapePHIPassRef BulletDrv::CreateCircleShape( )
{
	return _null;
}

_void BulletDrv::SetCircleShapeRadius( CircleShapePHI* shape, _float radius )
{
}

_float BulletDrv::GetCircleShapeRadius( CircleShapePHI* shape )
{
	return 0.0f;
}

EdgeShapePHIPassRef BulletDrv::CreateEdgeShape( )
{
	return _null;
}

PolygonShapePHIPassRef BulletDrv::CreatePolygonShape( )
{
	return _null;
}

_void BulletDrv::SetPolygonShapeVertices( PolygonShapePHI* shape, const Vector3* vertices, _dword number )
{
}

_void BulletDrv::SetPolygonShapeAsBox( PolygonShapePHI* shape, _float width, _float height )
{
}

_dword BulletDrv::GetPolygonShapeVerticesNumber( PolygonShapePHI* shape )
{
	return 0;
}

Vector3 BulletDrv::GetPolygonShapeVertexByIndex( PolygonShapePHI* shape, _dword index )
{
	return Vector3::cOrigin;
}

PlaneShapePHIPassRef BulletDrv::CreatePlaneShape( const Vector3& normal, _float constant )
{
	return new BulletPlaneShape( new btStaticPlaneShape( BulletHelper::Vec3ToBTVec3( normal ), constant ) );
}

BoxShapePHIPassRef BulletDrv::CreateBoxShape( const Vector3& half_extents )
{
	return new BulletBoxShape( new btBoxShape( BulletHelper::Vec3ToBTVec3( half_extents ) ) );
}

CylinderShapePHIPassRef BulletDrv::CreateCylinderShape( const Vector3& half_extents )
{
	return new BulletCylinderShape( new btCylinderShape( BulletHelper::Vec3ToBTVec3( half_extents ) ) );
}

CapsuleShapePHIPassRef BulletDrv::CreateCapsuleShape( _float radius, _float height )
{
	return new BulletCapsuleShape( new btCapsuleShape( radius, height ) );
}

ConeShapePHIPassRef BulletDrv::CreateConeShape( _float radius, _float height )
{
	return new BulletConeShape( new btConeShape( radius, height ) );
}

SphereShapePHIPassRef BulletDrv::CreateSphereShape( _float radius )
{
	return new BulletSphereShape( new btSphereShape( radius ) );
}

MultiSphereShapePHIPassRef BulletDrv::CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number )
{
	MemArrayPtr< btVector3 > bullet_pos_list( number );
	for ( _dword i = 0; i < number; i ++ )
	{
		bullet_pos_list[i].setX( pos_list[i].x );
		bullet_pos_list[i].setY( pos_list[i].y );
		bullet_pos_list[i].setZ( pos_list[i].z );
	}

	return new BulletMultiSphereShape( new btMultiSphereShape( bullet_pos_list, radius_list, number ) );
}

ConvexHullShapePHIPassRef BulletDrv::CreateConvexHullShape( const Vector3* pos_list, _dword number )
{
	return new BulletConvexHullShape( new btConvexHullShape( (const btScalar*) pos_list, number, sizeof( Vector3 ) ) );
}

ConvexTriangleMeshShapePHIPassRef BulletDrv::CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	if ( striding_mesh == _null )
		return _null;

	DYNAMIC_CAST_BULLET_RESOURCE( StridingMesh, striding_mesh );

	return new BulletConvexTriangleMeshShape( bt_striding_mesh, new btConvexTriangleMeshShape( bt_striding_mesh->GetBTStridingMesh( ) ) );
}

ConvexTriangleMeshShapePHIPassRef BulletDrv::CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	if ( striding_mesh == _null )
		return _null;

	DYNAMIC_CAST_BULLET_RESOURCE( StridingMesh, striding_mesh );

	return new BulletBvhTriangleMeshShape( bt_striding_mesh, new btBvhTriangleMeshShape( bt_striding_mesh->GetBTStridingMesh( ), _true, _true ) );
}

HeightFieldTerrainShapePHIPassRef BulletDrv::CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges )
{
	if ( grid_x == 0 || grid_y == 0 || field_data == _null )
		return _null;

	// Get the filed data size
	_dword field_data_size = BulletHelper::GetDataTypeSize( data_type ) * grid_x * grid_y;
	if ( field_data_size == 0 )
		return _null;

	// Get the up axis
	_int bullet_up_axis = 0;
	switch ( up_axis )
	{
		case _PHYSX_AXIS_TYPE_X: bullet_up_axis = 0; break;
		case _PHYSX_AXIS_TYPE_Y: bullet_up_axis = 1; break;
		case _PHYSX_AXIS_TYPE_Z: bullet_up_axis = 2; break;
		default:
			return _null;
	}

	// Copy field data
	_byte* field_data_temp = new _byte[ field_data_size ];
	EGE_MEM_CPY( field_data_temp, field_data, field_data_size );

	btHeightfieldTerrainShape* bullet_shape = new btHeightfieldTerrainShape( grid_x, grid_y, field_data_temp, height_scale, min_height, max_height, bullet_up_axis, BulletHelper::TranslateScalarType( data_type ), EGE_BOOLEAN( flip_quad_edges ) );

	return new BulletHeightFieldTerrainShape( field_data_temp, bullet_shape );
}

CompoundShapePHIPassRef BulletDrv::CreateCompoundShape( )
{
	return new BulletCompoundShape( new btCompoundShape( ) );
}

_dword BulletDrv::GetChildShapeNumberOfCompoundShape( const CompoundShapePHI* compound_shape )
{
	DYNAMIC_CAST_BULLET_RESOURCE( CompoundShape, compound_shape );

	return bt_compound_shape->GetChildShapesNumber( );
}

ShapePHIRef BulletDrv::GetChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, _dword index )
{
	DYNAMIC_CAST_BULLET_RESOURCE( CompoundShape, compound_shape );

	return bt_compound_shape->GetChildShape( index );
}

_ubool BulletDrv::AddChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, const Matrix4& transform, ShapePHI* shape )
{
	DYNAMIC_CAST_BULLET_RESOURCE( CompoundShape, compound_shape );

	return bt_compound_shape->AddChildShape( transform, shape );
}

_ubool BulletDrv::RemoveChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, ShapePHI* shape )
{
	DYNAMIC_CAST_BULLET_RESOURCE( CompoundShape, compound_shape );

	return bt_compound_shape->RemoveChildShape( shape );
}

////----------------------------------------------------------------------------
//// BulletCircleShape Implementation
////----------------------------------------------------------------------------
//
//BulletCircleShape::BulletCircleShape( )
//{
//}
//
//BulletCircleShape::~BulletCircleShape( )
//{
//}
//

////----------------------------------------------------------------------------
//// BulletEdgeShape Implementation
////----------------------------------------------------------------------------
//
//BulletEdgeShape::BulletEdgeShape( )
//{
//}
//
//BulletEdgeShape::~BulletEdgeShape( )
//{
//}
//
////----------------------------------------------------------------------------
//// BulletPolygonShape Implementation
////----------------------------------------------------------------------------
//
//BulletPolygonShape::BulletPolygonShape( )
//{
//}
//
//BulletPolygonShape::~BulletPolygonShape( )
//{
//}

//----------------------------------------------------------------------------
// BulletPlaneShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Plane, btStaticPlaneShape )

//----------------------------------------------------------------------------
// BulletBoxShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Box, btBoxShape )

//----------------------------------------------------------------------------
// BulletCylinderShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Cylinder, btCylinderShape )

//----------------------------------------------------------------------------
// BulletCapsuleShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Capsule, btCapsuleShape )

//----------------------------------------------------------------------------
// BulletConeShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Cone, btConeShape )

//----------------------------------------------------------------------------
// BulletSphereShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( Sphere, btSphereShape )

//----------------------------------------------------------------------------
// BulletMultiSphereShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( MultiSphere, btMultiSphereShape )

//----------------------------------------------------------------------------
// BulletConvexHullShape Implementation
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_IMPL( ConvexHull, btConvexHullShape )

//----------------------------------------------------------------------------
// BulletConvexTriangleMeshShape Implementation
//----------------------------------------------------------------------------

BulletConvexTriangleMeshShape::BulletConvexTriangleMeshShape( StridingMeshPHI* striding_mesh, btConvexTriangleMeshShape* shape ) : BaseClass( shape )
{
	mStridingMesh = striding_mesh;
}

BulletConvexTriangleMeshShape::~BulletConvexTriangleMeshShape( )
{
}

//----------------------------------------------------------------------------
// BulletBvhTriangleMeshShape Implementation
//----------------------------------------------------------------------------

BulletBvhTriangleMeshShape::BulletBvhTriangleMeshShape( StridingMeshPHI* striding_mesh, btBvhTriangleMeshShape* shape ) : BaseClass( shape )
{
	mStridingMesh = striding_mesh;
}

BulletBvhTriangleMeshShape::~BulletBvhTriangleMeshShape( )
{
}

//----------------------------------------------------------------------------
// BulletHeightFieldTerrainShape Implementation
//----------------------------------------------------------------------------

BulletHeightFieldTerrainShape::BulletHeightFieldTerrainShape( _byte* field_data, btHeightfieldTerrainShape* shape ) : BaseClass( shape )
{
	mFieldData = field_data;
}

BulletHeightFieldTerrainShape::~BulletHeightFieldTerrainShape( )
{
	EGE_DELETE_ARRAY( mFieldData );
}

//----------------------------------------------------------------------------
// BulletCompoundShape Implementation
//----------------------------------------------------------------------------

BulletCompoundShape::BulletCompoundShape( btCompoundShape* shape ) : BaseClass( shape )
{
}

BulletCompoundShape::~BulletCompoundShape( )
{
}

_dword BulletCompoundShape::GetChildShapesNumber( ) const
{
	return mChildShapes.Number( );
}

ShapePHIRef BulletCompoundShape::GetChildShape( _dword index )
{
	return mChildShapes[ index ];
}

_ubool BulletCompoundShape::AddChildShape( const Matrix4& transform, ShapePHI* shape )
{
	mChildShapes.Append( shape );

	mBTShape->addChildShape( BulletHelper::Mat4x4ToBTTransform( transform ), BulletHelper::GetBTCollisionShape( shape ) );

	return _true;
}

_ubool BulletCompoundShape::RemoveChildShape( ShapePHI* shape )
{
	mChildShapes.Remove( shape );

	mBTShape->removeChildShape( BulletHelper::GetBTCollisionShape( shape ) );

	return _true;
}

#endif