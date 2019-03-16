//! @file     iosAnalyticsCenterFlurry.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosAnalyticsCenterFlurry
//----------------------------------------------------------------------------

class iosAnalyticsCenterFlurry : public TObject< IAnalyticsCenter >
{
public:
	iosAnalyticsCenterFlurry( UStringPtr app_key );
	virtual ~iosAnalyticsCenterFlurry( );
private:
	UString		mAppKey;
public:
	virtual _void SetUserID( UStringPtr user_id ) override;
	virtual _void SetAge( _dword age ) override;
	virtual _void SetGender( _GENDER gender ) override;
	virtual _void Enable( _ubool enable ) override;
	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) override;
    virtual _void LogEvent( UStringPtr event_id, UStringPtr desc ) override;
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) override;
};

}
