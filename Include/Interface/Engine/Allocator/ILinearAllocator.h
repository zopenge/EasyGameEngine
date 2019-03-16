//! @file     ILinearAllocator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ILinearAllocator
//----------------------------------------------------------------------------

class ILinearAllocator : public IAllocator
{
public:
	//!	Relocate address of buffer.
	//!	@param		buffer		The address of buffer data.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool RelocateBufferAddress( _byte* buffer ) PURE;

	//!	Reserved buffer by start bytes.
	//!	@param		start_bytes	The start bytes from buffer.
	//!	@return		The referenced count.
	virtual _dword ReserveBufferByStartBytes( _dword start_bytes ) PURE;
	//!	Free by start bytes.
	//!	@param		start_bytes	The start bytes from buffer.
	//!	@return		The referenced count, 0 indicates has been free.
	virtual _dword FreeByStartBytes( _dword start_bytes ) PURE;
};

}