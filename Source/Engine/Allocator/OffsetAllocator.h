//! @file     OffsetAllocator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// OffsetAllocator
//----------------------------------------------------------------------------

class OffsetAllocator : public INTERFACE_OBJECT_IMPL( IOffsetAllocator )
{
private:
	//!	The base address for allocator
	enum { _BASE_ADDRESS = 0x00000001 };

private:
	ILinearAllocatorRef	mAllocator;

public:
	OffsetAllocator( );
	virtual ~OffsetAllocator( );

public:
	//!	Create.
	_ubool Create( _dword size, _dword arrange_size );

// IOffsetAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _dword	Alloc( _dword size ) override;
	virtual _dword	Free( _dword offset ) override;
	virtual _dword	Reserve( _dword offset ) override;
	virtual _void	FreeAll( ) override;
};

//----------------------------------------------------------------------------
// OffsetAllocator Implementation
//----------------------------------------------------------------------------

}