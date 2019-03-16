//! @file     GLHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLHelper Implementation
//----------------------------------------------------------------------------

// OpenGLES
#if (_OPENGLES_ == 1)

_ubool GLHelper::FindInternalFormatAndType( _PIXEL_FORMAT& format, GLenum& internalformat, GLenum& type )
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
			internalformat	= GL_RGBA;
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
			if ( gGLSupportFBODepthStencil )
			{
				internalformat	= GL_DEPTH_STENCIL_OES;
				type			= GL_UNSIGNED_INT_24_8_OES;
			}
			else
			{
				format			= _PF_SHADOW_DEPTH;

				internalformat	= GL_DEPTH_COMPONENT;
				type			= GL_UNSIGNED_INT;
			}
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

_void GLHelper::InitPixelFormats( )
{
	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_R8G8B8					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_R5G6B5					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_R5G5B5A1					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_R4G4B4A4					].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_G8						].mPlatformFormat	= GL_LUMINANCE;
	gPixelFormats[ _PF_A8G8						].mPlatformFormat	= GL_LUMINANCE_ALPHA;
	gPixelFormats[ _PF_G16						].mPlatformFormat	= GL_NONE;	// Not supported for rendering.
	gPixelFormats[ _PF_DXT1						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT3						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_DXT5						].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_UYVY						].mPlatformFormat	= GL_NONE;	// @todo opengl: Not supported in OpenGL
	gPixelFormats[ _PF_DEPTH_STENCIL			].mPlatformFormat	= GL_DEPTH_STENCIL_OES;
	gPixelFormats[ _PF_SHADOW_DEPTH				].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_FILTERED_SHADOW_DEPTH	].mPlatformFormat	= GL_DEPTH_COMPONENT;
	gPixelFormats[ _PF_R32F						].mIsSupported		= _false;
	gPixelFormats[ _PF_D24						].mPlatformFormat	= GL_NONE;
	
	gPixelFormats[ _PF_FLOAT_RGB				].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_FLOAT_RGB				].mBlockBytes		= 8;
	gPixelFormats[ _PF_FLOAT_RGBA				].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_FLOAT_RGBA				].mBlockBytes		= 8;

	gPixelFormats[ _PF_BC5						].mPlatformFormat	= GL_NONE;	// @todo opengl
	gPixelFormats[ _PF_A1						].mPlatformFormat	= GL_NONE;	// @todo opengl // Not supported for rendering.
	gPixelFormats[ _PF_A8						].mPlatformFormat	= GL_ALPHA;
}

// OpenGL
#else

