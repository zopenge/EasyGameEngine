//! @file     EGLLibANDROID.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#undef glMapBufferOES				
#undef glUnmapBufferOES				
#undef glBindVertexArrayOES
#undef glDeleteVertexArraysOES
#undef glGenVertexArraysOES
#undef glIsVertexArrayOES
#undef glDiscardFramebufferEXT
#undef glDrawArraysInstanced
#undef glDrawElementsInstanced

//----------------------------------------------------------------------------
// EGLMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, EGL )

#define DEFINE_FUNC_PTR( FuncDecl, FuncName ) FuncDecl FuncName = _null;
DEFINE_FUNC_PTR( PFNGLMAPBUFFEROESPROC, glMapBufferOES )
DEFINE_FUNC_PTR( PFNGLUNMAPBUFFEROESPROC, glUnmapBufferOES )
DEFINE_FUNC_PTR( PFNGLBINDVERTEXARRAYOESPROC, glBindVertexArrayOES )
DEFINE_FUNC_PTR( PFNGLDELETEVERTEXARRAYSOESPROC, glDeleteVertexArraysOES )
DEFINE_FUNC_PTR( PFNGLGENVERTEXARRAYSOESPROC, glGenVertexArraysOES )
DEFINE_FUNC_PTR( PFNGLISVERTEXARRAYOESPROC, glIsVertexArrayOES )
DEFINE_FUNC_PTR( PFNGLDISCARDFRAMEBUFFEREXTPROC, glDiscardFramebufferEXT )
DEFINE_FUNC_PTR( PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced )
DEFINE_FUNC_PTR( PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced )
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// Load the EGL library
//----------------------------------------------------------------------------

template< typename Type >
_ubool LoadGLFunc( Type& func_ptr, AStringPtr func_name )
{
	func_ptr = (Type) eglGetProcAddress( func_name.Str( ) );
	if ( func_ptr == _null )
	{
		ALOG_ERROR_2( "Load '%s'(0x%.8x) DLL function failed", func_name.Str( ), (_dword)func_ptr );
		return _false;
	}
	else
	{
		ALOG_TRACE_2( "Load '%s'(0x%.8x) DLL function OK", func_name.Str( ), (_dword) func_ptr );
		return _true;
	}
}

template< typename Type >
_void LoadOptionalGLFunc( Type& func_ptr, AStringPtr func_name )
{
	func_ptr = (Type) eglGetProcAddress( func_name.Str( ) );
	if ( func_ptr == _null )
	{
		ALOG_WARNING_2( "Load '%s'(0x%.8x) DLL function failed", func_name.Str( ), (_dword)func_ptr );
	}
	else
	{
		ALOG_TRACE_2( "Load '%s'(0x%.8x) DLL function OK", func_name.Str( ), (_dword) func_ptr );
	}
}

_ubool LoadEGLLibrary( )
{	
	WLOG_TRACE( L"Load extension functions from EGL library ..." );

	// OpenGLES mode
#if (_OPENGLES_ == 1)
	#define GET_EGL_FUNC_PTR( FuncDecl, FuncName ) if ( LoadGLFunc( EGL::FuncName, #FuncName ) == _false ) { return _false; }
	#define GET_EGL_OPTIONAL_FUNC_PTR( FuncDecl, FuncName ) LoadOptionalGLFunc( EGL::FuncName, #FuncName );

	// Get optional EGL functions
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLMAPBUFFEROESPROC, glMapBufferOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLUNMAPBUFFEROESPROC, glUnmapBufferOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLBINDVERTEXARRAYOESPROC, glBindVertexArrayOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLDELETEVERTEXARRAYSOESPROC, glDeleteVertexArraysOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLGENVERTEXARRAYSOESPROC, glGenVertexArraysOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLISVERTEXARRAYOESPROC, glIsVertexArrayOES )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced )
	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced )
	// The android does not support glDiscardFramebufferEXT well, so we disable it ( but ... only for OVR mode )
//	GET_EGL_OPTIONAL_FUNC_PTR( PFNGLDISCARDFRAMEBUFFEREXTPROC, glDiscardFramebufferEXT )
#endif

	WLOG_TRACE( L"Load extension functions from EGL library successful" );

	return _true;
}
