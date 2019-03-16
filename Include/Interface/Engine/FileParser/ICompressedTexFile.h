//! @file     ICompressedTexFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICompressedTexFile
//----------------------------------------------------------------------------

class ICompressedTexFile : public IImageFile
{
public:
	//!	The texture info
	struct TextureInfo
	{
		//!	The mipmaps number.
		_dword			mMipmapsNumber;
		//!	The compressed internal format, when not equal to 0 then indicates it's compressed texture.
		_dword			mCompressedInternalFormat;
		//!	The uncompressed internal format
		_dword			mUncompressedInternalFormat;
		//!	The data type
		_dword			mDataType;

		//!	The compressed pixel format
		_PIXEL_FORMAT	mCompressedPixelFormat;

		TextureInfo( )
		{
			mMipmapsNumber				= 0;
			mCompressedInternalFormat	= 0;
			mUncompressedInternalFormat	= 0;
			mDataType					= 0;

			mCompressedPixelFormat		= _PF_UNKNOWN;
		}
	};

public:
	//!	Get the texture info.
	//!	@param		none.
	//!	@return		The texture info.
	virtual const TextureInfo& GetTextureInfo( ) const PURE;

	//!	Get the mipmaps pixel buffer data.
	//!	@param		mip_index	The mipmaps index.
	//!	@param		width		The width in pixel.
	//!	@param		height		The height in pixel.
	//!	@param		image_size	The image size in bytes.
	//!	@return		The compressed buffer data.
	virtual const _byte* GetMipmapsPixelBufferData( _dword mip_index, _dword* width, _dword* height, _dword* image_size ) const PURE;

	//!	Decode the image pixel.
	//!	@param		none.
	//!	@return		The image pixel buffer.
	virtual const _byte* DecodeImagePixel( ) PURE;
};

}