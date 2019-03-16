//! @file     DeferredProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DeferredProcessor
//----------------------------------------------------------------------------

class DeferredProcessor
{
private:
	//! The status
	enum _STATUS
	{
		_STATUS_UNKONWN,
		_STATUS_FIRST_MESSAGE,
		_STATUS_IN_INTERVAL_RANGE,
	};

private:
	//! The status
	_STATUS	mStatus;
	//! The interval time
	_dword	mIntervalTime;
	//! The first delay time
	_dword	mFirstDelayTime;

	//! The previous tickcount
	_dword	mPrevTickcount;

public:
	DeferredProcessor( );
	~DeferredProcessor( );

public:
	//! Set the interval time.
	//! @param		interval	The interval time in milliseconds, -1 indicates unlimited.
	//! @return		none.
	_void SetIntervalTime( _dword interval );
	//! Set the first delay time.
	//! @param		delay		The delay time in milliseconds, -1 indicates unlimited.
	//! @return		none.
	_void SetFirstDelayTime( _dword delay );

	//! Clear.
	//! @param		none.
	//! @return		none.
	_void Clear( );

	//! Reset.
	//! @param		none.
	//! @return		none.
	_void Reset( );

	//! Update.
	//! @param		none.
	//! @return		True indicates can occur the event, otherwise we should wait for it.
	_ubool Update( );
};

//----------------------------------------------------------------------------
// DeferredProcessor Implementation
//----------------------------------------------------------------------------

}