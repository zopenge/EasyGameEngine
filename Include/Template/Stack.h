#pragma once

namespace EGE {

/// <summary>
/// This class is template container class, represents a stack.
/// </summary>
template <typename Type, typename Key = Type>
class Stack : public CountOf<> {
public:
	//! The iterator of stack class, provides ++ and -- operator to walk through the stack.
	struct Iterator {
		//! The stack reference.
		Stack<Type, Key>* mStack;
		//! The current index of the element.
		_dword index;

		//! Constructor, create an iterator of the stack.
		//! @param		stack	The stack reference.
		//! @param		index		The current index of the element.
		Iterator(Stack<Type, Key>* stack, _dword index)
		    : mStack(stack), index(index) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return (*mStack)[index];
		}

		//! Increase the iterator, point to the next element of the stack.
		//! @param		none
		_void operator++(_int) {
			index++;
		}
		//! decrease the iterator, point to the previous element of the stack.
		//! @param		none
		_void operator--(_int) {
			index--;
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return index < mStack->Number();
		}
	};

private:
	//! The allocated size of the stack in number of element.
	_dword mAllocedSize;
	//! The memory pointer of the stack.
	Type* mElements;

private:
	//! Grow.
	//! @param		none.
	//!	@return		none.
	_void Grow();

public:
	//! Constructor, create an empty stack.
	//! @param		number		The initial number of the stack in number of element.
	//! @param		grow		The initial grow size of the stack in number of element.
	Stack(_dword number = 0);
	//! Copy-Constructor, create a stack by copy from another one.
	//! @param		stack	The other stack.
	Stack(const Stack<Type, Key>& stack);
	//! Destructor, delete the stack, and release the elements memory.
	//! @param		none
	~Stack();

public:
	//! Copy elements from another stack, and recreates memory to hold it.
	//! @param		stack	The other stack.
	//! @return		The reference of current stack.
	Stack<Type, Key>& operator=(const Stack<Type, Key>& stack);

	//! Get a const element reference by index.
	//! @param		index		The index of the element in stack.
	//! @return		The const element reference.
	const Type& operator[](_dword index) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in stack.
	//! @return		The mutable element reference.
	Type& operator[](_dword index);

	//! Get the top element in stack.
	//! @param		none
	//! @return		The element reference of the top element.
	Type& Top();
	//! Get the top element in stack.
	//! @param		none
	//! @return		The element reference of the top element.
	const Type& Top() const;

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator() const;

	//! Get an iterator by the index of an element.
	//! @param		index		The index of the element in stack.
	//! @return		An iterator reference to the element.
	Iterator GetIterator(_dword index) const;

	//! Push an element into stack.
	//! @param		none.
	//!	@return		The new element to be push into.
	Type& Push();
	//! Push an element into stack.
	//! @param		element		The new element to be push into.
	//!	@return		none.
	_void Push(const Type& element);
	//! Pop an element from stack.
	//! @param		none
	//!	@return		The element reference of the top element what has been popped.
	Type& Pop();
	//! Resize the stack by create new memory and copy old element into it, the memory is larger than older by grow size.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Resize(_dword number);

	//! Clear the stack, delete all elements and free the memory.
	//! @param		freememory	If free the memory used by array.
	_void Clear(_ubool freememory = _false);
};

template <typename Type, typename Key>
Stack<Type, Key>::Stack(_dword number) {
	mAllocedSize = number;
	mNumber = number;
	mElements = _null;

	if (mAllocedSize > 0)
		mElements = new Type[mAllocedSize];
}

template <typename Type, typename Key>
Stack<Type, Key>::Stack(const Stack<Type, Key>& stack) {
	mAllocedSize = stack.mAllocedSize;
	mNumber = stack.mNumber;
	mElements = _null;

	if (mAllocedSize > 0) {
		mElements = new Type[mAllocedSize];

		// Copy elements into new memory, execute operator = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			mElements[i] = stack.mElements[i];
	}
}

