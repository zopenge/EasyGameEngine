//! @file     GLPlatformWIN.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_ENABLE_VR_OVR_SDK == 1)

//!	The WGL DLL Functions
static PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARBFunc		= _null;
static PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARBFunc	= _null;

//!	Get WGL DLL functions.
static _ubool GetWGLDLLFunc( HWND window, HDC dc )
{
	// First create a context for the purpose of getting access to wglChoosePixelFormatARB / wglCreateContextAttribsARB.
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;

	int pf = ChoosePixelFormat(dc, &pfd);
	if (!pf)
	{
		ReleaseDC(window, dc);
		return false;
	}

	if (!SetPixelFormat(dc, pf, &pfd))
	{
		ReleaseDC(window, dc);
		return false;
	}

	HGLRC context = wglCreateContext(dc);
	if (!wglMakeCurrent(dc, context))
	{
		wglDeleteContext(context);
		ReleaseDC(window, dc);
		return false;
	}

	wglChoosePixelFormatARBFunc = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARBFunc = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	wglDeleteContext(context);

	EGE_ASSERT( wglChoosePixelFormatARBFunc );
#if (_ENABLE_GL_DEBUG == 1)
	EGE_ASSERT( wglCreateContextAttribsARBFunc );
#endif
	
	return _true;
}

//!	The window GL context
struct WindowGLContextHandle
{
	HWND				mWindowHandle;
	HGLRC				mGLContext;
	HDC					mWindowDC;

	//! The context of OVR SDK.
	ovrGraphicsLuid		mOVRLUID;
	ovrHmd				mOVRHandle; 
	ovrHmdDesc			mOVRDesc;
	//!	The OVR GL context
	OVR::GLEContext     mOVRGLEContext;
	//! The render buffers
	ovrGLTexture		mOVREyeTextures[2];
	ovrEyeRenderDesc	mOVREyeRenderDesc[2]; 
	ovrPosef			mOVREyeRenderPose[2];

