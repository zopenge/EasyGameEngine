//! @file     NetworkHTTPConnection.curl.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// NetworkHTTPConnection Implementation
//----------------------------------------------------------------------------

NetworkHTTPConnection::NetworkHTTPConnection( INetworkConnectionThread* connection_thread ) : BaseClass( connection_thread )
{
	mURLMultiHandle = _null;

	mIsProcessing	= _false;

	// Set the default value of connection
	SetConnectTimeout( 10 SEC );
}

NetworkHTTPConnection::~NetworkHTTPConnection( )
{
	Stop( );
}

_int NetworkHTTPConnection::OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, size_t size, _void* userdata )
{
	// Get the info
	RequestInfo* request_info = (RequestInfo*) userdata;
	EGE_ASSERT( request_info != _null );

	// Whether abort it
	if ( request_info->IsAbort( ) || request_info->IsTimeout( ) || gNetworkModule->IsPowerOff( ) )
	{
		WLOG_ERROR( L"Abort HTTP connection by debug callback function" );
		return 0;
	}

	// Get the connection
	INetworkHTTPConnection* http_connection = request_info->mHTTPConnection;
	EGE_ASSERT( http_connection != _null );

	// Tell the user we receive data
	if ( request_info->HasNotifier( ) )
		http_connection->GetNotifier( )->OnDebugBuffer( _curlHelper::TranslateDebugType( type ), buffer, (_dword)size, request_info->mParameters );

	// Show debug info
	if ( type == CURLINFO_TEXT )
	{
		AString string( buffer, (_dword)size );
		ALOG_TRACE_1( "HTTP debug info: '%s'", string.Str( ) );
	}

	// Feedback the total bytes	
	return (_dword)size;
}

_int NetworkHTTPConnection::OnWriteFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata )
{
	// Get the info
	RequestInfo* request_info = (RequestInfo*) userdata;
	EGE_ASSERT( request_info != _null );

	// Whether abort it
	if ( request_info->IsAbort( ) || request_info->IsTimeout( ) || gNetworkModule->IsPowerOff( ) )
	{
		WLOG_ERROR( L"Abort HTTP connection by write callback function" );
		return 0;
	}

	// Get the connection
	INetworkHTTPConnection* http_connection = request_info->mHTTPConnection;
	EGE_ASSERT( http_connection != _null );

	// Get the total size
	_int total_size = (_int)(size * number);

	// Start to process with the received buffer data
	if ( request_info->HasNotifier( ) )
	{
		// Create stream to receive buffer data
		if ( request_info->mRecvBuffer.IsNull( ) )
			request_info->mRecvBuffer = GetInterfaceFactory( )->CreateMemStreamWriter( total_size );

		// Get the stream buffer
		IStreamWriter* stream = request_info->mRecvBuffer;
		EGE_ASSERT( stream != _null );

		// Receive buffer data
		stream->WriteBuffer( buffer, total_size );

		while ( stream->GetOffset( ) != 0 )
		{
			// Let the notifier to process data
			_dword processed_size = http_connection->GetNotifier( )->OnRecvBuffer( stream->GetOffset( ), stream->GetBuffer( ), request_info->mParameters );
			if ( processed_size == -1 )
			{
				WLOG_ERROR( L"Abort HTTP connection by notifier callback function" );
				return 0;
			}
			else if ( processed_size != 0 )
			{
				// Remove processed buffer data from stream
				_dword removed_size = stream->RemoveBuffer( processed_size );
				if ( removed_size != processed_size )
				{
					WLOG_ERROR_2( L"Abort HTTP connection by remove buffer failed, try to remove '%d' size (actual removed '%d' size)", processed_size, removed_size );
					return 0;
				}
			}
			else
			{
				// Finished it, or maybe we still need to wait for the received buffer comes
				break;
			}
		}
	}

	// Update the total download size
	GetNetworkModule( )->UpdateTotalDownloadBytes( total_size );

	// Feedback the total bytes	
	return total_size;
}

