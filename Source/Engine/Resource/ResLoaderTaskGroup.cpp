//! @file     ResLoaderTaskGroup.cpp
//! @author   foreven
//! @version  1.1
//! @date     2013.1.11
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ResLoaderTaskGroup Implementation
//----------------------------------------------------------------------------

ResLoaderTaskGroup::ResLoaderTaskGroup( )
{
	mResType		= 0;
	mResCaches		= _null;

	mProgression	= DwordProgression::cNull;

	SetFlags( ITask::_FLAG_AUTO_START );
}

ResLoaderTaskGroup::~ResLoaderTaskGroup( )
{
	for ( _dword i = 0; i < mTasks.Number( ); i ++ )
	{
		EGE_DELETE( mTasks[i] );
	}
}

template< typename Type >
_ubool ResLoaderTaskGroup::BringUpResTask( Type& tasks, const WStringObj& res_name )
{
	for ( Type::Iterator it = tasks.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		ResLoaderTask* task = it;

		if ( task->GetResName( ) == res_name )
		{
			tasks.Remove( it );
			tasks.EnqueueAtFront( task );
			return _true;
		}
	}

	return _false;
}

template< typename Type >
_ubool ResLoaderTaskGroup::HasResTask( const Type& tasks, const WStringObj& res_name ) const
{
	for ( _dword i = 0; i < tasks.Number( ); i ++ )
	{
		if ( tasks[i]->GetResName( ) == res_name )
			return _true;
	}

	return _false;
}

IThreadTask::_OPERATION_TYPE ResLoaderTaskGroup::OnProcess( _thread_id threadid, _dword& err_id )
{
	if ( mTasksInBackground.Number( ) == 0 )
		return _OPT_FINISH;

	mLock.Enter( );
	ResLoaderTask* task = _null;
	mTasksInBackground.Dequeue( task );
	mLock.Leave( );

	if ( task == _null )
		return _OPT_FINISH;

	task->Load( );

	// Get the task state
	ResLoaderTask::_RES_STATE res_state = task->GetState( );

	// continue to process task
	switch ( res_state )
	{
		// Let the task to be processed in main thread
		case ResLoaderTask::_RS_WAIT:
		{
			mLock.Enter( );
			mTasks.Enqueue( task );
			mLock.Leave( );
		}
		break;

		case ResLoaderTask::_RS_LOADING:
		case ResLoaderTask::_RS_LOADED:
		{
			mLock.Enter( );
			mTasksInBackground.Enqueue( task );
			mLock.Leave( );
		}
		break;

		case ResLoaderTask::_RS_DONE:
		{
			mProgression.UpdateCurProgression( 1 );
		}
		break;

		case ResLoaderTask::_RS_ERROR:
		{
			EGE_DELETE( task );
		}
		break;

		default:
			break;
	}

	return _OPT_CONTINUE;
}

_void ResLoaderTaskGroup::SetResType( _dword res_type )
{
	mResType = res_type;
}

_void ResLoaderTaskGroup::SetResCaches( ResCaches* caches )
{
	mResCaches = caches;
}

_void ResLoaderTaskGroup::ProcessInMainThread( )
{
	if ( mTasks.Number( ) == 0 )
		return;

	mLock.Enter( );
	ResLoaderTask* task = _null;
	mTasks.Dequeue( task );
	mLock.Leave( );

	if ( task == _null )
		return;
	
	// Get the task state
	ResLoaderTask::_RES_STATE res_state = task->GetState( );

	// Load resources in main thread
	if ( res_state == ResLoaderTask::_RS_WAIT )
		task->Load( );

	EGE_DELETE( task );

	mProgression.UpdateCurProgression( 1 );
}

_ubool ResLoaderTaskGroup::AddResTask( IResObject* res_obj, IResLoaderFactory* factory )
{
	if ( HasResTask( res_obj->GetResName( ) ) )
		return _true;

	mLock.Enter( );
	{
		mTasksInBackground.Enqueue( new ResLoaderTask( res_obj, mResCaches, factory ) );
		mProgression.UpdateMaxProgression( 1 );
	}
	mLock.Leave( );

	return _true;
}

_ubool ResLoaderTaskGroup::HasResTask( const WStringObj& res_name ) const
{
	LockOwner lock_owner( mLock );

	if ( HasResTask( mTasksInBackground, res_name ) )
		return _true;

	if ( HasResTask( mTasks, res_name ) )
		return _true;

	return _false;
}

_ubool ResLoaderTaskGroup::BringUpResTask( const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	if ( BringUpResTask( mTasksInBackground, res_name ) )
		return _true;

	if ( BringUpResTask( mTasks, res_name ) )
		return _true;

	return _false;
}

const DwordProgression& ResLoaderTaskGroup::GetTaskProgression( ) const
{
	return mProgression;
}
