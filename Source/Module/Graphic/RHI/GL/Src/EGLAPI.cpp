//! @file     EGLAPI.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

// Common function
#undef __glGetError							
#undef __glGetString						
#undef __glGetIntegerv						
#undef __glClearStencil						
#undef __glScissor							
#undef __glEnable							
#undef __glDisable							
#undef __glLineWidth						
#undef __glReadPixels						
#undef __glClear							
#undef __glClearColor						
#undef __glPixelStorei						
#undef __glTexSubImage2D					
#undef __glCullFace							
#undef __glColorMask						
#undef __glGetTexLevelParameteriv			
#undef __glDrawBuffer						
#undef __glReadBuffer						
#undef __glClearDepthf						
#undef __glDepthFunc						
#undef __glDepthMask						
#undef __glStencilOpSeparate				
#undef __glStencilFuncSeparate				
#undef __glStencilFunc						
#undef __glStencilOp						
#undef __glStencilMask						
#undef __glBlendEquation					
#undef __glBlendEquationSeparate			
#undef __glBlendFuncSeparate				
#undef __glBlendFunc						
#undef __glVertexAttribPointer				
#undef __glEnableVertexAttribArray			
#undef __glDisableVertexAttribArray			
#undef __glDeleteFramebuffers				
#undef __glGenFramebuffers					
#undef __glCheckFramebufferStatus			
#undef __glFramebufferTexture2D					
#undef __glFramebufferRenderbuffer				
#undef __glBindRenderbuffer						
#undef __glRenderbufferStorage					
#undef __glGenRenderbuffers						
#undef __glDeleteRenderbuffers					
#undef __glGetRenderbufferParameteriv			
#undef __glGetFramebufferAttachmentParameteriv	
#undef __glIsRenderbuffer						
#undef __glUniform1i							
#undef __glUniform1fv							
#undef __glUniform2fv							
#undef __glUniform3fv							
#undef __glUniform4fv							
#undef __glUniformMatrix2fv						
#undef __glUniformMatrix3fv						
#undef __glUniformMatrix4fv						
#undef __glDeleteShader							
#undef __glGetShaderInfoLog						
#undef __glGetShaderiv							
#undef __glCompileShader						
#undef __glShaderBinary							
#undef __glShaderSource							
#undef __glCreateShader							
#undef __glDetachShader							
#undef __glDeleteProgram						
#undef __glValidateProgram								
#undef __glGetProgramiv									
#undef __glGetProgramInfoLog					
#undef __glIsProgram								
#undef __glIsShader									
#undef __glLinkProgram								
#undef __glGetAttribLocation
#undef __glBindAttribLocation						
#undef __glAttachShader									
#undef __glCreateProgram								
#undef __glUseProgram								
#undef __glGetUniformLocation						
#undef __glBindTexture							
#undef __glGenTextures							
#undef __glGenTextures							
#undef __glDeleteTextures								
#undef __glActiveTexture								
#undef __glTexParameteri						
#undef __glTexParameterf						
#undef __glGetTexImage							
#undef __glTexImage2D							
#undef __glBindBuffer								
#undef __glBindFramebuffer							
#undef __glCompressedTexImage2D						
#undef __glCompressedTexSubImage2D						
#undef __glGenerateMipmap						
#undef __glGenBuffers							
#undef __glBufferSubData						
#undef __glDeleteBuffers				
#undef __glIsBuffer						
#undef __glBufferData					
#undef __glDrawArrays					
#undef __glDrawElements					
#undef __glViewport						
#undef __glPolygonMode					
#undef __glDebugMessageCallbackARB					
#undef __glDebugMessageControlARB					

// External interfaces
#undef __glMapBufferOES							
#undef __glUnmapBufferOES						
#undef __glBindVertexArrayOES				
#undef __glDeleteVertexArraysOES			
#undef __glGenVertexArraysOES				
#undef __glIsVertexArrayOES					
#undef __glDiscardFramebufferEXT			

// EGL interfaces
#undef __eglQueryString							
#undef __eglGetError							
#undef __eglCreateContext						
#undef __eglCreateWindowSurface					
#undef __eglSwapInterval						
#undef __eglGetConfigAttrib						
#undef __eglBindAPI								
#undef __eglInitialize							
#undef __eglGetDisplay							
#undef __eglChooseConfig						
#undef __eglTerminate							
#undef __eglDestroySurface						
#undef __eglDestroyContext						
#undef __eglMakeCurrent							
#undef __eglSwapBuffers							

//----------------------------------------------------------------------------
// EGL-SDK Implementations
//----------------------------------------------------------------------------

