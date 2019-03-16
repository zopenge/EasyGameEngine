//! @file     GraphicFilter.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicFilter Implementation
//----------------------------------------------------------------------------

GraphicFilter::GraphicFilter( )
{
}

GraphicFilter::~GraphicFilter( )
{
}

_void GraphicFilter::ProcessBlurEffect( IGraphicCanvas* canvas, const PointF& step_size, IGraphicSurface* surface )
{
	if ( canvas == _null || surface == _null )
		return;

	// Get the blur effect
	IGraphicEffect* effect = GetGraphicShaderManager( )->GetInternalEffect( _GIET_OVERLAY_POST_EFFECT_GAUSSIAN_BLUR );
	EGE_ASSERT( effect != _null );

	// Update step size
	effect->SetUBO( _GIUBT_STEP_SIZE, Vector2( step_size.x, step_size.y ) );

	// Draw texture with filter to canvas
	canvas->DrawSurface( Vector2::cOrigin, surface, effect );
	canvas->PresentRenderBuffers( );
}