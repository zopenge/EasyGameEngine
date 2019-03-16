//! @file     ResLoaderTask.h
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ResLoaderTask
//----------------------------------------------------------------------------

class ResLoaderTask
{
public:
	//!	The resource state
	enum _RES_STATE
	{
		_RS_UNKNOWN,	//!	Initial state
		_RS_ERROR,		//!	Error state
		_RS_LOADING,	//!	Loading state
		_RS_WAIT,		//!	Wait for Loading resources in main thread state
		_RS_LOADED,		//!	Loaded/Finished state
		_RS_DONE,		//!	All done
	};

private:
	//!	The resource state.
	_RES_STATE				mResState;

	//!	The resource object
	IResObjectRef			mResObj;

	//!	The resource caches
	ResCaches*				mResCaches;

	//!	The loader factory
	IResLoaderFactoryRef	mFactory;

private:
	//!	Load resource.
	IStreamReaderPassRef LoadResourceByName( WStringPtr res_name );

public:
	ResLoaderTask( IResObject* res_obj, ResCaches* res_caches, IResLoaderFactory* factory );
	~ResLoaderTask( );

public:
	//!	Get the task state.
	_RES_STATE GetState( ) const;
	//!	Get the resource name.
	const WStringObj& GetResName( ) const;

	//!	Load.
	_ubool Load( );
};

//----------------------------------------------------------------------------
// ResLoaderTask Implementation
//----------------------------------------------------------------------------

}