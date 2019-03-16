//! @file     GraphicMaskLayer.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicMaskLayer Implementation
//----------------------------------------------------------------------------

GraphicMaskLayer::GraphicMaskLayer( GraphicGeometryProcessor* geometry_processor )
	: mGeometryProcessor( geometry_processor )
{

}

GraphicMaskLayer::~GraphicMaskLayer( )
{
}

_void GraphicMaskLayer::UpdateStencilBuffer( const RectF& region, StencilStateRHI* stencil_state )
{
	// Start to update stencil buffer
	mStencilEffect->PushStates( );
	{
		// Update render states
		mStencilEffect->SetStencilState( stencil_state );

		// Render geometry
		mGeometryProcessor->RenderRectGeometry( region, Color::cNull );
	}
	mStencilEffect->PopStates( );
}

_void GraphicMaskLayer::BuildMaskLayer( const RectF& region, _dword mask_value, MaskLayerInfo& info )
{
	// Create the stencil state
	StencilStateInitializerRHI stencil_state_init;
	stencil_state_init.mEnableFrontFaceStencil			= _true;
	stencil_state_init.mFrontFaceStencilTest			= _CF_NEVER;
	stencil_state_init.mFrontFaceStencilFailStencilOp	= _SO_REPLACE;
	stencil_state_init.mStencilRef						= mask_value;

	// Create the stencil state
	StencilStateInitializerRHI stencil_state_init_for_effect;
	stencil_state_init_for_effect.mEnableFrontFaceStencil	= _true;
	stencil_state_init_for_effect.mFrontFaceStencilTest		= _CF_EQUAL;
	stencil_state_init_for_effect.mStencilRef				= mask_value;

	// Build mask layer info
	info.mMaskValue				= mask_value;
	info.mRegion				= region;
	info.mStencilState			= gDynamicRHI->CreateStencilState( stencil_state_init );
	info.mStencilStateForEffect = gDynamicRHI->CreateStencilState( stencil_state_init_for_effect );
}

_void GraphicMaskLayer::PushMaskSprite( const Matrix3& transform, const Vector2& offset, const Vector2& size, IGraphicTexture2D* sprite, const Color& color, const GraphicUVInfo& uv_info )
{
	MaskSpriteInfo info;
	info.mTransform = transform;
	info.mOffset	= offset;
	info.mSize		= size;
	info.mSprite	= sprite;
	info.mColor		= color;
	info.mUVInfo	= uv_info;
	mMaskSprites.Push( info );

	mMaskSpriteEffect->PushStates( );
	{
		// Create the stencil state
		StencilStateInitializerRHI stencil_state_init;
		stencil_state_init.mEnableFrontFaceStencil			= _true;
		stencil_state_init.mFrontFaceStencilTest			= _CF_NEVER;
		stencil_state_init.mFrontFaceStencilFailStencilOp	= _SO_INCREMENT;
		StencilStateRHIRef stencil_state					= gDynamicRHI->CreateStencilState( stencil_state_init );
		EGE_ASSERT( stencil_state.IsValid( ) );

		// Update the stencil state
		mMaskSpriteEffect->SetStencilState( stencil_state );

		// Draw mask sprite to stencil
		mGeometryProcessor->RenderSpriteGeometry( sprite, mMaskSpriteEffect, _null, offset, transform, size, uv_info, color );
	}
	mMaskSpriteEffect->PopStates( );
}

_void GraphicMaskLayer::PopMaskSprite( )
{
	MaskSpriteInfo& info = mMaskSprites.Top( );

	mMaskSpriteEffect->PushStates( );
	{
		// Create the stencil state
		StencilStateInitializerRHI stencil_state_init;
		stencil_state_init.mEnableFrontFaceStencil			= _true;
		stencil_state_init.mFrontFaceStencilTest			= _CF_NEVER;
		stencil_state_init.mFrontFaceStencilFailStencilOp	= _SO_DECREMENT;
		StencilStateRHIRef stencil_state					= gDynamicRHI->CreateStencilState( stencil_state_init );
		EGE_ASSERT( stencil_state.IsValid( ) );

		// Update the stencil state
		mMaskSpriteEffect->SetStencilState( stencil_state );

		// Draw mask sprite to stencil
		mGeometryProcessor->RenderSpriteGeometry( info.mSprite, mMaskSpriteEffect, _null, info.mOffset, info.mTransform, info.mSize, info.mUVInfo, info.mColor );
	}
	mMaskSpriteEffect->PopStates( );

	mMaskSprites.Pop( );
}

