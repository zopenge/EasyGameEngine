//! @file     ThreadPool.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ThreadPool Implementation
//----------------------------------------------------------------------------

ThreadPool::ThreadPool( )
{
	mSleepTime			= 10;

	mThreadTaskQueue	= new ThreadTaskQueue( mLocker );

	mThreadNumber		= 0;
	mThreadWakeEvents	= _null;
	mThreadWorkers		= _null;
}

ThreadPool::~ThreadPool( )
{
	Close( );

	EGE_DELETE( mThreadTaskQueue );
}

_ubool ThreadPool::RegisterTask( ITask* task )
{
	EGE_ASSERT( task != _null );

	// Register an observer of task set
	task->RegisterObserver( this );

	// Wakeup the workers to process tasks
	if ( task->HasFlags( ITask::_FLAG_AUTO_START ) || task->GetState( ) == _PS_RUNNING )
		Wakeup( );

	return _true;
}

_void ThreadPool::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	const ITask* task = static_cast< const ITask* >( object );
	EGE_ASSERT( task != _null );

	switch ( task->GetState( ) )
	{
		// Wakeup all workers if running
		case _PS_RUNNING:
		{
			Wakeup( );
		}
		break;

		// Remove it from observable pool when it's finished or releasing
		case _PS_RELEASING:
		case _PS_FINISHED:
		{
//			task->UnregisterObserver( this );
		}
		break;
            
        default:
            break;
	}

	// Notify all observers some task state has changed
	NotifyObservers( generator, event );
}

_void ThreadPool::SetSleepTime( _dword time )
{
	mSleepTime = time;
}

_dword ThreadPool::GetSleepTime( ) const
{
	return mSleepTime;
}

_ubool ThreadPool::IsBreakingAllProcessions( ) const
{
	return mFlags.HasFlags( _FLAG_BREAKING_ALL_PROCESSIONS );
}

_ubool ThreadPool::IsBusy( ) const
{
	for ( _dword i = 0; i < mThreadNumber; i ++ )
	{
		if ( mThreadWorkers[i].IsBusy( ) )
			return _true;
	}

	return _false;
}

_void ThreadPool::EnterLock( )
{
	mLocker.Enter( );
}

_void ThreadPool::LeaveLock( )
{
	mLocker.Leave( );
}

_ubool ThreadPool::Create( _dword thread_number, WStringPtr name )
{
	if ( thread_number == 0 )
		return _false;

	Close( );

	// Get the threads number in range and allocate it
	mThreadNumber		= Math::Min< _dword >( thread_number, _MAX_THREAD_NUMBER );
	mThreadWorkers		= new ThreadTaskWorker[ mThreadNumber ];

	// Create thread workers events
	mThreadWakeEvents	= new EventObject[ mThreadNumber ];

	// Create the threads workers
	for ( _dword i = 0; i < mThreadNumber; i ++ )
	{
		// Initialize wake event
		if ( mThreadWakeEvents[i].Create( _true, _false ) == _false )
			return _false;

		// Build the thread workers name
		_charw thread_worker_name[1024]; thread_worker_name[0] = 0;
		if ( name.IsEmpty( ) == _false )
			Platform::FormatStringBuffer( thread_worker_name, 1024, L"%s_THREAD(%d)", name.Str( ), i + 1 );

		// Create thread worker
		if ( mThreadWorkers[i].Initialize( thread_worker_name, &mThreadWakeEvents[i], this ) == _false )
			return _false;
	}

	return _true;
}

_void ThreadPool::Close( )
{
	// Change this member to make sure we won't add any new tasks
	mThreadNumber = 0;

	// Remove all tasks
	RemoveAllTasks( );

	// Break all processions
	mFlags.CombineFlags( _FLAG_BREAKING_ALL_PROCESSIONS );

	// Wakeup all thread workers to prevent the wait signal block
	Wakeup( );

	// Delete all events and workers
	EGE_DELETE_ARRAY( mThreadWorkers );
	EGE_DELETE_ARRAY( mThreadWakeEvents );

	// End to break all processions
	mFlags.ClearFlags( _FLAG_BREAKING_ALL_PROCESSIONS );
}

_dword ThreadPool::GetThreadNumber( ) const
{
	return mThreadNumber;
}

_dword ThreadPool::GetTaskNumber( ) const
{
	return mThreadTaskQueue->GetTaskNumber( );
}

_ubool ThreadPool::AddTask( OnProcessTask funcpointer )
{
	if ( funcpointer == _null )
		return _false;

	// Create task processor
	IThreadTaskPassRef processor = new ThreadTaskProcessor( funcpointer );
	processor->CombineFlags( ITask::_FLAG_AUTO_START );

	return AddTask( processor.GetPtr( ) );
}

_ubool ThreadPool::AddTask( IThreadTask* task )
{
	if ( task == _null )
		return _false;

	// Add task into queue
	mThreadTaskQueue->AddTask( task );

	// Register task
	if ( RegisterTask( task ) == _false )
		return _false;

	return _true;
}

_ubool ThreadPool::AddTaskSet( IThreadTaskSet* taskset )
{
	if ( taskset == _null )
		return _false;

	// Add task set into queue
	mThreadTaskQueue->AddTaskSet( taskset );

	// Register task
	if ( RegisterTask( taskset ) == _false )
		return _false;

	return _true;
}

_void ThreadPool::RemoveTask( IThreadTask* task )
{
	mThreadTaskQueue->RemoveTask( task );
}

_ubool ThreadPool::RemoveAllTasks( )
{
	// Break all processions
	mFlags.CombineFlags( _FLAG_BREAKING_ALL_PROCESSIONS );

	// Let all works to sleep
	Sleep( );

	// Make sure all the threads become to sleep
	for ( _dword i = 0; i < mThreadNumber; i ++ )
	{
		if ( mThreadWorkers[i].IsBusy( ) )
		{
			// Sleep a litter while
			Platform::Sleep( 10 );

			// Re-test it
			i --;
			continue;
		}
	}

	// Remove all task
	mThreadTaskQueue->RemoveAllTasks( );

	// End to break all processions
	mFlags.ClearFlags( _FLAG_BREAKING_ALL_PROCESSIONS );

	return _true;
}

_void ThreadPool::Wakeup( )
{
	if ( mFlags.HasFlags( _FLAG_SUSPENDING ) )
		return;

	// Wakeup threads
	for ( _dword i = 0; i < mThreadNumber; i ++ )
		mThreadWakeEvents[i].Set( );
}

_void ThreadPool::Sleep( )
{
	// Block at the wake up event
	for ( _dword i = 0; i < mThreadNumber; i ++ )
		mThreadWakeEvents[i].Reset( );
}

_void ThreadPool::Suspend( _ubool suspend )
{
	mFlags.EnableFlags( _FLAG_SUSPENDING, suspend );

	if ( suspend )
		Sleep( );
	else
		Wakeup( );
}
