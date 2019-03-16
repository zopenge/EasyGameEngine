//! @file     IRangeAllocator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IRangeAllocator
//----------------------------------------------------------------------------

class IRangeAllocator : public IObject
{
public:
	//!	Cleanup.
	//!	@param		none.
	//!	@return		none.
	virtual _void Cleanup( ) PURE;

	//!	Check whether can allocate by specified size.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates can allocate the buffer by specified size.
	virtual _ubool CanAlloc( _dword size ) const PURE;

	//!	Allocate.
	//!	@param		size		The buffer size in bytes.
	//!	@return		The start index, -1 indicates failure.
	virtual _dword Alloc( _dword size ) PURE;
	//!	Reserve.
	//!	@param		index		The start index.
	//!	@return		The referenced count.
	virtual _dword Reserve( _dword index ) PURE;
	//!	Free.
	//!	@param		index		The start index.
	//!	@return		The referenced count, 0 indicates has been free.
	virtual _dword Free( _dword index ) PURE;
};

}