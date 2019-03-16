//! @file     PhysxResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxResourceManager
//----------------------------------------------------------------------------

class PhysxResourceManager : public TObject< IPhysxResourceManager >
{
private:

public:
	PhysxResourceManager( );
	virtual ~PhysxResourceManager( );

// IPhysxResourceManager Interface
public:
	virtual IPhysxChainShapePassRef					CreateChainShape( ) override;
	virtual IPhysxCircleShapePassRef				CreateCircleShape( ) override;
	virtual IPhysxEdgeShapePassRef					CreateEdgeShape( ) override;
	virtual IPhysxPolygonShapePassRef				CreatePolygonShape( ) override;

	virtual IPhysxPlaneShapePassRef					CreatePlaneShape( const Vector3& normal, _float constant ) override;
	virtual IPhysxBoxShapePassRef					CreateBoxShape( const Vector3& half_extents ) override;
	virtual IPhysxCylinderShapePassRef				CreateCylinderShape( const Vector3& half_extents ) override;
	virtual IPhysxCapsuleShapePassRef				CreateCapsuleShape( _float radius, _float height ) override;
	virtual IPhysxConeShapePassRef					CreateConeShape( _float radius, _float height ) override;
	virtual IPhysxSphereShapePassRef				CreateSphereShape( _float radius ) override;
	virtual IPhysxMultiSphereShapePassRef			CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number ) override;
	virtual IPhysxConvexHullShapePassRef			CreateConvexHullShape( const Vector3* pos_list, _dword number ) override;
	virtual IPhysxConvexTriangleMeshShapePassRef	CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh ) override;
	virtual IPhysxConvexTriangleMeshShapePassRef	CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh ) override;
	virtual IPhysxHeightFieldTerrainShapePassRef	CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges ) override;
	virtual IPhysxCompoundShapePassRef				CreateCompoundShape( ) override;

	virtual IPhysxSoftBodyPassRef					CreateSoftPatch( IPhysxSoftWorldInfo* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, const PointU& grid, _dword fixeds, _ubool gendiags ) override;

	virtual IPhysxRigidBodyPassRef					CreateRigidBody( _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, IPhysxShape* shape ) override;

	virtual IPhysxScenePassRef						CreateScene( const Vector3& gravity ) override;
};

//----------------------------------------------------------------------------
// PhysxResourceManager Implementation
//----------------------------------------------------------------------------

}