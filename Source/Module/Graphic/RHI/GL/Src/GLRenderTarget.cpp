//! @file     GLRenderTarget.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-Surface Implementation
//----------------------------------------------------------------------------

SurfaceRHIPassRef GLDrv::CreateTargetableSurface( Texture2DRHI* texture )
{
	return new GLSurface( texture );
}

SurfaceRHIPassRef GLDrv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	return new GLSurface( texture );
}

SurfaceRHIPassRef GLDrv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	if ( width == 0 || height == 0 )
		return _null;

	// Create 2D texture resource
	Texture2DRHIRef texture = CreateTexture2D( L"", width, height, format, 1, _null, _true );
	if ( texture.IsNull( ) )
		return _null;

	// Create target surface
	SurfaceRHIPassRef surface = CreateTargetableSurface( texture );
	if ( surface.IsNull( ) )
		return _null;

	return surface;
}

const PointU& GLDrv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GLRESOURCE( Surface, surface );

	return gl_surface->GetSize( );
}

Texture2DRHI* GLDrv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GLRESOURCE( Surface, surface );

	return gl_surface->GetTexture2D( );
}

TextureCubeRHI* GLDrv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GLRESOURCE( Surface, surface );

	return gl_surface->GetTextureCube( );
}

_ubool GLDrv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	DYNAMIC_CAST_GLRESOURCE( Surface, surface );

	gl_surface->SetFaceIndex( index );

	return _true;
}

_dword GLDrv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	DYNAMIC_CAST_GLRESOURCE( Surface, surface );

	return gl_surface->GetFaceIndex( );
}

//----------------------------------------------------------------------------
// GLSurface Implementation
//----------------------------------------------------------------------------

GLSurface::GLSurface( Texture2DRHI* texture ) : mTexture2D( texture )
{
	DYNAMIC_CAST_GLRESOURCE( Texture2D, texture );

	mRenderBufferResource	= 0;
	mFormat					= gl_texture->GetPixelFormat( );
	mSize					= gl_texture->GetSize( ); 

	mFaceIndex				= -1;
}

GLSurface::GLSurface( TextureCubeRHI* texture ) : mTextureCube( texture )
{
	DYNAMIC_CAST_GLRESOURCE( TextureCube, texture );

	mRenderBufferResource	= 0;
	mFormat					= gl_texture->GetPixelFormat( );
	mSize					= gl_texture->GetSize( ); 

	mFaceIndex				= 0;
}

GLSurface::GLSurface( GLuint resource, _PIXEL_FORMAT format, const PointU& size )
{
	mRenderBufferResource	= resource;
	mFormat					= format;
	mSize					= size; 

	mFaceIndex				= -1;
}

GLSurface::~GLSurface( )
{
	// Tell the cache system that surface will be released
	GLFramebufferCache::GetInstance( ).ReleaseFramebuffer( this );

	// Delete render buffer resource
	if ( mRenderBufferResource != 0 )
		GL_CHECK_ERROR( __glDeleteRenderbuffers( 1, &mRenderBufferResource ) );
}

GLuint GLSurface::GetResourceID( ) const
{
	if ( mRenderBufferResource != 0 )
	{
		return mRenderBufferResource;
	}
	else if ( mTexture2D.IsValid( ) )
	{
		const GLTexture2D* gl_texture = mTexture2D.cast_static< GLTexture2D >( );
		EGE_ASSERT( gl_texture != _null );

		return gl_texture->GetResource( );
	}
	else if ( mTextureCube.IsValid( ) )
	{
		const GLTextureCube* gl_texture = mTextureCube.cast_static< GLTextureCube >( );
		EGE_ASSERT( gl_texture != _null );

		return gl_texture->GetResource( );
	}

	return 0;
}
