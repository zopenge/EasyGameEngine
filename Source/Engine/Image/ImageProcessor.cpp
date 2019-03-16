//! @file     ImageProcessor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// ImageProcessor Helpful Functions Implementation
// --------------------------------------------------------------------------------------------------------------

// Thanks for : http://blog.ivank.net/fastest-gaussian-blur.html sharing

static _void BoxesForGauss( _float sigma, _dword n, _int sizes[] )  // standard deviation, number of boxes
{
	_float	wIdeal	= Math::Sqrt( (12.0f * sigma*sigma / n) + 1 );  // Ideal averaging filter width 
	_int	wl		= (_dword)Math::Floor( wIdeal );  
	if ( wl % 2 == 0 ) 
		wl--;
	
	_int wu = wl + 2;

	_float	mIdeal	= (12.0f * sigma*sigma - n*wl*wl - 4.0f * n*wl - 3.0f * n) / (-4.0f * wl - 4.0f);
	_int	m		= Math::Round( mIdeal );

	for ( _int i = 0; i < (_int)n; i++ ) 
		sizes[i] = ( i < m ? wl : wu );
}

template< typename Type >
static _void BoxBlurH4( const Type* scl, Type* tcl, _dword w, _dword h, _float r )
{
	_float iarr = 1 / (r + r + 1.0f);

	for ( _dword i = 0; i < h; i++ )
	{
		_dword ti = i*w, li = ti, ri = ti + (_dword)r;
		_float fv = scl[ti], lv = scl[ti + w - 1], val = (r + 1.0f)*fv;
		for ( _dword j = 0; j < r; j++ ) val += scl[ti + j];
		for ( _dword j = 0; j <= (_dword)r; j++ ) { val += scl[ri++] - (Type)fv; tcl[ti++] = (Type)Math::Round( val*iarr ); }
		for ( _dword j = (_dword)r + 1; j < w - (_dword)r; j++ ) { val += scl[ri++] - scl[li++]; tcl[ti++] = (Type)Math::Round( val*iarr ); }
		for ( _dword j = w - (_dword)r; j < w; j++ ) { val += (Type)lv - scl[li++]; tcl[ti++] = (Type)Math::Round( val*iarr ); }
	}
}
template< typename Type >
static _void BoxBlurT4( const Type* scl, Type* tcl, _dword w, _dword h, _float r )
{
	_float iarr = 1 / (r + r + 1.0f);

	for ( _dword i = 0; i < w; i++ ) 
	{
		_dword ti = i, li = ti, ri = (_dword)(ti + r*w);
		_float fv = scl[ti], lv = scl[ti + w*(h - 1)], val = (r + 1)*fv;
		for ( _dword j = 0; j < r; j++ ) val += scl[ti + j*w];
		for ( _dword j = 0; j <= (_dword)r; j++ ) { val += scl[ri] - (Type)fv;  tcl[ti] = (Type)Math::Round( val*iarr );  ri += w; ti += w; }
		for ( _dword j = (_dword)r + 1; j < h - r; j++ ) { val += scl[ri] - scl[li];  tcl[ti] = (Type)Math::Round( val*iarr );  li += w; ri += w; ti += w; }
		for ( _dword j = h - (_dword)r; j < h; j++ ) { val += (Type)lv - scl[li];  tcl[ti] = (Type)Math::Round( val*iarr );  li += w; ti += w; }
	}
}

template< typename Type >
static _void BoxBlur4( Type* scl, Type* tcl, _dword w, _dword h, _float r )
{
	_dword size = w * h;
	EGE_MEM_CPY( tcl, scl, size );

	BoxBlurH4( tcl, scl, w, h, r );
	BoxBlurT4( scl, tcl, w, h, r );
}

template< typename Type >
static _void GaussBlur4( Type* scl, Type* tcl, _dword w, _dword h, _float r )
{
	_int bxs[3];
	BoxesForGauss( r, 3, bxs );

	BoxBlur4< Type >( scl, tcl, w, h, EGE_RATIO( bxs[0] - 1, 2 ) );
	BoxBlur4< Type >( tcl, scl, w, h, EGE_RATIO( bxs[1] - 1, 2 ) );
	BoxBlur4< Type >( scl, tcl, w, h, EGE_RATIO( bxs[2] - 1, 2 ) );
}

