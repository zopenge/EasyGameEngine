#pragma once

namespace EGE {

/// <summary>
/// The bits stream writer interface.
/// </summary>
class IBitStreamWriter : public IStreamWriter {
public:
	//!	Seek padded section data.
	//!	@param		none.
	//!	@return		none.
	virtual _void SeekPaddedSection() PURE;
	//!	Seek bits.
	//!	@param		bits	The bits number.
	//!	@return		none.
	virtual _void SeekBits(_dword bits) PURE;
};

} // namespace EGE