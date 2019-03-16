//! @file     ImageFillerSimpleBookshelf.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ImageFillerSimpleBookshelf
//----------------------------------------------------------------------------

class ImageFillerSimpleBookshelf : public INTERFACE_IMAGE_FILLER_IMPL( IImageFiller )
{
private:
	typedef INTERFACE_IMAGE_FILLER_IMPL( IImageFiller ) BaseClass;

private:
	//! The image start position
	PointU	mImageStartPos;
	//!	The max height of this line
	_dword	mMaxHeight;

// TImageFiller interface
private:
	virtual _ubool	OnFillImage( _dword width, _dword height, RectU& rect ) override;

public:
	ImageFillerSimpleBookshelf( const PointU& size, const PointU& space );
	virtual ~ImageFillerSimpleBookshelf( );

// IImageFiller Interface
public:
	virtual _void	Clear( ) override;
};

//----------------------------------------------------------------------------
// ImageFillerSimpleBookshelf Implementation
//----------------------------------------------------------------------------

}