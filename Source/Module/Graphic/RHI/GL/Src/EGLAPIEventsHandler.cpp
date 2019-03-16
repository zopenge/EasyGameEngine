//! @file     EGLAPIEventsHandler.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

// Implement them outside.
extern _void ProcessEvent( GLEventInitRenderContext& event );
extern _void ProcessEvent( GLEventFinalizeRenderContext& event );
extern _void ProcessEvent( GLEventPresentRenderBuffers& event );

#if (_ENABLE_GL_API_EVENT_DRIVER_MODE == 1)

//----------------------------------------------------------------------------
// GLPlatform Function Implementations
//----------------------------------------------------------------------------

static Lock* sEGLAPILocker = _null;

_ubool InitializeEGLAPI( )
{
	sEGLAPILocker = new Lock( );

	return _true;
}

_void FinalizeEGLAPI( )
{
	EGE_DELETE( sEGLAPILocker );
}

//----------------------------------------------------------------------------
// GLPlatform Helpful Function Implementations
//----------------------------------------------------------------------------

//!	Check whether it's async event.
static _ubool IsAsyncEvent( _dword event_id )
{
	switch ( event_id )
	{
		case _GL_EVENT_PRESENT_RENDER_BUFFERS:
			return _true;

		default:
			break;
	}

	return _false;
}

//----------------------------------------------------------------------------
// GLPlatform Event Function Implementations
//----------------------------------------------------------------------------

_void ProcessEvent( GLEventGetError& event )
{
	event.mRet = _GL_API_GET_FUN(GetError)( );
}

_void ProcessEvent( GLEventGetString& event )
{
	event.mRet = (_qword) _GL_API_GET_FUN(GetString)( event.mName );
}

_void ProcessEvent( GLEventGetIntegerv& event )
{
	_GL_API_GET_FUN(GetIntegerv)( event.mName, event.mParams );
}

_void ProcessEvent( GLEventClear& event )
{
	_GL_API_GET_FUN(Clear)( event.mMask );
}

_void ProcessEvent( GLEventClearColor& event )
{
	_GL_API_GET_FUN(ClearColor)( event.mRed, event.mGreen, event.mBlue, event.mAlpha );
}

_void ProcessEvent( GLEventClearStencil& event )
{
	_GL_API_GET_FUN(ClearStencil)( event.mValue );
}

_void ProcessEvent( GLEventScissor& event )
{
	_GL_API_GET_FUN(Scissor)( event.mX, event.mY, event.mWidth, event.mHeight );
}

_void ProcessEvent( GLEventEnable& event )
{
	_GL_API_GET_FUN(Enable)( event.mCap );
}

_void ProcessEvent( GLEventDisable& event )
{
	_GL_API_GET_FUN(Disable)( event.mCap );
}

_void ProcessEvent( GLEventLineWidth& event )
{
	_GL_API_GET_FUN(LineWidth)( event.mWidth );
}

_void ProcessEvent( GLEventReadPixels& event )
{
	_GL_API_GET_FUN(ReadPixels)( event.mX, event.mY, event.mWidth, event.mHeight, event.mFormat, event.mType, event.mPixels );
}

_void ProcessEvent( GLEventPixelStorei& event )
{
	_GL_API_GET_FUN(PixelStorei)( event.mName, event.mParam );
}

_void ProcessEvent( GLEventTexSubImage2D& event )
{
	_GL_API_GET_FUN(TexSubImage2D)( event.mTarget, event.mLevel, event.mXOffset, event.mYOffset, event.mWidth, event.mHeight, event.mFormat, event.mType, event.mPixels );
}

_void ProcessEvent( GLEventCullFace& event )
{
	_GL_API_GET_FUN(CullFace)( event.mMode );
}

_void ProcessEvent( GLEventColorMask& event )
{
	_GL_API_GET_FUN(ColorMask)( event.mRed, event.mGreen, event.mBlue, event.mAlpha );
}

_void ProcessEvent( GLEventGetTexLevelParameteriv& event )
{
	_GL_API_GET_FUN(GetTexLevelParameteriv)( event.mTarget, event.mLevel, event.mName, event.mParams );
}

_void ProcessEvent( GLEventDrawBuffer& event )
{
	_GL_API_GET_FUN(DrawBuffer)( event.mMode );
}

_void ProcessEvent( GLEventReadBuffer& event )
{
	_GL_API_GET_FUN(ReadBuffer)( event.mMode );
}

_void ProcessEvent( GLEventBindVertexArray& event )
{
	_GL_API_GET_FUN(BindVertexArray)( event.mArray );
}

