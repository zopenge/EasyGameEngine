//! @file     IImageProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IImageProcessor
//----------------------------------------------------------------------------

class IImageProcessor : public IObject
{
public:
	//!	Check whether it's transparent pixel.
	//!	@param		x			The x position.
	//!	@param		y			The y position.
	//!	@param		params	The user defined params.	
	//!	@return		True indicates it's transparent, otherwise indicates opaque. 
	typedef _ubool (*OnIsTransparentPixel)( _int x, _int y, const QwordParameters2& params );

public:
	//!	Scale image file.
	//!	@param		filter_type			The filter type.
	//!	@param		scale_factor		The scale factor.
	//!	@param		image_file			The image file.
	//!	@return		The new image file.
	virtual IImageFilePassRef ScaleImage( _IMAGE_FILTER filter, const Vector2& scale_factor, IImageFile* image_file ) PURE;
	//!	Scale image.
	//!	@param		filter_type			The filter type.
	//!	@param		pixel_format		The pixel format.
	//!	@param		original_size		The original size.
	//!	@param		original_pitch		The original pitch in bytes.
	//!	@param		original_pixel		The original pixel buffer.
	//!	@param		scale_size			The scale size.
	//!	@param		scale_pixel			The scale pixel, remember call delete[] when it's no usage.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ScaleImage( _IMAGE_FILTER filter, _PIXEL_FORMAT pixel_format, const PointU& original_size, _dword original_pitch, const _void* original_pixel, const PointU& scale_size, _byte*& scale_pixel ) PURE;
	//!	Scale image edge.
	//!	@param		pixel_format		The pixel format.
	//!	@param		rect				The rect.
	//!	@param		pitch				The pitch in bytes.
	//!	@param		border_size			The border size.
	//!	@param		pixel_buffer		The pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddImageBorder( _PIXEL_FORMAT pixel_format, const RectI& rect, _dword pitch, const PointU& border_size, _byte* pixel_buffer ) PURE;
	
	//!	Gaussian-Blur.
	//!	@param		des_image			The target image.
	//!	@param		src_image			The source image.
	//!	@param		des_rect			The region of target image.
	//!	@param		src_rect			The region of source image.
	//!	@param		factor				The blur factor.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GaussianBlur( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float factor ) const PURE;
	//!	Alpha blending.
	//!	@param		des_image			The target image.
	//!	@param		src_image			The source image.
	//!	@param		des_rect			The region of target image.
	//!	@param		src_rect			The region of source image.
	//!	@param		alpha				The alpha blending factor [0.0, 1.0].
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AlphaBlending( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float alpha ) const PURE;
	//!	Draw.
	//!	@param		des_image			The target image.
	//!	@param		src_image			The source image.
	//!	@param		des_rect			The region of target image.
	//!	@param		src_rect			The region of source image.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Draw( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect ) const PURE;
	//!	FillColorInTransparentArea
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		format				The format of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool FillColorInTransparentArea( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword width, _dword height ) PURE;
	//!	Flip pixel buffer.
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Flip( _byte* pixel_buffer, _dword pitch, _dword height ) const PURE;
	//!	Swap red and blue channel.
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SwapRBChannel( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const PURE;
	//!	Swap red and blue channel with alpha.
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SwapRBChannelWithAlpha( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const PURE;
	//!	Test color conversion.
	//!	@param		format				The format of pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//!	@param		des_format			The target pixel format.
	//!	@param		des_pitch			The target pitch.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool TestColorConversion( _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch ) const PURE;
	//!	Process color conversion.
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		format				The format of pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//!	@param		des_format			The target pixel format.
	//!	@param		des_pitch			The target pitch.
	//!	@param		des_pixel_buffer	The target pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword des_pitch, _byte* des_pixel_buffer ) const PURE;
	//!	Process color conversion.
	//!	@param		pixel_buffer		The pixel buffer.
	//!	@param		format				The format of pixel buffer.
	//!	@param		pitch				The pitch of pixel buffer.
	//!	@param		width				The width of pixel buffer.
	//!	@param		height				The height of pixel buffer.
	//!	@param		des_format			The target pixel format.
	//!	@param		des_pitch			The target pitch.
	//!	@param		des_pixel_buffer	The target pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch, MemArrayPtr< _byte >& des_pixel_buffer ) const PURE;

	//!	Get the transparent layer.
	//!	@param		image_info			The image info.
	//!	@param		transparent_layer	The transparent layer ( 1 bit buffer, 0 indicates transparent, 1 indicates opaque ).
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetTransparentLayer( const BitmapInfoReadOnly& image_info, BitArray< 1 >& transparent_layer ) const PURE;
	//!	Get the minimal region for opaque testing.
	//!	@param		image_info			The image info.
	//!	@param		rect				The opaque region of image.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetOpaqueRegion( const BitmapInfoReadOnly& image_info, RectI& rect ) const PURE;
	//!	Get the minimal region for opaque testing.
	//!	@remark		Use the seed filling algorithm.
	//!	@param		size				The image size.
	//!	@param		position			The start position.
	//!	@param		rect				The opaque region of image.
	//!	@param		funcpointer			The transparent check function pointer.
	//!	@param		params			The user defined params.	
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetOpaqueRegion( const PointI& size, const PointI& position, RectI& rect, OnIsTransparentPixel funcpointer, const QwordParameters2& params ) const PURE;
};

}