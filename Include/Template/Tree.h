//! @file     Tree.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Tree
//----------------------------------------------------------------------------

template <typename Type, typename Key = Type>
class Tree : public CountOf<> {
private:
	struct TreeNode;

public:
	//! The iterator of tree class
	struct Iterator {
		//!	The tree node
		TreeNode* mNode;

		//! Constructor, create an iterator of the tree.
		//! @param		node	The tree node.
		Iterator(TreeNode* node)
		    : mNode(node) {
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mNode != _null;
		}

		//!	Get element of tree node.
		operator Type&() {
			return mNode->mElement;
		}
		//!	Get element of tree node.
		operator const Type&() const {
			return mNode->mElement;
		}

		//!	Get the parent node.
		Iterator GetParent() const {
			return Iterator(mNode->mParent);
		}
		//!	Get the child node.
		Iterator GetChild() const {
			return Iterator(mNode->mChild);
		}
		//!	Get the previous node.
		Iterator GetPrev() const {
			return Iterator(mNode->mPrev);
		}
		//!	Get the next node.
		Iterator GetNext() const {
			return Iterator(mNode->mNext);
		}
	};

private:
	//!	The tree node
	struct TreeNode {
		//!	The node element
		Type mElement;

		//!	The parent node
		TreeNode* mParent;
		//!	The child node
		TreeNode* mChild;
		//!	The prev node
		TreeNode* mPrev;
		//!	The next node
		TreeNode* mNext;

		TreeNode()
		    : mParent(_null), mChild(_null), mPrev(_null), mNext(_null) {
		}

		TreeNode(const Type& element, TreeNode* parent = _null)
		    : mElement(element), mParent(parent), mChild(_null), mPrev(_null), mNext(_null) {
		}
	};

private:
	//!	The root node
	TreeNode mRootNode;

private:
	//!	Clear all child nodes.
	//!	@param		node	The tree node.
	//!	@return		none.
	_void ClearAllChilds(TreeNode* node);

public:
	Tree();
	~Tree();

public:
	//!	Get the root iterator.
	//!	@param		none.
	//!	@return		The root iterator.
	Iterator GetRootIterator() const;

	//!	Search the child node by key.
	//!	@param		iterator	The node iterator.
	//!	@param		key			The key.
	//!	@return		The node iterator.
	Iterator SearchInChild(const Iterator& iterator, const Key& key) const;

	//!	Insert the child node.
	//!	@param		element		The node element.
	//!	@param		iterator	The parent node.
	//!	@return		The node iterator.
	Iterator Insert(const Type& element, const Iterator& iterator);
	//!	Remove the node iterator.
	//!	@param		iterator	The node iterator.
	//!	@return		none.
	_void Remove(Iterator& iterator);

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear();
};

//----------------------------------------------------------------------------
// Tree Implementation
//----------------------------------------------------------------------------

template <typename Type, typename Key>
Tree<Type, Key>::Tree() {
}

template <typename Type, typename Key>
Tree<Type, Key>::~Tree() {
	ClearAllChilds(&mRootNode);
}

template <typename Type, typename Key>
_void Tree<Type, Key>::ClearAllChilds(TreeNode* node) {
	if (node == _null)
		return;

	TreeNode* child = node->mChild;

	while (child != _null) {
		TreeNode* temp = child;
		child = child->mNext;

		// Continue to clear children node
		ClearAllChilds(temp);

		// Delete the node
		delete temp;

		// Decrease the node number
		CountOf<>::Decrease();
	}

	node->mChild = _null;
}

template <typename Type, typename Key>
typename Tree<Type, Key>::Iterator Tree<Type, Key>::GetRootIterator() const {
	return Iterator((TreeNode*)&mRootNode);
}

template <typename Type, typename Key>
typename Tree<Type, Key>::Iterator Tree<Type, Key>::SearchInChild(const Iterator& iterator, const Key& key) const {
	EGE_ASSERT(iterator.mNode != _null);

	Iterator child = iterator.GetChild();

	while (child.IsValid()) {
		if (((const Type&)child) == key)
			return child;

		child = child.GetNext();
	}

	return Iterator(_null);
}

template <typename Type, typename Key>
typename Tree<Type, Key>::Iterator Tree<Type, Key>::Insert(const Type& element, const Iterator& iterator) {
	EGE_ASSERT(iterator.mNode != _null);

	TreeNode* node = new TreeNode(element, node);

	if (node->mChild == _null) {
		node->mChild = node;
	} else {
		TreeNode* child = node->mChild;

		while (child->mNext != _null)
			child = child->mNext;

		child->mNext = node;
		node->mPrev = child;
	}

	// Increase the number of nodes
	CountOf<>::Increase();

	return Iterator(node);
}

template <typename Type, typename Key>
_void Tree<Type, Key>::Remove(Iterator& iterator) {
	TreeNode* node = iterator.mNode;
	EGE_ASSERT(node != _null);

	// Get the parent node
	TreeNode* parent = node->mParent;
	if (parent == _null)
		return;

	// Remove the link
	if (parent->mChild == node)
		parent->mChild = node->mNext;

	if (node->mPrev != _null)
		node->mPrev->mNext = node->mNext;

	if (node->mNext != _null)
		node->mNext->mPrev = node->mPrev;

	// Clear the all children of node
	ClearAllChilds(node);

	// Delete the node
	EGE_DELETE(node);
}

template <typename Type, typename Key>
_void Tree<Type, Key>::Clear() {
	ClearAllChilds(&mRootNode);

	CountOf<>::Clear();
}

} // namespace EGE