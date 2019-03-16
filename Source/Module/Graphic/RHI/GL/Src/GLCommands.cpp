//! @file     GLCommands.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-Commands Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	Set texture sampler state.
template< typename Type >
static _void SetTextureSamplerState( GLenum tex_target, Type* texture, _dword samplerindex, const SamplerStateRHI* state )
{
	// The texture target and resource ID
	EGE_ASSERT( texture != _null );
	GLuint tex_resource	= texture->GetResource( );

	// Get the current texture stage info
	GLTextureStage& texture_stage = gGLCachedState.mTextures[ samplerindex ];

	// Check whether need to change texture binding
	_ubool needs_to_change_texture	= texture_stage.mTarget != tex_target || texture_stage.mResource != tex_resource;
	_ubool needs_to_update_state	= needs_to_change_texture || gDynamicRHI->IsSameSamplerState( texture_stage.mState, state ) == _false;

	// Bind the texture
	if ( needs_to_change_texture )
	{
		// Active the sampler index of texture
		GLCachedSetActiveTexture( samplerindex );

		// Bind texture
		GLCachedBindTexture( tex_target, tex_resource );

		// Update the cached state
		texture_stage.mTarget	= tex_target;
		texture_stage.mResource = tex_resource;
	}

	// Update the sampler of texture
	if ( needs_to_update_state )
	{
		if ( state != _null )
		{
			DYNAMIC_CAST_GLRESOURCE_CONST( SamplerState, state );

			texture->UpdateSamplerState( gl_state->mInfo );
		}

		// Update the cached state
		texture_stage.mState = state;
	}
}

//----------------------------------------------------------------------------
// GLDrv-Commands Implementation
//----------------------------------------------------------------------------

_void GLDrv::SetLineWidth( _float width )
{
	if ( gGLCachedState.mLineWidth != width )
	{
		GL_CHECK_ERROR( __glLineWidth( width ) );

		gGLCachedState.mLineWidth = width;
	}
}

_void GLDrv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
	DYNAMIC_CAST_GLRESOURCE( Surface, rendertarget );
	DYNAMIC_CAST_GLRESOURCE( Surface, depthstencil );

	// Bind the default frame buffer
	if ( gl_rendertarget == _null && gl_depthstencil == _null )
	{
		// Bind the main FBO
		mMainViewport->GetGLContext( )->Bind( );
	}
	// Bind the custom frame buffer
	else
	{
		// Get the frame buffer
		GLFramebuffer* gl_framebuffer = GLFramebufferCache::GetInstance( ).GetFramebuffer( gl_rendertarget, gl_depthstencil );
		EGE_ASSERT( gl_framebuffer != _null );

		// Bind the frame buffer
		gl_framebuffer->Bind( );
	}
}

_void GLDrv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{
	EGE_ASSERT( pixels );

	// Get the internal pixel format and data type
	GLenum internalformat = GL_RGBA; GLenum datatype = GL_UNSIGNED_BYTE;
	GLHelper::FindInternalFormatAndType( format, internalformat, datatype );

	GL_CHECK_ERROR( __glReadPixels( rect.l, rect.t, rect.GetWidth( ), rect.GetHeight( ), internalformat, datatype, pixels ) );
}

_void GLDrv::SetBoundShader( BoundShaderRHI* shader )
{
	if ( shader == _null )
		return;

	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );
	gl_shader->Bind( );
}

