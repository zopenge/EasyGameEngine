//! @file     GLEvents.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

// GL events
#define EGE_GL_EVENT_OFFSET 2200
#define EGE_GL_EVENT_BEGIN( struct_name, id_value )	\
	EGE_USER_EVENT_BEGIN( struct_name, id_value, EGE_GL_EVENT_OFFSET )

//----------------------------------------------------------------------------
// Global Events
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, GLEvents )

DECLARE_COUNTER;

//!	Get the GL error.
EGE_GL_EVENT_BEGIN( GLEventGetError, _GL_EVENT_GET_ERROR )
	EGE_EVENT_CLONE_0( GLEventGetError )
EGE_EVENT_END( )

//!	Get the GL string info.
EGE_GL_EVENT_BEGIN( GLEventGetString, _GL_EVENT_GET_STRING )
	GLenum mName;
	EGE_EVENT_CLONE_1( GLEventGetString, mName )
EGE_EVENT_END( )

//!	Get the GL integer info.
EGE_GL_EVENT_BEGIN( GLEventGetIntegerv, _GL_EVENT_GET_INTEGERV )
	GLenum mName;
	GLint* mParams;
	EGE_EVENT_CLONE_2( GLEventGetIntegerv, mName, mParams )
EGE_EVENT_END( )

//!	Clear buffers.
EGE_GL_EVENT_BEGIN( GLEventClear, _GL_EVENT_CLEAR )
	GLbitfield mMask;
	EGE_EVENT_CLONE_1( GLEventClear, mMask )
EGE_EVENT_END( )

//!	Clear color.
EGE_GL_EVENT_BEGIN( GLEventClearColor, _GL_EVENT_CLEAR_COLOR )
	GLclampf mRed;
	GLclampf mGreen;
	GLclampf mBlue;
	GLclampf mAlpha;
	EGE_EVENT_CLONE_4( GLEventClearColor, mRed, mGreen, mBlue, mAlpha )
EGE_EVENT_END( )

//!	Clear stencil buffer value.
EGE_GL_EVENT_BEGIN( GLEventClearStencil, _GL_EVENT_CLEAR_STENCIL )
	GLint mValue;
	EGE_EVENT_CLONE_1( GLEventClearStencil, mValue )
EGE_EVENT_END( )

//!	Set scissor.
EGE_GL_EVENT_BEGIN( GLEventScissor, _GL_EVENT_SCISSOR )
	GLint	mX;
	GLint	mY;
	GLsizei mWidth;
	GLsizei mHeight;
	EGE_EVENT_CLONE_4( GLEventScissor, mX, mY, mWidth, mHeight )
EGE_EVENT_END( )

//!	Enable.
EGE_GL_EVENT_BEGIN( GLEventEnable, _GL_EVENT_ENABLE )
	GLenum	mCap;
	EGE_EVENT_CLONE_1( GLEventEnable, mCap )
EGE_EVENT_END( )

//!	Disable.
EGE_GL_EVENT_BEGIN( GLEventDisable, _GL_EVENT_DISABLE )
	GLenum	mCap;
	EGE_EVENT_CLONE_1( GLEventDisable, mCap )
EGE_EVENT_END( )

//!	Set the line width.
EGE_GL_EVENT_BEGIN( GLEventLineWidth, _GL_EVENT_LINE_WIDTH )
	GLfloat	mWidth;
	EGE_EVENT_CLONE_1( GLEventLineWidth, mWidth )
EGE_EVENT_END( )

//!	Read pixels.
EGE_GL_EVENT_BEGIN( GLEventReadPixels, _GL_EVENT_READ_PIXELS )
	GLint	mX;
	GLint	mY;
	GLsizei mWidth;
	GLsizei mHeight;
	GLenum	mFormat;
	GLenum	mType;
	GLvoid*	mPixels;
	EGE_EVENT_CLONE_7( GLEventReadPixels, mX, mY, mWidth, mHeight, mFormat, mType, mPixels )
EGE_EVENT_END( )

//!	Set pixels store.
EGE_GL_EVENT_BEGIN( GLEventPixelStorei, _GL_EVENT_PIXEL_STOREI )
	GLenum	mName;
	GLint	mParam;
	EGE_EVENT_CLONE_2( GLEventPixelStorei, mName, mParam )
