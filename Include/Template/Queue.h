//! @file     Queue.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Queue
//----------------------------------------------------------------------------

//! This class is template container class, represents a queue, can insert at front and remove from rear.

//! A queue allocates a buffer to store all elements, the buffer will auto enlarge to hold more elements.
//! Each elements are adjacent in memory as a ring, can be accessed by index base from zero.<br>
//! Template parameter "Type" defines the element type storaged in the queue.<br>
//! For example, Queue< ClassA, _dword > defines a queue stores ClassA element, and access it
//! by _dword, means ClassA has a overload operator with _dword ( ==, !=, > and < etc ), or it can convert to _dword.
template <typename Type>
class Queue : public CountOf<> {
public:
	//! The iterator of queue class, provides ++ and -- operator to walk through the queue.
	struct Iterator {
		//! The queue reference.
		Queue<Type>* mQueue;
		//! The current index of the element.
		_dword index;

		//! Constructor, create an iterator of the queue.
		//! @param		queue	The queue reference.
		//! @param		index		The current index of the element.
		Iterator(Queue<Type>* queue, _dword index)
		    : mQueue(queue), index(index) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return mQueue->mElements[index];
		}

		//! Increase the iterator, point to the next element of the queue.
		//! @param		none
		_void operator++(_int) {
			index = (index + 1) % (mQueue->mAllocedSize + 1);
		}
		//! decrease the iterator, point to the previous element of the queue.
		//! @param		none
		_void operator--(_int) {
			index = (mQueue->mAllocedSize + index) % (mQueue->mAllocedSize + 1);
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			if (mQueue->mFront <= mQueue->mRear)
				return index >= mQueue->mFront && index < mQueue->mRear;
			else
				return (index < mQueue->mRear) || (index >= mQueue->mFront && index <= mQueue->mAllocedSize);
		}
	};

private:
	//! The allocated size of the queue in number of element.
	_dword mAllocedSize;
	//! The front index of queue.
	_dword mFront;
	//! The rear index of queue.
	_dword mRear;
	//! The memory pointer of the queue.
	Type* mElements;

private:
	//! Grow.
	//! @param		none.
	//!	@return		none.
	_void Grow();

public:
	//! Constructor, create an empty queue.
	//! @param		none.
	Queue();
	//! Copy-Constructor, create a queue by copy from another one.
	//! @param		queue	The other queue.
	Queue(const Queue<Type>& queue);
	//! Destructor, delete the queue, and release the elements memory.
	//! @param		none
	~Queue();

public:
	//! Copy elements from another queue, and recreates memory to hold it.
	//! @param		queue	The other queue.
	//! @return		The reference of current queue.
	Queue<Type>& operator=(const Queue<Type>& queue);

	//! Get a const element reference by index.
	//! @param		index		The index of the element in queue.
	//! @return		The const element reference.
	const Type& operator[](_dword index) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in queue.
	//! @return		The mutable element reference.
	Type& operator[](_dword index);

	//! Get the front element in queue.
	//! @param		none
	//! @return		The element reference of the front element.
	Type& Front();
	//! Get the front element in queue.
	//! @param		none
	//! @return		The element reference of the front element.
	const Type& Front() const;
	//! Get the rear element in queue.
	//! @param		none
	//! @return		The element reference of the rear element.
	Type& Rear();
	//! Get the rear element in queue.
	//! @param		none
	//! @return		The element reference of the rear element.
	const Type& Rear() const;

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator() const;
	//! Get an iterator by the index of an element.
	//! @param		index		The index of the element in queue.
	//! @return		An iterator reference to the element.
	Iterator GetIterator(_dword index) const;

	//! Get a const element from the head of queue.
	//! @param		none.
	//! @return		The const head element reference.
	const Type& GetHeadElement() const;
	//! Get a mutable element from the head of queue.
	//! @param		none.
	//! @return		The mutable head element reference.
	Type& GetHeadElement();

	//! Get a const element from the tail of queue.
	//! @param		none.
	//! @return		The const tail element reference.
	const Type& GetTailElement() const;
	//! Get a mutable element from the tail of queue.
	//! @param		none.
	//! @return		The mutable tail element reference.
	Type& GetTailElement();

	//! Search an element by the key in the queue.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in queue.
	template <typename Key>
	Iterator Search(const Key& key) const;

	//! Add an element at front of the queue.
	//! @param		element		The new element to be push into.
	//!	@return		none.
	_void EnqueueAtFront(const Type& element);
	//! Add an element at rear of the queue.
	//! @param		element		The new element to be push into.
	//!	@return		none.
	_void Enqueue(const Type& element);
	//! Remove an element at front of the queue.
	//! @param		none.
	//!	@return		none.
	_ubool Dequeue(Type& element);
	//! Remove an element by an iterator the queue.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		The next iterator.
	Iterator Remove(const Iterator& iterator);

	//! Initialize.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Init(_dword number);
	//! Resize the queue by create new memory and copy old element into it, the memory is larger than older by grow size.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Resize(_dword number);

	//! Clear the queue, delete all elements and free the memory.
	//! @param		freememory	If free the memory used by array.
	//!	@return		none.
	_void Clear(_ubool freememory = _false);
};

