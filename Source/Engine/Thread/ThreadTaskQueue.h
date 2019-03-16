//! @file     ThreadTaskQueue.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ThreadTaskInfo
//----------------------------------------------------------------------------

class ThreadTaskInfo : public TObject< IObject >
{
private:
	//!	The flags
	enum _FLAG
	{
		//!	True indicates enable it
		_FLAG_ENABLE		= 1 << 0,
		//!	True indicates it's task set type
		_FLAG_TASK_SET_TYPE	= 1 << 1,
	};

private:
	//!	The flags
	FlagsObject	mFlags;

	//!	The locker
	Lock&		mLock;

	//!	The task
	ITaskRef	mTask;

public:
	ThreadTaskInfo( Lock& lock, IThreadTask* task );
	ThreadTaskInfo( Lock& lock, IThreadTaskSet* task_set );
	virtual ~ThreadTaskInfo( );

public:
	EGE_GETR_ACCESSOR( Lock, Lock )

public:
	//!	Enable or disable it.
	_void Enable( _ubool enable );
	//!	Check whether enable or disable.
	_ubool IsEnable( ) const;

	//!	Check whether it's thread task set type.
	_ubool IsThreadTaskSetType( ) const;

	//!	Get the task.
	ITask* GetTask( );
	const ITask* GetTask( ) const;

	//!	Get the thread task.
	IThreadTask* GetThreadTask( );
	const IThreadTask* GetThreadTask( ) const;

	//!	Get the thread task set.
	IThreadTaskSet* GetThreadTaskSet( );
	const IThreadTaskSet* GetThreadTaskSet( ) const;

	//!	Check whether it's waiting task.
	_ubool IsWaiting( ) const;
	//!	Check whether it's suspended task.
	_ubool IsSuspended( ) const;
	//!	Check whether it's running task.
	_ubool IsRunning( ) const;
	//!	Check whether it's dead task.
	_ubool IsDead( ) const;

	//!	Finish.
	_ubool Finish( );

	//!	Get the task set work range [start_index, end_index).
	//!	@param		cur_index		The current index of task.
	//!	@param		sub_tasks_field	The sub-tasks field.
	//!	@return		True indicates we still have some unprocessed task, false indicates all the tasks had been processed.
	_ubool GetTaskSetRange( _dword& cur_index, DwordDataField& sub_tasks_field ) const;
};

//----------------------------------------------------------------------------
// ThreadTaskQueue
//----------------------------------------------------------------------------

class ThreadTaskQueue
{
private:
	typedef Array< ThreadTaskInfo* > TaskArray;

private:
	//!	The locker
	Lock&		mLock;

	//!	The current task index
	_dword		mTaskIndex;
	//!	The tasks
	TaskArray	mTasks;

public:
	ThreadTaskQueue( Lock& lock );
	virtual ~ThreadTaskQueue( );

public:
	//!	Get the first unfinished task from queue.
	//!	@param		none.
	//!	@return		Null-Ref indicates no-any more unfinished tasks, otherwise indicates get unfinished task successful.
	ThreadTaskInfo* GetTask( );

	//!	Get tasks number.
	_dword GetTaskNumber( ) const;
	//!	Add the task into queue.
	_void AddTask( IThreadTask* task );
	//!	Add the task set into queue.
	_void AddTaskSet( IThreadTaskSet* taskset );
	//!	Remove task.
	_void RemoveTask( IThreadTask* task );
	//!	Remove all tasks.
	_void RemoveAllTasks( );
};

//----------------------------------------------------------------------------
// ThreadTaskQueue Implementation
//----------------------------------------------------------------------------

}