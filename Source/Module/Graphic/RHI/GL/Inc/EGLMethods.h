//! @file     EGLMethods.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef DEFINE_FUNC_PTR
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) Ret FuncName Args;
#endif

// EGL
DEFINE_FUNC_PTR( 
	const char*, 
	eglQueryString,
	(EGLDisplay dpy, EGLint name)
	)
DEFINE_FUNC_PTR( 
	EGLint, 
	eglGetError,
	(void)
	)
DEFINE_FUNC_PTR( 
	EGLContext, 
	eglCreateContext,
	(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
	)
DEFINE_FUNC_PTR( 
	EGLSurface, 
	eglCreateWindowSurface,
	(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglSwapInterval,
	(EGLDisplay dpy, EGLint interval)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglGetConfigAttrib,
	(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglBindAPI,
	(EGLenum api)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglInitialize,
	(EGLDisplay dpy, EGLint *major, EGLint *minor)
	)
DEFINE_FUNC_PTR( 
	EGLDisplay, 
	eglGetDisplay,
	(EGLNativeDisplayType display_id)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglChooseConfig,
	(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglTerminate,
	(EGLDisplay dpy)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglDestroySurface,
	(EGLDisplay dpy, EGLSurface surface)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglDestroyContext,
	(EGLDisplay dpy, EGLContext ctx)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglMakeCurrent,
	(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
	)
DEFINE_FUNC_PTR( 
	EGLBoolean, 
	eglSwapBuffers,
	(EGLDisplay dpy, EGLSurface surface)
	)