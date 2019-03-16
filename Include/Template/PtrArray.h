//! @file     PtrArray.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PtrArray
//----------------------------------------------------------------------------

//! This class is template container class, represents a array.
template< typename Type, typename Key, typename KeyConverter = PtrType2Key< Type, Key > >
class PtrArray : public CountOf<>
{
public:
	typedef Type ElementType;

public:
	//! The iterator of array class, provides ++ and -- operator to walk through the array.
	struct Iterator
	{
		//! The array reference.
		PtrArray< Type, Key, KeyConverter >*	mArray;
		//! The current index of the element.
		_dword									mIndex;

		//! Constructor, create an iterator of the array.
		//! @param		none.
		Iterator( ) 
			: mArray( _null ), mIndex( -1 ) { }
		//! Constructor, create an iterator of the array.
		//! @param		array		The array reference.
		//! @param		index		The current index of the element.
		Iterator( PtrArray< Type, Key, KeyConverter >* array, _dword index )
			: mArray( array ), mIndex( index ) { }

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type& ( )
			{ return (*mArray)[ mIndex ]; }
		//! Get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		Type& GetObject( )
			{ return (*mArray)[ mIndex ]; }
		//! Get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		const Type& GetObject( ) const
			{ return (*mArray)[ mIndex ]; }

		//! Decrease the iterator, point to the previous element of the array.
		//! @param		none
		_void operator -- ( )
			{ mIndex --; }		
		_void operator -- ( _int )
			{ mIndex --; }		
		//! Increase the iterator, point to the next element of the array.
		//! @param		none
		_void operator ++ ( )
			{ mIndex ++; }
		_void operator ++ ( _int )
			{ mIndex ++; }

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid( ) const
			{ return mArray != _null && mIndex < mArray->Number( ); }
	};

private:
	//! The allocated size of the array in number of element.
	_dword	mAllocedSize;
	//! The memory pointer of the array.
	Type*	mElements;

private:
	//! Grow.
	//! @param		none.
	//!	@return		none.
	_void Grow( );

public:
	//! Constructor, create an empty array.
	//! @param		none.
	PtrArray( );
	//! Copy-Constructor, create an array by copy from another one.
	//! @param		array		The other array.
	PtrArray( const PtrArray< Type, Key, KeyConverter >& array );
	//! Destructor, delete the array, and release the elements memory.
	//! @param		none
	~PtrArray( );

public:
	//! Copy elements from another array, and recreates memory to hold it.
	//! @param		array		The other array.
	//! @return		The reference of current array.
	PtrArray< Type, Key, KeyConverter >& operator = ( const PtrArray< Type, Key, KeyConverter >& array );

	//! Append elements from another array, and recreates memory to hold it.
	//! @param		array		The other array.
	//! @return		The reference of current array.
	PtrArray< Type, Key, KeyConverter >& operator += ( const PtrArray< Type, Key, KeyConverter >& array );

	//! Get a const element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The const element reference.
	const Type& operator [] ( _dword index ) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The mutable element reference.
	Type& operator [] ( _dword index );

	//! Get the current size of elements buffer in array.
	//! @param		none
	//! @return		The current size of elements buffer in array.
	_dword Size( ) const;
	//!	Get the array buffer.
	//!	@param		none.
	//!	@return		The element buffer pointer.
	Type* GetBuffer( );
	//!	Get the array buffer.
	//!	@param		none.
	//!	@return		The element buffer pointer.
	const Type* GetBuffer( ) const;

	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index from the array.
	//! @param		index		The index of the element in array.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	Type* Index( _dword index );

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator( ) const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator( ) const;
	//! Get an iterator by the index of an element.
	//! @param		index		The index of the element in array.
	//! @return		An iterator reference to the element.
	Iterator GetIterator( _dword index ) const;

	//! Get a const element from the head of array.
	//! @param		none.
	//! @return		The const head element reference.
	const Type& GetHeadElement( ) const;
	//! Get a mutable element from the head of array.
	//! @param		none.
	//! @return		The mutable head element reference.
	Type& GetHeadElement( );

