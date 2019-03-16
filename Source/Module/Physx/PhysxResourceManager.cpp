//! @file     PhysxResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxResourceManager Implementation
//----------------------------------------------------------------------------

PhysxResourceManager::PhysxResourceManager( )
{
}

PhysxResourceManager::~PhysxResourceManager( )
{
}

IPhysxChainShapePassRef	PhysxResourceManager::CreateChainShape( )
{
	ChainShapePHIRef shape = gDynamicPHI->CreateChainShape( );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxChainShape( shape );
}

IPhysxCircleShapePassRef PhysxResourceManager::CreateCircleShape( )
{
	CircleShapePHIRef shape = gDynamicPHI->CreateCircleShape( );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxCircleShape( shape );
}

IPhysxEdgeShapePassRef PhysxResourceManager::CreateEdgeShape( )
{
	EdgeShapePHIRef shape = gDynamicPHI->CreateEdgeShape( );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxEdgeShape( shape );
}

IPhysxPolygonShapePassRef PhysxResourceManager::CreatePolygonShape( )
{
	PolygonShapePHIRef shape = gDynamicPHI->CreatePolygonShape( );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxPolygonShape( shape );
}

IPhysxPlaneShapePassRef PhysxResourceManager::CreatePlaneShape( const Vector3& normal, _float constant )
{
	PlaneShapePHIRef shape = gDynamicPHI->CreatePlaneShape( normal, constant );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxPlaneShape( shape );
}

IPhysxBoxShapePassRef PhysxResourceManager::CreateBoxShape( const Vector3& half_extents )
{
	BoxShapePHIRef shape = gDynamicPHI->CreateBoxShape( half_extents );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxBoxShape( shape );
}

IPhysxCylinderShapePassRef PhysxResourceManager::CreateCylinderShape( const Vector3& half_extents )
{
	CylinderShapePHIRef shape = gDynamicPHI->CreateCylinderShape( half_extents );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxCylinderShape( shape );
}

IPhysxCapsuleShapePassRef PhysxResourceManager::CreateCapsuleShape( _float radius, _float height )
{
	CapsuleShapePHIRef shape = gDynamicPHI->CreateCapsuleShape( radius, height );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxCapsuleShape( shape );
}

IPhysxConeShapePassRef PhysxResourceManager::CreateConeShape( _float radius, _float height )
{
	ConeShapePHIRef shape = gDynamicPHI->CreateConeShape( radius, height );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxConeShape( shape );
}

IPhysxSphereShapePassRef PhysxResourceManager::CreateSphereShape( _float radius )
{
	SphereShapePHIRef shape = gDynamicPHI->CreateSphereShape( radius );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxSphereShape( shape );
}

IPhysxMultiSphereShapePassRef PhysxResourceManager::CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number )
{
	MultiSphereShapePHIRef shape = gDynamicPHI->CreateMultiSphereShape( pos_list, radius_list, number );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxMultiSphereShape( shape );
}

IPhysxConvexHullShapePassRef PhysxResourceManager::CreateConvexHullShape( const Vector3* pos_list, _dword number )
{
	ConvexHullShapePHIRef shape = gDynamicPHI->CreateConvexHullShape( pos_list, number );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxConvexHullShape( shape );
}

IPhysxConvexTriangleMeshShapePassRef PhysxResourceManager::CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	ConvexTriangleMeshShapePHIRef shape = gDynamicPHI->CreateConvexTriangleMeshShape( striding_mesh );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxConvexTriangleMeshShape( shape );
}

IPhysxConvexTriangleMeshShapePassRef PhysxResourceManager::CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	ConvexTriangleMeshShapePHIRef shape = gDynamicPHI->CreateBvhTriangleMeshShape( striding_mesh );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxConvexTriangleMeshShape( shape );
}

IPhysxHeightFieldTerrainShapePassRef PhysxResourceManager::CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges )
{
	HeightFieldTerrainShapePHIRef shape = gDynamicPHI->CreateHeightFieldTerrainShape( grid_x, grid_y, field_data, height_scale, min_height, max_height, up_axis, data_type, flip_quad_edges );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxHeightFieldTerrainShape( shape );
}

IPhysxCompoundShapePassRef PhysxResourceManager::CreateCompoundShape( )
{
	CompoundShapePHIRef shape = gDynamicPHI->CreateCompoundShape( );
	if ( shape.IsNull( ) )
		return _null;

	return new PhysxCompoundShape( shape );
}

IPhysxSoftBodyPassRef PhysxResourceManager::CreateSoftPatch( IPhysxSoftWorldInfo* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, const PointU& grid, _dword fixeds, _ubool gendiags )
{
	if ( world_info == _null )
		return _null;

	SoftBodyPHIRef patch_body = gDynamicPHI->CreateSoftPatch( world_info->GetResource( ), corner00, corner10, corner01, corner11, grid.x, grid.y, fixeds, gendiags );
	if ( patch_body.IsNull( ) )
		return _null;

	return new PhysxSoftBody( patch_body );
}

IPhysxRigidBodyPassRef PhysxResourceManager::CreateRigidBody( _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, IPhysxShape* shape )
{
	RigidBodyPHIRef body_resource = gDynamicPHI->CreateRigidBody( mass, start_transform, center_of_mass_offset, local_inertia, shape->GetShapeResource( ) );
	if ( body_resource.IsNull( ) )
		return _null;

	return new PhysxRigidBody( body_resource, shape );
}

IPhysxScenePassRef PhysxResourceManager::CreateScene( const Vector3& gravity )
{
	ScenePHIRef scene = gDynamicPHI->CreateScene( gravity );
	if ( scene.IsNull( ) )
		return _null;

	PhysxScene* physx_scene = new PhysxScene( scene );
	if ( physx_scene->Initialize( ) == _false )
		{ EGE_RELEASE( physx_scene ); return _null; }

	return physx_scene;
}