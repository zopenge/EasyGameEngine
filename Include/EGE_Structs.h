//! @file     EGE_Structs.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Globals enumerations and structure
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CalendarTime
//----------------------------------------------------------------------------

//! The calendar time format
struct CalendarTime
{
	_word	mYear;
	_word	mMonth;
	// Sunday		0,
	// Monday		1,
	// Tuesday		2,
	// Wednesday	3,
	// Thursday		4,
	// Friday		5,
	// Saturday		6,
	_word	mDayOfWeek;
	_word	mDayOfMonth;
	_word	mHour;
	_word	mMinute;
	_word	mSecond;
	_word	mMilliseconds;

	_ubool operator == ( const CalendarTime& time ) const
	{
		return mYear == time.mYear && mMonth == time.mMonth && mDayOfMonth == time.mDayOfMonth && mHour == time.mHour &&
			mMinute == time.mMinute && mSecond == time.mSecond && mMilliseconds == time.mMilliseconds;
	}

	_ubool operator != ( const CalendarTime& time ) const
	{
		return mYear != time.mYear || mMonth != time.mMonth || mDayOfMonth != time.mDayOfMonth || mHour != time.mHour ||
			mMinute != time.mMinute || mSecond != time.mSecond || mMilliseconds != time.mMilliseconds;
	}

	_ubool operator > ( const CalendarTime& time ) const
	{
		EGE_CHECK_COMP_BIG( mYear, time.mYear );
		EGE_CHECK_COMP_BIG( mMonth, time.mMonth );
		EGE_CHECK_COMP_BIG( mDayOfMonth, time.mDayOfMonth );
		EGE_CHECK_COMP_BIG( mHour, time.mHour );
		EGE_CHECK_COMP_BIG( mMinute, time.mMinute );
		EGE_CHECK_COMP_BIG( mSecond, time.mSecond );
		EGE_CHECK_COMP_BIG( mMilliseconds, time.mMilliseconds );

		return _false;
	}

	_ubool operator < ( const CalendarTime& time ) const
	{
		EGE_CHECK_COMP_LESS( mYear, time.mYear );
		EGE_CHECK_COMP_LESS( mMonth, time.mMonth );
		EGE_CHECK_COMP_LESS( mDayOfMonth, time.mDayOfMonth );
		EGE_CHECK_COMP_LESS( mHour, time.mHour );
		EGE_CHECK_COMP_LESS( mMinute, time.mMinute );
		EGE_CHECK_COMP_LESS( mSecond, time.mSecond );
		EGE_CHECK_COMP_LESS( mMilliseconds, time.mMilliseconds );

		return _false;
	}

	_ubool operator >= ( const CalendarTime& time ) const
	{
		EGE_CHECK_COMP_BIG( mYear, time.mYear );
		EGE_CHECK_COMP_BIG( mMonth, time.mMonth );
		EGE_CHECK_COMP_BIG( mDayOfMonth, time.mDayOfMonth );
		EGE_CHECK_COMP_BIG( mHour, time.mHour );
		EGE_CHECK_COMP_BIG( mMinute, time.mMinute );
		EGE_CHECK_COMP_BIG( mSecond, time.mSecond );
		EGE_CHECK_COMP_BIG( mMilliseconds, time.mMilliseconds );

		return _true;
	}

	_ubool operator <= ( const CalendarTime& time ) const
	{
		EGE_CHECK_COMP_LESS( mYear, time.mYear );
		EGE_CHECK_COMP_LESS( mMonth, time.mMonth );
		EGE_CHECK_COMP_LESS( mDayOfMonth, time.mDayOfMonth );
		EGE_CHECK_COMP_LESS( mHour, time.mHour );
		EGE_CHECK_COMP_LESS( mMinute, time.mMinute );
		EGE_CHECK_COMP_LESS( mSecond, time.mSecond );
		EGE_CHECK_COMP_LESS( mMilliseconds, time.mMilliseconds );

		return _true;
	}

	CalendarTime( )
	{
		mYear			= 0;
		mMonth			= 0;
		mDayOfWeek		= 0;
		mDayOfMonth		= 0;
		mHour			= 0;
		mMinute			= 0;
		mSecond			= 0;
		mMilliseconds	= 0;
	}
};

//----------------------------------------------------------------------------
// FileTime
//----------------------------------------------------------------------------

// The file time format
struct FileTime
{
	_dword	mLowDateTime;
	_dword	mHighDateTime;

	//!	Convert to 64 bits value.
	operator _qword( ) const
	{
		return ( ((_qword) mHighDateTime) << 32 ) | mLowDateTime;
	}

	FileTime( )
	{
		mLowDateTime	= 0;
		mHighDateTime	= 0;
	}
	FileTime( _qword time )
	{
		mLowDateTime	= (_dword)(time & 0xFFFFFFFF);
		mHighDateTime	= (_dword)(time >> 32);
	}
};

//----------------------------------------------------------------------------
// FileFinderData
//----------------------------------------------------------------------------

