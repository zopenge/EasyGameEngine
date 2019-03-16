//! @file     GLContextIOS.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//!	The context handle
struct GLContext::Handle
{
	//!	The frame buffer
	GLuint	mFramebuffer;
	//!	The color render buffer
	GLuint	mColorRenderbuffer;
	//!	The depth render buffer
	GLuint	mDepthRenderBuffer;

	//!	The GL context
	_handle	mGLContext;
	//! The core animation layer handle
	_handle	mGLLayer;

	Handle( )
	{
		mFramebuffer		= 0;
		mColorRenderbuffer	= 0;
		mDepthRenderBuffer	= 0;

		mGLContext			= _null;
		mGLLayer			= _null;
	}
	~Handle( )
	{
		if ( mDepthRenderBuffer )
			GL_CHECK_ERROR( __glDeleteRenderbuffers( 1, &mDepthRenderBuffer ) );

		if ( mColorRenderbuffer )
			GL_CHECK_ERROR( __glDeleteRenderbuffers( 1, &mColorRenderbuffer ) );

		if ( mFramebuffer )
			GL_CHECK_ERROR( __glDeleteFramebuffers( 1, &mFramebuffer ) );

		ReleaseGLContext( mGLContext );
	}
};

//----------------------------------------------------------------------------
// GLContext Implementation
//----------------------------------------------------------------------------

GLContext::GLContext( )
{
	mHandle = _null;
}

GLContext::~GLContext( )
{
	Finalize( );
}

_ubool GLContext::Initialize( _handle app_handle )
{
	mHandle = new Handle( );

	// Use the application handle as core animation layer
	mHandle->mGLLayer = app_handle;

	// Create GL context
	mHandle->mGLContext = CreateGLContext( app_handle );
	if ( mHandle->mGLContext == _null )
		return _false;

	// Create color render buffer
	GL_CHECK_ERROR( __glGenRenderbuffers( 1, &mHandle->mColorRenderbuffer ) );
	GL_CHECK_ERROR( __glBindRenderbuffer( GL_RENDERBUFFER, mHandle->mColorRenderbuffer ) );

    // Allocate color buffer backing based on the current layer size
    NS_RenderbufferStorage( mHandle->mGLContext, app_handle );

    // Get render buffer size
    GLint width = 0, height = 0;
    GL_CHECK_ERROR( __glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width ) );
    GL_CHECK_ERROR( __glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height ) );

    // Create depth render buffer
	GL_CHECK_ERROR( __glGenRenderbuffers( 1, &mHandle->mDepthRenderBuffer ) );
	GL_CHECK_ERROR( __glBindRenderbuffer( GL_RENDERBUFFER, mHandle->mDepthRenderBuffer ) );
	GL_CHECK_ERROR( __glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, width, height ) );

    // Create frame buffer
    GL_CHECK_ERROR( __glGenFramebuffers( 1, &mHandle->mFramebuffer ) );
    GL_CHECK_ERROR( __glBindFramebuffer( GL_FRAMEBUFFER, mHandle->mFramebuffer ) );

    // Bind FBO with buffers
	GL_CHECK_ERROR( __glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mHandle->mColorRenderbuffer ) );
	GL_CHECK_ERROR( __glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mHandle->mDepthRenderBuffer ) );
	GL_CHECK_ERROR( __glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mHandle->mDepthRenderBuffer ) );

    // Check FBO status
    _dword status = __glCheckFramebufferStatus( GL_FRAMEBUFFER );
	if ( status != GL_FRAMEBUFFER_COMPLETE )
	{
		WLOG_ERROR_1( L"Create IOS GL frame buffer failed, error:0x%.8x", status );
		return _false;
	}

    // Gather OpenGL info
	GLDrv::GatherInfo( );
    
    return _true;
}

_void GLContext::Finalize( )
{
	EGE_DELETE( mHandle );
}

_handle GLContext::GetContext( ) const
{
	return mHandle->mGLContext;
}

_void GLContext::Bind( )
{
	// Bind the default frame buffer
	GLCachedBindFBO( mHandle->mFramebuffer );

	// Bind the color render buffer
	GLCachedBindRBO( mHandle->mColorRenderbuffer );
}

_void GLContext::Present( )
{
	FlushGLBuffers( mHandle->mGLContext );
}

_void GLContext::SetVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
}

PointU GLContext::GetVRTextureSize( _dword index ) const
{
	return PointU::cZeroPoint;
}

VREyeRHI GLContext::GetVREyeInfo( _dword index ) const
{
	static VREyeRHI sGraphicOVREyeInfo; 
	return sGraphicOVREyeInfo;
}