_void ProcessEvent( GLEventGenVertexArrays& event )
{
	_GL_API_GET_FUN(GenVertexArrays)( event.mNumber, event.mArrays );
}

_void ProcessEvent( GLEventDeleteVertexArrays& event )
{
	_GL_API_GET_FUN(DeleteVertexArrays)( event.mNumber, event.mArrays );
}

_void ProcessEvent( GLEventClearDepthf& event )
{
	_GL_API_GET_FUN(ClearDepthf)( event.mDepth );
}

_void ProcessEvent( GLEventDepthMask& event )
{
	_GL_API_GET_FUN(DepthMask)( event.mFlag );
}

_void ProcessEvent( GLEventBindTexture& event )
{
	_GL_API_GET_FUN(BindTexture)( event.mTarget, event.mTexture );
}

_void ProcessEvent( GLEventGenTextures& event )
{
	_GL_API_GET_FUN(GenTextures)( event.mNumber, event.mTextures );
}

_void ProcessEvent( GLEventActiveTexture& event )
{
	_GL_API_GET_FUN(ActiveTexture)( event.mTexture );
}

_void ProcessEvent( GLEventTexParameteri& event )
{
	_GL_API_GET_FUN(TexParameteri)( event.mTarget, event.mName, event.mParam );
}

_void ProcessEvent( GLEventTexParameterf& event )
{
	_GL_API_GET_FUN(TexParameterf)( event.mTarget, event.mName, event.mParam );
}

_void ProcessEvent( GLEventGetTexImage& event )
{
	_GL_API_GET_FUN(GetTexImage)( event.mTarget, event.mLevel, event.mFormat, event.mType, event.mPixels );
}

_void ProcessEvent( GLEventTexImage2D& event )
{
	_GL_API_GET_FUN(TexImage2D)( event.mTarget, event.mLevel, event.mInternalFormat, event.mWidth, event.mHeight, event.mBorder, event.mFormat, event.mType, event.mPixels );
}

_void ProcessEvent( GLEventCreateShader& event )
{
	event.mRet = _GL_API_GET_FUN(CreateShader)( event.mType );
}

_void ProcessEvent( GLEventShaderSource& event )
{
	_GL_API_GET_FUN(ShaderSource)( event.mShader, event.mCount, event.mString, event.mLength );
}

_void ProcessEvent( GLEventCompileShader& event )
{
	_GL_API_GET_FUN(CompileShader)( event.mShader );
}

_void ProcessEvent( GLEventGetShaderInfoLog& event )
{
	_GL_API_GET_FUN(GetShaderInfoLog)( event.mShader, event.mBufSize, event.mLength, event.mInfoLog );
}

_void ProcessEvent( GLEventGetShaderiv& event )
{
	_GL_API_GET_FUN(GetShaderiv)( event.mShader, event.mName, event.mParams );
}

_void ProcessEvent( GLEventCreateProgram& event )
{
	event.mRet = _GL_API_GET_FUN(CreateProgram)( );
}

_void ProcessEvent( GLEventAttachShader& event )
{
	_GL_API_GET_FUN(AttachShader)( event.mProgram, event.mShader );
}

_void ProcessEvent( GLEventBindAttribLocation& event )
{
	_GL_API_GET_FUN(BindAttribLocation)( event.mProgram, event.mIndex, event.mName );
}

_void ProcessEvent( GLEventLinkProgram& event )
{
	_GL_API_GET_FUN(LinkProgram)( event.mProgram );
}

_void ProcessEvent( GLEventUseProgram& event )
{
	_GL_API_GET_FUN(UseProgram)( event.mProgram );
}

_void ProcessEvent( GLEventGetUniformLocation& event )
{
	event.mRet = _GL_API_GET_FUN(GetUniformLocation)( event.mProgram, event.mName );
}

_void ProcessEvent( GLEventStencilOpSeparate& event )
{
	_GL_API_GET_FUN(StencilOpSeparate)( event.mFace, event.mFail, event.mZFail, event.mZPass );
}

_void ProcessEvent( GLEventStencilFuncSeparate& event )
{
	_GL_API_GET_FUN(StencilFuncSeparate)( event.mFace, event.mFunc, event.mRef, event.mMask );
}

_void ProcessEvent( GLEventBlendEquation& event )
{
	_GL_API_GET_FUN(BlendEquation)( event.mMode );
}

_void ProcessEvent( GLEventBlendEquationSeparate& event )
{
	_GL_API_GET_FUN(BlendEquationSeparate)( event.mModeRGB, event.mModeAlpha );
}

_void ProcessEvent( GLEventBlendFuncSeparate& event )
{
	_GL_API_GET_FUN(BlendFuncSeparate)( event.mSrcRGB, event.mDstRGB, event.mSrcAlpha, event.mDstAlpha );
}

