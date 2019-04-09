#pragma once

namespace EGE {

/// <summary>
/// The progression range.
/// </summary>
template <typename Type>
class Progression {
public:
	//! The empty range.
	static const Progression cNull;

private:
	//!	The bounds of progression [ Current, Max ]
	Type mCurrentProgression;
	Type mMaxProgression;

public:
	Progression();
	Progression(Type cur_value, Type max_value);
	~Progression();

public:
	//! Update progression.
	//! @param		progression	The other progression.
	//! @return		The reference of progression.
	Progression<Type>& operator+=(const Progression<Type>& progression);

	//!	Get the current progression.
	//!	@param		none.
	//!	@return		The current progression.
	Type GetCurProgression() const;
	//!	Get the max progression.
	//!	@param		none.
	//!	@return		The max progression.
	Type GetMaxProgression() const;

	//!	Clear the progression.
	//!	@param		none.
	//!	@return		none.
	_void ClearProgression();
	//!	Begin the progression.
	//!	@param		maxvalue	The max progression value.
	//! @return		none.
	_void BeginProgression(Type maxvalue);

	//!	Update the current progression.
	//!	@param		offset		The offset of progression.
	//!	@return		The latest progression.
	Type UpdateCurProgression(Type offset);
	//!	Update the max progression.
	//!	@param		offset		The offset of progression.
	//!	@return		The latest progression.
	Type UpdateMaxProgression(Type offset);

	//!	Set the current progression percentage.
	//!	@param		percentage	The current progression percentage.
	//!	@return		none.
	_void SetCurProgressionPercentage(_float percentage);
	//!	Get the current progression percentage.
	//!	@param		none.
	//!	@return		The current progression percentage.
	_float GetCurProgressionPercentage() const;

	//!	Check whether it has completed.
	//!	@param		none.
	//!	@return		True indicates it has completed.
	_ubool HasCompleted() const;
};

template <typename Type>
Progression<Type>::Progression() {
	mCurrentProgression = (Type)0;
	mMaxProgression = (Type)0;
}

template <typename Type>
Progression<Type>::Progression(Type cur_value, Type max_value) {
	EGE_ASSERT(cur_value <= max_value);

	mCurrentProgression = cur_value;
	mMaxProgression = max_value;
}

template <typename Type>
Progression<Type>::~Progression() {
}

template <typename Type>
Progression<Type>& Progression<Type>::operator+=(const Progression<Type>& progression) {
	mCurrentProgression += progression.mCurrentProgression;
	mMaxProgression += progression.mMaxProgression;

	return *this;
}

template <typename Type>
Type Progression<Type>::GetCurProgression() const {
	return mCurrentProgression;
}

template <typename Type>
Type Progression<Type>::GetMaxProgression() const {
	return mMaxProgression;
}

template <typename Type>
_void Progression<Type>::ClearProgression() {
	mCurrentProgression = (Type)0;
}

template <typename Type>
Type Progression<Type>::UpdateCurProgression(Type offset) {
	// Update the current progression
	mCurrentProgression = MIN(mCurrentProgression + offset, mMaxProgression);

	return mCurrentProgression;
}

template <typename Type>
Type Progression<Type>::UpdateMaxProgression(Type offset) {
	// Update the max progression
	mMaxProgression += offset;

	return mMaxProgression;
}

template <typename Type>
_void Progression<Type>::BeginProgression(Type maxvalue) {
	mCurrentProgression = (Type)0;
	mMaxProgression = maxvalue;
}

template <typename Type>
_void Progression<Type>::SetCurProgressionPercentage(_float percentage) {
	if (mMaxProgression == (Type)0)
		return;

	// Fix the percentage
	_float fixed_percentage = CLAMP(percentage, 0.0f, 1.0f);

	// Get the current progression by percentage
	Type currentprogression = Type(_float(mMaxProgression) * fixed_percentage);

	// Update the current progression
	mCurrentProgression = currentprogression;
}

template <typename Type>
_float Progression<Type>::GetCurProgressionPercentage() const {
	if (mMaxProgression == (Type)0)
		return 0.0f;

	return EGE_RATIO(mCurrentProgression, mMaxProgression);
}

template <typename Type>
_ubool Progression<Type>::HasCompleted() const {
	return mCurrentProgression == mMaxProgression;
}

} // namespace EGE
