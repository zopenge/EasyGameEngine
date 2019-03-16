//! @file     GLState.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

GLCachedState EGE::gGLCachedState;

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static GLenum TranslateAddressMode( _SAMPLER_ADDRESS_MODE mode )
{
	switch ( mode )
	{
#if (_OPENGLES_ == 1)
		case _SAM_CLAMP:			return GL_CLAMP_TO_EDGE;
#else
		case _SAM_CLAMP:			return GL_CLAMP;
#endif
		case _SAM_CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case _SAM_MIRROR:			return GL_MIRRORED_REPEAT;
		case _SAM_REPEAT:			return GL_REPEAT;
		default: 
			return GL_REPEAT;
	}
}

static _SAMPLER_ADDRESS_MODE TranslateAddressModeFromGL( GLenum mode )
{
	switch ( mode )
	{
#if (_OPENGLES_ == 1)
		case GL_CLAMP_TO_EDGE:		return _SAM_CLAMP;
#else
		case GL_CLAMP:				return _SAM_CLAMP;
		case GL_CLAMP_TO_EDGE:		return _SAM_CLAMP_TO_EDGE;
#endif
		case GL_MIRRORED_REPEAT:	return _SAM_MIRROR;
		case GL_REPEAT:				return _SAM_REPEAT;
		default: 
			return _SAM_REPEAT;
	}
}

static GLenum TranslateCullMode( _RASTERIZER_CULL_MODE mode )
{
	switch ( mode )
	{
		case _RCM_CW:	return GL_BACK;
		case _RCM_CCW:	return GL_FRONT;
		default: 
			return GL_NONE;
	}
}

static _RASTERIZER_CULL_MODE TranslateCullModeFromGL( GLenum mode )
{
	switch ( mode )
	{
		case GL_BACK:	return _RCM_CW;
		case GL_FRONT:	return _RCM_CCW;
		default: 
			return _RCM_NONE;
	}
}

static GLenum TranslateCompareFunction( _COMPARE_FUNCTION func )
{
	switch ( func )
	{
		case _CF_LESS:			return GL_LESS;
		case _CF_LESS_EQUAL:	return GL_LEQUAL;
		case _CF_GREATER:		return GL_GREATER;
		case _CF_GREATER_EQUAL: return GL_GEQUAL;
		case _CF_EQUAL:			return GL_EQUAL;
		case _CF_NOT_EQUAL:		return GL_NOTEQUAL;
		case _CF_NEVER:			return GL_NEVER;
		default: 
			return GL_ALWAYS;
	}
}

static _COMPARE_FUNCTION TranslateCompareFunctionFromGL( GLenum func )
{
	switch ( func )
	{
		case GL_LESS:		return _CF_LESS;
		case GL_LEQUAL:		return _CF_LESS_EQUAL;
		case GL_GREATER:	return _CF_GREATER;
		case GL_GEQUAL:		return _CF_GREATER_EQUAL;
		case GL_EQUAL:		return _CF_EQUAL;
		case GL_NOTEQUAL:	return _CF_NOT_EQUAL;
		case GL_NEVER:		return _CF_NEVER;
		default: 
			return _CF_ALWAYS;
	}
}

static GLenum TranslateStencilOp( _STENCIL_OPERATION op )
{
	switch ( op )
	{
		case _SO_ZERO:					return GL_ZERO;
		case _SO_REPLACE:				return GL_REPLACE;
		case _SO_SATURATED_INCREMENT:	return GL_INCR;
		case _SO_SATURATED_DECREMENT:	return GL_DECR;
		case _SO_INVERT:				return GL_INVERT;
		case _SO_INCREMENT:				return GL_INCR_WRAP;
		case _SO_DECREMENT:				return GL_DECR_WRAP;
		default: 
			return GL_KEEP;
	}
}

static _STENCIL_OPERATION TranslateStencilOpFromGL( GLenum op )
{
	switch ( op )
	{
		case GL_ZERO:		return _SO_ZERO;
		case GL_REPLACE:	return _SO_REPLACE;
		case GL_INCR:		return _SO_SATURATED_INCREMENT;
		case GL_DECR:		return _SO_SATURATED_DECREMENT;
		case GL_INVERT:		return _SO_INVERT;
		case GL_INCR_WRAP:	return _SO_INCREMENT;
		case GL_DECR_WRAP:	return _SO_DECREMENT;
		default: 
			return _SO_KEEP;
	}
}

