#pragma once

namespace EGE {

/// <summary>
/// The red black tree.
/// </summary>
template <typename Type, typename CompareFunc = Compare<Type>>
class RBTree : public CountOf<> {
private:
	typedef RBTree<Type, CompareFunc> SelfClass;

public:
	//!	The tree node
	struct TreeNode {
		//! If it equal to 0 then indicates the node is black
		_ubool mIsRed;
		//!	The parent node
		TreeNode* mParent;
		//!	The left child
		TreeNode* mLeftChild;
		//!	The right child
		TreeNode* mRightChild;
		//!	The element
		Type mElement;

		TreeNode()
		    : mIsRed(_false), mParent(_null), mLeftChild(_null), mRightChild(_null) {
		}

		TreeNode(_ubool is_red, const Type& element)
		    : mIsRed(is_red), mParent(_null), mLeftChild(_null), mRightChild(_null), mElement(element) {
		}

		TreeNode(const Type& element)
		    : mIsRed(_false), mParent(_null), mLeftChild(_null), mRightChild(_null), mElement(element) {
		}

		~TreeNode() {
		}
	};

public:
	//!	The iterator of RB-Tree
	struct Iterator {
		//!	The tree node
		TreeNode* mNode;
		//!	The tree
		const SelfClass* mTree;

		//! Constructor, create an iterator of the RB-Tree.
		//! @param		node		The node that iterator points to.
		Iterator(TreeNode* node, const SelfClass* tree)
		    : mNode(node), mTree(tree) {
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

		//! Decrease the iterator, point to the previous element of the RBTree.
		//! @param		none
		_void operator--() {
			if (mNode != _null) {
				// ==> largest of left subtree
				if (mNode->mLeftChild != &mTree->mNull) {
					mNode = MaxNode(mNode->mLeftChild);
				}
				// Climb looking for left subtree
				else {
					TreeNode* node = mNode->mParent;
					while (node != _null && mNode == node->mLeftChild) {
						// ==> parent while left subtree
						mNode = node;
						node = node->mParent;
					}

					if (node == &mTree->mRoot)
						mNode = _null;
					else
						mNode = node;
				}
			}
		}

		//! Increase the iterator, point to the next element of the RBTree.
		//! @param		none
		_void operator++() {
			if (mNode != _null) {
				// ==> smallest of right subtree
				if (mNode->mRightChild != &mTree->mNull) {
					mNode = MinNode(mNode->mRightChild);
				}
				// Climb looking for right subtree
				else {
					TreeNode* node = mNode->mParent;
					while (node != _null && mNode == node->mRightChild) {
						// ==> parent while right subtree
						mNode = node;
						node = node->mParent;
					}

					if (node == &mTree->mRoot)
						mNode = _null;
					else
						mNode = node;
				}
			}
		}

		//!	Return the left most node in subtree
		TreeNode* MinNode(TreeNode* node) const {
			while (node->mLeftChild != &mTree->mNull)
				node = node->mLeftChild;

			return node;
		}

		//!	Return the right most node in subtree
		TreeNode* MaxNode(TreeNode* node) const {
			while (node->mRightChild != &mTree->mNull)
				node = node->mRightChild;

			return node;
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mNode != _null;
		}
	};

private:
	//! mRoot::mLeft should always point to the node which is the root of the tree.
	TreeNode mRoot;
	//!	mNull points to a node which should always be black but has arbitrary children and parent and no key or element.
	TreeNode mNull;

private:
	//!	Initialize.
	_void Initialize();

	//! Copy from another RB-Tree.
	_void CopyFrom(TreeNode& node, const TreeNode& from_node, const TreeNode& from_null_node);

	//!	Get the leftmost node.
	TreeNode* LMost() const;

	//!	Recursively destroys the nodes of the tree.
	_void DestroyHelper(TreeNode* node);
	//!	Insert a node into the tree.
	_void InsertHelper(TreeNode* node);
	//!	Rotate tree node after insert.
	_void RotateAfterInsert(TreeNode* node);

	//! Get successor of node.
	TreeNode* GetSuccessor(TreeNode* x);
	//! Get predecessor of node.
	TreeNode* GetPredecessor(TreeNode* x);

