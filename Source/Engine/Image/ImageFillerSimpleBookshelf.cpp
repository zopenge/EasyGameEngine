//! @file     ImageFillerSimpleBookshelf.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ImageFillerSimpleBookshelf Implementation
//----------------------------------------------------------------------------

ImageFillerSimpleBookshelf::ImageFillerSimpleBookshelf( const PointU& size, const PointU& space ) : BaseClass( size, space )
{
	mImageStartPos	= PointU::cZeroPoint;
	mMaxHeight		= 0;
}

ImageFillerSimpleBookshelf::~ImageFillerSimpleBookshelf( )
{
	Clear( );
}

_ubool ImageFillerSimpleBookshelf::OnFillImage( _dword width, _dword height, RectU& rect )
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

_void ImageFillerSimpleBookshelf::Clear( )
{
	BaseClass::Clear( );

	mImageStartPos	= PointU::cZeroPoint;
	mMaxHeight		= 0;
}