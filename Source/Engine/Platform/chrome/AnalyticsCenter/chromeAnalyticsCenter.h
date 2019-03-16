//! @file     androidAnalyticsCenter.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidAnalyticsCenter
//----------------------------------------------------------------------------

class androidAnalyticsCenter : public TObject< IAnalyticsCenter >
{
private:
	//!	The analySDK interface object
	JNIInterfaceObject mAnalyticesCenterInterfaceObject;

public:
	androidAnalyticsCenter( );
	virtual ~androidAnalyticsCenter( );

public:
	//!	Initialize/Finalize.
	_ubool Initialize( UStringPtr app_id );
	_void Finalize( );

// IAnalyticsCenter Interface
public:
	virtual _void SetUserID( UStringPtr user_id ) override;
	virtual _void SetAge( _dword age ) override;
	virtual _void SetGender( _GENDER gender ) override;

	virtual _void Enable( _ubool enable ) override;

	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) override;
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) override;
};

//----------------------------------------------------------------------------
// androidAnalyticsCenter Implementation
//----------------------------------------------------------------------------

}