_ubool GLHelper::FindInternalFormatAndType( _PIXEL_FORMAT& format, GLenum& internalformat, GLenum& type )
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
			internalformat	= GL_RGBA;
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
			internalformat	= GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_DXT3:
		{
			internalformat	= GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;
		
		case _PF_DXT5:
		{
			internalformat	= GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		case _PF_G8:
		{
			internalformat	= GL_LUMINANCE8;
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
			internalformat	= GL_DEPTH24_STENCIL8;
			type			= GL_UNSIGNED_INT_24_8;
		}
		break;

		case _PF_D24:
		case _PF_SHADOW_DEPTH:
		case _PF_FILTERED_SHADOW_DEPTH:
		{
			internalformat	= GL_DEPTH_COMPONENT16;
			type			= GL_FLOAT;
		}
		break;

		case _PF_A8:
		{
			internalformat	= GL_ALPHA8;
			type			= GL_UNSIGNED_BYTE;
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_void GLHelper::InitPixelFormats( )
{
	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= GL_NONE;
	gPixelFormats[ _PF_R8G8B8					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_R5G6B5					].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= GL_RGBA;
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
	gPixelFormats[ _PF_D24						].mPlatformFormat	= GL_NONE;

	gPixelFormats[ _PF_FLOAT_RGB				].mPlatformFormat	= GL_RGB;
	gPixelFormats[ _PF_FLOAT_RGB				].mBlockBytes		= 8;
	gPixelFormats[ _PF_FLOAT_RGBA				].mPlatformFormat	= GL_RGBA;
	gPixelFormats[ _PF_FLOAT_RGBA				].mBlockBytes		= 8;

	gPixelFormats[ _PF_BC5						].mPlatformFormat	= GL_NONE;	// @todo opengl
	gPixelFormats[ _PF_A1						].mPlatformFormat	= GL_NONE;	// @todo opengl // Not supported for rendering.
	gPixelFormats[ _PF_A8						].mPlatformFormat	= GL_ALPHA;
}

#endif

GLenum GLHelper::FindPrimitiveType( _PRIMITIVE_TYPE type )
{
	switch ( type )
	{
		case _PT_POINT_LIST:		return GL_POINTS;
		case _PT_LINE_LIST:			return GL_LINES;
		case _PT_LINE_LOOP:			return GL_LINE_LOOP;
		case _PT_TRIANGLE_LIST:		return GL_TRIANGLES;
		case _PT_TRIANGLE_STRIP:	return GL_TRIANGLE_STRIP;
		case _PT_TRIANGLE_FAN:		return GL_TRIANGLE_FAN;
		default:
			return 0;
	}
}

AStringPtr GLHelper::ConvertInternalFormat2String( GLenum format )
{
    switch ( format )
    {
#if (_OPENGLES_ == 0)
	    case GL_STENCIL_INDEX:			return "GL_STENCIL_INDEX";
#endif
		case GL_DEPTH_COMPONENT:		return "GL_DEPTH_COMPONENT";
#if (_OPENGLES_ == 0)
	    case GL_DEPTH_STENCIL:			return "GL_DEPTH_STENCIL";
#endif
        case GL_ALPHA:					return "GL_ALPHA";
        case GL_RGB:					return "GL_RGB";
        case GL_RGBA:					return "GL_RGBA";
        case GL_LUMINANCE:				return "GL_LUMINANCE";
#if (_OPENGLES_ == 0)
        case GL_LUMINANCE_ALPHA:		return "GL_LUMINANCE_ALPHA";
        case GL_ALPHA4:					return "GL_ALPHA4";
        case GL_ALPHA8:					return "GL_ALPHA8";
        case GL_ALPHA12:				return "GL_ALPHA12";
        case GL_ALPHA16:				return "GL_ALPHA16";
        case GL_LUMINANCE4:				return "GL_LUMINANCE4";
        case GL_LUMINANCE8:				return "GL_LUMINANCE8";
        case GL_LUMINANCE12:			return "GL_LUMINANCE12";
        case GL_LUMINANCE16:			return "GL_LUMINANCE16";
        case GL_LUMINANCE4_ALPHA4:		return "GL_LUMINANCE4_ALPHA4";
        case GL_LUMINANCE6_ALPHA2:		return "GL_LUMINANCE6_ALPHA2";
        case GL_LUMINANCE8_ALPHA8:		return "GL_LUMINANCE8_ALPHA8";
        case GL_LUMINANCE12_ALPHA4:		return "GL_LUMINANCE12_ALPHA4";
        case GL_LUMINANCE12_ALPHA12:	return "GL_LUMINANCE12_ALPHA12";
        case GL_LUMINANCE16_ALPHA16:	return "GL_LUMINANCE16_ALPHA16";
        case GL_INTENSITY:				return "GL_INTENSITY";
        case GL_INTENSITY4:				return "GL_INTENSITY4";
        case GL_INTENSITY8:				return "GL_INTENSITY8";
        case GL_INTENSITY12:			return "GL_INTENSITY12";
        case GL_INTENSITY16:			return "GL_INTENSITY16";
        case GL_R3_G3_B2:				return "GL_R3_G3_B2";
        case GL_RGB4:					return "GL_RGB4";
        case GL_RGB5:					return "GL_RGB4";
        case GL_RGB8:					return "GL_RGB8";
        case GL_RGB10:					return "GL_RGB10";
        case GL_RGB12:					return "GL_RGB12";
        case GL_RGB16:					return "GL_RGB16";
        case GL_RGBA2:					return "GL_RGBA2";
        case GL_RGBA4:					return "GL_RGBA4";
        case GL_RGB5_A1:				return "GL_RGB5_A1";
        case GL_RGBA8:					return "GL_RGBA8";
        case GL_RGB10_A2:				return "GL_RGB10_A2";
        case GL_RGBA12:					return "GL_RGBA12";
        case GL_RGBA16:					return "GL_RGBA16";
#endif
		default:
			break;
    }

	return "Unknown Format";
}