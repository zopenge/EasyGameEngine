//! @file     PhysxNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullPhysxResourceManager
//----------------------------------------------------------------------------

class NullPhysxResourceManager : public INTERFACE_OBJECT_IMPL( IPhysxResourceManager )
{
private:
	typedef INTERFACE_OBJECT_IMPL( IPhysxResourceManager ) BaseClass;

public:
	NullPhysxResourceManager( ) { }
	virtual ~NullPhysxResourceManager( ) { }

// IPhysxResourceManager Interface
public:
	virtual IPhysxChainShapePassRef					CreateChainShape( ) { return _null; }
	virtual IPhysxCircleShapePassRef				CreateCircleShape( ) { return _null; }
	virtual IPhysxEdgeShapePassRef					CreateEdgeShape( ) { return _null; }
	virtual IPhysxPolygonShapePassRef				CreatePolygonShape( ) { return _null; }

	virtual IPhysxPlaneShapePassRef					CreatePlaneShape( const Vector3& normal, _float constant ) { return _null; }
	virtual IPhysxBoxShapePassRef					CreateBoxShape( const Vector3& half_extents ) { return _null; }
	virtual IPhysxCylinderShapePassRef				CreateCylinderShape( const Vector3& half_extents ) { return _null; }
	virtual IPhysxCapsuleShapePassRef				CreateCapsuleShape( _float radius, _float height ) { return _null; }
	virtual IPhysxConeShapePassRef					CreateConeShape( _float radius, _float height ) { return _null; }
	virtual IPhysxSphereShapePassRef				CreateSphereShape( _float radius ) { return _null; }
	virtual IPhysxMultiSphereShapePassRef			CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number ) { return _null; }
	virtual IPhysxConvexHullShapePassRef			CreateConvexHullShape( const Vector3* pos_list, _dword number ) { return _null; }
	virtual IPhysxConvexTriangleMeshShapePassRef	CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh ) { return _null; }
	virtual IPhysxConvexTriangleMeshShapePassRef	CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh ) { return _null; }
	virtual IPhysxHeightFieldTerrainShapePassRef	CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges ) { return _null; }
	virtual IPhysxCompoundShapePassRef				CreateCompoundShape( ) { return _null; }

	virtual IPhysxSoftBodyPassRef					CreateSoftPatch( IPhysxSoftWorldInfo* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, const PointU& grid, _dword fixeds, _ubool gendiags ) { return _null; }

	virtual IPhysxRigidBodyPassRef					CreateRigidBody( _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, IPhysxShape* shape ) { return _null; }

	virtual IPhysxScenePassRef						CreateScene( const Vector3& gravity ) { return _null; }
};

//----------------------------------------------------------------------------
// NullPhysxModule
//----------------------------------------------------------------------------

class NullPhysxModule : public INTERFACE_MODULE_IMPL( IPhysxModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IPhysxModule ) BaseClass;

public:
	NullPhysxModule( ) : BaseClass( L"", Version::cZero ) { }
	virtual ~NullPhysxModule( ) { }

// IPhysxModule Interface
public:
	virtual IPhysxScenePassRef	CreateScene( const Vector3& gravity ) { return _null; }
};

//----------------------------------------------------------------------------
// NullPhysx
//----------------------------------------------------------------------------

class NullPhysx
{
	SINGLETON( NullPhysx )

private:
	NullDynamicPHI				mDynamicPHI;
	NullPhysxResourceManager	mPhysxResourceManager;
	NullPhysxModule				mPhysxModule;

public:
	EGE_GETR_ACCESSOR( NullDynamicPHI, DynamicPHI )
	EGE_GETR_ACCESSOR( NullPhysxResourceManager, PhysxResourceManager )
	EGE_GETR_ACCESSOR( NullPhysxModule, PhysxModule )
};

}