//! @file     GraphicSurface.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSurface Implementation
//----------------------------------------------------------------------------

GraphicSurface::GraphicSurface( )
{
}

GraphicSurface::~GraphicSurface( )
{
}

_ubool GraphicSurface::Initialize( SurfaceRHI* resource )
{
	if ( resource == _null )
		return _false;

	mResource = resource;

	// Create assistants of textures
	mTexture2D		= GetGraphicResourceManager( )->CreateTexture2D( gDynamicRHI->GetSurfaceTexture2D( mResource ) );
	mTextureCube	= GetGraphicResourceManager( )->CreateTextureCube( gDynamicRHI->GetSurfaceTextureCube( mResource ) );

	return _true;
}

SurfaceRHI* GraphicSurface::GetResource( )
{
	return mResource;
}

const PointU& GraphicSurface::GetSize( ) const
{
	return gDynamicRHI->GetSurfaceSize( mResource.GetPtr( ) );
}

_dword GraphicSurface::GetTexture2DResID( ) const
{
	if ( mTexture2D.IsNull( ) )
		return 0;

	_dword tex_id = gDynamicRHI->GetTexture2DResID( mTexture2D->GetResource( ) );
	return tex_id;
}

IGraphicTexture2D* GraphicSurface::GetTexture2D( ) const
{
	return mTexture2D.GetPtr( );
}

IGraphicTextureCube* GraphicSurface::GetTextureCube( ) const
{
	return mTextureCube.GetPtr( );
}

_ubool GraphicSurface::SetFaceIndex( _dword index )
{
	return GetDynamicRHI( )->SetSurfaceTextureCubeFaceIndex( mResource, index );
}

_dword GraphicSurface::GetFaceIndex( ) const
{
	return GetDynamicRHI( )->GetSurfaceTextureCubeFaceIndex( mResource.GetPtr( ) );
}

_ubool GraphicSurface::SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b )
{
	return mTexture2D->SaveToFile( fileformat, filename, is_vert_flip, swap_r_and_b );
}