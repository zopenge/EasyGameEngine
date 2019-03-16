//! @file     TAllocator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAllocator
//----------------------------------------------------------------------------

template< typename Type >
class TAllocator : public Type
{
protected:
	//!	The arrange size in bytes
	_dword	mArrangeSize;

protected:
	TAllocator( _dword arrange_size );
	virtual ~TAllocator( );

// IAllocator Interface
public:
	virtual _dword	GetArrangeSize( ) const override;

	virtual _byte*	Alloc( _dword size ) override;
	virtual _byte*	AllocZ( _dword size ) override;
	virtual _byte*	AllocM( _dword size, const _byte* buffer ) override;

	virtual _byte*	ReAlloc( _void* pointer, _dword size ) override;
	virtual _byte*	ReAlloc( _void* pointer, _dword size, const _byte* buffer ) override;
};

//----------------------------------------------------------------------------
// TAllocator Implementation
//----------------------------------------------------------------------------

template< typename Type >
TAllocator< Type >::TAllocator( _dword arrange_size )
{
	EGE_ASSERT( arrange_size != 0 );

	mArrangeSize = arrange_size;
}

template< typename Type >
TAllocator< Type >::~TAllocator( )
{
}

template< typename Type >
_dword TAllocator< Type >::GetArrangeSize( ) const
{
	return mArrangeSize;
}

template< typename Type >
_byte* TAllocator< Type >::Alloc( _dword size )
{
	// The inherited class must implement it
	EGE_ASSERT( _false );

	return _null;
}

template< typename Type >
_byte* TAllocator< Type >::AllocZ( _dword size )
{
	_byte* buffer = Alloc( size );
	if ( buffer != _null )
		EGE_MEM_SET( buffer, 0, size );

	return buffer;
}

template< typename Type >
_byte* TAllocator< Type >::AllocM( _dword size, const _byte* buffer )
{
	_byte* alloc_buffer = Alloc( size );
	if ( alloc_buffer == _null )
		return _null;

	if ( buffer != _null )
		EGE_MEM_CPY( alloc_buffer, buffer, size );
	else
		EGE_MEM_SET( alloc_buffer, 0, size );

	return alloc_buffer;
}

template< typename Type >
_byte* TAllocator< Type >::ReAlloc( _void* pointer, _dword size )
{
	this->Free( pointer );

	return Alloc( size );
}

template< typename Type >
_byte* TAllocator< Type >::ReAlloc( _void* pointer, _dword size, const _byte* buffer )
{
	_byte* realloc_buf = ReAlloc( pointer, size );
	if ( realloc_buf == _null )
		return _null;

	if ( buffer != _null )
		EGE_MEM_CPY( realloc_buf, buffer, size );

	return realloc_buf;
}

}