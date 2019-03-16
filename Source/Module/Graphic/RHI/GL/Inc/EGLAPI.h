//! @file     EGLAPIEvents.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// EGLMethods
//----------------------------------------------------------------------------

// Windows Platform
#ifdef _PLATFORM_WINDOWS_

	// PowerVR SDK
	#if (_OPENGLES_USE_POWERVR_SDK_ == 1)

		EGE_BEGIN_NAMESPACE_2( EGE, XGL )

		#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (*_##FuncName) Args; extern _##FuncName __##FuncName;
		#include "Module/Graphic/RHI/GL/Inc/GLMethods.h"
		#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
		#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
		#undef DEFINE_FUNC_PTR

		EGE_END_NAMESPACE_2( )

		#define _XEGL_( x )			EGE::XGL::__##x
		#define _EXEGL_( x, ext )	EGE::XGL::__##x##ext

	// Adreno SDK
	#elif (_OPENGLES_USE_ADRENO_SDK_ == 1)

		EGE_BEGIN_NAMESPACE_2( EGE, XGL )

		#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (*_##FuncName) Args; extern _##FuncName __##FuncName;
		#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
		#undef DEFINE_FUNC_PTR

		EGE_END_NAMESPACE_2( )

		#define _EXEGL_( x, ext )	EGE::XGL::__##x##ext

	// Use the original API functions
	#else

		#define _EXEGL_( x, ext ) x

	#endif

// Android Platform
#elif _PLATFORM_ANDROID_

	EGE_BEGIN_NAMESPACE_2( EGE, XGL )

	#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (*_##FuncName) Args; extern _##FuncName __##FuncName;
	#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
	#undef DEFINE_FUNC_PTR

	#define _EXEGL_( x, ext ) EGE::XGL::__##x##ext

	EGE_END_NAMESPACE_2( )

#endif

// Use the standard OpenGL-Interface
#ifndef _XEGL_
#define _XEGL_( x )	x
#endif
#ifndef _EXEGL_
#define _EXEGL_( x, ext ) x##ext
#endif

