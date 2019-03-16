//! @file     PNGFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PNGFile Implementation
//----------------------------------------------------------------------------

PNGFile::PNGFile( )
{
	mBitDepth			= 0;
	mColorType			= 0;

	mBackgroundColor	= Color::cNull;
}

PNGFile::~PNGFile( )
{
	Unload( );
}

_void PNGFile::OnErrorHandler( _handle pngstruct, const char* error )
{
}

_void PNGFile::OnWarningHandler( _handle pngstruct, const char* warning )
{
}

_void PNGFile::OnReadProc( _handle pngstruct, unsigned char* buffer, size_t size )
{
	IStreamReader* stream_reader = (IStreamReader*) ::png_get_io_ptr( (png_structp) pngstruct );
	EGE_ASSERT( stream_reader != _null );

	stream_reader->ReadBuffer( buffer, (_dword)size );
}

_void PNGFile::OnWriteProc( _handle pngstruct, unsigned char* buffer, size_t size )
{
	IStreamWriter* stream_writer = (IStreamWriter*) ::png_get_io_ptr( (png_structp) pngstruct );
	EGE_ASSERT( stream_writer != _null );

	stream_writer->WriteBuffer( buffer, (_dword)size );
}

_void PNGFile::OnFlushProc( _handle pngstruct )
{

}