	WindowGLContextHandle( )
	{
		mWindowHandle	= _null;
		mGLContext		= _null;
		mWindowDC		= _null;

		mOVRHandle		= _null; 
		EGE_INIT( mOVRLUID );
		EGE_INIT( mOVRDesc );
		EGE_INIT_ARRAY( mOVREyeTextures );
		EGE_INIT_ARRAY( mOVREyeRenderDesc );
		EGE_INIT_ARRAY( mOVREyeRenderPose );
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

// The OVR SDK log callback function
static void OnOVRLogCallback( uintptr_t userData, int level, const char* message )
{
	ALOG_TRACE_1( "[OVR] %s", message );
}

_handle CreateGLContext( _handle app_handle )
{
	if ( app_handle == _null )
		return _null;

	// Allocate a buffer to store OpenGL render context, window DC and window
	MemPtr< WindowGLContextHandle > gl_context( new WindowGLContextHandle( ) );
	gl_context->mWindowHandle = (HWND) app_handle;

	// The OVR initialized params
	ovrInitParams ovr_init_params = 
	{
		ovrInit_RequestVersion, // Flags
		OVR_MINOR_VERSION,      // RequestedMinorVersion
		OnOVRLogCallback,		// LogCallback
		0,                      // UserData
		0,                      // ConnectionTimeoutSeconds
		OVR_ON64("")            // pad0
	};

#ifdef _DEBUG
	ovr_init_params.Flags |= ovrInit_Debug;
#endif

	// Initialize OVR system
	OVR::System::Init( OVR::Log::ConfigureDefaultLog( OVR::LogMask_All ) );
	if ( ovr_Initialize( &ovr_init_params ) == ovrFalse )
	{
		WLOG_ERROR( L"Unable to initialize libOVR" );
		return _null;
	}

	// Create context of OVR SDK
	if ( OVR_FAILURE( ovr_Create( &gl_context->mOVRHandle, &gl_context->mOVRLUID ) ) )
	{
		WLOG_ERROR( L"Create context of OVR SDK failed" );
		return _null;
	}

	// Get the description of OVR SDK
	gl_context->mOVRDesc = ovr_GetHmdDesc( gl_context->mOVRHandle );

	// Show the OVR product name
	ALOG_TRACE_1( "Create '%s' OVR device", (const _chara*)gl_context->mOVRDesc.ProductName );

	// Get window DC
	gl_context->mWindowDC = ::GetDC( gl_context->mWindowHandle );
	if ( gl_context->mWindowDC == _null )
		return _null;

	#define WGL_SAMPLE_BUFFERS_ARB 0x2041
	#define WGL_SAMPLES_ARB 0x2042

	// Initialize pixel attributes
	int pixel_attributes[] = 
	{
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE, // Must support OGL rendering
		WGL_DOUBLE_BUFFER_ARB,	GL_TRUE, // Double buffered context
		WGL_COLOR_BITS_ARB,     32, // 8 bits of each R, G and B
		WGL_DEPTH_BITS_ARB,     16, // 24 bits of depth precision for window
		WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
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
	{
		WLOG_WARNING_1( L"The GL can not support '%d' multisample, disable it", gMultisampleNumber );

		// Try again without MSAA
		pixel_attributes[19] = 1;
		wglChoosePixelFormatARBFunc( gl_context->mWindowDC, pixel_attributes, fpixel_attributes, 1, &pixel_format, (UINT*)&pixel_count );
	}

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

	// Initialize OVR GL context
	OVR::GLEContext::SetCurrentContext( &gl_context->mOVRGLEContext );
	gl_context->mOVRGLEContext.Init( );

	// Configure the sensor tracking
	ovr_ConfigureTracking( gl_context->mOVRHandle, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0 );

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

	ovr_Destroy( gl_context->mOVRHandle );
	ovr_Shutdown( );

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

	// Get eye poses, feeding in correct IPD offset
	ovrVector3f view_offset[2] = { gl_context->mOVREyeRenderDesc[0].HmdToEyeViewOffset, gl_context->mOVREyeRenderDesc[1].HmdToEyeViewOffset };
	ovr_GetEyePoses( gl_context->mOVRHandle, 0, view_offset, gl_context->mOVREyeRenderPose, _null );

	return _true;
}

_ubool ShareGLContext( _handle context_1, _handle context_2 )
{
	WindowGLContextHandle* gl_context_1 = (WindowGLContextHandle*) context_1;
	WindowGLContextHandle* gl_context_2 = (WindowGLContextHandle*) context_2;
	if ( gl_context_1 == _null || gl_context_2 == _null )
		return _false;

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

	// Update OVR sdk info
	ovrGLTexture& eye_texture				= gl_context->mOVREyeTextures[ index ];
	eye_texture.OGL.Header.API				= ovrRenderAPI_OpenGL;
	eye_texture.OGL.Header.TextureSize.w	= tex_size.x;
	eye_texture.OGL.Header.TextureSize.h	= tex_size.y;
	eye_texture.OGL.TexId					= tex_id;
}

PointU GetVRTextureSize( _handle context, _dword index )
{
	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	EGE_ASSERT( gl_context != _null );

	ovrSizei tex_size = ovr_GetFovTextureSize( gl_context->mOVRHandle, (ovrEyeType_)index, gl_context->mOVRDesc.DefaultEyeFov[index], 1.0f );
	return PointU( tex_size.w, tex_size.h );
}

VREyeRHI GetVREyeInfo( _handle context, _dword index )
{
	EGE_ASSERT( index < 2 );

	WindowGLContextHandle* gl_context = (WindowGLContextHandle*) context;
	EGE_ASSERT( gl_context != _null );

	VREyeRHI eye_info;

	// Get the eye pos info
	const ovrPosef& eye_pos = gl_context->mOVREyeRenderPose[index];

	// Convert the quaternion ( swap y to z )
	Quaternion quat = Quaternion( eye_pos.Orientation.x, eye_pos.Orientation.y, eye_pos.Orientation.z, eye_pos.Orientation.w ) * Quaternion( ).RotationX( Math::cPi * 0.5f );
	// Convert the offset ( swap y to z )
	Vector3 offset = Vector3( eye_pos.Position.x, eye_pos.Position.y, eye_pos.Position.z ) * Quaternion( ).RotationX( Math::cPi * 0.5f );

	// Get the default eye fov info
	const ovrFovPort& default_fov_port = gl_context->mOVRDesc.DefaultEyeFov[index];

	// Update eye info
	eye_info.mHeight					= ovr_GetFloat( gl_context->mOVRHandle, OVR_KEY_EYE_HEIGHT, eye_info.mHeight );
	eye_info.mDefaultEyeFov.mUpTan		= default_fov_port.UpTan;
	eye_info.mDefaultEyeFov.mDownTan	= default_fov_port.DownTan;
	eye_info.mDefaultEyeFov.mLeftTan	= default_fov_port.LeftTan;
	eye_info.mDefaultEyeFov.mRightTan	= default_fov_port.RightTan;
	eye_info.mTransform					= Transform3D( quat, offset );

	return eye_info;
}

#endif