//! @file     GLESContext.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLContext Implementation
//----------------------------------------------------------------------------

GLContext::GLContext( )
{
	mFramebuffer		= 0;
	mColorRenderbuffer	= 0;
	
	mGLDriver			= _null;
}

GLContext::~GLContext( )
{
	if ( mColorRenderbuffer )
		::glDeleteRenderbuffers( 1, &mColorRenderbuffer );

	if ( mFramebuffer )
		::glDeleteFramebuffers(1, &mFramebuffer);
}

_ubool GLContext::Initialize( GLDrv* gl_driver )
{
	mGLDriver = gl_driver;
	
	// Create frame buffer and color render buffer
	::glGenFramebuffers( 1, &mFramebuffer );
	::glGenRenderbuffers( 1, &mColorRenderbuffer );
	::glBindFramebuffer( GL_FRAMEBUFFER, mFramebuffer );
	::glBindRenderbuffer( GL_RENDERBUFFER, mColorRenderbuffer );
	GL_CHECK_ERROR( ::glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorRenderbuffer ) );

	// Allocate color buffer backing based on the current layer size
	::glBindRenderbuffer( GL_RENDERBUFFER, mColorRenderbuffer );
#if defined _PLATFORM_IOS_
	NS_RenderbufferStorage( mGLDriver->GetGLContext( ), mGLDriver->GetGLLayer( ) );
#elif defined _PLATFORM_ANDROID_
#endif

	return _true;
}

_void GLContext::Bind( )
{
	// Bind the default frame buffer
	GL_CHECK_ERROR( ::glBindFramebuffer( GL_FRAMEBUFFER, mFramebuffer ) );

	// Bind the color render buffer
	GL_CHECK_ERROR( ::glBindRenderbuffer( GL_RENDERBUFFER, mColorRenderbuffer ) );
}