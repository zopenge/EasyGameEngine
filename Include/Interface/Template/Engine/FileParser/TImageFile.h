//! @file     TImageFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TImageFile
//----------------------------------------------------------------------------

template< typename Type >
class TImageFile : public Type
{
protected:
	//!	The image width
	_dword			mImageWidth;
	//!	The image height
	_dword			mImageHeight;
	//!	The image pitch of line
	_dword			mImagePitch;
	//!	The image pixel format
	_PIXEL_FORMAT	mImagePixelFormat;
	//!	The image pixel buffer
	_byte*			mImagePixelBuffer;

protected:
	//!	When process color conversion.
	virtual _ubool OnProcessColorConversion( );
	//!	When save to file.
	virtual _ubool OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const { return _false; }

protected:
	TImageFile( );
	virtual ~TImageFile( );

// IBaseFile Interface
public:
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:
	virtual _dword 			GetWidth( ) const override;
	virtual _dword 			GetHeight( ) const override;
	virtual Ratio			GetRatio( ) const override;
	virtual _dword 			GetPitch( ) const override;
	virtual _dword			GetImageSize( ) const override;
	virtual _PIXEL_FORMAT 	GetPixelFormat( ) const override;
	virtual _dword			GetPixelBytes( ) const override;
	virtual const _byte*	GetPixelBuffer( ) const override;

	virtual _ubool			IsOpaqueImage( const DwordRange& alpha_range ) const override;
	virtual _ubool			DiscardAlphaChannel( ) override;

	virtual _ubool			GetTransparentLayer( OneBitArray& layer ) const override;

	virtual _ubool			UpdatePixel( const RectI& region, const _byte* pixel, _dword pixel_bytes ) override;

	virtual _ubool			Rotate( IImageFile::_CLOCKWISE_FLAG flag ) override;
	virtual _ubool			Scale( _IMAGE_FILTER filter, _dword width, _dword height ) override;

	virtual _ubool			Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) override;

	virtual _ubool			SaveToFileBySubRegion( const RectU& region, WStringPtr filename ) const override;
};

//----------------------------------------------------------------------------
// TImageFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TImageFile< Type >::TImageFile( )
{
	mImageWidth			= 0;
	mImageHeight		= 0;
	mImagePitch			= 0;
	mImagePixelFormat	= _PF_UNKNOWN;
	mImagePixelBuffer	= _null;
}

template< typename Type >
TImageFile< Type >::~TImageFile( )
{
	// The image pixel buffer must be freed in Unload( ) function
	EGE_ASSERT( mImagePixelBuffer == _null );
}

template< typename Type >
_ubool TImageFile< Type >::OnProcessColorConversion( )
{
	// Get the target pixel format
	_PIXEL_FORMAT des_pixel_format = _PF_UNKNOWN;
	if ( this->HasFlags( IImageFile::_FLAG_DECODE_AS_R5G5B5A1 ) )
		des_pixel_format = _PF_R5G5B5A1;
	else if ( this->HasFlags( IImageFile::_FLAG_DECODE_AS_R4G4B4A4 ) )
		des_pixel_format = _PF_R4G4B4A4;
	else if ( this->HasFlags( IImageFile::_FLAG_DECODE_AS_R5G6B5 ) )
		des_pixel_format = _PF_R5G6B5;
	else if ( this->HasFlags( IImageFile::_FLAG_DECODE_AS_A8G8 ) )
		des_pixel_format = _PF_A8G8;

	// Convert color
	if ( des_pixel_format != _PF_UNKNOWN )
	{
		_dword des_pitch = 0; MemArrayPtr< _byte > des_pixel_buffer;
		if ( GetImageProcessor( )->ProcessColorConversion( mImagePixelBuffer, mImagePixelFormat, mImagePitch, mImageWidth, mImageHeight, des_pixel_format, des_pitch, des_pixel_buffer ) == _false )
			return _false;

		// Delete the previous pixel buffer and save the new one
		EGE_DELETE_ARRAY( mImagePixelBuffer );
		des_pixel_buffer.EnableAutoDelete( _false );

		// Update image info
		mImagePitch			= des_pitch;
		mImagePixelFormat	= des_pixel_format;
		mImagePixelBuffer	= des_pixel_buffer;
	}

	return _true;
}

template< typename Type >
_void TImageFile< Type >::Unload( )
{
	EGE_DELETE_ARRAY( mImagePixelBuffer );
}

template< typename Type >
_dword TImageFile< Type >::GetWidth( ) const
{
	return mImageWidth;
}

template< typename Type >
_dword TImageFile< Type >::GetHeight( ) const
{
	return mImageHeight;
}

template< typename Type >
Ratio TImageFile< Type >::GetRatio( ) const
{
	return Ratio( mImageWidth, mImageHeight );
}

template< typename Type >
_dword TImageFile< Type >::GetPitch( ) const
{
	return mImagePitch;
}

template< typename Type >
_dword TImageFile< Type >::GetImageSize( ) const
{
	return mImagePitch * mImageHeight;
}

