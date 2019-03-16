//! @file     SingleThreadPool.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SingleThreadPool
//----------------------------------------------------------------------------

//! A single thread pool class
class SingleThreadPool : public INTERFACE_OBSERVER_IMPL( IThreadPool )
{
private:
	typedef INTERFACE_OBSERVER_IMPL( IThreadPool ) BaseClass;

private:
	//!	The thread pool locker
	Lock				mLocker;

	//!	The sleep time in milliseconds
	_dword				mSleepTime;

	//!	The thread task queue
	ThreadTaskQueue*	mThreadTaskQueue;

// IObserver Interface
private:
	virtual _void 	Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

public:
	SingleThreadPool( );
	virtual ~SingleThreadPool( );

// IObject Interface
public:
	virtual _void	Tick( _dword limited_elapse, _dword elapse ) override;

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