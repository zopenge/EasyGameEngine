#pragma once

namespace EGE {

/// <summary>
///	The data field with offset and number, range is in [base + offset, base + offset + number).
/// </summary>
template <typename Type>
class DataField {
public:
	//! The empty field.
	static const DataField cNull;

private:
	//!	The offset
	Type mOffset;
	//!	The total number
	Type mNumber;

public:
	DataField();
	DataField(Type offset, Type number);
	~DataField();

public:
	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear();

	//!	Initialize.
	_void Init(Type offset, Type number);

	//!	Get start offset of the data field.
	//!	@param		none.
	//!	@return		The start offset of the data field.
	Type GetOffset() const;
	//!	Get end offset of the data field.
	//!	@param		none.
	//!	@return		The end offset of the data field.
	Type GetEndOffset() const;
	//!	Get number of the data field.
	//!	@param		none.
	//!	@return		The number of the data field.
	Type GetNumber() const;

	//!	Check whether can combine.
	_ubool CanCombine(const DataField& data_field) const;
	//!	Combine.
	DataField& Combine(const DataField& data_field);

	_ubool operator==(const DataField& data_field) const;
	_ubool operator!=(const DataField& data_field) const;
};

template <typename Type>
DataField<Type>::DataField() {
}

template <typename Type>
DataField<Type>::DataField(Type offset, Type number)
    : mOffset(offset), mNumber(number) {
}

template <typename Type>
DataField<Type>::~DataField() {
}

template <typename Type>
_void DataField<Type>::Clear() {
	mOffset = 0;
	mNumber = 0;
}

template <typename Type>
_void DataField<Type>::Init(Type offset, Type number) {
	mOffset = offset;
	mNumber = number;
}

template <typename Type>
Type DataField<Type>::GetOffset() const {
	return mOffset;
}

template <typename Type>
Type DataField<Type>::GetEndOffset() const {
	return mOffset + mNumber;
}

template <typename Type>
Type DataField<Type>::GetNumber() const {
	return mNumber;
}

template <typename Type>
_ubool DataField<Type>::CanCombine(const DataField& data_field) const {
	if (mOffset == data_field.mOffset && mNumber == data_field.mNumber)
		return _true;

	if (mOffset == data_field.GetEndOffset())
		return _true;

	if (GetEndOffset() == data_field.mOffset)
		return _true;

	return _false;
}

template <typename Type>
DataField<Type>& DataField<Type>::Combine(const DataField& data_field) {
	if (CanCombine(data_field)) {
		if (mOffset != data_field.mOffset || mNumber != data_field.mNumber) {
			if (mOffset > data_field.mOffset)
				mOffset = data_field.mOffset;

			mNumber += data_field.mNumber;
		}
	}

	return *this;
}

template <typename Type>
_ubool DataField<Type>::operator==(const DataField& data_field) const {
	if (mOffset != data_field.mOffset)
		return _false;

	if (mNumber != data_field.mNumber)
		return _false;

	return _true;
}

template <typename Type>
_ubool DataField<Type>::operator!=(const DataField& data_field) const {
	if (mOffset != data_field.mOffset)
		return _true;

	if (mNumber != data_field.mNumber)
		return _true;

	return _false;
}

} // namespace EGE