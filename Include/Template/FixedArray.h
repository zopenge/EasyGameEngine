#pragma once

namespace EGE {

/// <summary>
/// This class is template container class, represents a array.
/// </summary>
template <typename Type, _dword _MAX_SIZE, typename Key = Type>
class FixedArray : public CountOf<> {
public:
	typedef Type ElementType;

public:
	//! The iterator of array class, provides ++ and -- operator to walk through the array.
	struct Iterator {
		//! The array reference.
		FixedArray<Type, _MAX_SIZE, Key>* mArray;
		//! The current index of the element.
		_dword mIndex;

		//! Constructor, create an iterator of the array.
		//! @param		none.
		Iterator()
		    : mArray(_null), mIndex(-1) {
		}
		//! Constructor, create an iterator of the array.
		//! @param		array		The array reference.
		//! @param		index		The current index of the element.
		Iterator(FixedArray<Type, _MAX_SIZE, Key>* array, _dword index)
		    : mArray(array), mIndex(index) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return (*mArray)[mIndex];
		}

		//! Decrease the iterator, point to the previous element of the array.
		//! @param		none
		_void operator--(_int) {
			mIndex--;
		}
		//! Increase the iterator, point to the next element of the array.
		//! @param		none
		_void operator++(_int) {
			mIndex++;
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mIndex < mArray->Number();
		}
	};

private:
	//! The memory pointer of the array.
	Type mElements[_MAX_SIZE];

public:
	//! Constructor, create an empty array.
	//! @param		none.
	FixedArray();
	//! Copy-Constructor, create an array by copy from another one.
	//! @param		array		The other array.
	FixedArray(const FixedArray<Type, _MAX_SIZE, Key>& array);
	//! Destructor, delete the array, and release the elements memory.
	//! @param		none.
	~FixedArray();

public:
	//! Copy elements from another array, and recreates memory to hold it.
	//! @param		array		The other array.
	//! @return		The reference of current array.
	FixedArray<Type, _MAX_SIZE, Key>& operator=(const FixedArray<Type, _MAX_SIZE, Key>& array);

	//! Append elements from another array, and recreates memory to hold it.
	//! @param		array		The other array.
	//! @return		The reference of current array.
	FixedArray<Type, _MAX_SIZE, Key>& operator+=(const FixedArray<Type, _MAX_SIZE, Key>& array);

	//! Get a const element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The const element reference.
	const Type& operator[](_dword index) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The mutable element reference.
	Type& operator[](_dword index);

	//! Get the max size of elements buffer in array.
	//! @param		none
	//! @return		The max size of elements buffer in array.
	_dword MaxSize() const;
	//!	Get the array buffer.
	//!	@param		none.
	//!	@return		The element buffer pointer.
	const Type* GetBuffer() const;

	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index from the array.
	//! @param		index		The index of the element in array.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	Type* Index(_dword index);

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator() const;
	//! Get an iterator by the index of an element.
	//! @param		index		The index of the element in array.
	//! @return		An iterator reference to the element.
	Iterator GetIterator(_dword index) const;

	//! Get a const element from the head of array.
	//! @param		none.
	//! @return		The const head element reference.
	const Type& GetHeadElement() const;
	//! Get a mutable element from the head of array.
	//! @param		none.
	//! @return		The mutable head element reference.
	Type& GetHeadElement();

	//! Get a const element from the tail of array.
	//! @param		none.
	//! @return		The const tail element reference.
	const Type& GetTailElement() const;
	//! Get a mutable element from the tail of array.
	//! @param		none.
	//! @return		The mutable tail element reference.
	Type& GetTailElement();

	//! Search an element by the key in the array.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator Search(const Key& key) const;
	//!	Search element by key in ascending way.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator SearchAscending(const Key& key) const;
	//!	Search element by key in descending way.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator SearchDescending(const Key& key) const;

	//!	Return the index of element by upper bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	//!	@return		The index of elements.
	_dword UpperBound(_int left, _int right, const Key& key) const;
	//!	Return the index of element by lower bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	_dword LowerBound(_int left, _int right, const Key& key) const;

