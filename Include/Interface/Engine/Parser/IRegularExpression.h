#pragma once

namespace EGE {

/// <summary>
/// The regular expression interface.
/// </summary>
class IRegularExpression : public IObject {
public:
	//!	Set the pattern.
	//!	@param		pattern		The pattern string.
	//!	@param		ignoreCase	True indicates ignore case.
	//! @return		True indicates success false indicates failure.
	virtual _ubool SetPattern(WStringPtr pattern, _ubool ignoreCase) PURE;
	//!	Get the pattern.
	//!	@param		none.
	//! @return		The pattern string.
	virtual WStringPtr GetPattern() const PURE;

	//!	Check whether match UNICODE string or not.
	//!	@param		string		The string what to be matched.
	//!	@return		True indicates match successful.
	virtual _ubool Match(WStringPtr string) const PURE;
};

} // namespace EGE