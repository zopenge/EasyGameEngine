//! @file     ElementArray.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Array
//----------------------------------------------------------------------------

//! This class is template container class, represents a array.
template< typename Type > 
class ElementArray
{
private:
	_dword			mLastIndex;
	Type			mDefaultValue;
	Array< Type* >	mElements;

private:
	_void Init( );

	_void RemoveAll( );

public:
	//! Constructor, create an empty array.
	//! @param		none.
	ElementArray( );
	//! Constructor, create an empty array.
	//! @param		none.
	ElementArray( const Type& default_value );
	//! Destructor, delete the array, and release the elements memory.
	//! @param		none
	~ElementArray( );

public:
	//!	Clear.
	_void Clear( );

	//!	Reset cache elements.
	_void Reset( );

	//!	Add cache element.
	Type* Append( );
	Type* Append( const Type& value );

	//!	Get last cache value.
	const Type* GetLastValue( ) const;
};

//----------------------------------------------------------------------------
// ElementArray Implementation
//----------------------------------------------------------------------------

template< typename Type >
ElementArray< Type >::ElementArray( )
{
	mDefaultValue = Type( );

	Init( );
}

template<>
inline ElementArray< _ubool >::ElementArray( )
{
	mDefaultValue = _false;

	Init( );
}

template<>
inline ElementArray< _int >::ElementArray( )
{
	mDefaultValue = 0;

	Init( );
}

template<>
inline ElementArray< _dword >::ElementArray( )
{
	mDefaultValue = 0;

	Init( );
}

template< typename Type >
ElementArray< Type >::ElementArray( const Type& default_value )
{
	mLastIndex		= 0;
	mDefaultValue	= default_value;

	mElements.Append( new Type( default_value ) );
}

template< typename Type >
ElementArray< Type >::~ElementArray( )
{
	RemoveAll( );
}

template< typename Type >
_void ElementArray< Type >::Init( )
{
	mLastIndex = 0;

	mElements.Append( new Type( mDefaultValue ) );
}

template< typename Type >
_void ElementArray< Type >::RemoveAll( )
{
	mLastIndex = 0;

	for ( _dword i = 0; i < mElements.Number( ); i ++ )
	{
		EGE_DELETE( mElements[i] );
	}
	mElements.Clear( _true );
}

template< typename Type >
_void ElementArray< Type >::Clear( )
{
	RemoveAll( );

	Init( );
}

template< typename Type >
_void ElementArray< Type >::Reset( )
{
	if ( mLastIndex == 0 )
		return;

	Type* element = mElements[0];
	mElements[0] = mElements[mLastIndex];
	mElements[mLastIndex] = element;

	mLastIndex = 0;
}

template< typename Type >
Type* ElementArray< Type >::Append( )
{
	mLastIndex ++;
	if ( mLastIndex >= mElements.Number( ) )
		mElements.Append( new Type( ) );

	return mElements[mLastIndex];
}

template< typename Type >
Type* ElementArray< Type >::Append( const Type& value )
{
	mLastIndex ++;
	if ( mLastIndex >= mElements.Number( ) )
		mElements.Append( new Type( value ) );
	else
		*mElements[mLastIndex] = value;

	return mElements[mLastIndex];
}

template< typename Type >
const Type* ElementArray< Type >::GetLastValue( ) const
{
	return mElements[mLastIndex];
}

}