//!	The OS file finder data
struct FileFinderData
{
	//!	The file attributes, @see _FILE_ATTRIBUTE
	_dword		mFileAttributes;
	//!	The file time info
	FileTime 	mCreationTime;
	FileTime 	mLastAccessTime;
	FileTime 	mLastWriteTime;
	//!	The file size
	_qword 		mFileSize;
	//!	The file name
	_charw 		mFileName[ 260 ];
	//!	The alternative name for the file.
	_charw 		mAlternateFileName[ 14 ];

	FileFinderData( )
	{
		mFileAttributes			= 0;
		mFileSize				= 0;
		mFileName[0]			= 0;
		mAlternateFileName[0]	= 0;
	}
};

//----------------------------------------------------------------------------
// IOPerformanceInfo
//----------------------------------------------------------------------------

//!	The IO performance info
struct IOPerformanceInfo
{
	_qword	mFileOpenCount;
	_qword	mFileReadCount;
	_qword	mFileReadBytes;
	_qword	mFileWriteCount;
	_qword	mFileWriteBytes;

	IOPerformanceInfo( )
	{
		mFileOpenCount	= 0;
		mFileReadCount	= 0;
		mFileReadBytes	= 0;
		mFileWriteCount	= 0;
		mFileWriteBytes	= 0;
	}
};

//----------------------------------------------------------------------------
// ThirdPersonCamera
//----------------------------------------------------------------------------

struct ThirdPersonCamera
{
	_float		mTargetX;
	_float		mTargetY;
	_float		mZOffset;
	_float		mRotation;
	_float		mAoA;
	_float		mRange;
	_float		mRoll;
	_float		mFOV;

	ThirdPersonCamera( )
		: mTargetX( 0.0f )
		, mTargetY( 0.0f )
		, mZOffset( 0.0f )
		, mRotation( 0.0f )
		, mAoA( 0.0f )
		, mRange( 100.0f )
		, mRoll( 0.0f )
		, mFOV( 58.0f )
	{

	}
	ThirdPersonCamera( _float target_x, _float target_y, _float z_offset, _float rotation, _float aoa, _float range, _float roll, _float fov = 58.0f )
		: mTargetX( target_x )
		, mTargetY( target_y )
		, mZOffset( z_offset )
		, mRotation( rotation )
		, mAoA( aoa )
		, mRange( range )
		, mRoll( roll )
		, mFOV( fov )
	{

	}
};

//----------------------------------------------------------------------------
// FirstPersonCamera
//----------------------------------------------------------------------------

struct FirstPersonCamera
{
	_float		mEyeX;
	_float		mEyeY;
	_float		mEyeZ;

	_float		mQuatX;
	_float		mQuatY;
	_float		mQuatZ;
	_float		mQuatW;

	_float		mFOV;

	FirstPersonCamera( )
		: mEyeX( 0.0f )
		, mEyeY( 0.0f )
		, mEyeZ( 0.0f )
		, mQuatX( 0.0f )
		, mQuatY( 0.0f )
		, mQuatZ( 0.0f )
		, mQuatW( 1.0f )
		, mFOV( 58.0f )
	{

	}
	FirstPersonCamera( const FirstPersonCamera& camera )
		: mEyeX( camera.mEyeX )
		, mEyeY( camera.mEyeY )
		, mEyeZ( camera.mEyeZ )
		, mQuatX( camera.mQuatX )
		, mQuatY( camera.mQuatY )
		, mQuatZ( camera.mQuatZ )
		, mQuatW( camera.mQuatW )
		, mFOV( camera.mFOV )
	{

	}
	FirstPersonCamera( _float eye_x, _float eye_y, _float eye_z, _float x, _float y, _float z, _float w, _float fov = 58.0f )
		: mEyeX( eye_x )
		, mEyeY( eye_y )
		, mEyeZ( eye_z )
		, mQuatX( x )
		, mQuatY( y )
		, mQuatZ( z )
		, mQuatW( w )
		, mFOV( fov )
	{

	}

	_ubool IsEqual( const FirstPersonCamera& camera )
	{
		if ( mEyeX != camera.mEyeX )
			return _false;
		if ( mEyeY != camera.mEyeY )
			return _false;
		if ( mEyeZ != camera.mEyeZ )
			return _false;
		if ( mFOV != camera.mFOV )
			return _false;

		if ( mQuatX != camera.mQuatX )
			return _false;
		if ( mQuatY != camera.mQuatY )
			return _false;
		if ( mQuatZ != camera.mQuatZ )
			return _false;
		if ( mQuatW != camera.mQuatW )
			return _false;

		return _true;
	}

	FirstPersonCamera ToPitchYawRoll( ) const
	{
		FirstPersonCamera camera( mEyeX, mEyeY, mEyeZ, mQuatX, mQuatZ, -mQuatY, mQuatW, mFOV );
		return camera;
	}

	FirstPersonCamera ToRotXYZ( ) const
	{
		FirstPersonCamera camera( mEyeX, mEyeY, mEyeZ, mQuatX, -mQuatZ, mQuatY, mQuatW, mFOV );
		return camera;
	}
};

}