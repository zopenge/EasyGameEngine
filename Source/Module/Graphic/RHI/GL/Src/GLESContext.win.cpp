//! @file     GLESContext.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_OPENGLES_ == 1)

//----------------------------------------------------------------------------
// GLESContext Internal Handler Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( GLESContext )
	//!	The EGL info
	EGLDisplay	mEGLDisplay;
	EGLSurface	mEGLSurface;
	EGLContext	mEGLContext;
	EGLConfig	mEGLConfig;
	Version		mEGLVersion;
	Version		mGLESVersion;
	EGLint		mConfigID;

	//!	The window handle
	_handle		mWindowHandle;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mEGLDisplay		= EGL_NO_DISPLAY;
		mEGLSurface		= EGL_NO_SURFACE;
		mEGLContext		= EGL_NO_CONTEXT;
		mEGLConfig		= _null;
		mEGLVersion		= Version::cZero;
		mGLESVersion	= Version::cZero;
		mConfigID		= 0;

		mWindowHandle	= _null;
	}

	INTERNAL_HANDLER_DESTRUCTOR( )
	{
		if ( mEGLDisplay != EGL_NO_DISPLAY )
		{
			__eglMakeCurrent( mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );

			if ( mEGLSurface != EGL_NO_SURFACE )
			{
				ALOG_TRACE_1( "Release EGL surface( 0x%.8x)", (_dword)mEGLSurface );
				__eglDestroySurface( mEGLDisplay, mEGLSurface );
			}

			if ( mEGLContext != EGL_NO_CONTEXT )
			{
				ALOG_TRACE_1( "Release EGL context( 0x%.8x)", (_dword)mEGLContext );
				__eglDestroyContext( mEGLDisplay, mEGLContext );
			}

			ALOG_TRACE_1( "Release EGL display( 0x%.8x)", (_dword)mEGLDisplay );
			__eglTerminate( mEGLDisplay );
		}
	}

	//!	Initialize the config list.
	_ubool ChooseConfigList( _handle app_handle );
	//!	Create EGL context.
	_ubool CreateEGLContext( EGLint gles_ver_id );
	//!	Create EGL surface.
	_ubool CreateEGLSurface( _handle app_handle );

	//!	Create.
	_ubool Create( _handle app_handle );

	_ubool MakeCurrentGLContext( );
	_void FlushGLBuffers( );

INTERNAL_HANDLER_IMPL_END( )