EGE_EVENT_END( )

//!	Set sub-image 2D.
EGE_GL_EVENT_BEGIN( GLEventTexSubImage2D, _GL_EVENT_TEX_SUB_IMAGE2D )
	GLenum			mTarget;
	GLint			mLevel;
	GLint			mXOffset;
	GLint			mYOffset;
	GLsizei			mWidth;
	GLsizei			mHeight;
	GLenum			mFormat;
	GLenum			mType;
	const GLvoid*	mPixels;
	EGE_EVENT_CLONE_9( GLEventTexSubImage2D, mTarget, mLevel, mXOffset, mYOffset, mWidth, mHeight, mFormat, mType, mPixels )
EGE_EVENT_END( )

//!	Set cull face.
EGE_GL_EVENT_BEGIN( GLEventCullFace, _GL_EVENT_CULL_FACE )
	GLenum	mMode;
	EGE_EVENT_CLONE_1( GLEventCullFace, mMode )
EGE_EVENT_END( )

//!	Set color mask.
EGE_GL_EVENT_BEGIN( GLEventColorMask, _GL_EVENT_COLOR_MASK )
	GLboolean	mRed;
	GLboolean	mGreen;
	GLboolean	mBlue;
	GLboolean	mAlpha;
	EGE_EVENT_CLONE_4( GLEventColorMask, mRed, mGreen, mBlue, mAlpha )
EGE_EVENT_END( )

//!	Set texture level parameter.
EGE_GL_EVENT_BEGIN( GLEventGetTexLevelParameteriv, _GL_EVENT_GET_TEX_LEVEL_PARAMETERIV )
	GLenum	mTarget;
	GLint	mLevel;
	GLenum	mName;
	GLint*	mParams;
	EGE_EVENT_CLONE_4( GLEventGetTexLevelParameteriv, mTarget, mLevel, mName, mParams )
EGE_EVENT_END( )

//!	Set draw buffer.
EGE_GL_EVENT_BEGIN( GLEventDrawBuffer, _GL_EVENT_DRAW_BUFFER )
	GLenum	mMode;
	EGE_EVENT_CLONE_1( GLEventDrawBuffer, mMode )
EGE_EVENT_END( )

//!	Read buffer.
EGE_GL_EVENT_BEGIN( GLEventReadBuffer, _GL_EVENT_READ_BUFFER )
	GLenum	mMode;
	EGE_EVENT_CLONE_1( GLEventReadBuffer, mMode )
EGE_EVENT_END( )

//!	Bind vertex array.
EGE_GL_EVENT_BEGIN( GLEventBindVertexArray, _GL_EVENT_BIND_VERTEX_ARRAY )
	GLuint	mArray;
	EGE_EVENT_CLONE_1( GLEventBindVertexArray, mArray )
EGE_EVENT_END( )

//!	Gen vertex array.
EGE_GL_EVENT_BEGIN( GLEventGenVertexArrays, _GL_EVENT_GEN_VERTEX_ARRAYS )
	GLsizei mNumber;
	GLuint*	mArrays;
	EGE_EVENT_CLONE_2( GLEventGenVertexArrays, mNumber, mArrays )
EGE_EVENT_END( )

//!	Del vertex array.
EGE_GL_EVENT_BEGIN( GLEventDeleteVertexArrays, _GL_EVENT_DELETE_VERTEX_ARRAYS )
	GLsizei			mNumber;
	const GLuint*	mArrays;
	EGE_EVENT_CLONE_2( GLEventDeleteVertexArrays, mNumber, mArrays )
EGE_EVENT_END( )

//!	Clear depth.
EGE_GL_EVENT_BEGIN( GLEventClearDepthf, _GL_EVENT_CLEAR_DEPTHF )
	GLclampf mDepth;
	EGE_EVENT_CLONE_1( GLEventClearDepthf, mDepth )
EGE_EVENT_END( )

//!	Set depth mask.
EGE_GL_EVENT_BEGIN( GLEventDepthMask, _GL_EVENT_DEPTH_MASK )
	GLboolean mFlag;
	EGE_EVENT_CLONE_1( GLEventDepthMask, mFlag )
