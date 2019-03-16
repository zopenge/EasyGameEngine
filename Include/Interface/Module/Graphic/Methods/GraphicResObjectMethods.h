//! @file     GraphicResObjectMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_GRAPHIC_RESOBJ_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_GRAPHIC_RESOBJ_METHOD
	#error "The DEFINE_GRAPHIC_RESOBJ_METHOD marco must be defined"
	#define DEFINE_GRAPHIC_RESOBJ_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetEffect,
	(IGraphicEffect* effect),
	(effect),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	IGraphicEffect*,
	GetEffect,
	() const,
	(),
	return,
	_null;
	)

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetColor,
	(const Color& color),
	(color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	const Color&,
	GetColor,
	() const,
	(),
	return,
	Color::cWhite;
	)

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetPosition2D,
	(const Vector2& position),
	(position),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	Vector2,
	GetPosition2D,
	() const,
	(),
	return,
	Vector2::cOrigin;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetScale2D,
	(const Vector2& position),
	(position),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	Vector2,
	GetScale2D,
	() const,
	(),
	return,
	Vector2::cOrigin;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetTransform2D,
	(const Transform2D& transform),
	(transform),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	Transform2D,
	GetTransform2D,
	() const,
	(),
	return,
	Transform2D::cZero;
	)

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetTransform3D,
	(const Transform3D& transform),
	(transform),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	Transform3D,
	GetTransform3D,
	() const,
	(),
	return,
	Transform3D::cZero;
	)

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	SetAABox,
	(const AxisAlignedBox& box),
	(box),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	OrientedBox2D,
	GetOBBox,
	() const,
	(),
	return,
	OrientedBox2D::cNull;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	OrientedBox2D,
	GetOriginalOBBox,
	() const,
	(),
	return,
	OrientedBox2D::cNull;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	AxisAlignedBox,
	GetAABox,
	() const,
	(),
	return,
	AxisAlignedBox::cNullBox;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	AxisAlignedBox,
	GetOriginAABox,
	() const,
	(),
	return,
	AxisAlignedBox::cNullBox;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	Box,
	GetBox,
	() const,
	(),
	return,
	Box::cNullBox;
	)

DEFINE_GRAPHIC_RESOBJ_METHOD(
	_ubool,
	TestPoint,
	(const Matrix3& camera_transform, const Vector2& position) const,
	(camera_transform, position),
	return,
	_false;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_ubool,
	TestPoint,
	(const Vector2& position) const,
	(position),
	return,
	_false;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_ubool,
	TestRegion,
	(const RectF& region) const,
	(region),
	return,
	_false;
	)

#ifndef CUSTOM_RENDER_OVERLAY // We could implement it in other way, so use the macro to ignore it
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderOverlay,
	(IGraphicScene* scene, const Matrix3& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)
#endif
#undef CUSTOM_RENDER_OVERLAY
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderScreenAlignedBillboard,
	(IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color),
	(scene, matrix, position, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderViewpointOrientedBillboard,
	(IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color),
	(scene, matrix, position, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderAxialBillboard,
	(IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Vector3& axis, const Color& color, const Vector3* result_scaling),
	(scene, matrix, position, axis, color, result_scaling),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderRectBillboard,
	(IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color),
	(scene, matrix, position, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderWireFrame,
	(IGraphicScene* scene, const Matrix4& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderNormal,
	(IGraphicScene* scene, const Matrix4& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderAxisAlignedBox,
	(IGraphicScene* scene, const Matrix4& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderStroke,
	(IGraphicScene* scene, const Matrix4& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderZBuffer,
	(IGraphicScene* scene, const Matrix4& transform),
	(scene, transform),
	,
	;
	)
DEFINE_GRAPHIC_RESOBJ_METHOD(
	_void,
	RenderGeometry,
	(IGraphicScene* scene, const Matrix4& transform, const Color& color),
	(scene, transform, color),
	,
	;
	)