// Relocate the OpenGL function to XGL (add render events)
#define __glGetError							_XEGL_( glGetError )
#define __glGetString							_XEGL_( glGetString )
#define __glGetIntegerv							_XEGL_( glGetIntegerv )
#define __glClearStencil						_XEGL_( glClearStencil )
#define __glScissor								_XEGL_( glScissor )
#define __glEnable								_XEGL_( glEnable )
#define __glDisable								_XEGL_( glDisable )
#define __glLineWidth							_XEGL_( glLineWidth )
#define __glReadPixels							_XEGL_( glReadPixels )
#define __glClear								_XEGL_( glClear )
#define __glClearColor							_XEGL_( glClearColor )
#define __glPixelStorei							_XEGL_( glPixelStorei )
#define __glTexSubImage2D						_XEGL_( glTexSubImage2D )
#define __glCullFace							_XEGL_( glCullFace )
#define __glColorMask							_XEGL_( glColorMask )
#define __glGetTexLevelParameteriv				_XEGL_( glGetTexLevelParameteriv )
#define __glDrawBuffer							_XEGL_( glDrawBuffer )
#define __glReadBuffer							_XEGL_( glReadBuffer )
#define __glClearDepthf							_XEGL_( glClearDepthf )
#define __glDepthFunc							_XEGL_( glDepthFunc )
#define __glDepthMask							_XEGL_( glDepthMask )
#define __glStencilOpSeparate					_XEGL_( glStencilOpSeparate )
#define __glStencilFuncSeparate					_XEGL_( glStencilFuncSeparate )
#define __glStencilFunc							_XEGL_( glStencilFunc )
#define __glStencilOp							_XEGL_( glStencilOp )
#define __glStencilMask							_XEGL_( glStencilMask )
#define __glBlendEquation						_XEGL_( glBlendEquation )
#define __glBlendEquationSeparate				_XEGL_( glBlendEquationSeparate )
#define __glBlendFuncSeparate					_XEGL_( glBlendFuncSeparate )
#define __glBlendFunc							_XEGL_( glBlendFunc )
#define __glVertexAttribPointer					_XEGL_( glVertexAttribPointer )			
#define __glEnableVertexAttribArray				_XEGL_( glEnableVertexAttribArray )
#define __glDisableVertexAttribArray			_XEGL_( glDisableVertexAttribArray )
#define __glDeleteFramebuffers					_XEGL_( glDeleteFramebuffers )			
#define __glGenFramebuffers						_XEGL_( glGenFramebuffers )				
#define __glCheckFramebufferStatus				_XEGL_( glCheckFramebufferStatus )		
#define __glFramebufferTexture2D				_XEGL_( glFramebufferTexture2D )			
#define __glFramebufferRenderbuffer				_XEGL_( glFramebufferRenderbuffer )		
#define __glBindRenderbuffer					_XEGL_( glBindRenderbuffer )				
#define __glRenderbufferStorage					_XEGL_( glRenderbufferStorage )			
#define __glGenRenderbuffers					_XEGL_( glGenRenderbuffers )				
#define __glDeleteRenderbuffers					_XEGL_( glDeleteRenderbuffers )			
#define __glGetRenderbufferParameteriv			_XEGL_( glGetRenderbufferParameteriv )
#define __glGetFramebufferAttachmentParameteriv	_XEGL_( glGetFramebufferAttachmentParameteriv )
#define __glIsRenderbuffer						_XEGL_( glIsRenderbuffer )
#define __glUniform1i							_XEGL_( glUniform1i )
#define __glUniform1fv							_XEGL_( glUniform1fv )
#define __glUniform2fv							_XEGL_( glUniform2fv )
#define __glUniform3fv							_XEGL_( glUniform3fv )
#define __glUniform4fv							_XEGL_( glUniform4fv )
#define __glUniformMatrix2fv					_XEGL_( glUniformMatrix2fv )
#define __glUniformMatrix3fv					_XEGL_( glUniformMatrix3fv )
#define __glUniformMatrix4fv					_XEGL_( glUniformMatrix4fv )				
#define __glDeleteShader						_XEGL_( glDeleteShader )					
#define __glGetShaderInfoLog					_XEGL_( glGetShaderInfoLog )				
#define __glGetShaderiv							_XEGL_( glGetShaderiv )					
#define __glCompileShader						_XEGL_( glCompileShader )					
#define __glShaderBinary						_XEGL_( glShaderBinary )
#define __glShaderSource						_XEGL_( glShaderSource )					
#define __glCreateShader						_XEGL_( glCreateShader )					
#define __glDetachShader						_XEGL_( glDetachShader )					
#define __glDeleteProgram						_XEGL_( glDeleteProgram )					
#define __glValidateProgram						_XEGL_( glValidateProgram )					
#define __glGetProgramiv						_XEGL_( glGetProgramiv )					
#define __glGetProgramInfoLog					_XEGL_( glGetProgramInfoLog )
#define __glIsProgram							_XEGL_( glIsProgram )					
#define __glIsShader							_XEGL_( glIsShader )					
#define __glLinkProgram							_XEGL_( glLinkProgram )					
#define __glGetAttribLocation					_XEGL_( glGetAttribLocation )			
#define __glBindAttribLocation					_XEGL_( glBindAttribLocation )			
#define __glAttachShader						_XEGL_( glAttachShader )					
#define __glCreateProgram						_XEGL_( glCreateProgram )					
#define __glUseProgram							_XEGL_( glUseProgram )					
#define __glGetUniformLocation					_XEGL_( glGetUniformLocation )			
#define __glBindTexture							_XEGL_( glBindTexture )
#define __glGenTextures							_XEGL_( glGenTextures )
#define __glGenTextures							_XEGL_( glGenTextures )
#define __glDeleteTextures						_XEGL_( glDeleteTextures )					
#define __glActiveTexture						_XEGL_( glActiveTexture )					
#define __glTexParameteri						_XEGL_( glTexParameteri )
#define __glTexParameterf						_XEGL_( glTexParameterf )
#define __glGetTexImage							_XEGL_( glGetTexImage )
#define __glTexImage2D							_XEGL_( glTexImage2D )
#define __glBindBuffer							_XEGL_( glBindBuffer )					
#define __glBindFramebuffer						_XEGL_( glBindFramebuffer )				
#define __glCompressedTexImage2D				_XEGL_( glCompressedTexImage2D )		
#define __glCompressedTexSubImage2D				_XEGL_( glCompressedTexSubImage2D )		
#define __glGenerateMipmap						_XEGL_( glGenerateMipmap )
#define __glGenBuffers							_XEGL_( glGenBuffers )
#define __glBufferSubData						_XEGL_( glBufferSubData )
#define __glDeleteBuffers						_XEGL_( glDeleteBuffers )
#define __glIsBuffer							_XEGL_( glIsBuffer )
#define __glBufferData							_XEGL_( glBufferData )
#define	__glDrawArrays							_XEGL_( glDrawArrays )
#define __glDrawElements						_XEGL_( glDrawElements )
#define __glViewport							_XEGL_( glViewport )
#define __glPolygonMode							_XEGL_( glPolygonMode )
#define __glDebugMessageCallbackARB				_XEGL_( glDebugMessageCallbackARB )
#define __glDebugMessageControlARB				_XEGL_( glDebugMessageControlARB )

