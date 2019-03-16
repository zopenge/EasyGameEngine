//! @file     NetworkFTPConnection.chrome.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CHROME_SDK == 1)

//----------------------------------------------------------------------------
// NetworkFTPConnection Implementation
//----------------------------------------------------------------------------

NetworkFTPConnection::NetworkFTPConnection( ) : BaseClass( GetNetworkResourceManager( )->GetFTPConnectionThread( ) )
{
}

NetworkFTPConnection::~NetworkFTPConnection( )
{
}

_ubool NetworkFTPConnection::Initialize( const Address& remote_address )
{
	return _true;
}

_ubool NetworkFTPConnection::Initialize( WStringPtr url_address )
{
	return _true;
}

_NETWORK_CONNECTION_TYPE NetworkFTPConnection::GetType( ) const
{
	return _NETWORK_CONNECTION_FTP;
}

_void NetworkFTPConnection::Stop( )
{

}

_ubool NetworkFTPConnection::IsRemoteFileExist( WStringPtr filename )
{
	return _false;
}

INetworkStreamReaderPassRef NetworkFTPConnection::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	return _null;
}

_void NetworkFTPConnection::ProcessDelayConnectOperations( )
{
}

_void NetworkFTPConnection::ProcessDelaySendOperations( )
{
}

_void NetworkFTPConnection::ProcessDelayRecvOperations( )
{
}

_void NetworkFTPConnection::SetFTPNotifier( INetworkFTPConnectionNotifier* notifier )
{
}

INetworkFTPConnectionNotifierRef NetworkFTPConnection::GetFTPNotifier( )
{
	return &NullNetwork::GetInstance( ).GetNetworkFTPConnectionNotifier( );
}

_void NetworkFTPConnection::SetUserName( AStringPtr username )
{
}

_void NetworkFTPConnection::SetPassword( AStringPtr password )
{
}

_ubool NetworkFTPConnection::UploadFile( WStringPtr local_filename, WStringPtr remote_filename, const QwordParameters4& parameters )
{
	return _false;
}

#endif
