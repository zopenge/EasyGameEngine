//! @file     GLPlatformiPhone.mm
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGEGraphic.h"

_handle CreateGLContext( IApplication* application )
{	
	// Create OpenGL context
	EAGLContext* gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	if ( gl_context == _null )
	{
		gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		if ( gl_context == _null )
			return _null;
	}

	// Make the current OpenGL context
	[EAGLContext setCurrentContext:gl_context]; 

	return gl_context;
}

_void ReleaseGLContext( _handle context )
{
	if ( context == _null )
		return;

	EAGLContext* gl_context = (EAGLContext*) context;
	[gl_context release];
}

_void MakeCurrentGLContext( _handle context )
{
	GL_CHECK_ERROR( [EAGLContext setCurrentContext:(EAGLContext*) context] );
}

_void FlushGLBuffers( _handle context )
{
	if ( context == _null )
		return;

	EAGLContext* gl_context = (EAGLContext*) context;
	GL_CHECK_ERROR( [gl_context presentRenderbuffer:GL_RENDERBUFFER] );
}

_void NS_RenderbufferStorage( _handle context, _handle layer )
{
	if ( context == _null || layer == _null )
		return;

	EAGLContext* gles_context   = (EAGLContext*) context;
	CAEAGLLayer* eagl_layer		= (CAEAGLLayer*) layer;	
	GL_CHECK_ERROR( [gles_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eagl_layer] );
}