	//! Get a const element from the tail of array.
	//! @param		none.
	//! @return		The const tail element reference.
	const Type& GetTailElement( ) const;
	//! Get a mutable element from the tail of array.
	//! @param		none.
	//! @return		The mutable tail element reference.
	Type& GetTailElement( );

	//! Search an element by the key in the array.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator Search( const Key& key ) const;
	//!	Search element by key in ascending way.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator SearchAscending( const Key& key ) const;
	//!	Search element by key in descending way.
	//! @param		key			The key of element to be searched.
	//! @return		The const iterator points to the element in array.
	Iterator SearchDescending( const Key& key ) const;

	//!	Return the index of element by upper bound.
	//! @param		key			The key of element to be compared.
	//!	@return		The index of elements.
	_dword UpperBoundAscending( const Key& key ) const;
	//!	Return the index of element by upper bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	//!	@return		The index of elements.
	_dword UpperBoundAscending( _int left, _int right, const Key& key ) const;
	//!	Return the index of element by upper bound.
	//! @param		key			The key of element to be compared.
	//!	@return		The index of elements.
	_dword UpperBoundDescending( const Key& key ) const;
	//!	Return the index of element by upper bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	//!	@return		The index of elements.
	_dword UpperBoundDescending( _int left, _int right, const Key& key ) const;
	//!	Return the index of element by lower bound within a range.
	//! @param		key			The key of element to be compared.
	_dword LowerBoundAscending( const Key& key ) const;
	//!	Return the index of element by lower bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	_dword LowerBoundAscending( _int left, _int right, const Key& key ) const;
	//!	Return the index of element by lower bound within a range.
	//! @param		key			The key of element to be compared.
	_dword LowerBoundDescending( const Key& key ) const;
	//!	Return the index of element by lower bound within a range.
	//!	@param		left		The start index of elements.
	//!	@param		right		The end index of elements.
	//! @param		key			The key of element to be compared.
	_dword LowerBoundDescending( _int left, _int right, const Key& key ) const;

	//! Append an element to the end of the array.
	//! @param		element		The new element to be appended into.
	//! @return		The index of element in array.
	_dword Append( const Type& element );
	//! Append element to the end of the array.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		The index of element in array.
	_dword Append( const Type* elements, _dword number );
	//! Append element to the end of the array.
	//! @param		arr			The elements to be appended into.
	//! @return		The index of element in array.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_dword AppendArray( const ArrayType& arr );
	//! Insert an element into the array, the position is specified by an iterator.
	//! @param		element		The new element to be inserted into.
	//! @param		iterator	The iterator specifies a position.
	//! @return		The index of element in array.
	_dword Insert( const Type& element, const Iterator& iterator );
	//! Insert an element into the array, the position is specified by an index.
	//! @param		element		The new element to be inserted into.
	//! @param		index		The index specifies a position.
	//! @return		The index of element in array.
	_dword Insert( const Type& element, _dword index );
	//!	Insert element by key in ascending way.
	//! @param		element		The new element to be inserted into.
	//! @return		The index of element in array.
	_dword InsertAscending( const Type& element );
	//!	Insert element by key in descending way.
	//! @param		element		The new element to be inserted into.
	//! @return		The index of element in array.
	_dword InsertDescending( const Type& element );
	//! Insert element by key in ascending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void InsertAscending( const Type* elements, _dword number );
	//! Insert element by key in descending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void InsertDescending( const Type* elements, _dword number );
	//! Insert element by key in ascending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void InsertArrayAscending( const ArrayType& arr );
	//! Insert element by key in descending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void InsertArrayDescending( const ArrayType& arr );
	//! Append element to the end of the array.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void Merge( const Type* elements, _dword number );
	//! Insert element by key in ascending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void MergeAscending( const Type* elements, _dword number );
	//! Insert element by key in descending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void MergeDescending( const Type* elements, _dword number );
	//! Append element to the end of the array.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void MergeArray( const ArrayType& arr );
	//! Insert element by key in ascending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void MergeArrayAscending( const ArrayType& arr );
	//! Insert element by key in descending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void MergeArrayDescending( const ArrayType& arr );
	//! Remove an element from the array, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//! @return		The next iterator.
	Iterator Remove( Iterator iterator );
	//! Remove an element from array.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool Remove( const Key& key );
	//! Remove an element from the array, the element is specified by an index.
	//! @param		index		The index of element in array.
	//! @return		The next iterator.
	Iterator RemoveByIndex( _dword index );
	//! Remove elements from the array.
	//! @param		index		The start index of element in array.
	//! @param		number		The number of elements.
	//! @return		none.
	_void RemoveByRange( _dword index, _dword number );
	//! Remove an element from array in ascending way.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool RemoveAscending( const Key& key );
	//! Remove an element from array in descending way.
	//! @param		key			The key of element to be removed.
	//! @return		True if the element is removed, false otherwise.
	_ubool RemoveDescending( const Key& key );
	//! Remove elements from the array.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void Remove( const Type* elements, _dword number );
	//! Remove element by key in ascending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void RemoveAscending( const Type* elements, _dword number );
	//! Remove element by key in descending way.
	//! @param		elements	The elements to be appended into.
	//! @param		number		The number of the elements to be appended into.
	//! @return		none.
	_void RemoveDescending( const Type* elements, _dword number );
	//! Remove elements from the array.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void RemoveArray( const ArrayType& arr );
	//! Remove element by key in ascending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void RemoveArrayAscending( const ArrayType& arr );
	//! Remove element by key in descending way.
	//! @param		arr			The elements to be appended into.
	//! @return		none.
	template< typename ArrayType = PtrArray< Type, Key, KeyConverter > >
	_void RemoveArrayDescending( const ArrayType& arr );

