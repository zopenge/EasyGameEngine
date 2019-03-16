//! @file     GLPlatformIOS.mm
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// EAGLContextInfo
//----------------------------------------------------------------------------

struct EAGLContextInfo
{
    EAGLContext*    mGLContext;
    
    EAGLContextInfo( EAGLContext* gl_context )
    {
        mGLContext = gl_context;
    }
    ~EAGLContextInfo( )
    {
        mGLContext = nil;
    }
};

_handle CreateGLContext( _handle app_handle, const PointU& device_size )
{	
	// Create OpenGL context
	EAGLContext* gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	if ( gl_context == _null )
        return _null;

	// Make the current OpenGL context
	if ( [EAGLContext setCurrentContext:gl_context] == _false )
        return _null;

	// Check GL features
	if ( CheckGLFeatures( ) == _false )
		return _null;

	// Initialize pixel formats
	GLHelper::InitPixelFormats( );

	return new EAGLContextInfo( gl_context );
}

_void ReleaseGLContext( _handle context )
{
	if ( context == _null )
		return;

	EAGLContextInfo* gl_context = (EAGLContextInfo*) context;
	EGE_DELETE( gl_context );
}

_ubool MakeCurrentGLContext( _handle context )
{
	EAGLContextInfo* gl_context = (EAGLContextInfo*) context;
    EGE_ASSERT( gl_context != _null );

	GL_CHECK_ERROR( [EAGLContext setCurrentContext: gl_context->mGLContext] );
	return _true;
}

_ubool ShareGLContext( _handle context_1, _handle context_2 )
{
	return _false;
}

_dword GetGLContextNumber( )
{
    return 1;
}

_void FlushGLBuffers( _handle context )
{
	EAGLContextInfo* gl_context = (EAGLContextInfo*) context;
    EGE_ASSERT( gl_context != _null );
	
	// Discard the depth buffer
//#if (_OPENGLES_ == 1)
//	if ( __glDiscardFramebufferEXT != _null )
//	{
//		GLenum attachments[] = { GL_DEPTH_ATTACHMENT };
//		GL_CHECK_ERROR( __glDiscardFramebufferEXT( GL_FRAMEBUFFER, 1, attachments ) );
//	}
//#endif

	// Present render buffer
	GL_CHECK_ERROR( [gl_context->mGLContext presentRenderbuffer:GL_RENDERBUFFER] );
}

_void NS_RenderbufferStorage( _handle context, _handle layer )
{
	EAGLContextInfo* gl_context = (EAGLContextInfo*) context;
    EGE_ASSERT( gl_context != _null );

    GL_CHECK_ERROR( [gl_context->mGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(__bridge CAEAGLLayer*) layer] );
}
