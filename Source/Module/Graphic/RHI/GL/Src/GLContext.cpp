//! @file     GLContext.cpp
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
}

_ubool GLContext::Initialize( GLDrv* gl_driver )
{
	mGLDriver = gl_driver;
	
	return _true;
}

_void GLContext::Bind( )
{
	CachedBindFramebuffer( 0 );

	// Update the pending frame buffer
	gGLCachedState.mPendingFramebuffer = 0;
}