// Windows Platform
#ifdef _PLATFORM_WINDOWS_

	// PowerVR SDK
	#if (_OPENGLES_USE_POWERVR_SDK_ == 1)

	EGE_BEGIN_NAMESPACE_2( EGE, XGL )
	#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName __##FuncName = _null;
	#include "Module/Graphic/RHI/GL/Inc/GLMethods.h"
	#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
	#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
	#undef DEFINE_FUNC_PTR
	EGE_END_NAMESPACE_2( )

	//! Load EGL-SDK.
	static _ubool LoadEGLSDK( )
	{
		ALOG_TRACE( "Loading PowerVR OpenGLES emulator library ..." );

		//!	The EGL library file name
		const _chara* libegl_dll_filename = "PowerVRSDK/libEGL.dll";
		const _chara* libgles_v2_filename = "PowerVRSDK/libGLESv2.dll";

		// Load EGL library
		_handle egl_dll = Platform::LoadLibrary( libegl_dll_filename );
		if ( egl_dll == _null )
		{
			ALOG_ERROR_1( "Load '%s' PowerVR emulator library failed", libegl_dll_filename );
			return _false;
		}

		// Load GLES v2.0 library
		_handle gles_v2_dll = Platform::LoadLibrary( libgles_v2_filename );
		if ( gles_v2_dll == _null )
		{
			ALOG_ERROR_1( "Load '%s' PowerVR emulator library failed", libgles_v2_filename );
			return _false;
		}

		// Load functions from EGL-SDK
		#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) GET_FUNC_PTR_FROM_DLL( egl_dll, EGE::XGL::__##FuncName, EGE::XGL::_##FuncName, #FuncName, ; )
		#include "Module/Graphic/RHI/GL/Inc/EGLMethods.h"
		#undef DEFINE_FUNC_PTR
		#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) GET_FUNC_PTR_FROM_DLL( gles_v2_dll, EGE::XGL::__##FuncName, EGE::XGL::_##FuncName, #FuncName, ; )
		#include "Module/Graphic/RHI/GL/Inc/GLMethods.h"
		#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
		#undef DEFINE_FUNC_PTR

		ALOG_TRACE( "Loading PowerVR OpenGLES emulator library OK" );

		// Initialize GLSL optimizer
		if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGLES20 ) == _false )
			return _false;

		return _true;
	}

	//!	Unload EGL-SDK.
	static _void UnloadEGLSDK( )
	{

	}

	// Adreno SDK
	#elif (_OPENGLES_USE_ADRENO_SDK_ == 1)

	EGE_BEGIN_NAMESPACE_2( EGE, XGL )
	#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName __##FuncName = _null;
	#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
	#undef DEFINE_FUNC_PTR
	EGE_END_NAMESPACE_2( )

	//! Load EGL-SDK.
	static _ubool LoadEGLSDK( )
	{
		// Initialize GLSL optimizer
		if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGLES20 ) == _false )
			return _false;

		return _true;
	}

	//!	Unload EGL-SDK.
	static _void UnloadEGLSDK( )
	{

	}

	#else

	//! Load EGL-SDK.
	static _ubool LoadEGLSDK( )
	{
		// Initialize GLSL optimizer
		if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGL ) == _false )
			return _false;

		return _true;
	}

	//!	Unload EGL-SDK.
	static _void UnloadEGLSDK( )
	{

	}

	#endif

// Android Platform
#elif _PLATFORM_ANDROID_

EGE_BEGIN_NAMESPACE_2( EGE, XGL )
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName __##FuncName = _null;
#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
#undef DEFINE_FUNC_PTR
EGE_END_NAMESPACE_2( )

template< typename Type >
_void LoadGLFunc( Type& func_ptr, AStringPtr func_name )
{
	func_ptr = (Type)eglGetProcAddress( func_name.Str( ) );
	if ( func_ptr == _null )
	{
		ALOG_WARNING_2( "Load '%s'(0x%.16llx) Android-GL function failed", func_name.Str( ), (_qword)func_ptr );
	}
	else
	{
		ALOG_TRACE_2( "Load '%s'(0x%.16llx) Android-GL function OK", func_name.Str( ), (_qword)func_ptr );
	}
}

//! Load EGL-SDK.
static _ubool LoadEGLSDK( )
{
	ALOG_TRACE( "Loading Andriod EX-OpenGL library ..." );

	// Load functions from EGL-SDK
	#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) LoadGLFunc( EGE::XGL::__##FuncName, #FuncName );
	#include "Module/Graphic/RHI/GL/Inc/EXGLMethods.h"
	#undef DEFINE_FUNC_PTR

	ALOG_TRACE( "Loading Andriod EX-OpenGL library OK" );

	// Initialize GLSL optimizer
	if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGLES20 ) == _false )
		return _false;

	return _true;
}

//!	Unload EGL-SDK.
static _void UnloadEGLSDK( )
{

}

// IOS Platform
#elif _PLATFORM_IOS_

//! Load EGL-SDK.
static _ubool LoadEGLSDK( )
{
	// Initialize GLSL optimizer
	if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGLES20 ) == _false )
		return _false;

	return _true;
}

//!	Unload EGL-SDK.
static _void UnloadEGLSDK( )
{
	
}

// Chrome Platform
#elif _PLATFORM_CHROME_

//! Load EGL-SDK.
static _ubool LoadEGLSDK( )
{
	// Initialize GLSL optimizer
	if ( GLSLOptimizer::GetInstance( ).Initialize( kGlslTargetOpenGLES20 ) == _false )
		return _false;

	return _true;
}

//!	Unload EGL-SDK.
static _void UnloadEGLSDK( )
{

}

#endif

//----------------------------------------------------------------------------
// EGLMethods Implementations
//----------------------------------------------------------------------------

_ubool InitializeEGLAPI( )
{
	if ( LoadEGLSDK( ) == _false )
		return _false;

	return _true;
}

_void FinalizeEGLAPI( )
{
	UnloadEGLSDK( );
}