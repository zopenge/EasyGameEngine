//! @file     GLPlatformWIN.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

AStringPtr	gGLExtensions;
AStringPtr	gEGLExtensions;
_ubool		gGLSupportETC1					= _false;
_ubool		gGLSupportETC2					= _false;
_ubool		gGLSupportInstancedRendering	= _false;
_ubool		gGLSupportVAO					= _false;
_ubool		gGLSupportFBO					= _false;
_ubool		gGLSupportFBODepthStencil		= _false;

//----------------------------------------------------------------------------
// Static Functions Implementation
//----------------------------------------------------------------------------

//!	Get the GL info.
static _void GetGLInfo( )
{
	WLOG_TRACE( L"Getting GL info ..." );

	// Get OpenGL vendor string
	AStringPtr gl_vendor_string = (const _chara*) glGetString( GL_VENDOR );
	if ( gl_vendor_string.IsEmpty( ) )
		gl_vendor_string = "UNKNOWN";

	// Get OpenGL version string
	AStringPtr gl_version_string = (const _chara*) glGetString( GL_VERSION );
	if ( gl_version_string.IsEmpty( ) )
		gl_version_string = "UNKNOWN";

	// Get OpenGL renderer string
	AStringPtr gl_renderer_string = (const _chara*) glGetString( GL_RENDERER );
	if ( gl_renderer_string.IsEmpty( ) )
		gl_renderer_string = "UNKNOWN";

	// Get OpenGL shader language version string
	AStringPtr gl_shader_version_string = (const _chara*) glGetString( GL_SHADING_LANGUAGE_VERSION );
	if ( gl_shader_version_string.IsEmpty( ) )
		gl_shader_version_string = "UNKNOWN";

	// Get the GL extension
	gGLExtensions = (const _chara*) glGetString( GL_EXTENSIONS );

	// Output the OpenGL info
	ALOG_TRACE_1( "OpenGL Vendor: %s", gl_vendor_string.Str( ) );
	ALOG_TRACE_1( "OpenGL Version: %s", gl_version_string.Str( ) );
	ALOG_TRACE_1( "OpenGL Renderer: %s", gl_renderer_string.Str( ) );
	ALOG_TRACE_1( "OpenGL Shader Language Version: %s", gl_shader_version_string.Str( ) );

	// Finished
	WLOG_TRACE( L"Getting GL info OK" );
}

//!	Check ETC1 support.
static _void CheckETC1Feature( const Version& gl_version )
{
	if ( IsGLSupport( "GL_OES_compressed_ETC1_RGB8_texture" ) )
		gGLSupportETC1 = _true;
}

//!	Check ETC2 support.
static _void CheckETC2Feature( const Version& gl_version )
{
}

//!	Check instanced rendering feature.
static _void CheckInstancedRenderingFeature( const Version& gl_version )
{
#if defined(_PLATFORM_WINDOWS_)
	if ( gl_version >= Version( 3, 2, 0, 0 ) )
		gGLSupportInstancedRendering = _true;
#else
	if ( gl_version >= Version( 3, 0, 0, 0 ) )
		gGLSupportInstancedRendering = _true;
#endif
}

//!	Check VAO feature.
static _void CheckVAOFeature( const Version& gl_version )
{
#if defined(_PLATFORM_IOS_)
	// IOS platform always try to enable VAO features
	if ( IsGLSupport( "GL_OES_vertex_array_object" ) || IsGLSupport( "GL_ARB_vertex_array_object" ) )
		gGLSupportVAO = _true;
#elif defined(_PLATFORM_ANDROID_)
	// Android platform always try to enable VAO features if it's GLES 3.0 version
	if ( gl_version >= Version( 3, 0, 0, 0 ) )
	{
		if ( IsGLSupport( "GL_OES_vertex_array_object" ) || IsGLSupport( "GL_ARB_vertex_array_object" ) )
			gGLSupportVAO = _true;
	}
#elif defined(_PLATFORM_WINDOWS_)
	// Windows platform disable VAO features to test as mobile device
	gGLSupportVAO = _false;
#endif
}

//!	Check FBO feature.
static _void CheckFBOFeature( const Version& gl_version )
{
	// The FBO is part of OpenGL 2.0's core, so we don't need to care about it
	if ( gl_version.GetMajorVersion( ) >= 2 || IsGLSupport( "GL_OES_framebuffer_object" ) || IsGLSupport( "GL_ARB_framebuffer_object" ) || IsGLSupport( "GL_EXT_framebuffer_object" ) )
		gGLSupportFBO = _true;

	// Check whether support FBO's stencil depth
	if ( IsGLSupport( "GL_OES_packed_depth_stencil" ) )
		gGLSupportFBODepthStencil = _true;
}

