//! @file     _curlMultiHandle.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// _curlMultiHandle Implementation
//----------------------------------------------------------------------------

_curlMultiHandle::_curlMultiHandle( )
{
	// Initialize the cURL multi-thread handle
	mURLMultiHandle = ::curl_multi_init( );
	EGE_ASSERT( mURLMultiHandle != _null );
}

_curlMultiHandle::~_curlMultiHandle( )
{
	if ( mURLMultiHandle != _null )
	{
		// Remove the cURL handle from the multi-thread handle
		for ( _dword i = 0; i < mURLHandles.Number( ); i ++ )
		{
			::curl_multi_remove_handle( mURLMultiHandle, mURLHandles[i]->GetSessionHandle( ) );

			// Notify outside we have removed
			mRemoveRequestFunc.Invoke( mURLHandles[i] );
		}

		// Cleanup the cURL multi-thread handle
		::curl_multi_cleanup( mURLMultiHandle );
	}
}

_curlHandle* _curlMultiHandle::GetURLHandle( CURL* handle )
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mURLHandles.Number( ); i ++ )
	{
		if ( mURLHandles[i]->GetSessionHandle( ) == handle )
			return mURLHandles[i];
	}

	return _null;
}

_void _curlMultiHandle::RemoveURLHandle( _curlHandle* handle )
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mURLHandles.Number( ); i ++ )
	{
		if ( mURLHandles[i] == handle )
		{
			::curl_multi_remove_handle( mURLMultiHandle, mURLHandles[i]->GetSessionHandle( ) );

			mURLHandles.RemoveByIndex( i );
			break;
		}
	}
}

_void _curlMultiHandle::RegisterFinishRequestFunc( OnFinishRequest func, const QwordParameters2& parameters )
{
	mFinishRequestFunc.Init( func, parameters );
}

_void _curlMultiHandle::RegisterRemoveRequestFunc( OnRemoveRequest func, const QwordParameters2& parameters )
{
	mRemoveRequestFunc.Init( func, parameters );
}

_void _curlMultiHandle::AppendURLHandle( _curlHandle* url_handle )
{
	if ( url_handle == _null )
		return;

	LockOwner lock_owner( mLock );

	mURLHandles.Append( url_handle );

	::curl_multi_add_handle( mURLMultiHandle, url_handle->GetSessionHandle( ) );
}

_void _curlMultiHandle::Perform( )
{
	if ( mURLHandles.Number( ) == 0 )
		return;

	// Perform multiple operations
	_int running_handles = 0;
	while ( CURLM_CALL_MULTI_PERFORM == ::curl_multi_perform( mURLMultiHandle, &running_handles ) );

	// Get URL message info
	while ( _true )
	{
		// Read the URL message info
		_int msgs_in_queue = 0;
		CURLMsg* curl_msg = ::curl_multi_info_read( mURLMultiHandle, &msgs_in_queue );
		if ( curl_msg == _null )
			break;

		// Get the URL handle to set error ID
		_curlHandle* url_handle = GetURLHandle( curl_msg->easy_handle );
		EGE_ASSERT( url_handle != _null );

		// Only work with finished operation
		if ( curl_msg->msg == CURLMSG_DONE )
		{
			url_handle->SetLastErrorID( curl_msg->data.result );

			// Notify outside we have finished
			mFinishRequestFunc.Invoke( url_handle );

			// Remove it from request queue
			RemoveURLHandle( url_handle );

			// Notify outside we have removed
			mRemoveRequestFunc.Invoke( url_handle );
		}
	}
}

#endif