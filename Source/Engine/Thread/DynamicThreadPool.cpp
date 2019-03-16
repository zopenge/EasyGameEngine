//! @file     DynamicThreadPool.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DynamicThreadPool Implementation
//----------------------------------------------------------------------------

DynamicThreadPool::DynamicThreadPool( )
{
	mSleepTime			= 100;

	mThreadTaskQueue	= new ThreadTaskQueue( mLocker );
}

DynamicThreadPool::~DynamicThreadPool( )
{
	Close( );

	EGE_DELETE( mThreadTaskQueue );
}

_void DynamicThreadPool::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	// Notify all observers some task state has changed
	NotifyObservers( generator, event );
}

_void DynamicThreadPool::Tick( _time_t tick, _dword elapse )
{
	// Query for the task queue ( process only 1 task each tick )
	ThreadTaskInfo* task_info = mThreadTaskQueue->GetTask( );
	if ( task_info != _null )
		ThreadTaskProcessor::ProcessTask( Platform::GetMainThreadID( ), mSleepTime, task_info, this );
}

_ubool DynamicThreadPool::IsBreakingAllProcessions( ) const
{
	return _false;
}

_void DynamicThreadPool::SetSleepTime( _dword time )
{
	mSleepTime = time;
}

_dword DynamicThreadPool::GetSleepTime( ) const
{
	return mSleepTime;
}

_void DynamicThreadPool::EnterLock( )
{

}

_void DynamicThreadPool::LeaveLock( )
{

}

_ubool DynamicThreadPool::Create( _dword thread_number, WStringPtr name )
{
	return _true;
}

_void DynamicThreadPool::Close( )
{
}

_dword DynamicThreadPool::GetThreadNumber( ) const
{
	return 1;
}

_dword DynamicThreadPool::GetTaskNumber( ) const
{
	return mThreadTaskQueue->GetTaskNumber( );
}

_ubool DynamicThreadPool::AddTask( OnProcessTask funcpointer )
{
	if ( funcpointer == _null )
		return _false;

	// Create task processor
	IThreadTaskPassRef processor = new ThreadTaskProcessor( funcpointer );
	processor->CombineFlags( ITask::_FLAG_AUTO_START );

	return AddTask( processor.GetPtr( ) );
}

_ubool DynamicThreadPool::AddTask( IThreadTask* task )
{
	if ( task == _null )
		return _false;

	// Add task into queue
	mThreadTaskQueue->AddTask( task );

	// Register an observer of task
	task->RegisterObserver( this );

	return _true;
}

_ubool DynamicThreadPool::AddTaskSet( IThreadTaskSet* taskset )
{
	if ( taskset == _null )
		return _false;

	// Add task set into queue
	mThreadTaskQueue->AddTaskSet( taskset );

	// Register an observer of task set
	taskset->RegisterObserver( this );

	return _true;
}

_void DynamicThreadPool::RemoveTask( IThreadTask* task )
{
	mThreadTaskQueue->RemoveTask( task );
}

_ubool DynamicThreadPool::RemoveAllTasks( )
{
	// Remove all task
	mThreadTaskQueue->RemoveAllTasks( );

	return _true;
}

_void DynamicThreadPool::Wakeup( )
{
}

_void DynamicThreadPool::Sleep( )
{
}

_void DynamicThreadPool::Suspend( _ubool suspend )
{
}
