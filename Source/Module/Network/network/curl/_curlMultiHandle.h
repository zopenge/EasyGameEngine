//! @file     _curlMultiHandle.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _curlMultiHandle
//----------------------------------------------------------------------------

class _curlMultiHandle
{
private:
	//!	When finish request.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	typedef _void (*OnFinishRequest)( _curlHandle* url_handle, const QwordParameters2& parameters );
	//!	When remove request.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	typedef _void (*OnRemoveRequest)( _curlHandle* url_handle, const QwordParameters2& parameters );

private:
	typedef CallbackFunc< OnFinishRequest, _ubool, QwordParameters2 > FinishRequestFunc;
	typedef CallbackFunc< OnRemoveRequest, _void, QwordParameters2 > RemoveRequestFunc;

	typedef Array< _curlHandle* > URLHandleArray;

private:
	//!	The thread lock
	Lock				mLock;

	//!	The cURL multi-thread handle
	CURLM*				mURLMultiHandle;
	//!	The cURL handle array of multi-thread operation
	URLHandleArray		mURLHandles;

	//!	The callback functions
	FinishRequestFunc	mFinishRequestFunc;
	RemoveRequestFunc	mRemoveRequestFunc;

private:
	//!	Get the URL handle.
	_curlHandle* GetURLHandle( CURL* handle );
	//!	Remove the URL handle.
	_void RemoveURLHandle( _curlHandle* handle );

public:
	_curlMultiHandle( );
	~_curlMultiHandle( );

public:
	//!	Get the cURL multi-thread handle.
	EGE_GET_ACCESSOR( CURLM*, URLMultiHandle )

public:
	//!	Register callback functions.
	_void RegisterFinishRequestFunc( OnFinishRequest func, const QwordParameters2& parameters );
	_void RegisterRemoveRequestFunc( OnRemoveRequest func, const QwordParameters2& parameters );

	//!	Append URL handle.
	_void AppendURLHandle( _curlHandle* url_handle );

	//!	Perform.
	_void Perform( );
};

//----------------------------------------------------------------------------
// _curlMultiHandle Implementation
//----------------------------------------------------------------------------

}