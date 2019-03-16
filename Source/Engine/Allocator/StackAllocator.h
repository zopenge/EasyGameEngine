//! @file     StackAllocator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StackAllocator
//----------------------------------------------------------------------------

class StackAllocator : public TAllocator< INTERFACE_OBJECT_IMPL( IStackAllocator ) >
{
private:
	typedef TAllocator< INTERFACE_OBJECT_IMPL( IStackAllocator ) > BaseClass;

private:
	//!	The buffer data
	_byte*	mBuffer;
	//!	The buffer size
	_dword	mBufferSize;
	//!	The current buffer offset in bytes ( bounds in [0, mBufferSize) )
	_dword	mBufferOffset; 

public:
	StackAllocator( _dword arrange_size );
	virtual ~StackAllocator( );

public:
	//!	Create.
	//!	@param		size		The buffer size.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool Create( _dword size );

// IAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _byte*	Alloc( _dword size ) override;
	virtual _void	Free( _void* pointer ) override;

	virtual _void	FreeAll( ) override;

// IStackAllocator Interface
public:
	virtual _dword	GetOffset( ) const override;
	virtual _void	SetOffset( _dword offset ) override;
	
	virtual _dword	GetStackSize( ) const override;

	virtual _void	Pop( _dword size ) override;
};

//----------------------------------------------------------------------------
// StackAllocator Implementation
//----------------------------------------------------------------------------

}