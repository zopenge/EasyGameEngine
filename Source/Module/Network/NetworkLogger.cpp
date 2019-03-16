//! @file     NetworkLogger.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkLogger Implementation
//----------------------------------------------------------------------------

NetworkLogger::NetworkLogger( )
{
	mInterval			= 10;
	mLastTickcount		= 0;

	mEnableCompression	= _false;
}

NetworkLogger::~NetworkLogger( )
{
}

_void NetworkLogger::SendMessage( _dword id, const google::protobuf::MessageLite& message )
{
	// Get the message size in bytes
	_dword msg_size = message.ByteSize( );

	// Create buffer to save binary data of message
	MemArrayPtr< _byte > temp_buf;
	temp_buf.Create( msg_size );

	// Serialize message to binary data
	message.SerializePartialToArray( temp_buf.GetPointer( ), msg_size );

	// Create final buffer to save header and message
	MemArrayPtr< _byte > buffer( msg_size + sizeof( _dword ) * 2 );

	// Write message into stream writer
	_dword write_size = mProtocolBufProcessor->WriteMessageIntoBuffer( id, message, buffer );
	EGE_ASSERT( write_size == buffer.SizeOfBytes( ) );

	// Send it
	if ( mConnection->Send( write_size, buffer ) == _false )
		mConnection->Connect( );
}

_void NetworkLogger::SendLogString( )
{
	// We need to compress it when send data
	if ( mEnableCompression )
	{

	}
	// Just send the original data
	else
	{
		NetworkPacket::LogStringInfo info;
		info.set_allocated_uid( new NetworkPacket::UID( GetPlatform( )->GetDeviceInfoInNetworkPacketFormat( ).uid( ) ) );
		info.set_has_compressed( _false );
		info.set_log( AString( ).FromString( mString ).Str( ) );

		// Send message
		SendMessage( NetworkPacket::MT_LOGGER_STRING, info );
	}

	// Clear the sent log string
	mString = L"";
}

_void NetworkLogger::OnPreWriteLogString( _LOG type, WString& string )
{
}

_void NetworkLogger::OnWriteLogString( _LOG type, WStringPtr string )
{
	// Update log string
	mString += string;

	// Check whether need to send log data
	_dword cur_tickcount = Platform::GetCurrentTickCount( );
	if ( cur_tickcount - mLastTickcount > mInterval )
	{
		mLastTickcount = cur_tickcount;

		SendLogString( );
	}
}

_ubool NetworkLogger::Initialize( INetworkConnection* connection )
{
	if ( connection == _null )
		return _false;

	// Create protocol buffer processor
	mProtocolBufProcessor = GetInterfaceFactory( )->CreateProtoBufProcessor( );
	if ( mProtocolBufProcessor.IsNull( ) )
		return _false;

	// Connect to server
	mConnection = connection;
	if ( mConnection->Connect( ) == _false )
		return _false;

	return _true;
}

_void NetworkLogger::LogIn( )
{
	NetworkPacket::LoginInfo info;
	info.set_allocated_device( new NetworkPacket::DeviceInfo( GetPlatform( )->GetDeviceInfoInNetworkPacketFormat( ) ) );

	SendMessage( NetworkPacket::MT_LOGIN, info );
}

_void NetworkLogger::LogOut( )
{
	NetworkPacket::LogoutInfo info;
	info.set_allocated_device( new NetworkPacket::DeviceInfo( GetPlatform( )->GetDeviceInfoInNetworkPacketFormat( ) ) );

	SendMessage( NetworkPacket::MT_LOGOUT, info );
}

_void NetworkLogger::SetInterval( _dword interval )
{
	mInterval = interval;
}

_dword NetworkLogger::GetInterval( ) const
{
	return mInterval;
}

_void NetworkLogger::EnableCompression( _ubool enable )
{
	mEnableCompression = enable;
}

_ubool NetworkLogger::IsEnabledCompression( ) const
{
	return mEnableCompression;
}
