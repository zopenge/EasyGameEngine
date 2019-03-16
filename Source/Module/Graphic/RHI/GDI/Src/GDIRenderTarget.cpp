//! @file     GDIRenderTarget.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIDrv-Surface Implementation
//----------------------------------------------------------------------------

SurfaceRHIPassRef GDIDrv::CreateTargetableSurface( Texture2DRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef GDIDrv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	return _null;
}

SurfaceRHIPassRef GDIDrv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	return new GDISurface( PointU( width, height ), CreateTexture2D( L"", width, height, format, 1, 0, _null ).GetPtr( ) );
}

const PointU& GDIDrv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GDIRESOURCE( Surface, surface );

	return gdi_surface->GetSize( );
}

Texture2DRHI* GDIDrv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GDIRESOURCE( Surface, surface );

	return _null;
}

TextureCubeRHI* GDIDrv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Surface, surface );

	return _null;
}

_ubool GDIDrv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	return _false;
}

_dword GDIDrv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	return -1;
}

//----------------------------------------------------------------------------
// GDISurface Implementation
//----------------------------------------------------------------------------

GDISurface::GDISurface( const PointU& size, Texture2DRHI* texture ) : mSize( size ), mTexture( texture )
{
	mCompatibleDC		= _null;
	mCompatibleBitmap	= _null;

	mGDIGraphics		= _null;
	mGDIPen				= _null;
	mGDISolidColorBrush = _null;
}

GDISurface::~GDISurface( )
{
	// Release pen
	if ( mGDIPen != _null )
		GDI::GdipDeletePen( mGDIPen );

	// Release solid color brush
	if ( mGDISolidColorBrush != _null )
		GDI::GdipDeleteBrush( mGDISolidColorBrush );

	// Release graphic
	if ( mGDIGraphics != _null )
		GDI::GdipDeleteGraphics( mGDIGraphics );

	// Release compatible bitmap
	if ( mCompatibleBitmap != _null )
		::DeleteObject( mCompatibleBitmap );

	// Release compatible DC
	if ( mCompatibleDC != _null )
		::DeleteDC( mCompatibleDC );
}

_ubool GDISurface::CreateCompatibleDC( HDC hdc )
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

	// Create graphic handle for compatible DC
	if ( GDI::GdipCreateFromHDC( mCompatibleDC, &mGDIGraphics ) != Gdiplus::Ok )
		return _false;

	return _true;
}

Gdiplus::GpPen* GDISurface::GetGDIPen( _float width, const Color& color )
{
	if ( mGDIPen != _null )
	{
		GDI::GdipSetPenWidth( mGDIPen, width );
		GDI::GdipSetPenColor( mGDIPen, (_dword) color );
		return mGDIPen;
	}

	// Create pen
	if ( GDI::GdipCreatePen1( (_dword) color, width, Gdiplus::UnitPixel, &mGDIPen ) != Gdiplus::Ok )
		return _null;

	return mGDIPen;
}

Gdiplus::GpSolidFill* GDISurface::GetGDISolidColorBrush( const Color& color )
{
	if ( mGDISolidColorBrush != _null )
	{
		GDI::GdipSetSolidFillColor( mGDISolidColorBrush, (_dword) color );
		return mGDISolidColorBrush;
	}

	// Create solid color brush
	if ( GDI::GdipCreateSolidFill( (_dword) color, &mGDISolidColorBrush ) != Gdiplus::Ok )
		return _null;

	return mGDISolidColorBrush;
}