//! @file     IGraphicBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicBuffer
//----------------------------------------------------------------------------

class IGraphicBuffer : public IObject
{
public:
	//!	Get buffer stride in bytes.
	//!	@param		none.
	//!	@return		The stride in bytes.
	virtual _dword GetStride( ) const PURE;
	//!	Get buffer size in bytes.
	//!	@param		none.
	//!	@return		The size in bytes.
	virtual _dword GetSize( ) const PURE;

	//!	Write buffer by internal offset.
	//!	@param		offset	The buffer offset in bytes.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		none.
	virtual _void Write( _dword offset, _dword size, const _byte* buffer ) PURE;
	//!	Flush.
	//!	@param		none.
	//!	@return		none.
	virtual _void Flush( ) PURE;

	//!	Lock buffer data.
	//!	@param		offset		The offset in bytes.
	//!	@param		size		The size in bytes.
	//!	@return		The buffer data.
	virtual _byte* LockBufferData( _dword offset, _dword size ) PURE;
	//!	Unlock buffer data.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnlockBufferData( ) PURE;
	//!	Get buffer data.
	//!	@param		none.
	//!	@return		The buffer data.
	virtual const _byte* GetBufferData( ) PURE;
};

}