//! @file     GraphicCanvas.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicCanvas Implementation
//----------------------------------------------------------------------------

GraphicCanvas::GraphicCanvas( )
{
	mSize						= PointU::cZeroPoint;

	mRenderTargetLockedPixels	= _null;
}

GraphicCanvas::~GraphicCanvas( )
{
}

_ubool GraphicCanvas::CheckSurfaces( IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) const
{
	if ( render_target == _null && depth_stencil == _null )
	{
		WLOG_ERROR( L"Render target and depth stencil both are null, to create canvas, you must provide at least one surface" );
		return _false;
	}

	if ( render_target != _null && depth_stencil != _null )
	{
		// Check the size of surfaces, all the surfaces must have the same size
		if ( render_target->GetSize( ) != depth_stencil->GetSize( ) )
		{
			WLOG_ERROR( L"Render target and depth stencil must be the same size" );
			return _false;
		}
	}

	return _true;
}

_ubool GraphicCanvas::Initialize( IGraphicSurface* render_target, IGraphicSurface* depth_stencil )
{
	// Create internal scene
	IGraphicSceneRef scene = GetGraphicResourceManager( )->CreateScene( );
	if ( scene.IsNull( ) )
		return _false;

	return Initialize( scene, render_target, depth_stencil );
}

_ubool GraphicCanvas::Initialize( IGraphicScene* scene, IGraphicSurface* render_target, IGraphicSurface* depth_stencil )
{
	// Check the surfaces
	if ( CheckSurfaces( render_target, depth_stencil ) == _false )
		return _false;

	// Set render target and depth stencil
	mRenderTarget = render_target;
	mDepthStencil = depth_stencil;

	// Set the canvas size
	mSize = mRenderTarget.IsValid( ) ? mRenderTarget->GetSize( ) : mDepthStencil->GetSize( );

	// Update scene and its size
	mScene = scene;
	if ( mScene.IsValid( ) )
		mScene->SetClientSize( mSize );

	return _true;
}

_void GraphicCanvas::PresentRenderBuffers( )
{
	mScene->PresentRenderBuffers( this );
}

_void GraphicCanvas::SetScene( IGraphicScene* scene )
{
	mScene = scene;
}

IGraphicScene* GraphicCanvas::GetScene( )
{
	return mScene;
}

const PointU& GraphicCanvas::GetSize( ) const
{
	return mSize;
}

IGraphicSurface* GraphicCanvas::GetRenderTarget( )
{
	return mRenderTarget;
}

IGraphicSurface* GraphicCanvas::GetDepthStencil( )
{
	return mDepthStencil;
}

_void* GraphicCanvas::LockRenderTarget( _dword& stride )
{
	EGE_ASSERT( mRenderTargetLockedPixels == _null );

	// Get the size of render target
	const PointU& size = mRenderTarget->GetSize( );

	// Get the pixel format
	_PIXEL_FORMAT pixel_format = mRenderTarget->GetTexture2D( )->GetPixelFormat( );

	// Feedback the stride in bytes
	switch ( pixel_format )
	{
		case _PF_A8R8G8B8:	stride = size.x * 4; break;
		case _PF_R8G8B8:	stride = size.x * 3; break;
		default:
			EGE_ASSERT( 0 );
			return _null;
	}

	// Bind the canvas
	GetDynamicRHI( )->SetRenderTarget( mRenderTarget->GetResource( ), mDepthStencil->GetResource( ) );

	// Allocate and read pixels buffer
	mRenderTargetLockedPixels = new _byte[stride * size.y];
	GetDynamicRHI( )->ReadPixels( RectU( 0, 0, size.x, size.y ), pixel_format, mRenderTargetLockedPixels );

	return mRenderTargetLockedPixels;
}

_void GraphicCanvas::UnlockRenderTarget( )
{
	EGE_ASSERT( mRenderTargetLockedPixels != _null );

	// Bind to the default FBO
	GetDynamicRHI( )->SetRenderTarget( _null, _null );

	// Free pixels buffer
	EGE_DELETE_ARRAY( mRenderTargetLockedPixels );
}

_void GraphicCanvas::SetViewportAndProjectionTransform( const PointU& client_size, IGraphicScene* scene )
{
	if ( scene == _null )
		return;

	// Set the client size
	SetClientSize( client_size );

	// Get the ratio and render size by it
	Ratio	ratio			= scene->GetClientRatio( );
	PointU	rendering_size	= ratio.UpdateSize( mSize.x, mSize.y );

	// Set the viewport by ratio
	Viewport viewport( ratio.mOffset.x, ratio.mOffset.y, (_float)rendering_size.x, (_float)rendering_size.y, 0.0f, 1.0f );
	SetViewport( viewport );

	// Get the source scene view
	IGraphicSceneView* scene_view = scene->GetSceneView( );
	EGE_ASSERT( scene_view != _null );

	// Set the projection transform
	_float aspect = EGE_RATIO( rendering_size.x, rendering_size.y );
	GetSceneView( )->SetProjectionTransform( aspect, scene_view->GetZNear( ), scene_view->GetZFar( ) );
	GetSceneView( )->SetFovY( scene_view->GetFovY( ) );
}