_void ProcessEvent( GLEventVertexAttribPointer& event )
{
	_GL_API_GET_FUN(VertexAttribPointer)( event.mIndex, event.mSize, event.mType, event.mNormalized, event.mStride, event.mPointer );
}

_void ProcessEvent( GLEventEnableVertexAttribArray& event )
{
	_GL_API_GET_FUN(EnableVertexAttribArray)( event.mIndex );
}

_void ProcessEvent( GLEventDisableVertexAttribArray& event )
{
	_GL_API_GET_FUN(DisableVertexAttribArray)( event.mIndex );
}

_void ProcessEvent( GLEventDeleteFramebuffers& event )
{
	_GL_API_GET_FUN(DeleteFramebuffers)( event.mNumber, event.mFramebuffers );
}

_void ProcessEvent( GLEventGenFramebuffers& event )
{
	_GL_API_GET_FUN(GenFramebuffers)( event.mNumber, event.mFramebuffers );
}

_void ProcessEvent( GLEventCheckFramebufferStatus& event )
{
	event.mRet = _GL_API_GET_FUN(CheckFramebufferStatus)( event.mTarget );
}

_void ProcessEvent( GLEventFramebufferTexture2D& event )
{
	_GL_API_GET_FUN(FramebufferTexture2D)( event.mTarget, event.mAttachment, event.mTexTarget, event.mTexture, event.mLevel );
}

_void ProcessEvent( GLEventFramebufferRenderbuffer& event )
{
	_GL_API_GET_FUN(FramebufferRenderbuffer)( event.mTarget, event.mAttachment, event.mRenderbufferTarget, event.mRenderbuffer );
}

_void ProcessEvent( GLEventBindRenderbuffer& event )
{
	_GL_API_GET_FUN(BindRenderbuffer)( event.mTarget, event.mRenderbuffer );
}

_void ProcessEvent( GLEventRenderbufferStorage& event )
{
	_GL_API_GET_FUN(RenderbufferStorage)( event.mTarget, event.mInternalFormat, event.mWidth, event.mHeight );
}

_void ProcessEvent( GLEventGenRenderbuffers& event )
{
	_GL_API_GET_FUN(GenRenderbuffers)( event.mNumber, event.mRenderbuffers );
}

_void ProcessEvent( GLEventDeleteRenderbuffers& event )
{
	_GL_API_GET_FUN(DeleteRenderbuffers)( event.mNumber, event.mRenderbuffers );
}

_void ProcessEvent( GLEventGetRenderbufferParameteriv& event )
{
	_GL_API_GET_FUN(GetRenderbufferParameteriv)( event.mTarget, event.mName, event.mParams );
}

_void ProcessEvent( GLEventGetFramebufferAttachmentParameteriv& event )
{
	_GL_API_GET_FUN(GetFramebufferAttachmentParameteriv)( event.mTarget, event.mAttachment, event.mName, event.mParams );
}

_void ProcessEvent( GLEventIsRenderbuffer& event )
{
	event.mRet = _GL_API_GET_FUN(IsRenderbuffer)( event.mRenderbuffer );
}

_void ProcessEvent( GLEventUniform1i& event )
{
	_GL_API_GET_FUN(Uniform1i)( event.mLocation, event.mValue );
}

_void ProcessEvent( GLEventUniform1fv& event )
{
	_GL_API_GET_FUN(Uniform1fv)( event.mLocation, event.mNumber, event.mValues );
}

_void ProcessEvent( GLEventUniform2fv& event )
{
	_GL_API_GET_FUN(Uniform2fv)( event.mLocation, event.mNumber, event.mValues );
}

_void ProcessEvent( GLEventUniform3fv& event )
{
	_GL_API_GET_FUN(Uniform3fv)( event.mLocation, event.mNumber, event.mValues );
}

_void ProcessEvent( GLEventUniform4fv& event )
{
	_GL_API_GET_FUN(Uniform4fv)( event.mLocation, event.mNumber, event.mValues );
}

_void ProcessEvent( GLEventUniformMatrix2fv& event )
{
	_GL_API_GET_FUN(UniformMatrix2fv)( event.mLocation, event.mNumber, event.mTranspose, event.mValues );
}

_void ProcessEvent( GLEventUniformMatrix3fv& event )
{
	_GL_API_GET_FUN(UniformMatrix3fv)( event.mLocation, event.mNumber, event.mTranspose, event.mValues );
}

_void ProcessEvent( GLEventUniformMatrix4fv& event )
{
	_GL_API_GET_FUN(UniformMatrix4fv)( event.mLocation, event.mNumber, event.mTranspose, event.mValues );
}

