//! @file     RenderUtils.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GeometryBuildInfo
//----------------------------------------------------------------------------

//!	The geometry build info
struct GeometryBuildInfo
{
	MemArrayPtr< GraphicVertexInfo >	mVertexBuffer;
	MemArrayPtr< _word >				mIndexBuffer;

	IGraphicEffect*						mEffect;
	GraphicGeometryInfo					mGeometryInfo;

	GeometryBuildInfo( )
	{
		mEffect	= _null;
	}
	GeometryBuildInfo( IGraphicEffect* effect )
	{
		mEffect	= effect;
	}
};

//----------------------------------------------------------------------------
// PixelFormatInfo
//----------------------------------------------------------------------------

struct PixelFormatInfo
{
	//!	The block x-size 
	_dword	mBlockSizeX;
	//!	The block y-size 
	_dword	mBlockSizeY;
	//!	The block z-size 
	_dword	mBlockSizeZ;
	//!	The block size in bytes
	_dword	mBlockBytes;

	//!	The number of color components
	_dword	mNumComponents;

	//! Platform specific token
	_dword	mPlatformFormat;
	//! Format specific internal flags
	_dword	mFlags;
	//! Whether the texture format is supported on the current platform
	_ubool	mIsSupported;
};

//! Maps members of PixelFormatInfo describing the format.
extern PixelFormatInfo gPixelFormats[ _PF_MAX ];
	
//!	The multisample number
extern _dword gMultisampleNumber;

//----------------------------------------------------------------------------
// RenderUtils
//----------------------------------------------------------------------------

class RenderUtils
{
public:
	//!	Check whether it's embedded system or not.
	//!	@param		none.
	//!	@return		True indicates it's embedded system.
	static _ubool IsEmbeddedSystem( );

	//! Calculates the amount of memory used for a texture.
	//!	@param		width		Number of horizontal texels (for the base mip-level)
	//!	@param 		height		Number of vertical texels (for the base mip-level)
	//!	@param 		format		Texture format
	//!	@param 		mipcount	Number of mip-levels (including the base mip-level)
	//!	@return		The texture size in bytes.
	static _dword CaluTextureSize( _dword width, _dword height, _PIXEL_FORMAT format, _dword mipcount );
};

//----------------------------------------------------------------------------
// RenderUtils Implementation
//----------------------------------------------------------------------------

}