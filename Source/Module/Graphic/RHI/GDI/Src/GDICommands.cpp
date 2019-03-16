//! @file     GDICommands.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIDrv-Commands Implementation
//----------------------------------------------------------------------------

_void GDIDrv::SetLineWidth( _float width )
{

}

_void GDIDrv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
}

_void GDIDrv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{

}

_void GDIDrv::SetBoundShader( BoundShaderRHI* shader )
{
}

_void GDIDrv::SetDepthState( const DepthStateRHI* state )
{
}

_void GDIDrv::SetStencilState( const StencilStateRHI* state )
{
}

_void GDIDrv::SetBlendState( const BlendStateRHI* state )
{
}

_void GDIDrv::SetRasterizerState( const RasterizerStateRHI* state )
{

}

_void GDIDrv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{
	RasterizerStateRHIRef state = CreateRasterizerState( initializer );
	SetRasterizerState( state );
}

_void GDIDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureRHI* texture )
{
}

_void GDIDrv::SetViewport( const Viewport& viewport )
{
}

_void GDIDrv::SetViewport( const Viewport& viewport, const Ratio& ratio )
{
}

_void GDIDrv::SetScissorRect( _ubool enable, const RectU* rect )
{

}

_void GDIDrv::Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mGDIClearColor = color;
}

_void GDIDrv::DrawPoint( const Vector2& position, const Color& color ) 
{
}

_void GDIDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
}

_void GDIDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	DrawLine( start, end, color_start, width );
}

_void GDIDrv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
	DrawRectangle( RectF( ).InitWithPosition( (_float) rect.l, (_float) rect.t, (_float) rect.r, (_float) rect.b ), color, (_float) width );
}

_void GDIDrv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
}

_void GDIDrv::FillRectangle( const RectI& rect, const Color& color )
{
	FillRectangle( RectF( ).InitWithPosition( (_float) rect.l, (_float) rect.t, (_float) rect.r, (_float) rect.b ), color );
}

_void GDIDrv::FillRectangle( const RectF& rect, const Color& color )
{
}

_void GDIDrv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
}

_void GDIDrv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
}

_void GDIDrv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
}

_void GDIDrv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{

}

_void GDIDrv::DrawPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword offset, _dword number, _dword instances_number )
{
}

_void GDIDrv::DrawIndexedPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword start_index, _dword number, _dword instances_number )
{
}