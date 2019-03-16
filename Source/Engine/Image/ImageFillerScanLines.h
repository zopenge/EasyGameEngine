//! @file     ImageFillerScanLines.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ImageFillerScanLines
//----------------------------------------------------------------------------

class ImageFillerScanLines : public INTERFACE_IMAGE_FILLER_IMPL( IImageFiller )
{
private:
	typedef INTERFACE_IMAGE_FILLER_IMPL( IImageFiller ) BaseClass;

private:
	//!	The minimal height between each scan lines
	enum { _MIN_HEIGHT_BETWEEN_EACH_LINES = 4 };

	//!	The base lines type
	typedef Array< _short > ShortArray;

private:
	// The image region mask buffer ( determine how to sort the images )
	_byte*		mRegionMaskBuffer;

	// The Y-Position base line array ( low -> high )
	ShortArray	mBaseLines;

private:
	//!	Update the region mask buffer.
	//!	@param		rect		The image region.
	//!	@return		none.
	_void UpdateRegionMaskBuffer( const RectU& rect );
	//!	Test the region mask buffer.
	//!	@param		rect		The image region.
	//!	@return		True indicates all the region can be used.
	_ubool TestRegionMaskBuffer( const RectU& rect ) const;

	//!	Find the free x start position.
	//!	@param		y			The y position.
	//!	@return		The x position.
	_dword GetFreeXStartPosition( _dword y );

	//!	Cleanup the base lines.
	//!	@param		none.
	//!	@return		none.
	_void CleanupBaseLines( );

// TImageFiller interface
private:
	virtual _ubool	OnAddImage( _dword width, _dword height, RectU& rect ) override;
	virtual _ubool	OnFreeImage( const RectU& rect ) override;

public:
	ImageFillerScanLines( const PointU& size, const PointU& space );
	virtual ~ImageFillerScanLines( );

// IImageFiller Interface
public:
	virtual _void	ClearAllImages( ) override;
};

//----------------------------------------------------------------------------
// ImageFillerScanLines Implementation
//----------------------------------------------------------------------------

}