//! @file     INetworkModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkModule
//----------------------------------------------------------------------------

class INetworkModule : public IModule
{
public:
	//!	Enable/Disable options.
	//!	@param		options		The options, @see _NETWORK_OPTIONS.
	//!	@param		enable		True indicates enable options, otherwise disable.
	//!	@return		none.
	virtual _void EnableOptions( _dword options, _ubool enable ) PURE;
	//!	Check enable options or not.
	//!	@param		options		The options, @see _NETWORK_OPTIONS.
	//!	@return		True indicates these options enabled, otherwise disable.
	virtual _ubool IsEnableOptions( _dword options ) const PURE;

	//!	Get the remote site's time.
	//!	@param		url			The URL address.
	//!	@param		time_out	The time out in milliseconds.
	//!	@param		time		The remote site's time.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetRemoteSiteTime( WStringPtr url, _dword time_out, Time& time ) PURE;

	//!	Update the total download bytes.
	//!	@param		size		The size in bytes.
	//!	@return		none.
	virtual _void UpdateTotalDownloadBytes( _qword size ) PURE;
	//!	Update the total upload bytes.
	//!	@param		size		The size in bytes.
	//!	@return		none.
	virtual _void UpdateTotalUploadBytes( _qword size ) PURE;

	//!	Get the total download bytes.
	//!	@param		none.
	//!	@return		The total download bytes.
	virtual _qword GetTotalDownloadBytes( ) const PURE;
	//!	Get the total upload bytes.
	//!	@param		none.
	//!	@return		The total upload bytes.
	virtual _qword GetTotalUploadBytes( ) const PURE;

	//!	Set simulating lag.
	//!	@param		min_lag		The min lag time in milliseconds.
	//!	@param		max_lag		The max lag time in milliseconds.
	//!	@return		none.
	virtual _void SetSimulatingLag( _dword min_lag, _dword max_lag ) PURE;
	//!	Get simulating lag.
	//!	@param		none.
	//!	@return		The lag time range in milliseconds.
	virtual const DwordRange& GetSimulatingLag( ) const PURE;
};

}