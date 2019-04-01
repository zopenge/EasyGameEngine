//! @file     Time.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Time Time::cNull;

//----------------------------------------------------------------------------
// Time Helpful Functions Implementation
//----------------------------------------------------------------------------

//! Convert day string to integer.
static _dword GetDayOfWeek(AStringPtr string) {
	if (string == "Sun")
		return 7;
	if (string == "Mon")
		return 1;
	if (string == "Tue")
		return 2;
	if (string == "Wed")
		return 3;
	if (string == "Thu")
		return 4;
	if (string == "Fri")
		return 5;
	if (string == "Sat")
		return 6;

	return 0;
}

//! Convert month string to integer.
static _dword GetMonth(AStringPtr string) {
	if (string == "Jan")
		return 1;
	if (string == "Feb")
		return 2;
	if (string == "Mar")
		return 3;
	if (string == "Apr")
		return 4;
	if (string == "May")
		return 5;
	if (string == "Jun")
		return 6;
	if (string == "Jul")
		return 7;
	if (string == "Aug")
		return 8;
	if (string == "Sep")
		return 9;
	if (string == "Oct")
		return 10;
	if (string == "Nov")
		return 11;
	if (string == "Dec")
		return 12;

	return 0;
}

//----------------------------------------------------------------------------
// Time Implementation
//----------------------------------------------------------------------------

Time::Time() {
}

Time::Time(_time_t time) {
	*this = GetTimeFrom1970(time);
}

Time::Time(const FileTime& time) {
	Platform::FileTimeToSystemTime(*this, time);
}

Time::Time(const CalendarTime& time) {
	*this = time;
}

Time::Time(UStringPtr string) {
	// The string format is "YYYY/MM/DD HH::MM::SS(MMMM)"
	StringFormatter::ParseString(string.CStr(), "%d/%d/%d %d:%d:%d(%d)",
	                             mYear, mMonth, mDayOfMonth, mHour, mMinute, mSecond, mMilliseconds);
}

Time::Time(WStringPtr string) {
	// The string format is "YYYY/MM/DD HH::MM::SS(MMMM)"
	StringFormatter::ParseString(string.CStr(), L"%d/%d/%d %d:%d:%d(%d)",
	                             mYear, mMonth, mDayOfMonth, mHour, mMinute, mSecond, mMilliseconds);
}

Time& Time::operator=(const FileTime& time) {
	Platform::FileTimeToSystemTime(*this, time);

	return *this;
}

Time& Time::operator=(const CalendarTime& time) {
	mYear = time.mYear;
	mMonth = time.mMonth;
	mDayOfWeek = time.mDayOfWeek;
	mDayOfMonth = time.mDayOfMonth;
	mHour = time.mHour;
	mMinute = time.mMinute;
	mSecond = time.mSecond;
	mMilliseconds = time.mMilliseconds;

	return *this;
}

Time& Time::operator=(UStringPtr string) {
	// The string format is "YYYY/MM/DD HH::MM::SS(MMMM)"
	StringFormatter::ParseString(string.CStr(), "%d/%d/%d %d:%d:%d(%d)",
	                             mYear, mMonth, mDayOfMonth, mHour, mMinute, mSecond, mMilliseconds);

	return *this;
}

Time& Time::operator=(WStringPtr string) {
	// The string format is "YYYY/MM/DD HH::MM::SS(MMMM)"
	StringFormatter::ParseString(string.CStr(), L"%d/%d/%d %d:%d:%d(%d)",
	                             mYear, mMonth, mDayOfMonth, mHour, mMinute, mSecond, mMilliseconds);

	return *this;
}

FileTime Time::ToFileTime() const {
	FileTime file_time;
	if (Platform::SystemTimeToFileTime(file_time, *this))
		return FileTime(0);

	return file_time;
}

_time_t Time::ToSecondsOfDay() const {
	return mSecond + mMinute * 60 + mHour * 3600;
}

_time_t Time::ToSecondsFrom1970() const {
	return Platform::MakeTime(*this);
}

