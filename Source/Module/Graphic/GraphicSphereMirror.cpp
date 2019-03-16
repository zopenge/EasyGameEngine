//! @file     GraphicSphereMirror.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSphereMirror Implementation
//----------------------------------------------------------------------------

GraphicSphereMirror::GraphicSphereMirror( )
{
	mMirrorViewport = Viewport::cNull;
}

GraphicSphereMirror::~GraphicSphereMirror( )
{
}

_ubool GraphicSphereMirror::Initialize( const PointU& size )
{
	mCanvas = GetGraphicResourceManager( )->CreateCanvas( size.x, size.y, _GRAPHIC_SURFACE_ALL );
	if ( mCanvas.IsNull( ) )
		return _false;

	mMirrorViewport = Viewport( 0.0f, 0.0f, (_float) size.x, (_float) size.y, 0.0f, 1.0f );

	return _true;
}

_void GraphicSphereMirror::DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	EGE_ASSERT( effect != _null );

	// Create effect
	IGraphicEffectRef mirror_effect = GetGraphicResourceManager( )->CreateEffectFromEffect( effect, "_USE_REFLECT_BY_SPHERE_MIRROR_" );
	if ( mirror_effect.IsNull( ) )
		return;

	// Draw mesh geometry
	mCanvas->SetViewport( mMirrorViewport );
	mCanvas->DrawMeshGeometry( mirror_effect, geometry_info );
}

_GRAPHIC_MIRROR_TYPE GraphicSphereMirror::GetMirrorType( ) const
{
	return _GRAPHIC_MIRROR_SPHERE;
}

const PointU& GraphicSphereMirror::GetMirrorSize( ) const
{
	return mCanvas->GetSize( );
}

const Viewport& GraphicSphereMirror::GetMirrorViewport( ) const
{
	return mMirrorViewport;
}

IGraphicSceneView* GraphicSphereMirror::GetEnvironmentMapSceneView( )
{
	if ( mEnvironmentMapSceneView.IsNull( ) )
		mEnvironmentMapSceneView = new GraphicSceneView( );

	return mEnvironmentMapSceneView.GetPtr( );
}