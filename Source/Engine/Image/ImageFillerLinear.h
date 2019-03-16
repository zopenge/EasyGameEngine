//! @file     ImageFillerLinear.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ImageFillerLinear
//----------------------------------------------------------------------------

class ImageFillerLinear : public INTERFACE_IMAGE_FILLER_IMPL( IImageFiller )
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
	virtual _ubool	OnAddImage( _dword width, _dword height, RectU& rect ) override;
	virtual _ubool	OnFreeImage( const RectU& rect ) override;

public:
	ImageFillerLinear( const PointU& size, const PointU& space );
	virtual ~ImageFillerLinear( );

// IImageFiller Interface
public:
	virtual _void	ClearAllImages( ) override;
};

//----------------------------------------------------------------------------
// ImageFillerLinear Implementation
//----------------------------------------------------------------------------

}