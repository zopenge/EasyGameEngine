//! @file     CountOf.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// CountOf
//----------------------------------------------------------------------------

template <typename Type = _dword>
class CountOf {
protected:
	//! The current number of elements
	Type mNumber;

protected:
	CountOf(Type number = 0)
	    : mNumber(number) {
	}

protected:
	//!	Increase number of elements.
	//!	@param		none.
	//!	@return		The previous number of elements.
	Type Increase() {
		return mNumber++;
	}

	//!	Decrease number of elements.
	//!	@param		none.
	//!	@return		The previous number of elements.
	Type Decrease() {
		EGE_ASSERT(mNumber != 0);

		return mNumber--;
	}

	//!	Clear elements.
	//!	@param		none.
	//!	@return		none.
	_void Clear() {
		mNumber = 0;
	}

public:
	//!	Get number of elements.
	//!	@param		none.
	//!	@return		The number of elements.
	Type Number() const {
		return mNumber;
	}
};

} // namespace EGE