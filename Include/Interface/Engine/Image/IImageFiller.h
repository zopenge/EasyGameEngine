//! @file     IImageFiller.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IImageFiller
//----------------------------------------------------------------------------

class IImageFiller : public IObject
{
public:
	//!	Get the image size.
	//!	@param		none.
	//!	@return		The image size.
	virtual const PointU& GetSize( ) const PURE;
	//!	Get the area area size.
	//!	@param		none.
	//!	@return		The area size.
	virtual _dword GetAreaSize( ) const PURE;
	//!	Get the free area size.
	//!	@param		none.
	//!	@return		The free area size.
	virtual _dword GetFreeAreaSize( ) const PURE;
	//!	Get the fill rate.
	//!	@param		none.
	//!	@return		The fill rate in percentage.
	virtual _float GetFillRate( ) const PURE;

	//!	Set the space.
	//!	@param		space	The space in pixel between images.
	//!	@return		none.
	virtual _void SetSpace( const PointU& space ) PURE;
	//!	Get the space.
	//!	@param		none.
	//!	@return		The space in pixel between images.
	virtual const PointU& GetSpace( ) const PURE;

	//!	Clear all images.
	//!	@param		none.
	//! @return		none.
	virtual _void ClearAllImages( ) PURE;
	//!	Add image block.
	//!	@param		size	The image size.
	//!	@param		rect	The image region in filler.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddImage( const PointU& size, RectU& rect ) PURE;
	//!	Add image block.
	//!	@param		size	The image size.
	//!	@param		rect	The image region in filler.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddImage( const PointU& size, RectI& rect ) PURE;
	//!	Free image block.
	//!	@param		rect	The image region in filler.
	//! @return		True indicates free successful.
	virtual _ubool FreeImage( const RectU& rect ) PURE;
	//!	Free image block.
	//!	@param		rect	The image region in filler.
	//! @return		True indicates free successful.
	virtual _ubool FreeImage( const RectI& rect ) PURE;
};

}