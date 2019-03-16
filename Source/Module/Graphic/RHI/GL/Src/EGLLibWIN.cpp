//! @file     EGLLibWIN.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_OPENGLES_USE_POWERVR_SDK_ == 1)

//!	The EGL library file name
#define POWERVR_LIBEGL_DLL_NAME		"libEGL.dll"
#define POWERVR_LIBGLESv2_DLL_NAME	"libGLESv2.dll"

//----------------------------------------------------------------------------
// EGLMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, EGL )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName FuncName = _null;
#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// Load the EGL library
//----------------------------------------------------------------------------

_ubool LoadEGLLibrary( )
{
	ALOG_TRACE( "Loading PowerVR OpenGLES emulator library ..." );

	// Load EGL library
	_handle egl_dll = Platform::LoadLibrary( POWERVR_LIBEGL_DLL_NAME );
	if ( egl_dll == _null )
	{
		ALOG_ERROR_1( "Load '%s' OpenGLES emulator library failed", (const _chara*) POWERVR_LIBEGL_DLL_NAME );
		return _false;
	}

	// Load EGLES v2.0 library
	_handle egles_v2_dll = Platform::LoadLibrary( POWERVR_LIBGLESv2_DLL_NAME );
	if ( egles_v2_dll == _null )
	{
		ALOG_ERROR_1( "Load '%s' OpenGLES emulator library failed", (const _chara*) POWERVR_LIBGLESv2_DLL_NAME );
		return _false;
	}

	// Get EGL functions
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glClearDepthf )
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glStencilOpSeparate )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glStencilFuncSeparate )
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBlendEquation )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBlendEquationSeparate )
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBlendFuncSeparate )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glVertexAttribPointer )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glEnableVertexAttribArray )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDisableVertexAttribArray )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteFramebuffers )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGenFramebuffers )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCheckFramebufferStatus )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glFramebufferTexture2D )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glFramebufferRenderbuffer )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBindRenderbuffer )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glRenderbufferStorage )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGenRenderbuffers )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteRenderbuffers )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetRenderbufferParameteriv )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetFramebufferAttachmentParameteriv )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glIsRenderbuffer )		
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniform1i )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniform1fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniform2fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniform3fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniform4fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniformMatrix2fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniformMatrix3fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUniformMatrix4fv )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetShaderInfoLog )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetShaderiv )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCompileShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glShaderBinary )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glShaderSource )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCreateShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDetachShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteProgram )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glValidateProgram )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetProgramiv )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetProgramInfoLog )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glIsProgram )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glIsShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glLinkProgram )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBindAttribLocation )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glAttachShader )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCreateProgram )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUseProgram )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGetUniformLocation )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glActiveTexture )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBindBuffer )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBindFramebuffer )			
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCompressedTexImage2D )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glCompressedTexSubImage2D )	
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGenerateMipmap )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGenBuffers )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glMapBufferOES )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glUnmapBufferOES )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBufferSubData )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteBuffers )				
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glIsBuffer )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBufferData )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glBindVertexArrayOES )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDeleteVertexArraysOES )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glGenVertexArraysOES )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glIsVertexArrayOES )					
	GET_FUNC_PTR( EGE::EGL, egles_v2_dll, glDiscardFramebufferEXT )					

	GET_FUNC_PTR( EGL, egl_dll, eglGetError )				
	GET_FUNC_PTR( EGL, egl_dll, eglQueryString )				
	GET_FUNC_PTR( EGL, egl_dll, eglCreateContext )				
	GET_FUNC_PTR( EGL, egl_dll, eglCreateWindowSurface )		
	GET_FUNC_PTR( EGL, egl_dll, eglSwapInterval )				
	GET_FUNC_PTR( EGL, egl_dll, eglGetConfigAttrib )			
	GET_FUNC_PTR( EGL, egl_dll, eglBindAPI )					
	GET_FUNC_PTR( EGL, egl_dll, eglInitialize )				
	GET_FUNC_PTR( EGL, egl_dll, eglGetDisplay )				
	GET_FUNC_PTR( EGL, egl_dll, eglChooseConfig )				
	GET_FUNC_PTR( EGL, egl_dll, eglTerminate )					
	GET_FUNC_PTR( EGL, egl_dll, eglDestroySurface )			
	GET_FUNC_PTR( EGL, egl_dll, eglDestroyContext )			
	GET_FUNC_PTR( EGL, egl_dll, eglMakeCurrent )				
	GET_FUNC_PTR( EGL, egl_dll, eglSwapBuffers )					

	ALOG_TRACE( "Load PowerVR OpenGLES emulator library OK" );

	return _true;
}

#elif (_OPENGLES_USE_ADRENO_SDK_ == 1)

_ubool LoadEGLLibrary( )
{
	ALOG_TRACE( "Loading AdrenoSDK OpenGLES emulator library ..." );

	ALOG_TRACE( "Load AdrenoSDK OpenGLES emulator library OK" );

	return _true;
}

#else

_ubool LoadEGLLibrary( )
{
	return _true;
}

#endif
