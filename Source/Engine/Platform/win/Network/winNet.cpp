//! @file     winNet.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winNet Implementation
//----------------------------------------------------------------------------

winNet::winNet( )
{
}

winNet::~winNet( )
{
}

INet::_STATUS winNet::GetStatus( ) const
{
	FlagsObject flags;
	if ( ::InternetGetConnectedState( (LPDWORD) &flags, 0 ) )
	{
		if ( flags.HasFlags( INTERNET_CONNECTION_MODEM ) )
			return _STATUS_VIA_MODEM;
		if ( flags.HasFlags( INTERNET_CONNECTION_LAN ) )
			return _STATUS_VIA_LAN;
	}

	return _STATUS_OFFLINE;
}

_dword winNet::GetAdapterNumber( ) const
{
	// Get host name
	_chara hostname[1024];
	if ( ::gethostname( hostname, 1024 ) != 0 )
		return 0;

	addrinfo* addressinfo = _null;
	addrinfo* addresslink = _null;

	// Get host address information link
	_int error = ::getaddrinfo( hostname, _null, _null, &addressinfo );
	if ( error != 0 )
		return 0;

	addresslink = addressinfo;

	_dword number = 0;

	while ( addresslink != _null )
	{
		// Skip other than ipv4
		if ( addresslink->ai_family != AF_INET )
		{
			addresslink = addresslink->ai_next;

			continue;
		}

		addresslink = addresslink->ai_next;

		number ++;
	}

	// Free the memory used by address link
	::freeaddrinfo( addressinfo );

	return number;
}

_dword winNet::GetLocalIPAddress( _dword adapterindex ) const
{
	// Get host name
	_chara hostname[1024];
	if ( ::gethostname( hostname, 1024 ) != 0 )
		return 0;

	addrinfo* addressinfo = _null;
	addrinfo* addresslink = _null;

	_int error = ::getaddrinfo( hostname, _null, _null, &addressinfo );

	// Get host address information link
	if ( error != 0 )
		return 0;

	addresslink = addressinfo;

	_dword i = 0;

	while ( addresslink != _null )
	{
		// Skip other than ipv4
		if ( addresslink->ai_family != AF_INET )
		{
			addresslink = addresslink->ai_next;

			continue;
		}

		// Found it
		if ( i == adapterindex )
			break;

		addresslink = addresslink->ai_next;

		i ++;
	}

	_dword ip = 0;

	if ( addresslink != _null )
		ip = Math::BSwap32( ( (sockaddr_in*) addresslink->ai_addr )->sin_addr.s_addr );

	// Free the memory used by address link
	::freeaddrinfo( addressinfo );

	return ip;
}

_ubool winNet::GetLocalMACAddress( AString& mac_address ) const
{
	// Allocate information for up to 16 NICs
	IP_ADAPTER_INFO adapter_info[16];       

	// Start to get adapters info
	ULONG buffer_size = sizeof( adapter_info );  // Save memory size of buffer
	if ( ::GetAdaptersInfo( adapter_info, &buffer_size ) != ERROR_SUCCESS )
		return _false;

	// Get the first adapter info
	const _byte* ptr = adapter_info[0].Address;
	mac_address.Format( "%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5) );

	return _true;
}

_ubool winNet::EnumIPAddress( _dword* address_list, _dword& number ) const
{
	// Create socket
	SOCKET _socket = ::socket( AF_INET, SOCK_DGRAM, 0 );
	if ( _socket == INVALID_SOCKET )
		return _false;

	// Get interface list
	INTERFACE_INFO interface_list[20]; DWORD bytes_returned = 0;
	if ( ::WSAIoctl( _socket, SIO_GET_INTERFACE_LIST, 0, 0, &interface_list, sizeof( interface_list ), &bytes_returned, 0, 0) == -1 ) 
		return _false;

	// Get the interface number
	number = bytes_returned / sizeof( INTERFACE_INFO );
	for ( _dword i = 0; i < number; i ++ )
	{
		const sockaddr_in* addr_in = (const sockaddr_in*) &interface_list[i].iiAddress;

		// Feedback IP address
		address_list[i] = Math::BSwap32( addr_in->sin_addr.s_addr );
	}

	// Release socket
	::closesocket( _socket );

	return _true;
}

_dword winNet::GetURLIPAddress( AStringPtr url_address ) const
{
	return Platform::GetURLIPAddress( url_address.Str( ) );
}

_ubool winNet::GetNetworkCardName( AString& name ) const
{
	// Load "iphlpapi.dll" library
	_handle dll_module = Platform::LoadLibrary( "iphlpapi.dll" );
	if ( dll_module == _null )
		return _false;

	// Get "GetAdaptersInfo" function interface
	typedef _dword (_stdcall *GetAdapter)( IP_ADAPTER_INFO*, _dword* );
	GetAdapter get_adapter_func = (GetAdapter) ::GetProcAddress( (HMODULE) dll_module, "GetAdaptersInfo" );
	if ( get_adapter_func == _null )
		return _false;

	// Call "GetAdaptersInfo" function
	IP_ADAPTER_INFO adapter = { 0 }; _dword size = sizeof( IP_ADAPTER_INFO );
	if ( (*get_adapter_func)( &adapter, &size ) != 0 )
		return _false;

	// Get adapter description
	name = adapter.Description;

	return _true;
}

_ubool winNet::Ping( AStringPtr address ) const
{
	return _false;
}