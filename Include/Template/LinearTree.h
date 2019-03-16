//! @file     LinearTree.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LinearTree
//----------------------------------------------------------------------------

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key = Type > 
class LinearTree : public CountOf<>
{
private:
	struct Node;

private:
	typedef Pair< _qword, Node* >	NodePair;
	typedef Array< NodePair >		NodeArray;

public:
	//! The iterator of tree class
	struct Iterator
	{
		//!	The index of nodes array
		_int		mIndex;

		//!	The tree
		LinearTree*	mTree;

		//! Constructor, create an iterator of the tree.
		Iterator( )
			: mIndex( -1 ), mTree( _null ) { }
		Iterator( _int index, LinearTree* tree ) 
			: mIndex( index ), mTree( tree ) { }

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid( ) const
			{ return mIndex != -1 && mIndex < (_int) mTree->mNodes.Number( ) && GetNode( ) != _null; }

		//!	Get node.
		Node* GetNode( )
			{ return mTree != _null ? mTree->mNodes[ mIndex ].mObject2 : _null; }
		//!	Get node.
		const Node* GetNode( ) const
			{ return mTree != _null ? mTree->mNodes[ mIndex ].mObject2 : _null; }

		//!	Get element of tree node.
		operator Type& ( )
			{ return GetNode( )->mElement; }
		//!	Get element of tree node.
		operator const Type& ( ) const
			{ return GetNode( )->mElement; }

		//! Decrease the iterator, point to the previous element of the tree node.
		//! @param		none
		_void operator -- ( _int )
		{ 
			if ( mIndex > 0 )
				mIndex --;
		}
		//! Increase the iterator, point to the next element of the tree node.
		//! @param		none
		_void operator ++ ( _int )
		{
			if ( mIndex < (_int) mTree->mNodes.Number( ) )
				mIndex ++;
		}

		//!	Get ID.
		_qword GetID( ) const
		{
			return mTree->mNodes[ mIndex ].mObject2->mID;
		}
		//!	Get depth.
		_dword GetDepth( ) const
		{
			return GetNode( )->mDepth;
		}
		//!	Get parent ID.
		_qword GetParentID( ) const
		{
			Iterator it = *this;

			while ( _true )
			{
				// Get the first child of parent
				Iterator prev_it = it.GetPrev( );
				if ( prev_it.IsValid( ) )
				{
					it = prev_it;
					continue;
				}

				// Get the node
				Node* node = it.GetNode( );
				if ( node == _null )
					return -1;

				// Get the bound of depth
				_qword bound = mTree->mIDBoundRangeOfDepths[ node->mDepth ];

				// Found the first child of parent node
				_qword parent_id = node->mID - bound;
				return parent_id;
			}			
		}
		
		//!	Get the iterator by ID.
		Iterator GetIteratorByID( _qword id ) const
		{
			typename NodeArray::Iterator it = mTree->mNodes.SearchAscending( id );
			if ( it.IsValid( ) == _false || ((const NodePair&) it).mObject2 == _null )
				return Iterator( );

			return Iterator( it.mIndex, mTree );
		}

