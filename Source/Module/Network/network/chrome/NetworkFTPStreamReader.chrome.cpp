//! @file     NetworkFTPStreamReader.chrome.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CHROME_SDK == 1)

//----------------------------------------------------------------------------
// NetworkFTPStreamReader Implementation
//----------------------------------------------------------------------------

NetworkFTPStreamReader::NetworkFTPStreamReader( _ubool debug_mode, INetworkStreamReaderNotifier* notifier ) : BaseClass( debug_mode, notifier )
{
}

NetworkFTPStreamReader::~NetworkFTPStreamReader( )
{
}

_ubool NetworkFTPStreamReader::Initialize( AStringPtr remote_filename, AStringPtr username_and_password, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename )
{
	mRemoteFileName			= remote_filename;
	mUserNameAndPassword	= username_and_password;

	// Create stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( 128 KB );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// Cut the unused memory block
	if ( mStreamWriter->SetCurOffsetAsEndPos( ) == _false )
		return _false;

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mStreamWriter->GetBuffer( ), mStreamWriter->GetSize( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

_float NetworkFTPStreamReader::GetDownloadSpeed( )
{
	return 0.0f;
}

#endif