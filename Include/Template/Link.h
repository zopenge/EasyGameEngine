//! @file     Link.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Link
//----------------------------------------------------------------------------

//! This class is template base class of some bidirectional chain structure container class.
template <typename Type>
class Link : public CountOf<> {
public:
	NO_COPY_OPERATIONS(Link)

public:
	//! The node in the chain structure stores an element.
	struct Node {
		//! The element of the node.
		Type mElement;
		//! The previous node in the chain structure.
		Node* mPrev;
		//! The next node in the chain structure.
		Node* mNext;

		//! Constructor, create an unlinked node.
		//! @param		none
		Node()
		    : mPrev(_null), mNext(_null) {
		}

		//! Constructor, create an unlinked node stores an element.
		//! @param		element		The element will be stored in the node.
		Node(const Type& element)
		    : mElement(element), mPrev(_null), mNext(_null) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return mElement;
		}
	};

	//! The iterator of link class, provides ++ and -- operator to walk through the queue.
	struct Iterator {
		//! The current node that iterator points to.
		Node* mNode;
		//! The previous node in the chain structure.
		Node* mPrev;
		//! The next node in the chain structure.
		Node* mNext;

		//! Constructor, create an iterator of the link.
		//! @param		node		The node that iterator points to.
		Iterator(Node* node)
		    : mNode(node), mPrev(_null), mNext(_null) {
			if (mNode != _null) {
				mPrev = mNode->mPrev;
				mNext = mNode->mNext;
			}
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return mNode->mElement;
		}
		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator const Type&() const {
			return mNode->mElement;
		}

		//! Increase the iterator, point to the next element of the array.
		//! @param		none
		_void operator++(_int) {
			mPrev = mNode;
			mNode = mNext;
			mNext = mNode != _null ? mNode->mNext : _null;
		}
		//! decrease the iterator, point to the previous element of the array.
		//! @param		none
		_void operator--(_int) {
			mNext = mNode;
			mNode = mPrev;
			mPrev = mNode != _null ? mNode->mPrev : _null;
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mNode != _null;
		}
	};

protected:
	//! The head node of the link.
	Node* mHead;
	//! The tail node of the link.
	Node* mTail;

protected:
	//!	Check node.
	_ubool CheckNode(Node* node) const;
	//!	Get node number.
	_dword GetNodeNumber() const;

public:
	//! Constructor, create an empty link, only can be called by derived classes.
	//! @param		none
	Link();

public:
	//! Get the pointer of first element in the link.
	//! @param		none
	//! @return		The pointer to a element if there is, null otherwise.
	Type* GetFirstElement() const;
	//! Get the pointer of last element in the link.
	//! @param		none
	//! @return		The pointer to a element if there is, null otherwise.
	Type* GetLastElement() const;

	//! Get the head node pointer.
	//! @param		none
	//! @return		The head node.
	Node* GetHeadNode() const;
	//! Get the tail node pointer.
	//! @param		none
	//! @return		The tail node.
	Node* GetTailNode() const;

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator() const;

	//! Insert a node into the link at head.
	//! @param		node		The node to be inserted.
	//!	@return		none.
	_void InsertHead(Node* node);
	//! Insert a node into the link at tail.
	//! @param		node		The node to be inserted.
	//!	@return		none.
	_void InsertTail(Node* node);
	//! Insert a node into the link before the position specified by an iterator.
	//! @param		node		The node to be inserted.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		none.
	_void InsertBefore(Node* node, const Iterator& iterator);
	//! Insert a node into the link after the position specified by an iterator.
	//! @param		node		The node to be inserted.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		none.
	_void InsertAfter(Node* node, const Iterator& iterator);
	//! Remove a node from the link.
	//! @param		node		The node to be removed.
	//!	@param		none.
	//!	@return		none.
	_void Remove(Node* node);

	//! Clear the link, just clean the head and tail pointer, derived classes must release memory used by nodes.
	//! @param		none
	//!	@param		none.
	_void Clear();
};

//----------------------------------------------------------------------------
// Link Implementation
//----------------------------------------------------------------------------

template <typename Type>
Link<Type>::Link()
    : mHead(_null), mTail(_null) {
}

template <typename Type>
_ubool Link<Type>::CheckNode(Node* node) const {
	for (Node* node_temp = mHead; node_temp != _null; node_temp = node_temp->mNext) {
		if (node_temp == node)
			return _true;
	}

	return _false;
}