template <typename Type, typename Key>
Stack<Type, Key>::~Stack() {
	Clear(_true);
}

template <typename Type, typename Key>
_void Stack<Type, Key>::Grow() {
	// Increase the allocated size
	_dword alloced_size = MAX(mAllocedSize + 1, mAllocedSize * 2);

	Resize(alloced_size);
}

template <typename Type, typename Key>
Stack<Type, Key>& Stack<Type, Key>::operator=(const Stack<Type, Key>& stack) {
	Clear(_true);

	mAllocedSize = stack.mAllocedSize;
	mNumber = stack.mNumber;
	mElements = _null;

	if (mAllocedSize > 0) {
		mElements = new Type[mAllocedSize];

		// Copy elements one by one, execute operator = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			mElements[i] = stack.mElements[i];
	}

	return *this;
}

template <typename Type, typename Key>
const Type& Stack<Type, Key>::operator[](_dword index) const {
	EGE_ASSERT(index < mNumber);

	return mElements[index];
}

template <typename Type, typename Key>
Type& Stack<Type, Key>::operator[](_dword index) {
	EGE_ASSERT(index < mNumber);

	return mElements[index];
}

template <typename Type, typename Key>
Type& Stack<Type, Key>::Top() {
	EGE_ASSERT(mNumber > 0);

	return mElements[mNumber - 1];
}

template <typename Type, typename Key>
const Type& Stack<Type, Key>::Top() const {
	EGE_ASSERT(mNumber > 0);

	return mElements[mNumber - 1];
}

template <typename Type, typename Key>
typename Stack<Type, Key>::Iterator Stack<Type, Key>::GetHeadIterator() const {
	return Iterator((Stack<Type, Key>*)this, 0);
}

template <typename Type, typename Key>
typename Stack<Type, Key>::Iterator Stack<Type, Key>::GetTailIterator() const {
	return Iterator((Stack<Type, Key>*)this, mNumber - 1);
}

template <typename Type, typename Key>
typename Stack<Type, Key>::Iterator Stack<Type, Key>::GetIterator(_dword index) const {
	return Iterator((Stack<Type, Key>*)this, index);
}

template <typename Type, typename Key>
Type& Stack<Type, Key>::Push() {
	// Resize the stack when necessary.
	if (mNumber == mAllocedSize)
		Grow();

	// Assign the element.
	Type& element = mElements[mNumber];

	// Increase the element number.
	CountOf<>::Increase();

	return element;
}

template <typename Type, typename Key>
_void Stack<Type, Key>::Push(const Type& element) {
	// Resize the stack when necessary.
	if (mNumber == mAllocedSize)
		Grow();

	// Assign the element.
	mElements[mNumber] = element;

	// Increase the element number.
	CountOf<>::Increase();
}

template <typename Type, typename Key>
Type& Stack<Type, Key>::Pop() {
	EGE_ASSERT(mNumber > 0);

	// Decrease the element number
	CountOf<>::Decrease();

	// Pop the top element
	return mElements[mNumber];
}

template <typename Type, typename Key>
_void Stack<Type, Key>::Resize(_dword number) {
	// Clear the elements buffer
	if (number == 0) {
		Clear(_true);
	}
	// Resize the elements buffer
	else {
		// Create elements
		Type* newelements = new Type[number];

		// Copy elements into new memory, execute operator = of Type class.
		for (_dword i = 0; i < mNumber; i++)
			newelements[i] = mElements[i];

		EGE_DELETE_ARRAY(mElements);

		mElements = newelements;
		mAllocedSize = number;

		if (mNumber > mAllocedSize)
			mNumber = mAllocedSize;
	}
}

template <typename Type, typename Key>
_void Stack<Type, Key>::Clear(_ubool freememory) {
	if (freememory == _true) {
		EGE_DELETE_ARRAY(mElements);

		mAllocedSize = 0;
		mElements = _null;
	}

	CountOf<>::Clear();
}

} // namespace EGE