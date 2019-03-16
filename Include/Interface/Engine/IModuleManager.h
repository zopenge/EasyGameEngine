//! @file     IModuleManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IModuleManager
//----------------------------------------------------------------------------

class IModuleManager : public ITPowerable< IObservable >
{
public:
	//!	Check whether it's in launching application procession.
	//!	@param		none.
	//!	@return		True indicates it's in launching application procession.
	virtual _ubool IsLaunchingApp( ) const PURE;
	//!	Check whether has loaded application.
	//!	@param		none.
	//!	@return		True indicates it has loaded application.
	virtual _ubool HasLoadedApp( ) const PURE;

	//!	Reset resources.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ResetResources( ) PURE;
	//!	Unload resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnloadResources( ) PURE;

	//!	Register observer.
	//!	@param		app_delegate	The application delegate.
	//!	@return		none.
	virtual _void RegisterAppDelegate( IAppDelegate* app_delegate ) PURE;
	//!	Get registered application delegate.
	//!	@param		none.
	//!	@return		The application delegate.
	virtual IAppDelegate* GetRegisteredAppDelegate( ) PURE;

	//!	Register module.
	//!	@param		module			The module object.
	//!	@param		priority		The module priority, low value indicates low priority.
	//!	@return		none.
	virtual _void RegisterModule( IModule* module, _dword priority ) PURE;
	//!	Unregister module.
	//!	@param		module			The module.
	//!	@return		none.
	virtual _void UnregisterModule( IModule* module ) PURE;

	//!	Output string in ANSI mode.
	//! @param		type		The log type.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString( _LOG type, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) PURE;
	//!	Output string in UNICODE mode.
	//! @param		type		The log type.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString( _LOG type, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) PURE;
	//!	Output string in ANSI mode.
	//! @param		type		The log type.
	//! @param		module_name	The module name.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString( _LOG type, AStringPtr module_name, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) PURE;
	//!	Output string in UNICODE mode.
	//! @param		type		The log type.
	//! @param		module_name	The module name.
	//!	@param		string		The log string.
	//!	@param		file_name	The optional file name.
	//!	@param		line_number	The optional line number in file.
	//!	@return		none.
	virtual _void OutputString( _LOG type, WStringPtr module_name, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) PURE;

	//!	Add delay message.
	//!	@param		message			The message info.
	//!	@return		none.
	virtual _void AddDelayEvent( const EventBase& event ) PURE;
	//!	Process all delay events.
	//!	@param		none.
	//!	@return		none.
	virtual _void ProcessDelayEvents( ) PURE;
	//!	Process event.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void ProcessEvent( EventBase& event ) PURE;
};

}