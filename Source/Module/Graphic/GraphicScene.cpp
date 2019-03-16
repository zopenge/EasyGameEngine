//! @file     GraphicScene.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicScene Implementation
//----------------------------------------------------------------------------

GraphicScene::GraphicScene( )
{
	mClientSize			= PointU::cZeroPoint;
	mClientRatio		= Ratio::cNull;

	mViewport			= Viewport::cNull;

	mGeometryBuilder	= _null;
	mGeometryProcessor	= _null;

	mMaskLayer			= _null;

	mScissorRectStack.Push( RectF::cNull );
	mOverlayTransformStack.Push( OverlayTransformInfo( ) );
	mUserOrthoTransformStack.Push( Matrix4::cIdentity );
	mOffsetTransformStack.Push( Matrix4::cIdentity );

	ResetClearBuffersOperations( );
}

GraphicScene::~GraphicScene( )
{
	EGE_DELETE( mGeometryProcessor );
	EGE_DELETE( mGeometryBuilder );

	EGE_DELETE( mMaskLayer );
}

_void GraphicScene::OnSceneViewTransformChangedCallback( const QwordParameters2& parameters )
{
	GraphicScene* scene = (GraphicScene*) parameters[0];
	EGE_ASSERT( scene != _null );

	scene->UpdateTransforms( );
}

_void GraphicScene::ResetClearBuffersOperations( )
{
	mClearBuffersInfo.Reset( );
}

_void GraphicScene::UpdateTransforms( )
{
	// Convert the overlay transform to matrix 4x4
	Matrix4 overlay_transform = Matrix4( ).FromTranslationRotation( GetOverlayTransform( ) );

	// Get the user ortho transform
	const Matrix4* user_ortho = &GetUserOrthoTransform( );
	if ( *user_ortho == Matrix4::cIdentity )
		user_ortho = _null;

	// Update transforms
	mGeometryBuilder->UpdateTransform( &overlay_transform, user_ortho, &GetOffsetTransform( ), _false );
}

_void GraphicScene::RenderCharacter( IGraphicFont* font, _dword prev_code, _dword code, const Vector2& start_position, Vector2& position, const FontColorRHI& font_color, const Matrix3& transform, IGraphicEffect* effect )
{
	// The selected font
	IGraphicFont* selected_font = _null;

	// Get the selected font and resource
	const FontCodeRHI* font_code = font->GetFontCode( code, selected_font );
	if ( font_code == _null )
		return;

	// Get the font resource
	FontRHI* font_resource = selected_font->GetResource( );
	EGE_ASSERT( font_resource != _null );

	// Get the advance of character
	_float advance = font_code->mAdvanceX;

	// Start to render character
	mMaskLayer->PushEffect( effect );
	{
		// Render character with blur effect.
		if ( font_color.mBlur.mSize != 0 && font_color.mBlur.mFactor != 0 )
		{
			// Get the font code info
			const FontCodeRHI* blur_font_code = gDynamicRHI->GetFontCodeByBlurEffect( font_resource, code, font_color.mBlur.mSize, font_color.mBlur.mFactor );
			if ( blur_font_code == _null )
				return;

			// Render blur character
			mGeometryProcessor->RenderCharacterGeometry( effect, prev_code, code, font_resource, blur_font_code, font_color.mBlur.mColor, position, transform );

			// Update the advance
			advance = Math::Max< _float >( blur_font_code->mAdvanceX, advance );
		}

		// Render character with stroke effect
		if ( font_color.mStroke.mSize != 0 )
		{
			// Get the font code info
			const FontCodeRHI* stroke_font_code = gDynamicRHI->GetFontCodeByStrokeEffect( font_resource, code, font_color.mStroke.mSize );
			if ( stroke_font_code == _null )
				return;

			// Render blur character
			mGeometryProcessor->RenderCharacterGeometry( effect, prev_code, code, font_resource, stroke_font_code, font_color.mStroke.mColor, position, transform );

			// Update the advance
			advance = Math::Max< _float >( stroke_font_code->mAdvanceX, advance );
		}

		// Render character
		mGeometryProcessor->RenderCharacterGeometry( effect, prev_code, code, font_resource, font_code, font_color.mFillColor, position, transform );
	}
	mMaskLayer->PopEffect( effect );

	// Prepare to draw the next character
	position.x += advance;
}

