//! @file     IPhysxResourceManager.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxResourceManager
//----------------------------------------------------------------------------

class IPhysxResourceManager : public IObject
{
public:
	//!	Create chain shape.
	//!	@param		none.
	//!	@return		The chain shape.
	virtual IPhysxChainShapePassRef CreateChainShape( ) PURE;
	//!	Create circle shape.
	//!	@param		none.
	//!	@return		The circle shape.
	virtual IPhysxCircleShapePassRef CreateCircleShape( ) PURE;
	//!	Create edge shape.
	//!	@param		none.
	//!	@return		The edge shape.
	virtual IPhysxEdgeShapePassRef CreateEdgeShape( ) PURE;
	//!	Create polygon shape.
	//!	@param		none.
	//!	@return		The polygon shape.
	virtual IPhysxPolygonShapePassRef CreatePolygonShape( ) PURE;

	//!	Create plane shape.
	//!	@param		normal		The normal of plane.
	//!	@param		constant	The offset constant of plane.
	//!	@return		The plane shape.
	virtual IPhysxPlaneShapePassRef CreatePlaneShape( const Vector3& normal, _float constant ) PURE;
	//!	Create box shape.
	//!	@param		half_extents	The half extents.
	//!	@return		The box shape.
	virtual IPhysxBoxShapePassRef CreateBoxShape( const Vector3& half_extents ) PURE;
	//!	Create cylinder shape.
	//!	@param		half_extents	The half extents.
	//!	@return		The box shape.
	virtual IPhysxCylinderShapePassRef CreateCylinderShape( const Vector3& half_extents ) PURE;
	//!	Create capsule shape.
	//!	@param		radius			The radius.
	//!	@param		height			The height.
	//!	@return		The capsule shape.
	virtual IPhysxCapsuleShapePassRef CreateCapsuleShape( _float radius, _float height ) PURE;
	//!	Create cone shape.
	//!	@param		radius			The radius.
	//!	@param		height			The height.
	//!	@return		The cone shape.
	virtual IPhysxConeShapePassRef CreateConeShape( _float radius, _float height ) PURE;
	//!	Create sphere shape.
	//!	@param		radius		The radius of sphere.
	//!	@return		The sphere shape.
	virtual IPhysxSphereShapePassRef CreateSphereShape( _float radius ) PURE;
	//!	Create multiple sphere shape.
	//!	@param		pos_list	The position list of sphere.
	//!	@param		radius_list	The radius list of sphere.
	//!	@param		number		The number of sphere.
	//!	@return		The multiple sphere shape.
	virtual IPhysxMultiSphereShapePassRef CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number ) PURE;
	//!	Create convex hull shape.
	//!	@param		pos_list	The vertex list.
	//!	@param		number		The vertex number.
	//!	@return		The convex hull shape.
	virtual IPhysxConvexHullShapePassRef CreateConvexHullShape( const Vector3* pos_list, _dword number ) PURE;
	//!	Create convex triangle mesh shape.
	//!	@param		striding_mesh	The striding mesh interface.
	//!	@return		The convex triangle mesh shape.
	virtual IPhysxConvexTriangleMeshShapePassRef CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh ) PURE;
	//!	Create BVH triangle mesh shape.
	//!	@param		striding_mesh	The striding mesh interface.
	//!	@return		The convex triangle mesh shape.
	virtual IPhysxConvexTriangleMeshShapePassRef CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh ) PURE;
	//!	Create height field terrain shape.
	//!	@param		grid_x			The grid width.
	//!	@param		grid_y			The grid height.
	//!	@param		field_data		The field data.
	//!	@param		height_scale	The scale of height.
	//!	@param		min_height		The min height.
	//!	@param		max_height		The max height.
	//!	@param		up_axis			The up axis.
	//!	@param		data_type		The data type.
	//!	@param		flip_quad_edges	True indicates flip the quad edges.
	//!	@return		The convex triangle mesh shape.
	virtual IPhysxHeightFieldTerrainShapePassRef CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges ) PURE;
	//!	Create compound shape.
	//!	@param		none.
	//!	@return		The compound shape.
	virtual IPhysxCompoundShapePassRef CreateCompoundShape( ) PURE;

	//!	Create a patch.
	//!	@param		world_info		The world info.
	//!	@param		corner00		The corner position.
	//!	@param		corner10		The corner position.
	//!	@param		corner01		The corner position.
	//!	@param		corner11		The corner position.
	//!	@param		grid			The grid size.
	//!	@param		fixeds			The fixeds.
	//!	@param		gendiags		True indicates diags.
	//!	@return		The body interface.
	virtual IPhysxSoftBodyPassRef CreateSoftPatch( IPhysxSoftWorldInfo* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, const PointU& grid, _dword fixeds, _ubool gendiags ) PURE;

	//!	Create the rigid body.
	//!	@param		mass					The mass of body, kg, if it's equal to 0.0f then indicates it's static object.
	//!	@param		start_transform			The start transform of body.
	//!	@param		center_of_mess_offset	The offset of mass center position.
	//!	@param		local_inertia			The inertia of body.
	//!	@param		shape					The shape of body.
	//!	@return		The body interface.
	virtual IPhysxRigidBodyPassRef CreateRigidBody( _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, IPhysxShape* shape ) PURE;

	//!	Create the physx scene.
	//! @param		gravity		The gravity position and weight.
	//!	@return		The physx scene.
	virtual IPhysxScenePassRef CreateScene( const Vector3& gravity ) PURE;
};

}