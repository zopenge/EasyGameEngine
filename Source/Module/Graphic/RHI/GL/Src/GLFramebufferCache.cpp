//! @file     GLFramebufferCache.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLFramebufferCache Implementation
//----------------------------------------------------------------------------

GLFramebufferCache::GLFramebufferCache( )
{

}

GLFramebufferCache::~GLFramebufferCache( )
{

}

_void GLFramebufferCache::Clear( )
{
	mCache.Clear( );
}

GLFramebuffer* GLFramebufferCache::GetFramebuffer( GLSurface* rendertarget, GLSurface* depthstencil )
{
	// Convert the key of cache
	_qword key = BuildFBOKeyID( rendertarget, depthstencil );

	// Search for existing frame buffer object
	GLFramebufferData* old_cache = mCache.Search( key );
	if ( old_cache != _null )
	{
		GLFramebuffer& frame_buffer = old_cache->mFramebuffer;

		// Change the binding render target when using cube texture
		if ( rendertarget != _null && rendertarget->GetTextureCube( ) != _null )
			frame_buffer.AttachTextureCube( GL_COLOR_ATTACHMENT0, rendertarget->GetFaceIndex( ), rendertarget->GetResourceID( ) );

		return &frame_buffer;
	}

	// Create frame buffer object with render target and depth stencil target
	GLFramebufferData& cache	= mCache[ key ];
	cache.mRenderTarget 		= rendertarget;
	cache.mDepthStencil			= depthstencil;
	if ( cache.mFramebuffer.Initialize( ) == _false )
		return _null;

	// Get the frame buffer
	GLFramebuffer& frame_buffer = cache.mFramebuffer;

	// Attach render target
	if ( rendertarget != _null )
	{
		// It's texture 2D surface
		if ( rendertarget->GetTexture2D( ) != _null )
			frame_buffer.AttachTexture2D( GL_COLOR_ATTACHMENT0, rendertarget->GetResourceID( ) );
		// It's texture cube surface ( we use '0' here to let the frame buffer object create successful, we will change the index when hitting cache )
		else if ( rendertarget->GetTextureCube( ) != _null )
			frame_buffer.AttachTextureCube( GL_COLOR_ATTACHMENT0, 0, rendertarget->GetResourceID( ) );
	}
	else
	{
#if (_OPENGLES_ == 1)
		WLOG_ERROR( L"We must provide render target and depth or stencil both in OpenGLES mode" );
		return _null;
#else
		// No color output in the bound framebuffer, only depth.
		GL_CHECK_ERROR( __glDrawBuffer( GL_NONE ) );
		GL_CHECK_ERROR( __glReadBuffer( GL_NONE ) );
#endif
	}

	// Attach depth stencil target
	if ( depthstencil != _null )
	{
		switch ( depthstencil->GetFormat( ) )
		{
			case _PF_DEPTH_STENCIL:
			{
				frame_buffer.AttachTexture2D( GL_DEPTH_ATTACHMENT, depthstencil->GetResourceID( ) );
				frame_buffer.AttachTexture2D( GL_STENCIL_ATTACHMENT, depthstencil->GetResourceID( ) );
			}
			break;

			case _PF_SHADOW_DEPTH:
			{
				frame_buffer.AttachTexture2D( GL_DEPTH_ATTACHMENT, depthstencil->GetResourceID( ) );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	// Dump frame buffer info
	ALOG_TRACE( frame_buffer.DumpInfo( ).Str( ) );

	// Check the frame buffer state
	if ( GL_CHECK_FBO( frame_buffer.GetResource( ) ) == _false )
		return _null;

	return &frame_buffer;
}

_void GLFramebufferCache::ReleaseFramebuffer( GLSurface* surface )
{
	for ( GLFramebufferDataMap::Iterator it = mCache.GetHeadIterator( ); it.IsValid( ); )
	{
		GLFramebufferData& cache = ( (GLFramebufferDataMap::PairType&) it ).mObject2;

		if ( cache.mRenderTarget == surface || cache.mDepthStencil == surface )
		{
			GLPurgeFramebufferFromCaches( cache.mFramebuffer.GetResource( ) );
			it = mCache.Remove( it );
		}
		else
		{
			++ it;
		}
	}
}
