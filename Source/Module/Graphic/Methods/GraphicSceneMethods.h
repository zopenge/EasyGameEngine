//! @file     GraphicSceneMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_SCENE_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_SCENE_METHOD
	#error "The DEFINE_SCENE_METHOD marco must be defined"
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_SCENE_METHOD(
	_void,
	SetViewport,
	(const Viewport& viewport),
	(viewport),
	,
	;
	)
DEFINE_SCENE_METHOD(
	const Viewport&,
	GetViewport,
	() const,
	(),
	return,
	Viewport::cNull;
	)

DEFINE_SCENE_METHOD(
	_void,
	SetClientSize,
	(const PointU& size),
	(size),
	,
	;
	)
DEFINE_SCENE_METHOD(
	const PointU&,
	GetClientSize,
	() const,
	(),
	return,
	PointU::cZeroPoint;
	)
DEFINE_SCENE_METHOD(
	const Ratio&,
	GetClientRatio,
	() const,
	(),
	return,
	Ratio::cNull;
	)

DEFINE_SCENE_METHOD(
	_void,
	FlushBuffers,
	(),
	(),
	,
	;
	)

DEFINE_SCENE_METHOD(
	_void,
	ClearCaches,
	(),
	(),
	,
	;
	)

DEFINE_SCENE_METHOD(
	const Matrix4&,
	GetViewTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)
DEFINE_SCENE_METHOD(
	const Matrix4&,
	GetVPTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)

DEFINE_SCENE_METHOD(
	_void,
	ClearRenderBuffers,
	(_ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil),
	(clearcolor, color, cleardepth, depth, clearstencil, stencil),
	,
	;
	)
#ifndef CUSTOM_PRESENT_RENDER_BUFFERS // We could implement it in other way, so use the macro to ignore it
DEFINE_SCENE_METHOD(
	_void,
	PresentRenderBuffers,
	(),
	(),
	,
	;
	)
#endif
#undef CUSTOM_PRESENT_RENDER_BUFFERS
DEFINE_SCENE_METHOD(
	_void,
	PresentRenderBuffers,
	(IGraphicCanvas* canvas),
	(canvas),
	,
	;
	)

DEFINE_SCENE_METHOD(
	_void,
	SetSceneView,
	(IGraphicSceneView* view),
	(view),
	,
	;
	)
DEFINE_SCENE_METHOD(
	IGraphicSceneView*,
	GetSceneView,
	() const,
	(),
	return,
	_null;
	)

DEFINE_SCENE_METHOD(
	const Viewport*,
	GetLastViewport,
	(),
	(),
	return,
	_null;
	)

DEFINE_SCENE_METHOD(
	_ubool,
	PickMeshes,
	(const Ray& ray, _ubool bound_box_only, IGraphicMeshRefArray& meshes),
	(ray, bound_box_only, meshes),
	return,
	_false;
	)
DEFINE_SCENE_METHOD(
	_ubool,
	PickMeshes,
	(const AxisAlignedBox& box, _ubool bound_box_only, IGraphicMeshRefArray& meshes),
	(box, bound_box_only, meshes),
	return,
	_false;
	)

DEFINE_SCENE_METHOD(
	IGraphicMeshPassRef,
	AddMesh,
	(IGeometryMeshChunk* mesh_chunk),
	(mesh_chunk),
	return,
	_null;
	)

DEFINE_SCENE_METHOD(
	Vector2,
	Convert3DTo2D,
	(const Vector3& point, _float* zsort),
	(point, zsort),
	return,
	Vector2::cOrigin;
	)
DEFINE_SCENE_METHOD(
	Vector2,
	Convert3DTo2D,
	(const PointU& size, const Vector3& point, _float* zsort),
	(size, point, zsort),
	return,
	Vector2::cOrigin;
	)

DEFINE_SCENE_METHOD(
	Ray,
	GetPickRay,
	(_int x, _int y),
	(x, y),
	return,
	Ray::cNull;
	)
DEFINE_SCENE_METHOD(
	Ray,
	GetPickRay,
	(const PointU& size, _int x, _int y),
	(size, x, y),
	return,
	Ray::cNull;
	)