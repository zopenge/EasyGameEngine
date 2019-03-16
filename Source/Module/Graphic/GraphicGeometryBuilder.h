//! @file     GraphicGeometryBuilder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicGeometryBuilder
//----------------------------------------------------------------------------

class GraphicGeometryBuilder
{
private:
	typedef ElementArray< Viewport >	ViewportElementArray;

public:
	//!	The last transform slot
	enum _TRANSFORM_SLOT
	{
		_TRANSFORM_ORTHO,	//£¡ Ortho
		_TRANSFORM_OVERLAY,	//£¡ Overlay
		_TRANSFORM_VIEW,	//£¡ World * View
		_TRANSFORM_VP,		//£¡ View * Projection
		_TRANSFORM_MAXNUMBER,
	};

private:
	//!	The last client size
	PointU					mLastClientSize;
	//!	The last right-hand transform slot (for OpenGL)
	Matrix4					mLastRHTransformSlots[ _TRANSFORM_MAXNUMBER ];

	//!	The element caches
	ViewportElementArray	mViewports;

	//!	The buffer allocator
	IBufferAllocatorRef		mBufferAllocator;

	//!	The useful effect
	IGraphicEffectRef		mVertexColorEffect;

	//!	(SAB, ScreenAlignedBillboard cache )
	Vector3					mSABRightAxis;
	Vector3					mSABUpAxis;
	Matrix3					mSABMatrix;

	//!	(VOB, ViewpointOrientedBillboard cache )
	Vector3					mVOBLookAxis;
	Vector3					mVOBUpAxis;
	Matrix3					mVOBMatrix;

	//!	(AB, AxialBillboard cache )
	Vector3					mABLookAxis;
	Vector3					mABUpAxis;
	Matrix3					mABMatrix;

	//!	The graphic scene
	IGraphicScene*			mScene;

private:
	//!	Allocate vertex buffer.
	_void AllocVB( GeometryBuildInfo& info, _dword vb_number );

	//!	Build the vertex of overlay.
	_void BuildOverlayVertex( Vector2& lt, Vector2& rt, Vector2& rb, Vector2& lb, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform );

	//!	Set the overlay.
	_void SetOverlay( GraphicVertexInfo* vertex_buffer, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color );
	//!	Set the overlay with texture info.
	_void SetOverlay( GraphicVertexInfo* vertex_buffer, IGraphicTexture2D* sprite, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color );
	//! Set the triangle overlay with texture info.
	_void SetOverlay( GraphicVertexInfo* vertex_buffer, IGraphicTexture2D* sprite, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color );
	//!	Set the primitive with texture info.
	_void SetPrimitive( GraphicVertexInfo* vertex_buffer, Vector3& lt, Vector3& rt, Vector3& lb, Vector3& rb, const Vector2* vertex_offsets, const Matrix3& sprite_transform, const Matrix3& viewmatrix, const Vector3& position, const Vector3* scaling, const GraphicUVInfo& uv_info, const Color& color );

	_void SetRectangle( GraphicVertexInfo* vertex_buffer, const Vector2& position, const Vector2& lt, const Vector2& rt, const Vector2& lb, const Vector2& rb, const Color& color, const GraphicUVInfo& uv_info, const Matrix3& transform );

public:
	GraphicGeometryBuilder( IGraphicScene* scene );
	~GraphicGeometryBuilder( );

public:
	//!	Initialize.
	_ubool Initialize( );

	//!	Clear caches.
	_void ClearCaches( );

	//!	Get the last viewport.
	const Viewport* GetLastViewport( ) const;
	//!	Get the last transform.
	const Matrix4& GetLastTransformRH( _TRANSFORM_SLOT slot ) const;

	//!	Update the viewport.
	_void UpdateViewport( const Viewport& viewport );
	//!	Update the transform.
	_void UpdateTransform( const Matrix4* overlay, const Matrix4* ortho_user, const Matrix4* offset, _ubool force_update );

	//!	Build geometry.
	_void BuildGeometry( _TRANSFORM_SLOT slot, GeometryBuildInfo& info );