//----------------------------------------------------------------------------
// Queue Implementation
//----------------------------------------------------------------------------

template <typename Type>
Queue<Type>::Queue() {
	mAllocedSize = 0;
	mNumber = 0;
	mFront = 0;
	mRear = 0;
	mElements = _null;
}

template <typename Type>
Queue<Type>::Queue(const Queue<Type>& queue) {
	mAllocedSize = queue.mAllocedSize;
	mNumber = queue.mNumber;
	mFront = 0;
	mRear = queue.mNumber;
	mElements = _null;

	if (mAllocedSize > 0) {
		mElements = new Type[mAllocedSize + 1];

		// Copy elements one by one, execute operator = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			mElements[i] = queue.mElements[(queue.mFront + i) % (mAllocedSize + 1)];
	}
}

template <typename Type>
Queue<Type>::~Queue() {
	// Release queue memory.
	EGE_DELETE_ARRAY(mElements);
}

template <typename Type>
_void Queue<Type>::Grow() {
	// Increase the allocated size
	_dword alloced_size = Math::Max(mAllocedSize + 1, mAllocedSize * 2);

	Resize(alloced_size);
}

template <typename Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& queue) {
	Clear(_true);

	mAllocedSize = queue.mAllocedSize;
	mNumber = queue.mNumber;
	mFront = 0;
	mRear = queue.mNumber;
	mElements = _null;

	if (mAllocedSize > 0) {
		mElements = new Type[mAllocedSize + 1];

		// Copy elements one by one, execute operate = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			mElements[i] = queue.mElements[(queue.mFront + i) % (mAllocedSize + 1)];
	}

	return *this;
}

template <typename Type>
const Type& Queue<Type>::operator[](_dword index) const {
	return mElements[(mFront + index) % (mAllocedSize + 1)];
}

template <typename Type>
Type& Queue<Type>::operator[](_dword index) {
	return mElements[(mFront + index) % (mAllocedSize + 1)];
}

template <typename Type>
Type& Queue<Type>::Front() {
	EGE_ASSERT(mFront <= mAllocedSize);

	return mElements[mFront];
}

template <typename Type>
const Type& Queue<Type>::Front() const {
	EGE_ASSERT(mFront <= mAllocedSize);

	return mElements[mFront];
}

template <typename Type>
Type& Queue<Type>::Rear() {
	EGE_ASSERT(mRear <= mAllocedSize);

	return mElements[(mRear + mAllocedSize) % (mAllocedSize + 1)];
}

template <typename Type>
const Type& Queue<Type>::Rear() const {
	EGE_ASSERT(mRear <= mAllocedSize);

	return mElements[(mRear + mAllocedSize) % (mAllocedSize + 1)];
}

template <typename Type>
typename Queue<Type>::Iterator Queue<Type>::GetHeadIterator() const {
	return Iterator((Queue<Type>*)this, mFront);
}

template <typename Type>
typename Queue<Type>::Iterator Queue<Type>::GetTailIterator() const {
	return Iterator((Queue<Type>*)this, mRear - 1);
}

template <typename Type>
typename Queue<Type>::Iterator Queue<Type>::GetIterator(_dword index) const {
	return Iterator((Queue<Type>*)this, (mFront + index) % (mAllocedSize + 1));
}

