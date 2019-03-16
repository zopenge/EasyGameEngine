//! @file     INetworkLogger.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkLogger
//----------------------------------------------------------------------------

class INetworkLogger : public ILogger
{
public:
	//!	Log in.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _void LogIn( ) PURE;
	//!	Log out.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _void LogOut( ) PURE;

	//!	Set the interval of sending log.
	//!	@param		interval	The interval in milliseconds.
	//! @return		none.
	virtual _void SetInterval( _dword interval ) PURE;
	//!	Get the interval of sending log.
	//!	@param		none.
	//! @return		The interval in milliseconds.
	virtual _dword GetInterval( ) const PURE;

	//!	Enable compression of sending log.
	//!	@param		enable		True indicates enable compression, otherwise send original log.
	//!	@return		none.
	virtual _void EnableCompression( _ubool enable ) PURE;
	//!	Check whether enable compression of sending log.
	//!	@param		none.
	//!	@return		True indicates enable compression, otherwise send original log.
	virtual _ubool IsEnabledCompression( ) const PURE;
};

}