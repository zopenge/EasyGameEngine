//! @file     List.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// List
//----------------------------------------------------------------------------

template< typename Type, typename Key = Type > 
class List : public Link< Type >
{
public:
	//! Constructor, create an empty list.
	//! @param		none
	List( );
	//! Copy-Constructor, create a list by copy from another one.
	//! @param		list		The other list.
	List( const List< Type, Key >& list );
	//! Destructor, delete the list, and release the memory used by nodes.
	//! @param		none
	~List( );

public:
	//! Copy elements from another list, and allocates nodes to hold it.
	//! @param		list		The other list.
	//! @return		The reference of current list.
	List< Type, Key >& operator = ( const List< Type, Key >& list );

public:
	//! Insert a node into the link at head.
	//! @param		node		The node to be inserted.
	_void InsertHead( typename Link< Type >::Node* node );
	//! Insert a node into the link at tail.
	//! @param		node		The node to be inserted.
	_void InsertTail( typename Link< Type >::Node* node );
	//! Insert a node into the link before the position specified by an iterator.
	//! @param		node		The node to be inserted.
	//! @param		iterator	The iterator specifies a position.
	_void InsertBefore( typename Link< Type >::Node* node, const typename Link< Type >::Iterator& iterator );
	//! Insert a node into the link after the position specified by an iterator.
	//! @param		node		The node to be inserted.
	//! @param		iterator	The iterator specifies a position.
	_void InsertAfter( typename Link< Type >::Node* node, const typename Link< Type >::Iterator& iterator );
	//! Remove a node from the link.
	//! @param		node		The node to be removed.
	//!	@param		none.
	_void Remove( typename Link< Type >::Node* node );

	//! Insert an element into the list at head.
	//! @param		element		The element to be inserted.
	//!	@return		The node to be inserted.
	typename Link< Type >::Node* InsertHead( const Type& element );
	//! Insert an element into the list at tail.
	//! @param		element		The element to be inserted.
	//!	@return		The node to be inserted.
	typename Link< Type >::Node* InsertTail( const Type& element );
	//! Insert an element into the list before the position specified by an iterator.
	//! @param		element		The element to be inserted.
	//!	@return		The node to be inserted.
	typename Link< Type >::Node* InsertBefore( const Type& element, const typename Link< Type >::Iterator& iterator );
	//! Insert an element into the list after the position specified by an iterator.
	//! @param		element		The element to be inserted.
	//!	@return		The node to be inserted.
	typename Link< Type >::Node* InsertAfter( const Type& element, const typename Link< Type >::Iterator& iterator );
	//! Remove an element from the list, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//! @return		none.
	_void Remove( typename Link< Type >::Iterator& iterator );

	//! Search an element in the list.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	typename Link< Type >::Iterator Search( const Key& key ) const;
	//! Remove an element from the list.
	//! @param		key			The key of element to be searched.
	//! @return		True if the element is removed, false otherwise.
	_ubool Remove( const Key& key );

	//! Clear list and delete all memory used by nodes.
	//! @param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// List Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key >
List< Type, Key >::List( )
{
}

template< typename Type, typename Key >
List< Type, Key >::List( const List< Type, Key >& list )
{
	for ( typename Link< Type >::Node* node = list.mHead; node != _null; node = node->mNext )
		InsertTail( node->mElement );
}

template< typename Type, typename Key >
List< Type, Key >::~List( )
{
	Clear( );
}

template< typename Type, typename Key >
List< Type, Key >& List< Type, Key >::operator = ( const List< Type, Key >& list )
{
	Clear( );

	for ( typename Link< Type >::Node* node = list.mHead; node != _null; node = node->mNext )
		InsertTail( node->mElement );

	return *this;
}

template< typename Type, typename Key >
_void List< Type, Key >::InsertHead( typename Link< Type >::Node* node )
{
	Link< Type >::InsertHead( node );
}

template< typename Type, typename Key >
_void List< Type, Key >::InsertTail( typename Link< Type >::Node* node )
{
	Link< Type >::InsertTail( node );
}

template< typename Type, typename Key >
_void List< Type, Key >::InsertBefore( typename Link< Type >::Node* node, const typename Link< Type >::Iterator& iterator )
{
	Link< Type >::InsertBefore( node, iterator );
}

template< typename Type, typename Key >
_void List< Type, Key >::InsertAfter( typename Link< Type >::Node* node, const typename Link< Type >::Iterator& iterator )
{
	Link< Type >::InsertAfter( node, iterator );
}

template< typename Type, typename Key >
_void List< Type, Key >::Remove( typename Link< Type >::Node* node )
{
	Link< Type >::Remove( node );

	EGE_DELETE( node );
}

template< typename Type, typename Key >
typename Link< Type >::Node* List< Type, Key >::InsertHead( const Type& element )
{
	typename Link< Type >::Node* node = new typename Link< Type >::Node( element );
	Link< Type >::InsertHead( node );

	return node;
}

template< typename Type, typename Key >
typename Link< Type >::Node* List< Type, Key >::InsertTail( const Type& element )
{
	typename Link< Type >::Node* node = new typename Link< Type >::Node( element );
	Link< Type >::InsertTail( node );

	return node;
}

template< typename Type, typename Key >
typename Link< Type >::Node* List< Type, Key >::InsertBefore( const Type& element, const typename Link< Type >::Iterator& iterator )
{
	typename Link< Type >::Node* node = new typename Link< Type >::Node( element );
	Link< Type >::InsertBefore( node, iterator );

	return node;
}

template< typename Type, typename Key >
typename Link< Type >::Node* List< Type, Key >::InsertAfter( const Type& element, const typename Link< Type >::Iterator& iterator )
{
	typename Link< Type >::Node* node = new typename Link< Type >::Node( element );
	Link< Type >::InsertAfter( node, iterator );

	return node;
}

template< typename Type, typename Key >
_void List< Type, Key >::Remove( typename Link< Type >::Iterator& iterator )
{
	EGE_ASSERT( iterator.IsValid( ) );

	Link< Type >::Remove( iterator.mNode );

	EGE_DELETE( iterator.mNode );
}

template< typename Type, typename Key >
typename Link< Type >::Iterator List< Type, Key >::Search( const Key& key ) const
{
	for ( typename Link< Type >::Node* node = Link< Type >::mHead; node != _null; node = node->mNext )
	{
		if ( node->mElement == key )
			return typename Link< Type >::Iterator( node );
	}

	return typename Link< Type >::Iterator( _null );
}

template< typename Type, typename Key >
_ubool List< Type, Key >::Remove( const Key& key )
{
	typename Link< Type >::Iterator it = Search( key );
	if ( it.IsValid( ) == _false )
		return _false;

	Remove( it );

	return _true;
}

template< typename Type, typename Key >
_void List< Type, Key >::Clear( )
{
	while ( Link< Type >::mHead != _null )
	{
		typename Link< Type >::Node* node = Link< Type >::mHead; 
		Link< Type >::mHead = node->mNext;

		delete node;
	}

	Link< Type >::Clear( );
}

}