EGE_EVENT_END( )

//!	Set stencil operations.
EGE_GL_EVENT_BEGIN( GLEventStencilOpSeparate, _GL_EVENT_STENCIL_OP_SEPARATE )
	GLenum	mFace;
	GLenum	mFail;
	GLenum	mZFail;
	GLenum	mZPass;
	EGE_EVENT_CLONE_4( GLEventStencilOpSeparate, mFace, mFail, mZFail, mZPass )
EGE_EVENT_END( )

//!	Set stencil function.
EGE_GL_EVENT_BEGIN( GLEventStencilFuncSeparate, _GL_EVENT_STENCIL_FUNC_SEPARATE )
	GLenum	mFace;
	GLenum	mFunc;
	GLint	mRef;
	GLuint	mMask;
	EGE_EVENT_CLONE_4( GLEventStencilFuncSeparate, mFace, mFunc, mRef, mMask )
EGE_EVENT_END( )

//!	Set blend equation.
EGE_GL_EVENT_BEGIN( GLEventBlendEquation, _GL_EVENT_BLEND_EQUATION )
	GLenum	mMode;
	EGE_EVENT_CLONE_1( GLEventBlendEquation, mMode )
EGE_EVENT_END( )

//!	Set blend equation separate.
EGE_GL_EVENT_BEGIN( GLEventBlendEquationSeparate, _GL_EVENT_BLEND_EQUATION_SEPARATE )
	GLenum	mModeRGB;
	GLenum	mModeAlpha;
	EGE_EVENT_CLONE_2( GLEventBlendEquationSeparate, mModeRGB, mModeAlpha )
EGE_EVENT_END( )

//!	Set blend function separate.
EGE_GL_EVENT_BEGIN( GLEventBlendFuncSeparate, _GL_EVENT_BLEND_FUNC_SEPARATE )
	GLenum mSrcRGB;
	GLenum mDstRGB;
	GLenum mSrcAlpha;
	GLenum mDstAlpha;
	EGE_EVENT_CLONE_4( GLEventBlendFuncSeparate, mSrcRGB, mDstRGB, mSrcAlpha, mDstAlpha )
EGE_EVENT_END( )

//!	Set vertex attribute pointer.
EGE_GL_EVENT_BEGIN( GLEventVertexAttribPointer, _GL_EVENT_VERTEX_ATTRIB_POINTER )
	GLuint			mIndex;
	GLint			mSize;
	GLenum			mType;
	GLboolean		mNormalized;
	GLsizei			mStride;
	const GLvoid*	mPointer;
	EGE_EVENT_CLONE_6( GLEventVertexAttribPointer, mIndex, mSize, mType, mNormalized, mStride, mPointer )
EGE_EVENT_END( )

//!	Enable vertex attribute array.
EGE_GL_EVENT_BEGIN( GLEventEnableVertexAttribArray, _GL_EVENT_ENABLE_VERTEX_ATTRIB_ARRAY )
	GLuint	mIndex;
	EGE_EVENT_CLONE_1( GLEventEnableVertexAttribArray, mIndex )
EGE_EVENT_END( )

//!	Disable vertex attribute array.
EGE_GL_EVENT_BEGIN( GLEventDisableVertexAttribArray, _GL_EVENT_DISABLE_VERTEX_ATTRIB_ARRAY )
	GLuint	mIndex;
	EGE_EVENT_CLONE_1( GLEventDisableVertexAttribArray, mIndex )
EGE_EVENT_END( )

//!	Delete frame buffers.
EGE_GL_EVENT_BEGIN( GLEventDeleteFramebuffers, _GL_EVENT_DELETE_FRAMEBUFFERS )
	GLsizei			mNumber;
	const GLuint*	mFramebuffers;
	EGE_EVENT_CLONE_2( GLEventDeleteFramebuffers, mNumber, mFramebuffers )
EGE_EVENT_END( )

//!	Generate frame buffers.
EGE_GL_EVENT_BEGIN( GLEventGenFramebuffers, _GL_EVENT_GEN_FRAMEBUFFERS )
	GLsizei	mNumber;
	GLuint*	mFramebuffers;
	EGE_EVENT_CLONE_2( GLEventGenFramebuffers, mNumber, mFramebuffers )
