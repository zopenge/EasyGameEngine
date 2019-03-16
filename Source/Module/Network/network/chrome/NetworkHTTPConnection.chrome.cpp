//! @file     NetworkHTTPConnection.chrome.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CHROME_SDK == 1)

//----------------------------------------------------------------------------
// NetworkHTTPConnection Implementation
//----------------------------------------------------------------------------

NetworkHTTPConnection::NetworkHTTPConnection( )
{
}

NetworkHTTPConnection::~NetworkHTTPConnection( )
{
}

_void NetworkHTTPConnection::OnConnectionFinished( _void* user_data, _int result )
{
	RequestInfo* request_info = (RequestInfo*) user_data;
	EGE_ASSERT( request_info != _null );
}

_void NetworkHTTPConnection::OnRecv( _void* user_data, _int result )
{
	// Get the web socket interface
	const PPB_WebSocket* web_socket = GetPPResourceModule( )->GetPPBWebSocket( );
	EGE_ASSERT( web_socket != _null );

	// Get the receive request info
	RequestInfo* request_info = (RequestInfo*) user_data;
	EGE_ASSERT( request_info != _null );

	// Get the connection resource
	PP_Resource connection = request_info->mPPBConnection;

	// We have got something
	if ( result == PP_OK ) 
	{
		// Clear the 'no recv data' flag
		request_info->ClearFlags( BaseInfo::_FLAG_NO_RECV_DATA );

		// Get the received data
		_dword	size	= 0;
		_void*	buffer	= GetPPResourceModule( )->MapPPVarArrayData( request_info->mRecvData, size );
		if ( size != 0 && buffer != _null )
		{
			// Create stream to receive buffer data
			if ( request_info->mRecvBuffer.IsNull( ) )
				request_info->mRecvBuffer = GetInterfaceFactory( )->CreateMemStreamWriter( size );

			// Get the stream buffer
			IStreamWriter* stream = request_info->mRecvBuffer;
			EGE_ASSERT( stream != _null );

			// Receive buffer data
			stream->WriteBuffer( buffer, size );

			// Start to process with the received buffer data
			while ( stream->GetOffset( ) != 0 )
			{
				// Let the notifier to process data
				_int processed_size = request_info->mHTTPConnection->GetNotifier( )->OnRecvBuffer( stream->GetOffset( ), stream->GetBuffer( ), request_info->mParameters );
				if ( processed_size > 0 )
				{
					// Remove processed buffer data from stream
					stream->RemoveBuffer( processed_size );
				}
				else
				{
					// Finished it, or maybe we still need to wait for the received buffer comes
					break;
				}
			}
		}
		GetPPResourceModule( )->UnmapPPVarArrayData( request_info->mRecvData );
	}

	// Continue to receive data from server
	web_socket->ReceiveMessage( connection, &request_info->mRecvData, PP_MakeCompletionCallback( OnRecv, request_info ) );
}

_void NetworkHTTPConnection::Stop( )
{
	// Close all connections
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		GetPPResourceModule( )->GetPPBWebSocket( )->Close( request_info->mPPBConnection, -1, GetPPResourceModule( )->Utf16ToVar( L"Stop" ), PP_BlockUntilComplete( ) );

		EGE_DELETE( request_info );
	}

	mRequests.Clear( );
}

_ubool NetworkHTTPConnection::IsRemoteFileExist( WStringPtr filename )
{
	return _false;
}

INetworkStreamReaderPassRef NetworkHTTPConnection::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	if ( filename.IsEmpty( ) )
		return _null;

	// Create HTTP stream reader
	NetworkHTTPStreamReader* stream_reader = new NetworkHTTPStreamReader( HasFlags( _FLAG_DEBUG_MODE ), notifier );
	if ( stream_reader->Initialize( filename ) == _false )
	{
		WLOG_ERROR_1( L"Open '%s' HTTP remote file failed", filename.Str( ) );

		EGE_RELEASE( stream_reader );
		return _null; 
	}

	return stream_reader;
}

_void NetworkHTTPConnection::ProcessDelayConnectOperations( )
{
	// Get the web socket interface
	const PPB_WebSocket* web_socket = GetPPResourceModule( )->GetPPBWebSocket( );
	EGE_ASSERT( web_socket != _null );

	// Connect to server
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		// Get the connection resource
		PP_Resource connection = request_info->mPPBConnection;

		// Get the connection status
		PP_WebSocketReadyState status = web_socket->GetReadyState( connection );
		if ( status != PP_WEBSOCKETREADYSTATE_INVALID )
			continue; // We have connected to server

		// Build the URL address
		AString url_address = _networkHelper::BuildURLAddress( IsEnableSSL( ), mRemoteAddress, mRootURL, request_info->mURLName );

		// Start to connect server
		web_socket->Connect( connection, GetPPResourceModule( )->AnsiToVar( url_address ), _null, 0, PP_MakeCompletionCallback( OnConnectionFinished, request_info ) );
	}
}

