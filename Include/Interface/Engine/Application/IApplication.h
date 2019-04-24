#pragma once

namespace EGE {

/// <summary>
/// The main application.
/// </summary>
class IApplication : public IObserver {
public:
	//!	Get the application handle.
	//!	@param		none.
	//!	@return		The application handle.
	virtual _handle GetHandle() const PURE;
	//!	Get the application layer handle.
	//!	@param		none.
	//!	@return		The application layer handle.
	virtual _handle GetLayerHandle() const PURE;

	//!	Quit the application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Quit() PURE;

	//!	Restart the application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Restart() PURE;

	//!	Run the application.
	//!	@remark		We just use the application delegate pointer directly without clone or copy. <br />
	//!				The user should never call this interface.
	//!	@param		app_delegate	The application delegate.
	//!	@param		cmd_parser		The command line parser.
	//!	@return		The return value.
	virtual _int Run(IAppDelegate* app_delegate, ICommandLineParser* cmd_parser) PURE;
};

} // namespace EGE