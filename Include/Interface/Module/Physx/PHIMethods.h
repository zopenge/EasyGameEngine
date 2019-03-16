//! @file     PHIMethods.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_PHIMETHOD is used by the includer to modify the PHI method definitions.
#ifndef DEFINE_PHIMETHOD
	#error "The DEFINE_PHIMETHOD marco must be defined"
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) Type Name ParameterTypesAndNames
#endif

//----------------------------------------------------------------------------
// PHI resource management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	_ubool,
	Initialize,
	(),
	return _false;
	)

//----------------------------------------------------------------------------
// PHI scene management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	ScenePHIPassRef,
	CreateScene,
	(const Vector3& gravity),
	return _null;
	)
DEFINE_PHIMETHOD(
	_void,
	UpdateScene,
	(ScenePHI* scene, _dword elapse),
	;
	)
DEFINE_PHIMETHOD(
	_void,
	DrawScene,
	(ScenePHI* scene, IPhysxRenderer* renderer),
	;
	)

DEFINE_PHIMETHOD(
	_void,
	AddBody,
	(ScenePHI* scene, BodyPHI* body),
	;
	)
DEFINE_PHIMETHOD(
	_void,
	RemoveBody,
	(ScenePHI* scene, BodyPHI* body),
	;
	)

//----------------------------------------------------------------------------
// PHI soft body management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	SoftWorldInfoPHIPassRef,
	CreateSoftWorldInfo,
	(ScenePHI* scene),
	return _null;
	)

//----------------------------------------------------------------------------
// PHI soft body management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	SoftBodyPHIPassRef,
	CreateSoftPatch,
	(SoftWorldInfoPHI* world_info, const Vector3& corner00, const Vector3& corner10, const Vector3& corner01, const Vector3& corner11, _dword resx, _dword resy, _dword fixeds, _ubool gendiags),
	return _null;
	)

//----------------------------------------------------------------------------
// PHI rigid body management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	RigidBodyPHIPassRef,
	CreateRigidBody,
	(_float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, ShapePHI* shape),
	return _null;
	)

DEFINE_PHIMETHOD(
	Vector3,
	GetRigidBodyCenter,
	(const RigidBodyPHI* body),
	return Vector3::cOrigin;
	)
DEFINE_PHIMETHOD(
	Matrix4,
	GetRigidBodyTransform,
	(const RigidBodyPHI* body),
	return Matrix4::cIdentity;
	)
DEFINE_PHIMETHOD(
	_void,
	SetRigidBodyRestitution,
	(RigidBodyPHI* body, _float restitution),
	;
	)
DEFINE_PHIMETHOD(
	_float,
	GetRigidBodyRestitution,
	(const RigidBodyPHI* body),
	return 0.0f;
	)
DEFINE_PHIMETHOD(
	_void,
	SetRigidBodyDamping,
	(RigidBodyPHI* body, _float lin_damping, _float ang_damping),
	;
	)
DEFINE_PHIMETHOD(
	_void,
	SetRigidBodyLinearFactor,
	(RigidBodyPHI* body, const Vector3& factor),
	;
	)
DEFINE_PHIMETHOD(
	Vector3,
	GetRigidBodyLinearFactor,
	(const RigidBodyPHI* body),
	return Vector3::cOrigin;
	)
DEFINE_PHIMETHOD(
	_void,
	SetRigidBodyAngularFactor,
	(RigidBodyPHI* body, const Vector3& factor),
	;
	)
DEFINE_PHIMETHOD(
	Vector3,
	GetRigidBodyAngularFactor,
	(const RigidBodyPHI* body),
	return Vector3::cOrigin;
	)
DEFINE_PHIMETHOD(
	_void,
	ApplyRigidBodyCentralImpulse,
	(RigidBodyPHI* body, const Vector3& force),
	;
	)
DEFINE_PHIMETHOD(
	_void,
	ApplyRigidBodyTorqueImpulse,
	(RigidBodyPHI* body, const Vector3& force),
	;
	)

//----------------------------------------------------------------------------
// PHI striding mesh management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	StridingMeshPHIPassRef,
	CreateStridingMesh,
	(const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number),
	return _null;
	)

//----------------------------------------------------------------------------
// PHI shape management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	ShapePHIPassRef,
	CloneShape,
	(const ShapePHI* shape),
	return _null;
	)

// Chain Shape
DEFINE_PHIMETHOD(
	ChainShapePHIPassRef,
	CreateChainShape,
	(),
	return _null;
	)

// Circle Shape
DEFINE_PHIMETHOD(
	CircleShapePHIPassRef,
	CreateCircleShape,
	(),
	return _null;
	)
DEFINE_PHIMETHOD(
	_void,
	SetCircleShapeRadius,
	(CircleShapePHI* shape, _float radius),
	return;
	)