_void GLDrv::SetDepthState( const DepthStateRHI* state )
{
	DYNAMIC_CAST_GLRESOURCE_CONST( DepthState, state );
	if ( gl_state == _null )
		return;

	GLDepthStateInfo*&		cached_state	= gGLCachedState.mDepthState;
	const GLDepthStateInfo& last_state		= gl_state->mInfo;

	if ( cached_state == _null )
	{
		if ( last_state.mZEnable )
		{
			GL_CHECK_ERROR( __glEnable( GL_DEPTH_TEST ) );
		}
		else
		{
			GL_CHECK_ERROR( __glDisable( GL_DEPTH_TEST ) );
		}

		GL_CHECK_ERROR( __glDepthFunc( last_state.mZFunc ) );
		GL_CHECK_ERROR( __glDepthMask( EGE_BOOLEAN( last_state.mZWriteEnable ) ) );

		cached_state = new GLDepthStateInfo( last_state );
	}
	else
	{
		if ( cached_state->mZEnable != last_state.mZEnable )
		{
			if ( last_state.mZEnable )
			{
				GL_CHECK_ERROR( __glEnable( GL_DEPTH_TEST ) );
			}
			else
			{
				GL_CHECK_ERROR( __glDisable( GL_DEPTH_TEST ) );
			}

			cached_state->mZEnable = last_state.mZEnable;
		}

		if ( last_state.mZEnable && cached_state->mZFunc != last_state.mZFunc )
		{
			GL_CHECK_ERROR( __glDepthFunc( last_state.mZFunc ) );
			cached_state->mZFunc = last_state.mZFunc;
		}

		if ( cached_state->mZWriteEnable != last_state.mZWriteEnable )
		{
			GL_CHECK_ERROR( __glDepthMask( EGE_BOOLEAN( last_state.mZWriteEnable ) ) );
			cached_state->mZWriteEnable = last_state.mZWriteEnable;
		}
	}
}

