#pragma once

namespace EGE {

/// <summary>
/// The text file.
/// </summary>
class ITXTFile : public IObject {
public:
	//!	Get the encode type.
	//!	@param		none.
	//!	@return		The encode type.
	virtual Encoding GetEncodeType() const PURE;

	//!	Read all text characters into string.
	//!	@param		string			The string would store all text file characters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadString(WString& string) PURE;

	//!	Read the single line string in UNICODE mode.
	//!	@param		string			The UNICODE string.
	//!	@param		linenumber		The line number of it.
	//! @return		True indicates still has text need to read, otherwise indicates finished reading all texts.
	virtual _ubool ReadLine(WString& string, _dword* linenumber = _null) PURE;

	//!	Jump to the specific line.
	//!	@param		linenumber		The line number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool JumpToLine(_dword linenumber) PURE;
};

} // namespace EGE