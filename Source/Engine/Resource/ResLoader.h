//! @file     ResLoader.h
//! @author   foreven
//! @version  
//! @date     2012/05/15

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ResLoader
//----------------------------------------------------------------------------

class ResLoader : public TObject< IResLoader >
{
private:
	//!	Use the resource type as key.
	typedef Map< ResLoaderTaskGroup, _dword > ResLoaderTaskGroupMap;

private:
	//!	The thread lock
	Lock					mLock;

	//!	The thread pool
	IThreadPoolRef			mThreadPool;

	//!	The resource caches
	ResCaches				mResCaches;
	//!	The task groups
	ResLoaderTaskGroupMap	mTaskGroups;

	//!	The loader factory
	IResLoaderFactoryRef	mFactory;

private:
	IResObject*	QueryDefaultResObj( _dword res_type, const WStringObj& res_name );

public:
	ResLoader( );
	virtual ~ResLoader( );

public:
	_ubool Initialize( _dword thread_number, WStringPtr name, IResLoaderFactory* factory );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;

// IResLoader Interface
public:
	virtual _ubool					IsBusy( ) const override;

	virtual _ubool					HasComplete( ) const override;

	virtual IResLoaderFactory*		GetFactory( ) override;

	virtual _void					EnterLock( ) override;
	virtual _void					LeaveLock( ) override;

	virtual _void					Start( ) override;
	virtual _void					Suspend( _ubool suspend ) override;

	virtual _void					SetDefaultResObj( IResObject* res_obj ) override;
	virtual _void					SetDefaultResObjOfType( IResObject* res_obj ) override;
	virtual IResObject*				GetDefaultResObj( _dword res_type, const WStringObj& res_name ) override;

	virtual IResObjectRef			GetCachedResObj( _dword res_type, const WStringObj& res_name ) override;

	virtual IResObjectPassRef		CreateResObj( _dword res_type, const WStringObj& res_name ) override;
	virtual _ubool					LoadResObj( _dword res_type, const WStringObj& res_name ) override;
	virtual _void					UnloadResObj( _dword res_type, const WStringObj& res_name ) override;
	virtual _ubool					BringUpResObj( _dword res_type, const WStringObj& res_name ) override;
	virtual _void					StopAllResObjsLoading( ) override;

	virtual Array< IResObjectRef >	GetResObjCaches( _dword res_type ) const override;

	virtual DwordProgression		GetTaskProgression( ) const override;
};

}