	//!	Build line geometry.
	_void BuildLineGeometry( const Vector2& start, const Vector2& end, const Color& color, _float width, GeometryBuildInfo& info );
	_void BuildLineGeometry( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width, GeometryBuildInfo& info );
	_void BuildLineGeometry( const Vector3& start, const Vector3& end, const Color& color, _float width, GeometryBuildInfo& info );
	_void BuildLineGeometry( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width, GeometryBuildInfo& info );
	//!	Build lines geometry.
	_void BuildLinesGeometry( const Line2DArray& lines, const Color& color, _float width, GeometryBuildInfo& info );
	_void BuildLinesGeometry( const Line3DArray& lines, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build rectangle geometry.
	_void BuildRectGeometry( const RectF& rect, const Color& color, GeometryBuildInfo& info );
	_void BuildRectGeometry( const RectF& rect, const Matrix3& transform, const Color& color, GeometryBuildInfo& info );
	_void BuildRectLineGeometry( const RectF& rect, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build triangles geometry.
	_void BuildTrianglesGeometry( const TriangleArray& triangles, const Color& color, GeometryBuildInfo& info );
	_void BuildTrianglesGeometry( const Triangle2DArray& triangles, const Color& color, GeometryBuildInfo& info );
	_void BuildTrianglesLineGeometry( const Triangle2DArray& triangles, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build circle geometry.
	_void BuildCircleGeometry( const Vector2& center, _float radius, _dword segments, const Color& color, GeometryBuildInfo& info );
	_void BuildCircleLineGeometry( const Vector2& center, _float radius, _dword segments, const Color& color, GeometryBuildInfo& info );
	//!	Build orient box geometry.
	_void BuildOrientedBoxGeometry( const OrientedBox2D& box, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build box geometry.
	_void BuildBoxGeometry( const Box& box, const Color& color, GeometryBuildInfo& info );
	_void BuildBoxLineGeometry( const Box& box, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build axis geometry.
	_void BuildXYAxisGeometry( const Vector2& origin, _float length, _float width, GeometryBuildInfo& info );
	_void BuildXYZAxisGeometry( const Vector3& origin, _float length, _float width, GeometryBuildInfo& info );
	//!	Build sphere geometry.
	_void BuildSphereGeometry( const Vector3& origin, _float radius, _float latitude, _float longitude, GeometryBuildInfo& info );
	//!	Build frustum geometry.
	_void BuildFrustumGeometry( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width, GeometryBuildInfo& info );
	//!	Build polygon geometry.
	_void BuildPolygonLineGeometry( const Polygon2D& polygon, const Color& color, _float width, GeometryBuildInfo& info );
	//!	Build sprite geometry.
	_void BuildSpriteGeometry( IGraphicTexture2D* sprite, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	_void BuildSpriteGeometryInMaskMode( IGraphicTexture2D* sprite, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info, GeometryBuildInfo& info );
	_void BuildSpriteGeometryInTriangleMode( IGraphicTexture2D* sprite, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color, GeometryBuildInfo& info );
	_void BuildSpriteGeometryInTriangleStripeMode( IGraphicTexture2D* sprite, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number, GeometryBuildInfo& info );
	_void BuildSpriteGeometryInQuadMode( IGraphicTexture2D* sprite, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number, GeometryBuildInfo& info );
	_void BuildSpriteGeometryIn3x3Mode( IGraphicTexture2D* sprite, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	//!	Build billboard geometry.
	_void BuildScreenAlignedBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	_void BuildViewpointOrientedBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	_void BuildAxialBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	_void BuildRectBillboardGeometry( IGraphicTexture2D* sprite, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info );
	//!	Build character geometry.
	_void BuildCharacterGeometry( _dword prev_code, _dword code, FontRHI* font_resource, const FontCodeRHI* font_code, const Color& color, const Vector2& position, const Matrix3& transform, GeometryBuildInfo& info );
};

//----------------------------------------------------------------------------
// GraphicGeometryBuilder Implementation
//----------------------------------------------------------------------------

}