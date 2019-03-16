//! @file     GLPlatformWIN.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_ENABLE_VR_OVR_SDK == 0)

// OpenGLES with EGL emulator
#if (_OPENGLES_ == 1) && (_ENABLE_EGL_ == 1)

_handle CreateGLContext( _handle app_handle )
{
	MemPtr< GLESContext > gles_context( new GLESContext( ) );

	// Create EGL context
	if ( gles_context->Create( app_handle ) == _false )
		return _null;

	// Check GL features
	if ( CheckGLFeatures( ) == _false )
		return _null;

	// Initialize pixel formats
	GLHelper::InitPixelFormats( );

	WLOG_TRACE_1( L"Create OpenGLES context:0x%.16llx", (_qword) gles_context.GetPointer( ) );

	// Create EGL context successful, so we skip to delete it
	gles_context.EnableAutoDelete( _false );

	return gles_context;
}

_void ReleaseGLContext( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	WLOG_TRACE_1( L"Release OpenGLES context:0x%.16llx", (_qword) gles_context );

	EGE_DELETE( gles_context );
}

_ubool ResetGLContext( _handle context, _handle app_handle )
{
	return _true;
}

_void UnloadGLContext( _handle context )
{

}

_ubool MakeCurrentGLContext( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	return gles_context->MakeCurrentGLContext( );
}

_ubool ShareGLContext( _handle context_1, _handle context_2 )
{
	// EGL does not support for this operation
	return _false;
}

_dword GetGLContextNumber( )
{
	return 1;
}

_void FlushGLBuffers( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	gles_context->FlushGLBuffers( );
}

_void SetVRRenderTargetTexID( _handle context, _dword index, _dword tex_id, const PointU& tex_size )
{
}

PointU GetVRTextureSize( _handle context, _dword index )
{
	return PointU::cZeroPoint;
}

VREyeRHI GetVREyeInfo( _handle context, _dword index )
{
	return VREyeRHI( );
}

// OpenGL
#else

//!	The WGL DLL Functions
static PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARBFunc		= _null;
static PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARBFunc	= _null;

//!	Get WGL DLL functions.
static _ubool GetWGLDLLFunc( HWND window, HDC dc )
{
	wglChoosePixelFormatARBFunc		= wglChoosePixelFormatARB;
	wglCreateContextAttribsARBFunc	= wglCreateContextAttribsARB;

	EGE_ASSERT( wglChoosePixelFormatARBFunc );
#if (_ENABLE_GL_DEBUG == 1)
	EGE_ASSERT( wglCreateContextAttribsARBFunc );
#endif
	
	return _true;
}

//!	The window GL context
struct WindowGLContextHandle
{
	HWND	mWindowHandle;
	HGLRC	mGLContext;
	HDC		mWindowDC;

#if (_ENABLE_VR_SOFTWARE == 1)
	//!	The VR texture size
	PointU	mVRTextureSizes[2];
	//!	The VR texture IDs
	GLuint	mVRTextureIDs[2];
#endif

	WindowGLContextHandle( )
	{
		mWindowHandle	= _null;
		mGLContext		= _null;
		mWindowDC		= _null;

#if (_ENABLE_VR_SOFTWARE == 1)
		EGE_INIT_ARRAY( mVRTextureSizes );
		EGE_INIT_ARRAY( mVRTextureIDs );
#endif
	}
};

//!	The main GL context and window DC
static HGLRC	gMainGLContext	= _null;
static HDC		gMainWindowDC	= _null;

//!	The current GL context and window DC
static HGLRC	gCurGLContext	= _null;
static HDC		gCurWindowDC	= _null;

//!	The GL context list
static Array< WindowGLContextHandle* > gGLContextList;

#if (_DISABLE_GLEW_SDK == 0)

//!	The dummy window info
static const _chara*	gDummyWindowClassName	= "DummyForGLEW";
static HWND				gDummyWindowHandle		= _null;

