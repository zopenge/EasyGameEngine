//! @file     Algorithm.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Algorithm
//----------------------------------------------------------------------------

class Algorithm {
public:
	//!	Return the index of element by lower/upper bound within a range in binary search way.
	//!	@param		elements	The element array.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	template <typename Type, typename Key, typename KeyConverter, typename SortCompareFunc, typename BoundCompareFunc>
	static _dword binaryBound(const Type elements[], _int left, _int right, const Key& key);
	//!	Search the element by key by ascending/descending in binary search way.
	//!	@param		elements	The element array.
	//!	@param		number		The element number.
	//! @param		key			The key of element to be searched.
	//!	@return		The index of element in array.
	template <typename Type, typename Key, typename KeyConverter, typename CompareFunc>
	static _int binarySearch(const Type elements[], _int number, const Key& key);

	//!	Sort all elements in ascending/descending way.
	//!	@param		elements	The element array.
	//!	@param		left		The start index of element in array.
	//!	@param		right		The end index of element in array.
	//! @return		none.
	template <typename Type, typename Key, typename KeyConverter, typename GreaterFunc, typename LessFunc>
	static _void quickSort(Type elements[], _int left, _int right);
	//!	Sort all elements in ascending/descending way.
	//!	@param		elements	The element array.
	//!	@param		left		The start index of element in array.
	//!	@param		right		The end index of element in array.
	//! @return		none.
	template <typename Type, typename Key, typename KeyConverter, typename CompareFunc>
	static _void quickSort(Type elements[], _int left, _int right);
};

//----------------------------------------------------------------------------
// Algorithm Implementation
//----------------------------------------------------------------------------

template <typename Type, typename Key, typename KeyConverter, typename SortCompareFunc, typename BoundCompareFunc>
_dword Algorithm::binaryBound(const Type elements[], _int left, _int right, const Key& key) {
	_int i = left, j = right;

	while (i < j - 1) {
		_int m = (i + j) / 2;

		_int ret = SortCompareFunc()(KeyConverter()(elements[m]), key);
		if (ret == 0)
			return m;

		if (ret < 0)
			i = m;
		else
			j = m;
	}

	_dword index = -1;

	// the i,j test sequence or cause some bug if the SortCompareFunc is not equal BoundCompareFunc
	if (BoundCompareFunc()(KeyConverter()(elements[i]), key) > 0)
		index = i;
	else if (BoundCompareFunc()(KeyConverter()(elements[j]), key) > 0)
		index = j;

	return index;
}

template <typename Type, typename Key, typename KeyConverter, typename CompareFunc>
_int Algorithm::binarySearch(const Type elements[], _int number, const Key& key) {
	if (number <= 0)
		return -1;

	_int i = 0, j = number - 1;

	while (i < j - 1) {
		_int m = (i + j) / 2;

		_int ret = CompareFunc()(KeyConverter()(elements[m]), key);
		if (ret == 0)
			return m;

		if (ret < 0)
			i = m;
		else
			j = m;
	}

	if (i >= number || j >= number)
		return -1;

	if (CompareFunc()(KeyConverter()(elements[i]), key) == 0)
		return i;

	if (CompareFunc()(KeyConverter()(elements[j]), key) == 0)
		return j;

	return -1;
}

template <typename Type, typename Key, typename KeyConverter, typename GreaterFunc, typename LessFunc>
_void Algorithm::quickSort(Type elements[], _int left, _int right) {
	if (left >= right)
		return;

	_int i = left - 1, j = right + 1, c = (left + right) / 2;

	Key center = KeyConverter()(elements[c]);

	while (_true) {
		// Find the element that less than center from left to right.
		while (i < right && LessFunc()(KeyConverter()(elements[++i]), center))
			;
		// Find the element that greater than center from right to left.
		while (j > left && GreaterFunc()(KeyConverter()(elements[--j]), center))
			;

		if (i >= j)
			break;

		// Swap two elements.
		Type element = elements[i];
		elements[i] = elements[j];
		elements[j] = element;
	}

	quickSort<Type, Key, KeyConverter, GreaterFunc, LessFunc>(elements, left, i - 1);
	quickSort<Type, Key, KeyConverter, GreaterFunc, LessFunc>(elements, j + 1, right);
}

template <typename Type, typename Key, typename KeyConverter, typename CompareFunc>
_void Algorithm::quickSort(Type elements[], _int left, _int right) {
	if (left >= right)
		return;

	_int i = left - 1, j = right + 1, c = (left + right) / 2;

	Key center = KeyConverter()(elements[c]);

	while (_true) {
		// Find the element that less than center from left to right.
		while (i < right && CompareFunc()(KeyConverter()(elements[++i]), center) < 0)
			;
		// Find the element that greater than center from right to left.
		while (j > left && CompareFunc()(KeyConverter()(elements[--j]), center) > 0)
			;

		if (i >= j)
			break;

		// Swap two elements.
		Type element = elements[i];
		elements[i] = elements[j];
		elements[j] = element;
	}

	quickSort<Type, Key, KeyConverter, CompareFunc>(elements, left, i - 1);
	quickSort<Type, Key, KeyConverter, CompareFunc>(elements, j + 1, right);
}

} // namespace EGE