	//! Append an element to the end of the array.
	//! @param		none.
	//! @return		The referenced element.
	Type& Append();
	//! Append an element to the end of the array.
	//! @param		element		The new element to be appended into.
	//! @return		The index of element in array, -1 indicates array is full.
	_dword Append(const Type& element);
	//! Insert an element into the array, the position is specified by an iterator.
	//! @param		element		The new element to be inserted into.
	//! @param		iterator	The iterator specifies a position.
	//! @return		The index of element in array, -1 indicates array is full.
	_dword Insert(const Type& element, const Iterator& iterator);
	//! Insert an element into the array, the position is specified by an index.
	//! @param		element		The new element to be inserted into.
	//! @param		index		The index specifies a position.
	//! @return		The index of element in array, -1 indicates array is full.
	_dword Insert(const Type& element, _dword index);
	//!	Insert element by key in ascending way.
	//! @param		element		The new element to be inserted into.
	//! @return		The index of element in array.
	_dword InsertAscending(const Type& element);
	//!	Insert element by key in descending way.
	//! @param		element		The new element to be inserted into.
	//! @return		The index of element in array.
	_dword InsertDescending(const Type& element);
	//! Remove an element from the array, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//! @return		True if the element is removed, false otherwise.
	_ubool Remove(Iterator& iterator);
	//! Remove an element from array.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool Remove(const Key& key);
	//! Remove an element from the array, the element is specified by an index.
	//! @param		index		The index of element in array.
	//! @return		The next iterator.
	Iterator RemoveByIndex(_dword index);
	//! Remove an element from array in ascending way.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool RemoveAscending(const Key& key);
	//! Remove an element from array in descending way.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool RemoveDescending(const Key& key);

	//!	Sort all elements in ascending way.
	//! @param		none.
	//! @return		none.
	_void SortAscending();
	//!	Sort all elements in descending way.
	//! @param		none.
	//! @return		none.
	_void SortDescending();

	//! Resize the array by create new memory and copy old element into it, the memory is larger than old array by grow size.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Resize(_dword number);

	//! Clear all elements in the array.
	//! @param		none.
	//!	@return		none.
	_void Clear();
};

template <typename Type, _dword _MAX_SIZE, typename Key>
FixedArray<Type, _MAX_SIZE, Key>::FixedArray() {
}