static _void FillImageBorderR2L( _int border_size, _byte* pixel_buffer, const Color& border_color )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer -= 3;
		if ( pixel_buffer[0] != 0 || pixel_buffer[1] != 0 || pixel_buffer[2] != 0 )
			break;

		pixel_buffer[0] = border_color.b;
		pixel_buffer[1] = border_color.g;
		pixel_buffer[2] = border_color.r;
	}
}

static _void FillImageBorderL2R( _int border_size, _byte* pixel_buffer, const Color& border_color )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer += 3;
		if ( pixel_buffer[0] != 0 || pixel_buffer[1] != 0 || pixel_buffer[2] != 0 )
			break;

		pixel_buffer[0] = border_color.b;
		pixel_buffer[1] = border_color.g;
		pixel_buffer[2] = border_color.r;
	}
}

static _void FillImageBorderB2T( _int border_size, _byte* pixel_buffer, const Color& border_color, _dword pitch )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer -= pitch;
		if ( pixel_buffer[0] != 0 || pixel_buffer[1] != 0 || pixel_buffer[2] != 0 )
			break;

		pixel_buffer[0] = border_color.b;
		pixel_buffer[1] = border_color.g;
		pixel_buffer[2] = border_color.r;
	}
}

static _void FillImageBorderT2B( _int border_size, _byte* pixel_buffer, const Color& border_color, _dword pitch )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer += pitch;
		if ( pixel_buffer[0] != 0 || pixel_buffer[1] != 0 || pixel_buffer[2] != 0 )
			break;

		pixel_buffer[0] = border_color.b;
		pixel_buffer[1] = border_color.g;
		pixel_buffer[2] = border_color.r;
	}
}

static _void FillImageBorderR2L( _int border_size, _dword* pixel_buffer, const Color& border_color )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer --;
		if ( *pixel_buffer != 0 )
			break;

		*pixel_buffer = border_color;
	}
}

static _void FillImageBorderL2R( _int border_size, _dword* pixel_buffer, const Color& border_color )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer ++;
		if ( *pixel_buffer != 0 )
			break;

		*pixel_buffer = border_color;
	}
}

static _void FillImageBorderB2T( _int border_size, _dword* pixel_buffer, const Color& border_color, _dword pitch )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer = (_dword*)(((_byte*)pixel_buffer) - pitch);
		if ( *pixel_buffer != 0 )
			break;

		*pixel_buffer = border_color;
	}
}

static _void FillImageBorderT2B( _int border_size, _dword* pixel_buffer, const Color& border_color, _dword pitch )
{
	for ( _int i = 0; i < border_size; i ++ )
	{
		pixel_buffer = (_dword*)(((_byte*)pixel_buffer) + pitch);
		if ( *pixel_buffer != 0 )
			break;

		*pixel_buffer = border_color;
	}
}

static Color GetBorderColor( const PointU& border_size, _dword* pixel_buffer, _dword pitch )
{
	_dword r = 0, g = 0, b = 0, a = 0;

	for ( _int y = - (_int)border_size.y / 2; y < (_int)border_size.y / 2; y ++ )
	{
		for ( _int x = - (_int)border_size.x / 2; x < (_int)border_size.x / 2; x ++ )
		{
			_byte* pixel = (_byte*)pixel_buffer + y * pitch + x * 4;

			a += pixel[3];
			r += pixel[2];
			g += pixel[1];
			b += pixel[0];
		}
	}

	_dword number = border_size.x * border_size.y;

	Color border_color;
	border_color.a = a / number;
	border_color.r = r / number;
	border_color.g = g / number;
	border_color.b = b / number;

	return border_color;
}

static Color GetBorderColor( const PointU& border_size, _byte* pixel_buffer, _dword pitch )
{
	_dword r = 0, g = 0, b = 0;

	for ( _int y = - (_int)border_size.y / 2; y < (_int)border_size.y / 2; y ++ )
	{
		for ( _int x = - (_int)border_size.x / 2; x < (_int)border_size.x / 2; x ++ )
		{
			_byte* pixel = pixel_buffer + y * pitch + x * 3;

			r += pixel[2];
			g += pixel[1];
			b += pixel[0];
		}
	}

	_dword number = border_size.x * border_size.y;

	Color border_color;
	border_color.a = 0xFF;
	border_color.r = r / number;
	border_color.g = g / number;
	border_color.b = b / number;

	return border_color;
}

