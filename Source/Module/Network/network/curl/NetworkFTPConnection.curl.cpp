//! @file     NetworkFTPConnection.curl.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// NetworkFTPConnection Implementation
//----------------------------------------------------------------------------

NetworkFTPConnection::NetworkFTPConnection( INetworkConnectionThread* connection_thread ) : BaseClass( connection_thread )
{
	mFTPNotifier = &NullNetwork::GetInstance( ).GetNetworkFTPConnectionNotifier( );
}

NetworkFTPConnection::~NetworkFTPConnection( )
{
}

_dword NetworkFTPConnection::OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, _dword size, _void* userdata )
{
	// Get the info
	BaseInfo* info = (BaseInfo*) userdata;
	EGE_ASSERT( info != _null );

	// Get the connection
	NetworkFTPConnection* ftp_connection = info->mFTPConnection;
	EGE_ASSERT( ftp_connection != _null );

	// It's upload info
	//if ( info->mType == BaseInfo::_TYPE_UPLOAD )
	//{
	//	UploadInfo* upload_info = (UploadInfo*) info;


	//}

	// Tell the user we receive data
	ftp_connection->mNotifier->OnDebugBuffer( _curlHelper::TranslateDebugType( type ), buffer, size, info->mParameters );

	// Feedback the total bytes	
	return size;
}

_dword NetworkFTPConnection::OnWriteFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	// Get the info
	BaseInfo* info = (BaseInfo*) userdata;
	EGE_ASSERT( info != _null );

	// Whether abort it
	if ( info->HasFlags( BaseInfo::_FLAG_ABORT ) || gNetworkModule->IsPowerOff( ) )
		return 0;

	// Get the connection
	NetworkFTPConnection* ftp_connection = info->mFTPConnection;
	EGE_ASSERT( ftp_connection != _null );

	// Get the total size
	_dword total_size = size * number;

	// Feedback the total bytes	
	return total_size;
}

_dword NetworkFTPConnection::OnReadFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	// Get the info
	BaseInfo* info = (BaseInfo*) userdata;
	EGE_ASSERT( info != _null );

	// Whether abort it
	if ( info->HasFlags( BaseInfo::_FLAG_ABORT ) || gNetworkModule->IsPowerOff( ) )
		return CURL_READFUNC_ABORT;

	// Get the connection
	NetworkFTPConnection* ftp_connection = info->mFTPConnection;
	EGE_ASSERT( ftp_connection != _null );

	// Get the total size
	_dword totalsize = size * number;

	// Process reading operation
	switch ( info->mType )
	{
		// It's upload operation
		case BaseInfo::_TYPE_UPLOAD:
		{
			UploadInfo* update_info = (UploadInfo*) info;

			// Read the stream buffer data
			totalsize = update_info->mStreamReader->ReadBuffer( buffer, totalsize );
		}
		break;
            
        default:
            break;
	}
	
	// Tell the user we send data
	ftp_connection->mNotifier->OnSendBuffer( totalsize, (const _byte*) buffer, info->mParameters );

	// Feedback the total bytes
	return totalsize;
}

_dword NetworkFTPConnection::OnHeaderFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	// Get the info
	BaseInfo* info = (BaseInfo*) userdata;
	EGE_ASSERT( info != _null );

	// Whether abort it
	if ( info->HasFlags( BaseInfo::_FLAG_ABORT ) || gNetworkModule->IsPowerOff( ) )
		return 0;

	// Get the connection
	NetworkFTPConnection* ftp_connection = info->mFTPConnection;
	EGE_ASSERT( ftp_connection != _null );

	// Invoke the header buffer callback function
//	urlhandledata.mFTPSession->mHeaderBufferFunc.Invoke( &urlhandledata, buffer, size * number );

	// Feedback the total bytes
	return size * number;
}

_dword NetworkFTPConnection::OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow )
{
	// Get the info
	BaseInfo* info = (BaseInfo*) userdata;
	EGE_ASSERT( info != _null );

	// Get the connection
	NetworkFTPConnection* ftp_connection = info->mFTPConnection;
	EGE_ASSERT( ftp_connection != _null );

	// No error
	return 0;
}

NetworkFTPConnection::UploadInfo* NetworkFTPConnection::CreateUploadInfo( const QwordParameters4& parameters )
{
	// Create request handle
	UploadInfo* upload_info		= new UploadInfo( );
	upload_info->mFTPConnection	= this;
	upload_info->mParameters	= parameters;

	return upload_info;
}

_ubool NetworkFTPConnection::Initialize( const Address& remote_address )
{
	// Initialize the local address
	if ( InitLocalAddress( (Address::_TYPE) remote_address.mType ) == _false )
		return _false;

	// Initialize the remote address
	if ( InitRemoteAddress( (Address::_TYPE) remote_address.mType, remote_address.mPort, remote_address.mIP ) == _false )
		return _false;

	return _true;
}

