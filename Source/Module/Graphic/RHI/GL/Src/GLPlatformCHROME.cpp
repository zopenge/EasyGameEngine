//! @file     GLPlatformCHROME.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLContextInfo
//----------------------------------------------------------------------------

struct GLContextInfo
{
	PP_Resource	mGLContext;

	GLContextInfo( )
	{
		mGLContext = _null;
	}
};

//----------------------------------------------------------------------------
// GLPlatform-CHROME Platform Function Implementations
//----------------------------------------------------------------------------

_handle CreateGLContext( _handle app_handle, const PointU& device_size )
{
	WLOG_TRACE( L"Initializing chrome GL render context ..." );

	// Initialize PPAPI for OpenGL
	glInitializePPAPI( GetPPResourceModule( )->GetPPGetInterfaceFunc( ) );

	// Set the GL attibutes
	int32_t attribs[] = 
	{
		PP_GRAPHICS3DATTRIB_ALPHA_SIZE,		8,
		PP_GRAPHICS3DATTRIB_DEPTH_SIZE,		24,
		PP_GRAPHICS3DATTRIB_STENCIL_SIZE,	8,
		PP_GRAPHICS3DATTRIB_SAMPLES,		0,
		PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
		PP_GRAPHICS3DATTRIB_WIDTH,			(int32_t) device_size.x,
		PP_GRAPHICS3DATTRIB_HEIGHT,			(int32_t) device_size.y,
		PP_GRAPHICS3DATTRIB_NONE
	};

	// Create GL context info
	GLContextInfo* gl_context = new GLContextInfo( );

	// Create GL context
	gl_context->mGLContext = GetPPResourceModule( )->GetPPBGraphics3D( )->Create( GetPPResourceModule( )->GetPPInstance( ), 0, attribs );
	EGE_ASSERT( gl_context->mGLContext != _null );

	// Bind graphic with instance
	GetPPResourceModule( )->GetPPBInstance( )->BindGraphics( GetPPResourceModule( )->GetPPInstance( ), gl_context->mGLContext );

	// Set the current GL context
	glSetCurrentContextPPAPI( gl_context->mGLContext );

	// Check GL features
	if ( CheckGLFeatures( Version( 2, 0, 0, 0 ) ) == _false )
	{
		ReleaseGLContext( gl_context );
		return _null;
	}

	// Initialize pixel formats
	GLHelper::InitPixelFormats( );

	WLOG_TRACE_2( L"Initializing chrome GL render context (%dx%d) DONE", device_size.x, device_size.y );

	return gl_context;
}

_void ReleaseGLContext( _handle context )
{
	GLContextInfo* gl_context = (GLContextInfo*) context;
	EGE_ASSERT( gl_context != _null );

	// Terminate PPAPI for OpenGL
	glTerminatePPAPI( );

	// Release context resource
	GetPPResourceModule( )->ReleaseResource( gl_context->mGLContext );

	// Release GL context
	EGE_DELETE( gl_context );
}

_ubool MakeCurrentGLContext( _handle context )
{
	GLContextInfo* gl_context = (GLContextInfo*) context;
	EGE_ASSERT( gl_context != _null );

	// Set the current GL context
	glSetCurrentContextPPAPI( gl_context->mGLContext );

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
	GLContextInfo* gl_context = (GLContextInfo*) context;
	EGE_ASSERT( gl_context != _null );

	// Present render buffer
	GetPPResourceModule( )->GetPPBGraphics3D( )->SwapBuffers( gl_context->mGLContext, PP_BlockUntilComplete( ) );
}