static _void FillImageBorder( const RectI& rect, _dword pitch, const PointU& border_size, _dword* pixel_buffer )
{
	for ( _int y = rect.t; y < rect.b; y ++ )
	{
		for ( _int x = rect.l; x < rect.r; x ++ )
		{
			_dword* pixel = (_dword*)((_byte*)pixel_buffer + y * pitch + x * 4);
			if ( *pixel != 0 )
			{
				Color border_color = GetBorderColor( border_size, pixel, pitch );
				FillImageBorderL2R( border_size.x, pixel, border_color );
				FillImageBorderR2L( border_size.x, pixel, border_color );
				FillImageBorderB2T( border_size.y, pixel, border_color, pitch );
				FillImageBorderT2B( border_size.y, pixel, border_color, pitch );
			}
		}
	}
}

static _void FillImageBorder( const RectI& rect, _dword pitch, const PointU& border_size, _byte* pixel_buffer )
{
	for ( _int y = rect.t; y < rect.b; y ++ )
	{
		for ( _int x = rect.l; x < rect.r; x ++ )
		{
			_byte* pixel = pixel_buffer + y * pitch + x * 3;
			if ( pixel[0] != 0 || pixel[1] != 0 || pixel[2] != 0 )
			{
				Color border_color = GetBorderColor( border_size, pixel, pitch );
				FillImageBorderL2R( border_size.x, pixel, border_color );
				FillImageBorderR2L( border_size.x, pixel, border_color );
				FillImageBorderB2T( border_size.y, pixel, border_color, pitch );
				FillImageBorderT2B( border_size.y, pixel, border_color, pitch );
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------
// ImageProcessor Implementation
// --------------------------------------------------------------------------------------------------------------

ImageProcessor::ImageProcessor( )
{
}

ImageProcessor::~ImageProcessor( )
{
}

IImageFilePassRef ImageProcessor::ScaleImage( _IMAGE_FILTER filter, const Vector2& scale_factor, IImageFile* image_file )
{
	if ( image_file == _null )
		return _null;
	
	if ( scale_factor.x <= 0.0f || scale_factor.y <= 0.0f )
		return _null;

	// Get the image file ID
	_FILE_FORMAT file_format = image_file->GetFileID( );

	// Get the scaled image size
	_dword scaled_image_width	= Math::Max( 1U, (_dword)((_float)image_file->GetWidth( ) * scale_factor.x) );
	_dword scaled_image_height	= Math::Max( 1U, (_dword)((_float)image_file->GetHeight( ) * scale_factor.y) );

	// We only support RGB and ARGB pixel format
	_PIXEL_FORMAT pixel_format = image_file->GetPixelFormat( );
	if ( pixel_format != _PF_A8R8G8B8 && pixel_format != _PF_R8G8B8 )
		return _null;

	// Get the scaled image pixel size in bytes
	_dword					scaled_image_pitch		= (pixel_format == _PF_A8R8G8B8 ? 4 : 3) * scaled_image_width;
//	_dword					scaled_image_pixel_size = Math::Max( src_image_size_in_bytes, scaled_image_pitch * scaled_image_height );
	_dword					scaled_image_pixel_size = scaled_image_pitch * scaled_image_height;
	MemArrayPtr< _byte >	scale_image_pixel( scaled_image_pixel_size );
	EGE_MEM_SET( scale_image_pixel, 0, scaled_image_pixel_size );

	// Get filter
	GenericFilter* generic_filter = _null;
	switch ( filter )
	{
		case _IMAGE_FILTER_BOX:			generic_filter = new BoxFilter( ); break;
		case _IMAGE_FILTER_BICUBIC:		generic_filter = new BicubicFilter( ); break;
		case _IMAGE_FILTER_BILINEAR:	generic_filter = new BilinearFilter( ); break;
		case _IMAGE_FILTER_BSPLINE:		generic_filter = new BSplineFilter( ); break;
		case _IMAGE_FILTER_CATMULLROM:	generic_filter = new CatmullRomFilter( ); break;
		case _IMAGE_FILTER_LANCZOS3:	generic_filter = new Lanczos3Filter( ); break;
		default:
			return _null;
	}

	// Process scale
	ResizeEngine resize_engine( generic_filter );
	resize_engine.Scale( image_file, (unsigned)scaled_image_width, (unsigned)scaled_image_height, scaled_image_pitch, scale_image_pixel.GetPointer( ) );

	// Delete filter
	EGE_DELETE( generic_filter );

	// Create scale image file
	IImageFilePassRef scaled_image_file = GetInterfaceFactory( )->CreateImageFile( file_format, scaled_image_width, scaled_image_height, pixel_format, scale_image_pixel.GetPointer( ) );
	if ( scaled_image_file.IsNull( ) )
		return _null;

	return scaled_image_file;
}

_ubool ImageProcessor::ScaleImage( _IMAGE_FILTER filter, _PIXEL_FORMAT pixel_format, const PointU& original_size, _dword original_pitch, const _void* original_pixel, const PointU& scale_size, _byte*& scale_pixel )
{
	if ( original_pixel == _null )
		return _false;

	// Get the scaled image size
	_dword scaled_image_width	= Math::Max( 1U, scale_size.x );
	_dword scaled_image_height	= Math::Max( 1U, scale_size.y );

	// We only support RGB and ARGB pixel format
	if ( pixel_format != _PF_A8R8G8B8 && pixel_format != _PF_R8G8B8 )
		return _false;

	// Get the scaled image pixel size in bytes
	_dword scaled_image_pitch		= (pixel_format == _PF_A8R8G8B8 ? 4 : 3) * scaled_image_width;
	_dword scaled_image_pixel_size	= scaled_image_pitch * scaled_image_height;

	// Create scale image pixel
	scale_pixel = new _byte[scaled_image_pixel_size];
	EGE_MEM_SET( scale_pixel, 0, scaled_image_pixel_size );

	// Get filter
	GenericFilter* generic_filter = _null;
	switch ( filter )
	{
		case _IMAGE_FILTER_BOX:			generic_filter = new BoxFilter( ); break;
		case _IMAGE_FILTER_BICUBIC:		generic_filter = new BicubicFilter( ); break;
		case _IMAGE_FILTER_BILINEAR:	generic_filter = new BilinearFilter( ); break;
		case _IMAGE_FILTER_BSPLINE:		generic_filter = new BSplineFilter( ); break;
		case _IMAGE_FILTER_CATMULLROM:	generic_filter = new CatmullRomFilter( ); break;
		case _IMAGE_FILTER_LANCZOS3:	generic_filter = new Lanczos3Filter( ); break;
		default:
			return _false;
	}

	// Process scale
	ResizeEngine resize_engine( generic_filter );
	resize_engine.Scale( original_size.x, original_size.y, original_pitch, pixel_format, (const _byte*) original_pixel, scaled_image_width, scaled_image_height, scaled_image_pitch, scale_pixel );

	// Delete filter
	EGE_DELETE( generic_filter );

	return _true;
}

_ubool ImageProcessor::AddImageBorder( _PIXEL_FORMAT pixel_format, const RectI& rect, _dword pitch, const PointU& border_size, _byte* pixel_buffer )
{
	switch ( pixel_format )
	{
		case _PF_A8R8G8B8:
		{
			_dword* pixel = (_dword*) pixel_buffer;
			FillImageBorder( rect, pitch, border_size, pixel );
		}
		break;

		case _PF_R8G8B8:
		{
			_byte* pixel = pixel_buffer;
			FillImageBorder( rect, pitch, border_size, pixel );
		}
		break;

		default:
			break;
	}

	return _true;
}

_ubool ImageProcessor::GaussianBlur( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float factor ) const
{
	if ( des_image.IsValid( ) == _false || src_image.IsValid( ) == _false )
		return _false;

	// The pixel format must be equal
	if ( des_image.mPixelFormat != src_image.mPixelFormat )
		return _false;

	// Get the pixel format
	_PIXEL_FORMAT pixel_format = des_image.mPixelFormat;

	// The source and target region size must be the same
	if ( des_rect.GetSize( ) != src_rect.GetSize( ) )
		return _false;

	// Get the size of region
	_int width		= des_rect.GetWidth( );
	_int height	= src_rect.GetHeight( );

	// Process images
	switch ( pixel_format )
	{
		// A8 mode
		case _PF_A8:
		{
			GaussBlur4< _byte >( (_byte*)src_image.mPixelBuffer, (_byte*)des_image.mPixelBuffer, des_rect.GetWidth( ), des_rect.GetHeight( ), factor );
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_ubool ImageProcessor::AlphaBlending( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect, _float alpha ) const
{
	if ( des_image.IsValid( ) == _false || src_image.IsValid( ) == _false )
		return _false;

	// The pixel format must be equal
	if ( des_image.mPixelFormat != src_image.mPixelFormat )
		return _false;

	// Get the pixel format
	_PIXEL_FORMAT pixel_format = des_image.mPixelFormat;

	// The source and target region size must be the same
	if ( des_rect.GetSize( ) != src_rect.GetSize( ) )
		return _false;

	// Get the size of region
	_int width		= des_rect.GetWidth( );
	_int height	= src_rect.GetHeight( );

	// Process images
	switch ( pixel_format )
	{
		// ARGB mode
		case _PF_A8R8G8B8:
		{
			for ( _int y = 0; y < height; y ++ )
			{
				_byte*			des_pixel = des_image.GetPixelBufferByPos( des_rect.l, des_rect.t + y );
				const _byte*	src_pixel = src_image.GetPixelBufferByPos( src_rect.l, src_rect.t + y );

				for ( _int x = 0; x < width * 4; x += 4 )
				{
					_byte& des_a = des_pixel[x + 3];
					_byte& des_r = des_pixel[x + 2];
					_byte& des_g = des_pixel[x + 1];
					_byte& des_b = des_pixel[x + 0];

					_byte  src_a = src_pixel[x + 3];
					_byte  src_r = src_pixel[x + 2];
					_byte  src_g = src_pixel[x + 1];
					_byte  src_b = src_pixel[x + 0];

					des_a = ( ( 0xFF - src_a ) * des_a + ( src_a * src_a ) ) / 0xFF;
					des_r = ( ( 0xFF - src_a ) * des_r + ( src_a * src_r ) ) / 0xFF;
					des_g = ( ( 0xFF - src_a ) * des_g + ( src_a * src_g ) ) / 0xFF;
					des_b = ( ( 0xFF - src_a ) * des_b + ( src_a * src_b ) ) / 0xFF;
				}
			}
		}
		break;

		default:
			return _false;
	}
	
	return _true;
}

_ubool ImageProcessor::Draw( BitmapInfo& des_image, const BitmapInfoReadOnly& src_image, const RectI& des_rect, const RectI& src_rect ) const
{
	if ( des_image.IsValid( ) == _false || src_image.IsValid( ) == _false )
		return _false;

	// The source and target region size must be the same
	if ( des_rect.GetSize( ) != src_rect.GetSize( ) )
		return _false;

	// Get the size of region
	_int width		= des_rect.GetWidth( );
	_int height	= src_rect.GetHeight( );

	// It's same pixel format
	if ( des_image.mPixelFormat == src_image.mPixelFormat )
	{
		for ( _int y = 0; y < height; y ++ )
		{
			_byte*			des_pixel = des_image.GetPixelBufferByPos( des_rect.l, des_rect.t + y );
			const _byte*	src_pixel = src_image.GetPixelBufferByPos( src_rect.l, src_rect.t + y );

			EGE_MEM_CPY( des_pixel, src_pixel, width * des_image.mPixelBytes );
		}
	}
	// RGB -> RGBA
	else if ( src_image.mPixelFormat == _PF_R8G8B8 && des_image.mPixelFormat == _PF_A8R8G8B8 )
	{
		for ( _int y = 0; y < height; y ++ )
		{
			_byte*			des_pixel = des_image.GetPixelBufferByPos( des_rect.l, des_rect.t + y );
			const _byte*	src_pixel = src_image.GetPixelBufferByPos( src_rect.l, src_rect.t + y );

			for ( _int x = 0; x < width; x ++ )
			{
				_byte& des_a = des_pixel[x * des_image.mPixelBytes + 3];
				_byte& des_r = des_pixel[x * des_image.mPixelBytes + 2];
				_byte& des_g = des_pixel[x * des_image.mPixelBytes + 1];
				_byte& des_b = des_pixel[x * des_image.mPixelBytes + 0];

				_byte  src_r = src_pixel[x * src_image.mPixelBytes + 2];
				_byte  src_g = src_pixel[x * src_image.mPixelBytes + 1];
				_byte  src_b = src_pixel[x * src_image.mPixelBytes + 0];

				des_a = 0xFF;
				des_r = src_r;
				des_g = src_g;
				des_b = src_b;
			}
		}
	}
	// RGBA -> RGB
	else if ( src_image.mPixelFormat == _PF_A8R8G8B8 && des_image.mPixelFormat == _PF_R8G8B8 )
	{
		for ( _int y = 0; y < height; y ++ )
		{
			_byte*			des_pixel = des_image.GetPixelBufferByPos( des_rect.l, des_rect.t + y );
			const _byte*	src_pixel = src_image.GetPixelBufferByPos( src_rect.l, src_rect.t + y );

			for ( _int x = 0; x < width; x ++ )
			{
				_byte& des_r = des_pixel[x * des_image.mPixelBytes + 2];
				_byte& des_g = des_pixel[x * des_image.mPixelBytes + 1];
				_byte& des_b = des_pixel[x * des_image.mPixelBytes + 0];

				_byte  src_r = src_pixel[x * src_image.mPixelBytes + 2];
				_byte  src_g = src_pixel[x * src_image.mPixelBytes + 1];
				_byte  src_b = src_pixel[x * src_image.mPixelBytes + 0];

				des_r = src_r;
				des_g = src_g;
				des_b = src_b;
			}
		}
	}

	return _true;
}

_ubool ImageProcessor::FillColorInTransparentArea( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword width, _dword height )
{
	if ( pixel_buffer == _null || width == 0 || height == 0 )
		return _false;

	_int test_size = 2;

	switch ( format )
	{
	case _PF_A8R8G8B8:
		{
			_dword pixel_size	= 4;
			_dword pixel_number	= width * height;
			_dword buffer_size	= pixel_size * pixel_number;

			// Create temporary pixel buffer for storing image info
			MemArrayPtr< _byte > backup_buffer( buffer_size );
			EGE_MEM_CPY( backup_buffer, pixel_buffer, buffer_size );
			for ( _int i = 0; i < (_int)pixel_number; ++ i )
			{
				_byte* pixel = pixel_buffer + i * pixel_size;
				_byte* a = pixel + 3;
				_byte* r = pixel + 2;
				_byte* g = pixel + 1;
				_byte* b = pixel + 0;

				if ( *a == 0 )
				{
					_dword pixel_count = 0;
					_dword r_total = 0;
					_dword g_total = 0;
					_dword b_total = 0;
					for ( _int y = -test_size; y < test_size; ++ y )
					{
						for ( _int x = -test_size; x < test_size; ++ x )
						{
							_int pixel_index = i + y * (_int)width + x;
							if ( pixel_index >= 0 && pixel_index < (_int)pixel_number )
							{
								_byte* backup_pixel = backup_buffer.GetPointer( ) + pixel_index * pixel_size;
								_byte a_backup = backup_pixel[3];
								if ( a_backup != 0 )
								{
									r_total += (_dword)(backup_pixel[2]);
									g_total += (_dword)(backup_pixel[1]);
									b_total += (_dword)(backup_pixel[0]);
									pixel_count ++;
								}
							}
						}
					}

					if( pixel_count != 0 )
					{
						*r = (_byte)( r_total / pixel_count );
						*g = (_byte)( g_total / pixel_count );
						*b = (_byte)( b_total / pixel_count );
					}
				}
			}		
		}
		break;
	default:
		break;
	}

	return _true;
}

_ubool ImageProcessor::Flip( _byte* pixel_buffer, _dword pitch, _dword height ) const
{
	if ( pixel_buffer == _null || pitch == 0 || height == 0 )
		return _false;

	// Get the middle position
	_dword mid_pos = height / 2;

	// Create temporary pixel buffer for storing line-pixel info
	MemArrayPtr< _byte > line_pixel_buffer( pitch );

	// Start to flip
	for ( _dword y = 0; y <= mid_pos; y ++ )
	{
		_byte* line_1 = &pixel_buffer[ y * pitch ];
		_byte* line_2 = &pixel_buffer[ ( height - y - 1 ) * pitch ];

		// Backup the pixel buffer
		EGE_MEM_CPY( line_pixel_buffer, line_1, pitch );

		// Exchange pixel buffer by line
		EGE_MEM_CPY( line_1, line_2, pitch );
		EGE_MEM_CPY( line_2, line_pixel_buffer, pitch );
	}

	return _true;
}

_ubool ImageProcessor::SwapRBChannel( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const
{
	if ( pixel_buffer == _null || pitch == 0 || width == 0 || height == 0 )
		return _false;

	// Start to convert
	for ( _dword y = 0; y < height; y ++ )
	{
		for ( _dword x = 0; x < width; x ++ )
			Math::Swap( pixel_buffer[ y * pitch + x * 3 ], pixel_buffer[ y * pitch + x * 3 + 2 ] );
	}

	return _true;
}

_ubool ImageProcessor::SwapRBChannelWithAlpha( _byte* pixel_buffer, _dword pitch, _dword width, _dword height ) const
{
	if ( pixel_buffer == _null || pitch == 0 || width == 0 || height == 0 )
		return _false;

	// Start to convert
	for ( _dword y = 0; y < height; y ++ )
	{
		for ( _dword x = 0; x < width; x ++ )
			Math::Swap( pixel_buffer[ y * pitch + x * 4 ], pixel_buffer[ y * pitch + x * 4 + 2 ] );
	}

	return _true;
}

_ubool ImageProcessor::TestColorConversion( _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch ) const
{
	if ( pitch == 0 || width == 0 || height == 0 )
		return _false;

	switch ( des_format )
	{
		case _PF_R5G6B5:
		case _PF_R5G5B5A1:
		case _PF_R4G4B4A4:
		case _PF_A8G8:
		{
			des_pitch = Math::UpperArrange( width * sizeof( _word ), 4 );
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_ubool ImageProcessor::ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword des_pitch, _byte* des_pixel_buffer ) const
{
	if ( pixel_buffer == _null || pitch == 0 || width == 0 || height == 0 )
		return _false;

	switch ( des_format )
	{
		case _PF_R5G6B5:
		{
			if ( format == _PF_R8G8B8 )
				return RGBConversion< _word, R5G6B5 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else if ( format == _PF_A8R8G8B8 )
				return ARGBConversion< _word, R5G6B5 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else
				return _false;
		}
		break;

		case _PF_R5G5B5A1:
		{
			if ( format == _PF_R8G8B8 )
				return RGBConversion< _word, R5G5B5A1 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else if ( format == _PF_A8R8G8B8 )
				return ARGBConversion< _word, R5G5B5A1 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else
				return _false;
		}
		break;

		case _PF_R4G4B4A4:
		{
			if ( format == _PF_R8G8B8 )
				return RGBConversion< _word, R4G4B4A4 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else if ( format == _PF_A8R8G8B8 )
				return ARGBConversion< _word, R4G4B4A4 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else
				return _false;
		}
		break;

		case _PF_A8G8:
		{
			if ( format == _PF_R8G8B8 )
				return RGBConversion< _word, A8G8 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else if ( format == _PF_A8R8G8B8 )
				return ARGBConversion< _word, A8G8 >( pixel_buffer, pitch, width, height, des_pitch, des_pixel_buffer );
			else
				return _false;
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_ubool ImageProcessor::ProcessColorConversion( _byte* pixel_buffer, _PIXEL_FORMAT format, _dword pitch, _dword width, _dword height, _PIXEL_FORMAT des_format, _dword& des_pitch, MemArrayPtr< _byte >& des_pixel_buffer ) const
{
	if ( TestColorConversion( format, pitch, width, height, des_format, des_pitch ) == _false )
		return _false;

	return ProcessColorConversion( pixel_buffer, format, pitch, width, height, des_format, des_pitch, des_pixel_buffer.Create( des_pitch * height ) );
}

_ubool ImageProcessor::GetTransparentLayer( const BitmapInfoReadOnly& image_info, BitArray< 1 >& transparent_layer ) const
{
	if ( image_info.IsValid( ) == _false )
		return _false;

	// The transparent layer's buffer size must bigger than the image size
	_dword size = image_info.mWidth * image_info.mHeight;
	if ( size > transparent_layer.Number( ) )
	{
		WLOG_ERROR_4( L"The %dx%d(%d) image size is bigger than '%d' transparent layer",
			image_info.mWidth, image_info.mHeight, size, transparent_layer.Number( ) );

		return _false;
	}

	// ARGB mode
	if ( image_info.mPixelFormat == _PF_A8R8G8B8 )
	{
		for ( _dword y = 0; y < image_info.mHeight; y ++ )
		{
			const _dword* pixel_buffer = (const _dword*)( image_info.mPixelBuffer + y * image_info.mPitch );

			for ( _dword x = 0; x < image_info.mWidth; x ++ )
			{
				_ubool transparent = (pixel_buffer[x] >> 24) == 0;

				transparent_layer.Set( y * image_info.mWidth + x, transparent );
			}
		}
	}
	// Unsupported mode
	else
	{
		return _false;
	}

	return _true;
}

_ubool ImageProcessor::GetOpaqueRegion( const BitmapInfoReadOnly& image_info, RectI& rect ) const
{
	if ( image_info.IsValid( ) == _false )
		return _false;

	// We only support ARGB mode
	if ( image_info.mPixelFormat != _PF_A8R8G8B8 )
		return _false;

	// Initialize opaque region
	rect.l = (_int)image_info.mWidth;
	rect.t = (_int)image_info.mHeight;
	rect.r = 0;
	rect.b = 0;

	// Testing alpha to calculate opaque region
	for ( _dword y = 0; y < image_info.mHeight; y ++ )
	{
		const _dword* pixel_buffer = (const _dword*)( image_info.mPixelBuffer + y * image_info.mPitch );

		for ( _dword x = 0; x < image_info.mWidth; x ++ )
		{
			_ubool transparent = (pixel_buffer[x] >> 24) == 0;

			if ( transparent == _false )
			{
				rect.l = Math::Min< _int >( rect.l, (_int)x );
				rect.t = Math::Min< _int >( rect.t, (_int)y );
				rect.r = Math::Max< _int >( rect.r, (_int)x + 1 );
				rect.b = Math::Max< _int >( rect.b, (_int)y + 1 );
			}
		}
	}

	// Does all the image is whole transparent
	if ( rect.r == 0 && rect.b == 0 )
		rect = RectI::cNull;

	return _true;
}

_ubool ImageProcessor::GetOpaqueRegion( const PointI& size, const PointI& position, RectI& rect, OnIsTransparentPixel funcpointer, const QwordParameters2& parameters ) const
{
	if ( size.x == 0 || size.y == 0 )
		return _false;

	if ( funcpointer == _null )
		return _false;

	// Initialize callback function
	CallbackFunc< OnIsTransparentPixel, _ubool, QwordParameters2 > is_transparent_pixel_func;
	is_transparent_pixel_func.Init( funcpointer, parameters );

	// If the start position is transparent then skip it
	if ( is_transparent_pixel_func.InvokeR( position.x, position.y ) )
		return _false;

	// Initialize opaque region
	rect.l = Math::cMaxInt;
	rect.t = Math::cMaxInt;
	rect.r = Math::cMinInt;
	rect.b = Math::cMinInt;

	// The start position
	_int x = position.x;
	_int y = position.y;

	// The image size region
	const _int min_x = 0;
	const _int max_x = size.x;
	const _int max_y = size.y;

	// Make sure the start position is in the bitmap region
	if ( x <= min_x || x >= max_x || y <= min_x || y >= max_y )
		return _false;

	// Create pixel walked array
	BitArray< 1 > pixel_walked_array;
	pixel_walked_array.Create( max_x * max_y );

	// The pixel stack info
	Stack< PointI > pixel_info_stack;

	// Prepare to testing region
	pixel_info_stack.Push( PointI( x, y ) );
	pixel_walked_array.Set( y * max_x + x, 1 );

	// Start to fill
	while ( pixel_info_stack.Number( ) > 0 )
	{
		// Copy pixel info, for prevent the buffer re-allocation, we need to copy operation here
		PointI pixel_info = pixel_info_stack.Top( );

		// The delta offset (4-directions)
		static _int cDeltaOffset[] = 
		{
			-1,  0,
			 0, -1,
			 1,  0,
			 0,  1,
		};

		// Update opaque region
		_ubool update = _false;
		for ( _dword i = 0; i < EGE_ARRAY_NUMBER( cDeltaOffset ); i += 2 )
		{
			_int _x		= pixel_info.x + cDeltaOffset[i];
			_int _y		= pixel_info.y + cDeltaOffset[i + 1];
			_int _index	= _y * max_x + _x;

			// Check bounds
			if ( _x <= min_x || _x >= max_x || _y <= min_x || _y >= max_y )
				continue;

			// Check whether has been walked
			if ( pixel_walked_array[ _index ] )
				continue;

			// Update opaque region when it's none-transparent pixel
			if ( is_transparent_pixel_func.InvokeR( _x, _y ) == _false )
			{
				rect.l = Math::Min< _int >( rect.l, _x );
				rect.t = Math::Min< _int >( rect.t, _y );
				rect.r = Math::Max< _int >( rect.r, _x + 1 );
				rect.b = Math::Max< _int >( rect.b, _y + 1 );

				pixel_info_stack.Push( PointI( _x, _y ) );
				pixel_walked_array.Set( _index, 1 );

				update = _true;
			}
		}

		// Pop it if no used
		if ( update == _false )
			pixel_info_stack.Pop( );
	}

	return _true;
}