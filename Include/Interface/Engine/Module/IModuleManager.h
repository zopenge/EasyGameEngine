#pragma once

namespace EGE {

/// <summary>
/// The module manager interface.
/// </summary>
class IModuleManager : public IObservable {
public:
	//!	Load resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void LoadResources() PURE;
	//!	Unload resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnloadResources() PURE;

	//!	Register observer.
	//!	@param		app_delegate	The application delegate.
	//!	@return		none.
	virtual _void RegisterAppDelegate(IAppDelegate* app_delegate) PURE;
	//!	Get registered application delegate.
	//!	@param		none.
	//!	@return		The application delegate.
	virtual IAppDelegate* GetRegisteredAppDelegate() PURE;

	//!	Register module.
	//!	@param		module			The module object.
	//!	@param		priority		The module priority, low value indicates low priority.
	//!	@return		none.
	virtual _void RegisterModule(IModule* module, _dword priority) PURE;
	//!	Unregister module.
	//!	@param		module			The module.
	//!	@return		none.
	virtual _void UnregisterModule(IModule* module) PURE;

	//!	Output string in ANSI mode.
	//! @param		type		The log type.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString(LogType type, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0) PURE;
	//!	Output string in UNICODE mode.
	//! @param		type		The log type.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString(LogType type, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0) PURE;

	//!	Handle event.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void HandleEvent(BaseEventData& event) PURE;
};

} // namespace EGE