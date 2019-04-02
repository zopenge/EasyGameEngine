//! @file     iosPlatformTime.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Time Implementation
//----------------------------------------------------------------------------

_dword Platform::GetCurrentTickCount( )
{
	timeval time_interval;
	gettimeofday( &time_interval, _null );
	
	return EGE_TIME_TO_QWORD( time_interval );
}

_qword Platform::GetCurrentCycleCount( )
{
	return 0;
}

_qword Platform::GetSystemCycleFrequency( )
{
	return 0;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2 )
{
	return 0.0f;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2, _qword cyclefrequency )
{
	return 0.0f;
}

_ubool Platform::GetLocalTime( CalendarTime& time )
{
	return anyPlatformTime::GetLocalTime( time );
}

_ubool Platform::GetLocalTime( _time_t time, CalendarTime& calendar_time )
{
	return anyPlatformTime::GetLocalTime( time, calendar_time );
}

_time_t Platform::GetLocalTime( )
{
	return anyPlatformTime::GetLocalTime( );
}

_ubool Platform::GetSystemTime( CalendarTime& time )
{
	return anyPlatformTime::GetGMTTime( time );
}

_ubool Platform::GetSystemTime( _time_t time, CalendarTime& calendar_time )
{
	return anyPlatformTime::GetGMTTime( time, calendar_time );
}

_time_t Platform::GetSystemTime( )
{
	return anyPlatformTime::GetGMTTime( );
}

_time_t Platform::MakeTime( const CalendarTime& calendar_time )
{
	return anyPlatformTime::MakeTime( calendar_time );
}

_time_t Platform::MakeTimeM( const CalendarTime& calendar_time )
{
    return anyPlatformTime::MakeTimeM( calendar_time );
}

_ubool Platform::SystemTimeToFileTime( FileTime& filetime, const CalendarTime& systemtime )
{
	return anyPlatformTime::SystemTimeToFileTime( filetime, systemtime );
}

_ubool Platform::FileTimeToSystemTime( CalendarTime& systemtime, const FileTime& filetime )
{
	return anyPlatformTime::FileTimeToSystemTime( systemtime, filetime );
}

_ubool Platform::FileTimeToLocalFileTime( FileTime& localfiletime, const FileTime& filetime )
{
	return anyPlatformTime::FileTimeToLocalFileTime( localfiletime, filetime );
}

_ubool Platform::LocalFileTimeToFileTime( FileTime& filetime, const FileTime& localfiletime )
{
	return anyPlatformTime::LocalFileTimeToFileTime( filetime, localfiletime );
}