static GLenum TranslateBlendFactor( _BLEND_FACTOR factor )
{
	switch ( factor )
	{
		case _BF_ONE:					return GL_ONE;
		case _BF_SOURCE_COLOR:			return GL_SRC_COLOR;
		case _BF_INVERSE_SOURCE_COLOR:	return GL_ONE_MINUS_SRC_COLOR;
		case _BF_SOURCE_ALPHA:			return GL_SRC_ALPHA;
		case _BF_INVERSE_SOURCE_ALPHA:	return GL_ONE_MINUS_SRC_ALPHA;
		case _BF_DEST_ALPHA:			return GL_DST_ALPHA;
		case _BF_INVERSE_DEST_ALPHA:	return GL_ONE_MINUS_DST_ALPHA;
		case _BF_DEST_COLOR:			return GL_DST_COLOR;
		case _BF_INVERSE_DEST_COLOR:	return GL_ONE_MINUS_DST_COLOR;
		default: 
			return GL_ZERO;
	}
}

static _BLEND_FACTOR TranslateBlendFactorFromGL( GLenum factor )
{
	switch ( factor )
	{
		case GL_ONE:					return _BF_ONE;
		case GL_SRC_COLOR:				return _BF_SOURCE_COLOR;
		case GL_ONE_MINUS_SRC_COLOR:	return _BF_INVERSE_SOURCE_COLOR;
		case GL_SRC_ALPHA:				return _BF_SOURCE_ALPHA;
		case GL_ONE_MINUS_SRC_ALPHA:	return _BF_INVERSE_SOURCE_ALPHA;
		case GL_DST_ALPHA:				return _BF_DEST_ALPHA;
		case GL_ONE_MINUS_DST_ALPHA:	return _BF_INVERSE_DEST_ALPHA;
		case GL_DST_COLOR:				return _BF_DEST_COLOR;
		case GL_ONE_MINUS_DST_COLOR:	return _BF_INVERSE_DEST_COLOR;
		default: 
			return _BF_ZERO;
	}
}

template< typename Type >
_ubool IsSameState( const Type* state1, const Type* state2 )
{
	if ( state1 != state2 )
		return _false;

	if ( state1 && state2 )
	{
		if ( *state1 != *state2 )
			return _false;
	}

	return _true;
}

//----------------------------------------------------------------------------
// GLStateCache Implementation
//----------------------------------------------------------------------------

_void EGE::OnVBODeletion( GLuint buffer )
{
	if ( buffer == gGLCachedState.mCurVBO )
	{
		gGLCachedState.mPendingVBO = _null;
		GLCachedBindVBO( 0 );
	}
}

_void EGE::OnIBODeletion( GLuint buffer )
{
	if ( buffer == gGLCachedState.mCurIBO )
	{
		gGLCachedState.mPendingIBO = _null;
		GLCachedBindIBO( 0 );
	}
}

_void EGE::OnVAODeletion( GLuint buffer )
{
	if ( buffer == gGLCachedState.mCurVAO )
	{
		gGLCachedState.mPendingVAO = _null;
		GLCachedBindVAO( 0 );
	}
}

_void EGE::GLCachedSetActiveTexture( _dword index )
{
	if ( gGLCachedState.mActiveTextureIndex != index )
	{
		GL_CHECK_ERROR( __glActiveTexture( GL_TEXTURE0 + index ) );
		gGLCachedState.mActiveTextureIndex = index;
	}
}

_void EGE::GLCachedBindTexture( GLuint target, GLuint tex_id )
{
	GL_CHECK_ERROR( __glBindTexture( target, tex_id ) );
}

_void EGE::GLCachedBindFBO( GLuint buffer )
{
	if ( buffer != gGLCachedState.mCurFBO )
	{
		GL_CHECK_ERROR( __glBindFramebuffer( GL_FRAMEBUFFER, buffer ) );
		gGLCachedState.mCurFBO = buffer;
	}
}

_void EGE::GLCachedBindRBO( GLuint buffer )
{
	if ( buffer != gGLCachedState.mCurRBO )
	{
		GL_CHECK_ERROR( __glBindRenderbuffer( GL_RENDERBUFFER, buffer ) );
		gGLCachedState.mCurRBO = buffer;
	}
}

