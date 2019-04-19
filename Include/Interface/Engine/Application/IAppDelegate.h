#pragma once

namespace EGE {

/// <summary>
/// The application delegate to process kernel events.
/// </summary>
class IAppDelegate : public IObserver {
public:
	//!	When launch the application.
	//!	@remark		We should just process tasks lightly in this callback function, otherwise it could be killed by OS.
	//!	@param		application		The application.
	//! @param		cmd_parser		The command line parser.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnLaunch(IApplication* application, ICommandLineParser* cmd_parser) PURE;
	//!	When load the application.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnLoad() PURE;
	//!	When unload the application.
	//! @param		none.
	//! @return		none.
	virtual _void OnUnload() PURE;

	//!	When update the application.
	//! @param		elapse			The millisecond time of the update interval.
	//! @return		none.
	virtual _void OnTick(_dword elapse) PURE;

	//!	When handle the application event.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void OnHandleEvent(BaseEventData& event) PURE;
};

} // namespace EGE