_ubool GraphicScene::Initialize( )
{
	// Create scene view
	mSceneView = GetGraphicResourceManager( )->CreateSceneView( );
	if ( mSceneView.IsNull( ) )
		return _false;

	// Create builder and processor
	mGeometryBuilder	= new GraphicGeometryBuilder( this );
	mGeometryProcessor	= new GraphicGeometryProcessor( mGeometryBuilder, this );

	// Update transforms
	mSceneView->SetTransformChangedFunc( OnSceneViewTransformChangedCallback, QwordParameters2( ( _qword )this, _null ) );

	// Initialize geometry processor
	if ( mGeometryBuilder->Initialize( ) == _false )
		return _false;

	// Initialize geometry processor
	if ( mGeometryProcessor->Initialize( ) == _false )
		return _false;

	// Create mask layer
	mMaskLayer = new GraphicMaskLayer( mGeometryProcessor );
	if ( mMaskLayer->Initialize( ) == _false )
		return _false;

	return _true;
}

_void GraphicScene::DrawPoint( const Vector2& position, const Color& color )
{
}

_void GraphicScene::DrawPoint( const Vector3& position, const Color& color )
{
}

_void GraphicScene::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
	mGeometryProcessor->RenderLineGeometry( start, end, color, width );
}

_void GraphicScene::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	mGeometryProcessor->RenderLineGeometry( start, end, color_start, color_end, width );
}

_void GraphicScene::DrawLine( const Vector3& start, const Vector3& end, const Color& color, _float width )
{
	mGeometryProcessor->RenderLineGeometry( start, end, color, width );
}

_void GraphicScene::DrawLine( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width )
{
	mGeometryProcessor->RenderLineGeometry( start, end, color_start, color_end, width );
}

_void GraphicScene::DrawLine( const Line2D& line, const Color& color, _float width )
{
	DrawLine( line.mPoints[0], line.mPoints[1], color, width );
}

_void GraphicScene::DrawLine( const Line3D& line, const Color& color, _float width )
{
	DrawLine( line.mPoints[0], line.mPoints[1], color, width );
}

_void GraphicScene::DrawLines( const Line2DArray& lines, const Color& color, _float width )
{
	mGeometryProcessor->RenderLinesGeometry( lines, color, width );
}

_void GraphicScene::DrawLines( const Line3DArray& lines, const Color& color, _float width )
{
	mGeometryProcessor->RenderLinesGeometry( lines, color, width );
}

_void GraphicScene::FillTriangles( const TriangleArray& triangles, const Color& color )
{
	mGeometryProcessor->RenderTrianglesGeometry( triangles, color );
}

_void GraphicScene::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
	mGeometryProcessor->RenderRectLineGeometry( rect, color, width );
}

_void GraphicScene::FillRectangle( const RectF& rect, const Color& color )
{
	mGeometryProcessor->RenderRectGeometry( rect, color );
}

_void GraphicScene::DrawCircle( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	mGeometryProcessor->RenderCircleLineGeometry( center, radius, segments, color );
}

_void GraphicScene::FillCircle( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	mGeometryProcessor->RenderCircleGeometry( center, radius, segments, color );
}

_void GraphicScene::DrawOrientedBox( const OrientedBox2D& box, const Color& color, _float width )
{
	mGeometryProcessor->RenderOrientedBoxGeometry( box, color, width );
}

_void GraphicScene::DrawAxisAlignedBox( const AxisAlignedBox& box, const Color& color, _float width )
{
	// Draw box
	DrawBox( Box( box.mMinVector, box.mMaxVector ), color, width );
}

_void GraphicScene::DrawBox( const Box& box, const Color& color, _float width )
{
	mGeometryProcessor->RenderBoxLineGeometry( box, color, width );
}

_void GraphicScene::FillBox( const Box& box, const Color& color )
{
	mGeometryProcessor->RenderBoxGeometry( box, color );
}

