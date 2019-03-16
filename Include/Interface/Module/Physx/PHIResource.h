//! @file     PHIResource.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxFixtureDef
//----------------------------------------------------------------------------

struct PhysxFixtureDef
{
	//! The friction coefficient, usually in the range [0,1].
	_float				mFriction;
	//! The restitution (elasticity) usually in the range [0,1].
	_float				mRestitution;
	//! The density, usually in kg/m^2.
	_float				mDensity;

	//! A sensor shape collects contact information but never generates a collision response.
	_ubool				mIsSensor;

	//! The user defined parameters
	QwordParameters2	mParameters;

	PhysxFixtureDef( )
	{
		mFriction		= 0.2f;
		mRestitution	= 0.0f;
		mDensity		= 0.0f;

		mIsSensor		= _false;
	}
};

//----------------------------------------------------------------------------
// Common PHI definitions
//----------------------------------------------------------------------------

//!	The (PRT, Physx Resource Type)
enum _PHYSX_RESOURCE_TYPE
{
	_PRT_NONE,

	//!	Basic resources
	_PRT_STRIDING_MESH,
	_PRT_SOFT_WORLD_INFO,

	//!	Shape
	_PRT_SHAPE,
	_PRT_CHAIN_SHAPE,
	_PRT_CIRCLE_SHAPE,
	_PRT_EDGE_SHAPE,
	_PRT_POLYGON_SHAPE,
	_PRT_PLANE_SHAPE,
	_PRT_BOX_SHAPE,
	_PRT_CYLINDER_SHAPE,
	_PRT_CAPSULE_SHAPE,
	_PRT_CONE_SHAPE,
	_PRT_SPHERE_SHAPE,
	_PRT_MULTI_SPHERE_SHAPE,
	_PRT_CONVEX_HULL_SHAPE,
	_PRT_CONVEX_TRIANGLE_MESH_SHAPE,
	_PRT_HEIGHT_FIELD_TERRAIN_SHAPE,
	_PRT_COMPOUND_SHAPE,

	//!	Action
	_PRT_ACTION,
	_PRT_CHARACTER_CONTROLLER_ACTION,

	//!	Body
	_PRT_BODY,
	_PRT_SOFT_BODY,
	_PRT_RIGID_BODY,

	//!	Scene
	_PRT_SCENE,
};

//!	The physx data type
enum _PHYSX_DATA_TYPE
{
	_PHYSX_DATA_TYPE_UNKNOWN,
	_PHYSX_DATA_TYPE_FLOAT,
	_PHYSX_DATA_TYPE_DOUBLE,
	_PHYSX_DATA_TYPE_INTEGER,
	_PHYSX_DATA_TYPE_SHORT,
	_PHYSX_DATA_TYPE_UCHAR,
};

//!	The physx UP-AXIS type
enum _PHYSX_UP_AXIS_TYPE
{
	_PHYSX_AXIS_TYPE_UNKNOWN,
	_PHYSX_AXIS_TYPE_X,
	_PHYSX_AXIS_TYPE_Y,
	_PHYSX_AXIS_TYPE_Z,
};

//----------------------------------------------------------------------------
// The PHI resource types
//----------------------------------------------------------------------------

#define ENUM_PHI_RESOURCE_TYPES(EnumerationMacro)	\
	EnumerationMacro(StridingMesh, _PRT_STRIDING_MESH, _PRT_NONE)	\
	EnumerationMacro(SoftWorldInfo, _PRT_SOFT_WORLD_INFO, _PRT_NONE)	\
	EnumerationMacro(Shape, _PRT_SHAPE, _PRT_NONE)	\
	EnumerationMacro(ChainShape, _PRT_CHAIN_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(EdgeShape, _PRT_EDGE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(PolygonShape, _PRT_POLYGON_SHAPE, _PRT_SHAPE) \
	EnumerationMacro(CircleShape, _PRT_CIRCLE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(PlaneShape, _PRT_PLANE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(BoxShape, _PRT_BOX_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(CylinderShape, _PRT_CYLINDER_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(CapsuleShape, _PRT_CAPSULE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(ConeShape, _PRT_CONE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(SphereShape, _PRT_SPHERE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(MultiSphereShape, _PRT_MULTI_SPHERE_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(ConvexHullShape, _PRT_CONVEX_HULL_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(ConvexTriangleMeshShape, _PRT_CONVEX_TRIANGLE_MESH_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(HeightFieldTerrainShape, _PRT_HEIGHT_FIELD_TERRAIN_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(CompoundShape, _PRT_COMPOUND_SHAPE, _PRT_SHAPE)	\
	EnumerationMacro(Action, _PRT_ACTION, _PRT_NONE)	\
	EnumerationMacro(CharacterControllerAction, _PRT_CHARACTER_CONTROLLER_ACTION, _PRT_ACTION)	\
	EnumerationMacro(Body, _PRT_BODY, _PRT_NONE) \
	EnumerationMacro(SoftBody, _PRT_SOFT_BODY, _PRT_BODY) \
	EnumerationMacro(RigidBody, _PRT_RIGID_BODY, _PRT_BODY) \
	EnumerationMacro(Scene, _PRT_SCENE, _PRT_NONE)

template< _PHYSX_RESOURCE_TYPE ResourceType >
class TDynamicPHIResource : public TObject< IObject >
{
protected:
	TDynamicPHIResource( ) { }
	virtual ~TDynamicPHIResource( ) { }
};

#define DEFINE_DYNAMICPHI_REFERENCE_TYPE(Type, ResourceType, ParentResourceType)						\
template<> class TDynamicPHIResource< ResourceType > : public TDynamicPHIResource< ParentResourceType > \
{																										\
public:																									\
	virtual _PHYSX_RESOURCE_TYPE GetResourceType( ) const { return ResourceType; }						\
};																										\
typedef TDynamicPHIResource< ResourceType > Type##PHI;													\
typedef RefPtr< Type##PHI > Type##PHIRef;																\
typedef PassRefPtr< Type##PHI > Type##PHIPassRef;
ENUM_PHI_RESOURCE_TYPES(DEFINE_DYNAMICPHI_REFERENCE_TYPE)
#undef DEFINE_DYNAMICPHI_REFERENCE_TYPE

//----------------------------------------------------------------------------
// IDynamicPHI
//----------------------------------------------------------------------------

class IDynamicPHI : public IObject
{
public:
	// The PHI methods are defined as virtual functions.
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "Interface/Module/Physx/PHIMethods.h"
	#undef DEFINE_PHIMETHOD
};

//----------------------------------------------------------------------------
// NullDynamicPHI
//----------------------------------------------------------------------------

//! A null implementation of the dynamically bound PHI.
class NullDynamicPHI : public INTERFACE_OBJECT_IMPL( IDynamicPHI )
{
public:
	NullDynamicPHI( ) { }
	virtual ~NullDynamicPHI( ) { }

public:
	// The PHI methods are defined as virtual functions.
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames { NullImplementation }
	#include "Interface/Module/Physx/PHIMethods.h"
	#undef DEFINE_PHIMETHOD
};

}