//!	The dummy window message procession.
LRESULT CALLBACK DummyWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

_ubool InitGlewByDummyWindow( )
{
	// Register window class
	WNDCLASSEXA windowclass		= { sizeof( WNDCLASSEXA ) };
	windowclass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
	windowclass.lpfnWndProc		= (WNDPROC) DummyWndProc;
	windowclass.hInstance		= ::GetModuleHandleA( _null );
	windowclass.hIcon			= ::LoadIcon( _null, IDI_WINLOGO );
	windowclass.hCursor			= ::LoadCursor( _null, IDC_ARROW );
	windowclass.lpszClassName	= gDummyWindowClassName;
	if ( !::RegisterClassExA( &windowclass ) )
		return _false;

	// Create window
	gDummyWindowHandle = ::CreateWindowExA( 0, gDummyWindowClassName, gDummyWindowClassName, WS_OVERLAPPED, 0, 0, 1, 1, _null, _null, _null, _null );
	if ( gDummyWindowHandle == _null )
		return _false;

	// Get window DC
	HDC hdc = ::GetDC( gDummyWindowHandle );
	if ( hdc == _null )
		return _false;

	// Attempt to set the pixel format
	PIXELFORMATDESCRIPTOR pfd = {0};
	if ( !::SetPixelFormat( hdc, 1, &pfd ) )
		return _false;

	// Create GL context
	HGLRC glrc = wglCreateContext( hdc );
	wglMakeCurrent( hdc, glrc );

	// Initialize GLEW library
	if ( glewInit( ) != GLEW_OK )
		return _false;

	// Get GLEW SDK version string
	const _chara* glew_version_string = (const _chara*)glewGetString( GLEW_VERSION );
	if ( glew_version_string != _null )
	{
		ALOG_TRACE_1( "Using 'GLEW v%s' SDK", glew_version_string );
	}

	// Unbind GL context
	wglMakeCurrent( _null, _null );
	wglDeleteContext( glrc );

	// Unbind DC of window
	ReleaseDC( gDummyWindowHandle, hdc );

	// Destroy dummy window
	::DestroyWindow( gDummyWindowHandle );
	::UnregisterClassA( gDummyWindowClassName, ::GetModuleHandleA( _null ) );

	return _true;
}

#endif

_handle CreateGLContext( _handle app_handle )
{
	if ( app_handle == _null )
		return _null;

	// Allocate a buffer to store OpenGL render context, window DC and window
	MemPtr< WindowGLContextHandle > gl_context( new WindowGLContextHandle( ) );
	gl_context->mWindowHandle = (HWND) app_handle;

#if (_DISABLE_GLEW_SDK == 0)
	// Initialize GLEW library by dummy window
	if ( InitGlewByDummyWindow( ) == _false )
		return _null;
#endif

	// Get window DC
	gl_context->mWindowDC = ::GetDC( gl_context->mWindowHandle );
	if ( gl_context->mWindowDC == _null )
		return _null;

	// Initialize pixel attributes
	int pixel_attributes[] = 
	{
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE, // Must support OGL rendering
		WGL_DOUBLE_BUFFER_ARB,	GL_TRUE, // Double buffered context
		WGL_COLOR_BITS_ARB,     32, // 8 bits of each R, G and B
		WGL_DEPTH_BITS_ARB,     16, // 24 bits of depth precision for window
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB, // pf should be RGBA type
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, // pf that can run a window
		WGL_STENCIL_BITS_ARB,	8,
		WGL_SAMPLE_BUFFERS_ARB, gMultisampleNumber != 0 ? GL_TRUE : GL_FALSE,
		WGL_SAMPLES_ARB,        (int) gMultisampleNumber, // MSAA Number
		0, 0 // NULL termination
	}; 

	// Get the WGL functions
	if ( GetWGLDLLFunc( gl_context->mWindowHandle, gl_context->mWindowDC ) == _false )
		return _null;

	// Find the pixel format
	int pixel_format = -1, pixel_count = 0; float fpixel_attributes[] = { 0.0f, 0.0f };
	wglChoosePixelFormatARBFunc( gl_context->mWindowDC, pixel_attributes, fpixel_attributes, 1, &pixel_format, (UINT*)&pixel_count );
	if ( pixel_format == -1 )
		return _null;

	WLOG_TRACE_1( L"The GL use '%d' multisample mode", gMultisampleNumber );

	// Got a format, now set it as the current one
	PIXELFORMATDESCRIPTOR pfd = {0};
	if ( !::SetPixelFormat( gl_context->mWindowDC, pixel_format, &pfd ) )
		return _null;

#if (_ENABLE_GL_DEBUG == 1)
	// Set the context attributes
	int context_attribs[] = 
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,	2,
		WGL_CONTEXT_MINOR_VERSION_ARB,	0,
		WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0
	};

	// Create OpenGL render context
	gl_context->mGLContext = wglCreateContextAttribsARBFunc( gl_context->mWindowDC, _null, context_attribs );
	if ( gl_context->mGLContext == _null )
		return _null;
