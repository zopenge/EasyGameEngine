//! @file     Lanczos.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Lanczos Implementation
//----------------------------------------------------------------------------

Lanczos::Lanczos( )
{
	// See referenced website: http://blog.csdn.net/jia20003/article/details/17856859 Thanks for sharing code
	mLanczosSize = 3;
}

Lanczos::~Lanczos( )
{
}

_long Lanczos::Clamp( _long v ) const
{
	return v > 255 ? 255 : (v < 0 ? 0 : v);
}

_float Lanczos::GetFactor( _float distance ) const
{
	if ( distance > mLanczosSize )
		return 0.0f;

	distance *= Math::cPi;
	if ( Math::Abs( distance ) < 1e-16 )
		return 1.0f;

	_float xx = distance / mLanczosSize;
	
	return Math::Sin( distance ) * Math::Sin( xx ) / distance / xx;
}

_ubool Lanczos::FilterRGB( IImageFile* image_file, _dword scaled_width, _dword scaled_height, _byte* scaled_pixel )
{
	if ( image_file == _null )
		return _false;

	if ( scaled_width == 0 || scaled_height == 0 || scaled_pixel == _null )
		return _false;

	_long width			= image_file->GetWidth( );
	_long height		= image_file->GetHeight( );

	_float x_ratio		= EGE_RATIO( width, scaled_width );
	_float y_ratio		= EGE_RATIO( height, scaled_height );
	_float x_ratio_rcp	= 2.0f / x_ratio;
	_float y_ratio_rcp	= 2.0f / y_ratio;
	_float x_range2		= (_float) Math::Ceil( x_ratio * mLanczosSize / 2.0f );
	_float y_range2		= (_float) Math::Ceil( y_ratio * mLanczosSize / 2.0f );

	_byte* in_pixels	= (_byte*) image_file->GetPixelBuffer( );
	_byte* out_pixels	= (_byte*) scaled_pixel;

	_dword index = 0;
	_float fcy = 0, icy = 0, fcx = 0, icx = 0;
	for ( _long row = 0; row < (_long)scaled_height; row ++ )
	{
		_long ta = 0, tr = 0, tg = 0, tb = 0;
		fcy = (row + 0.5f) * y_ratio;
		icy = (_float) Math::Floor(fcy);
		for (_long col = 0; col < (_long)scaled_width; col++)
		{
			fcx = (col + 0.5f) * x_ratio;
			icx = (float) Math::Floor(fcx);

			float sumred = 0, sumgreen = 0, sumblue = 0;
			float totalWeight = 0;
			for (int subcol = (int) (icx - x_range2); subcol <= icx + x_range2; subcol++) 
			{
				if (subcol < 0 || subcol >= width)
					continue;

				int ncol = (int) Math::Floor(1000 * Math::Abs(subcol - fcx));

				for (int subrow = (int) (icy - y_range2); subrow <= icy + y_range2; subrow++) 
				{
					if (subrow < 0 || subrow >= height)
						continue;

					int nrow = (int) Math::Floor(1000 * Math::Abs(subrow - fcy));
					float weight = GetFactor(Math::Sqrt(Math::Pow(ncol * x_ratio_rcp, 2) + Math::Pow(nrow * y_ratio_rcp, 2)) / 1000);
					if (weight > 0) 
					{
						index = (subrow * width + subcol);
						tr = in_pixels[index * 3 + 2];
						tg = in_pixels[index * 3 + 1];
						tb = in_pixels[index * 3];
						totalWeight += weight;
						sumred += weight * tr;
						sumgreen += weight * tg;
						sumblue += weight * tb;
					}
				}
			}

			index = row * scaled_width + col;
			tr = (int) (sumred / totalWeight);
			tg = (int) (sumgreen / totalWeight);
			tb = (int) (sumblue / totalWeight);
			out_pixels[index * 3 + 2] = Clamp(tr);
			out_pixels[index * 3 + 1] = Clamp(tg);
			out_pixels[index * 3 + 0] = Clamp(tb);
		}
	}

	return _true;
}

_ubool Lanczos::FilterARGB( IImageFile* image_file, _dword scaled_width, _dword scaled_height, _byte* scaled_pixel )
{
	if ( image_file == _null )
		return _false;

	if ( scaled_width == 0 || scaled_height == 0 || scaled_pixel == _null )
		return _false;

	_long width			= image_file->GetWidth( );
	_long height		= image_file->GetHeight( );

	_float x_ratio		= EGE_RATIO( width, scaled_width );
	_float y_ratio		= EGE_RATIO( height, scaled_height );
	_float x_ratio_rcp	= 2.0f / x_ratio;
	_float y_ratio_rcp	= 2.0f / y_ratio;
	_float x_range2		= (_float) Math::Ceil( x_ratio * mLanczosSize / 2.0f );
	_float y_range2		= (_float) Math::Ceil( y_ratio * mLanczosSize / 2.0f );

	_dword* in_pixels	= (_dword*) image_file->GetPixelBuffer( );
	_dword* out_pixels	= (_dword*) scaled_pixel;

	_dword index = 0;
	_float fcy = 0, icy = 0, fcx = 0, icx = 0;
	for ( _long row = 0; row < (_long)scaled_height; row ++ )
	{
		_long ta = 0, tr = 0, tg = 0, tb = 0;
		fcy = (row + 0.5f) * y_ratio;
		icy = (_float) Math::Floor(fcy);
		for (_long col = 0; col < (_long)scaled_width; col++)
		{
			fcx = (col + 0.5f) * x_ratio;
			icx = (float) Math::Floor(fcx);

			float sumalpha = 0, sumred = 0, sumgreen = 0, sumblue = 0;
			float totalWeight = 0;
			for (int subcol = (int) (icx - x_range2); subcol <= icx + x_range2; subcol++) 
			{
				if (subcol < 0 || subcol >= width)
					continue;

				int ncol = (int) Math::Floor(1000 * Math::Abs(subcol - fcx));

				for (int subrow = (int) (icy - y_range2); subrow <= icy + y_range2; subrow++) 
				{
					if (subrow < 0 || subrow >= height)
						continue;

					int nrow = (int) Math::Floor(1000 * Math::Abs(subrow - fcy));
					float weight = GetFactor(Math::Sqrt(Math::Pow(ncol * x_ratio_rcp, 2) + Math::Pow(nrow * y_ratio_rcp, 2)) / 1000);
					if (weight > 0) 
					{
						index = (subrow * width + subcol);
						ta = (in_pixels[index] >> 24) & 0xff;
						tr = (in_pixels[index] >> 16) & 0xff;
						tg = (in_pixels[index] >> 8) & 0xff;
						tb = in_pixels[index] & 0xff;
						totalWeight += weight;
						sumalpha += weight * ta;
						sumred += weight * tr;
						sumgreen += weight * tg;
						sumblue += weight * tb;
					}
				}
			}

			index = row * scaled_width + col;
			ta = (int) (sumalpha / totalWeight);
			tr = (int) (sumred / totalWeight);
			tg = (int) (sumgreen / totalWeight);
			tb = (int) (sumblue / totalWeight);
			out_pixels[index] = (Clamp(ta) << 24) | (Clamp(tr) << 16) | (Clamp(tg) << 8) | Clamp(tb);
		}
	}

	return _true;
}
