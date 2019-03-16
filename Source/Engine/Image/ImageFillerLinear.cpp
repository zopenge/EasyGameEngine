//! @file     ImageFillerLinear.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ImageFillerLinear Implementation
//----------------------------------------------------------------------------

ImageFillerLinear::ImageFillerLinear( const PointU& size, const PointU& space ) : BaseClass( size, space )
{
	mImageStartPos	= PointU::cZeroPoint;
	mMaxHeight		= 0;
}

ImageFillerLinear::~ImageFillerLinear( )
{
	ClearAllImages( );
}

_ubool ImageFillerLinear::OnAddImage( _dword width, _dword height, RectU& rect )
{
	// We can not fill this image, because it's exceed the max height of filler
	if ( mImageStartPos.y + height > mSize.y )
		return _false;

	// The line is full, choose next line
	if ( mImageStartPos.x + width > mSize.x )
	{
		mImageStartPos.x  = 0; 
		mImageStartPos.y += mMaxHeight; 

		// Check whether we can fill it to the next line
		if ( mImageStartPos.y + height > mSize.y )
			return _false;

		// Clear the max height
		mMaxHeight = 0;
	}

	// Feedback the image region
	rect.InitWithSize( mImageStartPos.x, mImageStartPos.y, width, height );

	// Update the image start position for next image
	mImageStartPos.x += width;

	// Update the max height
	mMaxHeight = Math::Max< _dword >( mMaxHeight, height );

	return _true;
}

_ubool ImageFillerLinear::OnFreeImage( const RectU& rect )
{
	return _false;
}

_void ImageFillerLinear::ClearAllImages( )
{
	BaseClass::ClearAllImages( );

	mImageStartPos	= PointU::cZeroPoint;
	mMaxHeight		= 0;
}