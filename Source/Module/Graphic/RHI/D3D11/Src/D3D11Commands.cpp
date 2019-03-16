//! @file     D3D11Commands.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Commands Implementation
//----------------------------------------------------------------------------

_void D3D11Drv::SetLineWidth( _float width )
{

}

_void D3D11Drv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
	DYNAMIC_CAST_D3D11RESOURCE( Surface, rendertarget );
	DYNAMIC_CAST_D3D11RESOURCE( Surface, depthstencil );

	// Get the render target and stencil depth view
	ID3D11RenderTargetView* rendertarget_view = _null;
	ID3D11DepthStencilView* depthstencil_view = _null;
	if ( d3d_rendertarget != _null )
		rendertarget_view = d3d_rendertarget->GetRenderTargetView( );
	if ( d3d_depthstencil != _null )
		depthstencil_view = d3d_depthstencil->GetDepthStencilView( );

	// Set the render targets
	mDeviceContext->OMSetRenderTargets( 1, &rendertarget_view, depthstencil_view );
}

_void D3D11Drv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{

}

_void D3D11Drv::SetBoundShader( BoundShaderRHI* shader )
{
}

_void D3D11Drv::SetDepthState( const DepthStateRHI* state )
{
}

_void D3D11Drv::SetStencilState( const StencilStateRHI* state )
{
}

_void D3D11Drv::SetBlendState( const BlendStateRHI* state )
{
}

_void D3D11Drv::SetRasterizerState( const RasterizerStateRHI* state )
{

}

_void D3D11Drv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{

}

_void D3D11Drv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureRHI* texture )
{

}

_void D3D11Drv::SetViewport( const Viewport& viewport )
{
	if ( viewport.w > 0 && viewport.h > 0 )
		mDeviceContext->RSSetViewports( 1, (const D3D11_VIEWPORT*) &viewport );
}

_void D3D11Drv::SetViewport( const Viewport& viewport, const Ratio& ratio )
{
}

_void D3D11Drv::SetScissorRect( _ubool enable, const RectU* rect )
{

}

_void D3D11Drv::Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	// Get the render target and depth stencil view of device
	RefPtr< ID3D11RenderTargetView > rendertarget_view;
	RefPtr< ID3D11DepthStencilView > depthstencil_view;
	mDeviceContext->OMGetRenderTargets( 1, &rendertarget_view.GetRawRef( ), &depthstencil_view.GetRawRef( ) );

	// Clear color buffer
	if ( clearcolor && rendertarget_view.IsValid( ) )
		mDeviceContext->ClearRenderTargetView( rendertarget_view.GetPtr( ), (const _float*) &color );

	// Clear depth and stencil buffer
	if ( cleardepth && depthstencil_view.IsValid( ) )
	{
		_dword clear_flags = D3D11_CLEAR_DEPTH;
		if ( clearstencil )
			clear_flags |= D3D11_CLEAR_STENCIL;

		mDeviceContext->ClearDepthStencilView( depthstencil_view.GetPtr( ), clear_flags, depth, (UINT8) stencil );
	}
}

_void D3D11Drv::DrawPoint( const Vector2& position, const Color& color ) 
{
}

_void D3D11Drv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
}

_void D3D11Drv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
}

_void D3D11Drv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
}

_void D3D11Drv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
}

_void D3D11Drv::FillRectangle( const RectI& rect, const Color& color )
{
}

_void D3D11Drv::FillRectangle( const RectF& rect, const Color& color )
{
}

_void D3D11Drv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
}

_void D3D11Drv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
	//	DYNAMIC_CAST_GDIRESOURCE( Font, font );
}

_void D3D11Drv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
}

_void D3D11Drv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{

}

_void D3D11Drv::DrawPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword offset, _dword number, _dword instances_number )
{
}

_void D3D11Drv::DrawIndexedPrimitiveInstanced( _PRIMITIVE_TYPE type, _dword start_index, _dword number, _dword instances_number )
{
}