template <typename Type>
_dword Link<Type>::GetNodeNumber() const {
	_dword number = 0;
	for (Node* node = mHead; node != _null; node = node->mNext)
		number++;

	return number;
}

template <typename Type>
Type* Link<Type>::GetFirstElement() const {
	if (mHead == _null)
		return _null;

	return &(mHead->mElement);
}

template <typename Type>
Type* Link<Type>::GetLastElement() const {
	if (mTail == _null)
		return _null;

	return &(mTail->mElement);
}

template <typename Type>
typename Link<Type>::Node* Link<Type>::GetHeadNode() const {
	return mHead;
}

template <typename Type>
typename Link<Type>::Node* Link<Type>::GetTailNode() const {
	return mTail;
}

template <typename Type>
typename Link<Type>::Iterator Link<Type>::GetHeadIterator() const {
	return Iterator(mHead);
}

template <typename Type>
typename Link<Type>::Iterator Link<Type>::GetTailIterator() const {
	return Iterator(mTail);
}

template <typename Type>
_void Link<Type>::InsertHead(Node* node) {
	InsertBefore(node, Iterator(mHead));
}

template <typename Type>
_void Link<Type>::InsertTail(Node* node) {
	EGE_ASSERT(node != _null)

	if (mNumber == 0) {
		mHead = mTail = node;
	} else {
		node->mPrev = mTail;

		mTail->mNext = node;
		mTail = node;
	}

	// Increase the element number.
	CountOf<>::Increase();

#ifdef FULL_LINK_TEMPLATE_CLASS_TEST
	_dword node_number = GetNodeNumber();
	EGE_ASSERT(node_number == Number());
#endif
}

template <typename Type>
_void Link<Type>::InsertBefore(Node* node, const Iterator& iterator) {
	EGE_ASSERT(node != _null)

	if (iterator.IsValid() == _false) {
		mHead = mTail = node;
	} else {
		node->mPrev = iterator.mNode->mPrev;
		node->mNext = iterator.mNode;

		// Relink the previous one and next one both to this node.
		if (node->mPrev != _null)
			node->mPrev->mNext = node;
		if (node->mNext != _null)
			node->mNext->mPrev = node;

		// Adjust head and tail pointer.
		if (node->mPrev == _null)
			mHead = node;
		if (node->mNext == _null)
			mTail = node;
	}

	// Increase the element number.
	CountOf<>::Increase();

#ifdef FULL_LINK_TEMPLATE_CLASS_TEST
	_dword node_number = GetNodeNumber();
	EGE_ASSERT(node_number == Number());
#endif
}

template <typename Type>
_void Link<Type>::InsertAfter(Node* node, const Iterator& iterator) {
	EGE_ASSERT(node != _null)

	if (iterator.IsValid() == _false) {
		mHead = mTail = node;
	} else {
		node->mPrev = iterator.mNode;
		node->mNext = iterator.mNode->mNext;

		// Relink the previous one and next one both to this node.
		if (node->mPrev != _null)
			node->mPrev->mNext = node;
		if (node->mNext != _null)
			node->mNext->mPrev = node;

		// Adjust head and tail pointer.
		if (node->mPrev == _null)
			mHead = node;
		if (node->mNext == _null)
			mTail = node;
	}

	// Increase the element number.
	CountOf<>::Increase();

#ifdef FULL_LINK_TEMPLATE_CLASS_TEST
	_dword node_number = GetNodeNumber();
	EGE_ASSERT(node_number == Number());
#endif
}

template <typename Type>
_void Link<Type>::Remove(Node* node) {
	EGE_ASSERT(node != _null);

#ifdef FULL_LINK_TEMPLATE_CLASS_TEST
	EGE_ASSERT(CheckNode(node));
#endif

	// Relink the previous one to next one of this node.
	if (node->mPrev != _null)
		node->mPrev->mNext = node->mNext;
	if (node->mNext != _null)
		node->mNext->mPrev = node->mPrev;

	// Adjust head and tail pointer.
	if (mHead == node)
		mHead = node->mNext;
	if (mTail == node)
		mTail = node->mPrev;

	// Remove the link from the node.
	node->mPrev = _null;
	node->mNext = _null;

	// Decrease the element number.
	CountOf<>::Decrease();

#ifdef FULL_LINK_TEMPLATE_CLASS_TEST
	_dword node_number = GetNodeNumber();
	EGE_ASSERT(node_number == Number());
#endif
}

template <typename Type>
_void Link<Type>::Clear() {
	mHead = _null;
	mTail = _null;

	CountOf<>::Clear();
}

} // namespace EGE