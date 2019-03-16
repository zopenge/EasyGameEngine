//! @file     GLUMethods.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef DEFINE_FUNC_PTR
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) Ret FuncName Args;
#endif

// Standard OpenGL mode
#if (_OPENGLES_ == 0)

// GLU
DEFINE_FUNC_PTR( 
	const GLubyte*, 
	gluErrorString, 
	(GLenum) 
	)
DEFINE_FUNC_PTR( 
	const wchar_t*, 
	gluErrorUnicodeStringEXT, 
	(GLenum) 
	)
DEFINE_FUNC_PTR( 
	void,
	gluPerspective,
    (GLdouble, GLdouble, GLdouble, GLdouble)
	)

#endif