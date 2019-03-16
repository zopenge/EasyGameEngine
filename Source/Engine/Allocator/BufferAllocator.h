//! @file     BufferAllocator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BufferAllocator
//----------------------------------------------------------------------------

class BufferAllocator : public INTERFACE_OBJECT_IMPL( IBufferAllocator )
{
private:
	typedef Array< IStackAllocatorRef > StackAllocatorArray;

private:
	StackAllocatorArray	mStackAllocators;

public:
	BufferAllocator( );
	virtual ~BufferAllocator( );

public:
	//!	Create.
	_ubool Create( _dword size, _dword arrange_size );

// IBufferAllocator Interface
public:
	virtual _void	Reset( ) override;

	virtual _byte*	Alloc( _dword size ) override;
};

//----------------------------------------------------------------------------
// BufferAllocator Implementation
//----------------------------------------------------------------------------

}