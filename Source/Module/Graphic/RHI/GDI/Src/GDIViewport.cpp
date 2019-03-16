//! @file     GDIViewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIDrv-Viewport Implementation
//----------------------------------------------------------------------------

ViewportRHIPassRef GDIDrv::CreateViewport( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Create viewport
	GDIViewport* viewport = new GDIViewport( );
	if ( viewport->Initialize( app_handle, size, device_size ) == _false )
		{ delete viewport; return _null; }

	return viewport;
}

_ubool GDIDrv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	DYNAMIC_CAST_GDIRESOURCE( Viewport, viewport );

	return gdi_viewport->Resize( size );
}

const PointU& GDIDrv::GetViewportSize( ViewportRHI* viewport ) const
{
	DYNAMIC_CAST_GDIRESOURCE( Viewport, viewport );

	return PointU::cZeroPoint;
}

_void GDIDrv::BindViewport( ViewportRHI* viewport )
{
}

_void GDIDrv::Present( ViewportRHI* viewport, _ubool clear_caches )
{
}

//----------------------------------------------------------------------------
// GDIViewport Implementation
//----------------------------------------------------------------------------

GDIViewport::GDIViewport( )
{
	mWindowHandle	= _null;
	mWindowDC		= _null;

	mSize			= PointU::cZeroPoint;
}

GDIViewport::~GDIViewport( )
{
	mBackSurface.Clear( );

	// Release window DC
	if ( mWindowDC != _null && mWindowHandle != _null )
		ReleaseDC( mWindowHandle, mWindowDC );
}

_ubool GDIViewport::CreateBackSurface( )
{
	// Create the back surface
	mBackSurface = gDynamicRHI->CreateTargetableSurface( mSize.x, mSize.y, _PF_A8R8G8B8 ).cast_static< GDISurface >( );
	if ( mBackSurface.IsNull( ) )
		return _false;

	// Create the compatible DC
	if ( mBackSurface->CreateCompatibleDC( mWindowDC ) == _false )
		return _false;

	return _true;
}

_ubool GDIViewport::Initialize( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Get the window handle and DC
	mWindowHandle	= (HWND) app_handle;
	mWindowDC		= GetDC( mWindowHandle );
	if ( mWindowDC == _null )
		return _false;

	// Resize the viewport
	return Resize( size );
}

_ubool GDIViewport::Resize( const PointU& size )
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

	return _true;
}

_ubool GDIViewport::BeginDrawing( )
{
	GDIDrv* gdi_drv = static_cast< GDIDrv* >( gDynamicRHI );
	EGE_ASSERT( gdi_drv != _null );

	// Begin to draw
	GDI::GdipGraphicsClear( mBackSurface->GetGDIGraphics( ), (_dword) gdi_drv->GetGDIClearColor( ) );

	// Set the render target and viewport
	gDynamicRHI->SetRenderTarget( _null, _null );
	gDynamicRHI->SetViewport( Viewport( 0.0f, 0.0f, (_float) mSize.x, (_float) mSize.y, 0.0f, 1.0f ) );

	return _true;
}

_void GDIViewport::EndDrawing( )
{
}

_void GDIViewport::Present( )
{
	// Initialize the blend function
	BLENDFUNCTION blend;
	blend.BlendOp				= AC_SRC_OVER;
	blend.BlendFlags			= 0;
	blend.AlphaFormat			= AC_SRC_ALPHA;
	blend.SourceConstantAlpha	= 255;

	// Present window with alpha blending
	POINT src = { 0, 0 }; SIZE size = { (LONG) mSize.x, (LONG) mSize.y };
	::UpdateLayeredWindow( mWindowHandle, mWindowDC, _null, &size, mBackSurface->GetCompatibleDC( ), &src, 0, &blend, ULW_ALPHA );

	//{
	//	::BitBlt( mWindowDC, 0, 0, mSize.x, mSize.y, mBackSurface->GetCompatibleDC( ), 0, 0, SRCCOPY );
	//}
}

GDISurface* GDIViewport::GetBackSurface( )
{
	return mBackSurface;
}
