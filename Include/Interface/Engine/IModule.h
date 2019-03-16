//! @file     IModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IModule
//----------------------------------------------------------------------------

class IModule : public ITPowerable< IObserver >
{
public:
	//!	Reset resources.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ResetResources( ) PURE;
	//!	Unload resources.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnloadResources( ) PURE;

	//!	Get the module name.
	//!	@param		none.
	//!	@return		The module name.
	virtual WStringPtr GetModuleName( ) const PURE;
	//!	Get the module version.
	//!	@param		none.
	//!	@return		The module version.
	virtual const Version& GetModuleVersion( ) const PURE;

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

	//!	Handle event.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void HandleEvent( EventBase& event ) PURE;
};

}