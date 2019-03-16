//! @file     Lanczos.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Lanczos
//----------------------------------------------------------------------------

class Lanczos
{
private:
	_float mLanczosSize;

private:
	//!	Clamp value.
	_long Clamp( _long v ) const;

	//!	Get factor.
	_float GetFactor( _float distance ) const;

public:
	Lanczos( );
	~Lanczos( );

public:
	//!	Do filter RGB.
	_ubool FilterRGB( IImageFile* image_file, _dword scaled_width, _dword scaled_height, _byte* scaled_pixel );
	//!	Do filter ARGB.
	_ubool FilterARGB( IImageFile* image_file, _dword scaled_width, _dword scaled_height, _byte* scaled_pixel );
};

//----------------------------------------------------------------------------
// Lanczos Implementation
//----------------------------------------------------------------------------

}