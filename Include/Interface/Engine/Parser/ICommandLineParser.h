#pragma once

namespace EGE {

/// <summary>
/// The command line parser interface.
/// </summary>
class ICommandLineParser : public IObject {
public:
	//! The argument data
	struct ArgData {
		//! Indicates it's optional, and use '/name' argument style
		_ubool mIsOptional;
		//!	The configure key name
		WString mKeyName;
		//!	The configure value
		Variable mValue;
	};
	typedef Array<ArgData> ArgDataArray;

public:
	//!	Parse command line.
	//!	@param		string	The command line string.
	//!	@return		none.
	virtual _void Parse(WStringPtr string) PURE;
	//!	Parse command line.
	//!	@param		strings	The command line strings.
	//!	@return		none.
	virtual _void Parse(const WStringArray& strings) PURE;

	//!	Get the command line strings.
	//!	@param		none.
	//!	@return		The command line strings.
	virtual const WStringArray& GetStrings() const PURE;

	//!	Get the command arguments data.
	//!	@param		none.
	//!	@return		The command arguments data.
	virtual const ArgDataArray& GetArguments() const PURE;
};

} // namespace EGE