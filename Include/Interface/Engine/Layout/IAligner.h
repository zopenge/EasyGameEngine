//! @file     IAligner.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAligner
//----------------------------------------------------------------------------

class IAligner : public IObject
{
public:
 	//!	Horizontal align the multiple measurable objects.
	//!	@param		objects		The measurable objects.
 	//!	@param		alignment	The object alignment, @see _ALIGNMENT.
	//!	@param		margin_size	The margin size will plus to all objects.
 	//!	@param		space		The min space size between objects.
 	//!	@param		size		The size of region.
 	//!	@param		flags		The aligner flags, @see _ALIGNER_FLAGS.
 	//! @return		none.
	virtual _void HorzAlignObject( Array< IMeasurableObjectRef >& objects, const FlagsObject& alignment, const Vector2& margin_size, const Vector2& space, const Vector2& size, const FlagsObject& flags, RectF* real_size, Line2DArray* underlinearray ) PURE;
};

}