// External interfaces
#define __glMapBufferOES						_EXEGL_( glMapBuffer, OES )
#define __glUnmapBufferOES						_EXEGL_( glUnmapBuffer, OES )
#define __glBindVertexArrayOES					_EXEGL_( glBindVertexArray, OES )
#define __glDeleteVertexArraysOES				_EXEGL_( glDeleteVertexArrays, OES )
#define __glGenVertexArraysOES					_EXEGL_( glGenVertexArrays, OES )
#define __glIsVertexArrayOES					_EXEGL_( glIsVertexArray, OES )
#define __glDiscardFramebufferEXT				_EXEGL_( glDiscardFramebuffer, EXT )

// EGL interfaces
#define __eglQueryString						_XEGL_( eglQueryString )
#define __eglGetError							_XEGL_( eglGetError )
#define __eglCreateContext						_XEGL_( eglCreateContext )
#define __eglCreateWindowSurface				_XEGL_( eglCreateWindowSurface )
#define __eglSwapInterval						_XEGL_( eglSwapInterval )
#define __eglGetConfigAttrib					_XEGL_( eglGetConfigAttrib )
#define __eglBindAPI							_XEGL_( eglBindAPI )
#define __eglInitialize							_XEGL_( eglInitialize )
#define __eglGetDisplay							_XEGL_( eglGetDisplay )
#define __eglChooseConfig						_XEGL_( eglChooseConfig )
#define __eglTerminate							_XEGL_( eglTerminate )
#define __eglDestroySurface						_XEGL_( eglDestroySurface )
#define __eglDestroyContext						_XEGL_( eglDestroyContext )
#define __eglMakeCurrent						_XEGL_( eglMakeCurrent )
#define __eglSwapBuffers						_XEGL_( eglSwapBuffers )

//!	Initialize/Finalize API.
extern EGE::_ubool InitializeEGLAPI( );
extern EGE::_void FinalizeEGLAPI( );

// Redefine OpenGLES enumerations and functions rename
#if (_OPENGLES_ == 1)

	#ifndef GL_WRITE_ONLY
		#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
	#endif
	#ifndef GL_READ_ONLY
		#define GL_READ_ONLY GL_BUFFER_ACCESS_OES
	#endif
	#ifndef GL_READ_WRITE
		#define GL_READ_WRITE GL_BUFFER_MAPPED_OES
	#endif

	#ifndef GL_TEXTURE_COMPARE_MODE
		#define GL_TEXTURE_COMPARE_MODE GL_TEXTURE_COMPARE_MODE_EXT
	#endif
	#ifndef GL_TEXTURE_COMPARE_FUNC
		#define GL_TEXTURE_COMPARE_FUNC GL_TEXTURE_COMPARE_FUNC_EXT
	#endif
	#ifndef GL_COMPARE_R_TO_TEXTURE
		#define GL_COMPARE_R_TO_TEXTURE GL_COMPARE_REF_TO_TEXTURE_EXT
	#endif

#else

	#ifndef GL_BGRA
		#define GL_BGRA	GL_BGRA_EXT
	#endif

	#ifndef GL_DEPTH24_STENCIL8
		#define GL_DEPTH24_STENCIL8	GL_DEPTH24_STENCIL8_EXT
	#endif

	#ifndef GL_UNSIGNED_INT_24_8
		#define GL_UNSIGNED_INT_24_8 GL_UNSIGNED_INT_24_8_EXT
	#endif
	
#endif