_ubool NetworkFTPConnection::Initialize( WStringPtr url_address )
{
	// Initialize the local address
	if ( InitLocalAddress( Address::_TYPE_TCP ) == _false )
		return _false;

	// Jump the "xxx://" string
	AString url_address_without_protocols = _curlHelper::GetURLAddressWithoutProtocols( AString( ).FromString( url_address ) );

	// Get the URL address and port number
	StringFormatter::ParseString( url_address_without_protocols.Str( ), "%s:%d", mRootURL, mRemoteAddress.mPort );

	// Check root URL and port number
	if ( mRootURL.IsEmpty( ) || mRemoteAddress.mPort == 0 )
		return _false;

	return _true;
}

_NETWORK_CONNECTION_TYPE NetworkFTPConnection::GetType( ) const
{
	return _NETWORK_CONNECTION_FTP;
}

_void NetworkFTPConnection::Stop( )
{
	LockOwner lock_owner( mLock );

	// Abort all connections
	for ( _dword i = 0; i < mUploads.Number( ); i ++ )
	{
		UploadInfo* upload_info = mUploads[i];
		EGE_ASSERT( upload_info != _null );

		upload_info->CombineFlags( BaseInfo::_FLAG_ABORT );
	}

	// Remove all actions
	BaseClass::Stop( );

	// Remove all connections
	for ( _dword i = 0; i < mUploads.Number( ); i ++ )
	{
		EGE_DELETE( mUploads[i] );
	}
	mUploads.Clear( );
}

_ubool NetworkFTPConnection::Send( _dword size, const _byte* buffer )
{
	if ( BaseClass::Send( size, buffer ) == _false )
		return _false;

	return _true;
}

_ubool NetworkFTPConnection::SendInstant( _dword size, const _byte* buffer )
{
	if ( BaseClass::SendInstant( size, buffer ) == _false )
		return _false;

	return _true;
}

_ubool NetworkFTPConnection::IsRemoteFileExist( WStringPtr filename )
{
	if ( filename.IsEmpty( ) )
		return _false;

	// Build the URL address with the host URL
	AString remote_filename = _curlHelper::BuildURLAddress( _false, mRemoteAddress, mRootURL, AString( ).FromString( filename ) );
	if ( remote_filename.IsEmpty( ) )
		return _false;

	// Get the FTP header info
	_curlHandle url_handle;
	// Set the URL address and port options
	url_handle.SetOption( CURLOPT_URL, remote_filename.Str( ) );
	url_handle.SetOption( CURLOPT_PORT, mRemoteAddress.mPort );
	// Disable to use any signal/alarm handlers
	url_handle.SetOption( CURLOPT_NOSIGNAL, _true );
	// Doesn't need to send the body section
	url_handle.SetOption( CURLOPT_NOBODY, _true );
	// Use the location
	url_handle.SetOption( CURLOPT_FOLLOWLOCATION, _true );

	// Set timeout
	url_handle.SetConnectTimeout( 6 SEC );
	url_handle.SetConnectTimeout( mConnectTimeout );

	// Perform the URL handle options
	if ( url_handle.PerformFTP( ) == _false )
		return _false;

	return _true;
}

INetworkStreamReaderPassRef NetworkFTPConnection::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	if ( filename.IsEmpty( ) )
		return _null;

	// Build the URL address
	AString url_address = _curlHelper::BuildFTPURLAddress( mRemoteAddress, mRootURL, AString( ).FromString( filename ) );
	if ( url_address.IsEmpty( ) )
		return _null;

	// Create FTP stream reader
	NetworkFTPStreamReader* stream_reader = new NetworkFTPStreamReader( notifier );
	if ( stream_reader->Initialize( url_address, mUserNameAndPassword, mRemoteAddress.mPort, mConnectTimeout, _false, "", "", "" ) == _false )
		{ EGE_RELEASE( stream_reader ); return _null; }

	return stream_reader;
}

_void NetworkFTPConnection::ProcessDelayConnectOperations( )
{
}

_void NetworkFTPConnection::ProcessDelaySendOperations( )
{
	// Process all requests
	while ( _true )
	{
		// Get the request info
		mLock.Enter( );
		UploadInfo* upload_info = _null;
		mUploads.Dequeue( upload_info );
		mLock.Leave( );

		// Check whether all request info has finished
		if ( upload_info == _null )
			break;

		// Perform FTP request
		upload_info->mHandle.PerformFTP( );

		// Get the last error ID
		CURLcode last_url_err_id = upload_info->mHandle.GetLastErrorID( );
		if ( last_url_err_id == CURLE_OK )
		{
			// Upload file completed
			mFTPNotifier->OnUploadFileCompleted( upload_info->mLocalFileName, upload_info->mRemoteFileName );
		}
		else
		{
			// Build network error info
			NetworkErrorDesc err_desc;
			err_desc.mErrID		= _curlHelper::TranslateErrorType( last_url_err_id );
			err_desc.mErrDesc	= ::curl_easy_strerror( last_url_err_id );

			// Feedback the error ID by callback function
			mNotifier->OnError( err_desc, upload_info->mParameters );
		}

		// Release request
		EGE_DELETE( upload_info );

		WLOG_DEBUG_1( L"Finished FTP upload request, remain: %d", mUploads.Number( ) );
	}
}