		//!	Get the parent node.
		Iterator GetParent( ) const
		{
			_qword parent_id = GetParentID( );
			
			return GetIteratorByID( parent_id );
		}
		//!	Get the first child node.
		Iterator GetFirstChild( ) const
		{
			_qword bound = mTree->mIDBoundRangeOfDepths[ GetNode( )->mDepth + 1 ];
			if ( bound != 0 )
			{
				_qword id = GetID( );
				for ( _int i = 1; i < _MAX_NODE_NUMBER_EACH_LEVEL; i ++ )
				{
					Iterator it = GetIteratorByID( id + i * bound );
					if ( it.IsValid( ) )
						return it;
				}
			}

			return Iterator( );
		}
		//!	Get the last child node.
		Iterator GetLastChild( ) const
		{
			_qword bound = mTree->mIDBoundRangeOfDepths[ GetNode( )->mDepth + 1 ];
			if ( bound != 0 )
			{
				_qword id = GetID( );
				for ( _int i = _MAX_NODE_NUMBER_EACH_LEVEL - 1; i > 0; i -- )
				{
					Iterator it = GetIteratorByID( id + i * bound );
					if ( it.IsValid( ) )
						return it;
				}
			}

			return Iterator( );
		}
		//!	Get the previous node.
		Iterator GetPrev( ) const
		{
			const Node* node = GetNode( );
			if ( node == _null )
				return Iterator( );

			_qword bound = mTree->mIDBoundRangeOfDepths[ node->mDepth ];
			if ( bound == 0 )
				return Iterator( );

			_qword prev_id = GetID( ) - bound;

			Iterator prev_it = GetIteratorByID( prev_id );
			if ( prev_it.IsValid( ) == _false )
				return Iterator( );

			if ( prev_it.GetNode( )->mDepth != node->mDepth )
				return Iterator( );

			// Can not be the same node
			EGE_ASSERT( prev_it.mIndex != mIndex );

			return prev_it;
		}
		//!	Get the next node.
		Iterator GetNext( ) const
		{
			const Node* node = GetNode( );
			if ( node == _null )
				return Iterator( );

			_qword bound = mTree->mIDBoundRangeOfDepths[ node->mDepth ];
			if ( bound == 0 )
				return Iterator( );

			_qword next_id = GetID( ) + bound;

			Iterator next_it = GetIteratorByID( next_id );
			if ( next_it.IsValid( ) == _false )
				return Iterator( );

			if ( next_it.GetNode( )->mDepth != node->mDepth )
				return Iterator( );

			// Can not be the same node
			EGE_ASSERT( next_it.mIndex != mIndex );

			return next_it;
		}
	};

private:
	//!	The tree node
	struct Node
	{
		//!	The ID
		_qword	mID;
		//!	The depth of node, start from 0
		_dword	mDepth;

		//!	The node element
		Type	mElement;

		Node( )
			: mID( -1 ), mDepth( -1 ) { }

		Node( _qword id, _dword depth )
			: mID( id ), mDepth( depth ) { }

		Node( _qword id, _dword depth, const Type& element )
			: mID( id ), mDepth( depth ), mElement( element ) { }
	};

private:
	//!	The node list ( map to used ID list one by one )
	NodeArray	mNodes;
	//!	The ID bound range of depths ( Plus 1 to skip check bounds of child nodes )
	_qword		mIDBoundRangeOfDepths[ _MAX_LEVEL_NUMBER + 1 ];

private:
	//!	Check tree.
	_ubool CheckTree( ) const;

	//!	Get the root node.
	Node* GetRootNode( );
	const Node* GetRootNode( ) const;

	//!	Get the unused ID.
	_qword GetUnusedID( Node* parent_node ) const;
	_qword GetUnusedID( _qword start_id, _qword bound ) const;
	//!	Check whether it's full or not (for child nodes).
	_ubool IsFull( Node* parent_node ) const;

	//! Get the bound of child's depth
	_qword GetBoundOfChild( const Node* parent_node ) const;

	//!	Insert node by ID and depth.
	Iterator InsertNodeByIDAndDepth( const Type& element, _qword id, _dword depth );
	//!	Remove node.
	Iterator RemoveNode( Iterator it );
	//!	Remove all child of the node.
	_void RemoveAllChildNodes( Iterator it );

	//!	Move specified child's node to next position.
	_void MoveChildNodeToNext( Iterator parent_it, Iterator child_it );

	//!	Reset all child's ID of the node.
	_void ResetAllChildNodesID( Iterator it );
	//!	Update node's ID.
	_void UpdateNodeID( Iterator it, _qword id );

public:
	LinearTree( );
	~LinearTree( );

public:
	//!	Get the root iterator.
	//!	@param		none.
	//!	@return		The root iterator.
	Iterator GetRootIterator( ) const;
	//!	Get the head iterator.
	//!	@param		none.
	//!	@return		The head iterator.
	Iterator GetHeadIterator( ) const;
	//!	Get the tail iterator.
	//!	@param		none.
	//!	@return		The tail iterator.
	Iterator GetTailIterator( ) const;