_int NetworkHTTPConnection::OnReadFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata )
{
	// Get the info
	RequestInfo* request_info = (RequestInfo*) userdata;
	EGE_ASSERT( request_info != _null );

	// Whether abort it
	if ( request_info->IsAbort( ) || request_info->IsTimeout( ) || gNetworkModule->IsPowerOff( ) )
	{
		WLOG_ERROR( L"Abort HTTP connection by read callback function" );
		return CURL_READFUNC_ABORT;
	}

	// Get the connection
	INetworkHTTPConnection* http_connection = request_info->mHTTPConnection;
	EGE_ASSERT( http_connection != _null );

	// Get the total size
	_int total_size = (_int)(size * number);

	// Tell the user we send data
	if ( request_info->HasNotifier( ) )
		http_connection->GetNotifier( )->OnSendBuffer( total_size, (const _byte*) buffer, request_info->mParameters );

	// Update the total upload size
	GetNetworkModule( )->UpdateTotalUploadBytes( total_size );

	// Feedback the total bytes
	return total_size;
}

_int NetworkHTTPConnection::OnHeaderFunctionCallback( _chara* buffer, size_t size, size_t number, _void* userdata )
{
	// Get the info
	RequestInfo* request_info = (RequestInfo*) userdata;
	EGE_ASSERT( request_info != _null );

	// Whether abort it
	if ( request_info->IsAbort( ) || request_info->IsTimeout( ) || gNetworkModule->IsPowerOff( ) )
	{
		WLOG_ERROR( L"Abort HTTP connection by header callback function" );
		return 0;
	}

	// Get the connection
	INetworkHTTPConnection* http_connection = request_info->mHTTPConnection;
	EGE_ASSERT( http_connection != _null );

	// Get the total bytes
	_dword total_size = (_dword)(size * number);

	// Build ANSI string
	AString string( buffer, total_size );

	// It's 'Date' section
	if ( string.StartsWith( "Date: " ) )
		http_connection->SetRequestTime( Time::GetTimeFromHTTPGMTTimeFormat( string ) );
	else if ( string.StartsWith( "Last-Modified: " ) )
		request_info->mLastModifiedTime = Time::GetTimeFromHTTPGMTTimeFormat( string );

	// Tell the user we receive header info data
	if ( request_info->HasNotifier( ) )
		http_connection->GetNotifier( )->OnHeaderBuffer( total_size, buffer, request_info->mParameters );

	// Update the total download size
	GetNetworkModule( )->UpdateTotalDownloadBytes( total_size );

	// Feedback the total bytes
	return total_size;
}

_int NetworkHTTPConnection::OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow )
{
	// Get the info
	RequestInfo* request_info = (RequestInfo*) userdata;
	EGE_ASSERT( request_info != _null );

	// Whether abort it
	if ( request_info->IsAbort( ) || request_info->IsTimeout( ) || gNetworkModule->IsPowerOff( ) )
	{
		WLOG_ERROR( L"Abort HTTP connection by progress callback function" );
		return -1;
	}

	// Get the connection
	INetworkHTTPConnection* http_connection = request_info->mHTTPConnection;
	EGE_ASSERT( http_connection != _null );

	// Tell the user we have transferring data
	if ( request_info->HasNotifier( ) )
		http_connection->GetNotifier( )->OnProgressBuffer( dltotal, dlnow, ultotal, ulnow, request_info->mParameters );

	// No error
	return 0;
}

_void NetworkHTTPConnection::OnFinishRequestCallback( _curlHandle* url_handle, const QwordParameters2& parameters )
{
	NetworkHTTPConnection* connection = (NetworkHTTPConnection*) parameters[0];
	EGE_ASSERT( connection != _null );

	// Get the request info
	const RequestInfo* request_info = connection->GetRequest( url_handle );
	EGE_ASSERT( request_info != _null );

	// Notify request result
	connection->NotifyRequestResult( request_info );

	// Perform HTTP finished
	ALOG_TRACE_1( "Perform HTTP request (url: '%s') DONE", request_info->mURLName.Str( ) );
}

