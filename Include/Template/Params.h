#pragma once

namespace EGE {

/// <summary>
/// The params.
/// </summary>
template <typename Type, _dword MaxNumber>
class Params {
public:
	static const Params cNull;

protected:
	//!	Params
	Type mValues[MaxNumber];

public:
	Params();
	Params(Type p1);
	Params(Type p1, Type p2);
	Params(Type p1, Type p2, Type p3);
	Params(Type p1, Type p2, Type p3, Type p4);
	Params(const Params& params);

public:
	//!	Copy operation function.
	Params& operator=(const Params& params);

	//! Get a const element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The const element reference.
	const Type& operator[](_dword index) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The mutable element reference.
	Type& operator[](_dword index);

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear();

	//!	Get the number of params.
	//!	@param		none.
	//!	@return		The number of params.
	_dword Number() const;
};

template <typename Type, _dword MaxNumber>
const Type& Params<Type, MaxNumber>::operator[](_dword index) const {
	EGE_ASSERT(index < MaxNumber);

	return mValues[index];
}

template <typename Type, _dword MaxNumber>
Type& Params<Type, MaxNumber>::operator[](_dword index) {
	EGE_ASSERT(index < MaxNumber);

	return mValues[index];
}

template <typename Type, _dword MaxNumber>
_dword Params<Type, MaxNumber>::Number() const {
	return MaxNumber;
}

} // namespace EGE