_ubool GLESContext::INTERNAL_HANDLER_NAME::ChooseConfigList( _handle app_handle )
{
	EGLBoolean ret = EGL_TRUE;

	// The best setting pixel formats at runtime
	const EGLint cBest_PF_Red		= 5;
	const EGLint cBest_PF_Green		= 6;
	const EGLint cBest_PF_Blue		= 5;
	const EGLint cBest_PF_Alpha		= 0;
	const EGLint cBest_PF_Depth		= 24;
	const EGLint cBest_PF_Stencil	= 8;

	// The current match setting pixel formats at runtime
	EGLint cCur_PF_Red		= 0;
	EGLint cCur_PF_Green	= 0;
	EGLint cCur_PF_Blue		= 0;
	EGLint cCur_PF_Alpha	= 0;
	EGLint cCur_PF_Depth	= 0;
	EGLint cCur_PF_Stencil	= 0;

#define DEFAULT_FEATURES \
	EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT, \
	EGL_SURFACE_TYPE,		EGL_WINDOW_BIT, \
	EGL_RED_SIZE,			EGL_DONT_CARE, \
	EGL_GREEN_SIZE,			EGL_DONT_CARE, \
	EGL_BLUE_SIZE,			EGL_DONT_CARE, \
	EGL_ALPHA_SIZE,			EGL_DONT_CARE, \
	EGL_DEPTH_SIZE,			EGL_DONT_CARE, \
	EGL_STENCIL_SIZE,		EGL_DONT_CARE

	// The default attributes
	const EGLint cDefaultRequestedAttributes[] = 
	{
		DEFAULT_FEATURES,
		EGL_NONE
	};
	// The MSAA attributes
	const EGLint cMSAARequestedAttributes[] = 
	{
		DEFAULT_FEATURES,
		EGL_SAMPLE_BUFFERS,	gMultisampleNumber != 0 ? GL_TRUE : GL_FALSE,
		EGL_SAMPLES,		(EGLint) gMultisampleNumber,
		EGL_NONE
	};

	// Choose the attributes
	const EGLint* request_attribute = cDefaultRequestedAttributes;
	if ( gMultisampleNumber != 0 )
		request_attribute = cMSAARequestedAttributes;

	// Choose configurations
	const EGLint cMaxConfigs = 128;
	EGLConfig available_configs[cMaxConfigs] = {0};

	EGLint num_of_available_configs = 0;
	if ( !__eglChooseConfig( mEGLDisplay, request_attribute, available_configs, cMaxConfigs, &num_of_available_configs ) || num_of_available_configs == 0 )
	{
		WLOG_TRACE( L"Try to choose the best config failed, now try to match the minimal request configurations" );

		// Build the minimal request attribute
		EGLint min_request_attrs[] = { EGL_DEPTH_SIZE, 16, EGL_NONE };

		// Start to match the minimal request attribute
		if ( !__eglChooseConfig( mEGLDisplay, min_request_attrs, available_configs, cMaxConfigs, &num_of_available_configs ) || num_of_available_configs == 0 )
		{
			WLOG_ERROR_2( L"Choose EGL configures(number:%d) failed with '0x%x' error ID", num_of_available_configs, __eglGetError( ) );
			return _false;
		}

		WLOG_TRACE_1( L"Match the minimal request configurations OK, we have '%d' number candidates", num_of_available_configs );

		// Always get the first config if we try to match the minimal request attribute
		mEGLConfig = available_configs[0];

		// Query attributes from config
		EGLint RAvail, GAvail, BAvail, AAvail, DAvail, SAvail;
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_RED_SIZE, &RAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_GREEN_SIZE, &GAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_BLUE_SIZE, &BAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_ALPHA_SIZE, &AAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_DEPTH_SIZE, &DAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, available_configs[0], EGL_STENCIL_SIZE, &SAvail );

		// This one is really great - we're done
		ALOG_TRACE_6( "EGL Config (0) exactly matches our requested format: RGBA(%d, %d, %d, %d), DS(%d, %d)", 
			RAvail, GAvail, BAvail, AAvail, DAvail, SAvail );
	}

	WLOG_TRACE_1( L"The number of available configurations number is : %d, now start to choose the best of them", num_of_available_configs );

	// Dump the returned configurations
	EGLint best_match = -1; _dword distance_from_best_match = Math::cMaxDword; // More small value indicates much better match performance
	for ( EGLint config_index = 0; config_index < num_of_available_configs; config_index ++ )
	{
		EGLConfig config = available_configs[ config_index ];
		if ( config == _null )
			continue;

		// Query attributes from config
		EGLint RAvail, GAvail, BAvail, AAvail, DAvail, SAvail;
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_RED_SIZE, &RAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_GREEN_SIZE, &GAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_BLUE_SIZE, &BAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_ALPHA_SIZE, &AAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_DEPTH_SIZE, &DAvail );
		ret &= __eglGetConfigAttrib( mEGLDisplay, config, EGL_STENCIL_SIZE, &SAvail );

		if ( !ret )
		{
			WLOG_ERROR_1( L"Get EGL configure attribute failed with '0x%x' error ID", __eglGetError( ) );
			continue;
		}

		// Calculate the match distance 
		_dword distance =	Math::Abs( RAvail - cBest_PF_Red ) + 
							Math::Abs( GAvail - cBest_PF_Green ) +
							Math::Abs( BAvail - cBest_PF_Blue ) +
							Math::Abs( AAvail - cBest_PF_Alpha ) +
							Math::Abs( DAvail - cBest_PF_Depth ) +
							Math::Abs( SAvail - cBest_PF_Stencil );

		// Is it a better match ?
		if ( distance < distance_from_best_match )
		{
			distance_from_best_match	= distance;
			best_match					= config_index;

			cCur_PF_Red					= RAvail;
			cCur_PF_Green				= GAvail;
			cCur_PF_Blue				= BAvail;
			cCur_PF_Alpha				= AAvail;
			cCur_PF_Depth				= DAvail;
			cCur_PF_Stencil				= SAvail;
		}

		// Show the candidate
		ALOG_TRACE_8( "EGL Config (index:%d, distance:%d) format: RGBA(%d, %d, %d, %d), DS(%d, %d)", 
			config_index, distance, RAvail, GAvail, BAvail, AAvail, DAvail, SAvail );
	}

	// Found a great one!
	if ( best_match != -1 )
	{
		mEGLConfig = available_configs[best_match];

		// This one is really great - we're done
		ALOG_TRACE_9( "EGL Config (index:%d, distance:%d) exactly matches(total:%d) our requested format: RGBA(%d, %d, %d, %d), DS(%d, %d)", 
			best_match, distance_from_best_match, num_of_available_configs, cCur_PF_Red, cCur_PF_Green, cCur_PF_Blue, cCur_PF_Alpha, cCur_PF_Depth, cCur_PF_Stencil );
	}
	// No exact match was found
	else
	{
		ALOG_ERROR( "No exactly matching EGL configures found!" );
		return _false;
	}

	// Get the native visual config ID
	ALOG_TRACE( "Getting native visual ID ..." );
	if ( __eglGetConfigAttrib( mEGLDisplay, mEGLConfig, EGL_NATIVE_VISUAL_ID, &mConfigID ) == 0 )
	{
		ALOG_ERROR( "Get native visual ID failed" );
		return _false;
	}

	return _true;
}

