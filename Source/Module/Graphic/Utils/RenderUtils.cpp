//! @file     RenderUtils.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// Other Variables Implementation
//----------------------------------------------------------------------------

// Pixel Formats
PixelFormatInfo EGE::gPixelFormats[ _PF_MAX ] =
{
	// BlockSizeX	BlockSizeY	BlockSizeZ	BlockBytes	NumComponents	PlatformFormat	Flags	Supported
	{ 0,			0,			0,			0,			0,				0,				0,		_false,	}, // _PF_UNKNOWN
	{ 1,			1,			1,			3,			3,				0,				0,		_true,	}, // _PF_R8G8B8
	{ 1,			1,			1,			2,			3,				0,				0,		_true,	}, // _PF_R5G6B5
	{ 1,			1,			1,			4,			4,				0,				0,		_true,	}, // _PF_A8R8G8B8
	{ 1,			1,			1,			2,			4,				0,				0,		_true,	}, // _PF_R5G5B5A1
	{ 1,			1,			1,			2,			4,				0,				0,		_true,	}, // _PF_R4G4B4A4
	{ 1,			1,			1,			1,			1,				0,				0,		_true,	}, // _PF_G8
	{ 1,			1,			1,			2,			2,				0,				0,		_true,	}, // _PF_A8G8
	{ 1,			1,			1,			2,			1,				0,				0,		_true,	}, // _PF_G16
	{ 4,			4,			1,			8,			3,				0,				0,		_true,	}, // _PF_DXT1
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_DXT3
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_DXT5
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_ETC1_RGB8
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_ETC2_RGBA8
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_RGB_PVRTC_4BPP
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_RGB_PVRTC_2BPP
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_RGBA_PVRTC_4BPP
	{ 4,			4,			1,			16,			4,				0,				0,		_true,	}, // _PF_RGBA_PVRTC_2BPP
	{ 3,			1,			1,			4,			4,				0,				0,		_true,	}, // _PF_UYVY
	{ 1,			1,			1,			0,			3,				0,				0,		_true,	}, // _PF_FLOAT_RGB
	{ 1,			1,			1,			0,			4,				0,				0,		_true,	}, // _PF_FLOAT_RGBA
	{ 1,			1,			1,			4,			1,				0,				0,		_true,	}, // _PF_DEPTH_STENCIL
	{ 1,			1,			1,			4,			1,				0,				0,		_true,	}, // _PF_SHADOW_DEPTH
	{ 1,			1,			1,			4,			1,				0,				0,		_true,	}, // _PF_FILTERED_SHADOW_DEPTH
	{ 1,			1,			1,			4,			1,				0,				0,		_true,	}, // _PF_R32F
	{ 1,			1,			1,			4,			1,				0,				0,		_true,	}, // _PF_D24
	{ 4,			4,			1,			16,			2,				0,				0,		_true,	}, // _PF_BC5
	{ 1,			1,			1,			1,			1,				0,				0,		_true,	}, // _PF_A1
	{ 1,			1,			1,			1,			1,				0,				0,		_true,	}, // _PF_A8
	{ 1,			1,			1,			0,			3,				0,				0,		_true,	}, // _PF_FLOAT_R11G11B10
};

_dword EGE::gMultisampleNumber = 0;

//----------------------------------------------------------------------------
// RenderUtils Implementation
//----------------------------------------------------------------------------

_ubool RenderUtils::IsEmbeddedSystem( )
{
#if (_OPENGLES_ == 1)
	const _ubool is_embedded_system = _true;
#else
	const _ubool is_embedded_system = Platform::IsEmbeddedSystem( );
#endif

	return is_embedded_system;
}

_dword RenderUtils::CaluTextureSize( _dword width, _dword height, _PIXEL_FORMAT format, _dword mipcount )
{
	_dword size = 0;

	for ( _dword mipindex = 0; mipindex < mipcount; mipindex ++ )
	{
		const PixelFormatInfo& pixel_format_info = gPixelFormats[ format ];

		_dword mipsize_x	= Math::Max< _dword >( width >> mipindex, pixel_format_info.mBlockSizeX );
		_dword mipsize_y	= Math::Max< _dword >( height >> mipindex, pixel_format_info.mBlockSizeY );
		_dword pitch		= ( mipsize_x / pixel_format_info.mBlockSizeX ) * pixel_format_info.mBlockBytes;
		_dword rows			= mipsize_y / pixel_format_info.mBlockSizeY;

		size += rows * pitch;
	}

	return size;
}