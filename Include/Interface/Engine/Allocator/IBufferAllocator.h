//! @file     IBufferAllocator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBufferAllocator
//----------------------------------------------------------------------------

class IBufferAllocator : public IObject
{
public:
	//!	Reset.
	//!	@param		none.
	//!	@return		none.
	virtual _void Reset( ) PURE;

	//!	Allocate.
	//!	@param		size		The buffer size in bytes.
	//!	@return		The buffer data.
	virtual _byte* Alloc( _dword size ) PURE;
};

}