_void NetworkHTTPConnection::OnRemoveRequestCallback( _curlHandle* url_handle, const QwordParameters2& parameters )
{
	NetworkHTTPConnection* connection = (NetworkHTTPConnection*)parameters[0];
	EGE_ASSERT( connection != _null );

	// Get the request info
	RequestInfo* request_info = connection->GetRequest( url_handle );
	EGE_ASSERT( request_info != _null );

	// Remove request
	connection->RemoveRequest( request_info );
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::CreateRequestInfo( AStringPtr url_name, const QwordParameters4& parameters )
{
	LockOwner lock_owner( mLock );

	// Create request handle
	RequestInfo* request_info		= new RequestInfo( );
	request_info->mURLName			= FORMAT_ASTRING_3( "%s:%d/%s", mRootURL.Str( ), GetRemoteAddress( ).mPort, url_name.Str( ) );
	request_info->mHTTPConnection	= this;
	request_info->mParameters		= parameters;
	request_info->mTickcount		= Platform::GetCurrentTickCount( );
	request_info->mTimeout			= mTransferTimeout;

	return request_info;
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::CreateRequestInfo( _ubool post, _ubool no_body, AStringPtr url_name, const AStringArray& header_list, const QwordParameters4& parameters, AString& url_address )
{
	// Create request handle
	RequestInfo* request_info = CreateRequestInfo( url_name, parameters );
	if ( request_info == _null )
		return _null;

	// Feedback the URL address
	url_address = _networkHelper::BuildURLAddress( IsEnableSSL( ), mRemoteAddress, mRootURL, url_name );

	// Get the URL handle
	_curlHandle& url_handle = request_info->mHandle;

	// Set the HTTP header
	url_handle.SetHTTPHeader( header_list );

	// Set the common info
	url_handle.SetOption( CURLOPT_POST, (_boolean) post );
	url_handle.SetOption( CURLOPT_NOBODY, (_boolean) no_body );
	url_handle.SetOption( CURLOPT_PORT, mRemoteAddress.mPort );
	// Use the location
	url_handle.SetOption( CURLOPT_FOLLOWLOCATION, _true );
	// Disable to use any signal/alarm handlers
	url_handle.SetOption( CURLOPT_NOSIGNAL, _true );
	// Forbid reuse connection
	url_handle.SetOption( CURLOPT_FORBID_REUSE, _true );

	// Set the timeout
	url_handle.SetConnectTimeout( mConnectTimeout );

	// Set the low speed limit
	if ( mLimitSpeedBytes != -1 )
	{
		url_handle.SetOption( CURLOPT_LOW_SPEED_LIMIT, mLimitSpeedBytes );
		url_handle.SetOption( CURLOPT_LOW_SPEED_TIME, 1L );
	}

	// Set the upload speed
	if ( mMaxUploadSpeed != -1 )
		url_handle.SetOption( CURLOPT_MAX_SEND_SPEED_LARGE, mMaxUploadSpeed );

	// Set the download speed
	if ( mMaxDownloadSpeed != -1 )
		url_handle.SetOption( CURLOPT_MAX_RECV_SPEED_LARGE, mMaxDownloadSpeed );

	// Bind 'CURLOPT_WRITEFUNCTION' callback function
	url_handle.SetOption( CURLOPT_WRITEDATA, request_info );
	url_handle.SetOption( CURLOPT_WRITEFUNCTION, OnWriteFunctionCallback );
	// Bind 'CURLOPT_READFUNCTION' callback function
	url_handle.SetOption( CURLOPT_READDATA, request_info );
	url_handle.SetOption( CURLOPT_READFUNCTION, OnReadFunctionCallback );
	// Bind 'CURLOPT_HEADERFUNCTION' callback function
	url_handle.SetOption( CURLOPT_HEADERDATA, request_info );
	url_handle.SetOption( CURLOPT_HEADERFUNCTION, OnHeaderFunctionCallback );
	// Bind 'CURLOPT_PROGRESSFUNCTION' callback function
	url_handle.SetOption( CURLOPT_NOPROGRESS, _false );
	url_handle.SetOption( CURLOPT_PROGRESSDATA, request_info );
	url_handle.SetOption( CURLOPT_PROGRESSFUNCTION, OnProgressFunctionCallback );
	// Bind 'CURLOPT_DEBUGFUNCTION' callback function
	url_handle.SetOption( CURLOPT_VERBOSE, _true );
	url_handle.SetOption( CURLOPT_DEBUGDATA, request_info );
	url_handle.SetOption( CURLOPT_DEBUGFUNCTION, OnDebugFunctionCallback );

	// Set the SSL options
	url_handle.SetSSLOptions( mSSLKeyFileName, mSSLCertFileName, mCACertFileName );

	return request_info;
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::CreateRequestInfo( _ubool post, _ubool no_body, AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters )
{
	// The URL address
	AString url_address;

	// Create request handle
	RequestInfo* request_info = CreateRequestInfo( post, no_body, url_name, header_list, parameters, url_address );
	if ( request_info == _null )
		return _null;

	// Get the URL handle
	_curlHandle& url_handle = request_info->mHandle;

	// Save data filed
	if ( data_field.IsEmpty( ) == _false )
	{
		// Use 'POST' method
		if ( post )
		{
			MemArrayPtr< _byte >& field_buffer = request_info->mFieldBuffer;

			// Copy the data filed buffer
			field_buffer.Create( data_field.GetLength( ), (const _byte*) data_field.Str( ) );

			// Set the post field data
			url_handle.SetOption( CURLOPT_POSTFIELDS, field_buffer.GetPointer( ) );
			url_handle.SetOption( CURLOPT_POSTFIELDSIZE, field_buffer.SizeOfBytes( ) );
		}
		// Use 'GET' method
		else
		{
			// Combine URL with filed data
			url_address += "?";
			url_address += data_field;
		}

		// Update URL name with data field
		request_info->mURLName += "?" + data_field;
	}

	// Set the URL address
	url_handle.SetURL( url_address );

	return request_info;
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::CreateRequestInfo( _ubool no_body, AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	// The URL address
	AString url_address;

	// Create request handle
	RequestInfo* request_info = CreateRequestInfo( _true, no_body, url_name, header_list, parameters, url_address );
	if ( request_info == _null )
		return _null;

	// Get the URL handle
	_curlHandle& url_handle = request_info->mHandle;

	// Get the field buffer
	MemArrayPtr< _byte >& field_buffer = request_info->mFieldBuffer;

	// Copy the data filed buffer
	field_buffer.Create( size, buffer );

	// Set the post field data
	url_handle.SetOption( CURLOPT_POSTFIELDS, field_buffer.GetPointer( ) );
	url_handle.SetOption( CURLOPT_POSTFIELDSIZE, field_buffer.SizeOfBytes( ) );

	// Set the URL address
	url_handle.SetURL( url_address );

	return request_info;
}

_void NetworkHTTPConnection::EnableFlags( _dword flags, _ubool enable )
{
	BaseClass::EnableFlags( flags, enable );

	if ( HasFlags( _FLAG_ASYNC_PARALLEL_MODE ) )
		InitMultipleURLHandle( );
}

_void NetworkHTTPConnection::CombineFlags( _dword flags )
{
	BaseClass::CombineFlags( flags );

	if ( HasFlags( _FLAG_ASYNC_PARALLEL_MODE ) )
		InitMultipleURLHandle( );
}

_void NetworkHTTPConnection::SetFlags( _dword flags )
{
	BaseClass::SetFlags( flags );

	if ( HasFlags( _FLAG_ASYNC_PARALLEL_MODE ) )
		InitMultipleURLHandle( );
}

_void NetworkHTTPConnection::Tick( _dword limited_elapse, _dword elapse )
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		// Check whether it's timeout
		if ( request_info->IsAbort( ) == _false && request_info->IsTimeout( ) )
		{
			// Build network error info
			NetworkErrorDesc err_desc;
			err_desc.mErrID		= _NET_ERROR_OPERATION_TIMEDOUT;
			err_desc.mErrDesc	= "Timeout actively";

			// Feedback the error ID by callback function
			mNotifier->OnError( err_desc, request_info->mParameters );

			// Show error log
			ALOG_ERROR_2( "Perform HTTP request (url: '%s', err: '%s') failed (ACTIVELY)", request_info->mURLName.Str( ), err_desc.mErrDesc.Str( ) );

			// Abort it
			request_info->Abort( );
		}
	}
}

_ubool NetworkHTTPConnection::IsBusy( ) const
{
	if ( BaseClass::IsBusy( ) )
		return _true;

	if ( mIsProcessing )
		return _true;

	if ( mRequests.Number( ) != 0 )
		return _true;

	return _false;
}

_void NetworkHTTPConnection::Stop( )
{
	LockOwner lock_owner( mLock );

	// Abort all requests
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		request_info->Abort( );
	}

	// Abort all multiple requests
	EGE_DELETE( mURLMultiHandle );

	// Remove all actions
	BaseClass::Stop( );

	// Cleanup all connections
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		EGE_DELETE( mRequests[i] );
	}
	mRequests.Clear( );
}

