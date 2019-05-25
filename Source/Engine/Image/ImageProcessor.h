//! @file     ImageProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ImageProcessor
//----------------------------------------------------------------------------

class ImageProcessor : public TObject< IImageProcessor >
{
private:
	static _word R5G6B5( _byte /*a*/, _byte r, _byte g, _byte b ) { return EGE_R5G6B5( r, g, b ); }
	static _word R5G5B5A1( _byte a, _byte r, _byte g, _byte b ) { return EGE_R5G5B5A1( a, r, g, b ); }
	static _word R4G4B4A4( _byte a, _byte r, _byte g, _byte b ) { return EGE_R4G4B4A4( a, r, g, b ); }
	static _word A8G8( _byte a, _byte r, _byte g, _byte b ) { return EGE_A8G8( a, r, g, b ); }
	typedef _word (*OnBuildPixel)( _byte a, _byte r, _byte g, _byte b );

	//!	ARGB Color conversion.
	template< typename DesPixelType, OnBuildPixel _BUILD_PIXEL_FUNC >
	static _ubool ARGBConversion( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, _dword des_pitch, _byte* des_pixel_buffer );

	//!	RGB Color conversion.
	template< typename DesPixelType, OnBuildPixel _BUILD_PIXEL_FUNC >
	static _ubool RGBConversion( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, _dword des_pitch, _byte* des_pixel_buffer );

public:
	ImageProcessor( );
	virtual ~ImageProcessor( );

// IImageProcessor Interface
public:
	virtual IImageFilePassRef	ScaleImage( _IMAGE_FILTER filter, const Vector2& scale_factor, IImageFile* image_file ) override;
	virtual _ubool				ScaleImage( _IMAGE_FILTER filter, _PIXEL_FORMAT pixel_format, const PointU& original_size, _dword original_pitch, const _void* original_pixel, const PointU& scale_size, _byte*& scale_pixel ) override;
	virtual _ubool				AddImageBorder( _PIXEL_FORMAT pixel_format, const RectI& rect, _dword pitch, const PointU& border_size, _byte* pixel_buffer ) override;

	virtual _ubool				GaussianBlur( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float factor ) const override;
	virtual _ubool				AlphaBlending( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float alpha ) const override;
	virtual _ubool				Draw( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect ) const override;

	virtual _ubool				FillColorInTransparentArea( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword width, _dword height ) override;
	virtual _ubool				Flip( _byte* pixel_buffer, _dword pitch, _dword height ) const override;
	virtual _ubool				SwapRBChannel( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const override;
	virtual _ubool				SwapRBChannelWithAlpha( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const override;
	virtual _ubool				TestColorConversion( _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch ) const override;
	virtual _ubool				ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword des_pitch, _byte* des_pixel_buffer ) const override;
	virtual _ubool				ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch, MemArrayPtr< _byte >& des_pixel_buffer ) const override;

	virtual _ubool				GetTransparentLayer( const BitmapInfoReadOnly& image_info, BitArray< 1 >& transparent_layer ) const override;
	virtual _ubool				GetOpaqueRegion( const BitmapInfoReadOnly& image_info, RectI& rect ) const override;
	virtual _ubool				GetOpaqueRegion( const PointI& size, const PointI& position, RectI& rect, OnIsTransparentPixel funcpointer, const QwordParameters2& params ) const override;
};

//----------------------------------------------------------------------------
// ImageProcessor Implementation
//----------------------------------------------------------------------------

template< typename DesPixelType, ImageProcessor::OnBuildPixel _BUILD_PIXEL_FUNC >
_ubool ImageProcessor::ARGBConversion( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, _dword des_pitch, _byte* des_pixel_buffer )
{
	EGE_ASSERT( des_pixel_buffer != _null );

	for ( _dword y = 0; y < height; y ++ )
	{
		_dword offset_y = y * pitch;

		for ( _dword x = 0; x < width; x ++ )
		{
			_dword offset = offset_y + x * 4;

			_byte a = pixel_buffer[offset + 3];
			_byte r = pixel_buffer[offset + 2];
			_byte g = pixel_buffer[offset + 1];
			_byte b = pixel_buffer[offset + 0];

			DesPixelType* target_pixel_buffer = (DesPixelType*) (des_pixel_buffer + y * des_pitch + x * sizeof( DesPixelType ));
			*target_pixel_buffer = _BUILD_PIXEL_FUNC( a, r, g, b );
		}
	}

	return _true;
}

template< typename DesPixelType, ImageProcessor::OnBuildPixel _BUILD_PIXEL_FUNC >
_ubool ImageProcessor::RGBConversion( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, _dword des_pitch, _byte* des_pixel_buffer )
{
	EGE_ASSERT( des_pixel_buffer != _null );

	for ( _dword y = 0; y < height; y ++ )
	{
		_dword offset_y = y * pitch;

		for ( _dword x = 0; x < width; x ++ )
		{
			_dword offset = offset_y + x * 3;

			_byte r = pixel_buffer[offset + 2];
			_byte g = pixel_buffer[offset + 1];
			_byte b = pixel_buffer[offset + 0];

			DesPixelType* target_pixel_buffer = (DesPixelType*) (des_pixel_buffer + y * des_pitch + x * sizeof( DesPixelType ));
			*target_pixel_buffer = _BUILD_PIXEL_FUNC( 255, r, g, b );
		}
	}

	return _true;
}

}