_void EGE::GLCachedBindVBO( GLuint buffer )
{
	if ( buffer != gGLCachedState.mCurVBO )
	{
		GL_CHECK_ERROR( __glBindBuffer( GL_ARRAY_BUFFER, buffer ) );
		gGLCachedState.mCurVBO = buffer;
	}
}

_void EGE::GLCachedBindIBO( GLuint buffer )
{
	if ( buffer != gGLCachedState.mCurIBO )
	{
		GL_CHECK_ERROR( __glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffer ) );
		gGLCachedState.mCurIBO = buffer;
	}
}

_void EGE::GLCachedBindVAO( GLuint buffer )
{
	if ( buffer != gGLCachedState.mCurVAO )
	{
		GL_CHECK_ERROR( __glBindVertexArrayOES( buffer ) );
		gGLCachedState.mCurVAO = buffer;
	}
}

_void EGE::GLBindVBO( GLuint buffer )
{
	GL_CHECK_ERROR( __glBindBuffer( GL_ARRAY_BUFFER, buffer ) );
	gGLCachedState.mCurVBO = buffer;
}

_void EGE::GLBindIBO( GLuint buffer )
{
	GL_CHECK_ERROR( __glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffer ) );
	gGLCachedState.mCurIBO = buffer;
}

_void EGE::GLPurgeFramebufferFromCaches( GLuint buffer )
{
	if ( buffer == gGLCachedState.mCurFBO )
	{
		GL_CHECK_ERROR( __glBindFramebuffer( GL_FRAMEBUFFER, 0 ) );
		gGLCachedState.mCurFBO = 0;
	}
}

_void EGE::GLCachedSetReadBuffer( GLuint buffer )
{
#if (_OPENGLES_ == 0)
	if ( buffer != gGLCachedState.mReadBufferSet )
	{
		GL_CHECK_ERROR( __glReadBuffer( buffer ) );
		gGLCachedState.mReadBufferSet = buffer;
	}
#endif
}

_void EGE::GLCachedSetDrawBuffer( GLuint buffer )
{
#if (_OPENGLES_ == 0)
	if ( buffer != gGLCachedState.mDrawBufferSet )
	{
		GL_CHECK_ERROR( __glDrawBuffer( buffer ) );
		gGLCachedState.mDrawBufferSet = buffer;
	}
#endif
}

_void EGE::GLCachedBindProgram( GLuint program )
{
	if ( gGLCachedState.mCurProgram != program )
	{
		GL_CHECK_ERROR( __glUseProgram( program ) );
		gGLCachedState.mCurProgram = program;
	}
}

//----------------------------------------------------------------------------
// GL-Error Check Implementation
//----------------------------------------------------------------------------

_void EGE::GLCheckError( AStringPtr file, _dword line )
{
	GLenum error = glGetError( );
	if ( error )
	{
		AStringPtr error_id_string;
		switch ( error )
		{
			case GL_INVALID_ENUM:					error_id_string = "Invalid Enum"; break;
			case GL_INVALID_VALUE:					error_id_string = "Invalid Value"; break;
			case GL_INVALID_OPERATION:				error_id_string = "Invalid Operation"; break;
			case GL_OUT_OF_MEMORY:					error_id_string = "Out Of Memory"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:	error_id_string = "Invalid Frame Buffer Operation"; break;
			default:
				error_id_string = "Error";
				break;
		}

		ALOG_ERROR_4( "GL error code: 0x%x[%s] at %s:%d", (_dword) error, error_id_string.Str( ), file.Str( ), line );
		EGE_ASSERT( 0 );
	}
}

_ubool EGE::GLCheckShader( GLuint shader )
{
	ALOG_TRACE_1( "Checking (%d) Shader ...", shader );

	GLint status = 0;
	__glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

	if ( status )
	{
		ALOG_TRACE_1( "Check (%d) shader OK", shader );

		return _true;
	} 
	else
	{
		GLint log_len = 0; 
		_chara log_buffer[2048]; log_buffer[0] = 0;
		__glGetShaderInfoLog( shader, sizeof( log_buffer ), &log_len, log_buffer );

		ALOG_ERROR_2( "Check (%d) shader failed : %s", shader, (const _chara*) log_buffer );

		return _false;
	} 
}