_void GraphicScene::DrawXYAxis( const Vector2& origin, _float length, _float width )
{
	mGeometryProcessor->RenderXYAxisGeometry( origin, length, width );
}

_void GraphicScene::DrawXYZAxis( const Vector3& origin, _float length, _float width )
{
	mGeometryProcessor->RenderXYZAxisGeometry( origin, length, width );
}

_void GraphicScene::DrawSphere( const Vector3& origin, _float radius, _float latitude, _float longitude )
{
	mGeometryProcessor->RenderSphereGeometry( origin, radius, latitude, longitude );
}

_void GraphicScene::DrawFrustum( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width )
{
	mGeometryProcessor->RenderFrustumGeometry( frustum, near_plane_color, far_plane_color, line_color, width );
}

_void GraphicScene::DrawPolygon( const Polygon2D& polygon, const Color& color, _float width )
{
	mGeometryProcessor->RenderPolygonLineGeometry( polygon, color, width );
}

_void GraphicScene::DrawTriangles( const Triangle2DArray& triangles, const Color& color, _float width )
{
	mGeometryProcessor->RenderTrianglesLineGeometry( triangles, color, width );
}

_void GraphicScene::FillTriangles( const Triangle2DArray& triangles, const Color& color )
{
	mGeometryProcessor->RenderTrianglesGeometry( triangles, color );
}

_void GraphicScene::FillPolygon( const Polygon2D& polygon, const Color& color )
{
	Triangle2DArray triangles;
	polygon.ToTriangleArray( triangles );

	FillTriangles( triangles, color );
}