_void NetworkFTPConnection::ProcessDelayRecvOperations( )
{
}

_void NetworkFTPConnection::SetFTPNotifier( INetworkFTPConnectionNotifier* notifier )
{
	if ( notifier == _null )
		mFTPNotifier = &NullNetwork::GetInstance( ).GetNetworkFTPConnectionNotifier( );
	else
		mFTPNotifier = notifier;
}

INetworkFTPConnectionNotifier* NetworkFTPConnection::GetFTPNotifier( )
{
	return mFTPNotifier;
}

_void NetworkFTPConnection::SetUserName( AStringPtr username )
{
	mUserName				= username;
	mUserNameAndPassword	= mUserName + ":" + mPassword;
}

_void NetworkFTPConnection::SetPassword( AStringPtr password )
{
	mPassword				= password;
	mUserNameAndPassword	= mUserName + ":" + mPassword;
}

_ubool NetworkFTPConnection::UploadFile( WStringPtr local_filename, WStringPtr remote_filename, const QwordParameters4& parameters )
{
	// Check the user name and password
	if ( mUserNameAndPassword.IsEmpty( ) )
	{
		WLOG_ERROR( L"We must provide the user name and password to upload file" );
		return _false;
	}

	// Create request handle
	UploadInfo* upload_info = CreateUploadInfo( parameters );
	if ( upload_info == _null )
		return _false;

	// Save upload info
	upload_info->mLocalFileName		= local_filename;
	upload_info->mRemoteFileName	= remote_filename;

	// Open the local file stream reader
	upload_info->mStreamReader = GetInterfaceFactory( )->CreateFileStreamReader( local_filename );
	if ( upload_info->mStreamReader.IsNull( ) )
		{ delete upload_info; return _false; }

	// Build the URL address
	AString url_address = _curlHelper::BuildFTPURLAddress( mRemoteAddress, mRootURL, AString( ).FromString( remote_filename ) );

	// Set the common info
	upload_info->mHandle.SetOption( CURLOPT_UPLOAD, _true );
	upload_info->mHandle.SetOption( CURLOPT_FTP_CREATE_MISSING_DIRS, _true );
	// Set the URL address and port options
	upload_info->mHandle.SetOption( CURLOPT_URL, url_address.Str( ) );
	upload_info->mHandle.SetOption( CURLOPT_PORT, mRemoteAddress.mPort );
	// Use the user name and password
	upload_info->mHandle.SetOption( CURLOPT_USERPWD, mUserNameAndPassword.Str( ) );
	// Disable to use any signal/alarm handlers
	upload_info->mHandle.SetOption( CURLOPT_NOSIGNAL, _true );

	// Bind 'CURLOPT_WRITEFUNCTION' callback function
	upload_info->mHandle.SetOption( CURLOPT_WRITEDATA, upload_info );
	upload_info->mHandle.SetOption( CURLOPT_WRITEFUNCTION, OnWriteFunctionCallback );
	// Bind 'CURLOPT_READFUNCTION' callback function
	upload_info->mHandle.SetOption( CURLOPT_READDATA, upload_info );
	upload_info->mHandle.SetOption( CURLOPT_READFUNCTION, OnReadFunctionCallback );
	// Bind 'CURLOPT_HEADERFUNCTION' callback function
	upload_info->mHandle.SetOption( CURLOPT_HEADERDATA, upload_info );
	upload_info->mHandle.SetOption( CURLOPT_HEADERFUNCTION, OnHeaderFunctionCallback );
	// Bind 'CURLOPT_PROGRESSFUNCTION' callback function
	upload_info->mHandle.SetOption( CURLOPT_NOPROGRESS, _false );
	upload_info->mHandle.SetOption( CURLOPT_PROGRESSDATA, upload_info );
	upload_info->mHandle.SetOption( CURLOPT_PROGRESSFUNCTION, OnProgressFunctionCallback );

	// Bind 'CURLOPT_DEBUGFUNCTION' callback function
	upload_info->mHandle.SetOption( CURLOPT_VERBOSE, _true );
	upload_info->mHandle.SetOption( CURLOPT_DEBUGDATA, upload_info );
	upload_info->mHandle.SetOption( CURLOPT_DEBUGFUNCTION, OnDebugFunctionCallback );

	// Set the connection timeout in seconds
	if ( mConnectTimeout != -1 )
		upload_info->mHandle.SetOption( CURLOPT_FTP_RESPONSE_TIMEOUT, mConnectTimeout / 1000 );

	// Set the upload speed
	if ( mMaxUploadSpeed != -1 )
		upload_info->mHandle.SetOption( CURLOPT_MAX_SEND_SPEED_LARGE, mMaxUploadSpeed );

	// Set the download speed
	if ( mMaxDownloadSpeed != -1 )
		upload_info->mHandle.SetOption( CURLOPT_MAX_RECV_SPEED_LARGE, mMaxDownloadSpeed );

	mLock.Enter( );
	mUploads.Enqueue( upload_info );
	mLock.Leave( );

	return _true;
}

#endif