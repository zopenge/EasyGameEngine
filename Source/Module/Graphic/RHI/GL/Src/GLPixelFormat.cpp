//! @file     GLESDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

// OpenGLES
#if (_OPENGLES_ == 1)

_ubool GLDrv::FindInternalFormatAndType( _PIXEL_FORMAT format, GLenum& internalformat, GLenum& type, _ubool srgb )
{
	switch ( format )
	{
		case _PF_R8G8B8:
		{
			internalformat	= GL_RGB;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_R5G6B5:
		{
			internalformat	= GL_RGB;
			type			= GL_UNSIGNED_SHORT_5_6_5;
		}
		break;

		case _PF_A8R8G8B8:
		{
#ifdef _PLATFORM_IOS_
			internalformat	= GL_RGBA;
#elif _PLATFORM_ANDROID_
			internalformat	= gGLSupportBGRAPixelFormat ? GL_BGRA_EXT : GL_RGBA;
#endif
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_R5G5B5A1:
		{
			internalformat	= GL_RGBA;
			type			= GL_UNSIGNED_SHORT_5_5_5_1;
		}
		break;

		case _PF_R4G4B4A4:
		{
			internalformat	= GL_RGBA;
			type			= GL_UNSIGNED_SHORT_4_4_4_4;
		}
		break;

		case _PF_A8:
		{
			internalformat	= GL_ALPHA;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_A8G8:
		{
			internalformat	= GL_LUMINANCE_ALPHA;
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

_void GLDrv::InitPixelFormats( )
{
	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_A32B32G32R32F			].mIsSupported		= _false;
	gPixelFormats[ _PF_R8G8B8					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_R5G6B5					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= gGLSupportBGRAPixelFormat ? GL_BGRA_EXT : GL_RGBA;
	gPixelFormats[ _PF_R5G5B5A1					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_R4G4B4A4					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_G8						].mPlatformFormat	= GL_LUMINANCE;
	gPixelFormats[ _PF_A8G8						].mPlatformFormat	= GL_LUMINANCE_ALPHA;
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

// OpenGL
#else

_ubool GLDrv::FindInternalFormatAndType( _PIXEL_FORMAT format, GLenum& internalformat, GLenum& type, _ubool srgb )
{
	switch ( format )
	{
		case _PF_A32B32G32R32F:
		{
			internalformat	= srgb ? GL_NONE : GL_RGBA32F_ARB;
			type			= GL_UNSIGNED_NORMALIZED_ARB;
		}
		break;

		case _PF_R8G8B8:
		{
			internalformat	= srgb ? GL_SRGB8_EXT : GL_RGB;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_R5G6B5:
		{
			internalformat	= GL_RGB;
			type			= GL_UNSIGNED_SHORT_5_6_5;
		}
		break;

		case _PF_A8R8G8B8:
		{
			internalformat	= srgb ? GL_SRGB8_ALPHA8_EXT : GL_RGBA;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_R5G5B5A1:
		{
			internalformat	= GL_RGBA;
			type			= GL_UNSIGNED_SHORT_5_5_5_1;
		}
		break;

		case _PF_R4G4B4A4:
		{
			internalformat	= GL_RGBA;
			type			= GL_UNSIGNED_SHORT_4_4_4_4;
		}
		break;

		case _PF_DXT1:
		{
			internalformat	= srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT : GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_DXT3:
		{
			internalformat	= srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT : GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;
		
		case _PF_DXT5:
		{
			internalformat	= srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT : GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_G8:
		{
			internalformat	= srgb ? GL_RGB8 : GL_LUMINANCE8;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_A8G8:
		{
			internalformat	= GL_LUMINANCE8_ALPHA8;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_DEPTH_STENCIL:
		{
			internalformat	= srgb ? GL_NONE : GL_DEPTH24_STENCIL8_EXT;
			type			= GL_UNSIGNED_INT_24_8_EXT;
		}
		break;

		case _PF_D24:
		case _PF_SHADOW_DEPTH:
		case _PF_FILTERED_SHADOW_DEPTH:
		{
			internalformat	= srgb ? GL_NONE : GL_DEPTH_COMPONENT;
			type			= GL_FLOAT;
		}
		break;

		case _PF_G16R16:
		{
			internalformat	= srgb ? GL_RGBA16 : GL_RG16;
			type			= GL_UNSIGNED_SHORT;
		}
		break;

		case _PF_G16R16F:
		case _PF_G16R16F_FILTER:
		{
			internalformat	= srgb ? GL_RGBA16F_ARB : GL_RG16F;
			type			= GL_HALF_FLOAT_ARB;
		}
		break;

		case _PF_G32R32F:
		{
			internalformat	= srgb ? GL_RGBA32F_ARB : GL_RG32F;
			type			= GL_FLOAT;
		}
		break;

		case _PF_A2B10G10R10:
		{
			internalformat	= srgb ? GL_NONE : GL_RGB10_A2;
			type			= GL_UNSIGNED_INT_2_10_10_10_REV;
		}
		break;

		case _PF_A16B16G16R16:
		{
			internalformat	= srgb ? GL_NONE : GL_RGBA16F_ARB;
			type			= GL_HALF_FLOAT_ARB;
		}
		break;

		case _PF_R16F:
		case _PF_R16F_FILTER:
		{
			internalformat	= srgb ? GL_NONE : GL_R16F;
			type			= GL_HALF_FLOAT_ARB;
		}
		break;

		case _PF_V8U8:
		{
			internalformat	= srgb ? GL_NONE : GL_RG8;
			type			= GL_BYTE;
		}
		break;

		case _PF_A8:
		{
			internalformat	= srgb ? GL_NONE : GL_ALPHA8;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_void GLDrv::InitPixelFormats( )
{
	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_A32B32G32R32F			].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_R8G8B8					].mPlatformFormat	= GL_BGR;
	gPixelFormats[ _PF_R5G6B5					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= gGLSupportBGRAPixelFormat ? GL_BGRA_EXT : GL_RGBA;
	gPixelFormats[ _PF_R5G5B5A1					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_R4G4B4A4					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_G8						].mPlatformFormat	= GL_LUMINANCE;
	gPixelFormats[ _PF_A8G8						].mPlatformFormat	= GL_LUMINANCE_ALPHA;
	gPixelFormats[ _PF_G16						].mPlatformFormat	= GL_NONE;	// Not supported for rendering.
	gPixelFormats[ _PF_DXT1						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT3						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT5						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_UYVY						].mPlatformFormat	= GL_NONE;	// @todo opengl: Not supported in OpenGL
	gPixelFormats[ _PF_DEPTH_STENCIL			].mPlatformFormat	= GL_DEPTH_STENCIL;
	gPixelFormats[ _PF_SHADOW_DEPTH				].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_FILTERED_SHADOW_DEPTH	].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_R32F						].mPlatformFormat	= GL_RED;
	gPixelFormats[ _PF_G16R16					].mPlatformFormat	= GL_RG;
	gPixelFormats[ _PF_G16R16F					].mPlatformFormat	= GL_RG;
	gPixelFormats[ _PF_G16R16F_FILTER			].mPlatformFormat	= GL_RG;
	gPixelFormats[ _PF_G32R32F					].mPlatformFormat	= GL_RG;
	gPixelFormats[ _PF_A2B10G10R10   			].mPlatformFormat   = GL_RGBA;
	gPixelFormats[ _PF_A16B16G16R16  			].mPlatformFormat   = GL_RGBA;
	gPixelFormats[ _PF_D24						].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_R16F						].mPlatformFormat	= GL_RED;
	gPixelFormats[ _PF_R16F_FILTER				].mPlatformFormat	= GL_RED;

	gPixelFormats[ _PF_FLOAT_RGB				].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_FLOAT_RGB				].mBlockBytes		= 8;
	gPixelFormats[ _PF_FLOAT_RGBA				].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_FLOAT_RGBA				].mBlockBytes		= 8;

	gPixelFormats[ _PF_V8U8						].mPlatformFormat	= GL_RG;
	gPixelFormats[ _PF_BC5						].mPlatformFormat	= GL_NONE;	// @todo opengl
	gPixelFormats[ _PF_A1						].mPlatformFormat	= GL_NONE;	// @todo opengl // Not supported for rendering.
	gPixelFormats[ _PF_A8						].mPlatformFormat	= GL_ALPHA;
}

#endif