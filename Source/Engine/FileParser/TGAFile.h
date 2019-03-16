//! @file     TGAFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGAFile
//----------------------------------------------------------------------------

class TGAFile : public INTERFACE_IMAGEFILE_IMPL( ITGAFile )
{
private:
	typedef INTERFACE_IMAGEFILE_IMPL( ITGAFile ) BaseClass;

private:
	//!	The data type code ID
	enum _DATA_TYPE_CODE
	{
		_DTC_NO_IMAGE_DATA									= 0, // No image data included.
		_DTC_UNCOMPRESSED_COLOR_MAPPED_IMAGE_DATA			= 1, // Uncompressed, color-mapped images.
		_DTC_UNCOMPRESSED_RGB_IMAGE_DATA					= 2, // Uncompressed, RGB images.
		_DTC_UNCOMPRESSED_BW_IMAGE_DATA						= 3, // Uncompressed, black and white images.
		_DTC_RUNLENGTH_ENCODED_COLOR_MAPPED_IMAGE_DATA		= 9, // Runlength encoded color-mapped images.
		_DTC_RUNLENGTH_ENCODED_RGB_IMAGE_DATA				= 10, // Runlength encoded RGB images.
		_DTC_COMPRESSED_BW_IMAGE_DATA						= 11, // Compressed, black and white images.
		_DTC_COMPRESSED_COLOR_MAPPED_IMAGE_DATA				= 32, // Compressed color-mapped data, using Huffman, Delta, and runlength encoding.
		_DTC_COMPRESSED_COLOR_MAPPED_WITH_4_PASS_IMAGE_DATA	= 33, // Compressed color-mapped data, using Huffman, Delta, and runlength encoding ( 4-pass quadtree-type process ).
	};

private:
	//!	Load uncompressed RGB image data.
	_ubool LoadUncompressedRGBImageData( IStreamReader* stream_reader );
	//!	Load uncompressed black and white image data.
	_ubool LoadUncompressedBWImageData( IStreamReader* stream_reader );
	//!	Load compressed RGB image data.
	_ubool LoadCompressedRGBImageData( IStreamReader* stream_reader );

public:
	TGAFile( );
	virtual ~TGAFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:

// ITGAFile Interface
public:
};

}