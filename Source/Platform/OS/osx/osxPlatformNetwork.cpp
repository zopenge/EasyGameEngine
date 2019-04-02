//! @file     iosPlatformNetwork.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Network Implementation
//----------------------------------------------------------------------------

_dword Platform::GetURLIPAddress( const _chara* url_address )
{
	return anyPlatformNetwork::GetURLIPAddress( url_address );
}

_socket Platform::CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode )
{
	return anyPlatformNetwork::CreateSocket( families, type, block_mode );
}

_void Platform::CloseSocket( _socket handle )
{
	anyPlatformNetwork::CloseSocket( handle );
}

_dword Platform::GetSocketRecvTimeOutOption( _socket handle )
{
	timeval recv_timeout = anyPlatformNetwork::GetSocketOperationStatus< timeval >( handle, SOL_SOCKET, SO_RCVTIMEO );
	return EGE_TIME_TO_DWORD( recv_timeout );
}

_ubool Platform::SetSocketRecvTimeOutOption( _socket handle, _dword time )
{
	timeval recv_timeout; EGE_VALUE_TO_TIME( recv_timeout, time );
	return anyPlatformNetwork::SetSocketOperationStatus( handle, SOL_SOCKET, SO_RCVTIMEO, recv_timeout );
}

_dword Platform::GetSocketSendTimeOutOption( _socket handle )
{
	timeval send_timeout = anyPlatformNetwork::GetSocketOperationStatus< timeval >( handle, SOL_SOCKET, SO_SNDTIMEO );
	return EGE_TIME_TO_DWORD( send_timeout );
}

_ubool Platform::SetSocketSendTimeOutOption( _socket handle, _dword time )
{
	timeval send_timeout; EGE_VALUE_TO_TIME( send_timeout, time );
	return anyPlatformNetwork::SetSocketOperationStatus( handle, SOL_SOCKET, SO_SNDTIMEO, send_timeout );
}

_dword Platform::GetLastSocketErrorID( _socket handle )
{
	return anyPlatformNetwork::GetLastSocketErrorID( handle );
}

_ubool Platform::ConnectSocket( _socket handle, _dword remote_address, _dword port, OnIsBreakConnectingProc func,_void* userdata )
{
	return anyPlatformNetwork::ConnectSocket( handle, remote_address, port, func, userdata );
}

_dword Platform::ReadSocket( _socket handle, _void* buffer, _dword size )
{
	return anyPlatformNetwork::ReadSocket( handle, buffer, size );
}

_dword Platform::WriteSocket( _socket handle, const _void* buffer, _dword size )
{
	return anyPlatformNetwork::WriteSocket( handle, buffer, size );
}