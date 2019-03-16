//! @file     FPSTimer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FPSTimer
//----------------------------------------------------------------------------

class FPSTimer
{
private:
	//!	The default interval time
	enum { _DEFAULT_INTERVAL_TIME = 1000 };

private:
	//!	The interval time in milliseconds
	_dword	mInterval;

	//!	The current frame tick count
	_dword	mFrameTickcount;
	//!	The total frame tick count
	_dword	mTotalFrameTickcount;

	//!	The frame number in specified time region
	_dword	mFrameNumber;
	//!	The total frame number
	_dword	mTotalFrameNumber;

	//!	The frame number per-second
	_float	mFPS;

public:
	FPSTimer( );
	~FPSTimer( );

public:
	//!	Update.
	//! @param		elapse		The millisecond time of the update interval.
	//! @return		True indicates info has been flushed.
	_ubool Tick( _dword elapse );

	//!	Set the flush interval time.
	//!	@param		time		The interval time in milliseconds.
	//!	@return		none.
	_void SetInterval( _dword time );
	//!	Get the flush interval time.
	//!	@param		none.
	//!	@return		The interval time in milliseconds.
	_dword GetInterval( ) const;

	//!	Get the frame number pre-second.
	//!	@param		none.
	//!	@return		The frame number pre-second.
	_float GetFPS( ) const;
	//!	Get the average frame number pre-second.
	//!	@param		none.
	//!	@return		The average frame number pre-second.
	_float GetAvgFPS( ) const;
};

}