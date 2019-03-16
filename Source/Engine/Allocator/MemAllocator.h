//! @file     MemAllocator.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemAllocator
//----------------------------------------------------------------------------

class MemAllocator : public TAllocator< INTERFACE_OBJECT_IMPL( IAllocator ) >
{
private:
	typedef TAllocator< INTERFACE_OBJECT_IMPL( IAllocator ) > BaseClass;

private:
	PageAllocator	mPageAllocator;

private:
	//!	The page allocator callback functions.
	static _byte*	OnAllocate( _dword size );
	static _void	OnFree( _byte* address );

public:
	MemAllocator( _dword arrange_size );
	virtual ~MemAllocator( );

public:
	//!	Create.
	//!	@param		page_size		The page size.
	//!	@param		min_chunk_size	The minimal chunk size.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool Create( _dword page_size, _dword min_chunk_size );

// IAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _byte*	Alloc( _dword size ) override;
	virtual _void	Free( _void* pointer ) override;
	virtual _void	FreeAll( ) override;
};

}