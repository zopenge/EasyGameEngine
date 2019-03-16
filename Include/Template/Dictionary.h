//! @file     Dictionary.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Dictionary
//----------------------------------------------------------------------------

template< typename Type, typename Key, _dword _TABLE = 1, _dword _DIVISOR = 3907 > 
class Dictionary
{
private:
	//! The lookup table
	struct LookupTable : public Map< Type, Key >
	{
		_dword	mMaxTableLength;

		LookupTable( )
			: mMaxTableLength( 0 ) { }
	};

	//! The lookup table
	LookupTable	mLookupTable[ _TABLE ];

public:
	Dictionary( );
	~Dictionary( );

public:
	//!	Get the number of tables.
	//!	@param		none.
	//!	@return		The number of tables.
	_dword GetTableNumber( ) const;
	//!	Get the max length of table.
	//!	@param		tableid		The table ID.
	//!	@return		The .max length of table.
	_dword GetMaxTableLength( _dword tableid ) const;
	//!	Get the average length of table.
	//!	@param		tableid		The table ID.
	//!	@return		The average length of table.
	_dword GetAvgTableLength( _dword tableid ) const;

	//!	Insert element into lookup table.
	//!	@param		it			The element iterator.
	//!	@param		key			The key of element.
	//!	@param		tableid		The table ID.
	//!	@return		none.
	_void Insert( const Type& element, const Key& key, _dword tableid );
	//!	Remove element from lookup table.
	//!	@param		key			The key of element.
	//!	@param		tableid		The table ID.
	//!	@return		none.
	_void Remove( const Key& key, _dword tableid );
	//!	Search element.
	//!	@param		key			The key of element.
	//!	@param		tableid		The table ID.
	//!	@return		The element pointer, null indicates it's not existing.
	Type* Search( const Key& key, _dword tableid ) const;

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// Dictionary Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
Dictionary< Type, Key, _TABLE, _DIVISOR >::Dictionary( )
{
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
Dictionary< Type, Key, _TABLE, _DIVISOR >::~Dictionary( )
{
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_dword Dictionary< Type, Key, _TABLE, _DIVISOR >::GetTableNumber( ) const
{
	return _TABLE;
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_dword Dictionary< Type, Key, _TABLE, _DIVISOR >::GetMaxTableLength( _dword tableid ) const
{
	EGE_ASSERT( tableid < _TABLE );

	return mLookupTable[ tableid ].mMaxTableLength;
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_dword Dictionary< Type, Key, _TABLE, _DIVISOR >::GetAvgTableLength( _dword tableid ) const
{
	EGE_ASSERT( tableid < _TABLE );

	return mLookupTable[ tableid ].Number( ) / _DIVISOR;
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
Type* Dictionary< Type, Key, _TABLE, _DIVISOR >::Search( const Key& key, _dword tableid ) const
{
	EGE_ASSERT( tableid < _TABLE );

	return mLookupTable[ tableid ].Search( key );
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_void Dictionary< Type, Key, _TABLE, _DIVISOR >::Insert( const Type& element, const Key& key, _dword tableid )
{
	EGE_ASSERT( tableid < _TABLE );

	LookupTable& table = mLookupTable[ tableid ];

	table.Insert( element, key );

	// Lookup table statistic.
	if ( table.mMaxTableLength < table.Number( ) )
		table.mMaxTableLength = table.Number( );
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_void Dictionary< Type, Key, _TABLE, _DIVISOR >::Remove( const Key& key, _dword tableid )
{
	EGE_ASSERT( tableid < _TABLE );

	mLookupTable[ tableid ].Remove( key );
}

template< typename Type, typename Key, _dword _TABLE, _dword _DIVISOR >
_void Dictionary< Type, Key, _TABLE, _DIVISOR >::Clear( )
{
	for ( _dword i = 0; i < _TABLE; i ++ )
	{
		mLookupTable[i].mMaxTableLength	= 0;
		mLookupTable[i].Clear( );
	}
}

}