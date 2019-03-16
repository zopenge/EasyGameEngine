//! @file     Pool.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Pool
//----------------------------------------------------------------------------

//! This class is template container class, represents a pool.
template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
class Pool
{
protected:
	//!	The base iterator of pool
	template< typename PoolType >
	struct BaseIterator
	{
		//!	The index of node buffer
		_dword		mIndex;
		//! The pool reference.
		PoolType*	mPool;

		//! Constructor, create an iterator of the pool.
		BaseIterator( _dword index = -1, PoolType* pool = _null )
			: mIndex( index ), mPool( pool ) { }

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid( ) const
			{ return mIndex < _MAX_NUMBER; }

		//! Increase the iterator, point to the next element of the pool.
		//! @param		none
		_void operator ++ ( _int )
		{
			while ( mIndex < _MAX_NUMBER )
			{
				mIndex ++;

				if ( mPool->mIDTracker.HasEntry( mIndex ) )
					break;
			}
		}
		
		//! decrease the iterator, point to the previous element of the pool.
		//! @param		none
		_void operator -- ( _int )
		{
			while ( mIndex < _MAX_NUMBER )
			{
				mIndex --;

				if ( mPool->mIDTracker.HasEntry( mIndex ) )
					break;
			}
		}
	};

public:
	//!	The iterator of pool
	struct Iterator : public BaseIterator< Pool< Type, _MAX_NUMBER > >
	{
		typedef BaseIterator< Pool< Type, _MAX_NUMBER > > TBaseClass;

		//! Constructor, create an iterator of the pool.
		Iterator( _dword index = -1, Pool< Type, _MAX_NUMBER >* pool = _null )
			: TBaseClass( index, pool ) { }

		//! Type conversion, get the pair reference.
		//! @param		none
		//! @return		Reference of the pair.
		operator Type& ( )
            { return TBaseClass::mPool->mNodeBuffer[ TBaseClass::mIndex ]; }
		//! Type conversion, get the pair reference.
		//! @param		none
		//! @return		Reference of the pair.
		operator const Type& ( ) const
            { return TBaseClass::mPool->mNodeBuffer[ TBaseClass::mIndex ]; }
	};

	//!	The const iterator of pool
	struct ConstIterator : public BaseIterator< const Pool< Type, _MAX_NUMBER > >
	{
		typedef BaseIterator< const Pool< Type, _MAX_NUMBER > > TBaseClass;

		//! Constructor, create an iterator of the pool.
		ConstIterator( _dword index = -1, const Pool< Type, _MAX_NUMBER >* pool = _null )
			: TBaseClass( index, pool ) { }

		//! Type conversion, get the pair reference.
		//! @param		none
		//! @return		Reference of the pair.
		operator const Type& ( ) const
            { return TBaseClass::mPool->mNodeBuffer[ TBaseClass::mIndex ]; }
	};

private:
	//!	The ID tracker
	IDTracker< _MAX_NUMBER >	mIDTracker;
	//!	The tree node buffer
	Type						mNodeBuffer[ _MAX_NUMBER ];

public:
	//! Constructor, create an empty pool.
	//! @param		size		The maximal size of the pool in number of element.
	Pool( );
	//! Copy-Constructor, create a pool by copy from another one.
	//! @param		pool		The other pool.
	Pool( const Pool< Type, _MAX_NUMBER >& pool );
	//! Destructor, delete the pool, and release the memory used by nodes.
	//! @param		none
	~Pool( );

public:
	//! Copy elements from another pool.
	//! @param		pool		The other pool.
	//! @return		The reference of current pool.
	Pool< Type, _MAX_NUMBER >& operator = ( const Pool< Type, _MAX_NUMBER >& pool );

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator( );
	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	ConstIterator GetHeadIterator( ) const;

	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator( );
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	ConstIterator GetTailIterator( ) const;

	//! Get an iterator by the index of an element.
	//! @param		index		The index of the element in pool.
	//! @return		An iterator reference to the element.
	Iterator GetIterator( _dword index );
	//! Get an iterator by the an element.
	//! @param		element		The address of the element in pool.
	//! @return		An iterator reference to the element.
	Iterator GetIterator( const Type* element );

