//! @file     GraphicBackSurface.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicBackSurface Implementation
//----------------------------------------------------------------------------

GraphicBackSurface::GraphicBackSurface( )
{
	mIsRendering		= _false;
	mOriginalClientSize = PointU::cZeroPoint;
	mRenderingSize		= PointU::cZeroPoint;
	mRenderingScale		= 1.0f;
}

GraphicBackSurface::~GraphicBackSurface( )
{
}

_void GraphicBackSurface::FinishRendering( )
{
	// Finished rendering
	mIsRendering = _false;

	// Resize the scene size
	mCanvas->GetScene( )->SetClientSize( mOriginalClientSize );

	// Reset the clear render buffers operations
	mCanvas->GetScene( )->ClearRenderBuffers( mClearBuffersInfo.mIsClearColor, mClearBuffersInfo.mClearColor, mClearBuffersInfo.mIsClearDepth, mClearBuffersInfo.mClearDepth, mClearBuffersInfo.mIsClearStencil, mClearBuffersInfo.mClearStencil );
}

_ubool GraphicBackSurface::Initialize( _dword canvas_width, _dword canvas_height )
{
	mCanvas = GetGraphicResourceManager( )->CreateCanvas( _null, canvas_width, canvas_height, _GRAPHIC_SURFACE_ALL );
	if ( mCanvas.IsNull( ) )
		return _false;

	mEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eTex0 ) );
	if ( mEffect.IsNull( ) )
		return _false;

	return _true;
}

_ubool GraphicBackSurface::IsRendering( ) const
{
	return mIsRendering;
}

IGraphicCanvas* GraphicBackSurface::GetCanvas( )
{
	return mCanvas;
}

PointU GraphicBackSurface::GetSize( ) const
{
	return mCanvas->GetSize( );
}

_void GraphicBackSurface::SetPrevClientSize( const PointU& size )
{
	mOriginalClientSize = size;
}

_void GraphicBackSurface::SetClearBuffersInfo( const GraphicClearBuffersInfo& info )
{
	mClearBuffersInfo = info;
}

_void GraphicBackSurface::SetRenderScale( _float scale )
{
	mRenderingScale = scale;
}

_float GraphicBackSurface::GetRenderScale( ) const
{
	return mRenderingScale;
}

_void GraphicBackSurface::BeginRender( IGraphicScene* scene )
{
	EGE_ASSERT( scene != _null );

	if ( mIsRendering )
	{
		// We are rendering in back surface now
		EGE_ASSERT( 0 );
		return;
	}

	// Save the previous client size
	mOriginalClientSize = scene->GetClientSize( );

	// Get the canvas size
	const PointU& canvas_size = mCanvas->GetSize( );

	// Get the viewport size
	_dword viewport_width	= (_dword) scene->GetViewport( ).w;
	_dword viewport_height	= (_dword) scene->GetViewport( ).h;

	// Get the size of back surface
	if ( viewport_width > canvas_size.x || viewport_height > canvas_size.y )
	{
		_dword width	= Math::Min( canvas_size.x, viewport_width );
		_dword height	= Math::Min( canvas_size.y, viewport_height );
		mRenderingSize	= scene->GetClientRatio( ).FixSizeU( PointU( width, height ) );
	}
	else
	{
		mRenderingSize	= PointU( viewport_width, viewport_height );
	}

	// Scale it
	mRenderingSize.x = (_dword)((_float)mRenderingSize.x * mRenderingScale);
	mRenderingSize.y = (_dword)((_float)mRenderingSize.y * mRenderingScale);

	// Set the scene
	mCanvas->SetScene( scene );

	// Update the device size
	Viewport back_surface_viewport( 0.0f, 0.0f, (_float) mRenderingSize.x, (_float) mRenderingSize.y, 0.0f, 1.0f );
	mCanvas->SetViewport( back_surface_viewport );

	// Clear render buffers
	mCanvas->ClearRenderBuffers( mClearBuffersInfo.mIsClearColor, mClearBuffersInfo.mClearColor, mClearBuffersInfo.mIsClearDepth, mClearBuffersInfo.mClearDepth, mClearBuffersInfo.mIsClearStencil, mClearBuffersInfo.mClearStencil );

	// Begin the back surface drawing
	mIsRendering = _true;
}

_void GraphicBackSurface::EndRender( )
{
	PresentRenderBuffers( );

	// Finished rendering
	FinishRendering( );

	// Draw to screen
	RenderToScene( mCanvas->GetScene( ) );
}

_void GraphicBackSurface::RenderToScene( IGraphicScene* scene )
{
	// Draw to screen
	RenderToScene( scene, mEffect );
}

_void GraphicBackSurface::RenderToScene( IGraphicScene* scene, IGraphicEffect* effect )
{
	// Get the back surface
	IGraphicSurface* back_surface = mCanvas->GetRenderTarget( );
	EGE_ASSERT( back_surface != _null );

	// Render to scene
	Vector2 size( ConvertPoint2Vector2( mOriginalClientSize ) );
	Vector2 uv1( 0.0f, EGE_RATIO( mRenderingSize.y, back_surface->GetSize( ).y ) );
	Vector2 uv2( EGE_RATIO( mRenderingSize.x, back_surface->GetSize( ).x ), 0.0f );
	scene->DrawSurface( Vector2::cOrigin, size, uv1, uv2, back_surface, effect );
}

_void GraphicBackSurface::PresentRenderBuffers( )
{
	if ( mIsRendering == _false )
	{
		// We are not in rendering back surface
		EGE_ASSERT( 0 );
		return;
	}

	// Present scene to canvas
	mCanvas->PresentRenderBuffers( );
}