//! @file     SingleThreadPool.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// SingleThreadPool Implementation
//----------------------------------------------------------------------------

SingleThreadPool::SingleThreadPool( )
{
	mSleepTime			= 100;

	mThreadTaskQueue	= new ThreadTaskQueue( mLocker );
}

SingleThreadPool::~SingleThreadPool( )
{
	Close( );

	EGE_DELETE( mThreadTaskQueue );
}

_void SingleThreadPool::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	// Notify all observers some task state has changed
	NotifyObservers( generator, event );
}

_void SingleThreadPool::Tick( _dword limited_elapse, _dword elapse )
{
	// Query for the task queue ( process only 1 task each tick )
	ThreadTaskInfo* task_info = mThreadTaskQueue->GetTask( );
	if ( task_info != _null )
		ThreadTaskProcessor::ProcessTask( Platform::GetMainThreadID( ), mSleepTime, task_info, this );
}

_ubool SingleThreadPool::IsBreakingAllProcessions( ) const
{
	return _false;
}

_ubool SingleThreadPool::IsBusy( ) const
{
	if ( mThreadTaskQueue->GetTaskNumber( ) != 0 )
		return _true;

	return _false;
}

_void SingleThreadPool::SetSleepTime( _dword time )
{
	mSleepTime = time;
}

_dword SingleThreadPool::GetSleepTime( ) const
{
	return mSleepTime;
}

_void SingleThreadPool::EnterLock( )
{

}

_void SingleThreadPool::LeaveLock( )
{

}

_ubool SingleThreadPool::Create( _dword thread_number, WStringPtr name )
{
	return _true;
}

_void SingleThreadPool::Close( )
{
}

_dword SingleThreadPool::GetThreadNumber( ) const
{
	return 1;
}

_dword SingleThreadPool::GetTaskNumber( ) const
{
	return mThreadTaskQueue->GetTaskNumber( );
}

_ubool SingleThreadPool::AddTask( OnProcessTask funcpointer )
{
	if ( funcpointer == _null )
		return _false;

	// Create task processor
	IThreadTaskPassRef processor = new ThreadTaskProcessor( funcpointer );
	processor->CombineFlags( ITask::_FLAG_AUTO_START );

	return AddTask( processor.GetPtr( ) );
}

_ubool SingleThreadPool::AddTask( IThreadTask* task )
{
	if ( task == _null )
		return _false;

	// Add task into queue
	mThreadTaskQueue->AddTask( task );

	// Register an observer of task
	task->RegisterObserver( this );

	return _true;
}

_ubool SingleThreadPool::AddTaskSet( IThreadTaskSet* taskset )
{
	if ( taskset == _null )
		return _false;

	// Add task set into queue
	mThreadTaskQueue->AddTaskSet( taskset );

	// Register an observer of task set
	taskset->RegisterObserver( this );

	return _true;
}

_void SingleThreadPool::RemoveTask( IThreadTask* task )
{
	mThreadTaskQueue->RemoveTask( task );
}

_ubool SingleThreadPool::RemoveAllTasks( )
{
	// Remove all task
	mThreadTaskQueue->RemoveAllTasks( );

	return _true;
}

_void SingleThreadPool::Wakeup( )
{
}

_void SingleThreadPool::Sleep( )
{
}

_void SingleThreadPool::Suspend( _ubool suspend )
{
}
