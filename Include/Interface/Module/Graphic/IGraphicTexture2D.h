//! @file     IGraphicTexture2D.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicTexture2D
//----------------------------------------------------------------------------

class IGraphicTexture2D : public IObject
{
	RTTI_INTERFACE( IGraphicTexture2D )

public:
	//!	Check whether it's dynamic texture.
	//!	@param		none.
	//!	@return		True indicates it's dynamic texture.
	virtual _ubool IsDynamicTexture( ) const PURE;

	//!	Get the mipmaps.
	//!	@param		none.
	//!	@return		The mipmaps of texture.
	virtual _dword GetMipmaps( ) const PURE;
	//!	Get the size in bytes.
	//!	@param		none.
	//!	@return		The mipmaps of texture.
	virtual _dword GetSizeInBytes( ) const PURE;
	//!	Get the width.
	//!	@param		none.
	//!	@return		The width of texture in pixel.
	virtual _dword GetWidth( ) const PURE;
	//!	Get the height.
	//!	@param		none.
	//!	@return		The height of texture in pixel.
	virtual _dword GetHeight( ) const PURE;
	//!	Get the size.
	//!	@param		none.
	//!	@return		The size of texture in pixel.
	virtual const PointU& GetSize( ) const PURE;
	//!	Get each pixel size in bytes.
	//!	@param		none.
	//!	@return		The each pixel size in bytes.
	virtual _dword GetPixelSize( ) const PURE;
	//!	Get the pixel format.
	//!	@param		none.
	//!	@return		The pixel format of texture.
	virtual _PIXEL_FORMAT GetPixelFormat( ) const PURE;
	//!	Get the sampler state info.
	//!	@param		none.
	//!	@return		The sampler state of texture.
	virtual SamplerStateInitializerRHI GetSamplerStateInfo( ) const PURE;
	//!	Get the region in pixel.
	//!	@param		none.
	//!	@return		The region in pixel.
	virtual RectU GetRect( ) const PURE;
	//!	Get the transparent layer buffer.
	//!	@param		none.
	//!	@return		The transparent layer buffer.
	virtual const OneBitArray& GetTransparentLayer( ) const PURE;

	//!	Get the resource handle.
	//!	@param		none.
	//!	@return		The texture resource handle.
	virtual Texture2DRHI* GetResource( ) const PURE;
	//!	Set the resource handle.
	//!	@param		texture.
	//!	@return		none.
	virtual _void SetResource( Texture2DRHI* texture ) PURE;

	//!	Update the uv-coordinate.
	//!	@param		uv1			The uv1-coordinate.
	//!	@param		uv2			The uv2-coordinate.
	//!	@return		none.
	virtual _void SetUV( const Vector2& uv1, const Vector2& uv2 ) PURE;
	//!	Get the uv-coordinate.
	//!	@param		uv1			The uv1-coordinate.
	//!	@param		uv2			The uv2-coordinate.
	//!	@return		none.
	virtual _void GetUV( Vector2& uv1, Vector2& uv2 ) const PURE;

	//!	Fix the uv-coordinate.
	//!	@param		uv			The uv-coordinate.
	//!	@return		The fixed uv-coordinate.
	virtual Vector2 FixUV( const Vector2& uv ) const PURE;
	//!	Get the fixed uv-coordinate from pixel position.
	//!	@param		pos			The pixel position.
	//!	@return		The fixed uv-coordinate.
	virtual Vector2 FixUV( const PointU& pos ) const PURE;

	//!	Update the pixel buffer.
	//!	@param		rect		The rect of texture will be updated.
	//!	@param		buffer		The pixel buffer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool UpdatePixelBuffer( const RectU& rect, const _byte* buffer ) PURE;

	//!	Check whether it's transparent pixel.
	//!	@remark		You must create texture with _TCF_BUILD_TRANSPARENT_LAYER flag in order to use this interface.
	//!	@param		x			The x-coordinate of UV.
	//!	@param		y			The y-coordinate of UV.
	//!	@return		True indicates it's transparent pixel ( alpha == 0 ), otherwise indicates opaque pixel ( alpha != 0 ).
	virtual _ubool IsTransparentPixel( _dword x, _dword y ) const PURE;
	//!	Check whether has transparent layer.
	//!	@param		none.
	//!	@return		True indicates has transparent layer.
	virtual _ubool HasTransparentLayer( ) const PURE;
	//!	Set the transparent layer.
	//!	@remark		The width and height of pixel buffer must match to texture.
	//!	@param		width		The width of layer.
	//!	@param		height		The height of layer.
	//!	@param		layer		The transparent layer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetTransparentLayer( _dword width, _dword height, const OneBitArray& layer ) PURE;

	//!	Unload resource.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnloadResource( ) PURE;

	//!	Save to image file.
	//!	@param		fileformat		The file format.
	//!	@param		filename		The image file name.
	//!	@param		is_vert_flip	True indicates flip the vert.
	//!	@param		swap_r_and_b	True indicates swap red and blue channel.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) const PURE;
};

}