_void GraphicMaskLayer::RenderSpriteWithMask( IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, IGraphicTexture2D* sprite, const Color& color, const GraphicUVInfo& uv_info )
{
	// Process the sprite geometry
	effect->PushStates( );
	{
		// Create the stencil state
		StencilStateInitializerRHI stencil_state_init;
		stencil_state_init.mEnableFrontFaceStencil	= _true;
		stencil_state_init.mFrontFaceStencilTest	= _CF_EQUAL;
		stencil_state_init.mStencilRef				= GetCurMaskValue( ) + 1;
		StencilStateRHIRef stencil_state			= gDynamicRHI->CreateStencilState( stencil_state_init );
		EGE_ASSERT( stencil_state.IsValid( ) );

		// Update the stencil state
		effect->SetStencilState( stencil_state );

		// Draw sprite
		mGeometryProcessor->RenderSpriteGeometry( sprite, effect, _null, offset, transform, size, uv_info, color );
	}
	effect->PopStates( );
}

_ubool GraphicMaskLayer::Initialize( )
{
	// Get the rasterizer state of disable write to color buffer
	RasterizerStateRHIRef disable_color_buffer_write = GetGraphicResourceManager( )->GetRasterizerStateFromResName( WSTROBJ( RasterizerDisableColorWrite ) );
	if ( disable_color_buffer_write.IsNull( ) )
		return _false;

	// Create stencil effect
	mStencilEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eVertexColor ) );
	if ( mStencilEffect.IsNull( ) )
		return _false;

	mStencilEffect->SetRasterizerState( disable_color_buffer_write );

	// Create mask sprite effect
	mMaskSpriteEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eTex0DiscardTransparent ) );
	if ( mMaskSpriteEffect.IsNull( ) )
		return _false;

	mMaskSpriteEffect->SetRasterizerState( disable_color_buffer_write );

	// Initialize layer info
	MaskLayerInfo info;
	info.mMaskValue = 0;
	info.mRegion	= RectF( 0.0f, 0.0f, Math::cMaxFloat, Math::cMaxFloat );

	// Create the default stencil state
	StencilStateInitializerRHI stencil_state_init;
	stencil_state_init.mEnableFrontFaceStencil			= _true;
	stencil_state_init.mFrontFaceStencilTest			= _CF_NEVER;
	stencil_state_init.mFrontFaceStencilFailStencilOp	= _SO_REPLACE;
	stencil_state_init.mStencilRef						= info.mMaskValue;
	info.mStencilState = gDynamicRHI->CreateStencilState( stencil_state_init );
	if ( info.mStencilState.IsNull( ) )
		return _false;

	mMaskLayers.Push( info );

	return _true;
}

_void GraphicMaskLayer::SetMaskLayer( const RectF& region, _dword mask_value )
{
	EGE_ASSERT( mMaskLayers.Number( ) >= 2 );

	// Build mask layer info
	MaskLayerInfo info;
	BuildMaskLayer( region, mask_value, info );

	// Push mask layer
	mMaskLayers.Top( ) = info;

	// Update stencil buffer
	UpdateStencilBuffer( info.mRegion, info.mStencilState );
}

_void GraphicMaskLayer::PushMaskLayer( const RectF& region, _dword mask_value )
{
	EGE_ASSERT( mMaskLayers.Number( ) >= 1 );

	// Build mask layer info
	MaskLayerInfo info;
	BuildMaskLayer( region, mask_value, info );

	// Push mask layer
	mMaskLayers.Push( info );

	// Update stencil buffer
	UpdateStencilBuffer( info.mRegion, info.mStencilState );
}

_void GraphicMaskLayer::PopMaskLayer( )
{
	EGE_ASSERT( mMaskLayers.Number( ) > 1 );

	// Get the layer info
	MaskLayerInfo& prev_info	= mMaskLayers[ mMaskLayers.Number( ) - 2 ];
	MaskLayerInfo& cur_info		= mMaskLayers.Top( );

	// Get the region what to resume
	RectF region = RectF::Union( prev_info.mRegion, cur_info.mRegion );

	// Resume stencil buffer
	UpdateStencilBuffer( region, prev_info.mStencilState );

	// Pop mask layer
	mMaskLayers.Pop( );
}

_void GraphicMaskLayer::PushEffect( IGraphicEffect* effect )
{
	if ( mMaskLayers.Number( ) == 1 )
		return;

	// Get the current layer what to pop
	MaskLayerInfo& top_info = mMaskLayers.Top( );

	// Save the previous effect of it 
	effect->PushStates( );
	effect->SetStencilState( top_info.mStencilStateForEffect );
}

_void GraphicMaskLayer::PopEffect( IGraphicEffect* effect )
{
	if ( mMaskLayers.Number( ) == 1 )
		return;

	// Resume effect render states
	effect->PopStates( );
}

_dword GraphicMaskLayer::GetCurMaskValue( ) const
{
	return mMaskLayers.Top( ).mMaskValue;
}