	//!	Swap elements.
	//!	@param		index_1		The first index.
	//!	@param		index_2		The second index.
	//!	@return		True if the elements swap successful.
	_ubool Swap( _dword index_1, _dword index_2 );

	//!	Sort all elements in ascending way.
	//! @param		none.
	//! @return		none.
	_void SortAscending( );
	//!	Sort all elements in ascending way by range.
	//! @param		none.
	//! @return		none.
	_void SortAscendingByRange( _dword index, _dword number );
	//!	Sort all elements in descending way.
	//! @param		none.
	//! @return		none.
	_void SortDescending( );
	//!	Sort all elements in descending way by range.
	//! @param		none.
	//! @return		none.
	_void SortDescendingByRange( _dword index, _dword number );
	//!	Sort all elements in binary way
	//! @param		none.
	//! @return		none.
	template< typename GreaterFunc, typename LessFunc > 
	_void BinarySort( );
	//!	Sort all elements in binary way
	//! @param		none.
	//! @return		none.
	template< typename CompareFunc > 
	_void BinarySort( );

	//! Initialize.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Init( _dword number );
	//! Resize the array by create new memory and copy old element into it.
	//! @param		number		The total number of elements.
	//!	@return		none.
	_void Resize( _dword number );

	//! Clear all elements in the array.
	//! @param		freememory	True indicates free the memory used by array.
	//!	@return		none.
	_void Clear( _ubool freememory = _false );

	template< typename ToType , typename ToTypeArray = PtrArray< ToType, Key, PtrType2Key< ToType, Key > >, typename PtrType2ToType = PtrType2Key< Type, ToType > >
	ToTypeArray ConvertArray( ) const;
};

//----------------------------------------------------------------------------
// Array Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key, typename KeyConverter > 
PtrArray< Type, Key, KeyConverter >::PtrArray( )
{
	mAllocedSize	= 0;
	mNumber			= 0;
	mElements		= _null;
}

template< typename Type, typename Key, typename KeyConverter > 
PtrArray< Type, Key, KeyConverter >::PtrArray( const PtrArray< Type, Key, KeyConverter >& array )
{
	mAllocedSize	= array.mAllocedSize;
	mNumber			= array.mNumber;
	mElements		= _null;

	if ( mAllocedSize > 0 )
	{
		mElements = new Type[ mAllocedSize ];

		// Copy elements into new memory, execute operator = of Type class.
		for ( _dword i = 0; i < mNumber; i ++ )
			mElements[i] = array.mElements[i];
	}
}