_void GraphicScene::DrawSprite( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderSpriteGeometry( sprite, effect, vertex_offsets, offset, transform, size, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawSpriteInMaskMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask_sprite, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info )
{
	if ( effect == _null )
		return;

	// Draw sprite without mask
	if ( mask_sprite == _null )
	{
		DrawSprite( sprite, effect, _null, offset, transform, size, uv_info, color );
	}
	// Draw sprite with alpha mask
	else
	{
		// Get the effect combination flags
		AString macros = "_USE_SPRITE_MASK_";
		if ( mask_uv_info.mIsRotate )
			macros += "|_USE_SPRITE_MASK_WITH_ROTATION_";

		// Get the effect
		IGraphicEffectRef mask_effect = GetGraphicResourceManager( )->CreateEffectFromEffect( effect, macros );
		EGE_ASSERT( mask_effect != _null );

		// Use the nearest sampler effect
		mask_effect->SetSamplerState( ASTROBJ( uSpriteMaskTex ), GetGraphicResourceManager( )->GetSamplerStateFromResName( WSTROBJ( SamplerNearest ) ) );

		// Draw sprite
		mMaskLayer->PushEffect( mask_effect );
		mGeometryProcessor->RenderSpriteGeometryInMaskMode( sprite, mask_effect, offset, transform, size, uv_info, color, mask_sprite, mask_transform, mask_offset, mask_size, mask_uv_info );
		mMaskLayer->PopEffect( mask_effect );
	}
}

_void GraphicScene::DrawSpriteInTriangleMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertexs, const Triangle2D& uvs, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderSpriteGeometryInTriangleMode( sprite, effect, vertexs, uvs, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawSpriteInTriangleStripeMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderSpriteGeometryInTriangleStripeMode( sprite, effect, pos_list, uv_list, color_list, vertices_number );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawSpriteInQuadMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Color* color_list, const Vector2* uv_list, _dword vertices_number )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderSpriteGeometryInQuadMode( sprite, effect, pos_list, uv_list, color_list, vertices_number );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawSpriteIn3x3Mode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderSpriteGeometryIn3x3Mode( sprite, effect, offset, size, block_region, transform, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawScreenAlignedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderScreenAlignedBillboardGeometry( sprite, effect, mSceneView->GetViewTransform( ), vertex_offsets, transform, position, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawViewpointOrientedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderViewpointOrientedBillboardGeometry( sprite, effect, mSceneView->GetViewTransform( ), vertex_offsets, transform, position, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawAxialBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderAxialBillboardGeometry( sprite, effect, mSceneView->GetViewTransform( ), vertex_offsets, transform, position, scaling, axis, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawRectBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( effect == _null )
		return;

	mMaskLayer->PushEffect( effect );
	mGeometryProcessor->RenderRectBillboardGeometry( sprite, effect, vertex_offsets, transform, position, uv_info, color );
	mMaskLayer->PopEffect( effect );
}

_void GraphicScene::DrawSurface( const RectF& region, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// Get the position and size
	Vector2 position( region.l, region.t );
	Vector2 size( region.GetWidth( ), region.GetHeight( ) );

	// Draw the surface
	DrawSurface( position, size, surface, effect );
}

_void GraphicScene::DrawSurface( const RectF& region, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// Get the position and size
	Vector2 position( region.l, region.t );
	Vector2 size( region.GetWidth( ), region.GetHeight( ) );

	// Draw the surface
	DrawSurface( position, size, uv1, uv2, surface, effect );
}

_void GraphicScene::DrawSurface( const Vector2& position, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// Get the surface size
	const Vector2 size( (_float) surface->GetSize( ).x, (_float) surface->GetSize( ).y );

	// Draw it
	DrawSurface( position, size, surface, effect );
}

_void GraphicScene::DrawSurface( const Vector2& position, const Vector2& size, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// Get the UVs
	Vector2 uv1( 0.0f, EGE_RATIO( size.y, surface->GetSize( ).y ) );
	Vector2 uv2( EGE_RATIO( size.x, surface->GetSize( ).x ), 0.0f );

	// Draw the surface
	DrawSurface( position, size, uv1, uv2, surface, effect );
}

_void GraphicScene::DrawSurface( const Vector2& position, const Vector2& size, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// The sprite use the center position as origin
	Vector2 sprite_offset = position + (size / 2.0f);

	// Draw surface by flip it
	DrawSprite( surface->GetTexture2D( ), effect, _null, sprite_offset, Matrix3::cIdentity, size, GraphicUVInfo( uv1, uv2 ), Color::cWhite );
}

_void GraphicScene::DrawSurface( const Matrix3& transform, const Vector2& offset, IGraphicSurface* surface, IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	// Get the surface size
	const Vector2 size( (_float) surface->GetSize( ).x, (_float) surface->GetSize( ).y );

	// Get the UVs
	Vector2 uv1( 0.0f, EGE_RATIO( size.y, surface->GetSize( ).y ) );
	Vector2 uv2( EGE_RATIO( size.x, surface->GetSize( ).x ), 0.0f );

	// Draw surface by flip it
	DrawSprite( surface->GetTexture2D( ), effect, _null, offset, transform, size, GraphicUVInfo( uv1, uv2 ), Color::cWhite );
}

_void GraphicScene::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color )
{
	DrawText( position, string, font, font_color, Matrix3::cIdentity );
}

_void GraphicScene::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform )
{
	if ( font == _null || string.IsEmpty( ) )
		return;

	// Get the font RHI resource
	FontRHI* font_resource = font->GetResource( );
	EGE_ASSERT( font_resource != _null );

	// Get the font face interface
	IFontFaceRef font_face = gDynamicRHI->GetFontFace( font_resource );
	if ( font_face.IsNull( ) )
		return;

	// Get the effect
	IGraphicEffect* effect = font->GetEffect( );
	EGE_ASSERT( effect != _null );

	// The left-top position
	Vector2 pos = position;

	// Draw characters
	for ( _dword i = 0; string[i] != 0; i ++ )
	{
		_dword prev_code	= i == 0 ? 0 : string[i - 1];
		_dword code			= string[i];

		// Skip for unused character
		if ( code == '\r' )
			continue;

		// Check whether it's new line tag
		if ( code == '\n' )
		{
			pos.x  = position.x;
			pos.y += font_face->GetCharMaxHeight( );
			continue;
		}

		// Render character with stroke
		RenderCharacter( font, prev_code, code, position, pos, font_color, transform, effect );
	}
}

_void GraphicScene::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform, const FontColorRHI& bk_font_color, const Vector2& bk_offset )
{
	DrawText( position + bk_offset, string, font, bk_font_color, transform );
	DrawText( position, string, font, font_color, transform );
}

_void GraphicScene::DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	mGeometryProcessor->RenderMeshGeometry( this, mSceneView, effect, geometry_info );
}

