//! @file     anyPlatformTime.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformTime Implementation
//----------------------------------------------------------------------------

_ubool anyPlatformTime::GetLocalTime(CalendarTime& calendar_time) {
  timeval time_interval;
  gettimeofday(&time_interval, _null);

  if (anyPlatformTime::GetLocalTime(time_interval.tv_sec, calendar_time) ==
      _false)
    return _false;

  calendar_time.mMilliseconds = (_word)(time_interval.tv_usec / 1000.0);

  return _true;
}

_ubool anyPlatformTime::GetLocalTime(_time_t raw_time,
                                     CalendarTime& calendar_time) {
  // Get the local time
  tm time_info;
#if defined(_PLATFORM_WINDOWS_)
  localtime_s(&time_info, &raw_time);
#elif defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_)
  localtime_r(&raw_time, &time_info);
#else
#error "Unknown platform"
#endif

  // Feedback the calendar time
  calendar_time.mSecond = time_info.tm_sec;
  calendar_time.mMinute = time_info.tm_min;
  calendar_time.mHour = time_info.tm_hour;
  calendar_time.mDayOfMonth = time_info.tm_mday;
  calendar_time.mMonth = time_info.tm_mon + 1;
  calendar_time.mYear = time_info.tm_year + 1900;
  calendar_time.mDayOfWeek = time_info.tm_wday;

  return _true;
}

_time_t anyPlatformTime::GetLocalTime() { return time(_null); }

_ubool anyPlatformTime::GetGMTTime(CalendarTime& calendar_time) {
  timeval time_interval;
  gettimeofday(&time_interval, _null);

  if (anyPlatformTime::GetGMTTime(time_interval.tv_sec, calendar_time) ==
      _false)
    return _false;

  calendar_time.mMilliseconds = (_word)(time_interval.tv_usec / 1000.0);

  return _true;
}

_ubool anyPlatformTime::GetGMTTime(_time_t raw_time,
                                   CalendarTime& calendar_time) {
  // Get the local time by time value
  tm time_info;
#if defined(_PLATFORM_WINDOWS_)
  ::gmtime_s(&time_info, (const time_t*)&raw_time);
#elif defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_)
  ::gmtime_r((const time_t*)&raw_time, &time_info);
#else
#error "Unknown platform"
#endif

  // Feedback the calendar time
  calendar_time.mSecond = time_info.tm_sec;
  calendar_time.mMinute = time_info.tm_min;
  calendar_time.mHour = time_info.tm_hour;
  calendar_time.mDayOfMonth = time_info.tm_mday;
  calendar_time.mMonth = time_info.tm_mon + 1;
  calendar_time.mYear = time_info.tm_year + 1900;
  calendar_time.mDayOfWeek = time_info.tm_wday;

  return _true;
}

_time_t anyPlatformTime::GetGMTTime() {
  _time_t raw_time = time(_null);

  tm time_info;
#if defined(_PLATFORM_WINDOWS_)
  ::gmtime_s(&time_info, (const time_t*)&raw_time);
#elif defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_)
  ::gmtime_r((const time_t*)&raw_time, &time_info);
#else
#error "Unknown platform"
#endif

  _time_t time_value = ::mktime(&time_info);
  EGE_ASSERT(time_value != -1);

  return time_value;
}

_time_t anyPlatformTime::MakeTime(const CalendarTime& calendar_time) {
  tm _time;
  _time.tm_sec = calendar_time.mSecond;
  _time.tm_min = calendar_time.mMinute;
  _time.tm_hour = calendar_time.mHour;
  _time.tm_mday = calendar_time.mDayOfMonth;
  _time.tm_mon = calendar_time.mMonth - 1;
  _time.tm_year = calendar_time.mYear - 1900;
  _time.tm_wday = calendar_time.mDayOfWeek;
  _time.tm_yday = 0;
  _time.tm_isdst = 0;

  _time_t time_value = ::mktime(&_time);
  EGE_ASSERT(time_value != -1);

  return time_value;
}

_time_t anyPlatformTime::MakeTimeM(const CalendarTime& calendar_time) {
  _time_t time_value = MakeTime(calendar_time);
  EGE_ASSERT(time_value != -1);

  return time_value * 1000 + calendar_time.mMilliseconds;
}

_ubool anyPlatformTime::SystemTimeToFileTime(FileTime& filetime,
                                             const CalendarTime& systemtime) {
  _time_t _time = MakeTime(systemtime);

  filetime = FileTime(_time);

  return _true;
}

_ubool anyPlatformTime::FileTimeToSystemTime(CalendarTime& systemtime,
                                             const FileTime& filetime) {
  _time_t _time = (_qword)filetime;

  return GetGMTTime(_time, systemtime);
}

_ubool anyPlatformTime::FileTimeToLocalFileTime(FileTime& localfiletime,
                                                const FileTime& filetime) {
  _time_t file_time = (_qword)filetime;

  localfiletime = FileTime(file_time - 8 * 3600);

  return _true;
}

_ubool anyPlatformTime::LocalFileTimeToFileTime(FileTime& filetime,
                                                const FileTime& localfiletime) {
  filetime = FileTime(localfiletime + 8 * 3600);

  return _true;
}
