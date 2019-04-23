#pragma once

namespace EGE {

/// <summary>
/// The base event data.
/// </summary>
struct BaseEventData {
	//!	True indicates to stop event propagation.
	_ubool mStopPropagation;

	BaseEventData() {
		mStopPropagation = false;
	}
};

/// <summary>
/// The (OS, Operation System) data.
/// </summary>
struct OSData {
	const _charw* mName;
	_dword mMinor;
	_dword mMajor;

	OSData() {
		mName = _null;
		mMinor = 0;
		mMajor = 0;
	}
};

/// <summary>
/// The CPU data.
/// </summary>
struct CPUData {
	const _charw* mFamilyName;
	_dword mNumber;
	_dword mFeatures;

	CPUData() {
		mFamilyName = _null;
		mNumber = 0;
		mFeatures = 0;
	}
};

/// <summary>
/// The GPU data.
/// </summary>
struct GPUData {
	const _charw* mFamilyName;

	GPUData() {
		mFamilyName = _null;
	}
};

/// /// <summary>
/// The symbol file data.
/// </summary>
struct SymbolFileData {
	_dword mAddress;
	_dword mLineNumber;
	_chara mFileName[256];

	SymbolFileData() {
		mAddress = 0;
		mLineNumber = 0;
		mFileName[0] = 0;
	}
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
/// The detail of file or directory data
/// </summary>
struct FileData {
	//! The enumeration depth
	_dword mDepth;
	//! The number of items found so far.
	_dword mItemNumber;

	//! The relative path
	WString mRelativePath;
	//! The absolute path
	WString mAbsolutePath;
	//! The file name
	WString mFileName;

	//! The file size
	_qword mSize;
	//! The file attributes, @see _FILE_ATTRIBUTE
	_dword mAttributes;
	//! The last write time
	_qword mLastWriteTime;

	FileData()
	    : mDepth(0), mItemNumber(0), mSize(0), mAttributes(0), mLastWriteTime(0) {
	}
};
typedef Array<FileData> FileDataArray;

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