DEFINE_PHIMETHOD(
	_float,
	GetCircleShapeRadius,
	(CircleShapePHI* shape),
	return 0.0f;
	)

// Edge Shape
DEFINE_PHIMETHOD(
	EdgeShapePHIPassRef,
	CreateEdgeShape,
	(),
	return _null;
	)

// Polygon Shape 
DEFINE_PHIMETHOD(
	PolygonShapePHIPassRef,
	CreatePolygonShape,
	(),
	return _null;
	)
DEFINE_PHIMETHOD(
	_void,
	SetPolygonShapeVertices,
	(PolygonShapePHI* shape, const Vector3* vertices, _dword number),
	;
	)
DEFINE_PHIMETHOD(
	_void,
	SetPolygonShapeAsBox,
	(PolygonShapePHI* shape, _float width, _float height),
	;
	)
DEFINE_PHIMETHOD(
	_dword,
	GetPolygonShapeVerticesNumber,
	(PolygonShapePHI* shape),
	return 0;
	)
DEFINE_PHIMETHOD(
	Vector3,
	GetPolygonShapeVertexByIndex,
	(PolygonShapePHI* shape, _dword index),
	return Vector3::cOrigin;
	)
		
// Plane Shape
DEFINE_PHIMETHOD(
	PlaneShapePHIPassRef,
	CreatePlaneShape,
	(const Vector3& normal, _float constant),
	return _null;
	)

// Box Shape
DEFINE_PHIMETHOD(
	BoxShapePHIPassRef,
	CreateBoxShape,
	(const Vector3& half_extents),
	return _null;
	)

// Cylinder Shape
DEFINE_PHIMETHOD(
	CylinderShapePHIPassRef,
	CreateCylinderShape,
	(const Vector3& half_extents),
	return _null;
	)

// Capsule Shape
DEFINE_PHIMETHOD(
	CapsuleShapePHIPassRef,
	CreateCapsuleShape,
	(_float radius, _float height),
	return _null;
	)

// Cone Shape
DEFINE_PHIMETHOD(
	ConeShapePHIPassRef,
	CreateConeShape,
	(_float radius, _float height),
	return _null;
	)

// Sphere Shape
DEFINE_PHIMETHOD(
	SphereShapePHIPassRef,
	CreateSphereShape,
	(_float radius),
	return _null;
	)

// MultiSphere Shape
DEFINE_PHIMETHOD(
	MultiSphereShapePHIPassRef,
	CreateMultiSphereShape,
	(const Vector3* pos_list, const _float* radius_list, _dword number),
	return _null;
	)

// ConvexHull Shape
DEFINE_PHIMETHOD(
	ConvexHullShapePHIPassRef,
	CreateConvexHullShape,
	(const Vector3* pos_list, _dword number),
	return _null;
	)

// ConvexTriangleMesh Shape
DEFINE_PHIMETHOD(
	ConvexTriangleMeshShapePHIPassRef,
	CreateConvexTriangleMeshShape,
	(const StridingMeshPHI* striding_mesh),
	return _null;
	)
DEFINE_PHIMETHOD(
	ConvexTriangleMeshShapePHIPassRef,
	CreateBvhTriangleMeshShape,
	(const StridingMeshPHI* striding_mesh),
	return _null;
	)

// HeightFieldTerrain Shape
DEFINE_PHIMETHOD(
	HeightFieldTerrainShapePHIPassRef,
	CreateHeightFieldTerrainShape,
	(_dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges),
	return _null;
	)

// Compound Shape
DEFINE_PHIMETHOD(
	CompoundShapePHIPassRef,
	CreateCompoundShape,
	(),
	return _null;
	)
DEFINE_PHIMETHOD(
	_dword,
	GetChildShapeNumberOfCompoundShape,
	(const CompoundShapePHI* compound_shape),
	return 0;
	)
DEFINE_PHIMETHOD(
	ShapePHIRef,
	GetChildShapeOfCompoundShape,
	(CompoundShapePHI* compound_shape, _dword index),
	return _null;
	)
DEFINE_PHIMETHOD(
	_ubool,
	AddChildShapeOfCompoundShape,
	(CompoundShapePHI* compound_shape, const Matrix4& transform, ShapePHI* shape),
	return _false;
	)
DEFINE_PHIMETHOD(
	_ubool,
	RemoveChildShapeOfCompoundShape,
	(CompoundShapePHI* compound_shape, ShapePHI* shape),
	return _false;
	)

//----------------------------------------------------------------------------
// PHI action management
//----------------------------------------------------------------------------

DEFINE_PHIMETHOD(
	ActionPHIPassRef,
	CreateKinematicCharacterController,
	(const Matrix4& transform, ShapePHI* shape, _float step_height, _PHYSX_UP_AXIS_TYPE up_axis),
	return _null;
	)
