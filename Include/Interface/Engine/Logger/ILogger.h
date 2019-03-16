//! @file     ILogger.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ILogger
//----------------------------------------------------------------------------

class ILogger : public IObject
{
public:
	//!	The filter flags.
	enum _FILTER_FLAGS
	{
		//!	The log will combine with time info
		_FILTER_WITH_TIME		= 1 << 0,
		//!	The log will combine with category info
		_FILTER_WITH_CATEGORY	= 1 << 1,
	};

	//!	The options.
	enum _OPTIONS
	{
		//!	We will keep all logs in it
		_OPTION_KEEP_HISTORY	= 1 << 0,
	};

public:
	//!	Get the filter flags.
	//!	@param		none.
	//!	@return		The filer flags, @see _FILTER_FLAGS.
	virtual const FlagsObject& GetFilterFlags( ) const PURE;
	//!	Set the filter flags.
	//!	@param		flags		The filer flags, @see _FILTER_FLAGS.
	//!	@return		none.
	virtual _void SetFilterFlags( _dword flags ) PURE;

	//!	Enable/Disable the options.
	//!	@param		option		The option, @see _OPTIONS.
	//!	@param		enable		True indicates enable it, otherwise disable it.
	//!	@return		none.
	virtual _void EnableOption( _dword option, _ubool enable ) PURE;
	//!	Check whether enable options.
	//!	@param		option		The option, @see _OPTIONS.
	//!	@return		True indicates enable it, otherwise disable it.
	virtual _ubool IsEnableOption( _dword option ) const PURE;

	//!	Get the history log.
	//!	@param		none.
	//!	@return		The history log.
	virtual WStringPtr GetHistoryLog( ) const PURE;
	//!	Clear the history log.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearHistoryLog( ) PURE;

	//!	Write log.
	//!	@param		type		The log type.
	//!	@param		string		The log string.
	//!	@return		none.
	virtual _void Write( _LOG type, WStringPtr string ) PURE;
	//!	Write log.
	//!	@param		type		The log type.
	//!	@param		category	The log category.
	//!	@param		string		The log string.
	//!	@return		none.
	virtual _void Write( _LOG type, WStringPtr category, WStringPtr string ) PURE;

	//!	Write original log.
	//!	@param		string		The log string.
	//!	@return		none.
	virtual _void WriteOriginalLog( WStringPtr string ) PURE;
};

}