_ubool PNGFile::LoadImage( _handle pngstruct, _handle pnginfo, IStreamReader* stream_reader )
{
	png_structp png_struct	= (png_structp) pngstruct;
	png_infop	png_info	= (png_infop) pnginfo;

	// Set the error long jump here
	if ( ::setjmp( png_jmpbuf( png_struct ) ) )
		return _false;

	// Initialize the IO
	::png_set_read_fn( png_struct, stream_reader, (png_rw_ptr) OnReadProc );

	// We will skip the signature because we have already read it
	::png_set_sig_bytes( png_struct, 8 );

	// Read the IHDR chunk
	::png_read_info( png_struct, png_info );
	::png_get_IHDR( png_struct, png_info, (png_uint_32*) &mImageWidth, (png_uint_32*) &mImageHeight, &mBitDepth, &mColorType, _null, _null, _null );

	// Get the transparent alpha info
	png_bytep trans_alpha = _null;
	::png_get_tRNS( png_struct, png_info, &trans_alpha, _null, _null );

	// Expand palette colors into true rgb
	if ( mColorType & PNG_COLOR_MASK_PALETTE )
		::png_set_palette_to_rgb( png_struct );

	// Check the channels ( we only support the Palette(8 bits)/RGB/ARGB color mode )
	_dword channels			= ::png_get_channels( png_struct, png_info );
	_dword fixed_channels	= channels;

	// Fix the channels and set image pixel format
	switch ( channels )
	{
		// Palette
		case 1:
		{
			if ( trans_alpha != _null )
			{
				// Palette has alpha layer
				fixed_channels		= 4; 
				mImagePixelFormat	= _PF_A8R8G8B8;
			}
			else
			{
				// Palette has not alpha layer
				fixed_channels		= 3; 
				mImagePixelFormat	= _PF_R8G8B8;
			}
		}
		break;

		// Gray-Alpha
		case 2:
		{
			fixed_channels		= 4;
			mImagePixelFormat	= _PF_A8R8G8B8;
		}
		break;

		// RGB
		case 3:
		{
			mImagePixelFormat = _PF_R8G8B8;
		}
		break;

		// ARGB
		case 4:
		{
			mImagePixelFormat = _PF_A8R8G8B8;
		}
		break;

		default:
			WLOG_ERROR_1( L"Decode PNG file failed on unsupported '%d' channel", channels );
			return _false;
	}

	// Set the image pitch
	mImagePitch = Math::UpperArrange( mImageWidth * fixed_channels, fixed_channels );

	// Decode the image pixel
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		// Read the background color
		png_color_16p backgroundcolor = _null;
		if ( ::png_get_bKGD( png_struct, png_info, &backgroundcolor ) )
			mBackgroundColor = Color( (_byte) backgroundcolor->red, (_byte) backgroundcolor->green, (_byte) backgroundcolor->blue, 255 );

		// Create pixel buffer
		mImagePixelBuffer = new _byte[ mImagePitch * mImageHeight ];

		// It's Gray-Alpha color mode
		if ( channels == 2 )
		{
			// Get the row bytes
			_dword row_bytes = (_dword)::png_get_rowbytes( png_struct, png_info );
			if ( row_bytes == 0 )
				return _false;

			// Create pixel buffer
			MemArrayPtr< _byte > tmp_pixel_buffer( row_bytes * mImageHeight );
			MemArrayPtr< png_bytep > rowpointers( mImageHeight );
			for ( _dword i = 0; i < mImageHeight; i ++ )
				rowpointers[i] = tmp_pixel_buffer.GetPointer( ) + row_bytes * i;

			// Read image buffer
			::png_read_image( png_struct, rowpointers );

			// Convert Gray-Alpha to ARGB
			for ( _dword y = 0; y < mImageHeight; y ++ )
			{
				_byte*			to_pixel_buffer		= mImagePixelBuffer + ( y * mImagePitch );
				const _byte*	from_pixel_buffer	= tmp_pixel_buffer.GetPointer( ) + ( y * row_bytes );

				for ( _dword x = 0; x < mImageWidth; x ++ )
				{
					to_pixel_buffer[ x * 4 + 3 ] = from_pixel_buffer[ x * 2 + 1 ];
					to_pixel_buffer[ x * 4 + 2 ] = from_pixel_buffer[ x * 2 + 0 ];
					to_pixel_buffer[ x * 4 + 1 ] = from_pixel_buffer[ x * 2 + 0 ];
					to_pixel_buffer[ x * 4 + 0 ] = from_pixel_buffer[ x * 2 + 0 ];
				}
			}
		}
		// Other color mode
		else
		{
			// Locate scan line pointer
			MemArrayPtr< png_bytep > rowpointers( mImageHeight );
			for ( _dword i = 0; i < mImageHeight; i ++ )
				rowpointers[i] = mImagePixelBuffer + mImagePitch * i;

			// Read image buffer
			::png_read_image( png_struct, rowpointers );
		}

		// fill the color in the transparent area
		if ( GetImageProcessor( )->FillColorInTransparentArea( mImagePixelBuffer, mImagePixelFormat, mImageWidth, mImageHeight ) == _false )
			return _false;

		// Process color conversion
		if ( OnProcessColorConversion( ) == _false )
			return _false;

		// End to read
		::png_read_end( png_struct, png_info );
	}

	return _true;
}

