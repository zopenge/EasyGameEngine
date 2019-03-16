//! @file     PersistenceThread.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PersistenceThread
//----------------------------------------------------------------------------

//! This class represents a thread in a process
class PersistenceThread : public Thread
{
public:
	//!	The feedback action of update thread callback function
	enum _ACTION
	{
		//!	Keep the function in the function queue
		_ACTION_KEEP	= 1,
		//!	Remove the function in the function queue
		_ACTION_REMOVE	= 2,
	};

protected:
	//! Define update callback function prototype.
	//! @param		parameters		The user defined parameters.
	//! @return		The action ID, @see _ACTION.
	typedef _dword (*OnUpdateFunction)( const QwordParameters2& parameters );

protected:
	typedef CallbackFunc< OnUpdateFunction, _dword, QwordParameters2 > UpdateFunc;
	
protected:
	//! Update interval
	_dword		mInterval;
	//!	Thread wake event
	EventObject	mWakeEvent;

	//!	The current updaters number
	_dword		mCurUpdatersNumber;
	//!	The max updaters number
	_dword		mMaxUpdatersNumber;
	//! The updaters buffer
	UpdateFunc*	mUpdaters;

// Thread Interface
protected:
	virtual _dword	OnRunThread( const QwordParameters2& parameters ) override;
	virtual _void	OnCloseThread( _dword exitcode, const QwordParameters2& parameters ) override;

public:
	//! Constructor, create a empty thread, that is not running.
	//! @param		none
	PersistenceThread( );
	//! Destructor, close thread and delete its kernel object.
	//! @param		none
	virtual ~PersistenceThread( );

public:
	//!	Get the interval in milliseconds.
	//!	@param		none.
	//!	@return		The interval in milliseconds.
	_dword GetInterval( ) const;

	//! Get if this thread is busy ( has some update function to call ) or not.
	//! @param		none.
	//! @return		True if thread is busy.
	_ubool IsThreadBusy( ) const;

	//! Creates a thread to execute update functions.
	//!	@param		max_updaters_number	The max updaters number.
	//!	@param		priority			The priority (0~99).
	//! @param		suspend				If it is true, thread is created in a suspended state and does not run until Resume is called.
	//! @param		interval			The sleep interval of thread in milliseconds
	//!	@param		name				The thread name.
	//! @return		True indicates success, false indicates failure.
	_ubool Create( _dword max_updaters_number, _dword priority, _ubool suspend, _dword interval, WStringPtr name = L"" );
	//! Close the thread in a safe way.
	//! @param		none.
	//!	@return		none.
	_void Close( );
	//! Suspend the thread, ( suspend count is incremented ).
	//! @param		none
	//! @return		True indicates success, false indicates failure.
	_ubool Suspend( );
	//! Decrements suspend count. When it is decremented to zero, the thread is resumed.
	//! @param		none
	//! @return		True indicates success, false indicates failure.
	_ubool Resume( );

	//! Add updater functions, the function will be called every interval in the thread.
	//! @param		func		Update function pointer.
	//! @param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	_ubool AddUpdaterFunc( OnUpdateFunction func, const QwordParameters2& parameters );
	//!	Remove all updater functions.
	//! @param		none.
	//! @return		none.
	_void RemoveAllUpdaterFuncs( );
};

}