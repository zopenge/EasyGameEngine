#pragma once

namespace EGE {

/// <summary>
/// The compressed texture file.
/// </summary>
class ICompressedTexFile : public IImageFile {
public:
	/// <summary>
	/// The texture data.
	/// </summary>
	struct TextureData {
		//!	The mipmaps number.
		_dword mMipmapsNumber;
		//!	The compressed internal format, when not equal to 0 then indicates it's compressed texture.
		_dword mCompressedInternalFormat;
		//!	The compressed pixel format
		PixelFormat mCompressedPixelFormat;
		//!	The uncompressed internal format
		_dword mUncompressedInternalFormat;
		//!	The data type
		_dword mDataType;

		TextureInfo() {
			mMipmapsNumber = 0;
			mCompressedInternalFormat = 0;
			mCompressedPixelFormat = _PF_UNKNOWN;
			mUncompressedInternalFormat = 0;
			mDataType = 0;
		}
	};

	/// <summary>
	/// The mipmaps data.
	/// </summary>
	struct MipmapsData {
		/// <summary>
		/// The width in pixel.
		/// </summary>
		_dword mWidth;
		/// <summary>
		/// The height in pixel.
		/// </summary>
		_dword mHeight;
		/// <summary>
		/// The image size in bytes.
		/// </summary>
		_dword mImageSize;
		/// <summary>
		/// The compressed pixel data.
		/// </summary>
		const _byte* mCompressedPixelData;
	};

public:
	//!	Get the texture info.
	//!	@param		none.
	//!	@return		The texture info.
	virtual const TextureData& GetTextureData() const PURE;

	//!	Get the mipmaps pixel buffer data.
	//!	@param		mip_index	The mipmaps index.
	//!	@param		data		The mipmaps data.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetMipmapsPixelBufferData(_dword mip_index, MipmapsData& data) const PURE;

	//!	Decode the image pixel.
	//!	@param		none.
	//!	@return		The image pixel buffer.
	virtual const _byte* DecodeImagePixel() PURE;
};

} // namespace EGE