	//! Get the current number of elements in the pool.
	//! @param		none.
	//! @return		The current number of elements in pool.
	_dword Number( ) const;
	//! Get the maximal size of the pool in number of element.
	//! @param		none.
	//! @return		The size of the pool.
	_dword GetMaxNumber( ) const;

	//!	Get the node buffer pointer.
	//!	@param		none.
	//!	@return		The address of node buffer.
	const _byte* GetNodeBuffer( ) const;

	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index from the pool.
	//! @param		index		The index of the element in pool.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	Type* Index( _dword index );
	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index from the pool.
	//! @param		index		The index of the element in pool.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	const Type* Index( _dword index ) const;

	//!	Check whether has this element or not.
	//!	@param		index		The index of the element to be checked.
	//!	@return		True indicates this element is existing and valid.
	_ubool HasElement( _dword index ) const;

	//! Create a node to store element in the pool.
	//! @param		element		The element to be stored in the pool.
	//!	@param		index		The index of the element to be stored.
	//! @return		The address of element, or null indicates there is no more node to store it.
	Type* Create( _dword* index = _null );
	//! Insert an element into the pool at specified index.
	//! @param		index		The index specifies a position.
	//! @return		The address of element, or null indicates there is no more node to store it.
	Type* Insert( _dword index );
	//! Create a node to store element in the pool.
	//! @param		element		The element to be stored in the pool.
	//! @return		The index of the element if it can be stored, or -1 indicates there is no more node to store it.
	_dword Insert( const Type& element );
	//! Insert an element into the pool at specified index.
	//! @param		element		The element to be inserted.
	//! @param		index		The index specifies a position.
	//! @return		True indicates success, false indicates failure.
	_ubool Insert( const Type& element, _dword index );
	//! Remove an element from the pool, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		The next iterator.
	Iterator Remove( Iterator iterator );
	//! Remove an element from the pool, the element is specified by an index.
	//! @param		index		The index specifies a position.
	//!	@return		True indicates remove successful.
	_ubool Remove( _dword index );
	//! Remove an element from the pool, the element is specified by an index.
	//! @param		pointer		The element address.
	//!	@return		True indicates remove successful.
	_ubool Remove( Type* pointer );

