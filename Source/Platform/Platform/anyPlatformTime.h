//! @file     anyPlatformTime.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// anyPlatformTime
//----------------------------------------------------------------------------

class anyPlatformTime
{
public:
	static _ubool GetLocalTime( CalendarTime& raw_time );
	static _ubool GetLocalTime( _time_t raw_time, CalendarTime& calendar_time );
	static _time_t GetLocalTime( );

	static _ubool GetGMTTime( CalendarTime& calendar_time );
	static _ubool GetGMTTime( _time_t raw_time, CalendarTime& calendar_time );
	static _time_t GetGMTTime( );

	static _time_t MakeTime( const CalendarTime& calendar_time );
	static _time_t MakeTimeM( const CalendarTime& calendar_time );

	static _ubool SystemTimeToFileTime( FileTime& filetime, const CalendarTime& systemtime );
	static _ubool FileTimeToSystemTime( CalendarTime& systemtime, const FileTime& filetime );

	static _ubool FileTimeToLocalFileTime( FileTime& localfiletime, const FileTime& filetime );
	static _ubool LocalFileTimeToFileTime( FileTime& filetime, const FileTime& localfiletime );
};

//----------------------------------------------------------------------------
// anyPlatformTime Implementation
//----------------------------------------------------------------------------


}