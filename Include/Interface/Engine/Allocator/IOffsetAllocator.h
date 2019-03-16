//! @file     IOffsetAllocator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IOffsetAllocator
//----------------------------------------------------------------------------

class IOffsetAllocator : public IObject
{
public:
	//!	Cleanup pages.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _void Cleanup( ) PURE;

	//!	Check whether can allocate by specified size.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates can allocate the buffer by specified size.
	virtual _ubool CanAlloc( _dword size ) const PURE;

	//!	Allocate.
	//!	@param		size		The buffer size in bytes.
	//!	@return		The offset, -1 indicates failure.
	virtual _dword Alloc( _dword size ) PURE;
	//!	Free.
	//!	@param		offset		The offset in bytes.
	//!	@return		The referenced count, 0 indicates has been free.
	virtual _dword Free( _dword offset ) PURE;
	//!	Reserved.
	//!	@param		offset		The offset in bytes.
	//!	@return		The referenced count.
	virtual _dword Reserve( _dword offset ) PURE;
	//!	Free all allocated buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void FreeAll( ) PURE;
};

}