EGE_EVENT_END( )

//!	Check frame buffer status.
EGE_GL_EVENT_BEGIN( GLEventCheckFramebufferStatus, _GL_EVENT_CHECK_FRAMEBUFFER_STATUS )
	GLenum	mTarget;
	EGE_EVENT_CLONE_1( GLEventCheckFramebufferStatus, mTarget )
EGE_EVENT_END( )

//!	Set the frame buffer texture 2D.
EGE_GL_EVENT_BEGIN( GLEventFramebufferTexture2D, _GL_EVENT_FRAMEBUFFER_TEXTURE2D )
	GLenum	mTarget;
	GLenum	mAttachment;
	GLenum	mTexTarget;
	GLuint	mTexture;
	GLint	mLevel;
	EGE_EVENT_CLONE_5( GLEventFramebufferTexture2D, mTarget, mAttachment, mTexTarget, mTexture, mLevel )
EGE_EVENT_END( )

//!	Set the frame render buffer.
EGE_GL_EVENT_BEGIN( GLEventFramebufferRenderbuffer, _GL_EVENT_FRAMEBUFFER_RENDERBUFFER )
	GLenum	mTarget;
	GLenum	mAttachment;
	GLenum	mRenderbufferTarget;
	GLuint	mRenderbuffer;
	EGE_EVENT_CLONE_4( GLEventFramebufferRenderbuffer, mTarget, mAttachment, mRenderbufferTarget, mRenderbuffer )
EGE_EVENT_END( )

//!	Bind render buffer.
EGE_GL_EVENT_BEGIN( GLEventBindRenderbuffer, _GL_EVENT_BIND_RENDERBUFFER )
	GLenum	mTarget;
	GLuint	mRenderbuffer;
	EGE_EVENT_CLONE_2( GLEventBindRenderbuffer, mTarget, mRenderbuffer )
EGE_EVENT_END( )

//!	Set render buffer storage.
EGE_GL_EVENT_BEGIN( GLEventRenderbufferStorage, _GL_EVENT_RENDERBUFFER_STORAGE )
	GLenum	mTarget;
	GLenum	mInternalFormat;
	GLsizei mWidth;
	GLsizei mHeight;
	EGE_EVENT_CLONE_4( GLEventRenderbufferStorage, mTarget, mInternalFormat, mWidth, mHeight )
EGE_EVENT_END( )

//!	Generate render buffers.
EGE_GL_EVENT_BEGIN( GLEventGenRenderbuffers, _GL_EVENT_GEN_RENDERBUFFERS )
	GLsizei mNumber;
	GLuint* mRenderbuffers;
	EGE_EVENT_CLONE_2( GLEventGenRenderbuffers, mNumber, mRenderbuffers )
EGE_EVENT_END( )

//!	Delete render buffers.
EGE_GL_EVENT_BEGIN( GLEventDeleteRenderbuffers, _GL_EVENT_DELETE_RENDERBUFFERS )
	GLsizei			mNumber;
	const GLuint*	mRenderbuffers;
	EGE_EVENT_CLONE_2( GLEventDeleteRenderbuffers, mNumber, mRenderbuffers )
EGE_EVENT_END( )

//!	Get render buffer info.
EGE_GL_EVENT_BEGIN( GLEventGetRenderbufferParameteriv, _GL_EVENT_GET_RENDERBUFFER_PARAMETERIV )
	GLenum	mTarget;
	GLenum	mName;
	GLint*	mParams;
	EGE_EVENT_CLONE_3( GLEventGetRenderbufferParameteriv, mTarget, mName, mParams )
EGE_EVENT_END( )

//!	Get framebuffer attachment info.
EGE_GL_EVENT_BEGIN( GLEventGetFramebufferAttachmentParameteriv, _GL_EVENT_GET_FRAMEBUFFER_ATTACHMENT_PARAMETERIV )
	GLenum	mTarget;
	GLenum	mAttachment;
	GLenum	mName;
	GLint*	mParams;
	EGE_EVENT_CLONE_4( GLEventGetFramebufferAttachmentParameteriv, mTarget, mAttachment, mName, mParams )
EGE_EVENT_END( )

