#pragma once

namespace EGE {

/// <summary>
/// The image file interface.
/// </summary>
class IImageFile : public ISerializable {
public:
	//!	Get the image width.
	//!	@param		none.
	//!	@return		The image width.
	virtual _dword GetWidth() const PURE;
	//!	Get the image height.
	//!	@param		none.
	//!	@return		The image height.
	virtual _dword GetHeight() const PURE;
	//!	Get the image pitch.
	//!	@param		none.
	//!	@return		The image pitch.
	virtual _dword GetPitch() const PURE;
	//!	Get the ratio.
	//!	@param		none.
	//!	@return		The ratio.
	virtual Ratio GetRatio() const PURE;

	//!	Get the image pixel format.
	//!	@param		none.
	//!	@return		The image pixel format.
	virtual PixelFormat GetPixelFormat() const PURE;
	//!	Get pixel size in bytes.
	//!	@param		none.
	//!	@return		The pixel size in bytes.
	virtual _dword GetPixelBytes() const PURE;
	//!	Get the image pixel buffer.
	//!	@remark		It would decode the pixel buffer if needed.
	//!	@param		none.
	//!	@return		The image pixel buffer pointer.
	virtual const _byte* GetPixelBuffer() PURE;
	//!	Get the sub-image pixel.
	//!	@param		region		The sub region in pixel.
	//!	@param		pixelBuffer	The pixel buffer of sub-image pixel.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetSubPixelBuffer(const RectU& region, _byte* pixelBuffer) PURE;

	//!	Get the The transparent layer (1 bit).
	//!	@remark		Only works for ARGB pixel format.
	//!	@param		layer		The transparent layer.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetTransparentLayer(OneBitArray& layer) const PURE;
};

} // namespace EGE