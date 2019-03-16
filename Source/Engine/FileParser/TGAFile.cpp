//! @file     TGAFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// TGAFile Implementation
//----------------------------------------------------------------------------

TGAFile::TGAFile( )
{
}

TGAFile::~TGAFile( )
{
	Unload( );
}

_ubool TGAFile::LoadUncompressedRGBImageData( IStreamReader* stream_reader )
{
	// Load the pixel buffer
	stream_reader->ReadBuffer( mImagePixelBuffer, GetImageSize( ) );

	// Flip the pixel buffer
	GetImageProcessor( )->Flip( mImagePixelBuffer, mImagePitch, mImageHeight );
   
	return _true;
}

_ubool TGAFile::LoadUncompressedBWImageData( IStreamReader* stream_reader )
{
	return _true;
}

_ubool TGAFile::LoadCompressedRGBImageData( IStreamReader* stream_reader )
{
	// Perform run-length decoding
	//while(bytePtr < pixel_data + tga_data.ImageSize)
	//{
	//	unsigned char nextByte = 0;
	//	if (fread(&nextByte, 1, sizeof(unsigned char), file) != 1)
	//	{
	//		delete[] pixel_data;
	//		return false;
	//	}

	//	if(nextByte > 127)
	//	{
	//		// Run of data
	//		nextByte -= 127;
	//		unsigned char repeatByte[4] = {0};
	//		if (fread(repeatByte, 1, sizeof(unsigned char) * tga_data.BytesPerPixel, file) != sizeof(unsigned char) * tga_data.BytesPerPixel)
	//		{
	//			delete[] pixel_data;
	//			return false;
	//		}

	//		// Decompress into buffer
	//		for(unsigned char i = 0; i < nextByte; ++i)
	//		{
	//			memcpy(bytePtr, repeatByte, sizeof(unsigned char) * tga_data.BytesPerPixel);
	//			bytePtr += sizeof(unsigned char) * tga_data.BytesPerPixel;
	//		}
	//	}
	//	else
	//	{
	//		// Raw data
	//		nextByte++;
	//		if (fread(bytePtr, 1, sizeof(unsigned char) * nextByte * tga_data.BytesPerPixel, file) != 
	//			sizeof(unsigned char) * nextByte * tga_data.BytesPerPixel)
	//		{
	//			delete[] pixel_data;
	//			return false;
	//		}

	//		bytePtr += sizeof(unsigned char) * nextByte * tga_data.BytesPerPixel;
	//	}
	//}

	return _true;
}

_FILE_FORMAT TGAFile::GetFileID( ) const
{
	return _FF_TGA;
}

_ubool TGAFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// The TGA file header format
	// http://paulbourke.net/dataformats/tga/
	_byte id_length = 0;			// size of ID field that follows 18 byte header (0 usually)
	_byte colour_map_type = 0;		// type of colour map 0=none, 1=has palette
	_byte data_type_code = 0;		// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	_word colour_map_origin = 0;	// first colour map entry in palette
	_word colour_map_length = 0;	// number of colours in palette
	_byte colour_map_depth = 0;		// number of bits per palette entry 15,16,24,32
	_word originX = 0;				// image x origin
	_word originY = 0;				// image y origin
	_word width = 0;				// image width in pixels
	_word height = 0;				// image height in pixels
	_byte bits_per_pixel = 0;		// image bits per pixel 8,16,24,32
	_byte image_descriptor = 0;		// image descriptor bits (vh flip bits)

	// Read TGA file header
	stream_reader->ReadByte( id_length );
	stream_reader->ReadByte( colour_map_type );
	stream_reader->ReadByte( data_type_code );
	stream_reader->ReadWord( colour_map_origin );
	stream_reader->ReadWord( colour_map_length );
	stream_reader->ReadByte( colour_map_depth );
	stream_reader->ReadWord( originX );
	stream_reader->ReadWord( originY );
	stream_reader->ReadWord( width );
	stream_reader->ReadWord( height );
	stream_reader->ReadByte( bits_per_pixel );
	stream_reader->ReadByte( image_descriptor );

	// Check the TGA header info
	if ( width == 0 || height == 0 || ( bits_per_pixel != 24 && bits_per_pixel != 32 ) )
		return _false;

	// Initialize image size
	mImageWidth			= width;
	mImageHeight		= height;
	mImagePixelFormat	= bits_per_pixel == 24 ? _PF_R8G8B8 : _PF_A8R8G8B8;
	mImagePitch			= GetPixelBytes( ) * mImageWidth;

	// Load image info
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		// Skip the extra image buffer data
		stream_reader->Seek( _SEEK_CURRENT, id_length );

		// Create pixel buffer
		mImagePixelBuffer = new _byte[ GetImageSize( ) ];

		// Decode image data info
		switch ( data_type_code )
		{
			case _DTC_UNCOMPRESSED_RGB_IMAGE_DATA:
				return LoadUncompressedRGBImageData( stream_reader );

			case _DTC_UNCOMPRESSED_BW_IMAGE_DATA:
				return LoadUncompressedBWImageData( stream_reader );

			case _DTC_RUNLENGTH_ENCODED_RGB_IMAGE_DATA:
				return LoadCompressedRGBImageData( stream_reader );
				
			default:
				WLOG_ERROR_1( L"TGA image file is not support for '%d' data type", data_type_code );
				return _false;
		}
	}

	return _true;
}

_void TGAFile::Unload( )
{
	BaseClass::Unload( );
}
