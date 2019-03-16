//! @file     ResLoaderTask.cpp
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ResLoaderTask Implementation
//----------------------------------------------------------------------------

ResLoaderTask::ResLoaderTask( IResObject* res_obj, ResCaches* res_caches, IResLoaderFactory* factory )
{
	EGE_ASSERT( res_obj != _null );
	EGE_ASSERT( res_caches != _null );
	EGE_ASSERT( factory != _null );

	mResObj		= res_obj;
	mResState	= _RS_LOADING;

	mResCaches	= res_caches;

	mFactory	= factory;
}

ResLoaderTask::~ResLoaderTask( )
{
}

IStreamReaderPassRef ResLoaderTask::LoadResourceByName( WStringPtr res_name )
{
	// Check whether it's HTTP protocol
	_ubool is_http_protocol = mFactory->IsHTTPProtocol( res_name );
	if ( is_http_protocol )
	{
		WString url = mFactory->GetHTTPURL( res_name );

		IArchiveRef network_archive = mFactory->CreateHTTPArchive( url, _true );
		if ( network_archive.IsNull( ) )
			return _false;

		return network_archive->LoadResourceByName( url );
	}

	return GetWorkingArchive( )->LoadResourceByName( res_name );
}

ResLoaderTask::_RES_STATE ResLoaderTask::GetState( ) const
{
	return mResState;
}

const WStringObj& ResLoaderTask::GetResName( ) const
{
	EGE_ASSERT( mResObj.IsValid( ) );

	return mResObj->GetResName( );
}

_ubool ResLoaderTask::Load( )
{
	switch ( mResState )
	{
		// Loading resource object
		case _RS_LOADING:
		{
			IStreamReaderRef stream_reader = LoadResourceByName( GetResName( ) );
			if ( stream_reader.IsNull( ) )
				return _false;

			if ( mResObj->LoadResourcesFromLoader( stream_reader ) == _false )
			{
				mResObj.Clear( );

				mResState = _RS_ERROR;
				return _false;
			}
			else
			{
				// Still need to load some resources in main thread
				mResState = _RS_WAIT; 
			}
		}
		break;

		case _RS_WAIT:
		{
			EGE_ASSERT( Platform::IsMainThread( ) );

			if ( mResObj->LoadResourcesFromLoaderInMainThread( ) == _false )
			{
				mResObj.Clear( );

				mResState = _RS_ERROR;
				return _false;
			}
			else
			{
				mResState = _RS_LOADED;
			}
		}
		break;

		// Loaded resource object
		case _RS_LOADED:
		{
			// Update caches
			mResCaches->AddResObject( mResObj );

			// All done
			mResState = _RS_DONE;
		}
		break;

		default:
			break;
	}

	return _true;
}