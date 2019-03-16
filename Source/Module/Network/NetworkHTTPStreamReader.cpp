//! @file     NetworkHTTPStreamReader.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// NetworkHTTPStreamReaderNotifier Implementation
//----------------------------------------------------------------------------

NetworkHTTPStreamReaderNotifier::NetworkHTTPStreamReaderNotifier( NetworkHTTPStreamReader* stream_reader )
{
	mStreamReader = stream_reader;
}

NetworkHTTPStreamReaderNotifier::~NetworkHTTPStreamReaderNotifier( )
{
}

_void NetworkHTTPStreamReaderNotifier::OnUpdateState( _CONNECTION_STATE state )
{
}

_void NetworkHTTPStreamReaderNotifier::OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters )
{

}

_void NetworkHTTPStreamReaderNotifier::OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters )
{
}

_dword NetworkHTTPStreamReaderNotifier::OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{
	mStreamReader->WriteBuffer( buffer, size );

	return size;
}

_void NetworkHTTPStreamReaderNotifier::OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{

}

_void NetworkHTTPStreamReaderNotifier::OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters )
{
	mStreamReader->RecvHeaderInfo( buffer, size );
}

_void NetworkHTTPStreamReaderNotifier::OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters )
{
	mStreamReader->UpdateProgression( (_dword)dlnow, (_dword)dltotal );
}

_void NetworkHTTPStreamReaderNotifier::OnFinishBuffer( const QwordParameters4& parameters )
{

}

//----------------------------------------------------------------------------
// NetworkHTTPStreamReader Implementation
//----------------------------------------------------------------------------

NetworkHTTPStreamReader::NetworkHTTPStreamReader( INetworkStreamReaderNotifier* notifier ) : BaseClass( notifier )
{
	mConnectionNotifier = new NetworkHTTPStreamReaderNotifier( this );
}

NetworkHTTPStreamReader::~NetworkHTTPStreamReader( )
{
	EGE_RELEASE( mConnectionNotifier );
}

_ubool NetworkHTTPStreamReader::Initialize( AStringPtr remote_filename, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename )
{
	// Create stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( 128 KB );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// Save remote file name
	mRemoteFileName = remote_filename;

	// Get the root URL address
	AString root_url	= FORMAT_ASTRING_2( "%s:%d", Path::GetPathRoot( remote_filename ).Str( ), port );
	AString sub_url		= Path::GetChildPathRoot( remote_filename );

	// Create HTTP connection
	mConnection = GetNetworkResourceManager( )->CreateHTTPConnection( root_url, mConnectionNotifier );
	if ( mConnection.IsNull( ) )
		return _false;

	// Perform to download file in block mode
	mConnection->SetConnectTimeout( timeout );
	mConnection->SetFlags( INetworkConnection::_FLAG_BLOCK_MODE );
	if ( mConnection->Get( sub_url, "" ) == _false )
		return _false;

	// Cut the unused memory block
	mStreamWriter->SetCurOffsetAsEndPos( );

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mStreamWriter->GetBuffer( ), mStreamWriter->GetSize( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
	{
		ALOG_ERROR_2( "Open HTTP remote file (url: '%s', size: %d) failed, due to create mem stream reader failed", remote_filename.Str( ), mStreamWriter->GetSize( ) );
		return _false;
	}

	// Unbind connection notifier
	mConnection->SetNotifier( _null );

	ALOG_TRACE_2( "Open HTTP remote file (url: '%s', size: %d) OK", remote_filename.Str( ), mStreamWriter->GetSize( ) );

	return _true;
}

_void NetworkHTTPStreamReader::WriteBuffer( const _byte* buffer, _dword size )
{
	// Write the buffer data
	mStreamWriter->WriteBuffer( buffer, size );

	// Notify outside
	GetNotifier( )->OnReading( size, mMIMEContentSize );
}

_void NetworkHTTPStreamReader::RecvHeaderInfo( const _chara* buffer, _dword size )
{
	// Try to match the MIME content
	_NETWORK_MIME_KEY_TYPE key = _MIME_KEY_TYPE_UNKNOWN; AString value;
	if ( NetworkProtocol::ParseMIME( buffer, key, value ) )
	{
		// Get the content type
		if ( key == _MIME_KEY_TYPE_CONTENT_TYPE )
		{
			mMIMEContentType = NetworkProtocol::ParseMIMEContentType( value );
		}
		// Get the content size
		else if ( key == _MIME_KEY_TYPE_CONTENT_LENGTH )
		{
			mMIMEContentSize = value.ToDword( 10 );
		}
		// Get the content MD5 code
		else if ( key == _MIME_KEY_TYPE_CONTENT_MD5CODE )
		{
			mMIMEContentMD5Code.ParseFromString( value );
		}
	}
}

_void NetworkHTTPStreamReader::UpdateProgression( _dword dlnow, _dword dltotal )
{
	mNotifier->OnReading( dlnow, dltotal );
}

#endif