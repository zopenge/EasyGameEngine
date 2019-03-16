//! @file     IImageFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IImageFile
//----------------------------------------------------------------------------

class IImageFile : public IBaseFile
{
public:
	//!	The flag
	enum _FLAG
	{
		//! Decode the image header only
		_FLAG_HEADER_ONLY			= 1 << 0, 
		//!	Decode RGB/ARGB as R5G5B5A1 color mode
		_FLAG_DECODE_AS_R5G5B5A1	= 1 << 1,
		//!	Decode RGB/ARGB as R4G4B4A4 color mode
		_FLAG_DECODE_AS_R4G4B4A4	= 1 << 2,
		//!	Decode RGB/ARGB as R5G6B5 color mode
		_FLAG_DECODE_AS_R5G6B5		= 1 << 3,
		//!	Decode RGB/ARGB as A8G8 color mode
		_FLAG_DECODE_AS_A8G8		= 1 << 4,
	};

	//!	The clockwise flag
	enum _CLOCKWISE_FLAG
	{
		_CLOCKWISE_90,
		_CLOCKWISE_180,
		_CLOCKWISE_270,
	};

public:
	//!	Get the image width.
	//!	@param		none.
	//!	@return		The image width.
	virtual _dword GetWidth( ) const PURE;
	//!	Get the image height.
	//!	@param		none.
	//!	@return		The image height.
	virtual _dword GetHeight( ) const PURE;
	//!	Get the ratio.
	//!	@param		none.
	//!	@return		The ratio.
	virtual Ratio GetRatio( ) const PURE;
	//!	Get the image pitch.
	//!	@param		none.
	//!	@return		The image pitch.
	virtual _dword GetPitch( ) const PURE;
	//!	Get the image total pixel size.
	//!	@param		none.
	//!	@return		The image total pixel size in bytes.
	virtual _dword GetImageSize( ) const PURE;
	//!	Get the image pixel format.
	//!	@param		none.
	//!	@return		The image pixel format.
	virtual _PIXEL_FORMAT GetPixelFormat( ) const PURE;
	//!	Get pre-pixel size in bytes.
	//!	@param		none.
	//!	@return		The pre-pixel size in bytes.
	virtual _dword GetPixelBytes( ) const PURE;
	//!	Get the image pixel buffer.
	//!	@remark		It would decode the pixel buffer if needed.
	//!	@param		none.
	//!	@return		The image pixel buffer pointer.
	virtual const _byte* GetPixelBuffer( ) const PURE;

	//!	Check whether it's opaque image.
	//!	@remark		It means we will check alpha channel of it.
	//!	@param		alpha_range	The alpha range to check.
	//!	@return		True indicates it's opaque image.
	virtual _ubool IsOpaqueImage( const DwordRange& alpha_range ) const PURE;
	//!	Discard the alpha channel.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool DiscardAlphaChannel( ) PURE;

	//!	Get the The transparent layer (1 bit).
	//!	@remark		Only works for ARGB pixel format.
	//!	@param		layer		The transparent layer.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetTransparentLayer( OneBitArray& layer ) const PURE;

	//!	Update image.
	//!	@param		region		The image region.
	//!	@param		pixel		The buffer of pixel what would fill into pixel buffer of image.
	//!	@param		pixel_bytes	The bytes pre pixel.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool UpdatePixel( const RectI& region, const _byte* pixel, _dword pixel_bytes ) PURE;

	//!	Rotate in clockwise.
	//!	@param		flag		The clockwise flag.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Rotate( _CLOCKWISE_FLAG flag ) PURE;
	//!	Scale.
	//!	@param		filter		The filter type.
	//!	@param		width		The image width.
	//!	@param		height		The image height.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Scale( _IMAGE_FILTER filter, _dword width, _dword height ) PURE;

	//!	Create image.
	//!	@param		width		The image width.
	//!	@param		height		The image height.
	//!	@param		pixelformat	The image pixel format.
	//!	@param		pixelbuffer	The image pixel buffer.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) PURE;

	//!	Save sub-image as file.
	//!	@param		region		The sub region in pixel.
	//!	@param		filename	The image file name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SaveToFileBySubRegion( const RectU& region, WStringPtr filename ) const PURE;
};

}