_void GraphicScene::PushScissorRect( const RectF& rect )
{
	mScissorRectStack.Push( rect );

	mMaskLayer->PushMaskLayer( rect, mScissorRectStack.Number( ) - 1 );
}

_void GraphicScene::PopScissorRect( )
{
	// At least we have one scissor rect info
	EGE_ASSERT( mScissorRectStack.Number( ) != 1 );

	mScissorRectStack.Pop( );

	mMaskLayer->PopMaskLayer( );
}

_void GraphicScene::SetScissorRect( const RectF& rect )
{
	mScissorRectStack.Top( ) = rect;

	mMaskLayer->SetMaskLayer( rect, mScissorRectStack.Number( ) - 1 );
}

const RectF& GraphicScene::GetScissorRect( ) const
{
	return mScissorRectStack.Top( );
}

_void GraphicScene::PushOverlayTransform( const Matrix3& transform )
{
	mOverlayTransformStack.Push( OverlayTransformInfo( transform ) );

	// Convert the overlay transform to matrix 4x4
	Matrix4 overlay_transform = Matrix4( ).FromTranslationRotation( transform );

	// Update transforms
	mGeometryBuilder->UpdateTransform( &overlay_transform, _null, _null, _false );
}

_void GraphicScene::PopOverlayTransform( )
{
	EGE_ASSERT( mOverlayTransformStack.Number( ) != 1 );

	mOverlayTransformStack.Pop( );

	// Convert the overlay transform to matrix 4x4
	Matrix4 overlay_transform = Matrix4( ).FromTranslationRotation( GetOverlayTransform( ) );

	// Update transforms
	mGeometryBuilder->UpdateTransform( &overlay_transform, _null, _null, _false );
}

_void GraphicScene::SetOverlayTransform( const Matrix3& transform )
{
	mOverlayTransformStack.Top( ) = OverlayTransformInfo( transform );

	// Convert the overlay transform to matrix 4x4
	Matrix4 overlay_transform = Matrix4( ).FromTranslationRotation( transform );

	// Update transforms
	mGeometryBuilder->UpdateTransform( &overlay_transform, _null, _null, _false );
}

const Matrix3& GraphicScene::GetOverlayTransform( ) const
{
	return mOverlayTransformStack.Top( ).mTransform;
}

_void GraphicScene::PushUserOrthoTransform( const Matrix4& transform )
{
	mUserOrthoTransformStack.Push( transform );

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, &transform, _null, _false );
}

_void GraphicScene::PopUserOrthoTransform( )
{
	EGE_ASSERT( mUserOrthoTransformStack.Number( ) != 1 );

	mUserOrthoTransformStack.Pop( );

	// Get the user ortho transform
	const Matrix4* user_ortho = &GetUserOrthoTransform( );
	if ( *user_ortho == Matrix4::cIdentity )
		user_ortho = _null;

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, user_ortho, _null, _true );
}

_void GraphicScene::SetUserOrthoTransform( const Matrix4& transform )
{
	mUserOrthoTransformStack.Top( ) = transform;

	// Get the user ortho transform
	const Matrix4* user_ortho = &GetUserOrthoTransform( );
	if ( *user_ortho == Matrix4::cIdentity )
		user_ortho = _null;

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, user_ortho, _null, _false );
}

const Matrix4& GraphicScene::GetUserOrthoTransform( ) const
{
	return mUserOrthoTransformStack.Top( );
}

_void GraphicScene::PushOffsetTransform( const Matrix4& transform )
{
	mOffsetTransformStack.Push( transform );

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, _null, &transform, _false );
}

_void GraphicScene::PopOffsetTransform( )
{
	EGE_ASSERT( mOffsetTransformStack.Number( ) != 1 );

	mOffsetTransformStack.Pop( );

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, _null, &GetOffsetTransform( ), _false );
}

_void GraphicScene::SetOffsetTransform( const Matrix4& transform )
{
	mOffsetTransformStack.Top( ) = transform;

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, _null, &transform, _false );
}

const Matrix4& GraphicScene::GetOffsetTransform( ) const
{
	return mOffsetTransformStack.Top( );
}

