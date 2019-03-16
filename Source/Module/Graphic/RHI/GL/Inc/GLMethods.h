//! @file     GLMethods.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef DEFINE_FUNC_PTR
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) Ret FuncName Args;
#endif

// GL
DEFINE_FUNC_PTR( 
	GLenum, 
	glGetError, 
	() 
	)
DEFINE_FUNC_PTR( 
	const GLubyte*, 
	glGetString, 
	(GLenum name) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetIntegerv, 
	(GLenum pname, GLint* params)
	)
DEFINE_FUNC_PTR( 
	void, 
	glClear, 
	(GLbitfield mask)
	)
DEFINE_FUNC_PTR( 
	void, 
	glClearColor, 
	(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
	)
DEFINE_FUNC_PTR( 
	void, 
	glPixelStorei, 
	(GLenum pname, GLint param)
	)
DEFINE_FUNC_PTR( 
	void, 
	glTexSubImage2D, 
	(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
	)
DEFINE_FUNC_PTR( 
	void, 
	glCullFace, 
	(GLenum mode)
	)
DEFINE_FUNC_PTR( 
	void, 
	glColorMask, 
	(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetTexLevelParameteriv, 
	(GLenum target, GLint level, GLenum pname, GLint *params)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDrawBuffer, 
	(GLenum mode)
	)
DEFINE_FUNC_PTR( 
	void, 
	glReadBuffer, 
	(GLenum mode)
	)
DEFINE_FUNC_PTR( 
	void, 
	glClearStencil, 
	(GLint s)
	)
DEFINE_FUNC_PTR( 
	void, 
	glScissor, 
	(GLint x, GLint y, GLsizei width, GLsizei height)
	)
DEFINE_FUNC_PTR( 
	void, 
	glEnable, 
	(GLenum cap) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glDisable, 
	(GLenum cap) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glLineWidth, 
	(GLfloat width) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glReadPixels, 
	(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
	)
DEFINE_FUNC_PTR( 
	void, 
	glClearDepthf, 
	(GLclampf depth) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glDepthFunc, 
	(GLenum func)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDepthMask, 
	(GLboolean flag)
	)
DEFINE_FUNC_PTR( 
	void, 
	glStencilOpSeparate, 
	(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glStencilFuncSeparate, 
	(GLenum face, GLenum func, GLint ref, GLuint mask) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glStencilFunc, 
	(GLenum func, GLint ref, GLuint mask)
	)
DEFINE_FUNC_PTR( 
	void, 
	glStencilOp, 
	(GLenum fail, GLenum zfail, GLenum zpass)
	)
DEFINE_FUNC_PTR( 
	void, 
	glStencilMask, 
	(GLuint mask)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBlendEquation, 
	(GLenum mode) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glBlendEquationSeparate, 
	(GLenum modeRGB, GLenum modeAlpha) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glBlendFuncSeparate, 
	(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glBlendFunc, 
	(GLenum sfactor, GLenum dfactor)
	)
DEFINE_FUNC_PTR( 
	void, 
	glVertexAttribPointer, 
	(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glEnableVertexAttribArray, 
	(GLuint index) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glDisableVertexAttribArray, 
	(GLuint index) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteFramebuffers, 
	(GLsizei n, const GLuint* framebuffers) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenFramebuffers, 
	(GLsizei n, GLuint* framebuffers)
	)
DEFINE_FUNC_PTR( 
	GLenum, 
	glCheckFramebufferStatus, 
	(GLenum target) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glFramebufferTexture2D, 
	(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) 
	)
DEFINE_FUNC_PTR( 
	void, 
	glFramebufferRenderbuffer,
	(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindRenderbuffer,
	(GLenum target, GLuint renderbuffer)
	)
DEFINE_FUNC_PTR( 
	void, 
	glRenderbufferStorage,
	(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenRenderbuffers,
	(GLsizei n, GLuint* renderbuffers)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteRenderbuffers,
	(GLsizei n, const GLuint* renderbuffers)
	)		
DEFINE_FUNC_PTR( 
	void, 
	glGetRenderbufferParameteriv,
	(GLenum target, GLenum pname, GLint* params)
	)		
DEFINE_FUNC_PTR( 
	void, 
	glGetFramebufferAttachmentParameteriv,
	(GLenum target, GLenum attachment, GLenum pname, GLint* params)
	)		
DEFINE_FUNC_PTR( 
	GLboolean, 
	glIsRenderbuffer,
	(GLuint renderbuffer)
	)		
DEFINE_FUNC_PTR( 
	void,
	glUniform1i,
	(GLint location, GLint x)
	)
DEFINE_FUNC_PTR( 
	void,
	glUniform1fv,
	(GLint location, GLsizei count, const GLfloat* v)
	)
DEFINE_FUNC_PTR( 
	void,
	glUniform2fv,
	(GLint location, GLsizei count, const GLfloat* v)
	)
DEFINE_FUNC_PTR( 
	void,
	glUniform3fv,
	(GLint location, GLsizei count, const GLfloat* v)
	)
DEFINE_FUNC_PTR( 
	void,
	glUniform4fv,
	(GLint location, GLsizei count, const GLfloat* v)
	)
DEFINE_FUNC_PTR( 
	void,
	glUniformMatrix2fv,
	(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	)
DEFINE_FUNC_PTR( 
	void, 
	glUniformMatrix3fv,
	(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	)
DEFINE_FUNC_PTR( 
	void, 
	glUniformMatrix4fv,
	(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteShader,
	(GLuint shader)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetShaderInfoLog,
	(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetShaderiv,
	(GLuint shader, GLenum pname, GLint* params)
	)		
DEFINE_FUNC_PTR( 
	void, 
	glCompileShader,
	(GLuint shader)
	)
DEFINE_FUNC_PTR( 
	void, 
	glShaderBinary,
	(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
	)
DEFINE_FUNC_PTR( 
	void, 
	glShaderSource,
	(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
	)
DEFINE_FUNC_PTR( 
	GLuint, 
	glCreateShader,
	(GLenum type)
	)
DEFINE_FUNC_PTR( 
	GLuint, 
	glDetachShader,
	(GLuint program, GLuint shader)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteProgram,
	(GLuint program)
	)
DEFINE_FUNC_PTR( 
	void, 
	glValidateProgram,
	(GLuint program)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetProgramiv,
	(GLuint program, GLenum pname, GLint* params)
	)			
DEFINE_FUNC_PTR( 
	void, 
	glGetProgramInfoLog,
	(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
	)			
DEFINE_FUNC_PTR( 
	GLboolean, 
	glIsProgram,
	(GLuint program)
	)
DEFINE_FUNC_PTR( 
	GLboolean, 
	glIsShader,
	(GLuint shader)
	)
DEFINE_FUNC_PTR( 
	void, 
	glLinkProgram,
	(GLuint program)
	)
DEFINE_FUNC_PTR( 
	GLint, 
	glGetAttribLocation,
	(GLuint program, const GLchar* name)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindAttribLocation,
	(GLuint program, GLuint index, const GLchar* name)
	)
DEFINE_FUNC_PTR( 
	void, 
	glAttachShader,
	(GLuint program, GLuint shader)
	)			
DEFINE_FUNC_PTR( 
	GLuint, 
	glCreateProgram,
	(void)
	)
DEFINE_FUNC_PTR( 
	void, 
	glUseProgram,
	(GLuint program)
	)
DEFINE_FUNC_PTR( 
	int, 
	glGetUniformLocation,
	(GLuint program, const GLchar* name)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindTexture,
	(GLenum target, GLuint texture)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenTextures,
	(GLsizei n, GLuint* textures)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteTextures,
	(GLsizei n, const GLuint *textures)
	)
DEFINE_FUNC_PTR( 
	void, 
	glActiveTexture,
	(GLenum texture)
	)
DEFINE_FUNC_PTR( 
	void, 
	glTexParameteri,
	(GLenum target, GLenum pname, GLint param)
	)
DEFINE_FUNC_PTR( 
	void, 
	glTexParameterf,
	(GLenum target, GLenum pname, GLfloat param)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGetTexImage,
	(GLenum target, GLint level, GLenum format, GLenum type, void *pixels)
	)
DEFINE_FUNC_PTR( 
	void, 
	glTexImage2D,
	(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindBuffer,
	(GLenum target, GLuint buffer)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBindFramebuffer,
	(GLenum target, GLuint framebuffer)
	)
DEFINE_FUNC_PTR( 
	void, 
	glCompressedTexImage2D,
	(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
	)
DEFINE_FUNC_PTR( 
	void, 
	glCompressedTexSubImage2D,
	(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenerateMipmap,
	(GLenum target)
	)
DEFINE_FUNC_PTR( 
	void, 
	glGenBuffers,
	(GLsizei n, GLuint* buffers)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBufferSubData,
	(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDeleteBuffers,
	(GLsizei n, const GLuint* buffers)
	)
DEFINE_FUNC_PTR( 
	GLboolean, 
	glIsBuffer,
	(GLuint buffer)
	)
DEFINE_FUNC_PTR( 
	void, 
	glBufferData,
	(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDrawArrays,
	(GLenum mode, GLint first, GLsizei count)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDrawElements,
	(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
	)
DEFINE_FUNC_PTR( 
	void, 
	glViewport,
	(GLint x, GLint y, GLsizei width, GLsizei height)
	)
DEFINE_FUNC_PTR( 
	void, 
	glPolygonMode,
	(GLenum face, GLenum mode)
	)

#if (_OPENGLES_ == 0)

DEFINE_FUNC_PTR( 
	void, 
	glDebugMessageCallbackARB,
	(GLDEBUGPROCARB callback, const void *userParam)
	)
DEFINE_FUNC_PTR( 
	void, 
	glDebugMessageControlARB,
	(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
	)
	
#endif