	//! Clear pool.
	//! @param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// Pool Implementation
//----------------------------------------------------------------------------

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Pool< Type, _MAX_NUMBER >::Pool( )
{
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Pool< Type, _MAX_NUMBER >::Pool( const Pool< Type, _MAX_NUMBER >& pool )
{
	mIDTracker	= pool.mIDTracker;

	for ( _dword i = 0; i < _MAX_NUMBER; i ++ )
		mNodeBuffer[i] = pool.mNodeBuffer[i];
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Pool< Type, _MAX_NUMBER >::~Pool( )
{
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Pool< Type, _MAX_NUMBER >& Pool< Type, _MAX_NUMBER >::operator = ( const Pool< Type, _MAX_NUMBER >& pool )
{
	Clear( );

	mIDTracker	= pool.mIDTracker;

	for ( _dword i = 0; i < _MAX_NUMBER; i ++ )
		mNodeBuffer[i] = pool.mNodeBuffer[i];

	return *this;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::Iterator Pool< Type, _MAX_NUMBER >::GetHeadIterator( )
{
	if ( Number( ) > 0 )
	{
		for ( _dword i = 0; i < _MAX_NUMBER; i ++ )
		{
			if ( mIDTracker.HasEntry( i ) )
				return Iterator( i, this );
		}
	}

	return Iterator( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::ConstIterator Pool< Type, _MAX_NUMBER >::GetHeadIterator( ) const
{
	if ( Number( ) > 0 )
	{
		for ( _dword i = 0; i < _MAX_NUMBER; i ++ )
		{
			if ( mIDTracker.HasEntry( i ) )
				return ConstIterator( i, this );
		}
	}

	return ConstIterator( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::Iterator Pool< Type, _MAX_NUMBER >::GetTailIterator( )
{
	if ( Number( ) > 0 )
	{
		for ( _int i = _MAX_NUMBER - 1; i >= 0; i -- )
		{
			if ( mIDTracker.HasEntry( i ) )
				return Iterator( i, this );
		}
	}

	return Iterator( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::ConstIterator Pool< Type, _MAX_NUMBER >::GetTailIterator( ) const
{
	if ( Number( ) > 0 )
	{
		for ( _int i = _MAX_NUMBER - 1; i >= 0; i -- )
		{
			if ( mIDTracker.HasEntry( i ) )
				return ConstIterator( i, this );
		}
	}

	return ConstIterator( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::Iterator Pool< Type, _MAX_NUMBER >::GetIterator( _dword index )
{
	if ( mIDTracker.HasEntry( index ) == _false )
		return Iterator( );

	return Iterator( index, this );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::Iterator Pool< Type, _MAX_NUMBER >::GetIterator( const Type* element )
{
	return GetIterator( element - mNodeBuffer );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_dword Pool< Type, _MAX_NUMBER >::Number( ) const
{
	return mIDTracker.GetUsedNumber( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_dword Pool< Type, _MAX_NUMBER >::GetMaxNumber( ) const
{
	return mIDTracker.GetMaxNumber( );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
const _byte* Pool< Type, _MAX_NUMBER >::GetNodeBuffer( ) const
{
	return (const _byte*) mNodeBuffer;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Type* Pool< Type, _MAX_NUMBER >::Index( _dword index )
{
	if ( mIDTracker.HasEntry( index ) == _false )
		return _null;

	return &mNodeBuffer[ index ];
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
const Type* Pool< Type, _MAX_NUMBER >::Index( _dword index ) const
{
	if ( mIDTracker.HasEntry( index ) == _false )
		return _null;

	return &mNodeBuffer[ index ];
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_ubool Pool< Type, _MAX_NUMBER >::HasElement( _dword index ) const
{
	return Index( index ) != _null;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Type* Pool< Type, _MAX_NUMBER >::Create( _dword* index )
{
	// Allocate entry ID
	_dword id = mIDTracker.AllocateEntry( );
	if ( id == -1 )
		return _null;

	// Feedback the index of node
	if ( index != _null )
		*index = id;

	return &mNodeBuffer[ id ];
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
Type* Pool< Type, _MAX_NUMBER >::Insert( _dword index )
{
	if ( mIDTracker.ForceAllocateEntry( index ) == _false )
		return _null;

	return &mNodeBuffer[ index ];
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_dword Pool< Type, _MAX_NUMBER >::Insert( const Type& element )
{
	// Allocate entry ID
	_dword id = mIDTracker.AllocateEntry( );
	if ( id == -1 )
		return _null;

	EGE_ASSERT( id < _MAX_NUMBER );
	mNodeBuffer[ id ] = element;

	return id;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_ubool Pool< Type, _MAX_NUMBER >::Insert( const Type& element, _dword index )
{
	if ( mIDTracker.ForceAllocateEntry( index ) == _false )
		return _false;

	mNodeBuffer[ index ] = element;

	return _true;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
typename Pool< Type, _MAX_NUMBER >::Iterator Pool< Type, _MAX_NUMBER >::Remove( Iterator iterator )
{
	EGE_ASSERT( iterator.IsValid( ) );

	Iterator next_it = iterator;
	next_it ++;

	// Remove it from ID tracker
	mIDTracker.RemoveEntry( iterator.mIndex );

	return next_it;
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_ubool Pool< Type, _MAX_NUMBER >::Remove( _dword index )
{
	// Remove it from ID tracker
	return mIDTracker.RemoveEntry( index );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_ubool Pool< Type, _MAX_NUMBER >::Remove( Type* pointer )
{
	if ( pointer == _null )
		return _false;

	return mIDTracker.RemoveEntry( _dword( pointer - mNodeBuffer ) );
}

template< typename Type, _ENUM_VALUE _MAX_NUMBER > 
_void Pool< Type, _MAX_NUMBER >::Clear( )
{
	mIDTracker.Clear( );
}

}