_ubool PNGFile::SaveImage( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const
{
	if ( stream_writer == _null )
		return _false;

	// Create the chunk manage structure
	png_structp png_struct = ::png_create_read_struct( PNG_LIBPNG_VER_STRING, _null, (png_error_ptr) OnErrorHandler, (png_error_ptr) OnWarningHandler );
	if ( png_struct == _null )
		return _false;

	// Clear the default read produce
	png_struct->read_data_fn = _null;

	// Create the info structure
	png_infop png_info = ::png_create_info_struct( png_struct );
	if ( png_info == _null )
	{
		::png_destroy_read_struct( &png_struct, _null, _null );
		return _false;
	}

	// Set the error long jump here
	if ( ::setjmp( png_jmpbuf( png_struct ) ) )
	{
		::png_destroy_read_struct( &png_struct, &png_info, _null );
		return _false;
	}

	// Initialize the IO
	::png_set_write_fn( png_struct, stream_writer, (png_rw_ptr) OnWriteProc, (png_flush_ptr) OnFlushProc );

	/* Set the library compression level.  Currently, valid values range from
	 * 0 - 9, corresponding directly to the zlib compression levels 0 - 9
	 * (0 - no compression, 9 - "maximal" compression).  Note that tests have
	 * shown that zlib compression levels 3-6 usually perform as well as level 9
	 * for PNG images, and do considerably fewer caclulations.  In the future,
	 * these values may not correspond directly to the zlib compression levels.
	 */
	::png_set_compression_level( png_struct, 3 );

	// Get the color type
	_dword colortype = 0;
	if ( mImagePixelFormat == _PF_R8G8B8 )
		colortype = PNG_COLOR_TYPE_RGB;
	else
		colortype = PNG_COLOR_TYPE_RGBA;

	// Set the IHDR chunk
	::png_set_IHDR( png_struct, png_info, (png_uint_32)width, (png_uint_32)height, 8, (int)colortype, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE );

	// Set the background color
	if ( mBackgroundColor != Color::cNull )
	{
		png_color_16 backgroundcolor;
		backgroundcolor.blue  = (png_uint_16) ( mBackgroundColor.b * 255.0f );
		backgroundcolor.green = (png_uint_16) ( mBackgroundColor.g * 255.0f );
		backgroundcolor.red   = (png_uint_16) ( mBackgroundColor.r * 255.0f );
		backgroundcolor.index = 0;

		::png_set_bKGD( png_struct, png_info, &backgroundcolor );
	}

	// Write the file header information.
	::png_write_info( png_struct, png_info );

	// Write pixel buffer
	for ( _dword i = 0; i < height; i ++ )
		::png_write_row( png_struct, (png_bytep) ( pixel_buffer + i * pitch ) );

	// Finish writing the rest of the file
	::png_write_end( png_struct, png_info );

	// Destroy png struct and info
	::png_destroy_write_struct( &png_struct, &png_info );

	return _true;
}

_ubool PNGFile::OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const
{
	if ( SaveImage( pixel_buffer, pitch, width, height, stream_writer ) == _false )
		return _false;

	return _true;
}

_FILE_FORMAT PNGFile::GetFileID( ) const
{
	return _FF_PNG;
}

_ubool PNGFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Read the signature
	_byte signature[8];
	stream_reader->ReadBuffer( signature, 8 );

	// Check the signature
	if ( ::png_sig_cmp( signature, 0, 8 ) != 0 )
		return _false;

	// Create the chunk manage structure
	png_structp pngstruct = ::png_create_read_struct( PNG_LIBPNG_VER_STRING, _null, _null, _null );
	if ( pngstruct == _null )
		return _false;

	// Create the info structure
	png_infop pnginfo = ::png_create_info_struct( pngstruct );
	if ( pnginfo == _null )
	{
		::png_destroy_read_struct( &pngstruct, _null, _null );
		return _false;
	}

	// Load image
	_ubool ret = LoadImage( pngstruct, pnginfo, stream_reader );

	// Destroy png struct and info
	::png_destroy_read_struct( &pngstruct, &pnginfo, _null );

	return ret;
}

_void PNGFile::Unload( )
{
	BaseClass::Unload( );
}

_ubool PNGFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	if ( SaveImage( mImagePixelBuffer, mImagePitch, mImageWidth, mImageHeight, stream_writer ) == _false )
		return _false;

	return _true;
}

_ubool PNGFile::Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer )
{
	if ( width == 0 || height == 0 )
		return _false;

	// We only support the RGB/RGBA mode
	if ( pixelformat != _PF_R8G8B8 && pixelformat != _PF_A8R8G8B8 )
		return _false;

	Unload( );

	// Initialize image info
	mImageWidth			= width;
	mImageHeight		= height;
	mImagePitch			= pixelformat == _PF_A8R8G8B8 ? width * 4 : width * 3;
	mImagePixelFormat	= pixelformat;
	mImagePixelBuffer	= new _byte[ mImagePitch * mImageHeight ];

	if ( pixelbuffer != _null )
		EGE_MEM_CPY( mImagePixelBuffer, pixelbuffer, mImagePitch * mImageHeight );

	return _true;
}

const Color& PNGFile::GetBackgroundColor( ) const
{
	return mBackgroundColor;
}