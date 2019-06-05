#pragma once

namespace EGE {

/// <summary>
/// The bits stream reader interface.
/// </summary>
class IBitStreamReader : public IStreamReader {
public:
	//!	Seek padded section data.
	//!	@param		none.
	//!	@return		none.
	virtual _void SeekPaddedSection() PURE;
	//!	Seek bits.
	//!	@param		bits	The bits number.
	//!	@return		none.
	virtual _void SeekBits(_dword bits) PURE;

	//!	Read the buffer data.
	//!	@param		buffer			The buffer data.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_void* buffer, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_tiny& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_byte& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_word& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_short& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_int& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_dword& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_qword& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_float& value, _dword bitsnumber) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream(_double& value) PURE;
};

} // namespace EGE