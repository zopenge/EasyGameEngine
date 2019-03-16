//! @file     FixedTree.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FixedTree
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_CHILD_NUMBER > 
class FixedTree : public CountOf<>
{
private:
	struct TreeNode;

public:
	//!	The iterator of fixed tree
	struct Iterator
	{
		TreeNode*	mNode;

		Iterator( TreeNode* node ) 
			: mNode( node ) { }

		//!	Check whether it's valid or not.
		_ubool IsValid( ) const
			{ return mNode != _null; }

		//!	Get the element of tree node.
		operator Type& ( )
			{ return mNode->mElement; }
		operator const Type& ( ) const
			{ return mNode->mElement; }

		//!	Get the parent iterator of node
		Iterator GetParent( ) const
		{
			EGE_ASSERT( mNode != _null );

			return Iterator( mNode->mParent );
		}

		//!	Get the child iterator of node.
		Iterator GetChild( _dword index ) const
		{
			EGE_ASSERT( mNode != _null );
			EGE_ASSERT( index < _MAX_CHILD_NUMBER );

			return Iterator( mNode->mChildList[ index ] );
		}
	};

private:
	//!	The node of fixed tree
	struct TreeNode
	{
		Type		mElement;
		TreeNode*	mParent;
		TreeNode*	mChildList[ _MAX_CHILD_NUMBER ];

		TreeNode( TreeNode* parent = _null ) : mParent( parent )
		{
			EGE_INIT_ARRAY( mChildList );
		}

		TreeNode( const Type& element, TreeNode* parent = _null ) : mElement( element ), mParent( parent )
		{
			EGE_INIT_ARRAY( mChildList );
		}
	};

protected:
	//!	The root node
	TreeNode	mRootNode;

protected:
	//!	Clear all child nodes.
	//!	@param		node	The tree node.
	//!	@return		none.
	_void ClearAllChilds( TreeNode* node );

public:
	FixedTree( );
	~FixedTree( );

public:
	//!	Get the root iterator.
	//!	@param		none.
	//!	@return		The root iterator.
	Iterator GetRootIterator( ) const;

	//!	Insert the child node.
	//!	@param		element		The node element.
	//!	@param		iterator	The parent node.
	//!	@param		index		The children index.
	//!	@return		The node iterator.
	Iterator Insert( const Type& element, const Iterator& iterator, _dword index );
	//!	Remove the node iterator.
	//!	@param		iterator	The node iterator.
	//!	@return		none.
	_void Remove( Iterator& iterator );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// FixedTree Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_CHILD_NUMBER >
FixedTree< Type, _MAX_CHILD_NUMBER >::FixedTree( )
{
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
FixedTree< Type, _MAX_CHILD_NUMBER >::~FixedTree( )
{
	Clear( );
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
_void FixedTree< Type, _MAX_CHILD_NUMBER >::ClearAllChilds( TreeNode* node )
{
	if ( node == _null )
		return;

	for ( _dword i = 0; i < _MAX_CHILD_NUMBER; i ++ )
	{
		// Continue to clear children node
		ClearAllChilds( node->mChildList[i] );

		// Delete the node
		EGE_DELETE( node->mChildList[i] );

		// Decrease the number of nodes
		CountOf<>::Decrease( );
	}
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
typename FixedTree< Type, _MAX_CHILD_NUMBER >::Iterator FixedTree< Type, _MAX_CHILD_NUMBER >::GetRootIterator( ) const
{
	return Iterator( (TreeNode*) &mRootNode );
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
typename FixedTree< Type, _MAX_CHILD_NUMBER >::Iterator FixedTree< Type, _MAX_CHILD_NUMBER >::Insert( const Type& element, const Iterator& iterator, _dword index )
{
	EGE_ASSERT( iterator.mNode != _null );
	EGE_ASSERT( index < _MAX_CHILD_NUMBER );

	// Get the child node
	TreeNode*& child = iterator.mNode->mChildList[ index ];

	// Update the element if it's already existing
	if ( iterator.mNode->mChildList[ index ] != _null )
	{
		child->mElement = element;
	}
	else
	{
		// Create the children node
		child = new TreeNode( element, iterator.mNode );

		// Increase the node number of trees
		CountOf<>::Increase( );
	}

	return Iterator( child );
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
_void FixedTree< Type, _MAX_CHILD_NUMBER >::Remove( Iterator& iterator )
{
	EGE_ASSERT( iterator.mNode != _null );

	// Get the parent of node
	TreeNode* parent = iterator.mNode->mParent;
	EGE_ASSERT( parent != _null );

	// Clear the link of parent
	for ( _dword i = 0; i < _MAX_CHILD_NUMBER; i ++ )
	{
		if ( parent->mChildList[i] == iterator.mNode )
		{
			parent->mChildList[i] = _null;
			break;
		}
	}

	// Clear all children
	ClearAllChilds( iterator.mNode );

	// Delete the node
	EGE_DELETE( iterator.mNode );
}

template< typename Type, _dword _MAX_CHILD_NUMBER >
_void FixedTree< Type, _MAX_CHILD_NUMBER >::Clear( )
{
	ClearAllChilds( &mRootNode );

	// All the nodes must be cleared
	CountOf<>::Clear( );
}

}