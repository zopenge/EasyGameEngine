//! @file     IGraphicDrawer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicDrawer
//----------------------------------------------------------------------------

class IGraphicDrawer : public IObject
{
public:
	//!	Draw point.
	//!	@param		position	The point position.
	//!	@param		color		The point color.
	//!	@return		none.
	virtual _void DrawPoint( const Vector2& position, const Color& color ) PURE;
	//!	Draw point.
	//!	@param		position	The point position.
	//!	@param		color		The point color.
	//!	@return		none.
	virtual _void DrawPoint( const Vector3& position, const Color& color ) PURE;

	//!	Draw line.
	//!	@param		start		The start position.
	//!	@param		end			The end position.
	//!	@param		color		The point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw line.
	//!	@param		start		The start position.
	//!	@param		end			The end position.
	//!	@param		color_start	The start point color.
	//!	@param		color_end	The end point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width = 1.0f ) PURE;
	//!	Draw line.
	//!	@param		start		The start position.
	//!	@param		end			The end position.
	//!	@param		color		The point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Vector3& start, const Vector3& end, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw line.
	//!	@param		start		The start position.
	//!	@param		end			The end position.
	//!	@param		color_start	The start point color.
	//!	@param		color_end	The end point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width = 1.0f ) PURE;
	//!	Draw line.
	//!	@param		line		The line.
	//!	@param		color		The point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Line2D& line, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw line.
	//!	@param		line		The line.
	//!	@param		color		The point color.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawLine( const Line3D& line, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw lines.
	//!	@param		lines		The lines.
	//!	@param		color		The point color.
	//!	@param		width		The lines width.
	//!	@return		none.
	virtual _void DrawLines( const Line2DArray& lines, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw lines.
	//!	@param		lines		The lines.
	//!	@param		color		The point color.
	//!	@param		width		The lines width.
	//!	@return		none.
	virtual _void DrawLines( const Line3DArray& lines, const Color& color, _float width = 1.0f ) PURE;

	//!	Fill 3D triangles.
	//!	@param		triangles	The triangles.
	//!	@param		color		The fill color.
	//!	@return		none.
	virtual _void FillTriangles( const TriangleArray& triangles, const Color& color ) PURE;

	//!	Draw rectangle.
	//!	@param		rect		The rect.
	//!	@param		width		The line width.
	//!	@param		color		The color.
	//!	@return		none.
	virtual _void DrawRectangle( const RectF& rect, const Color& color, _float width = 1.0f ) PURE;
	//!	Fill rectangle.
	//!	@param		rect		The rect.
	//!	@param		color		The color.
	//!	@return		none.
	virtual _void FillRectangle( const RectF& rect, const Color& color ) PURE;

	//!	Draw circle.
	//!	@param		center		The center position
	//!	@param		radius		The radius of circle.
	//!	@param		segments	The segments of circle.
	//!	@param		color		The edge color.
	//!	@return		none.
	virtual _void DrawCircle( const Vector2& center, _float radius, _dword segments, const Color& color ) PURE;
	//!	Draw solid circle.
	//!	@param		center		The center position
	//!	@param		radius		The radius of circle.
	//!	@param		segments	The segments of circle.
	//!	@param		color		The fill color.
	//!	@return		none.
	virtual _void FillCircle( const Vector2& center, _float radius, _dword segments, const Color& color ) PURE;

	//!	Draw axis-aligned box.
	//!	@param		box			The axis-aligned box.
	//!	@param		width		The line width.
	//!	@param		color		The edge color.
	//!	@return		none.
	virtual _void DrawOrientedBox( const OrientedBox2D& box, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw axis-aligned box.
	//!	@param		box			The axis-aligned box.
	//!	@param		width		The line width.
	//!	@param		color		The edge color.
	//!	@return		none.
	virtual _void DrawAxisAlignedBox( const AxisAlignedBox& box, const Color& color, _float width = 1.0f ) PURE;
	//!	Draw axis-aligned box.
	//!	@param		box			The axis-aligned box.
	//!	@param		width		The line width.
	//!	@param		color		The edge color.
	//!	@return		none.
	virtual _void DrawBox( const Box& box, const Color& color, _float width = 1.0f ) PURE;
	//!	Fill axis-aligned box.
	//!	@param		box			The axis-aligned box.
	//!	@param		color		The edge color.
	//!	@return		none.
	virtual _void FillBox( const Box& box, const Color& color ) PURE;

	//!	Draw XY axis.
	//!	@param		origin		The original position.
	//!	@param		length		The axis length.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawXYAxis( const Vector2& origin, _float length, _float width = 1.0f ) PURE;
	//!	Draw XYZ axis.
	//!	@param		origin		The original position.
	//!	@param		length		The axis length.
	//!	@param		width		The line width.
	//!	@return		none.
	virtual _void DrawXYZAxis( const Vector3& origin, _float length, _float width = 1.0f ) PURE;

	//!	Draw sphere.
	//!	@param		origin		The original position.
	//!	@param		radius		The sphere radius.
	//!	@param		latitude	The latitude factor(horz).
	//!	@param		longitude	The longitude factor (vert).
	//!	@return		none.
	virtual _void DrawSphere( const Vector3& origin, _float radius, _float latitude, _float longitude ) PURE;

	//!	Draw frustum.
	//!	@param		frustum				The frustum.
	//!	@param		near_plane_color	The near plane color.
	//!	@param		far_plane_color		The far plane color.
	//!	@param		line_color			The line from near to far color.
	//!	@param		width				The line width.
	//!	@return		none.
	virtual _void DrawFrustum( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width = 1.0f ) PURE;

	//!	Draw 2D polygon.
	//!	@param		polygon		The 2D polygon.
	//!	@param		color		The edge color.
	//!	@param		width		The edge width.
	//!	@return		none.
	virtual _void DrawPolygon( const Polygon2D& polygon, const Color& color, _float width = 1.0f ) PURE;
	//!	Fill 2D polygon.
	//!	@param		polygon		The 2D polygon.
	//!	@param		color		The fill color.
	//!	@return		none.
	virtual _void FillPolygon( const Polygon2D& polygon, const Color& color ) PURE;

	//!	Draw 2D triangles.
	//!	@param		triangles	The triangles.
	//!	@param		color		The fill color.
	//!	@param		width		The edge width.
	//!	@return		none.
	virtual _void DrawTriangles( const Triangle2DArray& triangles, const Color& color, _float width = 1.0f ) PURE;
	//!	Fill 2D triangles.
	//!	@param		triangles	The triangles.
	//!	@param		color		The fill color.
	//!	@return		none.
	virtual _void FillTriangles( const Triangle2DArray& triangles, const Color& color ) PURE;

	//!	Draw sprite.
	//! @param		sprite			The sprite.
	//! @param		effect			The effect.
	//! @param		vertex_offsets	The sprite vertex offsets.
	//! @param		offset			The sprite offset.
	//! @param		transform		The sprite transform.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	//!	@return		none.
	virtual _void DrawSprite( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color ) PURE;
	//!	Draw mask.
	//! @param		sprite			The sprite.
	//! @param		offset			The sprite offset.
	//! @param		size			The sprite size.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	virtual _void DrawSpriteInMaskMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask_sprite, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info ) PURE;
	//!	Draw sprite. triangle
	//!	@param		sprite			The sprite.
	//!	@param		effect			The effect.
	//! @param		vertexs			The triangle vertexs.
	//! @param		uvs				The triangle uvs.
	//! @param		color			The triangle color.
	//!	@return		none.
	virtual _void DrawSpriteInTriangleMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertexs, const Triangle2D& uvs, const Color& color ) PURE;
	//!	Draw sprite in triangle stripe mode.
	//!	@param		sprite			The sprite.
	//!	@param		effect			The effect.
	//!	@param		pos_list		The position list.
	//!	@param		uv_list			The UV list.
	//!	@param		color_list		The color list.
	//!	@param		number			The vertices number.
	//!	@return		none.
	virtual _void DrawSpriteInTriangleStripeMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number ) PURE;
	//!	Draw sprite in triangle quad mode.
	//!	@param		sprite			The sprite.
	//!	@param		effect			The effect.
	//!	@param		pos_list		The position list.
	//!	@param		uv_list			The UV list.
	//!	@param		color_list		The color list.
	//!	@param		number			The vertices number.
	//!	@return		none.
	virtual _void DrawSpriteInQuadMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Color* color_list, const Vector2* uv_list, _dword vertices_number ) PURE;
	//!	Draw sprite 3x3.
	//! @param		sprite			The sprite.
	//! @param		effect			The effect.
	//! @param		offset			The sprite offset.
	//!	@param		size			The sprite size.
	//! @param		block_region	The block region.
	//! @param		transform		The sprite transform.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The sprite color.
	//!	@return		none.
	virtual _void DrawSpriteIn3x3Mode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color ) PURE;

	//!	Draw screen billboard.
	//! @param		sprite			The billboard texture.
	//! @param		effect			The effect.
	//! @param		vertex_offsets	The offset per vertex.
	//! @param		transform		The billboard transform.
	//! @param		position		The billboard position.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	//!	@return		none.
	virtual _void DrawScreenAlignedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color ) PURE;
	//!	Draw viewpoint billboard.
	//! @param		sprite			The billboard texture.
	//! @param		effect			The effect.
	//! @param		vertex_offsets	The offset per vertex.
	//! @param		transform		The billboard transform.
	//! @param		position		The billboard position.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	//!	@return		none.
	virtual _void DrawViewpointOrientedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color ) PURE;
	//!	Draw axial billboard.
	//! @param		sprite			The billboard texture.
	//! @param		effect			The effect.
	//! @param		vertex_offsets	The offset per vertex.
	//! @param		transform		The billboard transform.
	//! @param		position		The billboard position.
	//! @param		scaling			The billboard scaling.
	//! @param		axis			The billboard axis.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	//!	@return		none.
	virtual _void DrawAxialBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color ) PURE;
	//!	Draw sprite rectangle
	//! @param		sprite			The billboard texture.
	//! @param		effect			The effect.
	//! @param		vertex_offsets	The offset per vertex.
	//! @param		transform		The billboard transform.
	//! @param		position		The billboard position.
	//! @param		uv_info			The texture UV coordinate.
	//! @param		color			The color.
	//!	@return		none.
	virtual _void DrawRectBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color ) PURE;

	//!	Draw surface.
	//!	@param		region		The draw region, the surface will use (0, 0) and region's size as position and size.
	//!	@param		surface		The surface.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const RectF& region, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;
	//!	Draw surface.
	//!	@param		region		The draw region, the surface will use (0, 0) and region's size as position and size.
	//!	@param		surface		The surface.
	//!	@param		uv1			The surface UV1 coordinates.
	//!	@param		uv2			The surface UV2 coordinates.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const RectF& region, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;
	//!	Draw surface.
	//!	@param		position	The left-top position.
	//!	@param		surface		The surface.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const Vector2& position, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;
	//!	Draw surface.
	//!	@param		position	The left-top position.
	//!	@param		size		The surface size.
	//!	@param		surface		The surface.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const Vector2& position, const Vector2& size, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;
	//!	Draw surface.
	//!	@param		position	The left-top position.
	//!	@param		size		The surface size.
	//!	@param		uv1			The surface UV1 coordinates.
	//!	@param		uv2			The surface UV2 coordinates.
	//!	@param		surface		The surface.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const Vector2& position, const Vector2& size, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;
	//!	Draw surface.
	//!	@param		transform	The transform.
	//!	@param		offset		The offset of xy coordinate.
	//!	@param		surface		The surface.
	//!	@param		effect		The effect.
	//!	@return		none.
	virtual _void DrawSurface( const Matrix3& transform, const Vector2& offset, IGraphicSurface* surface, IGraphicEffect* effect ) PURE;

	//!	Draw text.
	//!	@param		position	The left-top position of rendering string.
	//!	@param		string		The string what you want to render.
	//!	@param		font		The font interface.
	//!	@param		color		The font color.
	//!	@param		transform	The transform.
	//!	@return		none.
	virtual _void DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color ) PURE;
	//!	Draw text.
	//!	@param		position	The left-top position of rendering string.
	//!	@param		string		The string what you want to render.
	//!	@param		font		The font interface.
	//!	@param		color		The font color.
	//!	@param		transform	The transform.
	//!	@return		none.
	virtual _void DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform ) PURE;
	//!	Draw text with background text.
	//!	@param		position		The left-top position of rendering string.
	//!	@param		string			The string what you want to render.
	//!	@param		font			The font interface.
	//!	@param		font_color		The font color.
	//!	@param		transform		The transform.
	//!	@param		bk_font_color	The background font color.
	//!	@param		bk_offset		The background font offset.
	//!	@return		none.
	virtual _void DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform, const FontColorRHI& bk_font_color, const Vector2& bk_offset ) PURE;

	//!	Draw mesh geometry.
	//!	@param		effect			The effect.
	//!	@param		geometry_info	The mesh geometry info.
	//! @return		none.
	virtual _void DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info ) PURE;

	//!	Push the scissor/clip rect.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void PushScissorRect( const RectF& rect ) PURE;
	//!	Pop the scissor/clip rect.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopScissorRect( ) PURE;
	//!	Set the scissor/clip rect.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void SetScissorRect( const RectF& rect ) PURE;
	//!	Get the scissor/clip rect info.
	//!	@param		rect			The scissor rect.
	//!	@return		none.
	virtual const RectF& GetScissorRect( ) const PURE;

	//!	Push the overlay transform.
	//!	@param		transform	The overlay transform.
	//!	@return		none.
	virtual _void PushOverlayTransform( const Matrix3& transform ) PURE;
	//!	Pop the overlay transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopOverlayTransform( ) PURE;
	//!	Set the overlay transform.
	//!	@param		transform	The overlay transform.
	//!	@return		none.
	virtual _void SetOverlayTransform( const Matrix3& transform ) PURE;
	//!	Get the overlay transform.
	//!	@param		none.
	//!	@return		The overlay transform.
	virtual const Matrix3& GetOverlayTransform( ) const PURE;

	//!	Push the overlay world transform.
	//!	@param		transform	The overlay world transform.
	//!	@return		none.
	virtual _void PushUserOrthoTransform( const Matrix4& transform ) PURE;
	//!	Pop the overlay world transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopUserOrthoTransform( ) PURE;
	//!	Set the overlay world transform.
	//!	@param		transform	The overlay world transform.
	//!	@return		none.
	virtual _void SetUserOrthoTransform( const Matrix4& transform ) PURE;
	//!	Get the overlay world transform.
	//!	@param		none.
	//!	@return		The overlay world transform.
	virtual const Matrix4& GetUserOrthoTransform( ) const PURE;

	//!	Push the offset transform.
	//!	@param		transform	The offset transform.
	//!	@return		none.
	virtual _void PushOffsetTransform( const Matrix4& transform ) PURE;
	//!	Pop the offset transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopOffsetTransform( ) PURE;
	//!	Set the offset transform.
	//!	@param		transform	The offset transform.
	//!	@return		none.
	virtual _void SetOffsetTransform( const Matrix4& transform ) PURE;
	//!	Get the offset transform.
	//!	@param		none.
	//!	@return		The offset transform.
	virtual const Matrix4& GetOffsetTransform( ) const PURE; 
};

}