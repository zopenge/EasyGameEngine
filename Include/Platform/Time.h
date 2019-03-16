//! @file     Time.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Time
//----------------------------------------------------------------------------

class Time : public CalendarTime
{
public:
	//! The null time
	static const Time cNull;

public:
	//!	The useful constant info
	enum 
	{
		//! The hours number in one day 
		_ONE_DAY_HOURS			= 24, 
		//! The seconds number in one minute
		_ONE_MINUTE_SECONDS		= 60, 
		//! The seconds number in one hour
		_ONE_HOUR_SECONDS		= _ONE_MINUTE_SECONDS * 60, 
		//! The seconds number in one day
		_ONE_DAY_SECONDS		= _ONE_DAY_HOURS * _ONE_HOUR_SECONDS, 
		//! The seconds number in one week
		_ONE_WEEK_SECONDS		= _ONE_DAY_SECONDS * 7,

		//!	The hour in zero time
		_HOUR_AT_ZERO_TIME		= 8,
		//!	The minute in zero time
		_MINUTE_AT_ZERO_TIME	= 0,
		//!	The second in zero time
		_SECOND_AT_ZERO_TIME	= 0,

		//!	The number of seconds elapsed since zero time
		_SECOND_SINCE_ZERO_TIME	= _HOUR_AT_ZERO_TIME * _ONE_HOUR_SECONDS,
	};

	//!	The time format type
	enum _FORMAT
	{
		_FORMAT_WITH_DAY		= 1 << 0, // "YYYY/MM/DD"
		_FORMAT_WITH_TIME		= 1 << 1, // "HH::MM::SS"
		_FORMAT_WITH_TIME_MS	= 1 << 2, // "(MMMM)"
		_FORMAT_WITH_ALL		= _FORMAT_WITH_DAY | _FORMAT_WITH_TIME | _FORMAT_WITH_TIME_MS, // "YYYY/MM/DD HH::MM::SS(MMMM)"
	};

public:
	Time( );
	Time( _time_t time );
	Time( const FileTime& time );
	Time( const CalendarTime& time );
	Time( UStringPtr string );
	Time( WStringPtr string );

public:
	//!	Assign functions.
	Time& operator = ( const FileTime& time );
	Time& operator = ( const CalendarTime& time );
	Time& operator = ( UStringPtr string );
	Time& operator = ( WStringPtr string );

public:
	//!	Convert to file time.
	//!	@param		none.
	//!	@return		The file time.
	FileTime ToFileTime( ) const;
	//!	Convert to elapsed seconds of day.
	//!	@param		none.
	//!	@return		The seconds.
	_time_t ToSecondsOfDay( ) const;
	//!	Convert to elapsed seconds from 1970.
	//!	@param		none.
	//!	@return		The seconds.
	_time_t ToSecondsFrom1970( ) const;

	//! Convert to string as specified format by flag in ANSI mode.
	//!	@param		format		The time format.
	//!	@return		The time string.
	AString ToAString( _dword format = _FORMAT_WITH_ALL ) const;
	//! Convert to string as specified format by flag in ANSI mode.
	//!	@param		buffer		The string buffer.
	//!	@param		length		The string buffer length.
	//!	@param		format		The time format.
	//!	@return		The time string.
	_chara* ToAString( _chara* buffer, _dword length, _dword format = _FORMAT_WITH_ALL ) const;
	//! Convert to string as specified format by flag in UNICODE mode.
	//!	@param		format		The time format.
	//!	@return		The time string.
	WString ToWString( _dword format = _FORMAT_WITH_ALL ) const;
	//! Convert to string as specified format by flag in UNICODE mode.
	//!	@param		buffer		The string buffer.
	//!	@param		length		The string buffer length.
	//!	@param		format		The time format.
	//!	@return		The time string.
	_charw* ToWString( _charw* buffer, _dword length, _dword format = _FORMAT_WITH_ALL ) const;

public:
	//!	Get the current local time.
	//!	@param		none.
	//!	@return		The current local time.
	static Time GetCurrentLocalTime( );
	//!	Get the current local time stamp.
	//!	@param		none.
	//!	@return		The current local time stamp.
	static _time_t GetCurrentLocalTimeStamp( );
	//!	Get the current system time.
	//!	@param		none.
	//!	@return		The current system time.
	static Time GetCurrentSystemTime( );
	//!	Get the current system time stamp.
	//!	@param		none.
	//!	@return		The current system time stamp.
	static _time_t GetCurrentSystemTimeStamp( );

	//!	Get the time from 1970.
	//!	@param		seconds	The elapsed seconds from 1970.
	//!	@return		The time.
	static Time GetTimeFrom1970( _time_t seconds );

	//!	Get time from HTTP GMT time format.
	//!	@remark		The HTTP GMT time format is : (e.g.) Date: Fri, 31 Dec 1999 23:59:59 GMT
	//!	@param		string		The string.
	//!	@return		The time.
	static Time GetTimeFromHTTPGMTTimeFormat( AStringPtr string );
	//!	Get time from HTTP GMT time format.
	//!	@remark		The HTTP GMT time format is : (e.g.) Date: Fri, 31 Dec 1999 23:59:59 GMT
	//!	@param		string		The string.
	//!	@return		The time.
	static Time GetTimeFromHTTPGMTTimeFormat( WStringPtr string );

	//!	Get the start time (00:00) of day.
	//!	@param		time	The time value.
	//!	@return		The time in seconds since zero time.
	static _time_t GetStartTimeOfDay( _time_t time );
	//!	Get the start time (1st,00:00) of month.
	//!	@param		time	The time value.
	//!	@return		The time in seconds since zero time.
	static _time_t GetStartTimeOfMonth( _time_t time );

	//!	Make the date time.
	//!	@param		year	The year.
	//!	@param		month	The month of year.
	//!	@param		day		The day of month.
	//!	@return		The time in seconds since zero time.
	static _time_t MakeDateTime( _dword year, _dword month, _dword day );

	//!	Get the start day (Sunday: 0, Monday: 1 ... Saturday: 7 ) of week.
	//!	@param		year	The year.
	//!	@param		month	The month of year.
	//!	@param		day		The day of month.
	//!	@return		The start day of week.
	static _dword GetStartDayOfWeek( _dword year, _dword month, _dword day );

	//!	Get the total days number of month.
	//!	@param		year	The year.
	//!	@param		month	The month of year.
	//!	@return		The total days number of month.
	static _dword GetNumDaysOfMonth( _dword year, _dword month );

	//!	Get the diff number in weeks.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		The diff number in weeks.
	static _dword GetWeekDiff( _time_t time_1, _time_t time_2 );

	//!	Check whether it's same day.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same day.
	static _ubool IsSameDay( _time_t time_1, _time_t time_2 );
	//!	Check whether it's same day.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same day.
	static _ubool IsSameDay( const Time& time_1, const Time& time_2 );

	//!	Check whether it's same week.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same week.
	static _ubool IsSameWeek( _time_t time_1, _time_t time_2 );
	//!	Check whether it's same week.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same week.
	static _ubool IsSameWeek( const Time& time_1, const Time& time_2 );

	//!	Check whether it's same month.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same month.
	static _ubool IsSameMonth( _time_t time_1, _time_t time_2 );
	//!	Check whether it's same week.
	//!	@param		time_1	The first time value.
	//!	@param		time_2	The second time value.
	//!	@return		True indicates it's same week.
	static _ubool IsSameMonth( const Time& time_1, const Time& time_2 );
};

}