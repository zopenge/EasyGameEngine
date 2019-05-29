//! @file     ThreadTaskWorker.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class ThreadPool;

//----------------------------------------------------------------------------
// ThreadTaskWorker
//----------------------------------------------------------------------------

//! A thread worker of thread pool class
class ThreadTaskWorker : public Thread
{
private:
	typedef Thread BaseClass;

private:
	//!	True indicates the thread is busy now
	_ubool			mIsBusy;

	//!	The sleep time in milliseconds
	_dword			mSleepTime;

	//!	The thread wake event
	EventObject*	mThreadWakeEvent;

	//!	The thread pool
	ThreadPool*		mThreadPool;

// Thread Interface
private:
	//!	The parameter 1 : The wake event signal from thread pool
	//!	The parameter 2 : NA
	virtual _dword	OnRunThread( const QwordParams2& params ) override;
	virtual _void	OnCloseThread( _dword exitcode, const QwordParams2& params ) override;

public:
	ThreadTaskWorker( );
	virtual ~ThreadTaskWorker( );

public:
	//!	Check the thread is busy or not.
	EGE_IS_ACCESSOR( Busy )

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr name, EventObject* wait_event, ThreadPool* thread_pool );
};

}