//!	Check whether it's render buffer.
EGE_GL_EVENT_BEGIN( GLEventIsRenderbuffer, _GL_EVENT_IS_RENDERBUFFER )
	GLuint	mRenderbuffer;
	EGE_EVENT_CLONE_1( GLEventIsRenderbuffer, mRenderbuffer )
EGE_EVENT_END( )

//!	Bind texture.
EGE_GL_EVENT_BEGIN( GLEventBindTexture, _GL_EVENT_BIND_TEXTURE )
	GLenum	mTarget;
	GLuint	mTexture;
	EGE_EVENT_CLONE_2( GLEventBindTexture, mTarget, mTexture )
EGE_EVENT_END( )

//!	Generate texture.
EGE_GL_EVENT_BEGIN( GLEventGenTextures, _GL_EVENT_GEN_TEXTURES )
	GLsizei mNumber;
	GLuint* mTextures;
	EGE_EVENT_CLONE_2( GLEventGenTextures, mNumber, mTextures )
EGE_EVENT_END( )

//!	Active texture.
EGE_GL_EVENT_BEGIN( GLEventActiveTexture, _GL_EVENT_ACTIVE_TEXTURE )
	GLenum	mTexture;
	EGE_EVENT_CLONE_1( GLEventActiveTexture, mTexture )
EGE_EVENT_END( )

//!	Set texture attribute.
EGE_GL_EVENT_BEGIN( GLEventTexParameteri, _GL_EVENT_TEX_PARAMETERI )
	GLenum	mTarget;
	GLenum	mName;
	GLint	mParam;
	EGE_EVENT_CLONE_3( GLEventTexParameteri, mTarget, mName, mParam )
EGE_EVENT_END( )

//!	Set texture attribute.
EGE_GL_EVENT_BEGIN( GLEventTexParameterf, _GL_EVENT_TEX_PARAMETERF )
	GLenum	mTarget;
	GLenum	mName;
	GLfloat	mParam;
	EGE_EVENT_CLONE_3( GLEventTexParameterf, mTarget, mName, mParam )
EGE_EVENT_END( )

//!	Get texture image.
EGE_GL_EVENT_BEGIN( GLEventGetTexImage, _GL_EVENT_GET_TEX_IMAGE )
	GLenum	mTarget;
	GLint	mLevel;
	GLenum	mFormat;
	GLenum	mType;
	_void*	mPixels;
	EGE_EVENT_CLONE_5( GLEventGetTexImage, mTarget, mLevel, mFormat, mType, mPixels )
EGE_EVENT_END( )

//!	Set texture image 2D.
EGE_GL_EVENT_BEGIN( GLEventTexImage2D, _GL_EVENT_TEX_IMAGE_2D )
	GLenum			mTarget;
	GLint			mLevel;
	GLint			mInternalFormat;
	GLsizei			mWidth;
	GLsizei			mHeight;
	GLint			mBorder;
	GLenum			mFormat;
	GLenum			mType;
	const GLvoid*	mPixels;
	EGE_EVENT_CLONE_9( GLEventTexImage2D, mTarget, mLevel, mInternalFormat, mWidth, mHeight, mBorder, mFormat, mType, mPixels )
EGE_EVENT_END( )

//!	Create shader.
EGE_GL_EVENT_BEGIN( GLEventCreateShader, _GL_EVENT_CREATE_SHADER )
	GLenum	mType;
	EGE_EVENT_CLONE_1( GLEventCreateShader, mType )
EGE_EVENT_END( )

//!	Set shader source code.
EGE_GL_EVENT_BEGIN( GLEventShaderSource, _GL_EVENT_SHADER_SOURCE )
	GLuint			mShader;
	GLsizei			mCount;
	const GLchar**	mString;
	const GLint*	mLength;
	EGE_EVENT_CLONE_4( GLEventShaderSource, mShader, mCount, mString, mLength )
EGE_EVENT_END( )

//!	Get shader info log.
EGE_GL_EVENT_BEGIN( GLEventGetShaderInfoLog, _GL_EVENT_GET_SHADER_INFO_LOG )
	GLuint		mShader;
	GLsizei		mBufSize;
	GLsizei*	mLength;
	GLchar*		mInfoLog;
	EGE_EVENT_CLONE_4( GLEventGetShaderInfoLog, mShader, mBufSize, mLength, mInfoLog );
