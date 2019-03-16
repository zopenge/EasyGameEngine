//! @file     IGraphicVertexArray.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicVertexArray
//----------------------------------------------------------------------------

class IGraphicVertexArray : public IObject
{
public:
	//!	Get the vertex array resource.
	//!	@param		none.
	//!	@return		The vertex array resource.
	virtual VertexArrayRHI* GetResource( ) const PURE;

	//!	Bind.
	//!	@param		none.
	//!	@return		none.
	virtual _void Bind( ) PURE;

	//!	Get element's offset in bytes.
	//!	@param		usage		The vertex element usage.
	//!	@param		usage_index	The usage index.
	//!	@return		The offset in bytes.
	virtual _dword GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const PURE;

	//!	Lock vertex buffer data.
	//!	@param		offset		The offset in bytes.
	//!	@param		size		The size in bytes.
	//!	@return		The vertex buffer data.
	virtual _byte* LockVBData( _dword offset, _dword size ) PURE;
	//!	Unlock vertex buffer data.
	//!	@param		none.
	//!	@return		The vertex buffer data.
	virtual _void UnlockVBData( ) PURE;
	//!	Get vertex buffer data.
	//!	@param		none.
	//!	@return		The vertex buffer data.
	virtual const _byte* GetVBData( ) PURE;
	//!	Get stride size of vertex buffer in bytes.
	//!	@param		none.
	//! @return		The stride size in bytes.
	virtual _dword GetVBStride( ) const PURE;
	//!	Get total size of vertex buffer in bytes.
	//!	@param		none.
	//! @return		The total size in bytes.
	virtual _dword GetVBSize( ) const PURE;
	//!	Get offset of vertex buffer in bytes.
	//!	@param		none.
	//! @return		The offset in bytes.
	virtual _dword GetVBOffset( ) const PURE;
	//!	Get the current index of vertex buffer.
	//!	@param		none.
	//!	@return		The index of vertex buffer.
	virtual _dword GetVBIndex( ) const PURE;
	//!	Write vertex buffer by internal offset.
	//!	@param		offset		The buffer size in bytes.
	//!	@param		size		The vertices buffer size in bytes.
	//!	@param		buffer		The vertices buffer data.
	//!	@return		none.
	virtual _void WriteVB( _dword offset, _dword size, const _byte* buffer ) PURE;
	//!	Write vertex buffer.
	//!	@param		size		The vertices buffer size in bytes.
	//!	@param		buffer		The vertices buffer data.
	//!	@return		none.
	virtual _void WriteVB( _dword size, const _byte* buffer ) PURE;

	//!	Lock index buffer data.
	//!	@param		offset		The offset in bytes.
	//!	@param		size		The size in bytes.
	//!	@return		The index buffer data.
	virtual _byte* LockIBData( _dword offset, _dword size ) PURE;
	//!	Unlock index buffer data.
	//!	@param		none.
	//!	@return		The index buffer data.
	virtual _void UnlockIBData( ) PURE;
	//!	Get the index buffer data.
	//!	@param		none.
	//!	@return		The index buffer data.
	virtual const _byte* GetIBData( ) PURE;
	//!	Get stride size of index buffer in bytes.
	//!	@param		none.
	//! @return		The stride size in bytes.
	virtual _dword GetIBStride( ) const PURE;
	//!	Get total size of index buffer in bytes.
	//!	@param		none.
	//! @return		The total size in bytes.
	virtual _dword GetIBSize( ) const PURE;
	//!	Get offset of index buffer in bytes.
	//!	@param		none.
	//! @return		The offset in bytes.
	virtual _dword GetIBOffset( ) const PURE;
	//!	Write index buffer by internal offset.
	//!	@param		offset		The buffer size in bytes.
	//!	@param		size		The index buffer size in bytes.
	//!	@param		buffer		The index buffer data.
	//!	@return		none.
	virtual _void WriteIB( _dword offset, _dword size, const _byte* buffer ) PURE;
	//!	Write index buffer.
	//!	@param		size		The index buffer size in bytes.
	//!	@param		buffer		The index buffer data.
	//!	@return		none.
	virtual _void WriteIB( _dword size, const _byte* buffer ) PURE;

	//!	Write to vertex buffer and index buffer.
	virtual _void WriteBuffers( _dword vb_size, const _byte* vb_data, _dword ib_number, const _word* ib_data ) PURE;
	//!	Flush vertex and index buffer.
	//!	@param		none.
	//!	@return		none.
	virtual _void FlushBuffers( ) PURE;
};

}