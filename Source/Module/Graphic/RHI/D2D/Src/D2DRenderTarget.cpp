//! @file     D2DRenderTarget.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DDrv-Surface Implementation
//----------------------------------------------------------------------------

SurfaceRHIPassRef D2DDrv::CreateTargetableSurface( Texture2DRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef D2DDrv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef D2DDrv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	// Initialize the render target properties
	D2D1_RENDER_TARGET_PROPERTIES properties;
	properties.type						= D2D1_RENDER_TARGET_TYPE_DEFAULT;
	properties.pixelFormat.format		= DXGI_FORMAT_B8G8R8A8_UNORM;
	properties.pixelFormat.alphaMode	= D2D1_ALPHA_MODE_IGNORE;
	properties.dpiX						= 0.0f;
	properties.dpiY						= 0.0f;
	properties.usage					= D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;
	properties.minLevel					= D2D1_FEATURE_LEVEL_DEFAULT;

	// Create D2D render target 
	RefPtr< ID2D1DCRenderTarget > rendertarget;
	if ( FAILED( mD2DFactory->CreateDCRenderTarget( &properties, &rendertarget.GetRawRef( ) ) ) )
		return _null;

	// Create surface
	return new D2DSurface( rendertarget, PointU( width, height ) );
}

const PointU& D2DDrv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Surface, surface );

	return d2d_surface->GetSize( );
}

Texture2DRHI* D2DDrv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Surface, surface );

	return _null;
}

TextureCubeRHI* D2DDrv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Surface, surface );

	return _null;
}

_ubool D2DDrv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	return _false;
}

_dword D2DDrv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	return -1;
}

//----------------------------------------------------------------------------
// D2DSurface Implementation
//----------------------------------------------------------------------------

D2DSurface::D2DSurface( ID2D1DCRenderTarget* rendertarget, const PointU& size ) : mD2DRenderTarget( rendertarget ), mSize( size )
{
	mCompatibleDC		= _null;
	mCompatibleBitmap	= _null;
}

D2DSurface::~D2DSurface( )
{
	// Release compatible bitmap
	if ( mCompatibleBitmap != _null )
		::DeleteObject( mCompatibleBitmap );

	// Release compatible DC
	if ( mCompatibleDC != _null )
		::DeleteDC( mCompatibleDC );
}

_ubool D2DSurface::CreateCompatibleDC( HDC hdc )
{
	if ( hdc == _null )
		return _false;

	// Create compatible DC
	mCompatibleDC = ::CreateCompatibleDC( hdc );
	if ( mCompatibleDC == _null )
		return _false;

	// Create compatible bitmap
	mCompatibleBitmap = ::CreateCompatibleBitmap( hdc, mSize.x, mSize.y );
	if ( mCompatibleBitmap == _null )
		return _false;

	// Bind bitmap with DC
	::SelectObject( mCompatibleDC, mCompatibleBitmap );

	// Bind the DC with region
	RECT rect = { 0, 0, (LONG) mSize.x, (LONG) mSize.y };
	if ( FAILED( mD2DRenderTarget->BindDC( mCompatibleDC, &rect ) ) )
		return _false;

	return _true;
}

_ubool D2DSurface::BindDC( HDC hdc, const RectI& rect )
{
	// Bind the DC with region
	if ( FAILED( mD2DRenderTarget->BindDC( hdc, (const RECT*) &rect ) ) )
		return _false;

	return _true;
}

ID2D1SolidColorBrush* D2DSurface::GetD2DSolidColorBrush( const Color& color )
{
	if ( mD2DSolidColorBrush.IsValid( ) )
	{
		mD2DSolidColorBrush->SetColor( D2DDrv::TranslateD2DColorF( color ) );
		return mD2DSolidColorBrush;
	}

	if ( FAILED( mD2DRenderTarget->CreateSolidColorBrush( D2DDrv::TranslateD2DColorF( color ), &mD2DSolidColorBrush.GetRawRef( ) ) ) )
		return _null;

	return mD2DSolidColorBrush;
}
