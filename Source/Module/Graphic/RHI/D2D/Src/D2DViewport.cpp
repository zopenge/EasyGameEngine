//! @file     D2DViewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DDrv-Viewport Implementation
//----------------------------------------------------------------------------

ViewportRHIPassRef D2DDrv::CreateViewport( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Create viewport
	D2DViewport* viewport = new D2DViewport( );
	if ( viewport->Initialize( app_handle, size, device_size ) == _false )
		{ delete viewport; return _null; }

	return viewport;
}

_ubool D2DDrv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	DYNAMIC_CAST_D2DRESOURCE( Viewport, viewport );

	return d2d_viewport->Resize( size );
}

const PointU& D2DDrv::GetViewportSize( ViewportRHI* viewport ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Viewport, viewport );

	return PointU::cZeroPoint;
}

_void D2DDrv::BindViewport( ViewportRHI* viewport )
{
}

_void D2DDrv::Present( ViewportRHI* viewport, _ubool clear_caches )
{
}

//----------------------------------------------------------------------------
// D2DViewport Implementation
//----------------------------------------------------------------------------

D2DViewport::D2DViewport( )
{
	mWindowHandle	= _null;
	mWindowDC		= _null;

	mSize			= PointU::cZeroPoint;
}

D2DViewport::~D2DViewport( )
{
	mBackSurface.Clear( );

	// Release window DC
	if ( mWindowDC != _null && mWindowHandle != _null )
		ReleaseDC( mWindowHandle, mWindowDC );
}

_ubool D2DViewport::CreateBackSurface( )
{
	mBackSurface = gDynamicRHI->CreateTargetableSurface( mSize.x, mSize.y, _PF_A8R8G8B8 ).cast_static< D2DSurface >( );
	if ( mBackSurface.IsNull( ) )
		return _false;

	return _true;
}

_ubool D2DViewport::Initialize( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Get the window handle and DC
	mWindowHandle	= (HWND) app_handle;
	mWindowDC		= ::GetDC( mWindowHandle );
	if ( mWindowDC == _null )
		return _false;

	// Resize the viewport
	return Resize( size );
}

_ubool D2DViewport::Resize( const PointU& size )
{
	// The size must be different
	if ( mSize == size )
		return _true;

	// Update the size
	mSize = size;

	// Create a RHI surface to represent the viewport's back buffer.
	if ( mBackSurface == _null )
	{
		if ( CreateBackSurface( ) == _false )
			return _false;
	}

	// Bind the DC with region
	if ( mBackSurface->BindDC( mWindowDC, RectI( ).InitWithSize( 0, 0, mSize.x, mSize.y ) ) == _false )
		return _false;

	return _true;
}

D2DSurface* D2DViewport::GetBackSurface( )
{
	return mBackSurface;
}
