//! @file     CircularBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CircularBuffer
//----------------------------------------------------------------------------

//! This class is template circular container class, represents a CircularBuffer.
template< typename Type, typename Key = Type > 
class CircularBuffer
{
private:
	//!	The current index of buffer
	_dword	mCurIndex;
	//!	The max buffer number
	_dword	mMaxNumber;
	//!	The buffer data
	Type*	mBufferData;

public:
	//! Constructor, create an empty CircularBuffer.
	//! @param		none.
	CircularBuffer( );
	//! Constructor, create an empty CircularBuffer.
	//! @param		number		The initial allocated number of the elements.
	CircularBuffer( _dword number );
	//! Copy-Constructor, create an CircularBuffer by copy from another one.
	//! @param		CircularBuffer		The other CircularBuffer.
	CircularBuffer( const CircularBuffer< Type, Key >& circular_buffer );
	//! Destructor, delete the CircularBuffer, and release the elements memory.
	//! @param		none
	~CircularBuffer( );

public:
	//! Copy elements from another CircularBuffer, and recreates memory to hold it.
	//! @param		CircularBuffer		The other CircularBuffer.
	//! @return		The reference of current CircularBuffer.
	CircularBuffer< Type, Key >& operator = ( const CircularBuffer< Type, Key >& circular_buffer );

	//! Get current element.
	//! @param		none.
	//! @return		The element reference.
	Type& CurElement( );
	//! Get current element.
	//! @param		none.
	//! @return		The element reference.
	const Type& CurElement( ) const;

	//! Get the max number of buffer.
	//! @param		none.
	//! @return		The max number of buffer.
	_dword MaxNumber( ) const;

	//! Get buffer data.
	//! @param		none.
	//! @return		The buffer data.
	_byte* GetBuffer( );
	//! Get buffer data.
	//! @param		none.
	//! @return		The buffer data.
	const _byte* GetBuffer( ) const;

	//! Allocate.
	//! @param		none.
	//! @return		The element reference.
	Type& Alloc( );
	//! Allocate.
	//! @param		number		The number of elements.
	//! @return		The element pointer.
	Type* Alloc( _dword number );

	//! Create.
	//! @param		number		The initial allocated number of the elements.
	//! @return		none.
	_void Create( _dword number );
};

//----------------------------------------------------------------------------
// CircularBuffer Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key >
CircularBuffer< Type, Key >::CircularBuffer( )
{
	mCurIndex	= 0;
	mMaxNumber	= 0;
	mBufferData	= _null;
}

template< typename Type, typename Key >
CircularBuffer< Type, Key >::CircularBuffer( _dword number )
{
	EGE_ASSERT( number != 0 );

	mCurIndex	= 0;
	mMaxNumber	= number;
	mBufferData	= new Type[ number ];
}

template< typename Type, typename Key >
CircularBuffer< Type, Key >::CircularBuffer( const CircularBuffer< Type, Key >& circular_buffer )
{
	EGE_ASSERT( circular_buffer.mMaxNumber != 0 );

	mCurIndex	= circular_buffer.mCurIndex;
	mMaxNumber	= circular_buffer.mMaxNumber;
	mBufferData	= new Type[ circular_buffer.mMaxNumber ];

	// Copy elements into new memory, execute operator = of Type class.
	for ( _dword i = 0; i < mMaxNumber; i ++ )
		mBufferData[i] = circular_buffer.mBufferData[i];
}

template< typename Type, typename Key >
CircularBuffer< Type, Key >::~CircularBuffer( )
{
	EGE_DELETE_ARRAY( mBufferData );
}

template< typename Type, typename Key >
CircularBuffer< Type, Key >& CircularBuffer< Type, Key >::operator = ( const CircularBuffer< Type, Key >& circular_buffer )
{
	EGE_DELETE_ARRAY( mBufferData );

	mCurIndex	= circular_buffer.mCurIndex;
	mMaxNumber	= circular_buffer.mMaxNumber;
	mBufferData	= new Type[ circular_buffer.mMaxNumber ];

	// Copy elements into new memory, execute operator = of Type class.
	for ( _dword i = 0; i < mMaxNumber; i ++ )
		mBufferData[i] = circular_buffer.mBufferData[i];

	return *this;
}

template< typename Type, typename Key >
Type& CircularBuffer< Type, Key >::CurElement( )
{
	return mBufferData[ mCurIndex ];
}

template< typename Type, typename Key >
const Type& CircularBuffer< Type, Key >::CurElement( ) const
{
	return mBufferData[ mCurIndex ];
}

template< typename Type, typename Key >
_dword CircularBuffer< Type, Key >::MaxNumber( ) const
{
	return mMaxNumber;
}

template< typename Type, typename Key >
_byte* CircularBuffer< Type, Key >::GetBuffer( )
{
	return mBufferData;
}

template< typename Type, typename Key >
const _byte* CircularBuffer< Type, Key >::GetBuffer( ) const
{
	return mBufferData;
}

template< typename Type, typename Key >
Type& CircularBuffer< Type, Key >::Alloc( )
{
	// Allocate the element
	Type& element = mBufferData[ mCurIndex ];

	// Update the current buffer index
	mCurIndex ++;
	mCurIndex %= mMaxNumber;

	return element;
}

template< typename Type, typename Key >
Type* CircularBuffer< Type, Key >::Alloc( _dword number )
{
	EGE_ASSERT( number != 0 );

	if ( number > mMaxNumber )
		return _null;

	// if the buffer is full then re-roll it, the use need to make sure that has enough space
	_dword remained_number = mMaxNumber - mCurIndex;
	if ( remained_number < number )
		mCurIndex = 0;

	// Allocate the elements
	Type* elements = &mBufferData[ mCurIndex ];

	// Update the current buffer index
	mCurIndex += number;

	return elements;
}

template< typename Type, typename Key >
_void CircularBuffer< Type, Key >::Create( _dword number )
{
	EGE_ASSERT( number != 0 );

	if ( mMaxNumber == number )
		return;
		
	EGE_DELETE_ARRAY( mBufferData );

	mCurIndex	= 0;
	mMaxNumber	= number;
	mBufferData	= new Type[ number ];
}

}