_ubool GLESContext::INTERNAL_HANDLER_NAME::CreateEGLContext( EGLint gles_ver_id )
{
	// Build the GLES context attributes
	EGLint cContextAttrs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, gles_ver_id,
		EGL_NONE
	};

	// Create EGL context
	mEGLContext = __eglCreateContext( mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, cContextAttrs );
	if ( mEGLContext == EGL_NO_CONTEXT )
		return _false;

	// Save the GLES version
	mGLESVersion = Version( gles_ver_id, 0, 0, 0 );

	// Set the render hardware features
	FlagsObject features = _RHF_ETC1_RGB8;
	if ( gles_ver_id >= 3 )
		features.CombineFlags( _RHF_ETC2_RGBA8 );

	// Update the render hardware features
	GetDynamicRHI( )->SetHardwareFeatures( features );

	WLOG_TRACE_1( L"Create EGL(ver: %d.0) context OK", gles_ver_id );
	return _true;
}

_ubool GLESContext::INTERNAL_HANDLER_NAME::CreateEGLSurface( _handle app_handle )
{
	// Get the window handle
	mWindowHandle = app_handle;

	WLOG_TRACE_1( L"Create EGL surface with '0x%.8x' window handle ...", (_dword) mWindowHandle );

	// Create EGL surface
	mEGLSurface = __eglCreateWindowSurface( mEGLDisplay, mEGLConfig, (EGLNativeWindowType) mWindowHandle, _null );
	if ( mEGLSurface == EGL_NO_SURFACE )
	{
		WLOG_ERROR_1( L"Create EGL surface failed with '0x%x' error ID", __eglGetError( ) );
		return _false;
	}

	WLOG_TRACE( L"Create EGL surface OK" );

	return _true;
}

_ubool GLESContext::INTERNAL_HANDLER_NAME::Create( _handle app_handle )
{
	if ( app_handle == _null )
		return _false;

	// Get the default display handle
	mEGLDisplay = __eglGetDisplay( EGL_DEFAULT_DISPLAY );
	if ( mEGLDisplay == EGL_NO_DISPLAY )
	{
		WLOG_ERROR( L"Get EGL default display failed" );
		return _false;
	}

	// Bind the OpenGLES API
	if ( __eglBindAPI( EGL_OPENGL_ES_API ) == _false )
	{
		WLOG_ERROR( L"Bind OpenGLES API failed" );
		return _false;
	}

	// Initialize the EGL
	EGLint major_version = 0, minor_version = 0;
	if ( __eglInitialize( mEGLDisplay, &major_version, &minor_version ) == _false )
	{
		WLOG_ERROR( L"Initialize EGL failed" );
		return _false;
	}

	// Save the EGL version
	mEGLVersion = Version( major_version, minor_version, 0, 0 );
	ALOG_TRACE_1( "EGL Version: v%s", mEGLVersion.ToAString( ).Str( ) );

	// Choose the config
	if ( ChooseConfigList( app_handle ) == _false )
		return _false;

	// Create the EGL context
	if ( CreateEGLContext( 2 ) == _false )
		return _false;

	// Create the EGL surface
	if ( CreateEGLSurface( app_handle ) == _false )
		return _false;

	// Bind the EGL context
	if ( MakeCurrentGLContext( ) == _false )
	{
		WLOG_ERROR( L"Make current EGL failed" );
		return _false;
	}

	// Get the EGL extensions
	gEGLExtensions = __eglQueryString( mEGLDisplay, EGL_EXTENSIONS );

	return _true;
}

_ubool GLESContext::INTERNAL_HANDLER_NAME::MakeCurrentGLContext( )
{
	if ( __eglMakeCurrent( mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext ) == _false )
		return _false;

	return _true;
}

_void GLESContext::INTERNAL_HANDLER_NAME::FlushGLBuffers( )
{
	__eglSwapBuffers( mEGLDisplay, mEGLSurface );
}

//----------------------------------------------------------------------------
// GLESContext Implementation
//----------------------------------------------------------------------------

GLESContext::GLESContext( )
{
	INTERNAL_HANDLER_CREATE( );
}

GLESContext::~GLESContext( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool GLESContext::Create( _handle app_handle )
{
	return INTERNAL_HANDLER( )->Create( app_handle );
}

_ubool GLESContext::MakeCurrentGLContext( )
{
	return INTERNAL_HANDLER( )->MakeCurrentGLContext( );
}

_void GLESContext::FlushGLBuffers( )
{
	INTERNAL_HANDLER( )->FlushGLBuffers( );
}

#endif