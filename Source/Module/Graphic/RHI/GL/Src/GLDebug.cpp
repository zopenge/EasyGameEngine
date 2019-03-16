//! @file     GLDebug.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// Global Functions Implementation
//----------------------------------------------------------------------------

#if (_ENABLE_GL_DEBUG == 1)

//!	When GL debug callback.
static void OnGLDebugProcCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam )
{
	EGE_ASSERT( message != _null );

	// https://gitlab.com/freedroid/freedroid-src/blob/master/src/open_gl_debug.c
	// Ignore certain message IDs
	// "Waste of memory: Texture 0 has mipmaps, while it's min filter is inconsistent with mipmaps."
	// Possible nvidia bug in version 313.30, ignore it for now
	if ( id == 131204 )
		return;

	// https://lva.cg.tuwien.ac.at/cgue/wiki/doku.php?id=students:debugcontext
	// Program/shader state performance warning:
	// Fragment Shader is going to be recompiled because the shader key based on GL state mismatches.
	if ( id == 131218 )
		return;

	// Do not display notifications
	if ( severity == GL_DEBUG_SEVERITY_NOTIFICATION )
		return;

	// Get the source string
	AStringPtr source_string;
	switch ( source )
	{
		case GL_DEBUG_SOURCE_API:				source_string = "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		source_string = "WINDOW_SYSTEM"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:	source_string = "SHADER_COMPILER"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:		source_string = "THIRD_PARTY"; break;
		case GL_DEBUG_SOURCE_APPLICATION:		source_string = "APPLICATION"; break;
		case GL_DEBUG_SOURCE_OTHER:				source_string = "OTHER"; break;
		default:
			source_string = "UNKNOWN";
			break;
	}

	// Get the debug type string
	AStringPtr debug_type_string;
	switch ( type )
	{
		case GL_DEBUG_TYPE_ERROR:				debug_type_string = "ERROR"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	debug_type_string = "DEPRECATED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	debug_type_string = "UNDEFINED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:			debug_type_string = "PERFORMANCE"; break;
		case GL_DEBUG_TYPE_PORTABILITY:			debug_type_string = "PORTABILITY"; break;
		case GL_DEBUG_TYPE_MARKER:				debug_type_string = "MARKER"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:			debug_type_string = "PUSH_GROUP"; break;
		case GL_DEBUG_TYPE_POP_GROUP:			debug_type_string = "POP_GROUP"; break;
		case GL_DEBUG_TYPE_OTHER:				debug_type_string = "OTHER"; break;
		default:
			debug_type_string = "UNKNOWN";
			break;
	}

	// Get the severity string
	AStringPtr severity_string;
	switch ( severity )
	{
		case GL_DEBUG_SEVERITY_LOW:				severity_string = "LOW"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:			severity_string = "MEDIUM"; break;
		case GL_DEBUG_SEVERITY_HIGH:			severity_string = "HIGH"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	severity_string = "NOTIFICATION"; break;
		default:
			severity_string = "UNKNOWN";
			break;
	}

	// Output log
	ALOG_DEBUG_4( "GLDebug[%s][%s][%s]: %s", source_string.Str( ), debug_type_string.Str( ), severity_string.Str( ), message );
}

#endif

//----------------------------------------------------------------------------
// GLDebug Implementation
//----------------------------------------------------------------------------

GLDebug::GLDebug( )
{
}

GLDebug::~GLDebug( )
{
}

_ubool GLDebug::Initialize( )
{
#if (_ENABLE_GL_DEBUG == 1)
	GL_CHECK_ERROR( __glEnable( GL_DEBUG_OUTPUT ) );
	GL_CHECK_ERROR( __glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS ) );

	GLint flags;
	GL_CHECK_ERROR( __glGetIntegerv( GL_CONTEXT_FLAGS, &flags ) );
	if ( flags & GL_CONTEXT_FLAG_DEBUG_BIT )
	{
		GL_CHECK_ERROR( __glDebugMessageCallbackARB( (GLDEBUGPROCARB)OnGLDebugProcCallback, _null ) );
		GL_CHECK_ERROR( __glDebugMessageControlARB( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, _null, GL_TRUE ) );
	}
#endif

	return _true;
}