//! @file     RawArray.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RawArray
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_SIZE > 
class RawArray
{
protected:
	//!	The elements of array
	Type	mElements[ _MAX_SIZE ];

public:
	//! Default constructor.
	//! @param		none
	RawArray( );
	//! Constructor, set all elements to same value.
	//! @param		value		The value to set to all elements.
	RawArray( const Type& value );
	//! Copy-Constructor, create an array by copy from another one.
	//! @param		array		The other array.
	RawArray( const RawArray< Type, _MAX_SIZE >& array );
	//! Destructor.
	//! @param		none
	~RawArray( );

public:
	//! Copy elements from another array.
	//! @param		array		The other array.
	//! @return		The reference of current array.
	RawArray< Type, _MAX_SIZE >& operator = ( const RawArray< Type, _MAX_SIZE >& array );

	//! Get a const element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The const element reference.
	const Type& operator [] ( _dword index ) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The mutable element reference.
	Type& operator [] ( _dword index );

	//! Get the number of array.
	//! @param		none
	//! @return		The number of array.
	_dword Number( ) const;
	//!	Get the array buffer.
	//!	@param		none.
	//!	@return		The element buffer pointer.
	const Type* GetBuffer( ) const;

	//! Copy array.
	//! @param		buffer		The element buffer.
	//! @param		number		The element number.
	//!	@return		none.
	_void Copy( const Type* buffer, _dword number );

	//! Clear array, set all elements to same value.
	//! @param		value		The value to set to all elements.
	//!	@return		none.
	_void Set( const Type& value );
};

//----------------------------------------------------------------------------
// RawArray Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_SIZE >
RawArray< Type, _MAX_SIZE >::RawArray( )
{
}

template< typename Type, _dword _MAX_SIZE >
RawArray< Type, _MAX_SIZE >::RawArray( const Type& value )
{
	for ( _dword i = 0; i < _MAX_SIZE; i ++ )
		mElements[i] = value;
}

template< typename Type, _dword _MAX_SIZE >
RawArray< Type, _MAX_SIZE >::RawArray( const RawArray< Type, _MAX_SIZE >& array )
{
	for ( _dword i = 0; i < _MAX_SIZE; i ++ )
		mElements[i] = array.mElements[i];
}

template< typename Type, _dword _MAX_SIZE >
RawArray< Type, _MAX_SIZE >::~RawArray( )
{

}

template< typename Type, _dword _MAX_SIZE >
RawArray< Type, _MAX_SIZE >& RawArray< Type, _MAX_SIZE >::operator = ( const RawArray< Type, _MAX_SIZE >& array )
{
	for ( _dword i = 0; i < _MAX_SIZE; i ++ )
		mElements[i] = array.mElements[i];

	return *this;
}

template< typename Type, _dword _MAX_SIZE >
Type& RawArray< Type, _MAX_SIZE >::operator [] ( _dword index )
{
	EGE_ASSERT( index < _MAX_SIZE );

	return mElements[ index ];
}

template< typename Type, _dword _MAX_SIZE >
const Type& RawArray< Type, _MAX_SIZE >::operator [] ( _dword index ) const
{
	EGE_ASSERT( index < _MAX_SIZE );

	return mElements[ index ];
}

template< typename Type, _dword _MAX_SIZE >
_dword RawArray< Type, _MAX_SIZE >::Number( ) const
{
	return _MAX_SIZE;
}

template< typename Type, _dword _MAX_SIZE >
const Type* RawArray< Type, _MAX_SIZE >::GetBuffer( ) const
{
	return mElements;
}

template< typename Type, _dword _MAX_SIZE >
_void RawArray< Type, _MAX_SIZE >::Copy( const Type* buffer, _dword number )
{
	EGE_ASSERT( number < _MAX_SIZE );

	for ( _dword i = 0; i < number; i ++ )
		mElements[i] = buffer[i];
}

template< typename Type, _dword _MAX_SIZE >
_void RawArray< Type, _MAX_SIZE >::Set( const Type& value )
{
	for ( _dword i = 0; i < _MAX_SIZE; i ++ )
		mElements[i] = value;
}

}