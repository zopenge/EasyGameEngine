//! @file     IGraphicCachedBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicCachedBuffer
//----------------------------------------------------------------------------

class IGraphicCachedBuffer : public IObject
{
public:
	//!	Set the cached buffer size in bytes.
	//!	@remark		This operation will flush the buffer.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetCachedBufferSize( _dword size ) PURE;
	//!	Get the offset of cached buffer in bytes.
	//!	@param		none.
	//! @return		The offset of cached buffer in bytes.
	virtual _dword GetCachedBufferOffset( ) const PURE;

	//!	Get the offset of buffer in bytes.
	//!	@param		none.
	//! @return		The offset of buffer in bytes.
	virtual _dword GetBufferOffset( ) const PURE;
	//!	Seek buffer offset.
	//!	@param		flag	The seek flag.
	//!	@param		offset	The buffer size in bytes.
	//!	@return		The offset of buffer in bytes.
	virtual _dword SeekBufferOffset( _SEEK flag, _dword offset ) PURE;

	//!	Write buffer by internal offset.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool WriteBuffer( _dword size, const _byte* buffer ) PURE;
	//!	Flush cached buffer into buffer.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool FlushCachedBuffer( ) PURE;
	//!	Reset buffer.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ResetBuffer( ) PURE;
};

}