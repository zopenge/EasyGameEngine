//! @file     winAnalyticsCenter.Flurry.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winAnalyticsCenterFlurry Implementation
//----------------------------------------------------------------------------

winAnalyticsCenterFlurry::winAnalyticsCenterFlurry( )
{
}

winAnalyticsCenterFlurry::~winAnalyticsCenterFlurry( )
{
	Finalize( );
}

_ubool winAnalyticsCenterFlurry::Initialize( UStringPtr app_id )
{
	return _true;
}

_void winAnalyticsCenterFlurry::Finalize( )
{
}

_void winAnalyticsCenterFlurry::SetUserID( UStringPtr user_id )
{
}

_void winAnalyticsCenterFlurry::SetAge( _dword age )
{
}

_void winAnalyticsCenterFlurry::SetGender( _GENDER gender )
{
}

_void winAnalyticsCenterFlurry::Enable( _ubool enable )
{
}

_void winAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
}

_void winAnalyticsCenterFlurry::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{
}

_void winAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, UStringPtr desc )
{

}