_ubool EGE::GLCheckProgram( GLuint program )
{
	int log_len;
	_chara log_buffer[2048]; log_buffer[0] = 0;

	GLint status = 0;
	__glGetProgramiv( program, GL_LINK_STATUS, &status );
	if ( status == GL_FALSE )
	{
		__glGetProgramInfoLog( program, sizeof( log_buffer ), &log_len, log_buffer );
		ALOG_ERROR_2( "Link (%d) GLSL Program Error: %s", program, (const _chara*) log_buffer );

		return _false;
	} 
	else 
	{
#ifdef _DEBUG
		// Show the link info
		__glGetProgramInfoLog( program, sizeof( log_buffer ), &log_len, log_buffer );
		if ( log_buffer[0] != 0)
		{
			ALOG_TRACE_2( "Link (%d) GLSL Program results: %s", program, (const _chara*) log_buffer );
		}

		// Validate it
		__glValidateProgram( program );
		__glGetProgramInfoLog( program, sizeof( log_buffer ), &log_len, log_buffer );
		if ( log_buffer[0] != 0)
		{
			ALOG_TRACE_2( "Validate (%d) GLSL Program results: %s", program, (const _chara*) log_buffer );
		}
#endif
		return _true;
	}
}

_ubool EGE::GLCheckFramebuffer( GLuint fbo )
{
	GLCachedBindFBO( fbo );

	AStringPtr err_string;

	GLenum status = __glCheckFramebufferStatus( GL_FRAMEBUFFER );
	switch ( status )
	{
		case GL_FRAMEBUFFER_COMPLETE:
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			err_string = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			err_string = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;

#if (_OPENGLES_ == 1)
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			err_string = "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS";
			break;
#endif

		case GL_FRAMEBUFFER_UNSUPPORTED:
			err_string = "GL_FRAMEBUFFER_UNSUPPORTED";
			break;

		default:
			err_string = "UNKNOWN";
			break;
	}

	if ( status != GL_FRAMEBUFFER_COMPLETE )
	{
		ALOG_ERROR_2( "Create (%d) FBO failed, error: %s", fbo, err_string.Str( ) );
		return _false;
	}

	ALOG_TRACE_1( "Create (%d) FBO OK", fbo );

	return _true;
}

//----------------------------------------------------------------------------
// GLDrv-State Implementation
//----------------------------------------------------------------------------

SamplerStateInitializerRHI GLDrv::GetSamplerStateFromGL( const GLSamplerStateInfo& state ) const
{
	SamplerStateInitializerRHI init( _SF_NEAREST );
	init.mAddressU	= TranslateAddressModeFromGL( state.mAddressU );
	init.mAddressV	= TranslateAddressModeFromGL( state.mAddressV );
	init.mAddressW	= TranslateAddressModeFromGL( state.mAddressW );

	if ( state.mMagFilter == GL_LINEAR )
		init.mFilter = _SF_LINEAR;
	else if ( state.mMagFilter == GL_NEAREST )
		init.mFilter = _SF_NEAREST;

	return init;
}

SamplerStateRHIPassRef GLDrv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	GLSamplerState* state	= new GLSamplerState( );
	state->mInfo.mAddressU	= TranslateAddressMode( initializer.mAddressU );
	state->mInfo.mAddressV	= TranslateAddressMode( initializer.mAddressV );
	state->mInfo.mAddressW	= TranslateAddressMode( initializer.mAddressW );
	
	switch ( initializer.mFilter )
	{
		case _SF_LINEAR:
		{
			state->mInfo.mMagFilter	= GL_LINEAR;
			state->mInfo.mMinFilter	= GL_LINEAR_MIPMAP_LINEAR;
		}
		break;

		case _SF_NEAREST:
		{
			state->mInfo.mMagFilter	= GL_NEAREST;
			state->mInfo.mMinFilter	= GL_NEAREST_MIPMAP_LINEAR;
		}
		break;
	}

	state->mInfo.UpdateCRCValueForThis( state );

	return state;
}

RasterizerStateRHIPassRef GLDrv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	GLRasterizerState* state			= new GLRasterizerState( );
	state->mInfo.mEnableRedColorWrite	= initializer.mEnableRedColorWrite;
	state->mInfo.mEnableGreenColorWrite	= initializer.mEnableGreenColorWrite;
	state->mInfo.mEnableBlueColorWrite	= initializer.mEnableBlueColorWrite;
	state->mInfo.mEnableAlphaColorWrite	= initializer.mEnableAlphaColorWrite;
	state->mInfo.mCullModeEnabled		= initializer.mCullMode != _RCM_NONE;
	state->mInfo.mCullMode 				= TranslateCullMode( initializer.mCullMode );
	state->mInfo.UpdateCRCValueForThis( state );

	return state;
}

