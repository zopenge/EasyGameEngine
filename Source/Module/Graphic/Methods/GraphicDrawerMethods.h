//! @file     GraphicDrawerMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_DRAWER_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_DRAWER_METHOD
	#error "The DEFINE_DRAWER_METHOD marco must be defined"
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_DRAWER_METHOD(
	_void,
	DrawPoint,
	(const Vector2& position, const Color& color),
	(position, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawPoint,
	(const Vector3& position, const Color& color),
	(position, color),
	,
	;
	)
	
DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Vector2& start, const Vector2& end, const Color& color, _float width),
	(start, end, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width),
	(start, end, color_start, color_end, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Vector3& start, const Vector3& end, const Color& color, _float width),
	(start, end, color, width),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width),
	(start, end, color_start, color_end, width),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Line2D& line, const Color& color, _float width),
	(line, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawLine,
	(const Line3D& line, const Color& color, _float width),
	(line, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawLines,
	(const Line2DArray& lines, const Color& color, _float width),
	(lines, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawLines,
	(const Line3DArray& lines, const Color& color, _float width),
	(lines, color, width),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	FillTriangles,
	(const TriangleArray& triangles, const Color& color),
	(triangles, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawRectangle,
	(const RectF& rect, const Color& color, _float width),
	(rect, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	FillRectangle,
	(const RectF& rect, const Color& color),
	(rect, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawCircle,
	(const Vector2& center, _float radius, _dword segments, const Color& color),
	(center, radius, segments, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	FillCircle,
	(const Vector2& center, _float radius, _dword segments, const Color& color),
	(center, radius, segments, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawOrientedBox,
	(const OrientedBox2D& box, const Color& color, _float width),
	(box, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawAxisAlignedBox,
	(const AxisAlignedBox& box, const Color& color, _float width),
	(box, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawBox,
	(const Box& box, const Color& color, _float width),
	(box, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	FillBox,
	(const Box& box, const Color& color),
	(box, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawXYAxis,
	(const Vector2& origin, _float length, _float width),
	(origin, length, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawXYZAxis,
	(const Vector3& origin, _float length, _float width),
	(origin, length, width),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawSphere,
	(const Vector3& origin, _float radius, _float latitude, _float longitude),
	(origin, radius, latitude, longitude),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawFrustum,
	(const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width),
	(frustum, near_plane_color, far_plane_color, line_color, width),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawPolygon,
	(const Polygon2D& polygon, const Color& color, _float width),
	(polygon, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	FillPolygon,
	(const Polygon2D& polygon, const Color& color),
	(polygon, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawTriangles,
	(const Triangle2DArray& triangles, const Color& color, _float width),
	(triangles, color, width),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	FillTriangles,
	(const Triangle2DArray& triangles, const Color& color),
	(triangles, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawSprite,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, vertex_offsets, offset, transform, size, uv_info, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSpriteInMaskMode,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask_sprite, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info),
	(sprite, effect, transform, offset, size, uv_info, color, mask_sprite, mask_transform, mask_offset, mask_size, mask_uv_info),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSpriteInTriangleMode,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertexs, const Triangle2D& uvs, const Color& color),
	(sprite, effect, vertexs, uvs, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSpriteInTriangleStripeMode,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number),
	(sprite, effect, pos_list, uv_list, color_list, vertices_number),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSpriteInQuadMode,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Color* color_list, const Vector2* uv_list, _dword vertices_number),
	(sprite, effect, pos_list, color_list, uv_list, vertices_number),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSpriteIn3x3Mode,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& position, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, position, size, block_region, transform, uv_info, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawScreenAlignedBillboard,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, vertex_offsets, transform, position, uv_info, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawViewpointOrientedBillboard,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, vertex_offsets, transform, position, uv_info, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawAxialBillboard,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, vertex_offsets, transform, position, scaling, axis, uv_info, color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawRectBillboard,
	(IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color),
	(sprite, effect, vertex_offsets, transform, position, uv_info, color),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const RectF& region, IGraphicSurface* surface, IGraphicEffect* effect),
	(region, surface, effect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const RectF& region, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect),
	(region, uv1, uv2, surface, effect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const Vector2& position, IGraphicSurface* surface, IGraphicEffect* effect),
	(position, surface, effect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const Vector2& position, const Vector2& size, IGraphicSurface* surface, IGraphicEffect* effect),
	(position, size, surface, effect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const Vector2& position, const Vector2& size, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect),
	(position, size, uv1, uv2, surface, effect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawSurface,
	(const Matrix3& transform, const Vector2& offset, IGraphicSurface* surface, IGraphicEffect* effect),
	(transform, offset, surface, effect),
	,
	;
	)

DEFINE_DRAWER_METHOD(
	_void,
	DrawText,
	(const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color),
	(position, string, font, font_color),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawText,
	(const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform),
	(position, string, font, font_color, transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	DrawText,
	(const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform, const FontColorRHI& bk_font_color, const Vector2& bk_offset),
	(position, string, font, font_color, transform, bk_font_color, bk_offset),
	,
	;
	)

#ifndef CUSTOM_DRAW_MESH // We could implement it in other way, so use the macro to ignore it
DEFINE_DRAWER_METHOD(
	_void,
	DrawMeshGeometry,
	(IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info),
	(effect, geometry_info),
	,
	;
	)
#endif
#undef CUSTOM_DRAW_MESH

DEFINE_DRAWER_METHOD(
	_void,
	PushScissorRect,
	(const RectF& rect),
	(rect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	PopScissorRect,
	(),
	(),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	SetScissorRect,
	(const RectF& rect),
	(rect),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	const RectF&,
	GetScissorRect,
	() const,
	(),
	return,
	RectF::cNull;
	)

DEFINE_DRAWER_METHOD(
	_void,
	PushOverlayTransform,
	(const Matrix3& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	PopOverlayTransform,
	(),
	(),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	SetOverlayTransform,
	(const Matrix3& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	const Matrix3&,
	GetOverlayTransform,
	() const,
	(),
	return,
	Matrix3::cIdentity;
	)

DEFINE_DRAWER_METHOD(
	_void,
	PushUserOrthoTransform,
	(const Matrix4& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	PopUserOrthoTransform,
	(),
	(),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	SetUserOrthoTransform,
	(const Matrix4& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	const Matrix4&,
	GetUserOrthoTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)

DEFINE_DRAWER_METHOD(
	_void,
	PushOffsetTransform,
	(const Matrix4& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	PopOffsetTransform,
	(),
	(),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	_void,
	SetOffsetTransform,
	(const Matrix4& transform),
	(transform),
	,
	;
	)
DEFINE_DRAWER_METHOD(
	const Matrix4&,
	GetOffsetTransform,
	() const,
	(),
	return,
	Matrix4::cIdentity;
	)