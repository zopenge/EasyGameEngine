//! @file     GraphicGeometryProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicGeometryProcessor
//----------------------------------------------------------------------------

class GraphicGeometryProcessor
{
private:
	enum { _GEOMETRY_GROUP_NUMBER = 4 };

private:
	//!	The geometries array buffer to allocate
	typedef ElementArray< GraphicGeometry > GeometryElementArray;

private:
	//!	The VAO group
	GraphicVAOGroup			mVAOGroup;
	GraphicVAOGroup			mResidentVAOGroup;

	//! The mirrors group
	GraphicMirrorGroup		mMirrorGroup;

	//!	The temporary buffer allocator to save render info, like UBO etc.
	IBufferAllocatorRef		mBufferAllocator;

	//!	The element array
	GeometryElementArray	mGeometryElements;

	//!	The geometry chunks
	GraphicGeometryGroup	mGeometryGroups[ _GEOMETRY_GROUP_NUMBER ];

	//!	The geometry builder
	GraphicGeometryBuilder*	mGeometryBuilder;
	//!	The graphic scene
	IGraphicScene*			mScene;

private:
	//!	Clear caches.
	_void ClearCaches( );

	//!	Add mesh as mirror.
	_void AddMeshAsMirror( IGraphicSceneView* scene_view, _GRAPHIC_MIRROR_TYPE mirror_type, _dword mirror_size, GraphicGeometry& geometry );

public:
	GraphicGeometryProcessor( GraphicGeometryBuilder* geometry_builder, IGraphicScene* scene );
	~GraphicGeometryProcessor( );

public:
	//!	Initialize.
	_ubool Initialize( );

	//!	Render line geometry.
	_void RenderLineGeometry( const Vector2& start, const Vector2& end, const Color& color, _float width );
	_void RenderLineGeometry( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width );
	_void RenderLineGeometry( const Vector3& start, const Vector3& end, const Color& color, _float width );
	_void RenderLineGeometry( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width );
	//!	Render lines geometry.
	_void RenderLinesGeometry( const Line2DArray& lines, const Color& color, _float width );
	_void RenderLinesGeometry( const Line3DArray& lines, const Color& color, _float width );
	//!	Render rectangle geometry.
	_void RenderRectGeometry( const RectF& rect, const Color& color );
	_void RenderRectLineGeometry( const RectF& rect, const Color& color, _float width );
	//!	Render triangles geometry.
	_void RenderTrianglesGeometry( const TriangleArray& triangles, const Color& color );
	_void RenderTrianglesGeometry( const Triangle2DArray& triangles, const Color& color );
	_void RenderTrianglesLineGeometry( const Triangle2DArray& triangles, const Color& color, _float width );
	//!	Render circle geometry.
	_void RenderCircleGeometry( const Vector2& center, _float radius, _dword segments, const Color& color );
	_void RenderCircleLineGeometry( const Vector2& center, _float radius, _dword segments, const Color& color );
	//!	Render orient box geometry.
	_void RenderOrientedBoxGeometry( const OrientedBox2D& box, const Color& color, _float width );
	//!	Render box geometry.
	_void RenderBoxGeometry( const Box& box, const Color& color );
	_void RenderBoxLineGeometry( const Box& box, const Color& color, _float width );
	//!	Render axis geometry.
	_void RenderXYAxisGeometry( const Vector2& origin, _float length, _float width );
	_void RenderXYZAxisGeometry( const Vector3& origin, _float length, _float width );
	//!	Render sphere geometry.
	_void RenderSphereGeometry( const Vector3& origin, _float radius, _float latitude, _float longitude );
	//!	Render frustum geometry.
	_void RenderFrustumGeometry( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width );
	//!	Render polygon geometry.
	_void RenderPolygonLineGeometry( const Polygon2D& polygon, const Color& color, _float width );
	//!	Render sprite geometry.
	_void RenderSpriteGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color );
	_void RenderSpriteGeometryInMaskMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info );
	_void RenderSpriteGeometryInTriangleMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color );
	_void RenderSpriteGeometryInTriangleStripeMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number );
	_void RenderSpriteGeometryInQuadMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number );
	_void RenderSpriteGeometryIn3x3Mode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color );
	//!	Render billboard geometry.
	_void RenderScreenAlignedBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color );
	_void RenderViewpointOrientedBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color );
	_void RenderAxialBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color );
	_void RenderRectBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color );
	//!	Render character geometry.
	_void RenderCharacterGeometry( IGraphicEffect* effect, _dword prev_code, _dword code, FontRHI* font_resource, const FontCodeRHI* font_code, const Color& color, const Vector2& position, const Matrix3& transform );

	//!	Render geometry.
	_void RenderGeometry( IGraphicSceneView* scene_view, const GeometryBuildInfo& info );
	_void RenderGeometry( IGraphicSceneView* scene_view, const GeometryBuildInfo& info, const Vector3& center_pos );
	_void RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info );
	_void RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, const Vector3& center_pos );
	_void RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, _float distance );

	//!	Render mesh geometry.
	_void RenderMeshGeometry( IGraphicScene* scene, IGraphicSceneView* scene_view, IGraphicEffect* effect, IGraphicMesh* mesh );
	_void RenderMeshGeometry( IGraphicScene* scene, IGraphicSceneView* scene_view, IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info );

	//!	Add mesh.
	IGraphicMeshPassRef	AddMesh( IGeometryMeshChunk* mesh_chunk );

	//!	Flush buffers.
	_void FlushBuffers( );

	//!	Present to render buffers.
	_void PresentRenderBuffers( IGraphicCanvas* canvas, const GraphicClearBuffersInfo& clear_info );
	_void PresentRenderBuffers( IGraphicCanvas* canvas, const GraphicClearBuffersInfo& clear_info, const Viewport& viewport );
};

//----------------------------------------------------------------------------
// GraphicGeometryProcessor Implementation
//----------------------------------------------------------------------------

}