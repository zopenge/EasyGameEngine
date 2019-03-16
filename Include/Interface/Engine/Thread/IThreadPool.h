//! @file     IThreadPool.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IThreadPool
//----------------------------------------------------------------------------

class IThreadPool : public IObserver
{
public:
	//!	The task callback function.
	//!	@param		none.
	//!	@return		The error ID, 0 indicates no error.
	typedef _dword (*OnProcessTask)( );

public:
	//!	Check whether is breaking all processions now.
	//!	@param		none.
	//!	@return		True indicates break all processions.
	virtual _ubool IsBreakingAllProcessions( ) const PURE;
	//!	Check whether it's busy.
	//!	@param		none.
	//!	@return		True indicates it's busy.
	virtual _ubool IsBusy( ) const PURE;

	//!	Set the sleep time.
	//!	@param		time	The sleep time in milliseconds, -1 indicates work in full time.
	//! @return		none.
	virtual _void SetSleepTime( _dword time ) PURE;
	//!	Get the sleep time.
	//!	@param		none.
	//! @return		The sleep time in milliseconds, -1 indicates work in full time.
	virtual _dword GetSleepTime( ) const PURE;

	//!	Lock.
	//!	@param		none.
	//!	@return		none.
	virtual _void EnterLock( ) PURE;
	//!	Unlock.
	//!	@param		none.
	//!	@return		none.
	virtual _void LeaveLock( ) PURE;

	//!	Create.
	//!	@param		thread_number	The thread worker number.
	//!	@param		name			The thread pool name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Create( _dword thread_number, WStringPtr name = L"" ) PURE;
	//!	Close.
	//!	@param		none.
	//!	@return		none.
	virtual _void Close( ) PURE;

	//!	Get the thread number.
	//!	@param		none.
	//!	@return		The thread number.
	virtual _dword GetThreadNumber( ) const PURE;

	//!	Get tasks number.
	//!	@param		none.
	//! @return		The task number.
	virtual _dword GetTaskNumber( ) const PURE;
	//!	Add single task.
	//!	@param		funcpointer		The thread task callback function.
	//! @return		True indicates success false indicates failure.
	virtual _ubool AddTask( OnProcessTask funcpointer ) PURE;
	//!	Add single task.
	//!	@param		task			The thread task.
	//! @return		True indicates success false indicates failure.
	virtual _ubool AddTask( IThreadTask* task ) PURE;
	//!	Add task set.
	//!	@param		taskset			The thread task set.
	//! @return		True indicates success false indicates failure.
	virtual _ubool AddTaskSet( IThreadTaskSet* taskset ) PURE;
	//!	Remove task.
	//!	@param		task			The thread task.
	//! @return		none.
	virtual _void RemoveTask( IThreadTask* task ) PURE;
	//!	Remove all tasks.
	//!	@remark		The function won't return until all workers become to sleep and all tasks removed and except the keep alive tasks.
	//!	@param		none.
	//!	@return		none.
	virtual _ubool RemoveAllTasks( ) PURE;

	//!	Wakeup all workers to process tasks.
	//!	@param		none.
	//! @return		none.
	virtual _void Wakeup( ) PURE;
	//!	Let all workers sleep.
	//!	@param		none.
	//! @return		none.
	virtual _void Sleep( ) PURE;
	//!	Suspend.
	//!	@param		suspend			True indicates suspend it.
	//! @return		none.
	virtual _void Suspend( _ubool suspend ) PURE;
};

}