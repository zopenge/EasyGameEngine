//! @file     Timer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Timer
//----------------------------------------------------------------------------

class Timer
{
public:
	//!	When overdue ( time up ).
	//!	@param		parameters		The user defined parameters.
	//!	@return		none.
	typedef _void (*OnOverdue)( const QwordParameters2& parameters );

private:
	typedef CallbackFunc< OnOverdue, _void, QwordParameters2 > OverdueFunc;

private:
	//!	True indicates it's paused
	_ubool		mIsPaused;

	//!	The elapsed time
	_dword		mElapsedTime;
	//!	The interval time
	_dword		mIntervalTime;

	//!	The overdue callback function
	OverdueFunc	mOverdueFunc;

public:
	Timer( );
	~Timer( );

public:
	//!	Register overdue callback function.
	//! @param		funcpointer	The function pointer.
	//! @param		parameters	The user defined parameters.
	//! @return		none.
	_void RegisterOverdueFunc( OnOverdue funcpointer, const QwordParameters2& parameters );

	//!	Initialize.
	//!	@param		interval_time	The interval time in milliseconds.
	//!	@return		none.
	_void Init( _dword interval_time );

	//!	Resume.
	//!	@param		none.
	//!	@return		none.
	_void Resume( );
	//!	Pause.
	//!	@param		none.
	//!	@return		none.
	_void Pause( );

	//!	Get the elapsed time in milliseconds.
	//!	@param		none.
	//!	@return		The elapsed time in milliseconds.
	_dword GetElapsedTime( ) const;
	//!	Get the interval time in milliseconds.
	//!	@param		none.
	//!	@return		The interval time in milliseconds.
	_dword GetIntervalTime( ) const;

	//!	Check whether it's paused or not.
	//!	@param		none.
	//!	@return		True indicates it's paused.
	_ubool IsPaused( ) const;
	//!	Check whether it's overdue or not.
	//! @param		elapse		The millisecond time of the update interval.
	//!	@param		auto_pause	True indicates pause timer when overdue.
	//!	@return		True indicates it's overdue.
	_ubool IsOverdue( _dword elapse, _ubool auto_pause = _true );
};

}