template <typename Type>
const Type& Queue<Type>::GetHeadElement() const {
	EGE_ASSERT(mNumber > 0);

	return mElements[mFront];
}

template <typename Type>
Type& Queue<Type>::GetHeadElement() {
	EGE_ASSERT(mNumber > 0);

	return mElements[mFront];
}

template <typename Type>
const Type& Queue<Type>::GetTailElement() const {
	EGE_ASSERT(mNumber > 0);

	return mElements[mRear - 1];
}

template <typename Type>
Type& Queue<Type>::GetTailElement() {
	EGE_ASSERT(mNumber > 0);

	return mElements[mRear - 1];
}

template <typename Type>
template <typename Key>
typename Queue<Type>::Iterator Queue<Type>::Search(const Key& key) const {
	for (Iterator it = GetHeadIterator(); it.IsValid(); it++) {
		if (((const Key&)(const Type&)it) == key)
			return it;
	}

	return Iterator((Queue<Type>*)this, -1);
}

template <typename Type>
_void Queue<Type>::EnqueueAtFront(const Type& element) {
	// Resize the queue when necessary.
	if (mNumber == mAllocedSize)
		Grow();

	// Move the rear index.
	mRear = (mRear + 1) % (mAllocedSize + 1);

	// Increase the element number.
	CountOf<>::Increase();

	// Move all elements backwards
	for (_dword i = Number() - 1; i != 0; i--)
		mElements[i] = mElements[i - 1];

	// Insert element
	mElements[mFront] = element;
}

template <typename Type>
_void Queue<Type>::Enqueue(const Type& element) {
	// Resize the queue when necessary.
	if (mNumber == mAllocedSize)
		Grow();

	// Assign the element.
	mElements[mRear] = element;

	// Move the rear index.
	mRear = (mRear + 1) % (mAllocedSize + 1);

	// Increase the element number.
	CountOf<>::Increase();
}

template <typename Type>
_ubool Queue<Type>::Dequeue(Type& element) {
	if (Number() == 0)
		return _false;

	element = mElements[mFront];

	// Move the front index.
	mFront = (mFront + 1) % (mAllocedSize + 1);

	// Decrease the element number.
	CountOf<>::Decrease();

	return _true;
}

template <typename Type>
typename Queue<Type>::Iterator Queue<Type>::Remove(const Iterator& iterator) {
	EGE_ASSERT(iterator.IsValid());

	Iterator temp = iterator;
	Iterator next_it = iterator;
	next_it++;

	_dword index = 0;

	do {
		index = temp.index;
		temp++;

		// Move element forward.
		mElements[index] = mElements[temp.index];
	} while (temp.IsValid());

	// Set queue rear.
	mRear = index;

	// Decrease the element number.
	CountOf<>::Decrease();

	return next_it;
}

template <typename Type>
_void Queue<Type>::Init(_dword number) {
	mAllocedSize = number;
	mNumber = number;
	mFront = 0;
	mRear = number;

	EGE_DELETE_ARRAY(mElements);

	if (mAllocedSize > 0)
		mElements = new Type[mAllocedSize + 1];
}

template <typename Type>
_void Queue<Type>::Resize(_dword number) {
	// Clear the elements buffer
	if (number == 0) {
		Clear(_true);
	}
	// Resize the elements buffer
	else if (number != mNumber) {
		// Create elements
		Type* newelements = new Type[number + 1];

		// Copy elements into new memory, execute operator = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			newelements[i] = mElements[(mFront + i) % (mAllocedSize + 1)];

		EGE_DELETE_ARRAY(mElements);

		mElements = newelements;
		mAllocedSize = number;
		mNumber = MIN(mAllocedSize, mNumber);
		mFront = 0;
		mRear = mNumber;
	}
}

template <typename Type>
_void Queue<Type>::Clear(_ubool freememory) {
	mFront = 0;
	mRear = 0;

	if (freememory == _true) {
		EGE_DELETE_ARRAY(mElements);

		mAllocedSize = 0;
		mElements = _null;
	}

	CountOf<>::Clear();
}

} // namespace EGE