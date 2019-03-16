//! @file     D2DCommands.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DDrv-Commands Implementation
//----------------------------------------------------------------------------

_void D2DDrv::SetLineWidth( _float width )
{

}

_void D2DDrv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
}

_void D2DDrv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{

}

_void D2DDrv::SetBoundShader( BoundShaderRHI* shader )
{
}

_void D2DDrv::SetDepthState( const DepthStateRHI* state )
{
}

_void D2DDrv::SetStencilState( const StencilStateRHI* state )
{
}

_void D2DDrv::SetBlendState( const BlendStateRHI* state )
{
}

_void D2DDrv::SetRasterizerState( const RasterizerStateRHI* state )
{

}

_void D2DDrv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{
	RasterizerStateRHIRef state = CreateRasterizerState( initializer );
	SetRasterizerState( state );
}

_void D2DDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureRHI* texture )
{
}

_void D2DDrv::SetViewport( const Viewport& viewport )
{
}

_void D2DDrv::SetViewport( const Viewport& viewport, const Ratio& ratio )
{
}

_void D2DDrv::SetScissorRect( _ubool enable, const RectU* rect )
{

}

_void D2DDrv::Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mD2DClearColor = TranslateD2DColorF( color );
}

_void D2DDrv::DrawPoint( const Vector2& position, const Color& color ) 
{
	// Draw point
//	rendertarget->DrawLine( (const D2D1_POINT_2F&) position, (const D2D1_POINT_2F&) position, color );
}

_void D2DDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
}

_void D2DDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	DrawLine( start, end, color_start, width );
}

_void D2DDrv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
	DrawRectangle( RectF( ).InitWithPosition( (_float) rect.l, (_float) rect.t, (_float) rect.r, (_float) rect.b ), color, (_float) width );
}

_void D2DDrv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
}

_void D2DDrv::FillRectangle( const RectI& rect, const Color& color )
{
	FillRectangle( RectF( ).InitWithPosition( (_float) rect.l, (_float) rect.t, (_float) rect.r, (_float) rect.b ), color );
}

_void D2DDrv::FillRectangle( const RectF& rect, const Color& color )
{
}

_void D2DDrv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
}

_void D2DDrv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
	DYNAMIC_CAST_D2DRESOURCE( Font, font );
}

_void D2DDrv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
}

_void D2DDrv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{
}

_void D2DDrv::DrawPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword offset, _dword number, _dword instances_number )
{
}

_void D2DDrv::DrawIndexedPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword start_index, _dword number, _dword instances_number )
{
}