_void ProcessEvent( GLEventDeleteShader& event )
{
	_GL_API_GET_FUN(DeleteShader)( event.mShader );
}

_void ProcessEvent( GLEventDetachShader& event )
{
	_GL_API_GET_FUN(DetachShader)( event.mProgram, event.mShader );
}

_void ProcessEvent( GLEventDeleteProgram& event )
{
	_GL_API_GET_FUN(DeleteProgram)( event.mProgram );
}

_void ProcessEvent( GLEventValidateProgram& event )
{
	_GL_API_GET_FUN(ValidateProgram)( event.mProgram );
}

_void ProcessEvent( GLEventGetProgramiv& event )
{
	_GL_API_GET_FUN(GetProgramiv)( event.mProgram, event.mName, event.mParams );
}

_void ProcessEvent( GLEventGetProgramInfoLog& event )
{
	_GL_API_GET_FUN(GetProgramInfoLog)( event.mProgram, event.mBufSize, event.mLength, event.mInfoLog );
}

_void ProcessEvent( GLEventIsProgram& event )
{
	event.mRet = _GL_API_GET_FUN(IsProgram)( event.mProgram );
}

_void ProcessEvent( GLEventIsShader& event )
{
	event.mRet = _GL_API_GET_FUN(IsShader)( event.mShader );
}

_void ProcessEvent( GLEventBindBuffer& event )
{
	_GL_API_GET_FUN(BindBuffer)( event.mTarget, event.mBuffer );
}

_void ProcessEvent( GLEventBindFramebuffer& event )
{
	_GL_API_GET_FUN(BindFramebuffer)( event.mTarget, event.mFramebuffer );
}

_void ProcessEvent( GLEventCompressedTexImage2D& event )
{
	_GL_API_GET_FUN(CompressedTexImage2D)( event.mTarget, event.mLevel, event.mInternalFormat, event.mWidth, event.mHeight, event.mBorder, event.mImageSize, event.mData );
}

_void ProcessEvent( GLEventCompressedTexSubImage2D& event )
{
	_GL_API_GET_FUN(CompressedTexSubImage2D)( event.mTarget, event.mLevel, event.mXOffset, event.mYOffset, event.mWidth, event.mHeight, event.mFormat, event.mImageSize, event.mData );
}

_void ProcessEvent( GLEventGenerateMipmap& event )
{
	_GL_API_GET_FUN(GenerateMipmap)( event.mTarget );
}

_void ProcessEvent( GLEventGenBuffers& event )
{
	_GL_API_GET_FUN(GenBuffers)( event.mNumber, event.mBuffers );
}

_void ProcessEvent( GLEventBufferSubData& event )
{
	_GL_API_GET_FUN(BufferSubData)( event.mTarget, event.mOffset, event.mSize, event.mData );
}

_void ProcessEvent( GLEventDeleteBuffers& event )
{
	_GL_API_GET_FUN(DeleteBuffers)( event.mNumber, event.mBuffers );
}

_void ProcessEvent( GLEventIsBuffer& event )
{
	_GL_API_GET_FUN(IsBuffer)( event.mBuffer );
}

_void ProcessEvent( GLEventBufferData& event )
{
	_GL_API_GET_FUN(BufferData)( event.mTarget, event.mSize, event.mData, event.mUsage );
}

_void ProcessEvent( GLEventDrawArrays& event )
{
	_GL_API_GET_FUN(DrawArrays)( event.mMode, event.mFirst, event.mNumber );
}

_void ProcessEvent( GLEventDrawElements& event )
{
	_GL_API_GET_FUN(DrawElements)( event.mMode, event.mNumber, event.mType, event.mIndices );
}

_void ProcessEvent( GLEventViewport& event )
{
	_GL_API_GET_FUN(Viewport)( event.mX, event.mY, event.mWidth, event.mHeight );
}

//----------------------------------------------------------------------------
// GLPlatform Function Implementations
//----------------------------------------------------------------------------

