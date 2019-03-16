//! @file     ThreadPool.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ThreadPool
//----------------------------------------------------------------------------

//! A thread pool class
class ThreadPool : public INTERFACE_OBSERVER_IMPL( IThreadPool )
{
private:
	typedef INTERFACE_OBSERVER_IMPL( IThreadPool ) BaseClass;

private:
	//!	The maximal thread workers number
	enum { _MAX_THREAD_NUMBER = 16 };

	//!	The flags
	enum _FLAGS
	{
		//!	True indicates it's breaking all processions.
		_FLAG_BREAKING_ALL_PROCESSIONS	= 1 << 0,
		//!	True indicates it suspend now.
		_FLAG_SUSPENDING				= 1 << 1,
	};

private:
	//!	The thread pool locker
	Lock				mLocker;
	//!	The flags
	FlagsObject			mFlags;

	//!	The sleep time in milliseconds
	_dword				mSleepTime;

	//!	The thread task queue
	ThreadTaskQueue*	mThreadTaskQueue;

	//!	The thread number
	_dword				mThreadNumber;
	//!	The thread wake event
	EventObject*		mThreadWakeEvents;
	//!	The threads worker
	ThreadTaskWorker*	mThreadWorkers;

private:
	//!	Register task.
	_ubool RegisterTask( ITask* task );

// IObserver Interface
private:
	virtual _void 	Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

public:
	ThreadPool( );
	virtual ~ThreadPool( );

public:
	//!	Get the locker.
	EGE_GETR_ACCESSOR( Lock, Locker )
	//!	Get the thread task queue
	EGE_GETP_ACCESSOR( ThreadTaskQueue, ThreadTaskQueue )

// IThreadPool Interface
public:
	virtual _ubool	IsBreakingAllProcessions( ) const override;
	virtual _ubool	IsBusy( ) const override;

	virtual _void	SetSleepTime( _dword time ) override;
	virtual _dword	GetSleepTime( ) const override;

	virtual _void	EnterLock( ) override;
	virtual _void	LeaveLock( ) override;

	virtual _ubool 	Create( _dword thread_number, WStringPtr name = L"" ) override;
	virtual _void 	Close( ) override;

	virtual _dword	GetThreadNumber( ) const override;

	virtual _dword	GetTaskNumber( ) const override;
	virtual _ubool	AddTask( OnProcessTask funcpointer ) override;
	virtual _ubool 	AddTask( IThreadTask* task ) override;
	virtual _ubool 	AddTaskSet( IThreadTaskSet* taskset ) override;
	virtual _void	RemoveTask( IThreadTask* task ) override;
	virtual _ubool	RemoveAllTasks( ) override;

	virtual _void	Wakeup( ) override;
	virtual _void	Sleep( ) override;
	virtual _void	Suspend( _ubool suspend ) override;
};

}