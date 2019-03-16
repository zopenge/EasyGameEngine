//! @file     GLPlatform.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//!	The GL extensions string
extern EGE::AStringPtr	gGLExtensions;
//!	The EGL extensions string
extern EGE::AStringPtr	gEGLExtensions;
//!	The GL features.
extern EGE::_ubool		gGLSupportETC1;
extern EGE::_ubool		gGLSupportETC2;
extern EGE::_ubool		gGLSupportInstancedRendering;
extern EGE::_ubool		gGLSupportVAO;
extern EGE::_ubool		gGLSupportFBO;
extern EGE::_ubool		gGLSupportFBODepthStencil;


//!	Check whether OpenGL support this extension.
//!	@param		name		The extension name.
//!	@return		True indicates support it.
EGE_INTERNAL EGE::_ubool IsGLSupport( const EGE::_chara* name );
//!	Check the GL/EGL features.
//!	@param		none.
//! @return		True indicates success, false indicates failure.
EGE_INTERNAL EGE::_ubool CheckGLFeatures( );
//!	Get the OpenGL version.
//!	@param		none.
//!	@return		The OpenGL version.
EGE_INTERNAL EGE::Version GetGLVersion( );
//!	Get the GLSL version.
//!	@param		none.
//!	@return		The GLSL version.
EGE_INTERNAL EGE::Version GetGLSLVersion( );
//!	Create the GL context.
//!	@param		app_handle	The application handle.
//!	@return		The GL context.
EGE_INTERNAL EGE::_handle CreateGLContext( EGE::_handle app_handle );
//!	Release the GL context.
//!	@param		context		The GL context.
//!	@return		none.
EGE_INTERNAL EGE::_void ReleaseGLContext( EGE::_handle context );
//!	Make the current GL context.
//!	@param		context		The GL context.
//! @return		True indicates success, false indicates failure.
EGE_INTERNAL EGE::_ubool MakeCurrentGLContext( EGE::_handle context );
//!	Share the GL context.
//!	@param		context_1	Specifies the OpenGL rendering context with which to share display lists.
//!	@param		context_2	Specifies the OpenGL rendering context to share display lists with context_1.
//! @return		True indicates success, false indicates failure.
EGE_INTERNAL EGE::_ubool ShareGLContext( EGE::_handle context_1, EGE::_handle context_2 );
//!	Get GL contexts number.
//!	@param		none.
//! @return		The number of GL contexts.
EGE_INTERNAL EGE::_dword GetGLContextNumber( );
//!	Flush the current GL context.
//!	@param		context		The GL context.
//!	@return		none.
EGE_INTERNAL EGE::_void FlushGLBuffers( EGE::_handle context );
//!	Set the OVR's render target texture resource.
//!	@param		context		The GL context.
//!	@param		index		The eye index, 0 or 1.
//!	@param		tex_id		The render target texture ID.
//!	@param		tex_size	The render target texture size.
//!	@return		none.
EGE_INTERNAL EGE::_void SetVRRenderTargetTexID( EGE::_handle context, EGE::_dword index, EGE::_dword tex_id, const EGE::PointU& tex_size );
//!	Get the OVR's fov texture size.
//!	@param		context		The GL context.
//!	@param		index		The eye index, 0 or 1.
//!	@return		The size of texture size.
EGE_INTERNAL EGE::PointU GetVRTextureSize( EGE::_handle context, EGE::_dword index );
//!	Get the OVR's eye info.
//!	@param		context		The GL context.
//!	@param		index		The eye index, 0 or 1.
//! @return		The eye info.
EGE_INTERNAL EGE::VREyeRHI GetVREyeInfo( EGE::_handle context, EGE::_dword index );

#ifdef _PLATFORM_IOS_

//!	Allocate render buffer from core animation layer
//!	@param		context		The GL context.
//!	@param		layer		The core animation layer..
//!	@return		none.
EGE_INTERNAL EGE::_void NS_RenderbufferStorage( EGE::_handle context, EGE::_handle layer );

#endif