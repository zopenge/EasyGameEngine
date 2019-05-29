#pragma once

namespace EGE {

/// <summary>
/// The logger interface.
/// </summary>
class ILogger : public IObject {
public:
	//!	Output log.
	//!	@param		type		The log type.
	//!	@param		string		The log string.
	//!	@return		none.
	virtual _void OutputString(WStringPtr type, WStringPtr string) PURE;
};

} // namespace EGE