DepthStateRHIPassRef GLDrv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	GLDepthState* state			= new GLDepthState( );
	state->mInfo.mZEnable		= initializer.mDepthTest != _CF_ALWAYS || initializer.mEnableDepthWrite;
	state->mInfo.mZWriteEnable	= initializer.mEnableDepthWrite;
	state->mInfo.mZFunc			= TranslateCompareFunction( initializer.mDepthTest );
	state->mInfo.UpdateCRCValueForThis( state );

	return state;
}

StencilStateRHIPassRef GLDrv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	GLStencilState* state				= new GLStencilState( );
	state->mInfo.mStencilEnable			= initializer.mEnableFrontFaceStencil || initializer.mEnableBackFaceStencil;
	state->mInfo.mTwoSidedStencilMode	= initializer.mEnableBackFaceStencil;
	state->mInfo.mStencilFunc			= TranslateCompareFunction( initializer.mFrontFaceStencilTest );
	state->mInfo.mStencilFail			= TranslateStencilOp( initializer.mFrontFaceStencilFailStencilOp );
	state->mInfo.mStencilZFail			= TranslateStencilOp( initializer.mFrontFaceDepthFailStencilOp );
	state->mInfo.mStencilPass			= TranslateStencilOp( initializer.mFrontFacePassStencilOp );
	state->mInfo.mCCWStencilFunc		= TranslateCompareFunction( initializer.mBackFaceStencilTest );
	state->mInfo.mCCWStencilFail		= TranslateStencilOp( initializer.mBackFaceStencilFailStencilOp );
	state->mInfo.mCCWStencilZFail 		= TranslateStencilOp( initializer.mBackFaceDepthFailStencilOp );
	state->mInfo.mCCWStencilPass		= TranslateStencilOp( initializer.mBackFacePassStencilOp );
	state->mInfo.mStencilReadMask		= initializer.mStencilReadMask;
	state->mInfo.mStencilWriteMask		= initializer.mStencilWriteMask;
	state->mInfo.mStencilRef			= initializer.mStencilRef;
	state->mInfo.UpdateCRCValueForThis( state );

	return state;
}

BlendStateRHIPassRef GLDrv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	GLBlendState* state						= new GLBlendState( );
	state->mInfo.mColorSourceBlendFactor	= TranslateBlendFactor( initializer.mColorSourceBlendFactor );
	state->mInfo.mColorDestBlendFactor		= TranslateBlendFactor( initializer.mColorDestBlendFactor );
	state->mInfo.mAlphaSourceBlendFactor	= TranslateBlendFactor( initializer.mAlphaSourceBlendFactor );
	state->mInfo.mAlphaDestBlendFactor		= TranslateBlendFactor( initializer.mAlphaDestBlendFactor );
	state->mInfo.mAlphaBlendEnable			= initializer.mEnableBlend;
	state->mInfo.mSeparateAlphaBlendEnable	= initializer.mAlphaDestBlendFactor != initializer.mColorDestBlendFactor || initializer.mAlphaSourceBlendFactor != initializer.mColorSourceBlendFactor;
	state->mInfo.UpdateCRCValueForThis( state );

	return state;
}

SamplerStateInitializerRHI GLDrv::GetSamplerState( const SamplerStateRHI* state ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( SamplerState, state );

	return GetSamplerStateFromGL( gl_state->mInfo );
}

RasterizerStateInitializerRHI GLDrv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( RasterizerState, state );

	RasterizerStateInitializerRHI init( _false, _false, _false, _false, _RFM_POINT, _RCM_NONE );
	init.mEnableRedColorWrite	= gl_state->mInfo.mEnableRedColorWrite;
	init.mEnableGreenColorWrite	= gl_state->mInfo.mEnableGreenColorWrite;
	init.mEnableBlueColorWrite	= gl_state->mInfo.mEnableBlueColorWrite;
	init.mEnableAlphaColorWrite	= gl_state->mInfo.mEnableAlphaColorWrite;
	init.mCullMode 				= TranslateCullModeFromGL( gl_state->mInfo.mCullMode );

	return init;
}

