//! @file     IGraphicFilter.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/06/17

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicFilter
//----------------------------------------------------------------------------

class IGraphicFilter : public IObject
{
public:
	//!	Process the blur effect filter.
	//!	@param		canvas		The target canvas to save the filter result.
	//!	@param		step_size	The step size.
	//!	@param		surface		The source surface to filter.
	//!	@return		none.
	virtual _void ProcessBlurEffect( IGraphicCanvas* canvas, const PointF& step_size, IGraphicSurface* surface ) PURE;
};

}