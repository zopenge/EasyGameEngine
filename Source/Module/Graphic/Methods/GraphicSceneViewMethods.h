//! @file     GraphicSceneViewMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_SCENE_VIEW_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_SCENE_VIEW_METHOD
	#error "The DEFINE_SCENE_VIEW_METHOD marco must be defined"
	#define DEFINE_SCENE_VIEW_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetTransformChangedFunc,
	(OnTransformChanged funcpointer, const QwordParameters2& parameters),
	(funcpointer, parameters),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetCamera,
	(const Camera& camera),
	(camera),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	const Camera&,
	GetCamera,
	() const,
	(),
	return,
	Camera::cNull;
	)
DEFINE_SCENE_VIEW_METHOD(
	_float,
	GetDistanceFromCamera,
	(const Vector3& pos) const,
	(pos),
	return,
	0.0f;
	)

DEFINE_SCENE_VIEW_METHOD(
	const Frustum&,
	GetViewFrustum,
	() const,
	(),
	return,
	Frustum::cIdentity;
	)
DEFINE_SCENE_VIEW_METHOD(
	const Matrix4&,
	GetViewTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)

DEFINE_SCENE_VIEW_METHOD(
	_float,
	GetFovY,
	() const,
	(),
	return,
	0.0f;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetFovY,
	(_float fovy),
	(fovy),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_float,
	GetAspect,
	() const,
	(),
	return,
	0.0f;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetAspect,
	(_float aspect),
	(aspect),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_float,
	GetZNear,
	() const,
	(),
	return,
	0.0f;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetZNear,
	(_float znear),
	(znear),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_float,
	GetZFar,
	() const,
	(),
	return,
	0.0f;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetZFar,
	(_float zfar),
	(zfar),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetProjectionTransform,
	(_float aspect, _float znear, _float zfar),
	(aspect, znear, zfar),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	const Matrix4&,
	GetProjectionTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)

DEFINE_SCENE_VIEW_METHOD(
	const Matrix4&,
	GetViewProjectionTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)

DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetOrthoMode,
	(_ubool ortho),
	(ortho),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	_ubool,
	GetOrthoMode,
	() const,
	(),
	return,
	_false;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetOrthoViewHeight,
	(_float height),
	(height),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetOrthoScaleFactor,
	(_float factor),
	(factor),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	_void,
	PushCameraAndProjectionTransform,
	(const Camera& camera, _float aspect, _float znear, _float zfar),
	(camera, aspect, znear, zfar),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	PopCameraAndProjectionTransform,
	(),
	(),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetCameraAndProjectionTransform,
	(const Camera& camera, _float aspect, _float znear, _float zfar),
	(camera, aspect, znear, zfar),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetViewAndProjectionTransform,
	(const FirstPersonCamera& camera, _float znear, _float zfar),
	(camera, znear, zfar),
	,
	;
	)

DEFINE_SCENE_VIEW_METHOD(
	Vector2,
	Convert3DTo2D,
	(const PointU& size, const Vector3& point, _float* zsort),
	(size, point, zsort),
	return,
	Vector2::cOrigin;
	)
DEFINE_SCENE_VIEW_METHOD(
	Ray,
	GetPickRay,
	(const PointU& size, _int x, _int y),
	(size, x, y),
	return,
	Ray::cNull;
	)

DEFINE_SCENE_VIEW_METHOD(
	_void,
	SetObserverSceneView,
	(IGraphicSceneView* scene_view),
	(scene_view),
	,
	;
	)
DEFINE_SCENE_VIEW_METHOD(
	IGraphicSceneView*,
	GetObserverSceneView,
	() const,
	(),
	return,
	_null;
	)