template< typename Type, typename Key, typename KeyConverter > 
PtrArray< Type, Key, KeyConverter >::~PtrArray( )
{
	Clear( _true );
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::Grow( )
{
	// Increase the allocated size
	mAllocedSize = Math::Max( mAllocedSize + 1, mAllocedSize * 2 );

	// Create elements
	Type* newelements = new Type[ mAllocedSize ];

	// Copy elements into new memory, execute operator = of Type class.
	for ( _dword i = 0; i < mNumber; i ++ )
		newelements[i] = mElements[i];

	EGE_DELETE_ARRAY( mElements );

	mElements = newelements;
}

template< typename Type, typename Key, typename KeyConverter > 
PtrArray< Type, Key, KeyConverter >& PtrArray< Type, Key, KeyConverter >::operator = ( const PtrArray< Type, Key, KeyConverter >& array )
{
	// If we have enough space then skip re-allocate memory
	if ( mAllocedSize >= array.mNumber )
	{
		mNumber	= array.mNumber;

		for ( _dword i = 0; i < array.mNumber; i ++ )
			mElements[i] = array.mElements[i];
	}
	else
	{
		Clear( _true );

		mAllocedSize	= array.mAllocedSize;
		mNumber			= array.mNumber;
		mElements		= _null;

		if ( mAllocedSize > 0 )
		{
			mElements = new Type[ mAllocedSize ];

			// Copy elements one by one, execute operator = of Type class.
			for ( _dword i = 0; i < mNumber; i ++ )
				mElements[i] = array.mElements[i];
		}
	}

	return *this;
}

template< typename Type, typename Key, typename KeyConverter > 
PtrArray< Type, Key, KeyConverter >& PtrArray< Type, Key, KeyConverter >::operator += ( const PtrArray< Type, Key, KeyConverter >& array )
{
	for ( _dword i = 0; i < array.Number( ); i ++ )
		Append( array[i] );

	return *this;
}

template< typename Type, typename Key, typename KeyConverter > 
const Type& PtrArray< Type, Key, KeyConverter >::operator [] ( _dword index ) const
{
	EGE_ASSERT( index < mNumber );

	return mElements[ index ];
}

template< typename Type, typename Key, typename KeyConverter > 
Type& PtrArray< Type, Key, KeyConverter >::operator [] ( _dword index )
{
	EGE_ASSERT( index < mNumber );

	return mElements[ index ];
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::Size( ) const
{
	return mAllocedSize;
}

template< typename Type, typename Key, typename KeyConverter > 
Type* PtrArray< Type, Key, KeyConverter >::GetBuffer( )
{
	return mElements;
}

template< typename Type, typename Key, typename KeyConverter > 
const Type* PtrArray< Type, Key, KeyConverter >::GetBuffer( ) const
{
	return mElements;
}

template< typename Type, typename Key, typename KeyConverter > 
Type* PtrArray< Type, Key, KeyConverter >::Index( _dword index )
{
	if ( index >= mNumber )
		return _null;

	return &( mElements[ index ] );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::GetHeadIterator( ) const
{
	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, 0 );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::GetTailIterator( ) const
{
	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, mNumber - 1 );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::GetIterator( _dword index ) const
{
	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, index );
}

template< typename Type, typename Key, typename KeyConverter > 
const Type& PtrArray< Type, Key, KeyConverter >::GetHeadElement( ) const
{
	EGE_ASSERT( mNumber > 0 );

	return mElements[ 0 ];
}

template< typename Type, typename Key, typename KeyConverter > 
Type& PtrArray< Type, Key, KeyConverter >::GetHeadElement( )
{
	EGE_ASSERT( mNumber > 0 );

	return mElements[ 0 ];
}

template< typename Type, typename Key, typename KeyConverter > 
const Type& PtrArray< Type, Key, KeyConverter >::GetTailElement( ) const
{
	EGE_ASSERT( mNumber > 0 );

	return mElements[ mNumber - 1 ];
}

template< typename Type, typename Key, typename KeyConverter > 
Type& PtrArray< Type, Key, KeyConverter >::GetTailElement( )
{
	EGE_ASSERT( mNumber > 0 );

	return mElements[ mNumber - 1 ];
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::Search( const Key& key ) const
{
	for ( _dword i = 0; i < mNumber; i ++ )
	{
		if ( KeyConverter( )( mElements[i] ) == key )
			return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, i );
	}

	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, -1 );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::SearchAscending( const Key& key ) const
{
	// Search elements in ascending way
	_int index = Algorithm::BinarySearch< Type, Key, KeyConverter, Compare< Key > >( mElements, (_int)mNumber, key );
	if ( index == -1 )
		return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, -1 );

	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, index );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::SearchDescending( const Key& key ) const
{
	// Search elements in descending way
	_int index = Algorithm::BinarySearch< Type, Key, KeyConverter, NotCompare< Key > >( mElements, mNumber, key );
	if ( index == -1 )
		return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, -1 );

	return Iterator( (PtrArray< Type, Key, KeyConverter >*) this, index );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::UpperBoundAscending( const Key& key ) const
{
	return UpperBoundAscending( 0, mNumber - 1, key );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::UpperBoundAscending( _int left, _int right, const Key& key ) const
{
	if ( mNumber == 0 )
		return -1;

	if ( KeyConverter( )( mElements[left] ) >= key )
		return left;

	if ( KeyConverter( )( mElements[right] ) <= key )
		return right;

	_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, Compare< Key >, Compare< Key > >( mElements, left, right, key );

	return index;
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::UpperBoundDescending( const Key& key ) const
{
	return UpperBoundDescending( 0, mNumber - 1, key );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::UpperBoundDescending( _int left, _int right, const Key& key ) const
{
	if ( mNumber == 0 )
		return -1;

	if ( KeyConverter( )( mElements[right] ) >= key )
		return right;

	if ( KeyConverter( )( mElements[left] ) <= key )
		return left;

	_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, NotCompare< Key >, Compare< Key > >( mElements, left, right, key );

	return index;
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::LowerBoundAscending( const Key& key ) const
{
	return LowerBoundAscending( 0, (_int)mNumber - 1, key );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::LowerBoundAscending( _int left, _int right, const Key& key ) const
{
	if ( mNumber == 0 )
		return -1;

	if ( KeyConverter( )( mElements[right] ) <= key )
		return right;

	if ( KeyConverter( )( mElements[left] ) >= key )
		return left;

	_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, Compare< Key >, NotCompare< Key > >( mElements, left, right, key );

	return index;
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::LowerBoundDescending( const Key& key ) const
{
	return LowerBoundDescending( 0, mNumber - 1, key );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::LowerBoundDescending( _int left, _int right, const Key& key ) const
{
	if ( mNumber == 0 )
		return -1;

	if ( KeyConverter( )( mElements[left] ) <= key )
		return left;

	if ( KeyConverter( )( mElements[right] ) >= key )
		return right;

	_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, NotCompare< Key >, NotCompare< Key > >( mElements, left, right, key );

	return index;
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::Append( const Type& element )
{
	// Resize the array when necessary.
	if ( mNumber == mAllocedSize )
		Grow( );

	// Assign the element
	mElements[ mNumber ] = element;

	// Increase the element number
	return CountOf<>::Increase( );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::Append( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		Append( elements[i] );

	return mNumber - 1;
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_dword PtrArray< Type, Key, KeyConverter >::AppendArray( const ArrayType& arr )
{
	return Append( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::Insert( const Type& element, const Iterator& iterator )
{
	return Insert( element, iterator.mIndex );
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::Insert( const Type& element, _dword index )
{
	EGE_ASSERT( index <= mNumber );

	// Resize the array when necessary.
	if ( mNumber == mAllocedSize )
		Grow( );

	// Move elements after the index backward, make a place for the new element.
	for ( _dword i = 0; i < mNumber - index; i ++ )
		mElements[ mNumber - i ] = mElements[ mNumber - i - 1 ];

	// Assign the element.
	mElements[ index ] = element;

	// Increase the element number.
	CountOf<>::Increase( );

	return index;
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::InsertAscending( const Type& element )
{
	if ( mNumber == 0 )
	{
		Append( element );

		return 0;
	}
	else
	{
		_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, Compare< Key >, Compare< Key > >( mElements, 0, (_int)mNumber - 1, KeyConverter( )( element ) );
		if ( index == -1 )
			index = mNumber;

		Insert( element, index );

		return index;
	}
}

template< typename Type, typename Key, typename KeyConverter > 
_dword PtrArray< Type, Key, KeyConverter >::InsertDescending( const Type& element )
{
	if ( mNumber == 0 )
	{
		Append( element );

		return 0;
	}
	else
	{
		_dword index = Algorithm::BinaryBound< Type, Key, KeyConverter, NotCompare< Key >, NotCompare< Key > >( mElements, 0, (_int)mNumber - 1, KeyConverter( )( element ) );
		if ( index == -1 )
			index = mNumber;

		Insert( element, index );

		return index;
	}
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::InsertAscending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		InsertAscending( elements[i] );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::InsertDescending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		InsertDescending( elements[i] );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::InsertArrayAscending( const ArrayType& arr )
{
	InsertAscending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::InsertArrayDescending( const ArrayType& arr )
{
	InsertDescending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::Merge( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
	{
		if ( Search( KeyConverter( )( elements[i] ) ).IsValid( ) )
			continue;

		Append( elements[i] );
	}
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::MergeAscending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
	{
		if ( SearchAscending( KeyConverter( )( elements[i] ) ).IsValid( ) )
			continue;

		InsertAscending( elements[i] );
	}
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::MergeDescending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
	{
		if ( SearchDescending( KeyConverter( )( elements[i] ) ).IsValid( ) )
			continue;

		InsertDescending( elements[i] );
	}
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::MergeArray( const ArrayType& arr )
{
	Merge( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::MergeArrayAscending( const ArrayType& arr )
{
	MergeAscending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::MergeArrayDescending( const ArrayType& arr )
{
	MergeDescending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::Remove( Iterator iterator )
{
	return RemoveByIndex( iterator.mIndex );
}

template< typename Type, typename Key, typename KeyConverter > 
typename PtrArray< Type, Key, KeyConverter >::Iterator PtrArray< Type, Key, KeyConverter >::RemoveByIndex( _dword index )
{
	if ( index >= mNumber )
		return Iterator( );

	// It's the last element
	if ( index == mNumber - 1 )
	{
		mElements[index] = Type( );
	}
	// Move elements after the index forward, replace the deleted one.
	else
	{
		for ( _dword i = index; i < mNumber - 1; i ++ )
			mElements[i] = mElements[ i + 1 ];
	}

	// Decrease the element number.
	CountOf<>::Decrease( );

	// Feedback the next iterator
	return index < mNumber ? Iterator( this, index ) : Iterator( );
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::RemoveByRange( _dword index, _dword number )
{
	EGE_ASSERT( index < mNumber );
	EGE_ASSERT( index + number <= mNumber );

	for ( _dword i = index; i < index + number; i ++ )
	{
		if ( i + number >= mNumber )
			break;

		mElements[i] = mElements[i + number];
	}

	mNumber -= number;
}

template< typename Type, typename Key, typename KeyConverter > 
_ubool PtrArray< Type, Key, KeyConverter >::Remove( const Key& key )
{
	Iterator it = Search( key );
	if ( it.IsValid( ) == _false )
		return _false;

	RemoveByIndex( it.mIndex );

	return _true;
}

template< typename Type, typename Key, typename KeyConverter > 
_ubool PtrArray< Type, Key, KeyConverter >::RemoveAscending( const Key& key )
{
	Iterator it = SearchAscending( key );
	if ( it.IsValid( ) == _false )
		return _false;

	RemoveByIndex( it.mIndex );

	return _true;
}

template< typename Type, typename Key, typename KeyConverter > 
_ubool PtrArray< Type, Key, KeyConverter >::RemoveDescending( const Key& key )
{
	Iterator it = SearchDescending( key );
	if ( it.IsValid( ) == _false )
		return _false;

	RemoveByIndex( it.mIndex );

	return _true;
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::Remove( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		Remove( KeyConverter( )( elements[i] ) );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::RemoveAscending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		RemoveAscending( KeyConverter( )( elements[i] ) );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::RemoveDescending( const Type* elements, _dword number )
{
	for ( _dword i = 0; i < number; ++ i )
		RemoveDescending( KeyConverter( )( elements[i] ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::RemoveArray( const ArrayType& arr )
{
	Remove( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::RemoveArrayAscending( const ArrayType& arr )
{
	RemoveAscending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ArrayType >
_void PtrArray< Type, Key, KeyConverter >::RemoveArrayDescending( const ArrayType& arr )
{
	RemoveDescending( arr.GetBuffer( ), arr.Number( ) );
}

template< typename Type, typename Key, typename KeyConverter > 
_ubool PtrArray< Type, Key, KeyConverter >::Swap( _dword index_1, _dword index_2 )
{
	if ( index_1 >= mNumber )
		return _false;

	if ( index_2 >= mNumber )
		return _false;

	Math::Swap( mElements[index_1], mElements[index_2] );

	return _true;
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::SortAscending( )
{
	SortAscendingByRange( 0, mNumber );
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::SortAscendingByRange( _dword index, _dword number )
{
	if ( number == 0 )
		return;

	Algorithm::QuickSort< Type, Key, KeyConverter, Greater< Key >, Less< Key > >( mElements, index, index + number - 1 );
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::SortDescending( )
{
	SortDescendingByRange( 0, mNumber );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::SortDescendingByRange( _dword index, _dword number )
{
	if ( number == 0 )
		return;

	Algorithm::QuickSort< Type, Key, KeyConverter, Less< Key >, Greater< Key > >( mElements, index, index + number - 1 );
}

template< typename Type, typename Key, typename KeyConverter > 
template< typename GreaterFunc, typename LessFunc > 
_void PtrArray< Type, Key, KeyConverter >::BinarySort( )
{
	if ( mNumber == 0 )
		return;

	Algorithm::QuickSort< Type, Key, KeyConverter, GreaterFunc, LessFunc >( mElements, 0, mNumber - 1 );
}

template< typename Type, typename Key, typename KeyConverter > 
template< typename CompareFunc > 
_void PtrArray< Type, Key, KeyConverter >::BinarySort( )
{
	if ( mNumber == 0 )
		return;

	Algorithm::QuickSort< Type, Key, KeyConverter, CompareFunc >( mElements, 0, mNumber - 1 );
}

template< typename Type, typename Key, typename KeyConverter >
_void PtrArray< Type, Key, KeyConverter >::Init( _dword number )
{
	mAllocedSize	= number;
	mNumber			= number;
	
	EGE_DELETE_ARRAY( mElements );

	if ( mAllocedSize > 0 )
		mElements = new Type[ mAllocedSize ];
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::Resize( _dword number )
{
	// Clear the elements buffer
	if ( number == 0 )
	{
		Clear( _true );
	}
	// Resize the elements buffer
	else if ( number != mNumber )
	{
		// Create elements
		Type* newelements = new Type[ number ];

		// Copy elements into new memory, we must keep the old buffer data
		_dword min_number = MIN( number, mNumber );
		for ( _dword i = 0; i < min_number; i ++ )
			newelements[i] = mElements[i];

		EGE_DELETE_ARRAY( mElements );
		mElements		= newelements;
		mNumber			= min_number; // Only the buffer has been allocated ...
		mAllocedSize	= number;
	}
}

template< typename Type, typename Key, typename KeyConverter > 
_void PtrArray< Type, Key, KeyConverter >::Clear( _ubool freememory )
{
	if ( freememory == _true )
	{
		EGE_DELETE_ARRAY( mElements );

		mAllocedSize	= 0;
		mElements		= _null;
	}

	CountOf<>::Clear( );
}

template< typename Type, typename Key, typename KeyConverter >
template< typename ToType, typename ToTypeArray, typename PtrType2ToType >
ToTypeArray PtrArray< Type, Key, KeyConverter >::ConvertArray( ) const
{
	ToTypeArray to_array;
	to_array.Resize( Number( ) );

	for ( _dword i = 0; i < Number( ); ++ i )
		to_array.Append( PtrType2ToType( )( ( *this )[i] ) );

	return to_array;
}

}
