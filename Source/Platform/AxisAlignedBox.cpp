//! @file     AxisAlignedBox.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const AxisAlignedBox AxisAlignedBox::cNullBox( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const AxisAlignedBox AxisAlignedBox::cInitBox( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );
const AxisAlignedBox AxisAlignedBox::cMaxBox( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );

//----------------------------------------------------------------------------
// AxisAlignedBox Implementation
//----------------------------------------------------------------------------

AxisAlignedBox AxisAlignedBox::Union( const AxisAlignedBox& box1, const AxisAlignedBox& box2 )
{
	AxisAlignedBox box;
	box.mMinVector.x = MIN( box1.mMinVector.x, box2.mMinVector.x );
	box.mMinVector.y = MIN( box1.mMinVector.y, box2.mMinVector.y );
	box.mMinVector.z = MIN( box1.mMinVector.z, box2.mMinVector.z );
	box.mMaxVector.x = MAX( box1.mMaxVector.x, box2.mMaxVector.x );
	box.mMaxVector.y = MAX( box1.mMaxVector.y, box2.mMaxVector.y );
	box.mMaxVector.z = MAX( box1.mMaxVector.z, box2.mMaxVector.z );

	return box;
}
