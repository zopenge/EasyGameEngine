#pragma once

namespace EGE {

/// <summary>
/// The seek flag.
/// </summary>
enum class Seek {
	/// <summary>
	/// Seek from beginning.
	/// </summary>
	Begin,
	/// <summary>
	/// Seek from current position.
	/// </summary>
	Current,
	/// <summary>
	/// Seek from end plus "offset".
	/// </summary>
	End,
};

/// <summary>
/// The encode type.
/// </summary>
enum class Encoding {
	/// <summary>
	/// Unknown encoding.
	/// </summary>
	Unknown,
	/// <summary>
	/// ANSI encoding.
	/// </summary>
	Ansi,
	/// <summary>
	/// UTF-8 encoding.
	/// </summary>
	Utf8,
	/// <summary>
	/// UTF-16 encoding.
	/// </summary>
	Utf16,
};

/// <summary>
/// The endian type.
/// </summary>
enum class Endian {
	/// <summary>
	/// Unknown endian.
	/// </summary>
	Unknown,
	/// <summary>
	/// Little endian.
	/// </summary>
	Little,
	/// <summary>
	/// Big endian.
	/// </summary>
	Big,
};

/// <summary>
/// The mouse button type.
/// </summary>
enum class MouseButton {
	/// <summary>
	/// The left button.
	/// </summary>
	Left,
	/// <summary>
	/// The middle button.
	/// </summary>
	Middle,
	/// <summary>
	/// The right button.
	/// </summary>
	Right,
};

/// <summary>
/// The file attributes.
/// </summary>
enum class FileAttribute {
	/// <summary>
	/// It's directory.
	/// </summary>
	Directory = 1 << 0,
	/// <summary>
	/// It's hidden item.
	/// </summary>
	Hidden = 1 << 1,
};

/// <summary>
///	The callback frame data.
/// </summary>
struct CallStackFrameData {
	_dword mLineNumber;
	_chara* mFuncName;
	_chara* mFileName;

	CallStackFrameData() {
		mLineNumber = 0;
		mFuncName = _null;
		mFileName = _null;
	}
};

/// <summary>
/// The calendar time format.
/// </summary>
struct CalendarTime {
	_word mYear;
	_word mMonth;
	/// <summary>
	/// Sunday: 0
	/// Monday: 1
	/// Tuesday: 2
	/// Wednesday: 3
	/// Thursday: 4
	/// Friday: 5
	/// Saturday: 6
	/// </summary>
	_word mDayOfWeek;
	_word mDayOfMonth;
	_word mHour;
	_word mMinute;
	_word mSecond;
	_word mMilliseconds;

	_ubool operator==(const CalendarTime& time) const {
		return mYear == time.mYear && mMonth == time.mMonth && mDayOfMonth == time.mDayOfMonth && mHour == time.mHour &&
		       mMinute == time.mMinute && mSecond == time.mSecond && mMilliseconds == time.mMilliseconds;
	}

	_ubool operator!=(const CalendarTime& time) const {
		return mYear != time.mYear || mMonth != time.mMonth || mDayOfMonth != time.mDayOfMonth || mHour != time.mHour ||
		       mMinute != time.mMinute || mSecond != time.mSecond || mMilliseconds != time.mMilliseconds;
	}

	_ubool operator>(const CalendarTime& time) const {
		EGE_COMPARE_BIG(mYear, time.mYear);
		EGE_COMPARE_BIG(mMonth, time.mMonth);
		EGE_COMPARE_BIG(mDayOfMonth, time.mDayOfMonth);
		EGE_COMPARE_BIG(mHour, time.mHour);
		EGE_COMPARE_BIG(mMinute, time.mMinute);
		EGE_COMPARE_BIG(mSecond, time.mSecond);
		EGE_COMPARE_BIG(mMilliseconds, time.mMilliseconds);

		return _false;
	}

	_ubool operator<(const CalendarTime& time) const {
		EGE_COMPARE_LESS(mYear, time.mYear);
		EGE_COMPARE_LESS(mMonth, time.mMonth);
		EGE_COMPARE_LESS(mDayOfMonth, time.mDayOfMonth);
		EGE_COMPARE_LESS(mHour, time.mHour);
		EGE_COMPARE_LESS(mMinute, time.mMinute);
		EGE_COMPARE_LESS(mSecond, time.mSecond);
		EGE_COMPARE_LESS(mMilliseconds, time.mMilliseconds);

		return _false;
	}

	_ubool operator>=(const CalendarTime& time) const {
		EGE_COMPARE_BIG(mYear, time.mYear);
		EGE_COMPARE_BIG(mMonth, time.mMonth);
		EGE_COMPARE_BIG(mDayOfMonth, time.mDayOfMonth);
		EGE_COMPARE_BIG(mHour, time.mHour);
		EGE_COMPARE_BIG(mMinute, time.mMinute);
		EGE_COMPARE_BIG(mSecond, time.mSecond);
		EGE_COMPARE_BIG(mMilliseconds, time.mMilliseconds);

		return _true;
	}

	_ubool operator<=(const CalendarTime& time) const {
		EGE_COMPARE_LESS(mYear, time.mYear);
		EGE_COMPARE_LESS(mMonth, time.mMonth);
		EGE_COMPARE_LESS(mDayOfMonth, time.mDayOfMonth);
		EGE_COMPARE_LESS(mHour, time.mHour);
		EGE_COMPARE_LESS(mMinute, time.mMinute);
		EGE_COMPARE_LESS(mSecond, time.mSecond);
		EGE_COMPARE_LESS(mMilliseconds, time.mMilliseconds);

		return _true;
	}

	CalendarTime() {
		mYear = 0;
		mMonth = 0;
		mDayOfWeek = 0;
		mDayOfMonth = 0;
		mHour = 0;
		mMinute = 0;
		mSecond = 0;
		mMilliseconds = 0;
	}
};

/// <summary>
/// The file time format.
/// </summary>
struct FileTime {
	_dword mLowDateTime;
	_dword mHighDateTime;

	//!	Convert to 64 bits value.
	operator _qword() const {
		return (((_qword)mHighDateTime) << 32) | mLowDateTime;
	}

	FileTime() {
		mLowDateTime = 0;
		mHighDateTime = 0;
	}
	FileTime(_qword time) {
		mLowDateTime = (_dword)(time & 0xFFFFFFFF);
		mHighDateTime = (_dword)(time >> 32);
	}
};

/// <summary>
/// The OS file finder data.
/// </summary>
struct FileFinderData {
	//!	The file attributes, @see FileAttribute
	_dword mFileAttributes;
	//!	The file time info
	FileTime mCreationTime;
	FileTime mLastAccessTime;
	FileTime mLastWriteTime;
	//!	The file size
	_qword mFileSize;
	//!	The file name
	_charw mFileName[260];
	//!	The alternative name for the file.
	_charw mAlternateFileName[14];

	FileFinderData() {
		mFileAttributes = 0;
		mFileSize = 0;
		mFileName[0] = 0;
		mAlternateFileName[0] = 0;
	}
};

/// <summary>
/// The performance data
/// </summary>
struct PerformanceData {
	// IO
	_qword mFileOpenCount;
	_qword mFileReadCount;
	_qword mFileReadBytes;
	_qword mFileWriteCount;
	_qword mFileWriteBytes;

	PerformanceData() {
		mFileOpenCount = 0;
		mFileReadCount = 0;
		mFileReadBytes = 0;
		mFileWriteCount = 0;
		mFileWriteBytes = 0;
	}
};

} // namespace EGE