template <typename Type, _dword _MAX_SIZE, typename Key>
FixedArray<Type, _MAX_SIZE, Key>::FixedArray(const FixedArray<Type, _MAX_SIZE, Key>& array) {
	mNumber = array.mNumber;

	// Copy elements from another array
	for (_dword i = 0; i < mNumber; i++)
		mElements[i] = array.mElements[i];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
FixedArray<Type, _MAX_SIZE, Key>::~FixedArray() {
}

template <typename Type, _dword _MAX_SIZE, typename Key>
FixedArray<Type, _MAX_SIZE, Key>& FixedArray<Type, _MAX_SIZE, Key>::operator=(const FixedArray<Type, _MAX_SIZE, Key>& array) {
	mNumber = array.mNumber;

	// Copy elements from another array
	for (_dword i = 0; i < mNumber; i++)
		mElements[i] = array.mElements[i];

	return *this;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
FixedArray<Type, _MAX_SIZE, Key>& FixedArray<Type, _MAX_SIZE, Key>::operator+=(const FixedArray<Type, _MAX_SIZE, Key>& array) {
	for (_dword i = 0; i < array.Number(); i++)
		Append(array[i]);

	return *this;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
const Type& FixedArray<Type, _MAX_SIZE, Key>::operator[](_dword index) const {
	EGE_ASSERT(index < mNumber);

	return mElements[index];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
Type& FixedArray<Type, _MAX_SIZE, Key>::operator[](_dword index) {
	EGE_ASSERT(index < mNumber);

	return mElements[index];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::MaxSize() const {
	return _MAX_SIZE;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
const Type* FixedArray<Type, _MAX_SIZE, Key>::GetBuffer() const {
	return mElements;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
Type* FixedArray<Type, _MAX_SIZE, Key>::Index(_dword index) {
	if (index >= mNumber)
		return _null;

	return &(mElements[index]);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::GetHeadIterator() const {
	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, 0);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::GetTailIterator() const {
	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, mNumber - 1);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::GetIterator(_dword index) const {
	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, index);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
const Type& FixedArray<Type, _MAX_SIZE, Key>::GetHeadElement() const {
	EGE_ASSERT(mNumber > 0);

	return mElements[0];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
Type& FixedArray<Type, _MAX_SIZE, Key>::GetHeadElement() {
	EGE_ASSERT(mNumber > 0);

	return mElements[0];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
const Type& FixedArray<Type, _MAX_SIZE, Key>::GetTailElement() const {
	EGE_ASSERT(mNumber > 0);

	return mElements[mNumber - 1];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
Type& FixedArray<Type, _MAX_SIZE, Key>::GetTailElement() {
	EGE_ASSERT(mNumber > 0);

	return mElements[mNumber - 1];
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::Search(const Key& key) const {
	for (_dword i = 0; i < mNumber; i++) {
		if ((const Key&)mElements[i] == key)
			return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, i);
	}

	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, -1);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::SearchAscending(const Key& key) const {
	// Search elements in ascending way
	_int index = Algorithm::BinarySearch<Type, Key, Compare<Key>>(mElements, mNumber, key);
	if (index == -1)
		return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, -1);

	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, index);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::SearchDescending(const Key& key) const {
	// Search elements in descending way
	_int index = Algorithm::BinarySearch<Type, Key, NotCompare<Key>>(mElements, mNumber, key);
	if (index == -1)
		return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, -1);

	return Iterator((FixedArray<Type, _MAX_SIZE, Key>*)this, index);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::UpperBound(_int left, _int right, const Key& key) const {
	return Algorithm::BinaryBound<Type, Key, Compare<Key>>(mElements, left, right, key);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::LowerBound(_int left, _int right, const Key& key) const {
	return Algorithm::BinaryBound<Type, Key, NotCompare<Key>>(mElements, left, right, key);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
Type& FixedArray<Type, _MAX_SIZE, Key>::Append() {
	EGE_ASSERT(mNumber < _MAX_SIZE);

	// Assign the element
	Type& element = mElements[mNumber];

	// Increase the element number
	CountOf<>::Increase();

	return element;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::Append(const Type& element) {
	if (mNumber >= _MAX_SIZE)
		return -1;

	// Assign the element
	mElements[mNumber] = element;

	// Increase the element number
	return CountOf<>::Increase();
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::Insert(const Type& element, const Iterator& iterator) {
	return Insert(element, iterator.mIndex);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::Insert(const Type& element, _dword index) {
	EGE_ASSERT(index <= mNumber);

	// Resize the array when necessary.
	if (mNumber >= _MAX_SIZE)
		return -1;

	// Move elements after the index backward, make a place for the new element.
	for (_dword i = 0; i < mNumber - index; i++)
		mElements[mNumber - i] = mElements[mNumber - i - 1];

	// Assign the element.
	mElements[index] = element;

	// Increase the element number.
	CountOf<>::Increase();

	return index;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::InsertAscending(const Type& element) {
	if (mNumber == 0) {
		Append(element);

		return 0;
	} else {
		_dword index = UpperBound(0, mNumber - 1, (const Key&)element);

		Insert(element, index);

		return index;
	}
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_dword FixedArray<Type, _MAX_SIZE, Key>::InsertDescending(const Type& element) {
	if (mNumber == 0) {
		Append(element);

		return 0;
	} else {
		_dword index = LowerBound(0, mNumber - 1, (const Key&)element);

		Insert(element, index);

		return index;
	}
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_ubool FixedArray<Type, _MAX_SIZE, Key>::Remove(Iterator& iterator) {
	_ubool retval = Remove(iterator.mIndex);

	iterator.mIndex = -1;

	return retval;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
typename FixedArray<Type, _MAX_SIZE, Key>::Iterator FixedArray<Type, _MAX_SIZE, Key>::RemoveByIndex(_dword index) {
	if (index >= mNumber)
		return Iterator();

	// Move elements after the index forward, replace the deleted one.
	for (_dword i = index; i < mNumber - 1 && i < _MAX_SIZE - 1; i++)
		mElements[i] = mElements[i + 1];

	// Decrease the element number.
	CountOf<>::Decrease();

	// Feedback the next iterator
	return index < mNumber ? Iterator(this, index) : Iterator();
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_ubool FixedArray<Type, _MAX_SIZE, Key>::Remove(const Key& key) {
	Iterator it = Search(key);
	if (it.IsValid() == _false)
		return _false;

	RemoveByIndex(it.mIndex);

	return _true;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_ubool FixedArray<Type, _MAX_SIZE, Key>::RemoveAscending(const Key& key) {
	Iterator it = SearchAscending(key);
	if (it.IsValid() == _false)
		return _false;

	RemoveByIndex(it.mIndex);

	return _true;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_ubool FixedArray<Type, _MAX_SIZE, Key>::RemoveDescending(const Key& key) {
	Iterator it = SearchDescending(key);
	if (it.IsValid() == _false)
		return _false;

	RemoveByIndex(it.mIndex);

	return _true;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_void FixedArray<Type, _MAX_SIZE, Key>::SortAscending() {
	if (mNumber == 0)
		return;

	Algorithm::QuickSort<Type, Greater<Key>, Less<Key>>(mElements, 0, mNumber - 1);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_void FixedArray<Type, _MAX_SIZE, Key>::SortDescending() {
	if (mNumber == 0)
		return;

	Algorithm::QuickSort<Type, Less<Key>, Greater<Key>>(mElements, 0, mNumber - 1);
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_void FixedArray<Type, _MAX_SIZE, Key>::Resize(_dword number) {
	EGE_ASSERT(number <= _MAX_SIZE);

	mNumber = number;
}

template <typename Type, _dword _MAX_SIZE, typename Key>
_void FixedArray<Type, _MAX_SIZE, Key>::Clear() {
	CountOf<>::Clear();
}

} // namespace EGE