//!	Validate GL features.
static _ubool ValidateGLFeatures( )
{
#define CHECK_FEATURE( feature, x ) \
	if ( feature ) \
		{ WLOG_TRACE_1( L"GL: [%s] OK", (const _charw*)x ); } \
	else \
		{ WLOG_ERROR_1( L"GL: [%s] FAILED", (const _charw*)x ); return _false; }
#define CHECK_OPTIONAL_FEATURE( feature, x ) \
	if ( feature ) \
		{ WLOG_TRACE_1( L"GL: [%s] OK", (const _charw*)x ); } \
	else \
		{ WLOG_WARNING_1( L"GL: [%s] FAILED", (const _charw*)x ); }

	// Required features
	CHECK_FEATURE( gGLSupportFBO, L"FBO" );

	// Optional features
	CHECK_OPTIONAL_FEATURE( gGLSupportETC1, L"ETC1 Compressed Texture" );
	CHECK_OPTIONAL_FEATURE( gGLSupportETC2, L"ETC2 Compressed Texture" );
	CHECK_OPTIONAL_FEATURE( gGLSupportInstancedRendering, L"Instanced Rendering" );
	CHECK_OPTIONAL_FEATURE( gGLSupportVAO, L"VAO" );

	return _true;
}

//----------------------------------------------------------------------------
// GLPlatform Implementation
//----------------------------------------------------------------------------

_ubool IsGLSupport( const _chara* name )
{
	AStringPtr extensions[] = { gGLExtensions, gEGLExtensions };

	for ( _dword i = 0; i < EGE_ARRAY_NUMBER( extensions ); i ++ )
	{
		AStringPtr extension = extensions[i];

		_dword index = extension.SearchL2R( name, _false );
		if ( index != -1 )
		{
			_chara terminator = extension[ index + Platform::StringLength( name ) ];
			if ( terminator == ' ' || terminator == '\0' )
				return _true;
		}
	}

	return _false;
}

_ubool CheckGLFeatures( )
{
	WLOG_TRACE( L"Checking GL features ..." );

	// Get OpenGL info
	GetGLInfo( );

	// Get the OpenGL version
	Version gl_version = GetGLVersion( );
	WLOG_TRACE_1( L"GL version: %s", gl_version.ToWString( ).Str( ) );

	// Output GL extension
	ALOG_TRACE( "GL Extensions: " + gGLExtensions );
	ALOG_TRACE( "EGL Extensions: " + gEGLExtensions );

	// We minimize support GL 2.0 at least
	if ( gl_version < Version( 2, 0, 0, 0 ) )
	{
		WLOG_TRACE_1( L"The GL version: %s is too low, at least it's v2.0", gl_version.ToWString( ).Str( ) );
		return _false;
	}

	// Check features
	CheckETC1Feature( gl_version );
	CheckETC2Feature( gl_version );
	CheckInstancedRenderingFeature( gl_version );
	CheckVAOFeature( gl_version );
	CheckFBOFeature( gl_version );

	// Validate features
	if ( ValidateGLFeatures( ) == _false )
		return _false;

	WLOG_TRACE( L"Checking GL features OK" );

	return _true;
}

Version GetGLVersion( )
{
	//!	The current GL version info
	static GLint major = 0;
	static GLint minor = 0;

	// Try to get GL version
	if ( major == 0 && minor == 0 )
	{
		// Query GL version
		const _chara* gl_ver_string = (const _chara*)glGetString( GL_VERSION );
		EGE_ASSERT( gl_ver_string != _null );

		// Search for the version split character
		_dword index = Platform::SearchL2R( gl_ver_string, "." );
		if ( index != -1 )
		{
			// Get the major and minor version
			major = gl_ver_string[index - 1] - '0';
			minor = gl_ver_string[index + 1] - '0';

			// Check the version range
			EGE_ASSERT( major != 0 && major <= 9 );
			EGE_ASSERT( minor <= 9 );
		}
	}

	return Version( major, minor, 0, 0 );
}

Version GetGLSLVersion( )
{
#if defined(_PLATFORM_WINDOWS_)
	return Version( 1, 2, 0, 0 );
#else
	return Version( 1, 0, 0, 0 );
#endif
}

//----------------------------------------------------------------------------
// GLDrv Features Implementation
//----------------------------------------------------------------------------

_ubool GLDrv::IsSupportETC1( ) const
{
	return gGLSupportETC1;
}

_ubool GLDrv::IsSupportETC2( ) const
{
	return gGLSupportETC2;
}

_ubool GLDrv::IsSupportVAO( ) const
{
	return gGLSupportVAO;
}

_ubool GLDrv::IsSupportInstancedRendering( ) const
{
	return gGLSupportInstancedRendering;
}