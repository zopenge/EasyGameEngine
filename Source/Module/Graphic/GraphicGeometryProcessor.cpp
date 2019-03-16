//! @file     GraphicGeometryProcessor.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicGeometryProcessor Implementation
//----------------------------------------------------------------------------

GraphicGeometryProcessor::GraphicGeometryProcessor( GraphicGeometryBuilder* geometry_builder, IGraphicScene* scene )
{
	mGeometryBuilder	= geometry_builder;
	mScene				= scene;

	EGE_STATIC_ASSERT( sizeof( GraphicGeometryInfo ) % sizeof( _dword ) == 0, "The renderable geometry structure must align to 32 bits" );
}

GraphicGeometryProcessor::~GraphicGeometryProcessor( )
{
}

_void GraphicGeometryProcessor::ClearCaches( )
{
	// Reset temporary buffer allocator
	mBufferAllocator->Reset( );

	// Reset elements
	mGeometryElements.Reset( );

	// Clear geometry builder caches
	mGeometryBuilder->ClearCaches( );
}

_void GraphicGeometryProcessor::AddMeshAsMirror( IGraphicSceneView* scene_view, _GRAPHIC_MIRROR_TYPE mirror_type, _dword mirror_size, GraphicGeometry& geometry )
{
	switch ( mirror_type )
	{
		case _GRAPHIC_MIRROR_FLAT:
		{
			mMirrorGroup.AddFlatMirrorFromGeometry( scene_view, geometry.GetGeometryInfo( ).mMirrorReflectionPlane, mirror_size, geometry );
		}
		break;

		case _GRAPHIC_MIRROR_SPHERE:
		{
			mMirrorGroup.AddSphereMirrorFromGeometry( mirror_size, geometry );
		}
		break;

		default:
			break;
	}
}

_ubool GraphicGeometryProcessor::Initialize( )
{
	mBufferAllocator = GetInterfaceFactory( )->CreateBufferAllocator( 64 KB );
	if ( mBufferAllocator.IsNull( ) )
		return _false;

	for ( _dword i = 0; i < _GEOMETRY_GROUP_NUMBER; i ++ )
	{
		if ( mGeometryGroups[i].Initialize( (_GRAPHIC_RENDER_QUEUE)i ) == _false )
			return _false;
	}

	return _true;
}

