#pragma once

namespace EGE {

class Clipboard {
public:
	//! Copy the string to clipboard.
	//! @param string		The string what will be copied.
	//! @return True indicates success false indicates failure.
	static _ubool Copy(WStringPtr string);

	//! Paste the string from clipboard.
	//! @param string		The string what will be pasted.
	//! @return True indicates success false indicates failure.
	static _ubool Paste(WString& string);
};

} // namespace EGE