#pragma once

namespace EGE {

/// <summary>
/// The module interface.
/// </summary>
class IModule : public IObserver {
public:
	//!	Load resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void LoadResources() PURE;
	//!	Unload resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnloadResources() PURE;

	//!	Get the module name.
	//!	@param		none.
	//!	@return		The module name.
	virtual WStringPtr GetName() const PURE;
	//!	Get the module version.
	//!	@param		none.
	//!	@return		The module version.
	virtual const Version& GetVersion() const PURE;

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