_void GraphicGeometryProcessor::RenderLineGeometry( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLineGeometry( start, end, color, width, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderLineGeometry( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLineGeometry( start, end, color_start, color_end, width, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderLineGeometry( const Vector3& start, const Vector3& end, const Color& color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLineGeometry( start, end, color, width, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderLineGeometry( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLineGeometry( start, end, color_start, color_end, width, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderLinesGeometry( const Line2DArray& lines, const Color& color, _float width )
{
	if ( lines.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLinesGeometry( lines, color, width, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderLinesGeometry( const Line3DArray& lines, const Color& color, _float width )
{
	if ( lines.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildLinesGeometry( lines, color, width, info );

	// Draw lines
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderRectGeometry( const RectF& rect, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildRectGeometry( rect, color, info );

	// Fill rectangle
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderRectLineGeometry( const RectF& rect, const Color& color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildRectLineGeometry( rect, color, width, info );

	// Draw rectangle
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderTrianglesGeometry( const TriangleArray& triangles, const Color& color )
{
	if ( triangles.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildTrianglesGeometry( triangles, color, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderTrianglesGeometry( const Triangle2DArray& triangles, const Color& color )
{
	if ( triangles.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildTrianglesGeometry( triangles, color, info );

	// Draw line
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderTrianglesLineGeometry( const Triangle2DArray& triangles, const Color& color, _float width )
{
	if ( triangles.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildTrianglesLineGeometry( triangles, color, width, info );

	// Draw triangles
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderCircleGeometry( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	if ( segments == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildCircleGeometry( center, radius, segments, color, info );

	// Fill circle
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderCircleLineGeometry( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	if ( segments == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildCircleLineGeometry( center, radius, segments, color, info );

	// Draw circle
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderOrientedBoxGeometry( const OrientedBox2D& box, const Color& color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildOrientedBoxGeometry( box, color, width, info );

	// Draw orient box
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderBoxGeometry( const Box& box, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildBoxGeometry( box, color, info );

	// Draw box
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderBoxLineGeometry( const Box& box, const Color& color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildBoxLineGeometry( box, color, width, info );

	// Draw box
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderXYAxisGeometry( const Vector2& origin, _float length, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildXYAxisGeometry( origin, length, width, info );

	// Draw axis
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderXYZAxisGeometry( const Vector3& origin, _float length, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildXYZAxisGeometry( origin, length, width, info );

	// Draw axis
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSphereGeometry( const Vector3& origin, _float radius, _float latitude, _float longitude )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildSphereGeometry( origin, radius, latitude, longitude, info );

	// Draw sphere
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderFrustumGeometry( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width )
{
	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildFrustumGeometry( frustum, near_plane_color, far_plane_color, line_color, width, info );

	// Draw frustum
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderPolygonLineGeometry( const Polygon2D& polygon, const Color& color, _float width )
{
	if ( polygon.mVertexArray.Number( ) == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info;
	mGeometryBuilder->BuildPolygonLineGeometry( polygon, color, width, info );

	// Draw polygon
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( sprite == _null )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometry( sprite, vertex_offsets, offset, transform, size, uv_info, color, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometryInMaskMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info )
{
	if ( sprite == _null )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometryInMaskMode( sprite, offset, transform, size, uv_info, color, mask, mask_transform, mask_offset, mask_size, mask_uv_info, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometryInTriangleMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color )
{
	if ( sprite == _null )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometryInTriangleMode( sprite, vertex_triangle, uv_triangle, color, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometryInTriangleStripeMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number )
{
	if ( sprite == _null || pos_list == _null || color_list == _null || uv_list == _null || vertices_number == 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometryInTriangleStripeMode( sprite, pos_list, uv_list, color_list, vertices_number, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometryInQuadMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number )
{
	if ( sprite == _null || pos_list == _null || color_list == _null || uv_list == _null || vertices_number == 0 )
		return;

	// At least has one quad primitive
	if ( vertices_number < 4 || ( ( vertices_number - 4 ) % 2 ) != 0 )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometryInQuadMode( sprite, pos_list, uv_list, color_list, vertices_number, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderSpriteGeometryIn3x3Mode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( sprite == _null || effect == _null )
		return;

	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildSpriteGeometryIn3x3Mode( sprite, offset, size, block_region, transform, uv_info, color, info );

	// Draw sprite
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderScreenAlignedBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildScreenAlignedBillboardGeometry( sprite, view_transform, vertex_offsets, transform, position, uv_info, color, info );

	// Draw billboard
	RenderGeometry( mScene->GetSceneView( ), info, position );
}

_void GraphicGeometryProcessor::RenderViewpointOrientedBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildViewpointOrientedBillboardGeometry( sprite, view_transform, vertex_offsets, transform, position, uv_info, color, info );

	// Draw billboard
	RenderGeometry( mScene->GetSceneView( ), info, position );
}

_void GraphicGeometryProcessor::RenderAxialBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildAxialBillboardGeometry( sprite, view_transform, vertex_offsets, transform, position, scaling, axis, uv_info, color, info );

	// Draw billboard
	RenderGeometry( mScene->GetSceneView( ), info, position );
}

_void GraphicGeometryProcessor::RenderRectBillboardGeometry( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildRectBillboardGeometry( sprite, vertex_offsets, transform, position, uv_info, color, info );

	// Draw billboard
	RenderGeometry( mScene->GetSceneView( ), info, position );
}

_void GraphicGeometryProcessor::RenderCharacterGeometry( IGraphicEffect* effect, _dword prev_code, _dword code, FontRHI* font_resource, const FontCodeRHI* font_code, const Color& color, const Vector2& position, const Matrix3& transform )
{
	// Build vertex buffer
	GeometryBuildInfo info( effect );
	mGeometryBuilder->BuildCharacterGeometry( prev_code, code, font_resource, font_code, color, position, transform, info );

	// Render character
	RenderGeometry( mScene->GetSceneView( ), info );
}

_void GraphicGeometryProcessor::RenderGeometry( IGraphicSceneView* scene_view, const GeometryBuildInfo& info )
{
	RenderGeometry( scene_view, (const _byte*) info.mVertexBuffer.GetPointer( ), info.mIndexBuffer, info.mEffect, info.mGeometryInfo, 0.0f );
}

_void GraphicGeometryProcessor::RenderGeometry( IGraphicSceneView* scene_view, const GeometryBuildInfo& info, const Vector3& center_pos )
{
	RenderGeometry( scene_view, (const _byte*)info.mVertexBuffer.GetPointer( ), info.mIndexBuffer, info.mEffect, info.mGeometryInfo, center_pos );
}

_void GraphicGeometryProcessor::RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info )
{
	RenderGeometry( scene_view, vertex_buffer, index_buffer, effect, geometry_info, 0.0f );
}

_void GraphicGeometryProcessor::RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, const Vector3& center_pos )
{
	_float distance = scene_view->GetDistanceFromCamera( center_pos );

	RenderGeometry( scene_view, vertex_buffer, index_buffer, effect, geometry_info, distance );
}

_void GraphicGeometryProcessor::RenderGeometry( IGraphicSceneView* scene_view, const _byte* vertex_buffer, const _word* index_buffer, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, _float distance )
{
	EGE_ASSERT( vertex_buffer != _null );

	// The vertex type
	_dword vertex_type = _GVT_POS | _GVT_COLOR0 | _GVT_COLOR1 | _GVT_UV1;

	// Get the vertex array object
	IGraphicVertexArray* vao = mVAOGroup.GetVAO( vertex_type, geometry_info.mVBSize, geometry_info.GetIBSize( ) );
	EGE_ASSERT( vao != _null );

	// Get the IBO start index
	_dword ibo_start_index = index_buffer != _null ? vao->GetIBOffset( ) / sizeof( _word ) : 0;

	// Get the render queue type
	_GRAPHIC_RENDER_QUEUE render_queue_type = effect->GetRenderQueueType( );

	// Get the geometries
	GraphicGeometryGroup& geometry_group = mGeometryGroups[ render_queue_type ];

	// Try to combine with last geometry
	if ( geometry_group.TryCombineWithLastGeometry( effect, vao, ibo_start_index, vertex_buffer, index_buffer, geometry_info ) )
		return;

	// Allocate and initialize geometry
	GraphicGeometry* new_geometry = mGeometryElements.Append( );
	new_geometry->Init( vao, effect, geometry_info, ibo_start_index );

	// Update and save UBOs ( with scene only, because it doesn't have any none-mesh rendering )
	new_geometry->UpdateSceneUBOs( mScene );
	new_geometry->SaveUBOs( mBufferAllocator );

	// Update the vertex buffer
	const GraphicMeshGeometryInfo& new_geometry_info = new_geometry->GetGeometryInfo( );
	vao->WriteBuffers( new_geometry_info.mVBSize, vertex_buffer, new_geometry_info.mIBONumber, index_buffer );

	// Append new geometry
	geometry_group.InsertGeometry( distance, new_geometry );
}

_void GraphicGeometryProcessor::RenderMeshGeometry( IGraphicScene* scene, IGraphicSceneView* scene_view, IGraphicEffect* effect, IGraphicMesh* mesh )
{
	RenderMeshGeometry( scene, scene_view, effect, mesh->GetMeshGeometryInfo( ) );
}

_void GraphicGeometryProcessor::RenderMeshGeometry( IGraphicScene* scene, IGraphicSceneView* scene_view, IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	EGE_ASSERT( scene != _null );
	EGE_ASSERT( scene_view != _null );

	// Allocate and initialize geometry
	GraphicGeometry* new_geometry = mGeometryElements.Append( );
	new_geometry->Init( effect, geometry_info );

	// Update and save UBOs
	new_geometry->UpdateSceneUBOs( mScene );
	new_geometry->UpdateMeshUBOs( mScene );
	new_geometry->SaveUBOs( mBufferAllocator );

	// Get the render queue type
	_GRAPHIC_RENDER_QUEUE render_queue_type = effect->GetRenderQueueType( );

	// Get the geometries
	GraphicGeometryGroup& geometry_group = mGeometryGroups[render_queue_type];

	// Append new geometry
	geometry_group.InsertGeometry( scene_view, new_geometry );

	// If it's mirror then add it into mirror group
	if ( geometry_info.mMirrorType != _GRAPHIC_MIRROR_NONE )
		AddMeshAsMirror( scene_view, geometry_info.mMirrorType, geometry_info.mMirrorSize, *new_geometry );

	// Check whether draw into mirror
	mMirrorGroup.RenderGeometryInMirrors( scene_view, effect, geometry_info.mMirrorReflectType, *new_geometry );
}

IGraphicMeshPassRef	GraphicGeometryProcessor::AddMesh( IGeometryMeshChunk* mesh_chunk )
{
	EGE_ASSERT( mesh_chunk != _null );

	const GeometryMeshChunkInfo& info = mesh_chunk->GetInfo( );

	return mResidentVAOGroup.AddMesh( info.mVertexType, info.mVertexBufferStride, mesh_chunk->GetVertexBufferSize( ), mesh_chunk->GetVertexBufferData( ), mesh_chunk->GetIndexBufferSize( ), mesh_chunk->GetIndexBufferData( ) );
}

_void GraphicGeometryProcessor::FlushBuffers( )
{
	// Flush none-resident buffers
	mVAOGroup.FlushBuffers( );
	mVAOGroup.FreeBuffers( );

	// Flush resident buffers
	mResidentVAOGroup.FlushBuffers( );
}

_void GraphicGeometryProcessor::PresentRenderBuffers( IGraphicCanvas* canvas, const GraphicClearBuffersInfo& clear_info )
{
	// Get the last viewport
	const Viewport* last_viewport = mGeometryBuilder->GetLastViewport( );
	EGE_ASSERT( last_viewport != _null );

	// Render all geometry
	PresentRenderBuffers( canvas, clear_info, *last_viewport );
}

_void GraphicGeometryProcessor::PresentRenderBuffers( IGraphicCanvas* canvas, const GraphicClearBuffersInfo& clear_info, const Viewport& viewport )
{
	// Flush buffers
	FlushBuffers( );

	// Draw mirrors
	mMirrorGroup.PresentMirrors( );

	// Bind FBO
	if ( canvas != _null )
		GetGraphicModule( )->SetRenderTarget( canvas->GetRenderTarget( ), canvas->GetDepthStencil( ) );
	else
		GetGraphicModule( )->SetRenderTarget( _null, _null );

	// Clear buffers
	gDynamicRHI->ClearBuffers( clear_info.mIsClearColor, clear_info.mClearColor, clear_info.mIsClearDepth, clear_info.mClearDepth, clear_info.mIsClearStencil, clear_info.mClearStencil );

	// Set the viewport size
	gDynamicRHI->SetViewport( viewport );

	// Draw geometries
	for ( _dword i = 0; i < _GEOMETRY_GROUP_NUMBER; i ++ )
		mGeometryGroups[i].PaintGeometries( );

	// Clear caches
	ClearCaches( );
}