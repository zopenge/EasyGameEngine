//! @file     NetworkHTTPConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkHTTPConnection
//----------------------------------------------------------------------------

class NetworkHTTPConnection : public TNetworkHTTPConnection< INetworkHTTPConnection >
{
private:
	typedef TNetworkHTTPConnection< INetworkHTTPConnection > BaseClass;

private:
	//!	The request info
	struct RequestInfo : public BaseInfo
	{
		_ubool		mIsAsyncParallelMode;

		_dword		mTickcount;
		_dword		mTimeout;

		Time		mLastModifiedTime;

		_curlHandle	mHandle;

		_dword GetConnectTimeout( ) const
		{
			return mHandle.GetConnectTimeout( );
		}

		_dword GetTransferTimeout( ) const
		{
			return mHandle.GetTransferTimeout( );
		}

		_ubool IsTimeout( )
		{
			if ( mTimeout == -1 )
				return _false;

			_dword tickcount	= Platform::GetCurrentTickCount( );
			_ubool is_timeout	= tickcount - mTickcount >= mTimeout;

			mTimeout = tickcount;

			return is_timeout;
		}

		_void Abort( )
		{
			CombineFlags( BaseInfo::_FLAG_ABORT );

			mHandle.Abort( );
		}

		RequestInfo( )
		{
			mIsAsyncParallelMode	= _false;

			mTickcount				= 0;
			mTimeout				= 0;

			mLastModifiedTime		= Time::cNull;
		}
	};
	typedef Array< RequestInfo* > RequestInfoArray;

private:
	//!	The multiple URL handles.
	_curlMultiHandle*	mURLMultiHandle;

	//!	True indicates it's processing now
	_ubool				mIsProcessing;

	//!	The request info handles
	RequestInfoArray	mRequests;

private:
	//!	The CURLOPT_DEBUGFUNCTION callback function.
	static _int OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, size_t size, _void* userdata );
	//!	The CURLOPT_WRITEFUNCTION callback function.
	static _int OnWriteFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata );
	//!	The CURLOPT_READFUNCTION callback function.
	static _int OnReadFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata );
	//!	The CURLOPT_HEADERFUNCTION callback function.
	static _int OnHeaderFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata );
	//!	The CURLOPT_PROGRESSFUNCTION callback function.
	static _int OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow );

	//!	When async finish request.
	static _void OnFinishRequestCallback( _curlHandle* url_handle, const QwordParameters2& parameters );
	//!	When async remove request.
	static _void OnRemoveRequestCallback( _curlHandle* url_handle, const QwordParameters2& parameters );

private:
	//!	Create request info.
	RequestInfo* CreateRequestInfo( AStringPtr url_name, const QwordParameters4& parameters );
	RequestInfo* CreateRequestInfo( _ubool post, _ubool no_body, AStringPtr url_name, const AStringArray& header_list, const QwordParameters4& parameters, AString& url_address );
	RequestInfo* CreateRequestInfo( _ubool post, _ubool no_body, AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters );
	RequestInfo* CreateRequestInfo( _ubool no_body, AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters );

	//!	Process request.
	_ubool ProcessRequest( RequestInfo* request_info );
	//!	Remove request.
	_void RemoveRequest( RequestInfo* request_info );
	//!	Get request.
	RequestInfo* GetRequest( const _curlHandle* url_handle ) const;
	//!	Get sync request.
	RequestInfo* GetSyncRequest( );

	//!	Notify request result.
	_ubool NotifyRequestResult( const RequestInfo* request_info );

	//!	Process sync requests.
	_ubool ProcessSyncRequests( );
	//!	Process async requests.
	_void ProcessAsyncRequests( );

	//!	Initialize multiple URL handle.
	_void InitMultipleURLHandle( );

public:
	NetworkHTTPConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkHTTPConnection( );

// IFlagsObject Interface
public:
	virtual _void						EnableFlags( _dword flags, _ubool enable ) override;
	virtual _void						CombineFlags( _dword flags ) override;

	virtual _void						SetFlags( _dword flags ) override;

// IObject Interface
public:
	virtual _void						Tick( _dword limited_elapse, _dword elapse ) override;

// INetworkConnection Interface
public:
	virtual _ubool						IsBusy( ) const override;

	virtual _void						Stop( ) override;

	virtual _ubool						IsRemoteFileExist( WStringPtr filename ) override;
	virtual _ubool						GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time ) override;
	virtual INetworkStreamReaderPassRef	OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual _void						ProcessDelayConnectOperations( ) override;
	virtual _void						ProcessDelaySendOperations( ) override;
	virtual _void						ProcessDelayRecvOperations( ) override;

// INetworkHTTPConnection Interface
public:
	virtual _ubool						Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr get_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool						GetWithNoBody( AStringPtr url_name ) override;

	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters ) override;
	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
};

//----------------------------------------------------------------------------
// NetworkHTTPConnection Implementation
//----------------------------------------------------------------------------

}