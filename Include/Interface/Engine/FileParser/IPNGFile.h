//! @file     IPNGFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPNGFile
//----------------------------------------------------------------------------

class IPNGFile : public IImageFile
{
public:
	//!	Get the background color.
	//!	@param		none.
	//!	@return		The background color.
	virtual const Color& GetBackgroundColor( ) const PURE;
};

}