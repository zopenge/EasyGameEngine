//! @file     androidPlatformTime.cpp
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
	
	return (_qword)( time_interval.tv_sec * 1000.0 + ( time_interval.tv_usec / 1000.0 ) ) & 0x00000000FFFFFFFFLL;
}

_qword Platform::GetCurrentCycleCount( )
{
	timeval time_interval;
	gettimeofday( &time_interval, _null );

	return (_qword)( time_interval.tv_sec * 1000000.0 + time_interval.tv_usec );
}

_qword Platform::GetSystemCycleFrequency( )
{
	return 1000000;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2 )
{
	return (_float) ( cyclecount2 - cyclecount1 ) / 1000.0f;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2, _qword cyclefrequency )
{
	return (_float) ( cyclecount2 - cyclecount1 ) / cyclefrequency * 1000.0f;
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