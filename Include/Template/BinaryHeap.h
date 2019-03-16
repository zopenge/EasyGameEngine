//! @file     BinaryHeap.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BinaryHeap
//----------------------------------------------------------------------------

//! This class is template container class, represents a binary heap.
template< _dword _MAX_SIZE, typename Type, typename CompareFunc = Compare< Type > > 
class BinaryHeap
{
public:
	//! The iterator of binary heap class.
	struct Iterator
	{
		//! The heap reference.
		BinaryHeap< _MAX_SIZE, Type, CompareFunc >*	mHeap;
		//! The current index of the element index array.
		_dword										mIndex;

		//! Constructor, create an iterator of the heap.
		//! @param		none.
		Iterator( ) 
			: mHeap( _null ), mIndex( -1 ) { }
		//! Constructor, create an iterator of the heap.
		//! @param		heap		The heap reference.
		//! @param		index		The current index of the element.
		Iterator( BinaryHeap< _MAX_SIZE, Type, CompareFunc >* heap, _dword index )
			: mHeap( heap ), mIndex( index ) { }

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type& ( )
			{ return mHeap->mElements[ mIndex ]; }
		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator const Type& ( ) const
			{ return mHeap->mElements[ mIndex ]; }

		//! Decrease the iterator, point to the previous element of the array.
		//! @param		none
		_void operator -- ( _int )
			{ mIndex --; }		
		//! Increase the iterator, point to the next element of the array.
		//! @param		none
		_void operator ++ ( _int )
			{ mIndex ++; }

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid( ) const
			{ return mHeap != _null && mIndex < mHeap->mElements.Number( ); }
	};

private:
	//!	Here we use the 0 index as root element, so need to 1 more size
	typedef FixedArray< Type, _MAX_SIZE + 1 > ElementArray;

private:
	//!	The swap element callback function.
	typedef _void (*OnSwapElement)( _dword index1, Type& e1, _dword index2, Type& e2 );
	static _void OnSwapElementDummyFunc( _dword index1, Type& e1, _dword index2, Type& e2 ) { }

private:
	//!	The element array
	ElementArray	mElements;

	//!	THe callback functions
	OnSwapElement	mSwapElementFunc;

private:
	//!	Get the parent index.
	_dword GetParentIndex( _dword index ) const
		{ return index >> 1; }
	//!	Get the left child index.
	_dword GetLeftChildIndex( _dword index ) const
		{ return index << 1; }
	//!	Get the right child index.
	_dword GetRightChildIndex( _dword index ) const
		{ return ( index << 1 ) + 1; }

	//!	Get the element by index.
	Type& GetElementByIndex( _dword index )
		{ return mElements[ index ]; }
	//!	Get the parent element by index.
	Type& GetParentElementByIndex( _dword index )
		{ return mElements[ GetParentIndex( index ) ]; }

	//!	Swap tow elements.
	_void SwapElements( _dword index1, _dword index2 )
	{
		if ( index1 == index2 )
			return;

		mSwapElementFunc( index1, mElements[ index1 ], index2, mElements[ index2 ] );
		Swap( mElements[ index1 ], mElements[ index2 ] ); 
	}

	//!	Restores the heap property starting from a given node.
	//!	@param		index		The element index.
	//!	@return		none.
	_void Heapify( _dword index );
	//!	Sort and update the top element by compare function.
	//!	@param		index		The element index.
	//!	@return		The new index of element after sorting.
	_dword Sort( _dword index );

public:
	//! Constructor, create an empty binary heap.
	//! @param		none.
	BinaryHeap( );
	//! Copy-Constructor, create a binary heap by copy from another one.
	//! @param		heap		The other binary heap.
	BinaryHeap( const BinaryHeap< _MAX_SIZE, Type, CompareFunc >& heap );
	//! Destructor, delete the binary heap, and release the memory used by nodes.
	//! @param		none
	~BinaryHeap( );

public:
	//! Copy elements from another binary heap.
	//! @param		heap		The other binary heap.
	//! @return		The reference of current heap.
	BinaryHeap< _MAX_SIZE, Type, CompareFunc >& operator = ( const BinaryHeap< _MAX_SIZE, Type, CompareFunc >& heap );

	//!	Set the swap element callback function.
	//! @param		funcpointer	The callback function pointer.
	//! @return		none.
	_void SetSwapElementCallbackFunc( OnSwapElement funcpointer );

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator( ) const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator( ) const;

	//!	Get the top iterator.
	//! @param		none.
	//! @return		An iterator reference to the element.
	Iterator GetTopIterator( ) const;
	//!	Get the top element.
	//! @param		none.
	//! @return		The element referenced pointer.
	Type* GetTopElement( );
	//!	Get the top element.
	//! @param		none.
	//! @return		The element referenced pointer.
	const Type* GetTopElement( ) const;

	//! Get the current number of elements in array.
	//! @param		none
	//! @return		The current number of elements in array.
	_dword Number( ) const;

	//!	Insert an element.
	//! @param		element		The new element to be inserted.
	//! @return		The index of element.
	_dword Insert( const Type& element );
	//!	Remove an element.
	//! @param		index		The index of element.
	//! @return		none.
	_void Remove( _dword index );

	//! Extract and remove an top element from the heap.
	//! @param		top_element	The top element.
	//! @return		True indicates success, false indicates failure.
	_ubool ExtractTopElement( Type& top_element );
	//!	Remove the top element.
	//! @param		none.
	//! @return		none.
	_void RemoveTopElement( );
	//!	Try to bring up the tail element to the top.
	//!	@param		none.
	//!	@return		The new index of tail element.
	_dword BringTailElementToTop( );

