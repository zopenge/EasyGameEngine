//! @file     IAnalyticsCenter.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAnalyticsCenter
//----------------------------------------------------------------------------

class IAnalyticsCenter : public IObject
{
public:
	//!	The gender values.
	enum _GENDER
	{
		_GENDER_FEMALE,
		_GENDER_MALE,
	};

public:
	//!	Set the user ID.
	//!	@param		user_id		The user ID.
	//!	@return		none.
	virtual _void SetUserID( UStringPtr user_id ) PURE;
	//!	Set the age.
	//!	@param		age			The age.
	//!	@return		none.
	virtual _void SetAge( _dword age ) PURE;
	//!	Set the gender.
	//!	@param		gender		The gender.
	//!	@return		none.
	virtual _void SetGender( _GENDER gender ) PURE;

	//!	Enable/Disable.
	//!	@param		enable		True indicates enable it.
	//!	@return		none.
	virtual _void Enable( _ubool enable ) PURE;

	//!	Log.
	//!	@param		event_id	The event ID.
	//!	@param		parameters	The event parameters.
	//!	@return		none.
	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) PURE;
	//!	Log.
	//!	@param		event_id	The event ID.
	//!	@param		desc		The description.
	//!	@return		none.
    virtual _void LogEvent( UStringPtr event_id, UStringPtr desc ) PURE;

	//!	Error.
	//!	@param		error_id	The error ID.
	//!	@param		error_msg	The error message.
	//!	@param		error_class	The error class.
	//!	@return		none.
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) PURE;
};

}