_ubool NetworkHTTPConnection::ProcessRequest( RequestInfo* request_info )
{
	EGE_ASSERT( request_info != _null );

	mLock.Enter( );
	{
		if ( HasFlags( _FLAG_ASYNC_PARALLEL_MODE ) )
		{
			request_info->mIsAsyncParallelMode = _true;
			mURLMultiHandle->AppendURLHandle( &request_info->mHandle );
		}

		mRequests.Append( request_info );
		ALOG_TRACE_2( "Add request (asnyc: %d, total: %d)", (_dword)request_info->mIsAsyncParallelMode, mRequests.Number( ) );
	}
	mLock.Leave( );

	if ( HasFlags( _FLAG_BLOCK_MODE ) )
	{
		if ( ProcessSyncRequests( ) == _false )
			return _false;
	}

	return _true;
}

_void NetworkHTTPConnection::RemoveRequest( RequestInfo* request_info )
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		if ( mRequests[i] == request_info )
		{
			EGE_DELETE( mRequests[i] );
			mRequests.RemoveByIndex( i );
			break;
		}
	}
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::GetRequest( const _curlHandle* url_handle ) const
{
	LockOwner lock_owner( mLock );

	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		if ( &mRequests[i]->mHandle == url_handle )
			return mRequests[i];
	}

	return _null;
}

