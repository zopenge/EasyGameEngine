#pragma once

namespace EGE {

/// <summary>
/// The process debugger interface.
/// </summary>
class IProcessDebugger : public IObservable {
public:
	//!	Get the exit code.
	//!	@param		none.
	//!	@return		The exit code of process.
	virtual _long GetExitCode() const PURE;

	//!	Run the process.
	//!	@param		modulename		The module name of launching.
	//!	@param		cmdline			The command line of launching.
	//!	@param		workdir			The working directory.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Run(AStringPtr modulename, AStringPtr cmdline, AStringPtr workdir) PURE;
	//!	Run the process.
	//!	@param		modulename		The module name of launching.
	//!	@param		cmdline			The command line of launching.
	//!	@param		workdir			The working directory.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Run(WStringPtr modulename, WStringPtr cmdline, WStringPtr workdir) PURE;
};

} // namespace EGE