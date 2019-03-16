//! @file     EXGLMethods.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef DEFINE_FUNC_PTR
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) Ret FuncName Args;
#endif

// EXGL
DEFINE_FUNC_PTR( 
	void*, 
	glMapBufferOES,
	(GLenum target, GLenum access)
	)
DEFINE_FUNC_PTR( 
	GLboolean, 
	glUnmapBufferOES,
	(GLenum target)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindVertexArrayOES,
	(GLuint array)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteVertexArraysOES,
	(GLsizei n, const GLuint *arrays)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenVertexArraysOES,
	(GLsizei n, const GLuint *arrays)
	)
DEFINE_FUNC_PTR( 
	GLboolean, 
	glIsVertexArrayOES,
	(GLuint array)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDiscardFramebufferEXT,
	(GLenum target, GLsizei numAttachments, const GLenum *attachments)
	)