_void GLDrv::SetStencilState( const StencilStateRHI* state )
{
	DYNAMIC_CAST_GLRESOURCE_CONST( StencilState, state );
	if ( gl_state == _null )
		return;

	GLStencilStateInfo*&		cached_state	= gGLCachedState.mStencilState;
	const GLStencilStateInfo&	last_state		= gl_state->mInfo;

	if ( cached_state == _null )
	{
		if ( last_state.mStencilEnable )
		{
			GL_CHECK_ERROR( __glEnable( GL_STENCIL_TEST ) );
		}
		else
		{
			GL_CHECK_ERROR( __glDisable( GL_STENCIL_TEST ) );
		}

		if ( last_state.mStencilEnable )
		{
			if ( last_state.mTwoSidedStencilMode )
			{
				GL_CHECK_ERROR( __glStencilFuncSeparate( GL_BACK, last_state.mStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
				GL_CHECK_ERROR( __glStencilOpSeparate( GL_BACK, last_state.mStencilFail, last_state.mStencilZFail, last_state.mStencilPass ) );
				GL_CHECK_ERROR( __glStencilFuncSeparate( GL_FRONT, last_state.mCCWStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
				GL_CHECK_ERROR( __glStencilOpSeparate( GL_FRONT, last_state.mCCWStencilFail, last_state.mCCWStencilZFail, last_state.mCCWStencilPass ) );
			}
			else
			{
				GL_CHECK_ERROR( __glStencilFunc( last_state.mStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
				GL_CHECK_ERROR( __glStencilOp( last_state.mStencilFail, last_state.mStencilZFail, last_state.mStencilPass ) );
			}

			GL_CHECK_ERROR( __glStencilMask( last_state.mStencilWriteMask ) );
		}

		cached_state = new GLStencilStateInfo( last_state );
	}
	else
	{
		if ( cached_state->mStencilEnable != last_state.mStencilEnable )
		{
			if ( last_state.mStencilEnable )
			{
				GL_CHECK_ERROR( __glEnable( GL_STENCIL_TEST ) );
			}
			else
			{
				GL_CHECK_ERROR( __glDisable( GL_STENCIL_TEST ) );
			}

			cached_state->mStencilEnable = last_state.mStencilEnable;
		}

		if ( last_state.mStencilEnable )
		{
			if ( last_state.mTwoSidedStencilMode )
			{
				if ( cached_state->mStencilFunc != last_state.mStencilFunc
					|| cached_state->mStencilRef != last_state.mStencilRef
					|| cached_state->mStencilReadMask != last_state.mStencilReadMask )
				{
					GL_CHECK_ERROR( __glStencilFuncSeparate( GL_BACK, last_state.mStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
					cached_state->mStencilFunc 		= last_state.mStencilFunc;
					cached_state->mStencilRef		= last_state.mStencilRef;
					cached_state->mStencilReadMask	= last_state.mStencilReadMask;
				}

				if ( cached_state->mStencilFail != last_state.mStencilFail
					|| cached_state->mStencilZFail != last_state.mStencilZFail
					|| cached_state->mStencilPass != last_state.mStencilPass )
				{
					GL_CHECK_ERROR( __glStencilOpSeparate( GL_BACK, last_state.mStencilFail, last_state.mStencilZFail, last_state.mStencilPass ) );
					cached_state->mStencilFail	= last_state.mStencilFail;
					cached_state->mStencilZFail	= last_state.mStencilZFail;
					cached_state->mStencilPass	= last_state.mStencilPass;
				}

				if ( cached_state->mCCWStencilFunc != last_state.mCCWStencilFunc
					|| cached_state->mStencilRef != last_state.mStencilRef
					|| cached_state->mStencilReadMask != last_state.mStencilReadMask )
				{
					GL_CHECK_ERROR( __glStencilFuncSeparate( GL_FRONT, last_state.mCCWStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
					cached_state->mCCWStencilFunc = last_state.mCCWStencilFunc;
				}

				if ( cached_state->mCCWStencilFail != last_state.mCCWStencilFail
					|| cached_state->mCCWStencilZFail != last_state.mCCWStencilZFail
					|| cached_state->mCCWStencilPass != last_state.mCCWStencilPass )
				{
					GL_CHECK_ERROR( __glStencilOpSeparate( GL_FRONT, last_state.mCCWStencilFail, last_state.mCCWStencilZFail, last_state.mCCWStencilPass ) );
					cached_state->mCCWStencilFail	= last_state.mCCWStencilFail;
					cached_state->mCCWStencilZFail	= last_state.mCCWStencilZFail;
					cached_state->mCCWStencilPass	= last_state.mCCWStencilPass;
				}
			}
			else
			{
				if ( cached_state->mStencilFunc != last_state.mStencilFunc
					|| cached_state->mCCWStencilFunc != last_state.mStencilFunc
					|| cached_state->mStencilRef != last_state.mStencilRef
					|| cached_state->mStencilReadMask != last_state.mStencilReadMask )
				{
					GL_CHECK_ERROR( __glStencilFunc( last_state.mStencilFunc, last_state.mStencilRef, last_state.mStencilReadMask ) );
					cached_state->mStencilFunc		= last_state.mStencilFunc;
					cached_state->mCCWStencilFunc	= last_state.mStencilFunc;
					cached_state->mStencilRef		= last_state.mStencilRef;
					cached_state->mStencilReadMask	= last_state.mStencilReadMask;
				}

				if ( cached_state->mStencilFail != last_state.mStencilFail
					|| cached_state->mStencilZFail != last_state.mStencilZFail
					|| cached_state->mStencilPass != last_state.mStencilPass
					|| cached_state->mCCWStencilFail != last_state.mStencilFail
					|| cached_state->mCCWStencilZFail != last_state.mStencilZFail
					|| cached_state->mCCWStencilPass != last_state.mStencilPass )
				{
					GL_CHECK_ERROR( __glStencilOp( last_state.mStencilFail, last_state.mStencilZFail, last_state.mStencilPass ) );
					cached_state->mStencilFail		= last_state.mStencilFail;
					cached_state->mStencilZFail		= last_state.mStencilZFail;
					cached_state->mStencilPass		= last_state.mStencilPass;
					cached_state->mCCWStencilFail	= last_state.mStencilFail;
					cached_state->mCCWStencilZFail	= last_state.mStencilZFail;
					cached_state->mCCWStencilPass	= last_state.mStencilPass;
				}
			}

			if ( cached_state->mStencilWriteMask != last_state.mStencilWriteMask )
			{
				GL_CHECK_ERROR( __glStencilMask( last_state.mStencilWriteMask ) );
				cached_state->mStencilWriteMask = last_state.mStencilWriteMask;
			}
		}
	}
}

_void GLDrv::SetBlendState( const BlendStateRHI* state )
{
	DYNAMIC_CAST_GLRESOURCE_CONST( BlendState, state );
	if ( gl_state == _null )
		return;

	GLBlendStateInfo*&		cached_state	= gGLCachedState.mBlendState;
	const GLBlendStateInfo& last_state		= gl_state->mInfo;

	if ( cached_state == _null )
	{
		if ( last_state.mAlphaBlendEnable )
		{
			GL_CHECK_ERROR( __glEnable( GL_BLEND ) );
		}
		else
		{
			GL_CHECK_ERROR( __glDisable( GL_BLEND ) );
		}

		if ( last_state.mAlphaBlendEnable )
		{
			if ( last_state.mSeparateAlphaBlendEnable )
			{
				GL_CHECK_ERROR( __glBlendFuncSeparate( last_state.mColorSourceBlendFactor, last_state.mColorDestBlendFactor, last_state.mAlphaSourceBlendFactor, last_state.mAlphaDestBlendFactor ) );
			}
			else
			{
				GL_CHECK_ERROR( __glBlendFunc( last_state.mColorSourceBlendFactor, last_state.mColorDestBlendFactor ) );
			}
		}

		cached_state = new GLBlendStateInfo( last_state );
	}
	else
	{
		if ( cached_state->mAlphaBlendEnable != last_state.mAlphaBlendEnable )
		{
			if ( last_state.mAlphaBlendEnable )
			{
				GL_CHECK_ERROR( __glEnable( GL_BLEND ) );
			}
			else
			{
				GL_CHECK_ERROR( __glDisable( GL_BLEND ) );
			}

			cached_state->mAlphaBlendEnable = last_state.mAlphaBlendEnable;
		}

		if ( last_state.mAlphaBlendEnable )
		{
			if ( last_state.mSeparateAlphaBlendEnable )
			{
				if ( cached_state->mColorSourceBlendFactor != last_state.mColorSourceBlendFactor
					|| cached_state->mColorDestBlendFactor != last_state.mColorDestBlendFactor
					|| cached_state->mAlphaSourceBlendFactor != last_state.mAlphaSourceBlendFactor
					|| cached_state->mAlphaDestBlendFactor != last_state.mAlphaDestBlendFactor )
				{
					GL_CHECK_ERROR( __glBlendFuncSeparate( last_state.mColorSourceBlendFactor, last_state.mColorDestBlendFactor, last_state.mAlphaSourceBlendFactor, last_state.mAlphaDestBlendFactor ) );
					cached_state->mColorSourceBlendFactor	= last_state.mColorSourceBlendFactor;
					cached_state->mColorDestBlendFactor		= last_state.mColorDestBlendFactor;
					cached_state->mAlphaSourceBlendFactor	= last_state.mAlphaSourceBlendFactor;
					cached_state->mAlphaDestBlendFactor		= last_state.mAlphaDestBlendFactor;
				}
			}
			else
			{
				if ( cached_state->mColorSourceBlendFactor != last_state.mColorSourceBlendFactor
					|| cached_state->mColorDestBlendFactor != last_state.mColorDestBlendFactor
					|| cached_state->mAlphaSourceBlendFactor != last_state.mColorSourceBlendFactor
					|| cached_state->mAlphaDestBlendFactor != last_state.mColorDestBlendFactor )
				{
					GL_CHECK_ERROR( __glBlendFunc( last_state.mColorSourceBlendFactor, last_state.mColorDestBlendFactor ) );
					cached_state->mColorSourceBlendFactor	= last_state.mColorSourceBlendFactor;
					cached_state->mColorDestBlendFactor		= last_state.mColorDestBlendFactor;
					cached_state->mAlphaSourceBlendFactor	= last_state.mColorSourceBlendFactor;
					cached_state->mAlphaDestBlendFactor		= last_state.mColorDestBlendFactor;
				}
			}
		}
	}
}

_void GLDrv::SetRasterizerState( const RasterizerStateRHI* state )
{
	DYNAMIC_CAST_GLRESOURCE_CONST( RasterizerState, state );
	if ( gl_state == _null )
		return;

	GLRasterizerStateInfo*&			cached_state	= gGLCachedState.mRasterizerState;
	const GLRasterizerStateInfo&	last_state		= gl_state->mInfo;

	if ( cached_state == _null )
	{
		if ( last_state.mCullModeEnabled )
		{
			GL_CHECK_ERROR( __glEnable( GL_CULL_FACE ) );
		}
		else
		{
			GL_CHECK_ERROR( __glDisable( GL_CULL_FACE ) );
		}

		if ( last_state.mCullMode != GL_NONE )
		{
			GL_CHECK_ERROR( __glCullFace( last_state.mCullMode ) );
		}

		GL_CHECK_ERROR( __glColorMask( EGE_BOOLEAN( last_state.mEnableRedColorWrite ), EGE_BOOLEAN( last_state.mEnableGreenColorWrite ), EGE_BOOLEAN( last_state.mEnableBlueColorWrite ), EGE_BOOLEAN( last_state.mEnableAlphaColorWrite ) ) );

		cached_state = new GLRasterizerStateInfo( last_state );
	}
	else
	{
		if ( cached_state->mCullModeEnabled != last_state.mCullModeEnabled )
		{
			if ( last_state.mCullModeEnabled )
			{
				GL_CHECK_ERROR( __glEnable( GL_CULL_FACE ) );
			}
			else
			{
				GL_CHECK_ERROR( __glDisable( GL_CULL_FACE ) );
			}

			cached_state->mCullModeEnabled = last_state.mCullModeEnabled;
		}

		if ( last_state.mCullMode != GL_NONE && cached_state->mCullMode != last_state.mCullMode )
		{
			GL_CHECK_ERROR( __glCullFace( last_state.mCullMode ) );

			cached_state->mCullMode = last_state.mCullMode;
		}

		if ( cached_state->mEnableRedColorWrite != last_state.mEnableRedColorWrite
			|| cached_state->mEnableGreenColorWrite != last_state.mEnableGreenColorWrite
			|| cached_state->mEnableBlueColorWrite != last_state.mEnableBlueColorWrite
			|| cached_state->mEnableAlphaColorWrite != last_state.mEnableAlphaColorWrite )
		{
			GL_CHECK_ERROR( __glColorMask( EGE_BOOLEAN( last_state.mEnableRedColorWrite ), EGE_BOOLEAN( last_state.mEnableGreenColorWrite ), EGE_BOOLEAN( last_state.mEnableBlueColorWrite ), EGE_BOOLEAN( last_state.mEnableAlphaColorWrite ) ) );

			cached_state->mEnableRedColorWrite		= last_state.mEnableRedColorWrite;
			cached_state->mEnableGreenColorWrite	= last_state.mEnableGreenColorWrite;
			cached_state->mEnableBlueColorWrite		= last_state.mEnableBlueColorWrite;
			cached_state->mEnableAlphaColorWrite	= last_state.mEnableAlphaColorWrite;
		}
	}
}

_void GLDrv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{
	RasterizerStateRHIRef state = CreateRasterizerState( initializer );
	SetRasterizerState( state );
}

_void GLDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, Texture2DRHI* texture )
{
	if ( texture == _null )
		return;

	DYNAMIC_CAST_GLRESOURCE( Texture2D, texture );

	SetTextureSamplerState( GL_TEXTURE_2D, gl_texture, samplerindex, state );
}

_void GLDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureCubeRHI* texture )
{
	if ( texture == _null )
		return;

	DYNAMIC_CAST_GLRESOURCE( TextureCube, texture );

	SetTextureSamplerState( GL_TEXTURE_CUBE_MAP, gl_texture, samplerindex, state );
}

_void GLDrv::SetViewport( const Viewport& viewport )
{
	// Convert data type to pixel
	_dword offset_x	= (_dword) viewport.x;
	_dword offset_y	= (_dword) viewport.y;
	_dword width	= (_dword) viewport.w;
	_dword height	= (_dword) viewport.h;

	// Get the cached info
	PointU& cached_viewport_offset	= gGLCachedState.mViewportOffset;
	PointU& cached_viewport_size	= gGLCachedState.mViewportSize;

	// Check whether need to update GL viewport
	_ubool update_viewport = _false;
	if ( cached_viewport_offset.x != offset_x || cached_viewport_offset.y != offset_y )
		update_viewport = _true;
	else if ( cached_viewport_size.x != width || cached_viewport_size.y != height )
		update_viewport = _true;

	// Update GL viewport
	if ( update_viewport )
	{
		cached_viewport_offset.x	= offset_x;
		cached_viewport_offset.y	= offset_y;
		cached_viewport_size.x		= width;
		cached_viewport_size.y		= height;

		GL_CHECK_ERROR( __glViewport( offset_x, offset_y, width, height ) );

		//WLOG_DEBUG_4( L"Set GL viewport(offset_x: %d, offset_y:%d, width:%d, height:%d",
		//	offset_x, offset_y, width, height );
	}
}

_void GLDrv::ClearBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	_dword clear_flags = 0;

	// Update clear color
	if ( gGLCachedState.mClearColor == _null || *gGLCachedState.mClearColor != color )
	{
		GL_CHECK_ERROR( __glClearColor( color.Red( ), color.Green( ), color.Blue( ), color.Alpha( ) ) );

		if ( gGLCachedState.mClearColor == _null )
			gGLCachedState.mClearColor = new Color( );

		*gGLCachedState.mClearColor = color;
	}

	// Update depth clear value
	if ( gGLCachedState.mClearDepth == _null || *gGLCachedState.mClearDepth != depth )
	{
		GL_CHECK_ERROR( __glClearDepthf( depth ) );

		if ( gGLCachedState.mClearDepth == _null )
			gGLCachedState.mClearDepth = new _float( );

		*gGLCachedState.mClearDepth = depth;
	}

	// Update stencil clear value
	if ( gGLCachedState.mClearStencil == _null || *gGLCachedState.mClearStencil != stencil )
	{
		GL_CHECK_ERROR( __glClearStencil( stencil ) );

		if ( gGLCachedState.mClearStencil == _null )
			gGLCachedState.mClearStencil = new _dword( );

		*gGLCachedState.mClearStencil = stencil;
	}

	// Clear color buffer
	if ( clearcolor )
	{
		if ( gGLCachedState.mRasterizerState == _null )
		{
			GL_CHECK_ERROR( __glColorMask( _true, _true, _true, _true ) );
		}
		else if ( gGLCachedState.mRasterizerState->mEnableRedColorWrite == _false
			|| gGLCachedState.mRasterizerState->mEnableGreenColorWrite == _false
			|| gGLCachedState.mRasterizerState->mEnableBlueColorWrite == _false
			|| gGLCachedState.mRasterizerState->mEnableAlphaColorWrite == _false )
		{
			gGLCachedState.mRasterizerState->mEnableRedColorWrite	= _true;
			gGLCachedState.mRasterizerState->mEnableGreenColorWrite = _true;
			gGLCachedState.mRasterizerState->mEnableBlueColorWrite	= _true;
			gGLCachedState.mRasterizerState->mEnableAlphaColorWrite = _true;

			GL_CHECK_ERROR( __glColorMask( _true, _true, _true, _true ) );
		}

		clear_flags |= GL_COLOR_BUFFER_BIT;
	}

	// Clear depth and stencil buffer
	if ( cleardepth )
	{
		// Make the depth buffer writable
		if ( gGLCachedState.mDepthState == _null )
		{
			GL_CHECK_ERROR( __glDepthMask( _true ) );
		}
		else if ( gGLCachedState.mDepthState->mZWriteEnable != _true )
		{
			GL_CHECK_ERROR( __glDepthMask( _true ) );
			gGLCachedState.mDepthState->mZWriteEnable = _true;
		}

		clear_flags |= GL_DEPTH_BUFFER_BIT;
	}

	if ( clearstencil )
		clear_flags |= GL_STENCIL_BUFFER_BIT;

	// Clear render buffers
	if ( clear_flags != 0 )
	{
		GL_CHECK_ERROR( __glClear( clear_flags ) );
	}
}

_void GLDrv::DrawPoint( const Vector2& position, const Color& color ) 
{
}

_void GLDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
}

_void GLDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
}

_void GLDrv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
}

_void GLDrv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
}

_void GLDrv::FillRectangle( const RectI& rect, const Color& color )
{
}

_void GLDrv::FillRectangle( const RectF& rect, const Color& color )
{
}

_void GLDrv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
}

_void GLDrv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
//	DYNAMIC_CAST_GDIRESOURCE( Font, font );
}

_void GLDrv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
	// Find the primitive type
	GLenum drawmode = GLHelper::FindPrimitiveType( type );
	EGE_ASSERT( drawmode != 0 );

	// Draw vertex arrays
	GL_CHECK_ERROR( __glDrawArrays( drawmode, offset, number ) );
}

_void GLDrv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{
	// Find the primitive type
	GLenum drawmode = GLHelper::FindPrimitiveType( type );
	EGE_ASSERT( drawmode != 0 );

	// Draw elements ( The start index use as start bytes )
	GL_CHECK_ERROR( __glDrawElements( drawmode, number, GL_UNSIGNED_SHORT, (_void*) (start_index * sizeof( _word )) ) );
}