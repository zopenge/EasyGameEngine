#pragma once

namespace EGE {

/// <summary>
/// A interval range class, in [min, max] range
/// </summary>
template <typename Type>
class Range {
public:
	//! The empty range.
	static const Range cNull;

public:
	//!	The minimal value
	Type mMinValue;
	//!	The maximal value
	Type mMaxValue;

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
	//!	Get the percentage in [0.0, 1.0].
	//!	@param		none.
	//!	@return		The percentage.
	_float GetPercentage() const;

	//!	Check whether it's in range.
	//!	@param		value	The value.
	//!	@return		True indicates it's in range.
	_ubool IsIn(Type value) const;
	//!	Check whether it's finish.
	//!	@param		none.
	//!	@return		True indicates it's finish.
	_ubool IsFinish() const;
};

template <typename Type>
Range<Type>::Range() {
	mMinValue = (Type)0;
	mMaxValue = (Type)0;
}

template <typename Type>
Range<Type>::Range(Type min_value, Type max_value) {
	mMinValue = min_value;
	mMaxValue = max_value;
}

template <typename Type>
Range<Type>::~Range() {
}

template <typename Type>
Range<Type>& Range<Type>::operator+=(const Range& range) {
	mMinValue += range.mMinValue;
	mMaxValue += range.mMaxValue;

	return *this;
}

template <typename Type>
Range<Type>& Range<Type>::operator-=(const Range& range) {
	mMinValue -= range.mMinValue;
	mMaxValue -= range.mMaxValue;

	return *this;
}

template <typename Type>
Type Range<Type>::GetLength() const {
	return mMaxValue - mMinValue;
}

template <typename Type>
_float Range<Type>::GetPercentage() const {
	return EGE_RATIO(mMinValue, mMaxValue);
}

template <typename Type>
_ubool Range<Type>::IsIn(Type value) const {
	if (mMinValue > value)
		return _false;

	if (mMaxValue < value)
		return _false;

	return _true;
}

template <typename Type>
_ubool Range<Type>::IsFinish() const {
	return mMinValue == mMaxValue;
}

} // namespace EGE