_void NetworkHTTPConnection::ProcessDelaySendOperations( )
{
	// Get the web socket interface
	const PPB_WebSocket* web_socket = GetPPResourceModule( )->GetPPBWebSocket( );
	EGE_ASSERT( web_socket != _null );

	// Connect to server
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		// Get the connection resource
		PP_Resource connection = request_info->mPPBConnection;

		// Get the connection status
		PP_WebSocketReadyState status = web_socket->GetReadyState( connection );
		if ( status == PP_WEBSOCKETREADYSTATE_OPEN )
			continue; // Make sure we have connected to server already

		// Create PP-VAR array buffer to save sending data
		PP_VarPassRef pp_data = GetPPResourceModule( )->BuildPPVarArray( request_info->mFieldBuffer.SizeOfBytes( ), request_info->mFieldBuffer.GetPointer( ) );

		// Send message to server
		web_socket->SendMessage( connection, pp_data );
	}
}

_void NetworkHTTPConnection::ProcessDelayRecvOperations( )
{
	// Get the web socket interface
	const PPB_WebSocket* web_socket = GetPPResourceModule( )->GetPPBWebSocket( );
	EGE_ASSERT( web_socket != _null );

	// Connect to server
	for ( _dword i = 0; i < mRequests.Number( ); i ++ )
	{
		RequestInfo* request_info = mRequests[i];
		EGE_ASSERT( request_info != _null );

		// Get the connection resource
		PP_Resource connection = request_info->mPPBConnection;

		// Get the connection status
		PP_WebSocketReadyState status = web_socket->GetReadyState( connection );
		if ( status == PP_WEBSOCKETREADYSTATE_OPEN )
			continue; // Make sure we have connected to server already

		// Recive message from server
		web_socket->ReceiveMessage( connection, &request_info->mRecvData, PP_MakeCompletionCallback( OnRecv, request_info ) );
	}
}

_ubool NetworkHTTPConnection::Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters )
{
	// Build request info
	RequestInfo* request_info		= new RequestInfo( );
	request_info->mHTTPConnection	= this;
	request_info->mParameters		= parameters;
	request_info->mURLName			= url_name;

	// Initialize flags
	request_info->SetFlags( BaseInfo::_FLAG_NO_RECV_DATA );

	// Copy the data filed buffer
	if ( data_field.GetLength( ) > 0 )
		request_info->mFieldBuffer.Create( data_field.GetLength( ), (const _byte*) data_field.Str( ) );

	// Append it
	mLocker.Enter( );
	mRequests.Append( request_info );
	mLocker.Leave( );

	return _true;
}

_ubool NetworkHTTPConnection::GetWithNoBody( AStringPtr url_name )
{
	return _false;
}

_ubool NetworkHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters )
{
	// Build request info
	RequestInfo* request_info		= new RequestInfo( );
	request_info->mHTTPConnection	= this;
	request_info->mParameters		= parameters;
	request_info->mURLName			= url_name;

	// Initialize flags
	request_info->SetFlags( BaseInfo::_FLAG_NO_RECV_DATA );

	// Copy the data filed buffer
	if ( data_field.GetLength( ) > 0 )
		request_info->mFieldBuffer.Create( data_field.GetLength( ), (const _byte*) data_field.Str( ) );

	// Append it
	mLocker.Enter( );
	mRequests.Append( request_info );
	mLocker.Leave( );

	return _true;
}

_ubool NetworkHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	// Build request info
	RequestInfo* request_info		= new RequestInfo( );
	request_info->mHTTPConnection	= this;
	request_info->mParameters		= parameters;
	request_info->mURLName			= url_name;

	// Initialize flags
	request_info->SetFlags( BaseInfo::_FLAG_NO_RECV_DATA );

	// Copy the data filed buffer
	if ( buffer != _null && size != 0 )
		request_info->mFieldBuffer.Create( size, buffer );

	// Append it
	mLocker.Enter( );
	mRequests.Append( request_info );
	mLocker.Leave( );

	return _true;
}

#endif