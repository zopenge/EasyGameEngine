//! @file     ICacheBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICacheBufferNotifier
//----------------------------------------------------------------------------

class ICacheBufferNotifier : public IObject
{
public:
	//!	When resize buffer.
	virtual _void OnResizeBuffer( _dword size ) PURE;
	//!	When update buffer.
	virtual _void OnUpdateBuffer( _dword offset, _dword size, const _byte* buffer ) PURE;
};

//----------------------------------------------------------------------------
// ICacheBuffer
//----------------------------------------------------------------------------

class ICacheBuffer : public IObject
{
public:
	//!	Set the cache buffer size in bytes.
	//!	@remark		This operation will flush the buffer.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetCacheBufferSize( _dword size ) PURE;
	//!	Get the offset of cache buffer in bytes.
	//!	@param		none.
	//! @return		The offset of cache buffer in bytes.
	virtual _dword GetCacheBufferOffset( ) const PURE;
	//!	Get the size of cache buffer in bytes.
	//!	@param		none.
	//! @return		The size of cache buffer in bytes.
	virtual _dword GetCacheBufferSize( ) const PURE;
	//!	Get the cache buffer data.
	//!	@param		none.
	//!	@return		The cache buffer.
	virtual const _byte* GetCacheBufferData( ) const PURE;

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

	//!	Write buffer by internal offset.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		none.
	virtual _void Write( _dword size, const _byte* buffer ) PURE;
	//!	Flush.
	//!	@param		none.
	//!	@return		none.
	virtual _void Flush( ) PURE;
	//!	Reset buffer.
	//!	@param		none.
	//!	@return		none.
	virtual _void Reset( ) PURE;
};

}