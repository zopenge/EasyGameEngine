//! @file     GraphicViewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicViewport Implementation
//----------------------------------------------------------------------------

GraphicViewport::GraphicViewport( ViewportRHI* viewport_rhi ) 
{
	mViewportRHI	= viewport_rhi;

	mBackSurface	= &NullGraphic::GetInstance( ).GetGraphicBackSurface( );
}

GraphicViewport::~GraphicViewport( )
{
	mBackSurface.Clear( );

	mScene.Clear( );

	mViewportRHI.Clear( );
}

_ubool GraphicViewport::Initialize( )
{
	// Create scene
	mScene = GetGraphicResourceManager( )->CreateScene( );
	if ( mScene.IsNull( ) )
		return _false;

	// Resize the scene size
	mScene->SetClientSize( gDynamicRHI->GetViewportSize( mViewportRHI ) );

	return _true;
}

_void GraphicViewport::SetViewport( const Viewport& viewport )
{
	mScene->SetViewport( viewport );
}

const Viewport& GraphicViewport::GetViewport( ) const
{
	return mScene->GetViewport( );
}

_void GraphicViewport::SetClientSize( const PointU& size )
{
	// Skip for same client size
	if ( mScene->GetClientSize( ) == size )
		return;

	// Update back surface previous size, because we need to syn it
	mBackSurface->SetPrevClientSize( size );

	// Update client size
	mScene->SetClientSize( size );

	// Resize the viewport resource
	gDynamicRHI->ResizeViewport( mViewportRHI, mScene->GetViewport( ).GetSize( ) );

	WLOG_TRACE_2( L"Resize client size to (%dx%d)", size.x, size.y );
}

const PointU& GraphicViewport::GetClientSize( ) const
{
	return mScene->GetClientSize( );
}

const Ratio& GraphicViewport::GetClientRatio( ) const
{
	return mScene->GetClientRatio( );
}

_void GraphicViewport::FlushBuffers( )
{
	mScene->FlushBuffers( );
}

_void GraphicViewport::ClearCaches( ) 
{
	mScene->ClearCaches( );
}

const Matrix4& GraphicViewport::GetViewTransform( ) const 
{
	return mScene->GetViewTransform( );
}

const Matrix4& GraphicViewport::GetVPTransform( ) const 
{
	return mScene->GetVPTransform( );
}

_void GraphicViewport::ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	// Save the clear buffer operations
	mClearBuffersInfo.mIsClearColor		= clearcolor;
	mClearBuffersInfo.mClearColor		= color;
	mClearBuffersInfo.mIsClearDepth		= cleardepth;
	mClearBuffersInfo.mClearDepth		= depth;
	mClearBuffersInfo.mIsClearStencil	= clearstencil;
	mClearBuffersInfo.mClearStencil		= stencil;

	// Syn with back surface
	mBackSurface->SetClearBuffersInfo( mClearBuffersInfo );

	// Clear it
	mScene->ClearRenderBuffers( clearcolor, color, cleardepth, depth, clearstencil, stencil );
}

_void GraphicViewport::PresentRenderBuffers( )
{
	// Present back surface
	if ( mBackSurface->IsRendering( ) )
		mBackSurface->PresentRenderBuffers( );
	else
		mScene->PresentRenderBuffers( );
}

_void GraphicViewport::PresentRenderBuffers( IGraphicCanvas* canvas )
{
	mScene->PresentRenderBuffers( canvas );
}

_void GraphicViewport::SetSceneView( IGraphicSceneView* view )
{
	mScene->SetSceneView( view );
}

IGraphicSceneView* GraphicViewport::GetSceneView( ) const
{
	return mScene->GetSceneView( );
}

const Viewport* GraphicViewport::GetLastViewport( ) 
{
	return mScene->GetLastViewport( );
}

_ubool GraphicViewport::PickMeshes( const Ray& ray, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return mScene->PickMeshes( ray, bound_box_only, meshes );
}

_ubool GraphicViewport::PickMeshes( const AxisAlignedBox& box, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return mScene->PickMeshes( box, bound_box_only, meshes );
}

IGraphicMeshPassRef	GraphicViewport::AddMesh( IGeometryMeshChunk* mesh_chunk )
{
	return mScene->AddMesh( mesh_chunk );
}

Vector2 GraphicViewport::Convert3DTo2D( const Vector3& point, _float* zsort )
{
	return mScene->Convert3DTo2D( point, zsort );
}

Vector2 GraphicViewport::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return mScene->Convert3DTo2D( size, point, zsort );
}

Ray GraphicViewport::GetPickRay( _int x, _int y )
{
	return mScene->GetPickRay( x, y );
}

Ray GraphicViewport::GetPickRay( const PointU& size, _int x, _int y )
{
	return mScene->GetPickRay( size, x, y );
}

_void GraphicViewport::BeginBackSurfaceRendering( _float scale )
{
	mBackSurface->SetRenderScale( scale );
	mBackSurface->BeginRender( mScene );
}

_void GraphicViewport::EndBackSurfaceRendering( )
{
	if ( mBackSurface->IsRendering( ) == _false )
		return;

	mBackSurface->EndRender( );
}

_void GraphicViewport::ClearBackSurface( )
{
	mBackSurface = &NullGraphic::GetInstance( ).GetGraphicBackSurface( );
}

_ubool GraphicViewport::CreateBackSurface( const PointU& size )
{
	if ( mBackSurface->GetSize( ) != size )
	{
		// Create back surface
		GraphicBackSurface* back_suface = new GraphicBackSurface( );
		if ( back_suface->Initialize( size.x, size.y ) == _false )
			{ EGE_RELEASE( back_suface ); return _false; }

		mBackSurface = back_suface;
		mBackSurface->Release( );
	}

	return _true;
}

IGraphicBackSurface* GraphicViewport::GetBackSurface( )
{
	return mBackSurface;
}

_void GraphicViewport::Bind( )
{
	gDynamicRHI->BindViewport( mViewportRHI );
}

_void GraphicViewport::Present( )
{
	// Present VR device
	gGraphicVRDevice->Present( );

	// Present render buffers
	mScene->PresentRenderBuffers( );

	// Reset the clear render buffers
	mClearBuffersInfo.Reset( );

	// Swap buffers
	gDynamicRHI->Present( mViewportRHI );
}

_void GraphicViewport::SetSceneProxy( IGraphicScene* scene )
{
	if ( scene == _null )
		return;

	mScene = scene;
}

IGraphicScene* GraphicViewport::GetSceneProxy( )
{
	return mScene;
}