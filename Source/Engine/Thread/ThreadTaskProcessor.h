//! @file     ThreadTaskProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ThreadTaskProcessor
//----------------------------------------------------------------------------

//! A thread task processor to wrap callback function.
class ThreadTaskProcessor : public TTask< TFlagsObject< TObservable< TObject< IThreadTask > > > >
{
private:
	typedef TTask< TFlagsObject< TObservable< TObject< IThreadTask > > > > BaseClass;

private:
	//!	The task process callback function
	IThreadPool::OnProcessTask mProcessTaskFunc;

public:
	ThreadTaskProcessor( IThreadPool::OnProcessTask funcpointer );
	virtual ~ThreadTaskProcessor( );

public:
	//!	Process task.
	static _void ProcessTask( _thread_id thread_id, _dword sleep_time, ThreadTaskInfo* task_info, IThreadPool* thread_pool );

// IThreadTask Interface
public:
	virtual _OPERATION_TYPE OnProcess( _thread_id threadid, _dword& err_id ) override;
};

}