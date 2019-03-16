//! @file     ResLoader.cpp
//! @author   foreven
//! @version  1.1
//! @date     2013.1.11
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ResLoader Implementation
//----------------------------------------------------------------------------

ResLoader::ResLoader( )
{

}

ResLoader::~ResLoader( )
{
}

IResObject* ResLoader::QueryDefaultResObj( _dword res_type, const WStringObj& res_name )
{
	IResObject* res_obj = mResCaches.GetDefaultResObj( res_type, res_name );
	if ( res_obj == _null )
		res_obj = mResCaches.GetDefaultResObjOfType( res_type );

	return res_obj;
}

_ubool ResLoader::Initialize( _dword thread_number, WStringPtr name, IResLoaderFactory* factory )
{
	mFactory = factory;
	if ( mFactory.IsNull( ) )
		return _false;

	// Create thread pool
	mThreadPool = GetInterfaceFactory( )->CreateThreadPool( thread_number, name );
	if ( mThreadPool.IsNull( ) )
		return _false;

	return _true;
}

_void ResLoader::Tick( _dword limited_elapse, _dword elapse )
{
	LockOwner lock_owner( mLock );

	for ( ResLoaderTaskGroupMap::Iterator it = mTaskGroups.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		ResLoaderTaskGroup& task_group = it.GetObject( );

		task_group.ProcessInMainThread( );
	}
}

_ubool ResLoader::IsBusy( ) const
{
	return mThreadPool->IsBusy( );	
}

_ubool ResLoader::HasComplete( ) const
{
	DwordProgression progression = GetTaskProgression( );

	return progression.HasCompleted( );
}

IResLoaderFactory* ResLoader::GetFactory( )
{
	return mFactory;
}

_void ResLoader::EnterLock( )
{
	mThreadPool->EnterLock( );
}

_void ResLoader::LeaveLock( )
{
	mThreadPool->LeaveLock( );
}

_void ResLoader::Start( )
{
	mThreadPool->Wakeup( );
}

_void ResLoader::Suspend( _ubool suspend )
{
	mThreadPool->Suspend( suspend );
}

_void ResLoader::SetDefaultResObj( IResObject* res_obj )
{
	LockOwner lock_owner( mLock );

	mResCaches.SetDefaultResObj( res_obj );
}

_void ResLoader::SetDefaultResObjOfType( IResObject* res_obj )
{
	LockOwner lock_owner( mLock );

	mResCaches.SetDefaultResObjOfType( res_obj );
}

IResObject* ResLoader::GetDefaultResObj( _dword res_type, const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	return QueryDefaultResObj( res_type, res_name );
}

IResObjectRef ResLoader::GetCachedResObj( _dword res_type, const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	IResObject* res_obj = mResCaches.GetResObject( res_type, res_name );
	if ( res_obj == _null )
		res_obj = mResCaches.GetDefaultResObjOfType( res_type );

	return res_obj;
}

IResObjectPassRef ResLoader::CreateResObj( _dword res_type, const WStringObj& res_name )
{
	mLock.Enter( );
	IResObject* res_obj = mResCaches.GetResObject( res_type, res_name );
	mLock.Leave( );

	if ( res_obj == _null )
	{
		if ( LoadResObj( res_type, res_name ) == _false )
			return _null;

		res_obj = mResCaches.GetResObject( res_type, res_name );
		if ( res_obj == _null )
			return _null;
	}
	else
	{
		if ( res_obj->AreAllResourcesLoaded( ) == _false )
			LoadResObj( res_type, res_name );
	}

	return res_obj->CloneToPassRef< IResObject >( _false );
}

_ubool ResLoader::LoadResObj( _dword res_type, const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	IResObject* res_obj = mResCaches.GetResObject( res_type, res_name );
	if ( res_obj == _null )
	{
		// Get the default resource object of type
		res_obj = QueryDefaultResObj( res_type, res_name );
		if ( res_obj == _null )
		{
			WLOG_ERROR_1( L"We must provide the default resource for '%s' object", res_name.Str( ) );
			return _null;
		}

		// Use standalone mode to create resource
		IResObjectPassRef cached_res_obj = res_obj->CloneToPassRef< IResObject >( _true );
		if ( cached_res_obj.IsNull( ) )
			return _null;

		res_obj = cached_res_obj.GetPtr( );
		res_obj->SetResName( res_name );

		mResCaches.AddResObject( res_obj );
	}

	ResLoaderTaskGroup& task_group = mTaskGroups[res_type];
	task_group.SetResType( res_type );
	task_group.SetResCaches( &mResCaches );

	task_group.AddResTask( res_obj, mFactory );

	if ( mThreadPool->AddTask( &task_group ) == _false )
		return _false;

	// Wait for start
	task_group.Wait( );

	Start( );

	return _true;
}

_void ResLoader::UnloadResObj( _dword res_type, const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	// Get the default resource object
	IResObjectRef default_res_obj = QueryDefaultResObj( res_type, res_name );
	if ( default_res_obj.IsNull( ) )
		return;

	// Get the cached resource object
	IResObjectRef cached_res_obj = mResCaches.GetResObject( res_type, res_name );
	if ( cached_res_obj.IsNull( ) )
		return;

	// Use the default resource object to unload it
	cached_res_obj->UnloadResourcesFromLoader( default_res_obj );
}

_ubool ResLoader::BringUpResObj( _dword res_type, const WStringObj& res_name )
{
	LockOwner lock_owner( mLock );

	ResLoaderTaskGroup& task_group = mTaskGroups[res_type];
	task_group.SetResType( res_type );
	task_group.SetResCaches( &mResCaches );

	return task_group.BringUpResTask( res_name );
}

_void ResLoader::StopAllResObjsLoading( )
{
	LockOwner lock_owner( mLock );

	mTaskGroups.Clear( );
}

Array< IResObjectRef > ResLoader::GetResObjCaches( _dword res_type ) const
{
	LockOwner lock_owner( mLock );

	return mResCaches.GetResObjCaches( res_type );
}

DwordProgression ResLoader::GetTaskProgression( ) const
{
	DwordProgression progression = DwordProgression::cNull;

	for ( ResLoaderTaskGroupMap::Iterator it = mTaskGroups.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		ResLoaderTaskGroup& task_group = it.GetObject( );

		progression += task_group.GetTaskProgression( );
	}

	return progression;
}
