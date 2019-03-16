//! @file     IBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBuffer
//----------------------------------------------------------------------------

class IBuffer : public IObject
{
public:
	//!	Get buffer size in bytes.
	//!	@param		none.
	//!	@return		The size in bytes.
	virtual _dword GetSize( ) const PURE;
	//!	Get offset in bytes.
	//!	@param		none.
	//! @return		The offset in bytes.
	virtual _dword GetOffset( ) const PURE;

	//!	Seek buffer offset.
	//!	@param		flag	The seek flag.
	//!	@param		offset	The buffer size in bytes.
	//!	@return		The offset of buffer in bytes.
	virtual _dword Seek( _SEEK flag, _dword offset ) PURE;
	//!	Reset.
	//!	@param		none.
	//!	@return		none.
	virtual _void Reset( ) PURE;

	//!	Write buffer by internal offset.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		none.
	virtual _void Write( _dword size, const _byte* buffer ) PURE;
	//!	Flush.
	//!	@param		none.
	//!	@return		none.
	virtual _void Flush( ) PURE;
};

}