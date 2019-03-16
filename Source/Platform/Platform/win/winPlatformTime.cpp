//! @file     winPlatformTime.cpp
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
 return ::timeGetTime( );
}

_qword Platform::GetCurrentCycleCount( )
{
 _qword cyclecount = 0;
 ::QueryPerformanceCounter( (LARGE_INTEGER*) &cyclecount );

 return cyclecount;
}

_qword Platform::GetSystemCycleFrequency( )
{
 _qword cyclefrequency = 0;
 ::QueryPerformanceFrequency( (LARGE_INTEGER*) &cyclefrequency );

 return cyclefrequency;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2 )
{
 _qword cyclefrequency = 0;
 ::QueryPerformanceFrequency( (LARGE_INTEGER*) &cyclefrequency );

 if ( cyclefrequency == 0 )
  return 0.0f;

 return (_float) ( cyclecount2 - cyclecount1 ) / (_float) cyclefrequency * 1000.0f;
}

_float Platform::GetElapseTime( _qword cyclecount1, _qword cyclecount2, _qword cyclefrequency )
{
 if ( cyclefrequency == 0 )
  return 0.0f;

 return (_float) ( cyclecount2 - cyclecount1 ) / (_float) cyclefrequency * 1000.0f;
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
 return EGE_BOOLEAN( ::SystemTimeToFileTime( (const ::SYSTEMTIME*) &systemtime, (::FILETIME*) &filetime ) );
}

_ubool Platform::FileTimeToSystemTime( CalendarTime& systemtime, const FileTime& filetime )
{
 return EGE_BOOLEAN( ::FileTimeToSystemTime( (const ::FILETIME*) &filetime, (::SYSTEMTIME*) &systemtime ) );
}

_ubool Platform::FileTimeToLocalFileTime( FileTime& localfiletime, const FileTime& filetime )
{
 return EGE_BOOLEAN( ::FileTimeToLocalFileTime( (const ::FILETIME*) &filetime, (::FILETIME*) &localfiletime ) );
}

_ubool Platform::LocalFileTimeToFileTime( FileTime& filetime, const FileTime& localfiletime )
{
 return EGE_BOOLEAN( ::LocalFileTimeToFileTime( (const ::FILETIME*) &localfiletime, (::FILETIME*) &filetime ) );
}