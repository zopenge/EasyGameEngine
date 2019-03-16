//! @file     ResLoaderTaskGroup.h
//! @author   foreven
//! @version  
//! @date     2012/05/15

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ResLoaderTaskGroup
//----------------------------------------------------------------------------

class ResLoaderTaskGroup : public TTask< TObject< IThreadTask > >
{
private:
	typedef Queue< ResLoaderTask* > ResLoaderTaskPtrQueue;

private:
	Lock					mLock;

	_dword					mResType;

	ResCaches*				mResCaches;

	ResLoaderTaskPtrQueue	mTasksInBackground;
	ResLoaderTaskPtrQueue	mTasks;

	DwordProgression		mProgression;

private:
	template< typename Type >
	_ubool BringUpResTask( Type& tasks, const WStringObj& res_name );

	template< typename Type >
	_ubool HasResTask( const Type& tasks, const WStringObj& res_name ) const;

public:
	ResLoaderTaskGroup( );
	virtual ~ResLoaderTaskGroup( );

// IThreadTask Interface
public:
	virtual _OPERATION_TYPE OnProcess( _thread_id threadid, _dword& err_id ) override;

public:
	//!	Set the resource type.
	_void SetResType( _dword res_type );
	//!	Set the resource caches.
	_void SetResCaches( ResCaches* caches );

	//!	Process in main thread.
	_void ProcessInMainThread( );

	//!	Process resource task.
	_ubool AddResTask( IResObject* res_obj, IResLoaderFactory* factory );
	_ubool HasResTask( const WStringObj& res_name ) const;
	_ubool BringUpResTask( const WStringObj& res_name );

	//!	Get task progression.
	const DwordProgression& GetTaskProgression( ) const;
};

}