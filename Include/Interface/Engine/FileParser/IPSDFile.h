//! @file     IPSDFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPSDFile
//----------------------------------------------------------------------------

class IPSDFile : public IImageFile
{
public:
	enum _MODE
	{
		_MODE_BITMAP				= 0, // Bitmap (monochrome)
		_MODE_GRAY_SCALE			= 1, // Gray-scale
		_MODE_INDEXED_COLOR			= 2, // Indexed color (palette color)
		_MODE_RGB_COLOR				= 3, // RGB color
		_MODE_CMYK_COLOR			= 4, // CMYK color
		_MODE_MULTI_CHANNEL_COLOR	= 5, // Multichannel color
		_MODE_DUOTONE				= 6, // Duotone (halftone)
		_MODE_LAB_COLOR				= 7, // Lab color
	};

public:
	//!	The layer info
	struct LayerData
	{
		//!	The relative region
		RectI			mRegion;
		//!	The name of layer
		WString			mName;
		//!	The pixel of layer (ARGB)
		const _byte*	mPixelBuffer;
	};

public:
	//!	Get the mode.
	//!	@param		none.
	//!	@return		The mode.
	virtual _MODE GetMode( ) const PURE;

	//!	Get the layers number.
	//!	@param		none.
	//!	@return		The number of layers.
	virtual _dword GetLayerNumber( ) const PURE;
	//!	Get the layer by index.
	//!	@param		index		The layer index.
	//!	@param		layer		The layer info.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetLayerByIndex( _dword index, LayerData& layer ) const PURE;
};

}