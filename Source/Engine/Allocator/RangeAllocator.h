//! @file     RangeAllocator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RangeAllocator
//----------------------------------------------------------------------------

class RangeAllocator : public INTERFACE_OBJECT_IMPL( IRangeAllocator )
{
private:
	//!	The base address for allocator
	enum { _BASE_ADDRESS = 0x00000001 };

private:
	ILinearAllocatorRef	mAllocator;

public:
	RangeAllocator( );
	virtual ~RangeAllocator( );

public:
	//!	Create.
	_ubool Create( _dword size, _dword arrange_size );

// IRangeAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _dword	Alloc( _dword size ) override;
	virtual _dword	Reserve( _dword index ) override;
	virtual _dword	Free( _dword index ) override;
};

}