_void GraphicScene::SetViewport( const Viewport& viewport )
{
	mViewport = viewport;

	mGeometryBuilder->UpdateViewport( mViewport );

	mGeometryBuilder->UpdateTransform( _null, _null, _null, _false );
}

const Viewport& GraphicScene::GetViewport( ) const
{
	return mViewport;
}

_void GraphicScene::SetClientSize( const PointU& size )
{
	// Update the viewport
	mViewport = Viewport( 0.0f, 0.0f, (_float)size.x, (_float)size.y, 0.0f, 1.0f );

	// Update client size
	mClientSize = size;
	mClientRatio.Init( mViewport.w, mViewport.h );

	mGeometryBuilder->UpdateViewport( mViewport );

	mGeometryBuilder->UpdateTransform( _null, _null, _null, _false );
}

const PointU& GraphicScene::GetClientSize( ) const
{
	return mClientSize;
}

const Ratio& GraphicScene::GetClientRatio( ) const
{
	return mClientRatio;
}

_void GraphicScene::FlushBuffers( )
{
	mGeometryProcessor->FlushBuffers( );
}

_void GraphicScene::ClearCaches( )
{
	mGeometryBuilder->ClearCaches( );
}

const Matrix4& GraphicScene::GetViewTransform( ) const
{
	return mGeometryBuilder->GetLastTransformRH( GraphicGeometryBuilder::_TRANSFORM_VIEW );
}

const Matrix4& GraphicScene::GetVPTransform( ) const
{
	return mGeometryBuilder->GetLastTransformRH( GraphicGeometryBuilder::_TRANSFORM_VP );
}

_void GraphicScene::ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mClearBuffersInfo.mIsClearColor		= clearcolor;
	mClearBuffersInfo.mIsClearDepth		= cleardepth;
	mClearBuffersInfo.mIsClearStencil	= clearstencil;
	mClearBuffersInfo.mClearColor		= color;
	mClearBuffersInfo.mClearDepth		= depth;
	mClearBuffersInfo.mClearStencil		= stencil;
}

_void GraphicScene::PresentRenderBuffers( )
{
	PresentRenderBuffers( _null );
}

_void GraphicScene::PresentRenderBuffers( IGraphicCanvas* canvas )
{
	mGeometryProcessor->PresentRenderBuffers( canvas, mClearBuffersInfo );

	// Clear buffers operations
	ResetClearBuffersOperations( );
}

_void GraphicScene::SetSceneView( IGraphicSceneView* view )
{
	mSceneView = view;

	// Register callback functions
	view->SetTransformChangedFunc( OnSceneViewTransformChangedCallback, QwordParameters2( ( _qword )this, _null ) );

	// Update transforms
	mGeometryBuilder->UpdateTransform( _null, _null, _null, _false );
}

IGraphicSceneView* GraphicScene::GetSceneView( ) const
{
	return mSceneView.GetPtr( );
}

const Viewport* GraphicScene::GetLastViewport( )
{
	return mGeometryBuilder->GetLastViewport( );
}

_ubool GraphicScene::PickMeshes( const Ray& ray, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return _false;
}

_ubool GraphicScene::PickMeshes( const AxisAlignedBox& box, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return _false;
}

IGraphicMeshPassRef	GraphicScene::AddMesh( IGeometryMeshChunk* mesh_chunk )
{
	return mGeometryProcessor->AddMesh( mesh_chunk );
}

Vector2 GraphicScene::Convert3DTo2D( const Vector3& point, _float* zsort )
{
	const PointU& client_size = GetViewport( ).GetSize( );

	return GetSceneView( )->Convert3DTo2D( client_size, point, zsort );
}

Vector2 GraphicScene::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return GetSceneView( )->Convert3DTo2D( size, point, zsort );
}

Ray GraphicScene::GetPickRay( _int x, _int y )
{
	const PointU& client_size = GetClientSize( );

	return GetSceneView( )->GetPickRay( client_size, x, y );
}

Ray GraphicScene::GetPickRay( const PointU& size, _int x, _int y )
{
	return GetSceneView( )->GetPickRay( size, x, y );
}