NetworkHTTPConnection::RequestInfo* NetworkHTTPConnection::GetSyncRequest( )
{
	LockOwner lock_owner( mLock );

	if ( mRequests.Number( ) == 0 )
		return _null;

	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];

		if ( request_info->mIsAsyncParallelMode )
			continue;

		mRequests.RemoveByIndex( i );

		return request_info;
	}

	return _null;
}

_ubool NetworkHTTPConnection::NotifyRequestResult( const RequestInfo* request_info )
{
	EGE_ASSERT( request_info != _null );

	LockOwner lock_owner( mLock );

	// Get the last error ID
	CURLcode last_url_err_id = request_info->mHandle.GetLastErrorID( );
	if ( last_url_err_id != CURLE_OK )
	{
		// Build network error info
		NetworkErrorDesc err_desc;
		err_desc.mErrID		= _curlHelper::TranslateErrorType( last_url_err_id );
		err_desc.mErrDesc	= ::curl_easy_strerror( last_url_err_id );

		// Feedback the error ID by callback function
		mNotifier->OnError( err_desc, request_info->mParameters );

		// Show error log
		ALOG_ERROR_2( "Perform HTTP request (url: '%s', err: '%s') failed", request_info->mURLName.Str( ), err_desc.mErrDesc.Str( ) );

		return _false;
	}

	// Finish it
	mNotifier->OnFinishBuffer( request_info->mParameters );

	return _true;
}

_ubool NetworkHTTPConnection::ProcessSyncRequests( )
{
	_ubool ret = _true;

	// Process all requests
	while ( _true )
	{
		// Get the total request number
		_dword total_request_number = mRequests.Number( );
		if ( total_request_number == 0 )
			break;

		// Get the sync request info
		RequestInfo* request_info = GetSyncRequest( );
		if ( request_info == _null )
			break;

		// Fix the start tickcount for timeout
		request_info->mTickcount = Platform::GetCurrentTickCount( );

		// Will perform HTTP request
		ALOG_TRACE_4( "Perform HTTP request (url: '%s', connect_timeout: %d, timeout: %d) ... (remain: %d)", 
			request_info->mURLName.Str( ), request_info->GetConnectTimeout( ), request_info->GetTransferTimeout( ), total_request_number - 1 );

		// Perform HTTP request
		request_info->mHandle.PerformHTTP( );

		// Finish perform HTTP request
		ALOG_TRACE_5( "Perform HTTP request (url: '%s', connect_timeout: %d, timeout: %d) DONE (elapse: %d ms, remain: %d)", 
			request_info->mURLName.Str( ), request_info->GetConnectTimeout( ), request_info->GetTransferTimeout( ), Platform::GetCurrentTickCount( ) - request_info->mTickcount, total_request_number - 1 );

		// Notify request result
		ret &= NotifyRequestResult( request_info );

		// Release request
		EGE_DELETE( request_info );
	}

	return ret;
}

