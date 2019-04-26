#pragma once

namespace EGE {

/// <summary>
/// The cache buffer.
/// </summary>
class ICacheBuffer : public IBuffer {
public:
	//!	When resize buffer.
	typedef _void (*OnResizeBuffer)(_dword size);
	//!	When update buffer.
	typedef _void (*OnUpdateBuffer)(_dword offset, _dword size, const _byte* buffer);

public:
	//!	Set the cache buffer size in bytes.
	//!	@remark		This operation will flush the buffer.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetCacheBufferSize(_dword size) PURE;
	//!	Get the offset of cache buffer in bytes.
	//!	@param		none.
	//! @return		The offset of cache buffer in bytes.
	virtual _dword GetCacheBufferOffset() const PURE;
	//!	Get the size of cache buffer in bytes.
	//!	@param		none.
	//! @return		The size of cache buffer in bytes.
	virtual _dword GetCacheBufferSize() const PURE;
	//!	Get the cache buffer data.
	//!	@param		none.
	//!	@return		The cache buffer.
	virtual const _byte* GetCacheBufferData() const PURE;
};

} // namespace EGE