#else
	// Create OpenGL render context
	gl_context->mGLContext = ::wglCreateContext( gl_context->mWindowDC );	
	if ( gl_context->mGLContext == _null )
		return _null;
#endif

	// Bind OpenGL render context with windows DC
	if ( MakeCurrentGLContext( gl_context ) == _false )
		return _null;

	// Check GL features
	if ( CheckGLFeatures( ) == _false )
		return _null;

	// Update context list
	gGLContextList.Append( gl_context );

	WLOG_TRACE_1( L"Create Windows GL context:0x%.8x", (_dword) gl_context->mGLContext );

	// Initialize pixel formats
	GLHelper::InitPixelFormats( );

	// Create EGL context successful, so we skip to delete it
	gl_context.EnableAutoDelete( _false );

	// Update the main context info
	if ( gMainGLContext == _null )
		gMainGLContext = gl_context->mGLContext;
	if ( gMainWindowDC == _null )
		gMainWindowDC = gl_context->mWindowDC;

	return gl_context;
}

_void ReleaseGLContext( _handle context )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	if ( gl_context == _null )
		return;

	WLOG_TRACE_1( L"Release Windows GL context:0x%.8x", (_dword) gl_context->mGLContext );

	// Delete OpenGL render context
	if ( gl_context->mGLContext )
	{
		// http://www.opengl.org/wiki/Platform_specifics:_Windows#When_do_I_destroy_the_GL_context.3F
		if ( !::wglMakeCurrent( _null, _null ) )
			WLOG_ERROR_1( L"Unbind current GL context failed, error:%d", (_dword)::GetLastError( ) );
	
		if ( !::wglDeleteContext( gl_context->mGLContext ) )
			WLOG_ERROR_1( L"Delete GL context failed, error:%d", (_dword)::GetLastError( ) );
	}

	// Release window DC
	if ( gl_context->mWindowDC )
		::ReleaseDC( gl_context->mWindowHandle, gl_context->mWindowDC );

	// Remove it from context list
	gGLContextList.Remove( gl_context );

	// Clear context list if it's empty
	if ( gGLContextList.Number( ) == 0 )
	{
		gMainGLContext	= _null;
		gMainWindowDC	= _null;

		gCurWindowDC	= _null;
		gCurGLContext	= _null;

		gGLContextList.Clear( _true );
	}
	// If it's the binding context then set other GL context as current ( just for multiple contexts )
	else
	{
		WindowGLContextHandle* handle = gGLContextList[0];
		EGE_ASSERT( handle != _null );

		// We need to force bind context here, otherwise some resources delete will be failed.
		gCurWindowDC	= handle->mWindowDC;
		gCurGLContext	= handle->mGLContext;
		::wglMakeCurrent( handle->mWindowDC, handle->mGLContext );
	}
	
	// Release the store buffer
	delete gl_context;
}

