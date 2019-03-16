//! @file     ThreadTaskProcessor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ThreadTaskProcessor Implementation
//----------------------------------------------------------------------------

ThreadTaskProcessor::ThreadTaskProcessor( IThreadPool::OnProcessTask funcpointer )
{
	EGE_ASSERT( funcpointer != _null );

	mProcessTaskFunc = funcpointer;
}

ThreadTaskProcessor::~ThreadTaskProcessor( )
{

}

_void ThreadTaskProcessor::ProcessTask( _thread_id thread_id, _dword sleep_time, ThreadTaskInfo* task_info, IThreadPool* thread_pool )
{
	EGE_ASSERT( task_info != _null );
	EGE_ASSERT( thread_pool != _null );

	// The error ID of task
	_dword			err_id	= 0;
	// The operation type(result) of task
	_OPERATION_TYPE op_type = _OPT_ERR;

	// Get the task
	ITaskRef task = task_info->GetTask( );
	EGE_ASSERT( task.IsValid( ) );

	// It's task set
	if ( task_info->IsThreadTaskSetType( ) )
	{
		// Get the task set
		IThreadTaskSet* thread_task_set = task_info->GetThreadTaskSet( );
		EGE_ASSERT( thread_task_set != _null );

		// If the thread self is releasing now then terminate the thread worker
		while ( thread_pool->IsBreakingAllProcessions( ) == _false )
		{
			//!	The current sub-task index of task set
			_dword cur_sub_task_index = 0;

			// Get the task range
			DwordDataField sub_tasks_field;
			if ( task_info->GetTaskSetRange( cur_sub_task_index, sub_tasks_field ) == _false )
				break;

			// Process the tasks by range [ start_index, end_index )
			for ( _dword i = 0; i < sub_tasks_field.GetNumber( ); i ++ )
			{
				_dword index = sub_tasks_field.GetOffset( ) + i;

				op_type = thread_task_set->ProcessSubTask( thread_id, index, err_id );
				if ( op_type != ITask::_OPT_CONTINUE )
					break;
			}

			// Sleep awhile
			if ( sleep_time != -1 )
				Platform::Sleep( sleep_time );
		}
	}
	// It's single task
	else
	{
		// Get the thread task
		IThreadTask* thread_task = task_info->GetThreadTask( );
		EGE_ASSERT( thread_task != _null );

		// If the thread self is releasing now then terminate the thread worker
		while ( thread_pool->IsBreakingAllProcessions( ) == _false )
		{
			op_type = thread_task->OnProcess( thread_id, err_id );
			if ( op_type != ITask::_OPT_CONTINUE )
				break;

			// Sleep awhile
			if ( sleep_time != -1 )
				Platform::Sleep( sleep_time );
		}
	}

	// Make sure thread is safe
	LockOwner lock_owner( task_info->GetLock( ) );

	// Update task status
	switch ( op_type )
	{
		// Set the last error ID when it's failed
		case _OPT_ERR:
		{
			task->SetLastErrorID( err_id );
		}
		break;

		// Task finished 
		case _OPT_FINISH:
		{
			task->Finish( );
		}
		break;

		// Delay task 
		case _OPT_DELAY:
		{
			// The task will process again
			task->Wait( );
		}
		break;

		default:
			break;
	}

	// Enable to process it again, make sure only 1 thread process 1 task, so we create another 'enable' flag for it
	task_info->Enable( _true );
}

ITask::_OPERATION_TYPE ThreadTaskProcessor::OnProcess( _thread_id threadid, _dword& err_id )
{
	err_id = mProcessTaskFunc( );
	if ( err_id == 0 )
	{
		Finish( );
		return _OPT_FINISH;
	}
	else
	{
		Abort( );
		return _OPT_ERR;
	}
}