AString Time::ToAString(_dword format) const {
	_chara buffer[1024];
	buffer[0] = 0;
	return AString(ToAString(buffer, 1024, format));
}

_chara* Time::ToAString(_chara* buffer, _dword length, _dword format) const {
	_charw buffer_unicode[1024];
	buffer_unicode[0] = 0;
	ToWString(buffer_unicode, 1024, format);

	Platform::Utf16ToAnsi(buffer, length, buffer_unicode);

	return buffer;
}

WString Time::ToWString(_dword format) const {
	_charw buffer[1024];
	return WString(ToWString(buffer, 1024, format));
}

_charw* Time::ToWString(_charw* buffer, _dword length, _dword format) const {
	buffer[0] = 0;

	// "YYYY/MM/DD"
	if (format & _FORMAT_WITH_DAY) {
		Platform::AppendString(buffer, FORMAT_WSTRING_3(L"%.4d/%.2d/%.2d", mYear, mMonth, mDayOfMonth));
	}

	// "HH::MM::SS"
	if (format & _FORMAT_WITH_TIME) {
		// Add a split character when day info
		if (format & _FORMAT_WITH_DAY)
			Platform::AppendString(buffer, L" ");

		Platform::AppendString(buffer, FORMAT_WSTRING_3(L"%.2d:%.2d:%.2d", mHour, mMinute, mSecond));
	}

	// "(MMMM)"
	if (format & _FORMAT_WITH_TIME_MS) {
		Platform::AppendString(buffer, FORMAT_WSTRING_1(L"(%.3d)", mMilliseconds));
	}

	return buffer;
}

Time Time::GetCurrentLocalTime() {
	CalendarTime calendar_time;
	Platform::GetLocalTime(calendar_time);

	return Time(calendar_time);
}

_time_t Time::GetCurrentLocalTimeStamp() {
	return Platform::MakeTimeM(GetCurrentLocalTime());
}

Time Time::GetCurrentSystemTime() {
	CalendarTime calendar_time;
	Platform::GetSystemTime(calendar_time);

	return Time(calendar_time);
}

_time_t Time::GetCurrentSystemTimeStamp() {
	return Platform::MakeTimeM(GetCurrentSystemTime());
}

Time Time::GetTimeFrom1970(_time_t seconds) {
	CalendarTime calendar_time;
	Platform::GetLocalTime(seconds, calendar_time);

	return calendar_time;
}

Time Time::GetTimeFromHTTPGMTTimeFormat(AStringPtr string) {
	WString tag_name;
	_word day, year, hour, minute, second;
	AString week, mon;
	StringFormatter::ParseString(string.CStr(), "%s: %s, %d %s %d %d:%d:%d GMT", tag_name, week, day, mon, year, hour, minute, second);

	Time time;
	time.mYear = year;
	time.mMonth = (_word)GetMonth(mon);
	time.mDayOfWeek = (_word)GetDayOfWeek(week);
	time.mDayOfMonth = day;
	time.mHour = hour;
	time.mMinute = minute;
	time.mSecond = second;
	time.mMilliseconds = 0;

	return time;
}

Time Time::GetTimeFromHTTPGMTTimeFormat(WStringPtr string) {
	return GetTimeFromHTTPGMTTimeFormat(AString().FromString(string));
}

_time_t Time::GetStartTimeOfDay(_time_t time) {
	// Get the current local time by time value
	CalendarTime calendar_time = GetTimeFrom1970(time);

	// Get the time value without hours, minutes and seconds ( milliseconds )
	calendar_time.mHour = time <= 8 * 3600 ? 8 : 0;
	calendar_time.mMinute = 0;
	calendar_time.mSecond = 0;
	calendar_time.mMilliseconds = 0;
	return Platform::MakeTime(calendar_time);
}