_ubool HandleGLEvent( EventBase& event )
{
	LockOwner lock_owner( *sEGLAPILocker );

	switch ( event.mEventID )
	{
		case _GL_EVENT_GET_ERROR:								ProcessEvent( (GLEventGetError&) event ); break;
		case _GL_EVENT_GET_STRING:								ProcessEvent( (GLEventGetString&) event ); break;
		case _GL_EVENT_GET_INTEGERV:							ProcessEvent( (GLEventGetIntegerv&) event ); break;
		case _GL_EVENT_CLEAR:									ProcessEvent( (GLEventClear&) event ); break;
		case _GL_EVENT_CLEAR_COLOR:								ProcessEvent( (GLEventClearColor&) event ); break;
		case _GL_EVENT_CLEAR_STENCIL:							ProcessEvent( (GLEventClearStencil&) event ); break;
		case _GL_EVENT_SCISSOR:									ProcessEvent( (GLEventScissor&) event ); break;
		case _GL_EVENT_ENABLE:									ProcessEvent( (GLEventEnable&) event ); break;
		case _GL_EVENT_DISABLE:									ProcessEvent( (GLEventDisable&) event ); break;
		case _GL_EVENT_LINE_WIDTH:								ProcessEvent( (GLEventLineWidth&) event ); break;
		case _GL_EVENT_READ_PIXELS:								ProcessEvent( (GLEventReadPixels&) event ); break;
		case _GL_EVENT_PIXEL_STOREI:							ProcessEvent( (GLEventPixelStorei&) event ); break;
		case _GL_EVENT_TEX_SUB_IMAGE2D:							ProcessEvent( (GLEventTexSubImage2D&) event ); break;
		case _GL_EVENT_CULL_FACE:								ProcessEvent( (GLEventCullFace&) event ); break;
		case _GL_EVENT_COLOR_MASK:								ProcessEvent( (GLEventColorMask&) event ); break;
		case _GL_EVENT_GET_TEX_LEVEL_PARAMETERIV:				ProcessEvent( (GLEventGetTexLevelParameteriv&) event ); break;
		case _GL_EVENT_DRAW_BUFFER:								ProcessEvent( (GLEventDrawBuffer&) event ); break;
		case _GL_EVENT_READ_BUFFER:								ProcessEvent( (GLEventReadBuffer&) event ); break;
		case _GL_EVENT_BIND_VERTEX_ARRAY:						ProcessEvent( (GLEventBindVertexArray&) event ); break;
		case _GL_EVENT_GEN_VERTEX_ARRAYS:						ProcessEvent( (GLEventGenVertexArrays&) event ); break;
		case _GL_EVENT_DELETE_VERTEX_ARRAYS:					ProcessEvent( (GLEventDeleteVertexArrays&) event ); break;
		case _GL_EVENT_CLEAR_DEPTHF:							ProcessEvent( (GLEventClearDepthf&) event ); break;
		case _GL_EVENT_DEPTH_MASK:								ProcessEvent( (GLEventDepthMask&) event ); break;
		case _GL_EVENT_BIND_TEXTURE:							ProcessEvent( (GLEventBindTexture&) event ); break;
		case _GL_EVENT_GEN_TEXTURES:							ProcessEvent( (GLEventGenTextures&) event ); break;
		case _GL_EVENT_ACTIVE_TEXTURE:							ProcessEvent( (GLEventActiveTexture&) event ); break;
		case _GL_EVENT_TEX_PARAMETERI:							ProcessEvent( (GLEventTexParameteri&) event ); break;
		case _GL_EVENT_TEX_PARAMETERF:							ProcessEvent( (GLEventTexParameterf&) event ); break;
		case _GL_EVENT_TEX_IMAGE_2D:							ProcessEvent( (GLEventTexImage2D&) event ); break;
		case _GL_EVENT_CREATE_SHADER:							ProcessEvent( (GLEventCreateShader&) event ); break;
		case _GL_EVENT_SHADER_SOURCE:							ProcessEvent( (GLEventShaderSource&) event ); break;
		case _GL_EVENT_COMPILE_SHADER:							ProcessEvent( (GLEventCompileShader&) event ); break;
		case _GL_EVENT_GET_SHADER_INFO_LOG:						ProcessEvent( (GLEventGetShaderInfoLog&) event ); break;
		case _GL_EVENT_GET_SHADERIV:							ProcessEvent( (GLEventGetShaderiv&) event ); break;
		case _GL_EVENT_CREATE_PROGRAM:							ProcessEvent( (GLEventCreateProgram&) event ); break;
		case _GL_EVENT_ATTACH_SHADER:							ProcessEvent( (GLEventAttachShader&) event ); break;
		case _GL_EVENT_BIND_ATTRIB_LOCATION:					ProcessEvent( (GLEventBindAttribLocation&) event ); break;
		case _GL_EVENT_LINK_PROGRAM:							ProcessEvent( (GLEventLinkProgram&) event ); break;
		case _GL_EVENT_USE_PROGRAM:								ProcessEvent( (GLEventUseProgram&) event ); break;
		case _GL_EVENT_GET_UNIFORM_LOCATION:					ProcessEvent( (GLEventGetUniformLocation&) event ); break;
		case _GL_EVENT_STENCIL_OP_SEPARATE:						ProcessEvent( (GLEventStencilOpSeparate&) event ); break;
		case _GL_EVENT_STENCIL_FUNC_SEPARATE:					ProcessEvent( (GLEventStencilFuncSeparate&) event ); break;
		case _GL_EVENT_BLEND_EQUATION:							ProcessEvent( (GLEventBlendEquation&) event ); break;
		case _GL_EVENT_BLEND_EQUATION_SEPARATE:					ProcessEvent( (GLEventBlendEquationSeparate&) event ); break;
		case _GL_EVENT_BLEND_FUNC_SEPARATE:						ProcessEvent( (GLEventBlendFuncSeparate&) event ); break;
		case _GL_EVENT_VERTEX_ATTRIB_POINTER:					ProcessEvent( (GLEventVertexAttribPointer&) event ); break;
		case _GL_EVENT_ENABLE_VERTEX_ATTRIB_ARRAY:				ProcessEvent( (GLEventEnableVertexAttribArray&) event ); break;
		case _GL_EVENT_DISABLE_VERTEX_ATTRIB_ARRAY:				ProcessEvent( (GLEventDisableVertexAttribArray&) event ); break;
		case _GL_EVENT_DELETE_FRAMEBUFFERS:						ProcessEvent( (GLEventDeleteFramebuffers&) event ); break;
		case _GL_EVENT_GEN_FRAMEBUFFERS:						ProcessEvent( (GLEventGenFramebuffers&) event ); break;
		case _GL_EVENT_CHECK_FRAMEBUFFER_STATUS:				ProcessEvent( (GLEventCheckFramebufferStatus&) event ); break;
		case _GL_EVENT_FRAMEBUFFER_TEXTURE2D:					ProcessEvent( (GLEventFramebufferTexture2D&) event ); break;
		case _GL_EVENT_FRAMEBUFFER_RENDERBUFFER:				ProcessEvent( (GLEventFramebufferRenderbuffer&) event ); break;
		case _GL_EVENT_BIND_RENDERBUFFER:						ProcessEvent( (GLEventBindRenderbuffer&) event ); break;
		case _GL_EVENT_RENDERBUFFER_STORAGE:					ProcessEvent( (GLEventRenderbufferStorage&) event ); break;
		case _GL_EVENT_GEN_RENDERBUFFERS:						ProcessEvent( (GLEventGenRenderbuffers&) event ); break;
		case _GL_EVENT_DELETE_RENDERBUFFERS:					ProcessEvent( (GLEventDeleteRenderbuffers&) event ); break;
		case _GL_EVENT_GET_RENDERBUFFER_PARAMETERIV:			ProcessEvent( (GLEventGetRenderbufferParameteriv&) event ); break;
		case _GL_EVENT_GET_FRAMEBUFFER_ATTACHMENT_PARAMETERIV:	ProcessEvent( (GLEventGetFramebufferAttachmentParameteriv&) event ); break;
		case _GL_EVENT_IS_RENDERBUFFER:							ProcessEvent( (GLEventIsRenderbuffer&) event ); break;
		case _GL_EVENT_UNIFORM_1I:								ProcessEvent( (GLEventUniform1i&) event ); break;
		case _GL_EVENT_UNIFORM_1FV:								ProcessEvent( (GLEventUniform1fv&) event ); break;
		case _GL_EVENT_UNIFORM_2FV:								ProcessEvent( (GLEventUniform2fv&) event ); break;
		case _GL_EVENT_UNIFORM_3FV:								ProcessEvent( (GLEventUniform3fv&) event ); break;
		case _GL_EVENT_UNIFORM_4FV:								ProcessEvent( (GLEventUniform4fv&) event ); break;
		case _GL_EVENT_UNIFORM_MATRIX_2FV:						ProcessEvent( (GLEventUniformMatrix2fv&) event ); break;
		case _GL_EVENT_UNIFORM_MATRIX_3FV:						ProcessEvent( (GLEventUniformMatrix3fv&) event ); break;
		case _GL_EVENT_UNIFORM_MATRIX_4FV:						ProcessEvent( (GLEventUniformMatrix4fv&) event ); break;
		case _GL_EVENT_DELETE_SHADER:							ProcessEvent( (GLEventDeleteShader&) event ); break;
		case _GL_EVENT_DETACH_SHADER:							ProcessEvent( (GLEventDetachShader&) event ); break;
		case _GL_EVENT_DELETE_PROGRAM:							ProcessEvent( (GLEventDeleteProgram&) event ); break;
		case _GL_EVENT_VALIDATE_PROGRAM:						ProcessEvent( (GLEventValidateProgram&) event ); break;
		case _GL_EVENT_GET_PROGRAMIV:							ProcessEvent( (GLEventGetProgramiv&) event ); break;
		case _GL_EVENT_GET_PROGRAM_INFO_LOG:					ProcessEvent( (GLEventGetProgramInfoLog&) event ); break;
		case _GL_EVENT_IS_PROGRAM:								ProcessEvent( (GLEventIsProgram&) event ); break;
		case _GL_EVENT_IS_SHADER:								ProcessEvent( (GLEventIsShader&) event ); break;
		case _GL_EVENT_BIND_BUFFER:								ProcessEvent( (GLEventBindBuffer&) event ); break;
		case _GL_EVENT_BIND_FRAMEBUFFER:						ProcessEvent( (GLEventBindFramebuffer&) event ); break;
		case _GL_EVENT_COMPRESSED_TEX_IMAGE_2D:					ProcessEvent( (GLEventCompressedTexImage2D&) event ); break;
		case _GL_EVENT_COMPRESSED_TEX_SUB_IMAGE_2D:				ProcessEvent( (GLEventCompressedTexSubImage2D&) event ); break;
		case _GL_EVENT_GENERATE_MIPMAP:							ProcessEvent( (GLEventGenerateMipmap&) event ); break;
		case _GL_EVENT_GEN_BUFFERS:								ProcessEvent( (GLEventGenBuffers&) event ); break;
		case _GL_EVENT_BUFFER_SUB_DATA:							ProcessEvent( (GLEventBufferSubData&) event ); break;
		case _GL_EVENT_DELETE_BUFFERS:							ProcessEvent( (GLEventDeleteBuffers&) event ); break;
		case _GL_EVENT_IS_BUFFER:								ProcessEvent( (GLEventIsBuffer&) event ); break;
		case _GL_EVENT_BUFFER_DATA:								ProcessEvent( (GLEventBufferData&) event ); break;
		case _GL_EVENT_DRAW_ARRAYS:								ProcessEvent( (GLEventDrawArrays&) event ); break;
		case _GL_EVENT_DRAW_ELEMENTS:							ProcessEvent( (GLEventDrawElements&) event ); break;
		case _GL_EVENT_VIEWPORT:								ProcessEvent( (GLEventViewport&) event ); break;
		case _GL_EVENT_INIT_RENDER_CONTEXT:						ProcessEvent( (GLEventInitRenderContext&) event ); break;
		case _GL_EVENT_FINALIZE_RENDER_CONTEXT:					ProcessEvent( (GLEventFinalizeRenderContext&) event ); break;
		case _GL_EVENT_PRESENT_RENDER_BUFFERS:					ProcessEvent( (GLEventPresentRenderBuffers&) event ); break;
		default:
			return _false;
	}

	return _true;
}