_void NetworkHTTPConnection::ProcessAsyncRequests( )
{
	if ( mURLMultiHandle == _null )
		return;

	mURLMultiHandle->Perform( );
}

_void NetworkHTTPConnection::InitMultipleURLHandle( )
{
	if ( mURLMultiHandle == _null )
	{
		mURLMultiHandle = new _curlMultiHandle( );
		mURLMultiHandle->RegisterFinishRequestFunc( OnFinishRequestCallback, QwordParameters2( (_qword)this, _null ) );
		mURLMultiHandle->RegisterRemoveRequestFunc( OnRemoveRequestCallback, QwordParameters2( (_qword)this, _null ) );
	}
}

_ubool NetworkHTTPConnection::IsRemoteFileExist( WStringPtr filename )
{
	if ( filename.IsEmpty( ) )
		return _false;

	// Build the URL address with the host URL
	AString remote_filename = _networkHelper::BuildURLAddress( IsEnableSSL( ), mRemoteAddress, mRootURL, AString( ).FromString( filename ) );
	if ( remote_filename.IsEmpty( ) )
		return _false;

	// Get the HTTP header info
	_curlHandle url_handle;
	// Set the port
	url_handle.SetOption( CURLOPT_PORT, mRemoteAddress.mPort );
	// Disable to use any signal/alarm handlers
	url_handle.SetOption( CURLOPT_NOSIGNAL, _true );
	// Doesn't need to send the body section
	url_handle.SetOption( CURLOPT_NOBODY, _true );
	// Use the location
	url_handle.SetOption( CURLOPT_FOLLOWLOCATION, _true );

	// Set the timeout
	url_handle.SetConnectTimeout( mConnectTimeout );

	// Set the URL address
	url_handle.SetURL( remote_filename );

	// Perform the URL handle options
	return url_handle.PerformHTTP( );
}

_ubool NetworkHTTPConnection::GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time )
{
	if ( filename.IsEmpty( ) )
		return _false;

	// Build the URL address with the host URL
	AString remote_filename = _networkHelper::BuildURLAddress( IsEnableSSL( ), mRemoteAddress, mRootURL, AString( ).FromString( filename ) );
	if ( remote_filename.IsEmpty( ) )
		return _false;

	// Create request info
	RequestInfo* request_info = CreateRequestInfo( remote_filename, QwordParameters4( (_qword)this ) );
	if ( request_info == _null )
		return _false;

	// Disable notifier 
	request_info->SetFlags( RequestInfo::_FLAG_DISABLE_NOTIFIER );

	// Get the HTTP header info
	_curlHandle url_handle;
	// Set the port number
	url_handle.SetOption( CURLOPT_PORT, mRemoteAddress.mPort );
	// Disable to use any signal/alarm handlers
	url_handle.SetOption( CURLOPT_NOSIGNAL, _true );
	// Doesn't need to send the body section
	url_handle.SetOption( CURLOPT_NOBODY, _true );
	// Use the location
	url_handle.SetOption( CURLOPT_FOLLOWLOCATION, _true );

	// Bind 'CURLOPT_WRITEFUNCTION' callback function
	url_handle.SetOption( CURLOPT_WRITEDATA, request_info );
	url_handle.SetOption( CURLOPT_WRITEFUNCTION, OnWriteFunctionCallback );
	// Bind 'CURLOPT_READFUNCTION' callback function
	url_handle.SetOption( CURLOPT_READDATA, request_info );
	url_handle.SetOption( CURLOPT_READFUNCTION, OnReadFunctionCallback );
	// Bind 'CURLOPT_HEADERFUNCTION' callback function
	url_handle.SetOption( CURLOPT_HEADERDATA, request_info );
	url_handle.SetOption( CURLOPT_HEADERFUNCTION, OnHeaderFunctionCallback );
	// Bind 'CURLOPT_PROGRESSFUNCTION' callback function
	url_handle.SetOption( CURLOPT_NOPROGRESS, _false );
	url_handle.SetOption( CURLOPT_PROGRESSDATA, request_info );
	url_handle.SetOption( CURLOPT_PROGRESSFUNCTION, OnProgressFunctionCallback );
	// Bind 'CURLOPT_DEBUGFUNCTION' callback function
	url_handle.SetOption( CURLOPT_VERBOSE, _true );
	url_handle.SetOption( CURLOPT_DEBUGDATA, request_info );
	url_handle.SetOption( CURLOPT_DEBUGFUNCTION, OnDebugFunctionCallback );

	// Set the URL
	url_handle.SetURL( remote_filename );

	// Set the timeout
	url_handle.SetConnectTimeout( mConnectTimeout );

	// Perform the URL handle options
	_ubool ret = url_handle.PerformHTTP( );

	// Feedback the last modified time
	time = request_info->mLastModifiedTime;

	// Release request info
	EGE_DELETE( request_info );

	return ret;
}

