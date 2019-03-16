//! @file     SimplePool.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SimplePool
//----------------------------------------------------------------------------

//! This class is template container class, represents a simple pool.
template< typename Type > 
class SimplePool
{
private:
	//!	The current index [0, _MAX_NUMBER)
	_dword	mCurIndex;
	//!	The max number
	_dword	mMaxNumber;
	//!	The elements buffer
	Type*	mElements;

public:
	//! Constructor, create an empty pool.
	//! @param		number		The maximal size of the pool in number of element.
	SimplePool( );
	//! Destructor, delete the pool, and release the memory used by nodes.
	//! @param		none
	~SimplePool( );

public:
	//! Create.
	//! @param		number		The maximal size of the pool in number of element.
	//! @return		True indicates successful, otherwise indicates failed.
	_ubool Create( _dword number );

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
	const Type* GetElementsBuffer( ) const;

	//! Create a node to store element in the pool.
	//! @param		none.
	//! @return		The address of element, or null indicates there is no more node to store it.
	Type* CreateElement( );
	//! Create a node to store element in the pool.
	//! @param		number		The number of elements.
	//! @return		The address of element, or null indicates there is no more node to store it.
	Type* CreateElements( _dword number );

	//! Clear pool.
	//! @param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// SimplePool Implementation
//----------------------------------------------------------------------------

template< typename Type > 
SimplePool< Type >::SimplePool( )
{
	mCurIndex	= 0;
	mMaxNumber	= 0;
	mElements	= _null;
}

template< typename Type > 
SimplePool< Type >::~SimplePool( )
{
	EGE_DELETE_ARRAY( mElements );
}

template< typename Type >
_ubool SimplePool< Type >::Create( _dword number )
{
	EGE_DELETE_ARRAY( mElements );

	mCurIndex	= 0;
	mMaxNumber	= number;
	mElements	= new Type[ number ];

	return _true;
}

template< typename Type > 
_dword SimplePool< Type >::Number( ) const
{
	return mCurIndex;
}

template< typename Type > 
_dword SimplePool< Type >::GetMaxNumber( ) const
{
	return mMaxNumber;
}

template< typename Type > 
const Type* SimplePool< Type >::GetElementsBuffer( ) const
{
	return mElements;
}

template< typename Type > 
Type* SimplePool< Type >::CreateElement( )
{
	return CreateElements( 1 );
}

template< typename Type >
Type* SimplePool< Type >::CreateElements( _dword number )
{
	if ( mCurIndex + number >= mMaxNumber )
		return _null;

	Type* element = &mElements[mCurIndex];

	mCurIndex += number;

	return element;
}

template< typename Type > 
_void SimplePool< Type >::Clear( )
{
	mCurIndex = 0;
}

}