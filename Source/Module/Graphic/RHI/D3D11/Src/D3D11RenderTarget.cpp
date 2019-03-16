//! @file     D3D11RenderTarget.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Surface Implementation
//----------------------------------------------------------------------------

SurfaceRHIPassRef D3D11Drv::CreateTargetableSurface( Texture2DRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef D3D11Drv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef D3D11Drv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	_ubool depth_format = 
		format == _PF_DEPTH_STENCIL || 
		format == _PF_SHADOW_DEPTH || 
		format == _PF_FILTERED_SHADOW_DEPTH || 
		format == _PF_D24;

	// Initialize texture description for surface
	D3D11_TEXTURE2D_DESC desc;
	desc.Width				= width;
	desc.Height				= height;
	desc.MipLevels			= 1;
	desc.ArraySize			= 1;
	desc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count	= 1;
	desc.SampleDesc.Quality	= 0;
	desc.Usage				= D3D11_USAGE_DEFAULT;
	desc.BindFlags			= depth_format ? D3D11_BIND_DEPTH_STENCIL : D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags		= 0;
	desc.MiscFlags			= 0;

	// Create surface
	RefPtr< ID3D11Texture2D > surface_resource;
	if ( FAILED( mDevice->CreateTexture2D( &desc, _null, &surface_resource.GetRawRef( ) ) ) )
		return _null;

	// The type of surface
	D3D11Surface::_TYPE surface_type = D3D11Surface::_TYPE_UNKNOWN;

	// The view of render target or depth stencil
	RefPtr< ID3D11View > d3d_view;

	// Create either a render target view or depth stencil view for the surface
	if ( depth_format )
	{
		surface_type = D3D11Surface::_TYPE_RENDER_TARGET;

		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencil_desc;
		depthstencil_desc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstencil_desc.ViewDimension			= D3D11_DSV_DIMENSION_TEXTURE2D;
		depthstencil_desc.Texture2D.MipSlice	= 0;

		RefPtr< ID3D11DepthStencilView > depthstencil_view;
		if ( FAILED( mDevice->CreateDepthStencilView( surface_resource.GetPtr( ), &depthstencil_desc, &depthstencil_view.GetRawRef( ) ) ) )
			return _null;

		d3d_view = depthstencil_view;
	}
	else
	{
		surface_type = D3D11Surface::_TYPE_DEPTH_STENCIL;

		D3D11_TEXTURE2D_DESC resolvetarget_desc;
		surface_resource->GetDesc( &resolvetarget_desc );

		D3D11_RENDER_TARGET_VIEW_DESC rendertarget_desc;
		rendertarget_desc.Format				= resolvetarget_desc.Format;
		rendertarget_desc.ViewDimension			= D3D11_RTV_DIMENSION_TEXTURE2D;
		rendertarget_desc.Texture2D.MipSlice	= 0;

		RefPtr< ID3D11RenderTargetView > rendertarget_view;
		if ( FAILED( mDevice->CreateRenderTargetView( surface_resource.GetPtr( ), &rendertarget_desc, &rendertarget_view.GetRawRef( ) ) ) )
			return _null;

		d3d_view = rendertarget_view;
	}

	// Create surface
	return new D3D11Surface( surface_type, PointU( width, height ), d3d_view, surface_resource );
}

const PointU& D3D11Drv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D3D11RESOURCE( Surface, surface );

	return d3d_surface->GetSize( );
}

Texture2DRHI* D3D11Drv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D3D11RESOURCE( Surface, surface );

	return _null;
}

TextureCubeRHI* D3D11Drv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Surface, surface );

	return _null;
}

_ubool D3D11Drv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	return _false;
}

_dword D3D11Drv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	return -1;
}

//----------------------------------------------------------------------------
// D3D11Surface Implementation
//----------------------------------------------------------------------------

D3D11Surface::D3D11Surface( _TYPE type, const PointU& size, ID3D11View* view, ID3D11Texture2D* texture )
	: mType( type ), mSize( size ), mViewResource( view ), mResolveTargetResource( texture )
{
	mTexture = new D3D11Texture2D( texture );
}

D3D11Surface::~D3D11Surface( )
{
	EGE_RELEASE( mTexture );
}