INetworkStreamReaderPassRef NetworkHTTPConnection::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	if ( filename.IsEmpty( ) )
		return _null;

	// Build the URL address with the host URL
	AString remote_filename = _networkHelper::BuildURLAddress( IsEnableSSL( ), mRemoteAddress, mRootURL, AString( ).FromString( filename ) );
	if ( remote_filename.IsEmpty( ) )
		return _null;

	// Create HTTP stream reader
	NetworkHTTPStreamReader* stream_reader = new NetworkHTTPStreamReader( notifier );
	if ( stream_reader->Initialize( remote_filename, mRemoteAddress.mPort, mConnectTimeout, IsEnableSSL( ), mSSLKeyFileName, mSSLCertFileName, mCACertFileName ) == _false )
	{
		ALOG_ERROR_1( "Open '%s' HTTP remote file failed", remote_filename.Str( ) );

		EGE_RELEASE( stream_reader );
		return _null; 
	}

	return stream_reader;
}

_void NetworkHTTPConnection::ProcessDelayConnectOperations( )
{
}

_void NetworkHTTPConnection::ProcessDelaySendOperations( )
{
	mIsProcessing = _true;

	ProcessSyncRequests( );
	ProcessAsyncRequests( );

	mIsProcessing = _false;
}

_void NetworkHTTPConnection::ProcessDelayRecvOperations( )
{
}

_ubool NetworkHTTPConnection::Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters )
{
	RequestInfo* request_info = CreateRequestInfo( _false, _false, url_name, header_list, data_field, parameters );
	if ( request_info == _null )
		return _false;

	if ( ProcessRequest( request_info ) == _false )
		return _false;

	return _true;
}

_ubool NetworkHTTPConnection::GetWithNoBody( AStringPtr url_name )
{
	static AStringArray sNullHeaderList;

	RequestInfo* request_info = CreateRequestInfo( _false, _true, url_name, sNullHeaderList, "", QwordParameters4::cNull );
	if ( request_info == _null )
		return _false;

	if ( ProcessRequest( request_info ) == _false )
		return _false;

	return _true;
}

_ubool NetworkHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters )
{
	RequestInfo* request_info = CreateRequestInfo( _true, _false, url_name, header_list, data_field, parameters );
	if ( request_info == _null )
		return _false;

	if ( ProcessRequest( request_info ) == _false )
		return _false;

	return _true;
}

_ubool NetworkHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	if ( buffer == _null || size == 0 )
		return _false;

	RequestInfo* request_info = CreateRequestInfo( _false, url_name, header_list, buffer, size, parameters );
	if ( request_info == _null )
		return _false;

	if ( ProcessRequest( request_info ) == _false )
		return _false;

	return _true;
}

#endif