EGE_EVENT_END( )

//!	Get shader attribute.
EGE_GL_EVENT_BEGIN( GLEventGetShaderiv, _GL_EVENT_GET_SHADERIV )
	GLuint	mShader;
	GLenum	mName;
	GLint*	mParams;
	EGE_EVENT_CLONE_3( GLEventGetShaderiv, mShader, mName, mParams )
EGE_EVENT_END( )

//!	Compile shader.
EGE_GL_EVENT_BEGIN( GLEventCompileShader, _GL_EVENT_COMPILE_SHADER )
	GLuint mShader;
	EGE_EVENT_CLONE_1( GLEventCompileShader, mShader )
EGE_EVENT_END( )

//!	Create program.
EGE_GL_EVENT_BEGIN( GLEventCreateProgram, _GL_EVENT_CREATE_PROGRAM )
	EGE_EVENT_CLONE_0( GLEventCreateProgram )
EGE_EVENT_END( )

//!	Attach shader.
EGE_GL_EVENT_BEGIN( GLEventAttachShader, _GL_EVENT_ATTACH_SHADER )
	GLuint mProgram;
	GLuint mShader;
	EGE_EVENT_CLONE_2( GLEventAttachShader, mProgram, mShader )
EGE_EVENT_END( )

//!	Bind attribute location.
EGE_GL_EVENT_BEGIN( GLEventBindAttribLocation, _GL_EVENT_BIND_ATTRIB_LOCATION )
	GLuint			mProgram;
	GLuint			mIndex;
	const GLchar*	mName;
	EGE_EVENT_CLONE_3( GLEventBindAttribLocation, mProgram, mIndex, mName )
EGE_EVENT_END( )

//!	Link program.
EGE_GL_EVENT_BEGIN( GLEventLinkProgram, _GL_EVENT_LINK_PROGRAM )
	GLuint	mProgram;
	EGE_EVENT_CLONE_1( GLEventLinkProgram, mProgram )
EGE_EVENT_END( )

//!	Use program.
EGE_GL_EVENT_BEGIN( GLEventUseProgram, _GL_EVENT_USE_PROGRAM )
	GLuint	mProgram;
	EGE_EVENT_CLONE_1( GLEventUseProgram, mProgram )
EGE_EVENT_END( )

