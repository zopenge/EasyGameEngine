//! @file     InstanceAllocator.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// InstanceAllocator
//----------------------------------------------------------------------------

template< typename Type > 
class FixedAllocator
{
private:
	//!	The buffer in the heap
	Type*	mBuffer;
	//!	The current buffer index ( bounds in [0, mBufferNumber] )
	_dword	mBufferIndex;
	//!	The buffer number
	_dword	mBufferNumber;

public:
	FixedAllocator( _dword number );
	~FixedAllocator( );

public:
	//!	Clear buffer.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Get buffer total free element number.
	//!	@param		none.
	//!	@return		The total free element number.
	_dword GetTotalFreeNumber( ) const;
	//!	Get usage amount.
	//!	@param		none.
	//!	@return		The usage amount ( in percent ).
	_float GetUsageAmount( ) const;

	//!	Allocate.
	//!	@param		number		The number of elements what you want to allocate.
	//! @return		The allocated memory pointer.
	Type* Allocate( _dword number );
	//!	Allocate.
	//!	@param		pointer		The element's address what you want to copy from.
	//!	@param		number		The number of elements what you want to allocate.
	//! @return		The allocated memory pointer.
	Type* Allocate( const Type* pointer, _dword number );
};

//----------------------------------------------------------------------------
// InstanceAllocator Implementation
//----------------------------------------------------------------------------

template< typename Type >
FixedAllocator< Type >::FixedAllocator( _dword number )
{
	mBuffer			= new Type[ number ];
	mBufferIndex	= 0;
	mBufferNumber	= number;
}

template< typename Type >
FixedAllocator< Type >::~FixedAllocator( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

template< typename Type >
_void FixedAllocator< Type >::Clear( )
{
	mBufferIndex = 0;
}

template< typename Type >
_dword FixedAllocator< Type >::GetTotalFreeNumber( ) const
{
	return mBufferNumber - mBufferIndex;
}

template< typename Type >
_float FixedAllocator< Type >::GetUsageAmount( ) const
{
	return (_float) mBufferIndex / (_float) mBufferNumber;
}

template< typename Type >
Type* FixedAllocator< Type >::Allocate( _dword number )
{
	if ( number == 0 || mBufferIndex + number > mBufferNumber )
		return _null;

	// Get buffer address
	Type* buffer = mBuffer + mBufferIndex;

	// Update buffer index
	mBufferIndex += number;

	return buffer;
}

template< typename Type >
Type* FixedAllocator< Type >::Allocate( const Type* pointer, _dword number )
{
	// Allocate buffer
	Type* buffer = Allocate( number );
	if ( buffer == _null )
		return _null;

	// Copy elements
	if ( pointer != _null )
	{
		for ( _dword i = 0; i < number; i ++ )
			mBuffer[i] = pointer[i];
	}

	return buffer;
}

}