_ubool ResetGLContext( _handle context, _handle app_handle )
{
	return _true;
}

_void UnloadGLContext( _handle context )
{

}

_ubool MakeCurrentGLContext( _handle context )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	if ( gl_context == _null )
		return _false;

	// Bind OpenGL render context
	if ( gl_context->mWindowDC != gCurWindowDC || gl_context->mGLContext != gCurGLContext )
	{
		gCurWindowDC	= gl_context->mWindowDC;
		gCurGLContext	= gl_context->mGLContext;

		if ( !::wglMakeCurrent( gl_context->mWindowDC, gl_context->mGLContext ) )
		{
			WLOG_ERROR_1( L"Make current GL context failed, error:%d", (_dword)::GetLastError( ) );
			return _false;
		}

		// If we do not bind the default FBO then render device seems broken when rendering for other windows
		GL_CHECK_ERROR( __glBindFramebuffer( GL_FRAMEBUFFER, 0 ) );
		gGLCachedState.mCurFBO = 0;
	}

	return _true;
}

_ubool ShareGLContext( _handle context_1, _handle context_2 )
{
	WindowGLContextHandle* gl_context_1 = (WindowGLContextHandle*) context_1;
	WindowGLContextHandle* gl_context_2 = (WindowGLContextHandle*) context_2;
	if ( gl_context_1 == _null || gl_context_2 == _null )
		return _false;

	// Share GL contexts
	if ( !::wglShareLists( gl_context_1->mGLContext, gl_context_2->mGLContext ) )
	{
		WLOG_ERROR_1( L"Share GL context failed, error:%d", (_dword)::GetLastError( ) );
		return _false;
	}

	return _true;
}

_dword GetGLContextNumber( )
{
	return gGLContextList.Number( );
}

_void FlushGLBuffers( _handle context )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	if ( gl_context == _null )
		return;

	// Present screen
	::SwapBuffers( gl_context->mWindowDC );
}

_void SetVRRenderTargetTexID( _handle context, _dword index, _dword tex_id, const PointU& tex_size )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	if ( gl_context == _null )
		return;

	// Update VR info
#if (_ENABLE_VR_SOFTWARE == 1)
	gl_context->mVRTextureSizes[index]	= tex_size;
	gl_context->mVRTextureIDs[index]	= tex_id;
#endif
}

PointU GetVRTextureSize( _handle context, _dword index )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	EGE_ASSERT( gl_context != _null );

#if (_ENABLE_VR_SOFTWARE == 1)
	return gl_context->mVRTextureSizes[index];
#else
	return PointU::cZeroPoint;
#endif
}

VREyeRHI GetVREyeInfo( _handle context, _dword index )
{
	EGE_ASSERT( index < 2 );

	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	EGE_ASSERT( gl_context != _null );

	VREyeRHI eye_info;

#if (_ENABLE_VR_SOFTWARE == 1)
	// Get the client size
	PointU size = GetMainViewBasedApp( )->GetClientSize( );

	// Get the eye default height
	_float eye_height	= 1.675f;

	// Get the ratio and fov-Y, fov-X
	_float ratio	= EGE_RATIO( size.x / 2.0f, size.y );
	_float fov_y	= Math::Degree2Radian( 45.0f );
	_float fov_x	= ratio * fov_y;
	_float u_d_tan	= Math::Tan( fov_y / 2.0f );
	_float l_r_tan	= Math::Tan( fov_x / 2.0f );

	// Update the eye info
	eye_info.mHeight					= eye_height;
	eye_info.mDefaultEyeFov.mUpTan		= u_d_tan;
	eye_info.mDefaultEyeFov.mDownTan	= u_d_tan;
	eye_info.mDefaultEyeFov.mLeftTan	= l_r_tan;
	eye_info.mDefaultEyeFov.mRightTan	= l_r_tan;
#endif

	return eye_info;
}

#endif

#endif