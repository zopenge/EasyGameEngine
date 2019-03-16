//! @file     PagePool.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PagePool
//----------------------------------------------------------------------------

//! This class is template container class, represents a page pool.
template< typename Type, _dword _PAGE_SIZE > 
class PagePool
{
private:
	//!	Total page number
	_dword	mPageNumber;
	//! Element page pool
	Type**	mElementPages;

public:
	//! Constructor, create an empty PagePool.
	//! @param		size		The maximal size of the PagePool in number of element.
	PagePool( );
	//! Copy-Constructor, create a PagePool by copy from another one.
	//! @param		PagePool		The other PagePool.
	PagePool( const PagePool< Type, _PAGE_SIZE >& pool );
	//! Destructor, delete the PagePool, and release the memory used by nodes.
	//! @param		none
	~PagePool( );

public:
	//! Copy elements from another PagePool.
	//! @param		PagePool		The other PagePool.
	//! @return		The reference of current PagePool.
	PagePool< Type, _PAGE_SIZE >& operator = ( const PagePool< Type, _PAGE_SIZE >& pool );

	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in pool.
	//! @return		The mutable element reference.
	Type& operator [] ( _dword index );

	//!	Get the total page number.
	//!	@param		none.
	//!	@return		The total page number.
	_dword GetPageNumber( ) const;

	//!	Create.
	//!	@param		page_number	The page number.
	//!	@return		none.
	_void Create( _dword page_number );
	//! Clear.
	//! @param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// PagePool Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _PAGE_SIZE > 
PagePool< Type, _PAGE_SIZE >::PagePool( )
{
	mPageNumber		= 0;
	mElementPages	= _null;
}

template< typename Type, _dword _PAGE_SIZE > 
PagePool< Type, _PAGE_SIZE >::PagePool( const PagePool< Type, _PAGE_SIZE >& pool )
{
	mPageNumber		= pool.mPageNumber;
	mElementPages	= new Type*[ mPageNumber ];

	for ( _dword i = 0; i < mPageNumber; i ++ )
	{
		if ( pool.mElementPages[i] == _null )
			continue;

		mElementPages[i] = new Type[ _PAGE_SIZE ];
		for ( _dword j = 0; j < _PAGE_SIZE; j ++ )
			mElementPages[i][j] = pool.mElementPages[i][j];
	}
}

template< typename Type, _dword _PAGE_SIZE > 
PagePool< Type, _PAGE_SIZE >::~PagePool( )
{
	Clear( );

	EGE_DELETE_ARRAY( mElementPages );
}

template< typename Type, _dword _PAGE_SIZE > 
PagePool< Type, _PAGE_SIZE >& PagePool< Type, _PAGE_SIZE >::operator = ( const PagePool< Type, _PAGE_SIZE >& pool )
{
	Clear( );

	EGE_DELETE_ARRAY( mElementPages );

	mPageNumber		= pool.mPageNumber;
	mElementPages	= new Type*[ mPageNumber ];

	for ( _dword i = 0; i < mPageNumber; i ++ )
	{
		if ( pool.mElementPages[i] == _null )
			continue;

		mElementPages[i] = new Type[ _PAGE_SIZE ];
		for ( _dword j = 0; j < _PAGE_SIZE; j ++ )
			mElementPages[i][j] = pool.mElementPages[i][j];
	}

	return *this;
}

template< typename Type, _dword _PAGE_SIZE > 
Type& PagePool< Type, _PAGE_SIZE >::operator [] ( _dword index )
{
	EGE_ASSERT( index < _PAGE_SIZE * mPageNumber );

	_dword page_index		= index / _PAGE_SIZE;
	_dword element_index	= index - (page_index * _PAGE_SIZE);

	// Create the element page pool if it's empty
	Type*& element_page = mElementPages[ page_index ];
	if ( element_page == _null )
		element_page = new Type[ _PAGE_SIZE ];

	return element_page[ element_index ];
}

template< typename Type, _dword _PAGE_SIZE >
_dword PagePool< Type, _PAGE_SIZE >::GetPageNumber( ) const
{
	return mPageNumber;
}

template< typename Type, _dword _PAGE_SIZE > 
_void PagePool< Type, _PAGE_SIZE >::Create( _dword page_number )
{
	Clear( );

	EGE_DELETE_ARRAY( mElementPages );

	mPageNumber		= page_number;
	mElementPages	= new Type*[ mPageNumber ];
	EGE_MEM_SET( mElementPages, 0, sizeof( Type*) * mPageNumber );
}

template< typename Type, _dword _PAGE_SIZE > 
_void PagePool< Type, _PAGE_SIZE >::Clear( )
{
	for ( _dword i = 0; i < mPageNumber; i ++ )
		EGE_DELETE_ARRAY( mElementPages[i] );
}

}