DepthStateInitializerRHI GLDrv::GetDepthState( const DepthStateRHI* state ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( DepthState, state );

	DepthStateInitializerRHI init( _false, _CF_LESS );
	init.mEnableDepthWrite	= gl_state->mInfo.mZWriteEnable;
	init.mDepthTest			= TranslateCompareFunctionFromGL( gl_state->mInfo.mZFunc );

	return init;
}

StencilStateInitializerRHI GLDrv::GetStencilState( const StencilStateRHI* state ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( StencilState, state );

	StencilStateInitializerRHI init;
	init.mEnableFrontFaceStencil		= gl_state->mInfo.mStencilEnable;
	init.mEnableBackFaceStencil			= gl_state->mInfo.mTwoSidedStencilMode;
	init.mFrontFaceStencilTest			= TranslateCompareFunctionFromGL( gl_state->mInfo.mStencilFunc );
	init.mFrontFaceStencilFailStencilOp	= TranslateStencilOpFromGL( gl_state->mInfo.mStencilFail );
	init.mFrontFaceDepthFailStencilOp	= TranslateStencilOpFromGL( gl_state->mInfo.mStencilZFail );
	init.mFrontFacePassStencilOp		= TranslateStencilOpFromGL( gl_state->mInfo.mStencilPass );
	init.mBackFaceStencilTest			= TranslateCompareFunctionFromGL( gl_state->mInfo.mCCWStencilFunc );
	init.mBackFaceStencilFailStencilOp	= TranslateStencilOpFromGL( gl_state->mInfo.mCCWStencilFail );
	init.mBackFaceDepthFailStencilOp 	= TranslateStencilOpFromGL( gl_state->mInfo.mCCWStencilZFail );
	init.mBackFacePassStencilOp			= TranslateStencilOpFromGL( gl_state->mInfo.mCCWStencilPass );
	init.mStencilReadMask				= gl_state->mInfo.mStencilReadMask;
	init.mStencilWriteMask				= gl_state->mInfo.mStencilWriteMask;
	init.mStencilRef					= gl_state->mInfo.mStencilRef;

	return init;
}

BlendStateInitializerRHI GLDrv::GetBlendState( const BlendStateRHI* state ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( BlendState, state );

	BlendStateInitializerRHI init;
	init.mColorSourceBlendFactor	= TranslateBlendFactorFromGL( gl_state->mInfo.mColorSourceBlendFactor );
	init.mColorDestBlendFactor		= TranslateBlendFactorFromGL( gl_state->mInfo.mColorDestBlendFactor );
	init.mAlphaSourceBlendFactor	= TranslateBlendFactorFromGL( gl_state->mInfo.mAlphaSourceBlendFactor );
	init.mAlphaDestBlendFactor		= TranslateBlendFactorFromGL( gl_state->mInfo.mAlphaDestBlendFactor );

	return init;
}

_ubool GLDrv::IsSameSamplerState( const SamplerStateRHI* state1, const SamplerStateRHI* state2 ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( SamplerState, state1 );
	DYNAMIC_CAST_GLRESOURCE_CONST( SamplerState, state2 );

	return IsSameState( gl_state1, gl_state2 );
}

_ubool GLDrv::IsSameRasterizerState( const RasterizerStateRHI* state1, const RasterizerStateRHI* state2 ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( RasterizerState, state1 );
	DYNAMIC_CAST_GLRESOURCE_CONST( RasterizerState, state2 );

	return IsSameState( gl_state1, gl_state2 );
}

_ubool GLDrv::IsSameDepthState( const DepthStateRHI* state1, const DepthStateRHI* state2 ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( DepthState, state1 );
	DYNAMIC_CAST_GLRESOURCE_CONST( DepthState, state2 );

	return IsSameState( gl_state1, gl_state2 );
}

_ubool GLDrv::IsSameStencilState( const StencilStateRHI* state1, const StencilStateRHI* state2 ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( StencilState, state1 );
	DYNAMIC_CAST_GLRESOURCE_CONST( StencilState, state2 );

	return IsSameState( gl_state1, gl_state2 );
}

_ubool GLDrv::IsSameBlendState( const BlendStateRHI* state1, const BlendStateRHI* state2 ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( BlendState, state1 );
	DYNAMIC_CAST_GLRESOURCE_CONST( BlendState, state2 );

	return IsSameState( gl_state1, gl_state2 );
}