//! @file     NvPhysxShape.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// NvPhysxDrv-Shape Implementation
//----------------------------------------------------------------------------

ShapePHIPassRef NvPhysxDrv::CloneShape( const ShapePHI* shape )
{
	return _null;
}

ChainShapePHIPassRef NvPhysxDrv::CreateChainShape( )
{
	return _null;
}

CircleShapePHIPassRef NvPhysxDrv::CreateCircleShape( )
{
	return _null;
}

_void NvPhysxDrv::SetCircleShapeRadius( CircleShapePHI* shape, _float radius )
{
}

_float NvPhysxDrv::GetCircleShapeRadius( CircleShapePHI* shape )
{
	return 0.0f;
}

EdgeShapePHIPassRef NvPhysxDrv::CreateEdgeShape( )
{
	return _null;
}

PolygonShapePHIPassRef NvPhysxDrv::CreatePolygonShape( )
{
	return _null;
}

_void NvPhysxDrv::SetPolygonShapeVertices( PolygonShapePHI* shape, const Vector3* vertices, _dword number )
{
}

_void NvPhysxDrv::SetPolygonShapeAsBox( PolygonShapePHI* shape, _float width, _float height )
{
}

_dword NvPhysxDrv::GetPolygonShapeVerticesNumber( PolygonShapePHI* shape )
{
	return 0;
}

Vector3 NvPhysxDrv::GetPolygonShapeVertexByIndex( PolygonShapePHI* shape, _dword index )
{
	return Vector3::cOrigin;
}

PlaneShapePHIPassRef NvPhysxDrv::CreatePlaneShape( const Vector3& normal, _float constant )
{
	return _null;
}

BoxShapePHIPassRef NvPhysxDrv::CreateBoxShape( const Vector3& half_extents )
{
	return _null;
}

CylinderShapePHIPassRef NvPhysxDrv::CreateCylinderShape( const Vector3& half_extents )
{
	return _null;
}

CapsuleShapePHIPassRef NvPhysxDrv::CreateCapsuleShape( _float radius, _float height )
{
	return _null;
}

ConeShapePHIPassRef NvPhysxDrv::CreateConeShape( _float radius, _float height )
{
	return _null;
}

SphereShapePHIPassRef NvPhysxDrv::CreateSphereShape( _float radius )
{
	return _null;
}

MultiSphereShapePHIPassRef NvPhysxDrv::CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number )
{
	return _null;
}

ConvexHullShapePHIPassRef NvPhysxDrv::CreateConvexHullShape( const Vector3* pos_list, _dword number )
{
	return _null;
}

ConvexTriangleMeshShapePHIPassRef NvPhysxDrv::CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	return _null;
}

ConvexTriangleMeshShapePHIPassRef NvPhysxDrv::CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	return _null;
}

HeightFieldTerrainShapePHIPassRef NvPhysxDrv::CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges )
{
	return _null;
}

CompoundShapePHIPassRef NvPhysxDrv::CreateCompoundShape( )
{
	return _null;
}

_dword NvPhysxDrv::GetChildShapeNumberOfCompoundShape( const CompoundShapePHI* compound_shape )
{
	return 0;
}

ShapePHIRef NvPhysxDrv::GetChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, _dword index )
{
	return _null;
}

_ubool NvPhysxDrv::AddChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, const Matrix4& transform, ShapePHI* shape )
{
	return _false;
}

_ubool NvPhysxDrv::RemoveChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, ShapePHI* shape )
{
	return _false;
}

//----------------------------------------------------------------------------
// NvPhysxChainShape Implementation
//----------------------------------------------------------------------------

NvPhysxChainShape::NvPhysxChainShape( )
{
}

NvPhysxChainShape::~NvPhysxChainShape( )
{
}

//----------------------------------------------------------------------------
// NvPhysxCircleShape Implementation
//----------------------------------------------------------------------------

NvPhysxCircleShape::NvPhysxCircleShape( )
{
}

NvPhysxCircleShape::~NvPhysxCircleShape( )
{
}

//----------------------------------------------------------------------------
// NvPhysxEdgeShape Implementation
//----------------------------------------------------------------------------

NvPhysxEdgeShape::NvPhysxEdgeShape( )
{
}

NvPhysxEdgeShape::~NvPhysxEdgeShape( )
{
}

//----------------------------------------------------------------------------
// NvPhysxPolygonShape Implementation
//----------------------------------------------------------------------------

NvPhysxPolygonShape::NvPhysxPolygonShape( )
{
}

NvPhysxPolygonShape::~NvPhysxPolygonShape( )
{
}