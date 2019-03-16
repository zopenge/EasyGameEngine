//! @file     CyclicObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CyclicObject
//----------------------------------------------------------------------------

//! This class is template container class, represents a CyclicObject.
template< typename Type, _dword _MAX_OBJECT_NUMBER >
class CyclicObject
{
private:
	//!	The current index of objects
	_dword	mCurIndex;
	//!	The next index of objects
	_dword	mNextIndex;
	//!	The objects
	Type	mObjects[ _MAX_OBJECT_NUMBER ];

public:
	//! Constructor.
	CyclicObject( );
	//! Destructor.
	//! @param		none
	~CyclicObject( );

public:
	//! Get a const element reference by index.
	//! @param		index		The index of the element.
	//! @return		The const element reference.
	const Type& operator [] ( _dword index ) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element.
	//! @return		The mutable element reference.
	Type& operator [] ( _dword index );

	//! Get the current size of elements buffer.
	//! @param		none
	//! @return		The current size of elements buffer.
	_dword Size( ) const;
	//!	Get the CyclicObject buffer.
	//!	@param		none.
	//!	@return		The element buffer pointer.
	const Type* GetBuffer( ) const;

	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index.
	//! @param		index		The index of the element.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	Type* Index( _dword index );
	//! Get an element pointer by index.
	//! @remarks	This is a safe way to get an element by index.
	//! @param		index		The index of the element.
	//! @return		The pointer to a element if the index is valid, null otherwise.
	const Type* Index( _dword index ) const;

	//!	Get the current index.
	//!	@param		none.
	//!	@return		The current index.
	_dword GetCurIndex( ) const;

	//!	Get the current object.
	//!	@param		none.
	//!	@return		The current object.
	Type& GetCurObject( );
	//!	Get the current object.
	//!	@param		none.
	//!	@return		The current object.
	const Type& GetCurObject( ) const;

	//!	Get the next object.
	//!	@param		none.
	//!	@return		The next object.
	Type& GetNextObject( );
	//!	Get the next object.
	//!	@param		none.
	//!	@return		The next object.
	const Type& GetNextObject( ) const;

	//!	Roll circularly.
	//!	@param		none.
	//!	@return		none.
	_void Roll( );
};

//----------------------------------------------------------------------------
// CyclicObject Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_OBJECT_NUMBER >
CyclicObject< Type, _MAX_OBJECT_NUMBER >::CyclicObject( )
{
	EGE_STATIC_ASSERT( _MAX_OBJECT_NUMBER >= 2, "The number of sub-objects in cyclic object must large than 2, so we can roll it" );

	mCurIndex	= 0;
	mNextIndex	= 1;
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
CyclicObject< Type, _MAX_OBJECT_NUMBER >::~CyclicObject( )
{
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
const Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::operator [] ( _dword index ) const
{
	EGE_ASSERT( index < _MAX_OBJECT_NUMBER );

	return mObjects[ index ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::operator [] ( _dword index )
{
	EGE_ASSERT( index < _MAX_OBJECT_NUMBER );

	return mObjects[ index ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
_dword CyclicObject< Type, _MAX_OBJECT_NUMBER >::Size( ) const
{
	return _MAX_OBJECT_NUMBER;
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
const Type* CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetBuffer( ) const
{
	return mObjects;
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
Type* CyclicObject< Type, _MAX_OBJECT_NUMBER >::Index( _dword index )
{
	if ( index >= _MAX_OBJECT_NUMBER )
		return _null;

	return &( mObjects[ index ] );
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
const Type* CyclicObject< Type, _MAX_OBJECT_NUMBER >::Index( _dword index ) const
{
	if ( index >= _MAX_OBJECT_NUMBER )
		return _null;

	return &( mObjects[ index ] );
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
_dword CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetCurIndex( ) const
{
	return mCurIndex;
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetCurObject( )
{
	return mObjects[ mCurIndex ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
const Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetCurObject( ) const
{
	return mObjects[ mCurIndex ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetNextObject( )
{
	return mObjects[ mNextIndex ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
const Type& CyclicObject< Type, _MAX_OBJECT_NUMBER >::GetNextObject( ) const
{
	return mObjects[ mNextIndex ];
}

template< typename Type, _dword _MAX_OBJECT_NUMBER >
_void CyclicObject< Type, _MAX_OBJECT_NUMBER >::Roll( )
{
	mCurIndex	= ( mCurIndex  + 1 ) % _MAX_OBJECT_NUMBER;
	mNextIndex	= ( mNextIndex + 1 ) % _MAX_OBJECT_NUMBER;
}

}