	//!	Search the node by ID.
	//!	@param		id			The node ID.
	//!	@return		The node iterator.
	Iterator SearchNodeByID( _qword id ) const;
	//!	Search the node by key.
	//!	@param		key			The node key.
	//!	@return		The node iterator.
	Iterator SearchNodeByKey( const Key& key ) const;
	//!	Insert the node by ID.
	//!	@param		element		The node element.
	//!	@param		depth		The depth.
	//!	@param		id			The node ID.
	//!	@return		The node iterator.
	Iterator InsertNodeByID( const Type& element, _dword depth, _qword id );
	//!	Insert the node as first child.
	//!	@param		element		The node element.
	//!	@param		parent_it	The parent iterator.
	//!	@return		The node iterator.
	Iterator InsertNodeAsFirstChild( const Type& element, Iterator parent_it );
	//!	Insert the node as tail child.
	//!	@param		element		The node element.
	//!	@param		parent_it	The parent iterator.
	//!	@return		The node iterator.
	Iterator InsertNodeAsTailChild( const Type& element, Iterator parent_it );
	//!	Insert the node.
	//!	@param		element		The node element.
	//!	@param		parent_it	The parent iterator.
	//!	@param		prev_it		The previous iterator.
	//!	@return		The node iterator.
	Iterator InsertNode( const Type& element, Iterator parent_it, Iterator prev_it );
	//!	Remove the node by ID.
	//!	@param		id			The node ID.
	//!	@return		True indicates removed successful.
	_ubool RemoveNodeByID( _qword id );
	//!	Remove the node by iterator.
	//!	@param		it			The node iterator.
	//!	@return		The next iterator.
	Iterator RemoveNodeByIterator( Iterator it );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// LinearTree Implementation
//----------------------------------------------------------------------------

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::LinearTree( )
{
	// Initialize bound range of depth
	mIDBoundRangeOfDepths[0] = 0;
	for ( _dword i = 1; i < _MAX_LEVEL_NUMBER + 1; i ++ )
	{
		_qword value = _MAX_NODE_NUMBER_EACH_LEVEL;
		for ( _dword j = i + 1; j < _MAX_LEVEL_NUMBER + 1; j ++ )
			value *= _MAX_NODE_NUMBER_EACH_LEVEL;

		mIDBoundRangeOfDepths[i] = value;
	}

	// Add the root node
	mNodes.Append( NodePair( 0, new Node( 0, 0 ) ) );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::~LinearTree( )
{
	// Get the root node ( because the Clear( ) function will clear all nodes so we need to get root node firstly here )
	NodePair& root_node = mNodes[0];

	// Clear nodes
	Clear( );

	// Remove root node
	EGE_DELETE( root_node.mObject2 );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_ubool LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::CheckTree( ) const
{
	for ( _dword i = 0; i < mNodes.Number( ); i ++ )
	{
		for ( _dword j = i + 1; j < mNodes.Number( ); j ++ )
		{
			if ( mNodes[i].mObject1 == mNodes[j].mObject1 )
			{
				// The ID is duplicate
				EGE_ASSERT( 0 );
				return _false;
			}
		}
	}

	return _true;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Node* LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetRootNode( )
{
	return mNodes[0].mObject2;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
const typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Node* LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetRootNode( ) const
{
	return mNodes[0].mObject2;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_qword LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetUnusedID( Node* parent_node ) const
{
	EGE_ASSERT( parent_node != _null );

	// Get the bound of depth
	_qword bound	= GetBoundOfChild( parent_node );
	_qword id		= parent_node->mID + bound;

	// Try to get the unused ID
	_qword unused_id = GetUnusedID( id, bound );
	if ( unused_id != -1 )
		return unused_id;

	// No any more ID of this parent node
	return -1;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_qword LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetUnusedID( _qword start_id, _qword bound ) const
{
	for ( _dword i = 0; i < _MAX_NODE_NUMBER_EACH_LEVEL; i ++, start_id += bound )
	{
		typename NodeArray::Iterator it = mNodes.SearchAscending( start_id );
		if ( it.IsValid( ) == _false || ((const NodePair&) it).mObject2 == _null )
			return start_id;
	}

	return -1;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_ubool LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::IsFull( Node* parent_node ) const
{
	return GetUnusedID( parent_node ) == - 1;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_qword LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetBoundOfChild( const Node* parent_node ) const
{
	EGE_ASSERT( parent_node != _null );

	return mIDBoundRangeOfDepths[ parent_node->mDepth + 1 ];
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::InsertNodeByIDAndDepth( const Type& element, _qword id, _dword depth )
{
	// Skip for duplicate item
	typename NodeArray::Iterator it = mNodes.SearchAscending( id );
	if ( it.IsValid( ) )
		return Iterator( );

	// Insert node into array
	_dword index = mNodes.InsertAscending( NodePair( id, new Node( id, depth, element ) ) );

	// Increase number of nodes
	CountOf<>::Increase( );

	// Feedback the node
	return Iterator( index, this );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::RemoveNode( Iterator it )
{
	// Get the index
	_dword index = it.mIndex;

	// Get the parent node
	Iterator parent_it = it.GetParent( );
	EGE_ASSERT( parent_it.IsValid( ) );

	// The child bound of depth
	_qword bound = GetBoundOfChild( parent_it.GetNode( ) );

	// Update all next node's ID
	for ( Iterator brother_it = it.GetNext( ); brother_it.IsValid( ); )
	{
		Iterator next_brother_it = brother_it.GetNext( );
		UpdateNodeID( brother_it, brother_it.GetID( ) - bound );

		// Update all child node's ID
		Iterator child_temp_it = brother_it.GetFirstChild( );
		if ( child_temp_it.IsValid( ) )
			ResetAllChildNodesID( brother_it );

		brother_it = next_brother_it;
	}

	// Delete node
	Node* node = mNodes[ index ].mObject2;
	EGE_DELETE( node );

	// Remove it from array
	typename NodeArray::Iterator it_in_array = mNodes.RemoveByIndex( index );

	// Decrease number of nodes
	CountOf<>::Decrease( );

#ifdef _DEBUG
	CheckTree( );
#endif

	// Feedback the next iterator
	if ( it_in_array.IsValid( ) )
		return Iterator( );
	else
		return Iterator( it_in_array.mIndex, this );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_void LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::RemoveAllChildNodes( Iterator it )
{
	for ( Iterator child_it = it.GetFirstChild( ); child_it.IsValid( ); )
	{
		if ( child_it.GetFirstChild( ).IsValid( ) )
			RemoveAllChildNodes( child_it );

		child_it = RemoveNode( child_it );
	}
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_void LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::MoveChildNodeToNext( Iterator parent_it, Iterator child_it )
{
	Node* node = parent_it.GetNode( );

	// The child bound of depth
	_qword bound = GetBoundOfChild( node );

	for ( Iterator child_temp_it = child_it; child_temp_it.IsValid( ); )
	{
		Iterator next_it = child_temp_it.GetNext( );

		if ( child_temp_it.GetFirstChild( ).IsValid( ) )
			MoveChildNodeToNext( child_temp_it, child_temp_it.GetFirstChild( ) );

		// Update ID
		UpdateNodeID( child_temp_it, child_temp_it.GetID( ) + bound );

		// Continue to move
		child_temp_it = next_it;
	}

	// Resort nodes
	mNodes.SortAscending( );

#ifdef _DEBUG
	CheckTree( );
#endif
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_void LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::ResetAllChildNodesID( Iterator it )
{
	Node* node = it.GetNode( );
	EGE_ASSERT( node != _null );

	// The bound of depth
	_qword bound = GetBoundOfChild( node );

	// The ID counter
	_qword id = node->mID + bound;

	// Reset all child nodes ID recursively
	for ( Iterator child_it = it.GetFirstChild( ); child_it.IsValid( ); )
	{
		Iterator next_it = child_it.GetNext( );

		// Update child node ID
		UpdateNodeID( child_it, id );

		// Continue to reset 
		if ( child_it.GetFirstChild( ).IsValid( ) )
			ResetAllChildNodesID( child_it );

		// Increase ID counter
		id += bound;

		// Continue to reset
		child_it = next_it;
	}

	// Resort nodes
	mNodes.SortAscending( );

#ifdef _DEBUG
	CheckTree( );
#endif
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_void LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::UpdateNodeID( Iterator it, _qword id )
{
	mNodes[ it.mIndex ].mObject1 = id;
	it.GetNode( )->mID = id;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetRootIterator( ) const
{
	return Iterator( 0, (LinearTree*) this );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetHeadIterator( ) const
{
	// Except the root node
	for ( _dword i = 1; i < mNodes.Number( ); i ++ )
	{
		if ( mNodes[i].mObject2 != _null )
			return Iterator( i, (LinearTree*) this );
	}

	return Iterator( );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::GetTailIterator( ) const
{
	// Except the root node
	for ( _int i = mNodes.Number( ) - 1; i > 0; i -- )
	{
		if ( mNodes[i].mObject2 != _null )
			return Iterator( i, this );
	}

	return Iterator( );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::SearchNodeByID( _qword id ) const
{
	typename NodeArray::Iterator it = mNodes.SearchAscending( id );
	if ( it.IsValid( ) == _false || ((const NodePair&) it).mObject2 == _null )
		return Iterator( );

	return Iterator( it.mIndex, (LinearTree*) this );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::SearchNodeByKey( const Key& key ) const
{
	for ( _dword i = 0; i < mNodes.Number( ); i ++ )
	{
		if ( mNodes[i].mObject2->mElement == key )
			return Iterator( i, (LinearTree*) this );
	}

	return Iterator( );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::InsertNodeByID( const Type& element, _dword depth, _qword id )
{
	// Check for existing node
	typename NodeArray::Iterator it = mNodes.SearchAscending( id );
	if ( it.IsValid( ) && ((const NodePair&) it).mObject2 != _null )
		return Iterator( ); // This ID had been used

	return InsertNodeByIDAndDepth( element, id, depth );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::InsertNodeAsFirstChild( const Type& element, Iterator parent_it )
{
	// Get the parent node ( null indicates insert to root as child node of it )
	Node* parent_node = parent_it.GetNode( );
	EGE_ASSERT( parent_node != _null );

	// Check for the free space
	if ( IsFull( parent_node ) )
		return Iterator( );

	// Reset all child nodes
	ResetAllChildNodesID( parent_it );

	// Move all child nodes to next position to free the first ID 
	MoveChildNodeToNext( parent_it, parent_it.GetFirstChild( ) );

	// Get the unused ID
	_qword id = GetUnusedID( parent_node );
	EGE_ASSERT( id != -1 );

	// Add node
	return InsertNodeByIDAndDepth( element, id, parent_node->mDepth + 1 );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::InsertNodeAsTailChild( const Type& element, Iterator parent_it )
{
	// Get the parent node ( null indicates insert to root as child node of it )
	Node* parent_node = parent_it.GetNode( );

	// Check for the free space
	if ( IsFull( parent_node ) )
		return Iterator( );

	// Reset all child nodes
	ResetAllChildNodesID( parent_it );

	// Get the unused ID
	_qword id = GetUnusedID( parent_node );
	EGE_ASSERT( id != -1 );

	// Add node
	return InsertNodeByIDAndDepth( element, id, parent_node->mDepth + 1 );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::InsertNode( const Type& element, Iterator parent_it, Iterator prev_it )
{
	EGE_ASSERT( prev_it.IsValid( ) );

	// Get the parent node ( null indicates insert to root as child node of it )
	Node* parent_node = parent_it.GetNode( );
	EGE_ASSERT( parent_node != _null );

	// Check for the free space
	if ( IsFull( parent_node ) )
		return Iterator( );

	// Reset all child nodes
	ResetAllChildNodesID( parent_it );

	// If the next node of previous is existing then we need to move it
	Iterator next_it_of_prev = prev_it.GetNext( );
	if ( next_it_of_prev.IsValid( ) )
		MoveChildNodeToNext( parent_it, next_it_of_prev );

	// Get the unused ID
	_qword id = GetUnusedID( parent_node );
	EGE_ASSERT( id != -1 );

	// Add node
	return InsertNodeByID( element, parent_node->mDepth + 1, id );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_ubool LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::RemoveNodeByID( _qword id )
{
	// We can't remove the root node
	if ( id == 0 )
		return _false;

	// Check for existing node
	typename NodeArray::Iterator it = mNodes.SearchAscending( id );
	if ( it.IsValid( ) == _false || ((const NodePair&) it).mObject2 == _null )
		return _false;

	// Create iterator of node
	Iterator node_it( it.mIndex, this );

	// Remove by iterator
	RemoveNodeByIterator( node_it );

	return _true;
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
typename LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Iterator LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::RemoveNodeByIterator( Iterator it )
{
	// Remove all child of it
	RemoveAllChildNodes( it );

	// Remove node
	return RemoveNode( it );
}

template< _dword _MAX_LEVEL_NUMBER, _dword _MAX_NODE_NUMBER_EACH_LEVEL, typename Type, typename Key > 
_void LinearTree< _MAX_LEVEL_NUMBER, _MAX_NODE_NUMBER_EACH_LEVEL, Type, Key >::Clear( )
{
	// Release all nodes except the root node
	for ( _dword i = 1; i < mNodes.Number( ); i ++ )
		EGE_DELETE( mNodes[i].mObject2 );

	mNodes.Clear( );

	CountOf<>::Clear( );
}

}