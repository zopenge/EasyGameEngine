//! @file     GIFFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// GIFFile Implementation
//----------------------------------------------------------------------------

GIFFile::GIFFile( )
{
}

GIFFile::~GIFFile( )
{
	Unload( );
}

int GIFFile::OnReadFunction( GifFileType* gif_file, GifByteType* buffer, int size )
{
	DecodeInfo* decode_info = (DecodeInfo*) gif_file->UserData;
	EGE_ASSERT( decode_info != _null );

	return decode_info->mStreamReader->ReadBuffer( buffer, size );
}

_ubool GIFFile::DecodeImage( GifFileType* gif_file )
{
	// We only decode the first image
	if ( gif_file->ImageCount == 0 )
		return _false;

	const SavedImage&	image		= gif_file->SavedImages[0];
	const GifImageDesc& image_desc	= image.ImageDesc;

	mImageWidth			= image_desc.Width;
	mImageHeight		= image_desc.Height;
	mImagePitch			= mImageWidth * sizeof( _dword );
	mImagePixelFormat	= _PF_A8R8G8B8;

	// Check whether decode pixel buffer
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		mImagePixelBuffer = new _byte[ mImagePitch * mImageHeight ];

		const _byte* raster_buf = image.RasterBits;

		for ( _dword y = 0; y < mImageHeight; y ++ )
		{
			_byte* pixel_buffer = mImagePixelBuffer + y * mImagePitch;

			for ( _dword x = 0; x < mImageWidth; x ++, pixel_buffer += 4 ) 
			{
				const GifColorType& color_obj = gif_file->SColorMap->Colors[ *raster_buf ++ ];

				pixel_buffer[0] = color_obj.Red;
				pixel_buffer[1] = color_obj.Green;
				pixel_buffer[2] = color_obj.Blue;
				pixel_buffer[3] = 0xFF;
			}
		}
	}


	return _true;
}

_FILE_FORMAT GIFFile::GetFileID( ) const
{
	return _FF_GIF;
}

_ubool GIFFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Initialize decode info
	DecodeInfo decode_info;
	decode_info.mGifFile		= this;
	decode_info.mStreamReader	= stream_reader;

	// Open GIF file to decode
	GifFileType* gif_file = DGifOpen( &decode_info, OnReadFunction, _null );
	if ( gif_file == _null )
		return _false;

	// Decode GIF
	if ( DGifSlurp( gif_file ) == _false )
	{
		DGifCloseFile( gif_file, _null );
		return _false;
	}

	// Decode image
	if ( DecodeImage( gif_file ) == _false )
	{
		DGifCloseFile( gif_file, _null );
		return _false;
	}

	// Close GIF file
	DGifCloseFile( gif_file, _null );

	return _true;
}

_void GIFFile::Unload( )
{
	BaseClass::Unload( );
}