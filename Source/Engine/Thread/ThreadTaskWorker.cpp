//! @file     ThreadTaskWorker.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ThreadTaskWorker Implementation
//----------------------------------------------------------------------------

ThreadTaskWorker::ThreadTaskWorker( )
{
	mIsBusy				= _false;

	mSleepTime			= -1;

	mThreadWakeEvent	= _null;

	mThreadPool			= _null;
}

ThreadTaskWorker::~ThreadTaskWorker( )
{
	// We are releasing now
	mThreadID = 0;

	// Wake up
	if ( mThreadWakeEvent != _null )
		mThreadWakeEvent->Set( );

	// Close the thread
	BaseClass::Close( );
}

_dword ThreadTaskWorker::OnRunThread( const QwordParams2& params )
{
	ThreadTaskWorker* _self = (ThreadTaskWorker*) params[0];
	EGE_ASSERT( _self != _null );

	while ( _true )
	{
		// Prepare to start doing work
		mIsBusy = _false;

		// Wait for the wake event from the pool
		_self->mThreadWakeEvent->Wait( );

		// If the thread self is releasing now then terminate the thread worker
		if ( BaseClass::IsReleasing( ) )
			break;

		// If thread pool is releasing then terminate the thread worker
		if ( _self->mThreadPool->IsBreakingAllProcessions( ) )
			break;

		// Query for the task queue
		RefPtr< ThreadTaskInfo > task_info = _self->mThreadPool->GetThreadTaskQueue( )->GetTask( );
		if ( task_info.IsValid( ) )
		{
			// Start to work now
			mIsBusy = _true;

			// Process thread task
			ThreadTaskProcessor::ProcessTask( BaseClass::GetThreadID( ), mSleepTime, task_info, mThreadPool );
		}
		else
		{
			// The thread worker be going to sleep if no any works need to do
			_self->mThreadWakeEvent->Reset( );
		}
	}

	// Exit the thread
	return EXIT_SUCCESS;
}

_void ThreadTaskWorker::OnCloseThread( _dword exitcode, const QwordParams2& params )
{

}

_ubool ThreadTaskWorker::Initialize( WStringPtr name, EventObject* wait_event, ThreadPool* thread_pool )
{
	if ( wait_event == _null || thread_pool == _null )
		return _false;

	mThreadWakeEvent	= wait_event;

	mThreadPool			= thread_pool;

	if ( BaseClass::Create( 0, _false, name, QwordParams2( (_qword)this, _null ) ) == _false )
		return _false;

	return _true;
}