	//!	Rotate tree node to left.
	_void LeftRotate(TreeNode* y);
	//!	Rotate tree node to right.
	_void RightRotate(TreeNode* x);

	//!	Performs rotations and changes colors to restore red-black properties after a node is deleted.
	_void DeleteFixup(TreeNode* x);

public:
	RBTree();
	RBTree(RBTree<Type, CompareFunc>& rbtree);
	~RBTree();

public:
	//! Copy elements from another RB-Tree, and recreates memory to hold it.
	//! @param		rbtree		The other RB-Tree.
	//! @return		The reference of current RB-Tree.
	RBTree<Type, CompareFunc>& operator=(const RBTree<Type, CompareFunc>& rbtree);

	//! Get the head iterator.
	//! @param		none.
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;

	//!	Insert element.
	//!	@param		element		The element.
	//!	@return		The node iterator.
	typename RBTree<Type, CompareFunc>::Iterator Insert(const Type& element);
	//!	Insert element by key.
	//!	@param		key			The key of element.
	//!	@return		The node iterator.
	template <typename Key>
	typename RBTree<Type, CompareFunc>::Iterator Insert(const Key& key);
	//!	Search element.
	//!	@param		element		The element.
	//!	@return		The node iterator.
	typename RBTree<Type, CompareFunc>::Iterator Search(const Type& element) const;
	//!	Search element by key.
	//!	@param		key			The key of element.
	//!	@return		The node iterator.
	template <typename Key>
	typename RBTree<Type, CompareFunc>::Iterator Search(const Key& key) const;
	//!	Remove the node.
	//!	@param		node		The tree node.
	//! @return		none.
	_void Remove(TreeNode* node);
	//!	Remove the node.
	//!	@param		element		The element.
	//!	@return		True indicates remove it successful.
	_ubool Remove(const Type& element);
	//!	Remove the node by key.
	//!	@param		key			The key of element.
	//!	@return		True indicates remove it successful.
	template <typename Key>
	_ubool Remove(const Key& key);
	//!	Remove the node iterator.
	//!	@param		iterator	The node iterator.
	//! @return		The next iterator.
	typename RBTree<Type, CompareFunc>::Iterator Remove(typename RBTree<Type, CompareFunc>::Iterator iterator);

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear();
};

template <typename Type, typename CompareFunc>
RBTree<Type, CompareFunc>::RBTree() {
	Initialize();
}

template <typename Type, typename CompareFunc>
RBTree<Type, CompareFunc>::RBTree(RBTree<Type, CompareFunc>& rbtree) {
	Initialize();

	*this = rbtree;
}

template <typename Type, typename CompareFunc>
RBTree<Type, CompareFunc>::~RBTree() {
	Clear();
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::Initialize() {
	mNull.mParent = mNull.mLeftChild = mNull.mRightChild = &mNull;
	mRoot.mParent = mRoot.mLeftChild = mRoot.mRightChild = &mNull;
}

template <typename Type, typename CompareFunc>
void RBTree<Type, CompareFunc>::CopyFrom(TreeNode& node, const TreeNode& from_node, const TreeNode& from_null_node) {
	node.mIsRed = from_node.mIsRed;
	node.mElement = from_node.mElement;
	node.mLeftChild = &mNull;
	node.mRightChild = &mNull;

	if (from_node.mLeftChild != &from_null_node) {
		TreeNode* left_child_node = new TreeNode(from_node.mLeftChild->mIsRed, from_node.mLeftChild->mElement);
		left_child_node->mParent = &node;
		left_child_node->mLeftChild = &mNull;
		left_child_node->mRightChild = &mNull;

		node.mLeftChild = left_child_node;

		CopyFrom(*left_child_node, *from_node.mLeftChild, from_null_node);
	}

	if (from_node.mRightChild != &from_null_node) {
		TreeNode* right_child_node = new TreeNode(from_node.mRightChild->mIsRed, from_node.mRightChild->mElement);
		right_child_node->mParent = &node;
		right_child_node->mLeftChild = &mNull;
		right_child_node->mRightChild = &mNull;

		node.mRightChild = right_child_node;

		CopyFrom(*right_child_node, *from_node.mRightChild, from_null_node);
	}
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::TreeNode* RBTree<Type, CompareFunc>::LMost() const {
	TreeNode* node = mRoot.mLeftChild;
	while (node->mLeftChild != &mNull)
		node = node->mLeftChild;

	return node;
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::DestroyHelper(TreeNode* node) {
	if (node == &mNull)
		return;

	DestroyHelper(node->mLeftChild);
	DestroyHelper(node->mRightChild);

	EGE_DELETE(node);
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::InsertHelper(TreeNode* node) {
	node->mLeftChild = node->mRightChild = &mNull;

	TreeNode* y = &mRoot;
	TreeNode* x = mRoot.mLeftChild;

	while (x != &mNull) {
		y = x;

		if (CompareFunc()(x->mElement, node->mElement) > 0)
			x = x->mLeftChild;
		else
			x = x->mRightChild;
	}

	node->mParent = y;

	if ((y == &mRoot) || (CompareFunc()(y->mElement, node->mElement) > 0)) {
		y->mLeftChild = node;
		EGE_ASSERT(y->mLeftChild != y);
	} else {
		y->mRightChild = node;
		EGE_ASSERT(y->mRightChild != y);
	}

	// Null not red in InsertHelper
	EGE_ASSERT(mNull.mIsRed == _false);
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::RotateAfterInsert(TreeNode* node) {
	TreeNode* x = node;

	// Rotate the tree if needed
	while (x->mParent->mIsRed) {
		TreeNode* y = _null;

		if (x->mParent == x->mParent->mParent->mLeftChild) {
			y = x->mParent->mParent->mRightChild;
			if (y->mIsRed) {
				x->mParent->mIsRed = _false;
				y->mIsRed = _false;
				x->mParent->mParent->mIsRed = _true;

				x = x->mParent->mParent;
			} else {
				if (x == x->mParent->mRightChild) {
					x = x->mParent;
					LeftRotate(x);
				}

				x->mParent->mIsRed = _false;
				x->mParent->mParent->mIsRed = _true;

				RightRotate(x->mParent->mParent);
			}
		} else {
			y = x->mParent->mParent->mLeftChild;
			if (y->mIsRed) {
				x->mParent->mIsRed = _false;
				y->mIsRed = _false;
				x->mParent->mParent->mIsRed = _true;

				x = x->mParent->mParent;
			} else {
				if (x == x->mParent->mLeftChild) {
					x = x->mParent;
					RightRotate(x);
				}

				x->mParent->mIsRed = _false;
				x->mParent->mParent->mIsRed = _true;

				LeftRotate(x->mParent->mParent);
			}
		}
	}

	mRoot.mLeftChild->mIsRed = _false;
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::TreeNode* RBTree<Type, CompareFunc>::GetSuccessor(TreeNode* x) {
	TreeNode* y = _null;

	if (&mNull != (y = x->mRightChild)) {
		// Returns the minimum of the right subtree of x
		while (y->mLeftChild != &mNull)
			y = y->mLeftChild;

		return y;
	} else {
		y = x->mParent;

		while (x == y->mRightChild) {
			x = y;
			y = y->mParent;
		}

		if (y == &mRoot)
			return &mNull;

		return y;
	}
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::TreeNode* RBTree<Type, CompareFunc>::GetPredecessor(TreeNode* x) {
	TreeNode* y = _null;

	if (&mNull != (y = x->mLeftChild)) {
		// Returns the maximum of the left subtree of x
		while (y->mRightChild != &mNull)
			y = y->mRightChild;

		return y;
	} else {
		y = x->mParent;

		while (x == y->mLeftChild) {
			if (y == &mRoot)
				return &mNull;

			x = y;
			y = y->mParent;
		}

		return y;
	}
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::LeftRotate(TreeNode* x) {
	TreeNode* y = x->mRightChild;
	x->mRightChild = y->mLeftChild;
	EGE_ASSERT(x->mRightChild != x);

	if (y->mLeftChild != &mNull)
		y->mLeftChild->mParent = x;

	y->mParent = x->mParent;

	if (x == x->mParent->mLeftChild) {
		x->mParent->mLeftChild = y;
		EGE_ASSERT(x->mParent->mLeftChild != x->mParent);
	} else {
		x->mParent->mRightChild = y;
		EGE_ASSERT(x->mParent->mRightChild != x->mParent);
	}

	y->mLeftChild = x;
	x->mParent = y;

	// Null not red in LeftRotate
	EGE_ASSERT(mNull.mIsRed == _false);
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::RightRotate(TreeNode* y) {
	TreeNode* x = y->mLeftChild;
	y->mLeftChild = x->mRightChild;

	if (x->mRightChild != &mNull)
		x->mRightChild->mParent = y;

	x->mParent = y->mParent;

	if (y == y->mParent->mLeftChild) {
		y->mParent->mLeftChild = x;
		EGE_ASSERT(y->mParent->mLeftChild != y->mParent);
	} else {
		y->mParent->mRightChild = x;
		EGE_ASSERT(y->mParent->mRightChild != y->mParent);
	}

	x->mRightChild = y;
	y->mParent = x;
	EGE_ASSERT(x->mRightChild != x);

	// Null not red in RightRotate
	EGE_ASSERT(mNull.mIsRed == _false);
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::DeleteFixup(TreeNode* x) {
	TreeNode* root = mRoot.mLeftChild;

	while ((x->mIsRed == _false) && (root != x)) {
		TreeNode* w = _null;

		if (x == x->mParent->mLeftChild) {
			w = x->mParent->mRightChild;
			if (w->mIsRed) {
				w->mIsRed = _false;
				x->mParent->mIsRed = _true;
				LeftRotate(x->mParent);

				w = x->mParent->mRightChild;
			}

			if ((w->mRightChild->mIsRed == _false) && (w->mLeftChild->mIsRed == _false)) {
				w->mIsRed = _true;
				x = x->mParent;
			} else {
				if (w->mRightChild->mIsRed == _false) {
					w->mLeftChild->mIsRed = _false;
					w->mIsRed = _true;
					RightRotate(w);

					w = x->mParent->mRightChild;
				}

				w->mIsRed = x->mParent->mIsRed;
				x->mParent->mIsRed = _false;
				w->mRightChild->mIsRed = _false;
				LeftRotate(x->mParent);

				// This is to exit while loop
				x = root;
			}
		} else {
			w = x->mParent->mLeftChild;
			if (w->mIsRed) {
				w->mIsRed = _false;
				x->mParent->mIsRed = _true;
				RightRotate(x->mParent);

				w = x->mParent->mLeftChild;
			}

			if ((w->mRightChild->mIsRed == _false) && (w->mLeftChild->mIsRed == _false)) {
				w->mIsRed = _true;
				x = x->mParent;
			} else {
				if (w->mLeftChild->mIsRed == _false) {
					w->mRightChild->mIsRed = _false;
					w->mIsRed = _true;
					LeftRotate(w);

					w = x->mParent->mLeftChild;
				}

				w->mIsRed = x->mParent->mIsRed;
				x->mParent->mIsRed = _false;
				w->mLeftChild->mIsRed = _false;
				RightRotate(x->mParent);

				// This is to exit while loop
				x = root;
			}
		}
	}

	x->mIsRed = _false;

	// Null not red in DeleteFixup
	EGE_ASSERT(mNull.mIsRed == _false);
}

template <typename Type, typename CompareFunc>
RBTree<Type, CompareFunc>& RBTree<Type, CompareFunc>::operator=(const RBTree<Type, CompareFunc>& rbtree) {
	Clear();

	// Copy elements from another RB-Tree
	CopyFrom(mRoot, rbtree.mRoot, rbtree.mNull);

	this->mNumber = rbtree.mNumber;

	return *this;
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::GetHeadIterator() const {
	if (Number() == 0)
		return Iterator(_null, _null);

	return Iterator(LMost(), this);
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::Insert(const Type& element) {
	// Create tree node
	TreeNode* x = new TreeNode(element);
	x->mIsRed = _true;

	// Insert it into tree
	InsertHelper(x);
	RotateAfterInsert(x);

	// Increase the number of nodes
	CountOf<>::Increase();

	return Iterator(x, this);
}

template <typename Type, typename CompareFunc>
template <typename Key>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::Insert(const Key& key) {
	// Create tree node
	TreeNode* x = new TreeNode();
	x->mElement = key;
	x->mIsRed = _true;

	// Insert it into tree
	InsertHelper(x);
	RotateAfterInsert(x);

	// Increase the number of nodes
	CountOf<>::Increase();

	return Iterator(x, this);
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::Search(const Type& element) const {
	TreeNode* x = mRoot.mLeftChild;
	if (x == &mNull)
		return Iterator(_null, _null);

	while (_true) {
		_int ret = CompareFunc()(x->mElement, element);
		if (ret == 0)
			break;

		if (ret > 0)
			x = x->mLeftChild;
		else
			x = x->mRightChild;

		if (x == &mNull)
			return Iterator(_null, _null);
	}

	return Iterator(x, this);
}

template <typename Type, typename CompareFunc>
template <typename Key>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::Search(const Key& key) const {
	TreeNode* x = mRoot.mLeftChild;
	if (x == &mNull)
		return Iterator(_null, _null);

	while (_true) {
		_int ret = CompareFunc()(x->mElement, key);
		if (ret == 0)
			break;

		if (ret > 0)
			x = x->mLeftChild;
		else
			x = x->mRightChild;

		if (x == &mNull)
			return Iterator(_null, _null);
	}

	return Iterator(x, this);
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::Remove(TreeNode* node) {
	EGE_ASSERT(node != _null);

	TreeNode* z = node;
	TreeNode* y = ((z->mLeftChild == &mNull) || (z->mRightChild == &mNull)) ? z : GetSuccessor(z);
	TreeNode* x = (y->mLeftChild == &mNull) ? y->mRightChild : y->mLeftChild;

	if ((x->mParent = y->mParent) == &mRoot) {
		mRoot.mLeftChild = x;
	} else {
		if (y == y->mParent->mLeftChild)
			y->mParent->mLeftChild = x;
		else
			y->mParent->mRightChild = x;
	}

	if (y != z) {
		EGE_ASSERT(y != &mNull);

		// y is the node to splice out and x is its child
		if (y->mIsRed == _false)
			DeleteFixup(x);

		y->mLeftChild = z->mLeftChild;
		y->mRightChild = z->mRightChild;
		y->mParent = z->mParent;
		y->mIsRed = z->mIsRed;
		z->mLeftChild->mParent = z->mRightChild->mParent = y;
		EGE_ASSERT(y->mLeftChild != y);
		EGE_ASSERT(y->mRightChild != y);

		if (z == z->mParent->mLeftChild) {
			z->mParent->mLeftChild = y;
			EGE_ASSERT(z->mParent->mLeftChild != z->mParent);
		} else {
			z->mParent->mRightChild = y;
			EGE_ASSERT(z->mParent->mRightChild != z->mParent);
		}

		EGE_DELETE(z);
	} else {
		if (y->mIsRed == _false)
			DeleteFixup(x);

		EGE_DELETE(y);
	}

	// Decrease the number of nodes
	CountOf<>::Decrease();

	// Null not red in Remove
	EGE_ASSERT(mNull.mIsRed == _false);
}

template <typename Type, typename CompareFunc>
_ubool RBTree<Type, CompareFunc>::Remove(const Type& element) {
	Iterator it = Search(element);
	if (it.IsValid() == _false)
		return _false;

	Remove(it);
	return _true;
}

template <typename Type, typename CompareFunc>
template <typename Key>
_ubool RBTree<Type, CompareFunc>::Remove(const Key& key) {
	Iterator it = Search(key);
	if (it.IsValid() == _false)
		return _false;

	Remove(it);
	return _true;
}

template <typename Type, typename CompareFunc>
typename RBTree<Type, CompareFunc>::Iterator RBTree<Type, CompareFunc>::Remove(typename RBTree<Type, CompareFunc>::Iterator iterator) {
	Iterator next_it = iterator;
	++next_it;

	Remove(iterator.mNode);

	return next_it;
}

template <typename Type, typename CompareFunc>
_void RBTree<Type, CompareFunc>::Clear() {
	DestroyHelper(mRoot.mLeftChild);

	Initialize();

	CountOf<>::Clear();
}

} // namespace EGE