//! @file     GLESDrv.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv Implementation
//----------------------------------------------------------------------------

_ubool GLDrv::FindInternalFormatAndType( _PIXEL_FORMAT format, GLenum& internalformat, GLenum& type, _ubool srgb )
{
	switch ( format )
	{
		case _PF_A8R8G8B8:
		{
			internalformat	= GL_RGBA;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_A8:
		{
			internalformat	= GL_ALPHA;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_DEPTH_STENCIL:
		{
			internalformat	= GL_DEPTH24_STENCIL8_OES;
			type			= GL_UNSIGNED_INT_24_8_OES;
		}
		break;

		case _PF_SHADOW_DEPTH:
		{
			internalformat	= GL_DEPTH_COMPONENT;
			type			= GL_UNSIGNED_INT;
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_void GLDrv::InitializePixelFormats( )
{
	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_A32B32G32R32F			].mIsSupported		= _false;
	gPixelFormats[ _PF_R8G8B8					].mIsSupported		= _false;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= GL_BGRA_EXT;
	gPixelFormats[ _PF_G8						].mPlatformFormat	= GL_LUMINANCE;
	gPixelFormats[ _PF_G16						].mPlatformFormat	= GL_NONE;	// Not supported for rendering.
	gPixelFormats[ _PF_DXT1						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT3						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT5						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_UYVY						].mPlatformFormat	= GL_NONE;	// @todo opengl: Not supported in OpenGL
	gPixelFormats[ _PF_DEPTH_STENCIL			].mIsSupported		= _false;
	gPixelFormats[ _PF_SHADOW_DEPTH				].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_FILTERED_SHADOW_DEPTH	].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_R32F						].mIsSupported		= _false;
	gPixelFormats[ _PF_G16R16					].mIsSupported		= _false;
	gPixelFormats[ _PF_G16R16F					].mIsSupported		= _false;
	gPixelFormats[ _PF_G16R16F_FILTER			].mIsSupported		= _false;
	gPixelFormats[ _PF_G32R32F					].mIsSupported		= _false;
	gPixelFormats[ _PF_A2B10G10R10   			].mPlatformFormat   = GL_RGBA;
	gPixelFormats[ _PF_A16B16G16R16  			].mPlatformFormat   = GL_RGBA;
	gPixelFormats[ _PF_D24						].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_R16F						].mIsSupported		= _false;
	gPixelFormats[ _PF_R16F_FILTER				].mIsSupported		= _false;

	gPixelFormats[ _PF_FLOAT_RGB				].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_FLOAT_RGB				].mBlockBytes		= 8;
	gPixelFormats[ _PF_FLOAT_RGBA				].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_FLOAT_RGBA				].mBlockBytes		= 8;

	gPixelFormats[ _PF_V8U8						].mIsSupported		= _false;
	gPixelFormats[ _PF_BC5						].mPlatformFormat	= GL_NONE;	// @todo opengl
	gPixelFormats[ _PF_A1						].mPlatformFormat	= GL_NONE;	// @todo opengl // Not supported for rendering.
	gPixelFormats[ _PF_A8						].mPlatformFormat	= GL_ALPHA;
}