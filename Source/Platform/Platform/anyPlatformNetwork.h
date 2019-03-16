//! @file     anyPlatformNetwork.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// anyPlatformNetwork
//----------------------------------------------------------------------------

class anyPlatformNetwork
{
public:
	//!	Set socket option status.
	template< typename Type >
	static Type GetSocketOperationStatus( _socket handle, _dword protocol, _dword option );
	//!	Get socket option status.
	template< typename Type >
	static _ubool SetSocketOperationStatus( _socket handle, _dword protocol, _dword option, const Type& value );

public:
	static _dword GetURLIPAddress( const _chara* url_address );

	static _DOMAIN_FAMILY_TYPE GetFamilyType( _dword port, const _chara* url_address );

	static _socket CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode );
	static _socket CreateListenedSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode, _dword port, _dword max_connection_number );
	static _void CloseSocket( _socket handle );
	static _dword GetLastSocketErrorID( _socket handle );
	static _socket AcceptSocket( _socket handle );
	static _ubool ConnectSocket( _socket handle, const _chara* remote_address, _dword port, Platform::OnIsBreakConnectingProc func, _void* userdata );
	static _dword ReadSocket( _socket handle, _void* buffer, _dword size );
	static _dword WriteSocket( _socket handle, const _void* buffer, _dword size );
};

//----------------------------------------------------------------------------
// anyPlatformNetwork Implementation
//----------------------------------------------------------------------------

//!	Set socket option status.
template< typename Type >
Type anyPlatformNetwork::GetSocketOperationStatus( _socket handle, _dword protocol, _dword option )
{
	EGE_ASSERT( handle != _null );

	// Get the socket operation ID
	Type optval; _int optvallen = sizeof( Type );
	getsockopt( handle, protocol, option, (char*)&optval, (socklen_t*) &optvallen );

	return optval;
}

//!	Get socket option status.
template< typename Type >
_ubool anyPlatformNetwork::SetSocketOperationStatus( _socket handle, _dword protocol, _dword option, const Type& value )
{
	EGE_ASSERT( handle != _null );

	if ( setsockopt( handle, protocol, option, (char*)&value, sizeof( Type ) ) == -1 )
		return _false;

	return _true;
}

}