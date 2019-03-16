//! @file     ThreadTaskQueue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ThreadTaskInfo Implementation
//----------------------------------------------------------------------------

ThreadTaskInfo::ThreadTaskInfo( Lock& lock, IThreadTask* task ) : mLock( lock )
{
	mFlags.EnableFlags( _FLAG_ENABLE, _true );

	mTask = task;
}

ThreadTaskInfo::ThreadTaskInfo( Lock& lock, IThreadTaskSet* task_set ) : mLock( lock )
{
	mFlags.EnableFlags( _FLAG_ENABLE, _true );
	mFlags.EnableFlags( _FLAG_TASK_SET_TYPE, _true );

	mTask = task_set;
}

ThreadTaskInfo::~ThreadTaskInfo( )
{
}

_void ThreadTaskInfo::Enable( _ubool enable )
{
	mFlags.EnableFlags( _FLAG_ENABLE, enable );
}

_ubool ThreadTaskInfo::IsEnable( ) const
{
	return mFlags.HasFlags( _FLAG_ENABLE );
}

_ubool ThreadTaskInfo::IsThreadTaskSetType( ) const
{
	return mFlags.HasFlags( _FLAG_TASK_SET_TYPE );
}

ITask* ThreadTaskInfo::GetTask( )
{
	return mTask;
}

const ITask* ThreadTaskInfo::GetTask( ) const
{
	return mTask;
}

IThreadTask* ThreadTaskInfo::GetThreadTask( )
{
	return mTask.cast_static< IThreadTask >( );
}

const IThreadTask* ThreadTaskInfo::GetThreadTask( ) const
{
	return mTask.cast_static< IThreadTask >( );
}

IThreadTaskSet* ThreadTaskInfo::GetThreadTaskSet( )
{
	return mTask.cast_static< IThreadTaskSet >( );
}

const IThreadTaskSet* ThreadTaskInfo::GetThreadTaskSet( ) const
{
	return mTask.cast_static< IThreadTaskSet >( );
}

_ubool ThreadTaskInfo::IsWaiting( ) const
{
	_PROCESS_STATE state = mTask->GetState( );
	if ( state == _PS_NORMAL || state == _PS_WAITING )
		return _true;

	return _false;
}

_ubool ThreadTaskInfo::IsSuspended( ) const
{
	_PROCESS_STATE state = mTask->GetState( );
	if ( state == _PS_SUSPENDING )
		return _true;

	return _false;
}

_ubool ThreadTaskInfo::IsRunning( ) const
{
	_PROCESS_STATE state = mTask->GetState( );
	if ( state == _PS_RUNNING )
		return _true;

	return _false;
}

_ubool ThreadTaskInfo::IsDead( ) const
{
	_PROCESS_STATE state = mTask->GetState( );
	if ( state == _PS_ERROR || state == _PS_ABORTED || state == _PS_TIMEOUT || state == _PS_FINISHED )
		return _true;

	return _false;
}

_ubool ThreadTaskInfo::Finish( )
{
	return mTask->Finish( );
}

_ubool ThreadTaskInfo::GetTaskSetRange( _dword& cur_index, DwordDataField& sub_tasks_field ) const
{
	LockOwner lock_owner( mLock );

	// Get the thread task set
	const IThreadTaskSet* task_set = GetThreadTaskSet( );
	EGE_ASSERT( task_set != _null );

	// Get the number of tasks
	_dword tasks_number = task_set->GetSubTaskNumber( );

	// All task completed
	if ( cur_index >= tasks_number )
		return _false;

	// Get the remaining tasks number
	_dword tasks_remaining = tasks_number - cur_index;

	// Get the tasks to assign ( div 2 to make much small ... )
	_dword tasks_to_assign = Math::Clamp< _dword >( tasks_remaining, 1, task_set->GetMaxRangeOfSubTask( ) );

	// Feedback the start index and end index
	sub_tasks_field.Init( cur_index, tasks_to_assign );

	// Update the current sub-task index
	cur_index += tasks_to_assign;

	return _true;
}

//----------------------------------------------------------------------------
// ThreadTaskQueue Implementation
//----------------------------------------------------------------------------

ThreadTaskQueue::ThreadTaskQueue( Lock& lock ) : mLock( lock )
{
	mTaskIndex = 0;
}

ThreadTaskQueue::~ThreadTaskQueue( )
{
	LockOwner lock_owner( mLock );

	// Delete all tasks
	for ( _dword i = 0; i < mTasks.Number( ); i ++ )
		EGE_RELEASE( mTasks[i] );
}

ThreadTaskInfo* ThreadTaskQueue::GetTask( )
{
	LockOwner lock_owner( mLock );

	for ( _dword processed_task_number = 0; processed_task_number < mTasks.Number( ); processed_task_number ++ )
	{
		// Update the task index
		mTaskIndex %= mTasks.Number( );

		// Get the task info
		ThreadTaskInfo* task_info = mTasks[mTaskIndex ++];

		// If it's dead task then remove it
		if ( task_info->IsDead( ) )
		{
			EGE_RELEASE( task_info );
			mTasks.RemoveByIndex( processed_task_number -- );
			continue;
		}

		// Skip for disable task
		if ( task_info->IsEnable( ) == _false )
			continue;

		// Skip for processing task
		if ( task_info->IsWaiting( ) == _false )
			continue;

		// Get the task interface
		ITask* task = task_info->GetTask( );
		EGE_ASSERT( task != _null );

		// Make it to running state
		task->Start( );

		// Disable to make sure 1 thread get 1 task to do
		task_info->Enable( _false );

		// We found a unfinished task
		return task_info;
	}

	// No any more tasks
	return _null;
}

_dword ThreadTaskQueue::GetTaskNumber( ) const
{
	return mTasks.Number( );
}

_void ThreadTaskQueue::AddTask( IThreadTask* task )
{
	LockOwner lock_owner( mLock );

	EGE_ASSERT( task != _null );

	ThreadTaskInfo* task_info = new ThreadTaskInfo( mLock, task );
	mTasks.Append( task_info );
}

_void ThreadTaskQueue::AddTaskSet( IThreadTaskSet* taskset )
{
	LockOwner lock_owner( mLock );

	EGE_ASSERT( taskset != _null );

	ThreadTaskInfo* task_info = new ThreadTaskInfo( mLock, taskset );
	mTasks.Append( task_info );
}

_void ThreadTaskQueue::RemoveTask( IThreadTask* task )
{
	LockOwner lock_owner( mLock );

	// Delete all tasks
	for ( _dword i = 0; i < mTasks.Number( ); i ++ )
	{
		if ( mTasks[i]->GetThreadTask( ) != task )
			continue;

		EGE_RELEASE( mTasks[i] );
		mTasks.RemoveByIndex( i );
		return;
	}
}

_void ThreadTaskQueue::RemoveAllTasks( )
{
	LockOwner lock_owner( mLock );

	// Delete all tasks
	for ( _dword i = 0; i < mTasks.Number( ); i ++ )
	{
		// Skip to remove keep alive task
		if ( mTasks[i]->GetTask( )->HasFlags( ITask::_FLAG_KEEP_ALIVE ) )
			continue;

		EGE_RELEASE( mTasks[i] );
		mTasks.RemoveByIndex( i -- );
	}
}