//!	Get uniform location.
EGE_GL_EVENT_BEGIN( GLEventGetUniformLocation, _GL_EVENT_GET_UNIFORM_LOCATION )
	GLuint			mProgram;
	const GLchar*	mName;
	EGE_EVENT_CLONE_2( GLEventGetUniformLocation, mProgram, mName )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniform1i, _GL_EVENT_UNIFORM_1I )
	GLuint	mLocation;
	GLint	mValue;
	EGE_EVENT_CLONE_2( GLEventUniform1i, mLocation, mValue )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniform1fv, _GL_EVENT_UNIFORM_1FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_3( GLEventUniform1fv, mLocation, mNumber, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniform2fv, _GL_EVENT_UNIFORM_2FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_3( GLEventUniform2fv, mLocation, mNumber, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniform3fv, _GL_EVENT_UNIFORM_3FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_3( GLEventUniform3fv, mLocation, mNumber, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniform4fv, _GL_EVENT_UNIFORM_4FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_3( GLEventUniform4fv, mLocation, mNumber, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniformMatrix2fv, _GL_EVENT_UNIFORM_MATRIX_2FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	GLboolean		mTranspose;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_4( GLEventUniformMatrix2fv, mLocation, mNumber, mTranspose, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniformMatrix3fv, _GL_EVENT_UNIFORM_MATRIX_3FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	GLboolean		mTranspose;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_4( GLEventUniformMatrix3fv, mLocation, mNumber, mTranspose, mValues )
EGE_EVENT_END( )

//!	Set uniform value.
EGE_GL_EVENT_BEGIN( GLEventUniformMatrix4fv, _GL_EVENT_UNIFORM_MATRIX_4FV )
	GLuint			mLocation;
	GLsizei			mNumber;
	GLboolean		mTranspose;
	const GLfloat*	mValues;
	EGE_EVENT_CLONE_4( GLEventUniformMatrix4fv, mLocation, mNumber, mTranspose, mValues )
EGE_EVENT_END( )

//!	Delete shader.
EGE_GL_EVENT_BEGIN( GLEventDeleteShader, _GL_EVENT_DELETE_SHADER )
	GLuint	mShader;
	EGE_EVENT_CLONE_1( GLEventDeleteShader, mShader )
EGE_EVENT_END( )

//!	Detach shader.
EGE_GL_EVENT_BEGIN( GLEventDetachShader, _GL_EVENT_DETACH_SHADER )
	GLuint	mProgram;
	GLuint	mShader;
	EGE_EVENT_CLONE_2( GLEventDetachShader, mProgram, mShader )
EGE_EVENT_END( )

//!	Delete program.
EGE_GL_EVENT_BEGIN( GLEventDeleteProgram, _GL_EVENT_DELETE_PROGRAM )
	GLuint	mProgram;
	EGE_EVENT_CLONE_1( GLEventDeleteProgram, mProgram )
EGE_EVENT_END( )

//!	Validate program.
EGE_GL_EVENT_BEGIN( GLEventValidateProgram, _GL_EVENT_VALIDATE_PROGRAM )
	GLuint	mProgram;
	EGE_EVENT_CLONE_1( GLEventValidateProgram, mProgram )
EGE_EVENT_END( )

//!	Get program info.
EGE_GL_EVENT_BEGIN( GLEventGetProgramiv, _GL_EVENT_GET_PROGRAMIV )
	GLuint	mProgram;
	GLenum	mName;
	GLint*	mParams;
	EGE_EVENT_CLONE_3( GLEventGetProgramiv, mProgram, mName, mParams )
EGE_EVENT_END( )

//!	Get program info log.
EGE_GL_EVENT_BEGIN( GLEventGetProgramInfoLog, _GL_EVENT_GET_PROGRAM_INFO_LOG )
	GLuint		mProgram;
	GLsizei		mBufSize;
	GLsizei*	mLength;
	GLchar*		mInfoLog;
	EGE_EVENT_CLONE_4( GLEventGetProgramInfoLog, mProgram, mBufSize, mLength, mInfoLog )
EGE_EVENT_END( )

//!	Check whether it's program.
EGE_GL_EVENT_BEGIN( GLEventIsProgram, _GL_EVENT_IS_PROGRAM )
	GLuint	mProgram;
	EGE_EVENT_CLONE_1( GLEventIsProgram, mProgram )
EGE_EVENT_END( )

//!	Check whether it's shader.
EGE_GL_EVENT_BEGIN( GLEventIsShader, _GL_EVENT_IS_SHADER )
	GLuint	mShader;
	EGE_EVENT_CLONE_1( GLEventIsShader, mShader )
EGE_EVENT_END( )

//!	Bind buffer.
EGE_GL_EVENT_BEGIN( GLEventBindBuffer, _GL_EVENT_BIND_BUFFER )
	GLenum	mTarget;
	GLuint	mBuffer;
	EGE_EVENT_CLONE_2( GLEventBindBuffer, mTarget, mBuffer )
EGE_EVENT_END( )

//!	Bind framebuffer.
EGE_GL_EVENT_BEGIN( GLEventBindFramebuffer, _GL_EVENT_BIND_FRAMEBUFFER )
	GLenum	mTarget;
	GLuint	mFramebuffer;
	EGE_EVENT_CLONE_2( GLEventBindFramebuffer, mTarget, mFramebuffer )
EGE_EVENT_END( )

//!	Set compressed texture image 2D.
EGE_GL_EVENT_BEGIN( GLEventCompressedTexImage2D, _GL_EVENT_COMPRESSED_TEX_IMAGE_2D )
	GLenum			mTarget;
	GLint			mLevel;
	GLint			mInternalFormat;
	GLsizei			mWidth;
	GLsizei			mHeight;
	GLint			mBorder;
	GLsizei			mImageSize;
	const GLvoid*	mData;
	EGE_EVENT_CLONE_8( GLEventCompressedTexImage2D, mTarget, mLevel, mInternalFormat, mWidth, mHeight, mBorder, mImageSize, mData )
EGE_EVENT_END( )

//!	Set compressed texture sub-image 2D.
EGE_GL_EVENT_BEGIN( GLEventCompressedTexSubImage2D, _GL_EVENT_COMPRESSED_TEX_SUB_IMAGE_2D )
	GLenum			mTarget;
	GLint			mLevel;
	GLint			mXOffset;
	GLint			mYOffset;
	GLsizei			mWidth;
	GLsizei			mHeight;
	GLenum			mFormat;
	GLsizei			mImageSize;
	const GLvoid*	mData;
	EGE_EVENT_CLONE_9( GLEventCompressedTexSubImage2D, mTarget, mLevel, mXOffset, mYOffset, mWidth, mHeight, mFormat, mImageSize, mData )
EGE_EVENT_END( )

//!	Generate mipmap.
EGE_GL_EVENT_BEGIN( GLEventGenerateMipmap, _GL_EVENT_GENERATE_MIPMAP )
	GLenum	mTarget;
	EGE_EVENT_CLONE_1( GLEventGenerateMipmap, mTarget )
EGE_EVENT_END( )

//!	Generate buffers.
EGE_GL_EVENT_BEGIN( GLEventGenBuffers, _GL_EVENT_GEN_BUFFERS )
	GLsizei mNumber;
	GLuint* mBuffers;
	EGE_EVENT_CLONE_2( GLEventGenBuffers, mNumber, mBuffers )
EGE_EVENT_END( )

//!	Update buffer sub-data.
EGE_GL_EVENT_BEGIN( GLEventBufferSubData, _GL_EVENT_BUFFER_SUB_DATA )
	GLenum			mTarget;
	GLintptr		mOffset;
	GLsizeiptr		mSize;
	const GLvoid*	mData;
	EGE_EVENT_CLONE_4( GLEventBufferSubData, mTarget, mOffset, mSize, mData )
EGE_EVENT_END( )

//!	Detele buffers.
EGE_GL_EVENT_BEGIN( GLEventDeleteBuffers, _GL_EVENT_DELETE_BUFFERS )
	GLsizei			mNumber;
	const GLuint*	mBuffers;
	EGE_EVENT_CLONE_2( GLEventDeleteBuffers, mNumber, mBuffers )
EGE_EVENT_END( )

//!	Check whether it's buffer.
EGE_GL_EVENT_BEGIN( GLEventIsBuffer, _GL_EVENT_IS_BUFFER )
	GLuint	mBuffer;
	EGE_EVENT_CLONE_1( GLEventIsBuffer, mBuffer )
EGE_EVENT_END( )

//!	Set buffer data.
EGE_GL_EVENT_BEGIN( GLEventBufferData, _GL_EVENT_BUFFER_DATA )
	GLenum			mTarget;
	GLsizeiptr		mSize;
	const GLvoid*	mData;
	GLenum			mUsage;
	EGE_EVENT_CLONE_4( GLEventBufferData, mTarget, mSize, mData, mUsage )
EGE_EVENT_END( )

//!	Draw arrays.
EGE_GL_EVENT_BEGIN( GLEventDrawArrays, _GL_EVENT_DRAW_ARRAYS )
	GLenum	mMode;
	GLint	mFirst;
	GLsizei	mNumber;
	EGE_EVENT_CLONE_3( GLEventDrawArrays, mMode, mFirst, mNumber )
EGE_EVENT_END( )

//!	Draw elements.
EGE_GL_EVENT_BEGIN( GLEventDrawElements, _GL_EVENT_DRAW_ELEMENTS )
	GLenum			mMode;
	GLsizei			mNumber;
	GLenum			mType;
	const GLvoid*	mIndices;
	EGE_EVENT_CLONE_4( GLEventDrawElements, mMode, mNumber, mType, mIndices )
EGE_EVENT_END( )

//!	Set the viewport.
EGE_GL_EVENT_BEGIN( GLEventViewport, _GL_EVENT_VIEWPORT )
	GLint	mX;
	GLint	mY;
	GLsizei mWidth;
	GLsizei mHeight;
	EGE_EVENT_CLONE_4( GLEventViewport, mX, mY, mWidth, mHeight )
EGE_EVENT_END( )

EGE_END_NAMESPACE_2( )