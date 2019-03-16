//! @file     EGLLibANDROID.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// OpenGLES Function Declaration
//----------------------------------------------------------------------------

typedef void ( GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC )( GLenum mode, GLint first, GLsizei count, GLsizei primcount );
typedef void ( GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC )( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount );

//----------------------------------------------------------------------------
// EGLMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, EGL )

#define DEFINE_FUNC_PTR( FuncDecl, FuncName ) extern FuncDecl FuncName;
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

// OpenGLES mode
#if (_OPENGLES_ == 1)

#undef glMapBufferOES
#undef glUnmapBufferOES
#undef glBindVertexArrayOES
#undef glDeleteVertexArraysOES
#undef glGenVertexArraysOES
#undef glIsVertexArrayOES
#undef glDiscardFramebufferEXT
#undef glDrawArraysInstanced
#undef glDrawElementsInstanced

#define glMapBufferOES			EGL::glMapBufferOES
#define glUnmapBufferOES		EGL::glUnmapBufferOES
#define glBindVertexArrayOES	EGL::glBindVertexArrayOES
#define glDeleteVertexArraysOES	EGL::glDeleteVertexArraysOES
#define glGenVertexArraysOES	EGL::glGenVertexArraysOES
#define glIsVertexArrayOES		EGL::glIsVertexArrayOES
#define glDiscardFramebufferEXT	EGL::glDiscardFramebufferEXT
#define glDrawArraysInstanced	EGL::glDrawArraysInstanced
#define glDrawElementsInstanced	EGL::glDrawElementsInstanced

#endif