template< typename Type >
_PIXEL_FORMAT TImageFile< Type >::GetPixelFormat( ) const
{
	return mImagePixelFormat;
}

template< typename Type >
_dword TImageFile< Type >::GetPixelBytes( ) const
{
	switch ( mImagePixelFormat )
	{
		case _PF_R8G8B8:	return 3;
		case _PF_A8R8G8B8:	return 4;
		case _PF_G8:		return 1;
		case _PF_A8:		return 1;
		default:
			return 0;
	}
}

template< typename Type >
const _byte* TImageFile< Type >::GetPixelBuffer( ) const
{
	return mImagePixelBuffer;
}

template< typename Type >
_ubool TImageFile< Type >::IsOpaqueImage( const DwordRange& alpha_range ) const
{
	switch ( mImagePixelFormat )
	{
		case _PF_A8R8G8B8:
		{
			for ( _dword y = 0; y < mImageHeight; y ++ )
			{
				for ( _dword x = 0; x < mImageWidth; x ++ )
				{
					const _byte* color = &mImagePixelBuffer[ y * mImagePitch + x * 4 ];
					if  ( alpha_range.IsIn( color[3] ) == _false )
						return _false;
				}
			}
		}
		break;

		default:
			break;
	}

	return _true;
}

template< typename Type >
_ubool TImageFile< Type >::DiscardAlphaChannel( )
{
	switch ( mImagePixelFormat )
	{
		case _PF_A8R8G8B8:
		{
			_dword old_pitch		= mImagePitch;
			_byte* old_pixel_buffer	= mImagePixelBuffer;

			mImagePixelFormat	= _PF_R8G8B8;
			mImagePitch			= 3 * mImageWidth;
			mImagePixelBuffer	= new _byte[ mImagePitch * mImageHeight ];
			EGE_MEM_SET( mImagePixelBuffer, 0, mImagePitch * mImageHeight );

			for ( _dword y = 0; y < mImageHeight; y ++ )
			{
				for ( _dword x = 0; x < mImageWidth; x ++ )
				{
					_byte*			to_color	= &mImagePixelBuffer[ y * mImagePitch + x * 3 ];
					const _byte*	from_color	= &old_pixel_buffer[ y * old_pitch + x * 4 ];

					to_color[0] = from_color[0];
					to_color[1] = from_color[1];
					to_color[2] = from_color[2];
				}
			}

			EGE_DELETE( old_pixel_buffer );
		}
		break;

		default:
			break;
	}

	return _true;
}

