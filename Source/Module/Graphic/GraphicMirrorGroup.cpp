//! @file     GraphicMirrorGroup.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicMirrorGroup Implementation
//----------------------------------------------------------------------------

GraphicMirrorGroup::GraphicMirrorGroup( )
{
}

GraphicMirrorGroup::~GraphicMirrorGroup( )
{
	for ( MirrorInfoMap::Iterator it = mMirrors.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		MirrorInfoArray& mirrors = it.GetObject( );

		for ( _dword i = 0; i < mirrors.Number( ); i ++ )
		{
			EGE_DELETE( mirrors[i] );
		}
	}
}

GraphicMirrorGroup::MirrorInfo* GraphicMirrorGroup::CreateMirrorInfo( MirrorInfoArray& mirrors, IGraphicMirror* mirror )
{
	MirrorInfo* mirror_info	= new MirrorInfo( );
	mirror_info->mEnabled	= _true;
	mirror_info->mMirror	= mirror;
	mirrors.Append( mirror_info );

	return mirror_info;
}

GraphicMirrorGroup::MirrorInfo* GraphicMirrorGroup::GetFlatMirrorInfo( const Plane& plane, _dword mirror_size )
{
	// Build mirror size
	PointU size( mirror_size, mirror_size );

	// Try to use the existing flat mirror
	MirrorInfoArray& mirrors = mMirrors[_GRAPHIC_MIRROR_FLAT];
	for ( _dword i = 0; i < mirrors.Number( ); i ++ )
	{
		MirrorInfo* mirror_info = mirrors[i];
		EGE_ASSERT( mirror_info != _null );

		IGraphicFlatMirror* mirror = mirror_info->mMirror.cast_static< IGraphicFlatMirror >( );
		EGE_ASSERT( mirror != _null );

		if ( mirror->GetMirrorSize( ) != size )
			continue;

		if ( mirror->GetPlane( ).IsEqual( plane, 5.0f ) == _false )
			continue;;

		// Enable mirror to render
		mirror_info->mEnabled = _true;

		return mirror_info;
	}

	// Create flat mirror
	IGraphicFlatMirrorRef mirror = GetGraphicResourceManager( )->CreateFlatMirror( size, plane );
	if ( mirror.IsNull( ) )
		return _null;

	// Build mirror info
	return CreateMirrorInfo( mirrors, mirror );
}

GraphicMirrorGroup::MirrorInfo* GraphicMirrorGroup::GetSphereMirrorInfo( _dword mirror_size )
{
	// Build mirror size
	PointU size( mirror_size, mirror_size );

	// Create sphere mirror
	IGraphicSphereMirrorRef mirror = GetGraphicResourceManager( )->CreateSphereMirror( size );
	if ( mirror.IsNull( ) )
		return _null;

	// Build mirror info
	return CreateMirrorInfo( mMirrors[_GRAPHIC_MIRROR_SPHERE], mirror );
}

_ubool GraphicMirrorGroup::AddFlatMirrorFromGeometry( IGraphicSceneView* scene_view, const Plane& plane, _dword mirror_size, GraphicGeometry& geometry )
{
	MirrorInfo* mirror_info = GetFlatMirrorInfo( plane, mirror_size );
	if ( mirror_info == _null )
		return _false;

	IGraphicSceneView* mirror_scene_view = mirror_info->mMirror->GetSceneView( );
	EGE_ASSERT( mirror_scene_view != _null );

	mirror_scene_view->SetCameraAndProjectionTransform( scene_view->GetCamera( ), scene_view->GetAspect( ), scene_view->GetZNear( ), scene_view->GetZFar( ) );

	geometry.AppendTexture( ASTROBJ( uFlatMirrorTex ), mirror_info->mMirror->GetRenderTarget( )->GetTexture2D( ) );

	return _true;
}

_ubool GraphicMirrorGroup::AddSphereMirrorFromGeometry( _dword mirror_size, GraphicGeometry& geometry )
{
	MirrorInfo* mirror_info = GetSphereMirrorInfo( mirror_size );
	if ( mirror_info == _null )
		return _false;

	IGraphicSphereMirror* mirror = mirror_info->mMirror.cast_static< IGraphicSphereMirror >( );
	EGE_ASSERT( mirror != _null );

	IGraphicSceneView* env_scene_view = mirror->GetEnvironmentMapSceneView( );
	EGE_ASSERT( env_scene_view != _null );

	mirror->GetSceneView( )->SetCameraAndProjectionTransform( env_scene_view->GetCamera( ), env_scene_view->GetAspect( ), env_scene_view->GetZNear( ), env_scene_view->GetZFar( ) );

	geometry.AppendTexture( ASTROBJ( uSphereMirrorTex ), mirror_info->mMirror->GetRenderTarget( )->GetTexture2D( ) );

	return _true;
}

_void GraphicMirrorGroup::RenderGeometryInMirrors( IGraphicSceneView* scene_view, IGraphicEffect* effect, _dword mirror_reflect_type, GraphicGeometry& geometry )
{
	for ( MirrorInfoMap::Iterator it = mMirrors.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		MirrorInfoArray& mirrors = it.GetObject( );

		for ( _dword i = 0; i < mirrors.Number( ); i ++ )
		{
			MirrorInfo* mirror_info = mirrors[i];
			EGE_ASSERT( mirror_info != _null );

			if ( mirror_info->mEnabled == _false )
				continue;

			IGraphicMirror* mirror = mirror_info->mMirror;
			EGE_ASSERT( mirror != _null );

			if ( mirror->GetMirrorType( ) & mirror_reflect_type )
				mirror->DrawMeshGeometry( effect, geometry.GetGeometryInfo( ) );
		}
	}
}

_void GraphicMirrorGroup::PresentMirrors( )
{
	for ( MirrorInfoMap::Iterator it = mMirrors.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		MirrorInfoArray& mirrors = it.GetObject( );

		for ( _dword i = 0; i < mirrors.Number( ); i ++ )
		{
			MirrorInfo* mirror_info = mirrors[i];
			EGE_ASSERT( mirror_info != _null );

			if ( mirror_info->mEnabled == _false )
				continue;

			IGraphicMirror* mirror = mirror_info->mMirror;
			EGE_ASSERT( mirror != _null );

			mirror->ClearRenderBuffers( _true, Color::cNull, _true, 1.0f, _true, 0 );
			mirror->PresentRenderBuffers( );

			mirror_info->mEnabled = _false;
		}
	}
}