	//! Clear.
	//! @param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// BinaryHeap Implementation
//----------------------------------------------------------------------------

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
BinaryHeap< _MAX_SIZE, Type, CompareFunc >::BinaryHeap( )
{
	mSwapElementFunc = OnSwapElementDummyFunc;

	// The initial element to make sure all leafs can reach
	mElements.Append( Type( ) );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
BinaryHeap< _MAX_SIZE, Type, CompareFunc >::BinaryHeap( const BinaryHeap< _MAX_SIZE, Type, CompareFunc >& heap )
{
	mElements = heap.mElements;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
BinaryHeap< _MAX_SIZE, Type, CompareFunc >::~BinaryHeap( )
{
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_void BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Heapify( _dword index )
{
	while ( _true )
	{
		_dword left				= GetLeftChildIndex( index );
		_dword right			= GetRightChildIndex( index );
		_dword smallest_index	= index;

		if ( left < mElements.Number( ) )
		{
			Type& left_element	= GetElementByIndex( left );
			Type& element		= GetElementByIndex( index );

			if ( CompareFunc( )( left_element, element ) < 0 )
				smallest_index = left;
		}

		if ( right < mElements.Number( ) )
		{
			Type& right_element		= GetElementByIndex( right );
			Type& smallest_element	= GetElementByIndex( smallest_index );

			if ( CompareFunc( )( right_element, smallest_element ) < 0 )
				smallest_index = right;
		}

		if ( smallest_index == index )
			break;

		// Swap the elements
		SwapElements( smallest_index, index );

		// Update the index and continue to sort
		index = smallest_index;
	}
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_dword BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Sort( _dword index )
{
	// Sort the heap
	while ( index > 1 && CompareFunc( )( GetParentElementByIndex( index ), mElements[ index ] ) > 0 )
	{
		// Make the parent is always smaller than element
		SwapElements( GetParentIndex( index ), index );

		// Jump to the parent to keep pop the minimal element to the root node
		index = GetParentIndex( index );
	}

	return index;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
BinaryHeap< _MAX_SIZE, Type, CompareFunc >& BinaryHeap< _MAX_SIZE, Type, CompareFunc >::operator = ( const BinaryHeap< _MAX_SIZE, Type, CompareFunc >& heap )
{
	Clear( );

	mElements = heap.mElements;

	return *this;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_void BinaryHeap< _MAX_SIZE, Type, CompareFunc >::SetSwapElementCallbackFunc( OnSwapElement funcpointer )
{
	if ( funcpointer != _null )
		mSwapElementFunc = funcpointer;
	else
		mSwapElementFunc = OnSwapElementDummyFunc;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
typename BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Iterator BinaryHeap< _MAX_SIZE, Type, CompareFunc >::GetHeadIterator( ) const
{
	if ( Number( ) == 0 )
		return Iterator( );

	return Iterator( (BinaryHeap< _MAX_SIZE, Type, CompareFunc >*) this, 0 );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
typename BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Iterator BinaryHeap< _MAX_SIZE, Type, CompareFunc >::GetTailIterator( ) const
{
	if ( Number( ) == 0 )
		return Iterator( );

	return Iterator( (BinaryHeap< _MAX_SIZE, Type, CompareFunc >*) this, mElements.Number( ) - 1 );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
typename BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Iterator BinaryHeap< _MAX_SIZE, Type, CompareFunc >::GetTopIterator( ) const
{
	if ( Number( ) == 0 )
		return Iterator( );

	// Use 1 as the begin index, because we need to make sure all the leafs can reach
	return Iterator( (BinaryHeap< _MAX_SIZE, Type, CompareFunc >*) this, 1 );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
Type* BinaryHeap< _MAX_SIZE, Type, CompareFunc >::GetTopElement( )
{
	if ( Number( ) == 0 )
		return _null;

	return &mElements[1];
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
const Type* BinaryHeap< _MAX_SIZE, Type, CompareFunc >::GetTopElement( ) const
{
	if ( Number( ) == 0 )
		return _null;

	return &mElements[1];
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_dword BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Number( ) const
{
	// We have a initial element in index 0
	return mElements.Number( ) - 1;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_dword BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Insert( const Type& element )
{
	mElements.Append( element );

	return BringTailElementToTop( );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_void BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Remove( _dword index )
{
	EGE_ASSERT( index <= Number( ) );

	// Move the tail element to the removed node location in order to sort the heap
	SwapElements( index, Number( ) );

	// Remove the tail node what had been exchanged
	mElements.RemoveByIndex( Number( ) );

	// Sort the heap from root
	Heapify( index );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_ubool BinaryHeap< _MAX_SIZE, Type, CompareFunc >::ExtractTopElement( Type& top_element )
{
	if ( Number( ) == 0 )
		return _false;

	// Feedback the minimal element
	top_element = mElements[1];

	// Remove the minimal element
	RemoveTopElement( );

	return _true;
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_void BinaryHeap< _MAX_SIZE, Type, CompareFunc >::RemoveTopElement( )
{
	if ( Number( ) == 0 )
		return;

	// Remove the top element
	Remove( 1 );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_dword BinaryHeap< _MAX_SIZE, Type, CompareFunc >::BringTailElementToTop( )
{
	if ( Number( ) == 0 )
		return -1;

	return Sort( mElements.Number( ) - 1 );
}

template< _dword _MAX_SIZE, typename Type, typename CompareFunc >
_void BinaryHeap< _MAX_SIZE, Type, CompareFunc >::Clear( )
{
	mElements.Clear( );

	// The initial element to make sure all leafs can reach
	mElements.Append( Type( ) );
}

}