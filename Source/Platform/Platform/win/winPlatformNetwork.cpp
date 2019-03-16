//! @file     winPlatformNetwork.cpp
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

_DOMAIN_FAMILY_TYPE Platform::GetFamilyType( _dword port, const _chara* url_address )
{
	return anyPlatformNetwork::GetFamilyType( port, url_address );
}

_socket Platform::CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode )
{
	return anyPlatformNetwork::CreateSocket( families, type, block_mode );
}

_socket Platform::CreateListenedSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode, _dword port, _dword max_connection_number )
{
	return anyPlatformNetwork::CreateListenedSocket( families, type, block_mode, port, max_connection_number );
}

_void Platform::CloseSocket( _socket handle )
{
	anyPlatformNetwork::CloseSocket( handle );
}

_dword Platform::GetSocketRecvTimeOutOption( _socket handle )
{
	return anyPlatformNetwork::GetSocketOperationStatus< _dword >( handle, SOL_SOCKET, SO_RCVTIMEO );
}

_ubool Platform::SetSocketRecvTimeOutOption( _socket handle, _dword time )
{
	return anyPlatformNetwork::SetSocketOperationStatus( handle, SOL_SOCKET, SO_RCVTIMEO, time );
}

_dword Platform::GetSocketSendTimeOutOption( _socket handle )
{
	return anyPlatformNetwork::GetSocketOperationStatus< _dword >( handle, SOL_SOCKET, SO_SNDTIMEO );
}

_ubool Platform::SetSocketSendTimeOutOption( _socket handle, _dword time )
{
	return anyPlatformNetwork::SetSocketOperationStatus( handle, SOL_SOCKET, SO_SNDTIMEO, time );
}

_dword Platform::GetLastSocketErrorID( _socket handle )
{
	return anyPlatformNetwork::GetLastSocketErrorID( handle );
}

_socket Platform::AcceptSocket( _socket handle )
{
	return anyPlatformNetwork::AcceptSocket( handle );
}

_ubool Platform::ConnectSocket( _socket handle, const _chara* remote_address, _dword port, OnIsBreakConnectingProc func, _void* userdata )
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