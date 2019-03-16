//! @file     GraphicFlatMirror.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicFlatMirror Implementation
//----------------------------------------------------------------------------

GraphicFlatMirror::GraphicFlatMirror( )
{
	mAttenuationDistance		= 10.0f;

	mReflectionPlane			= Plane::cXYPlane;
	mReflectionPlaneTransform	= Matrix4::cIdentity;

	mMirrorViewport				= Viewport::cNull;
}

GraphicFlatMirror::~GraphicFlatMirror( )
{
}

_ubool GraphicFlatMirror::Initialize( const PointU& size )
{
	mCanvas = GetGraphicResourceManager( )->CreateCanvas( size.x, size.y, _GRAPHIC_SURFACE_ALL );
	if ( mCanvas.IsNull( ) )
		return _false;

	mMirrorViewport = Viewport( 0.0f, 0.0f, (_float) size.x, (_float) size.y, 0.0f, 1.0f );

	return _true;
}

_void GraphicFlatMirror::DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	EGE_ASSERT( effect != _null );

	// Build enable macros
	AString macros = "_USE_REFLECT_BY_FLAT_MIRROR_";
	if ( mAttenuationDistance != 0.0f )
		macros += "|_FLAT_MIRROR_ATTENUATION";

	// Create effect
	IGraphicEffectRef mirror_effect = GetGraphicResourceManager( )->CreateEffectFromEffect( effect, macros );
	if ( mirror_effect.IsNull( ) )
		return;

	// Build the geometry info
	GraphicMeshGeometryInfo new_geometry_info	= geometry_info;
	new_geometry_info.mModelTransform			= geometry_info.mModelTransform * mReflectionPlaneTransform;
	new_geometry_info.mMirrorReflectionPlane	= mReflectionPlane;
	new_geometry_info.mAABox					= geometry_info.mAABox * mReflectionPlaneTransform;

	// Update UBOs
	mirror_effect->SetUBO( ASTROBJ( uFlatMirrorPlane ), mReflectionPlane.ToVector4( ) );
	mirror_effect->SetUBO( ASTROBJ( uFlatMirrorAttenuationDistance ), mAttenuationDistance );

	// Draw mesh geometry
	mCanvas->SetViewport( mMirrorViewport );
	mCanvas->DrawMeshGeometry( mirror_effect, new_geometry_info );
}

_GRAPHIC_MIRROR_TYPE GraphicFlatMirror::GetMirrorType( ) const
{
	return _GRAPHIC_MIRROR_FLAT;
}

const PointU& GraphicFlatMirror::GetMirrorSize( ) const
{
	return mCanvas->GetSize( );
}

const Viewport& GraphicFlatMirror::GetMirrorViewport( ) const
{
	return mMirrorViewport;
}

_void GraphicFlatMirror::SetAttenuationDistance( _float distance )
{
	mAttenuationDistance = distance;
}

_float GraphicFlatMirror::GetAttenuationDistance( ) const
{
	return mAttenuationDistance;
}

_void GraphicFlatMirror::SetPlane( const Plane& plane )
{
	mReflectionPlane			= plane;
	mReflectionPlaneTransform	= plane.GetReflectionMatrix( );
}

const Plane& GraphicFlatMirror::GetPlane( ) const
{
	return mReflectionPlane;
}