_ubool IsBlockGLEvent( _dword event_id, _ubool& is_async )
{
	switch ( event_id )
	{
		case _GL_EVENT_GET_ERROR:
		case _GL_EVENT_GET_STRING:
		case _GL_EVENT_GET_INTEGERV:
		case _GL_EVENT_CLEAR:
		case _GL_EVENT_CLEAR_COLOR:
		case _GL_EVENT_CLEAR_STENCIL:
		case _GL_EVENT_SCISSOR:
		case _GL_EVENT_ENABLE:
		case _GL_EVENT_DISABLE:
		case _GL_EVENT_LINE_WIDTH:
		case _GL_EVENT_READ_PIXELS:
		case _GL_EVENT_CLEAR_DEPTHF:
		case _GL_EVENT_DEPTH_MASK:
		case _GL_EVENT_BIND_TEXTURE:
		case _GL_EVENT_GEN_TEXTURES:
		case _GL_EVENT_ACTIVE_TEXTURE:
		case _GL_EVENT_TEX_PARAMETERI:
		case _GL_EVENT_TEX_PARAMETERF:
		case _GL_EVENT_TEX_IMAGE_2D:
		case _GL_EVENT_CREATE_SHADER:
		case _GL_EVENT_SHADER_SOURCE:
		case _GL_EVENT_COMPILE_SHADER:
		case _GL_EVENT_GET_SHADER_INFO_LOG:
		case _GL_EVENT_GET_SHADERIV:
		case _GL_EVENT_CREATE_PROGRAM:
		case _GL_EVENT_ATTACH_SHADER:
		case _GL_EVENT_BIND_ATTRIB_LOCATION:
		case _GL_EVENT_LINK_PROGRAM:
		case _GL_EVENT_USE_PROGRAM:
		case _GL_EVENT_GET_UNIFORM_LOCATION:
		case _GL_EVENT_STENCIL_OP_SEPARATE:
		case _GL_EVENT_STENCIL_FUNC_SEPARATE:
		case _GL_EVENT_BLEND_EQUATION:
		case _GL_EVENT_BLEND_EQUATION_SEPARATE:
		case _GL_EVENT_BLEND_FUNC_SEPARATE:
		case _GL_EVENT_VERTEX_ATTRIB_POINTER:
		case _GL_EVENT_ENABLE_VERTEX_ATTRIB_ARRAY:
		case _GL_EVENT_DISABLE_VERTEX_ATTRIB_ARRAY:
		case _GL_EVENT_DELETE_FRAMEBUFFERS:
		case _GL_EVENT_GEN_FRAMEBUFFERS:
		case _GL_EVENT_CHECK_FRAMEBUFFER_STATUS:
		case _GL_EVENT_FRAMEBUFFER_TEXTURE2D:
		case _GL_EVENT_FRAMEBUFFER_RENDERBUFFER:
		case _GL_EVENT_BIND_RENDERBUFFER:
		case _GL_EVENT_RENDERBUFFER_STORAGE:
		case _GL_EVENT_GEN_RENDERBUFFERS:
		case _GL_EVENT_DELETE_RENDERBUFFERS:
		case _GL_EVENT_GET_RENDERBUFFER_PARAMETERIV:
		case _GL_EVENT_GET_FRAMEBUFFER_ATTACHMENT_PARAMETERIV:
		case _GL_EVENT_IS_RENDERBUFFER:
		case _GL_EVENT_UNIFORM_1I:
		case _GL_EVENT_UNIFORM_1FV:
		case _GL_EVENT_UNIFORM_2FV:
		case _GL_EVENT_UNIFORM_3FV:
		case _GL_EVENT_UNIFORM_4FV:
		case _GL_EVENT_UNIFORM_MATRIX_2FV:
		case _GL_EVENT_UNIFORM_MATRIX_3FV:
		case _GL_EVENT_UNIFORM_MATRIX_4FV:
		case _GL_EVENT_DELETE_SHADER:
		case _GL_EVENT_DETACH_SHADER:
		case _GL_EVENT_DELETE_PROGRAM:
		case _GL_EVENT_VALIDATE_PROGRAM:
		case _GL_EVENT_GET_PROGRAMIV:
		case _GL_EVENT_GET_PROGRAM_INFO_LOG:
		case _GL_EVENT_IS_PROGRAM:
		case _GL_EVENT_IS_SHADER:
		case _GL_EVENT_BIND_BUFFER:
		case _GL_EVENT_BIND_FRAMEBUFFER:
		case _GL_EVENT_COMPRESSED_TEX_IMAGE_2D:
		case _GL_EVENT_COMPRESSED_TEX_SUB_IMAGE_2D:
		case _GL_EVENT_GENERATE_MIPMAP:
		case _GL_EVENT_GEN_BUFFERS:
		case _GL_EVENT_BUFFER_SUB_DATA:
		case _GL_EVENT_DELETE_BUFFERS:
		case _GL_EVENT_IS_BUFFER:
		case _GL_EVENT_BUFFER_DATA:
		case _GL_EVENT_DRAW_ARRAYS:
		case _GL_EVENT_DRAW_ELEMENTS:
		case _GL_EVENT_VIEWPORT:
		case _GL_EVENT_INIT_RENDER_CONTEXT:
		case _GL_EVENT_FINALIZE_RENDER_CONTEXT:
		case _GL_EVENT_PRESENT_RENDER_BUFFERS:
			is_async = IsAsyncEvent( event_id );
			return _true;

		default:
			break;
	}

	return _false;
}

#else

_ubool HandleGLEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _GL_EVENT_INIT_RENDER_CONTEXT:		ProcessEvent( (GLEventInitRenderContext&) event ); break;
		case _GL_EVENT_FINALIZE_RENDER_CONTEXT:	ProcessEvent( (GLEventFinalizeRenderContext&) event ); break;
		case _GL_EVENT_PRESENT_RENDER_BUFFERS:	ProcessEvent( (GLEventPresentRenderBuffers&) event ); break;
		default:
			return _false;
	}

	return _true;
}

_ubool IsBlockGLEvent( _dword event_id, _ubool& is_async )
{
	is_async = _false;

	switch ( event_id )
	{
		case _GL_EVENT_INIT_RENDER_CONTEXT:
		case _GL_EVENT_FINALIZE_RENDER_CONTEXT:
		case _GL_EVENT_PRESENT_RENDER_BUFFERS:
			return _true;

		default:
			break;
	}

	return _false;
}

_ubool InitializeEGLAPI( )
{
	return _true;
}

_void FinalizeEGLAPI( )
{
}

#endif