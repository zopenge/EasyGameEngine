//! @file     EGLLibWIN.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

#if (_OPENGLES_USE_POWERVR_SDK_ == 1)

//----------------------------------------------------------------------------
// EGLMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, EGL )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (__stdcall *_##FuncName) Args;
#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
#undef DEFINE_FUNC_PTR

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) extern _##FuncName FuncName;
#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//!	The EGL library file name
#define POWERVR_LIBEGL_DLL_NAME		"libEGL.dll"
#define POWERVR_LIBGLESv2_DLL_NAME	"libGLESv2.dll"

// Relocate the extension OpenGL function to DLL
#define glClearDepthf							EGL::glClearDepthf
#define glStencilOpSeparate						EGL::glStencilOpSeparate
#define glStencilFuncSeparate					EGL::glStencilFuncSeparate
#define glBlendEquation							EGL::glBlendEquation
#define glBlendEquationSeparate					EGL::glBlendEquationSeparate
#define glBlendFuncSeparate						EGL::glBlendFuncSeparate
#define glVertexAttribPointer					EGL::glVertexAttribPointer			
#define glEnableVertexAttribArray				EGL::glEnableVertexAttribArray		
#define glDisableVertexAttribArray				EGL::glDisableVertexAttribArray		
#define glDeleteFramebuffers					EGL::glDeleteFramebuffers			
#define glGenFramebuffers						EGL::glGenFramebuffers				
#define glCheckFramebufferStatus				EGL::glCheckFramebufferStatus		
#define glFramebufferTexture2D					EGL::glFramebufferTexture2D			
#define glFramebufferRenderbuffer				EGL::glFramebufferRenderbuffer		
#define glBindRenderbuffer						EGL::glBindRenderbuffer				
#define glRenderbufferStorage					EGL::glRenderbufferStorage			
#define glGenRenderbuffers						EGL::glGenRenderbuffers				
#define glDeleteRenderbuffers					EGL::glDeleteRenderbuffers			
#define glGetRenderbufferParameteriv			EGL::glGetRenderbufferParameteriv
#define glGetFramebufferAttachmentParameteriv	EGL::glGetFramebufferAttachmentParameteriv
#define glIsRenderbuffer						EGL::glIsRenderbuffer
#define glUniform1i								EGL::glUniform1i
#define glUniform1fv							EGL::glUniform1fv
#define glUniform2fv							EGL::glUniform2fv
#define glUniform3fv							EGL::glUniform3fv
#define glUniform4fv							EGL::glUniform4fv
#define glUniformMatrix2fv						EGL::glUniformMatrix2fv
#define glUniformMatrix3fv						EGL::glUniformMatrix3fv
#define glUniformMatrix4fv						EGL::glUniformMatrix4fv				
#define glDeleteShader							EGL::glDeleteShader					
#define glGetShaderInfoLog						EGL::glGetShaderInfoLog				
#define glGetShaderiv							EGL::glGetShaderiv					
#define glCompileShader							EGL::glCompileShader					
#define glShaderBinary							EGL::glShaderBinary
#define glShaderSource							EGL::glShaderSource					
#define glCreateShader							EGL::glCreateShader					
#define glDetachShader							EGL::glDetachShader					
#define glDeleteProgram							EGL::glDeleteProgram					
#define glValidateProgram						EGL::glValidateProgram					
#define glGetProgramiv							EGL::glGetProgramiv					
#define glGetProgramInfoLog						EGL::glGetProgramInfoLog
#define glIsProgram								EGL::glIsProgram					
#define glIsShader								EGL::glIsShader					
#define glLinkProgram							EGL::glLinkProgram					
#define glBindAttribLocation					EGL::glBindAttribLocation			
#define glAttachShader							EGL::glAttachShader					
#define glCreateProgram							EGL::glCreateProgram					
#define glUseProgram							EGL::glUseProgram					
#define glGetUniformLocation					EGL::glGetUniformLocation			
#define glActiveTexture							EGL::glActiveTexture					
#define glBindBuffer							EGL::glBindBuffer					
#define glBindFramebuffer						EGL::glBindFramebuffer				
#define glCompressedTexImage2D					EGL::glCompressedTexImage2D		
#define glCompressedTexSubImage2D				EGL::glCompressedTexSubImage2D		
#define glGenerateMipmap						EGL::glGenerateMipmap
#define glGenBuffers							EGL::glGenBuffers
#define glMapBufferOES							EGL::glMapBufferOES
#define glUnmapBufferOES						EGL::glUnmapBufferOES
#define glBufferSubData							EGL::glBufferSubData
#define glDeleteBuffers							EGL::glDeleteBuffers
#define glIsBuffer								EGL::glIsBuffer
#define glBufferData							EGL::glBufferData
#define glBindVertexArrayOES					EGL::glBindVertexArrayOES
#define glDeleteVertexArraysOES					EGL::glDeleteVertexArraysOES
#define glGenVertexArraysOES					EGL::glGenVertexArraysOES
#define glIsVertexArrayOES						EGL::glIsVertexArrayOES
#define glDiscardFramebufferEXT					EGL::glDiscardFramebufferEXT

#define eglGetError								EGL::eglGetError
#define eglQueryString							EGL::eglQueryString
#define eglCreateContext						EGL::eglCreateContext
#define eglCreateWindowSurface					EGL::eglCreateWindowSurface
#define eglSwapInterval							EGL::eglSwapInterval
#define eglGetConfigAttrib						EGL::eglGetConfigAttrib
#define eglBindAPI								EGL::eglBindAPI
#define eglInitialize							EGL::eglInitialize
#define eglGetDisplay							EGL::eglGetDisplay
#define eglChooseConfig							EGL::eglChooseConfig
#define eglTerminate							EGL::eglTerminate
#define eglDestroySurface						EGL::eglDestroySurface
#define eglDestroyContext						EGL::eglDestroyContext
#define eglMakeCurrent							EGL::eglMakeCurrent
#define eglSwapBuffers							EGL::eglSwapBuffers

#elif (_OPENGLES_USE_ADRENO_SDK_ == 1)

#endif