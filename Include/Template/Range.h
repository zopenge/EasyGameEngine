#pragma once

namespace EGE {

/// <summary>
/// A interval range class, in [mStartIndex, mEndIndex] range
/// </summary>
template <typename Type>
class Range {
public:
	//! The empty range.
	static const Range cNull;

public:
	//!	The minimal value
	Type mStartIndex;
	//!	The maximal value
	Type mEndIndex;

public:
	Range();
	Range(Type min_value, Type max_value);
	~Range();

public:
	//! Add range.
	//! @param		range	The other range.
	//! @return		The reference of range.
	Range& operator+=(const Range& range);
	//! Sub range.
	//! @param		range	The other range.
	//! @return		The reference of range.
	Range& operator-=(const Range& range);

	//!	Get length of the range.
	//!	@param		none.
	//!	@return		The length of the range.
	Type GetLength() const;

	//!	Check whether it's in range.
	//!	@param		value	The value.
	//!	@return		True indicates it's in range.
	_ubool IsIn(Type value) const;
};

template <typename Type>
Range<Type>::Range() {
	mStartIndex = (Type)0;
	mEndIndex = (Type)0;
}

template <typename Type>
Range<Type>::Range(Type min_value, Type max_value) {
	mStartIndex = min_value;
	mEndIndex = max_value;
}

template <typename Type>
Range<Type>::~Range() {
}

template <typename Type>
Range<Type>& Range<Type>::operator+=(const Range& range) {
	mStartIndex += range.mStartIndex;
	mEndIndex += range.mEndIndex;

	return *this;
}

template <typename Type>
Range<Type>& Range<Type>::operator-=(const Range& range) {
	mStartIndex -= range.mStartIndex;
	mEndIndex -= range.mEndIndex;

	return *this;
}

template <typename Type>
Type Range<Type>::GetLength() const {
	return mEndIndex - mStartIndex + 1;
}

template <typename Type>
_ubool Range<Type>::IsIn(Type value) const {
	if (value < mStartIndex)
		return _false;

	if (value > mEndIndex)
		return _false;

	return _true;
}

} // namespace EGE