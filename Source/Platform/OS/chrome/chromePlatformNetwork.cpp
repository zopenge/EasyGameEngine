//! @file     chromePlatformNetwork.cpp
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
	return 0;
}

_socket Platform::CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode )
{
	return _null;
}

_void Platform::CloseSocket( _socket handle )
{
}

_dword Platform::GetSocketRecvTimeOutOption( _socket handle )
{
	return 0;
}

_ubool Platform::SetSocketRecvTimeOutOption( _socket handle, _dword time )
{
	return _false;
}

_dword Platform::GetSocketSendTimeOutOption( _socket handle )
{
	return 0;
}

_ubool Platform::SetSocketSendTimeOutOption( _socket handle, _dword time )
{
	return _false;
}

_dword Platform::GetLastSocketErrorID( _socket handle )
{
	return 0;
}

_ubool Platform::ConnectSocket( _socket handle, _dword remote_address, _dword port, OnIsBreakConnectingProc func, _void* userdata )
{
	return _false;
}

_dword Platform::ReadSocket( _socket handle, _void* buffer, _dword size )
{
	return 0;
}

_dword Platform::WriteSocket( _socket handle, const _void* buffer, _dword size )
{
	return 0;
}