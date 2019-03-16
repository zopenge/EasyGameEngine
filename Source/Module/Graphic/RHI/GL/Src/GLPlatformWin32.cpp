//! @file     GLPlatformWin32.mm
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGEGraphic.h"

//!	Output the OpenGL version info
static _void OutputGLVersion( )
{
	// Get "Glew" version string
	const _chara* glew_version_string = (const _chara*) ::glewGetString( GLEW_VERSION );
	if ( glew_version_string != _null )
		ALOG_TRACE_1( "Using GLEW %s", glew_version_string );

	// Get OpenGL vendor string
	const _chara* gl_vendor_string = (const _chara*) ::glGetString( GL_VENDOR );
	if ( gl_vendor_string != _null )
		ALOG_TRACE_1( "OpenGL Vendor: %s", gl_vendor_string );

	// Get OpenGL version string
	const _chara* gl_version_string = (const _chara*) ::glGetString( GL_VERSION );
	if ( gl_version_string != _null )
		ALOG_TRACE_1( "OpenGL Version: %s", gl_version_string );

	// Get OpenGL renderer string
	const _chara* gl_renderer_string = (const _chara*) ::glGetString( GL_RENDERER );
	if ( gl_renderer_string != _null )
		ALOG_TRACE_1( "OpenGL Renderer: %s", gl_renderer_string );

	// Get OpenGL shader language version string
	const _chara* gl_shader_version_string = (const _chara*) ::glGetString( GL_SHADING_LANGUAGE_VERSION );
	if ( gl_shader_version_string != _null )
	{
		ALOG_TRACE_1( "OpenGL Shader Language Version: %s", gl_shader_version_string );
	}
	else
	{
		ALOG_ERROR( "OpenGL Shader Language does not support" );
	}
}

_handle CreateGLContext( IApplication* application )
{
	// Get the window handle
	HWND window_handle = (HWND) application->GetApplicationHandle( );
	if ( window_handle == _null )
		return _null;

	// Get window DC
	HDC window_dc = ::GetDC( window_handle );
	if ( window_dc == _null )
		return _null;

	// Initialize pixel format data
	PIXELFORMATDESCRIPTOR pfd	= { 0 };
	pfd.nSize		  			= sizeof( pfd );
	pfd.nVersion	  			= 1;
	pfd.dwFlags		  			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType    			= PFD_TYPE_RGBA;
	pfd.cColorBits	  			= 32;
	pfd.cDepthBits	  			= 0;
	pfd.cStencilBits  			= 0;
	pfd.cAccumBits	  			= 0;
	pfd.iLayerType    			= PFD_MAIN_PLANE;

	// Choose the closed pixel format
	_dword pixelformat = ::ChoosePixelFormat( window_dc, &pfd );
	if ( pixelformat == 0 )
		{ ::ReleaseDC( window_handle, window_dc ); return _null; }

	// Set the pixel format data
	if ( ::SetPixelFormat( window_dc, pixelformat, &pfd ) == _false )
		{ ::ReleaseDC( window_handle, window_dc ); return _null; }

	// Create OpenGL render context
	HGLRC gl_context = ::wglCreateContext( window_dc );
	if ( gl_context == _null )
		{ ::ReleaseDC( window_handle, window_dc ); return _null; }

	// Bind OpenGL render context with windows DC
	if ( ::wglMakeCurrent( window_dc, gl_context ) == _false )
		{ ::wglDeleteContext( gl_context ); ::ReleaseDC( window_handle, window_dc ); return _null; }

	// Initialize the glew SDK
	static _ubool glew_inited = _false;
	if ( glew_inited == _false )
	{
		if ( glewInit( ) != GLEW_OK )
			{ ::wglDeleteContext( gl_context ); ::ReleaseDC( window_handle, window_dc ); return _null; }

		// We must support the (FBO, frame buffer object) feature at least
		if ( !GL_ARB_framebuffer_object )
			{ ::wglDeleteContext( gl_context ); ::ReleaseDC( window_handle, window_dc ); return _null; }

		glew_inited = _true;

		// Output the OpenGL version info
		OutputGLVersion( );
	}

	// Allocate a buffer to store OpenGL render context, window DC and window handle
	_dword* buffer	= new _dword[3];
	buffer[0]		= (_dword) gl_context;
	buffer[1]		= (_dword) window_dc;
	buffer[2]		= (_dword) window_handle;

	return buffer;
}

_void ReleaseGLContext( _handle context )
{
	if ( context == _null )
		return;

	// Get OpenGL render context, window DC and window handle
	_dword* buffer			= (_dword*) context;
	HGLRC	gl_context		= (HGLRC) buffer[0];
	HDC		window_dc		= (HDC) buffer[1];
	HWND	window_handle	= (HWND) buffer[2];

	// Delete OpenGL render context
	if ( gl_context )
	{
		::wglMakeCurrent( _null, _null );
		::wglDeleteContext( gl_context );
	}

	// Release window DC
	if ( window_dc )
		::ReleaseDC( window_handle, window_dc );

	// Release the store buffer
	delete[] buffer;
}

_void MakeCurrentGLContext( _handle context )
{
	if ( context == _null )
		return;

	// Get OpenGL render context, window DC and window handle
	_dword* buffer		= (_dword*) context;
	HGLRC	gl_context	= (HGLRC) buffer[0];
	HDC		window_dc	= (HDC) buffer[1];

	// Bind OpenGL render context
	::wglMakeCurrent( window_dc, gl_context );
}

_void FlushGLBuffers( _handle context )
{
	if ( context == _null )
		return;

	// Get OpenGL render context, window DC and window handle
	_dword* buffer		= (_dword*) context;
	HDC		window_dc	= (HDC) buffer[1];

	// Present screen
	::SwapBuffers( window_dc );
}