#pragma once

namespace EGE {

/// <summary>
/// The stream interface.
/// </summary>
class IStream : public IObject {
public:
	//!	Get buffer size in bytes.
	//!	@param		none.
	//!	@return		The buffer size.
	virtual _dword GetSize() const PURE;
	//!	Get the offset of current buffer pointer from begin.
	//!	@param		none.
	//!	@return		The offset of current buffer pointer in bytes from begin.
	virtual _dword GetOffset() const PURE;

	//!	Seek current buffer pointer to begin.
	//!	@param		flag		The seek flag.
	//! @param		distance	Number of bytes to move.
	//! @return		The current offset of stream from begin.
	virtual _dword Seek(SeekFlag flag, _int distance) PURE;

	//!	Set the stream endian type.
	//!	@param		endian		The endian type.
	//!	@return		none.
	virtual _void SetEndian(Encoding endian) PURE;
	//!	Get the stream endian type.
	//!	@param		none.
	//!	@return		The endian type.
	virtual Encoding GetEndian() const PURE;
};

} // namespace EGE