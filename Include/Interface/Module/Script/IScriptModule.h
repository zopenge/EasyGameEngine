//! @file     IScriptModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptModule
//----------------------------------------------------------------------------

class IScriptModule : public IModule
{
public:
	//!	Get the total memory size in bytes.
	//!	@param		none.
	//!	@return		The memory size in bytes.
	virtual _dword GetTotalMemSize( ) const PURE;

	//!	Set the remote debugger.
	//!	@param		address		The remote address.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetRemoteDebugger( const Address& address ) PURE;
	//!	Get the remote debugger.
	//!	@param		none.
	//!	@return		The remote address.
	virtual const Address& GetRemoteDebugger( ) const PURE;
};

}