_time_t Time::GetStartTimeOfMonth(_time_t time) {
	// Get the current local time by time value
	CalendarTime calendar_time = GetTimeFrom1970(time);

	// Get the time value without hours, minutes and seconds ( milliseconds )
	calendar_time.mHour = time <= 8 * 3600 ? 8 : 0;
	calendar_time.mMinute = 0;
	calendar_time.mSecond = 0;
	calendar_time.mMilliseconds = 0;
	Platform::MakeTime(calendar_time);

	// Sunday is '0' index, but we will use Monday as start day of week, so make Sunday as last week by decrease 1
	calendar_time.mDayOfWeek--;
	if (calendar_time.mDayOfWeek < 0)
		calendar_time.mDayOfWeek += 7; // The Monday of last week

	// Make the time value at Monday of week as start time
	time -= _ONE_DAY_SECONDS * calendar_time.mDayOfWeek;
	if (time < 0)
		time = 0;

	return time;
}

_time_t Time::MakeDateTime(_dword year, _dword month, _dword day) {
	CalendarTime calendar_time;
	calendar_time.mYear = (_word)year;
	calendar_time.mMonth = (_word)month;
	calendar_time.mDayOfMonth = (_word)day;

	return Platform::MakeTime(calendar_time);
}

_dword Time::GetStartDayOfWeek(_dword year, _dword month, _dword day) {
	EGE_ASSERT(month <= 12);
	EGE_ASSERT(day <= 31);

	_dword a = (_dword)(floor((14 - month) / 12.f));
	_dword y = year - a;
	_dword m = month + 12 * a - 2;
	_dword d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	return d;
}

_dword Time::GetNumDaysOfMonth(_dword year, _dword month) {
	_dword num_of_days = 0;

	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {
		num_of_days = 31;
	} break;

	case 2: {
		if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0)
			num_of_days = 29;
		else
			num_of_days = 28;
	} break;

	case 4:
	case 6:
	case 9:
	case 11: {
		num_of_days = 30;
	} break;

	default:
		EGE_ASSERT(0);
		break;
	}

	return num_of_days;
}

_dword Time::GetWeekDiff(_time_t time_1, _time_t time_2) {
	// Prevent for negative result
	if (time_1 < time_2)
		Math::Swap(time_1, time_2);

	// Calculate the diff in weeks
	_dword diff_in_weeks = 0;
	while (IsSameWeek(time_1, time_2) == _false) {
		diff_in_weeks++;

		// Jump to last week
		time_1 -= _ONE_WEEK_SECONDS;
	}

	return diff_in_weeks;
}

_ubool Time::IsSameDay(_time_t time_1, _time_t time_2) {
	_time_t t1 = GetStartTimeOfDay(time_1);
	_time_t t2 = GetStartTimeOfDay(time_2);

	return t1 == t2;
}

_ubool Time::IsSameDay(const Time& time_1, const Time& time_2) {
	return IsSameDay(time_1.ToSecondsFrom1970(), time_2.ToSecondsFrom1970());
}

_ubool Time::IsSameWeek(_time_t time_1, _time_t time_2) {
	// Get the bigger time value
	if (time_1 < time_2)
		Math::Swap(time_1, time_2);

	// Get the current local time by time value
	CalendarTime calendar_time = GetTimeFrom1970(time_1);

	// We get the start day of week
	_dword day = calendar_time.mDayOfWeek;
	if (calendar_time.mDayOfWeek == 0)
		day = 7; // It's Sunday

	// Get the diff time from Monday
	_time_t diff = (day - 1) * _ONE_DAY_SECONDS +
	               calendar_time.mHour * _ONE_HOUR_SECONDS +
	               calendar_time.mMinute * _ONE_MINUTE_SECONDS +
	               calendar_time.mSecond;

	return time_2 >= time_1 - diff;
}

_ubool Time::IsSameWeek(const Time& time_1, const Time& time_2) {
	return IsSameWeek(time_1.ToSecondsFrom1970(), time_2.ToSecondsFrom1970());
}

_ubool Time::IsSameMonth(_time_t time_1, _time_t time_2) {
	return GetStartTimeOfMonth(time_1) == GetStartTimeOfMonth(time_2);
}

_ubool Time::IsSameMonth(const Time& time_1, const Time& time_2) {
	return IsSameMonth(time_1.ToSecondsFrom1970(), time_2.ToSecondsFrom1970());
}