template< typename Type >
_ubool TImageFile< Type >::GetTransparentLayer( OneBitArray& layer ) const
{
	// The pixel buffer must be provided
	const _byte* pixel_buffer = GetPixelBuffer( );
	if ( pixel_buffer == _null )
		return _false;

	// We must have the alpha component
	if ( mImagePixelFormat != _PF_A8R8G8B8 )
		return _false;

	// Create transparent layer buffer
	layer.Create( GetWidth( ) * GetHeight( ) );

	// Get the transparent from pixel buffer
	BitmapInfoReadOnly bitmap_info( mImagePixelFormat, 4, mImagePitch, mImageWidth, mImageHeight, pixel_buffer );
	if ( GetImageProcessor( )->GetTransparentLayer( bitmap_info, layer ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TImageFile< Type >::UpdatePixel( const RectI& region, const _byte* pixel, _dword pixel_bytes )
{
	if ( pixel == _null || pixel_bytes == _null )
		return _false;

	if ( mImagePixelBuffer == _null )
		return _false;

	// Intersect the sub-region with image region
	RectI sub_region = RectI::Intersect( region, RectI( ).InitWithSize( 0, 0, (_int)mImageWidth, (_int)mImageHeight ) );

	// Fill pixel buffer
	for ( _int y = sub_region.t; y < sub_region.b; y ++ )
	{
		_byte* des_buffer = mImagePixelBuffer + ( y * mImagePitch ) + sub_region.l * GetPixelBytes( );
		const _byte* src_buffer = pixel + ( y * pixel_bytes );

		EGE_MEM_CPY( des_buffer, src_buffer, sub_region.GetWidth( ) * pixel_bytes );
	}

	return _true;
}

template< typename Type >
_ubool TImageFile< Type >::Rotate( IImageFile::_CLOCKWISE_FLAG flag )
{
	// Backup the old info
	_dword pitch			= mImagePitch;
	_dword height			= mImageHeight;
	_dword component_size	= mImagePitch / mImageWidth;
	_dword size				= pitch * mImageHeight;
	
	switch ( flag )
	{
		case IImageFile::_CLOCKWISE_90:
		{
			// Update info
			Math::Swap( mImageWidth, mImageHeight );
			mImagePitch = component_size * mImageWidth;

			// Copy pixel buffer
			MemArrayPtr< _byte > pixel_buffer;
			pixel_buffer.Create( size, mImagePixelBuffer );

			// Start to rotate
			_byte* des = mImagePixelBuffer;
			for ( _dword y = 0; y < height; y ++ )
			{
				const _byte* src = pixel_buffer.GetPointer( ) + ((height - 1) * pitch) + (component_size * y);

				for ( _dword x = 0; x < mImageWidth; x ++, des += component_size, src -= pitch )
				{
					switch ( component_size )
					{
						case 1:
							des[0] = src[0];
							break;

						case 2:
							des[0] = src[0];
							des[1] = src[1];
							break;

						case 3:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							break;

						case 4:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							des[3] = src[3];
							break;

						default:
							break;
					}
				}
			}

			return _true;
		}
		break;

		case IImageFile::_CLOCKWISE_180:
		{
			// Update info
			Math::Swap( mImageWidth, mImageHeight );
			mImagePitch = component_size * mImageWidth;

			// Copy pixel buffer
			MemArrayPtr< _byte > pixel_buffer;
			pixel_buffer.Create( size, mImagePixelBuffer );

			// Start to rotate
			_byte* des = mImagePixelBuffer;
			for ( _dword y = 0; y < mImageHeight; y ++ )
			{
				const _byte* src = pixel_buffer.GetPointer( ) + ((height - y) * pitch) - component_size;

				for ( _dword x = 0; x < mImageWidth; x ++, des += component_size, src -= component_size )
				{
					switch ( component_size )
					{
						case 1:
							des[0] = src[0];
							break;

						case 2:
							des[0] = src[0];
							des[1] = src[1];
							break;

						case 3:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							break;

						case 4:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							des[3] = src[3];
							break;

						default:
							break;
					}
				}
			}

			return _true;
		}
		break;

		case IImageFile::_CLOCKWISE_270:
		{
			// Update info
			Math::Swap( mImageWidth, mImageHeight );
			mImagePitch = component_size * mImageWidth;

			// Copy pixel buffer
			MemArrayPtr< _byte > pixel_buffer;
			pixel_buffer.Create( size, mImagePixelBuffer );

			// Start to rotate
			_byte* des = mImagePixelBuffer;
			for ( _dword y = 0; y < height; y ++ )
			{
				const _byte* src = pixel_buffer.GetPointer( ) + pitch - (component_size * (y + 1));

				for ( _dword x = 0; x < mImageWidth; x ++, des += component_size, src += pitch )
				{
					switch ( component_size )
					{
						case 1:
							des[0] = src[0];
							break;

						case 2:
							des[0] = src[0];
							des[1] = src[1];
							break;

						case 3:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							break;

						case 4:
							des[0] = src[0];
							des[1] = src[1];
							des[2] = src[2];
							des[3] = src[3];
							break;

						default:
							break;
					}
				}
			}

			return _true;
		}
		break;

		default:
			break;
	}

	return _false;
}

template< typename Type >
_ubool TImageFile< Type >::Scale( _IMAGE_FILTER filter, _dword width, _dword height )
{
	_dword component_size = mImagePitch / mImageWidth;

	_byte* pixel_buffer = _null;
	if ( GetImageProcessor( )->ScaleImage( filter, mImagePixelFormat, PointU( mImageWidth, mImageHeight ), mImagePitch, mImagePixelBuffer, PointU( width, height ), pixel_buffer ) == _false )
		return _false;

	EGE_DELETE_ARRAY( mImagePixelBuffer );
	
	mImageWidth			= width;
	mImageHeight		= height;
	mImagePitch			= width * component_size;
	mImagePixelBuffer	= pixel_buffer;

	return _true;
}

template< typename Type >
_ubool TImageFile< Type >::Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer )
{
	return _false;
}

template< typename Type >
_ubool TImageFile< Type >::SaveToFileBySubRegion( const RectU& region, WStringPtr filename ) const
{
	if ( mImagePixelBuffer == _null )
		return _false;

	// Get the sub region width and height
	_dword sub_width	= region.GetWidth( );
	_dword sub_height	= region.GetHeight( );
	if ( sub_width > mImageWidth || sub_height > mImageHeight )
		return _false;

	// Get the sub-region pitch in bytes
	_dword sub_pitch = region.GetWidth( ) * GetPixelBytes( );

	// Create sub region pixel buffer
	MemArrayPtr< _byte > sub_pixel_buffer( sub_width * sub_pitch * sub_height );
	for ( _dword y = 0; y < sub_height; y ++ )
	{
		_byte*			des_buffer	= &sub_pixel_buffer[y * sub_pitch];
		const _byte*	src_buffer	= mImagePixelBuffer + ( ( region.t + y ) * mImagePitch ) + ( region.l * GetPixelBytes( ) );

		EGE_MEM_CPY( des_buffer, src_buffer, sub_pitch );
	}

	// Create file stream
	IFileStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateFileStreamWriter( filename );
	if ( stream_writer.IsNull( ) )
		return _false;

	// Save sub region to file
	if ( OnSaveToFile( sub_pixel_buffer, sub_pitch, sub_width, sub_height, stream_writer ) == _false )
		return _false;

	return _true;
}

}