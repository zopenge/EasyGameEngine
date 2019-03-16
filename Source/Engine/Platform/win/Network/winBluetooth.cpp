//! @file     winBluetoothAdapter.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winBluetoothSocket Implementation
//----------------------------------------------------------------------------

winBluetoothSocket::winBluetoothSocket( )
{
	EGE_INIT( mRemoteBthSocketAddress );
}

winBluetoothSocket::~winBluetoothSocket( )
{

}

_ubool winBluetoothSocket::Initialize( AStringPtr remote_address )
{
	mRemoteAddress = remote_address;

	// Get the remote address in UTF-16
	WString remote_address_utf16;
	remote_address_utf16.FromString( mRemoteAddress );

	// Get the BTH address
	_int addr_size = sizeof( mRemoteBthSocketAddress );
	if ( ::WSAStringToAddressW( (LPWSTR) remote_address_utf16.Str( ), AF_BTH, _null, (LPSOCKADDR)&mRemoteBthSocketAddress, &addr_size) != 0 )
		return _false;

	return _true;
}

_void winBluetoothSocket::Connect( )
{
}

AStringR winBluetoothSocket::GetRemoteDeviceAddress( )
{
	return AString( "" );
}

_dword winBluetoothSocket::GetAvailableBytes( )
{
	return 0;
}

_dword winBluetoothSocket::Send( const _byte* buffer, _dword size )
{
	return 0;
}

_dword winBluetoothSocket::Recv( _byte* buffer, _dword size )
{
	return 0;
}

//----------------------------------------------------------------------------
// winBluetoothServerSocket Implementation
//----------------------------------------------------------------------------

winBluetoothServerSocket::winBluetoothServerSocket( )
{
}

winBluetoothServerSocket::~winBluetoothServerSocket( )
{

}

IBluetoothSocketPassRef winBluetoothServerSocket::Accept( _dword timeout )
{
	return _null;
//	return new winBluetoothSocket( );
}

//----------------------------------------------------------------------------
// winBluetoothDevice Implementation
//----------------------------------------------------------------------------

winBluetoothDevice::winBluetoothDevice( )
{

}

winBluetoothDevice::~winBluetoothDevice( )
{

}

_ubool winBluetoothDevice::Initialize( AStringPtr address )
{
	mAddress = address;

	return _true;
}

IBluetoothDevice::_STATE winBluetoothDevice::GetState( ) const
{
	return _STATE_BOND_NONE;
}

IBluetoothDevice::_TYPE winBluetoothDevice::GetType( ) const
{
	return _TYPE_UNKNOWN;
}

IBluetoothSocketPassRef winBluetoothDevice::CreateClientSocket( const UID128& uuid )
{
	// Get the UID string
	AString uid_string = uuid.ToStringA( );

	// Create bluetooth socket
	winBluetoothSocket* socket = new winBluetoothSocket( );
	if ( socket->Initialize( uid_string ) == _false )
		{ EGE_RELEASE( socket ); return _null; }

	return socket;
}

//----------------------------------------------------------------------------
// winBluetoothAdapter Implementation
//----------------------------------------------------------------------------

winBluetoothAdapter::winBluetoothAdapter( )
{
}

winBluetoothAdapter::~winBluetoothAdapter( )
{
}

IBluetoothAdapter::_STATE winBluetoothAdapter::GetState( ) const
{
	return _STATE_OFF;
}

_ubool winBluetoothAdapter::Enable( _ubool enable )
{
	return _true;
}

_ubool winBluetoothAdapter::IsEnabled( ) const
{
	return _true;
}

IBluetoothDevicePassRef winBluetoothAdapter::GetRemoteDevice( AStringPtr address )
{
	winBluetoothDevice* device = new winBluetoothDevice( );
	if ( device->Initialize( address ) == _false )
		{ EGE_RELEASE( device ); return _null; }

	return device;
}

_ubool winBluetoothAdapter::CreateBondOfRemoteDevice( AStringPtr address )
{
	return _false;
}

_ubool winBluetoothAdapter::RemoveBondOfRemoteDevice( AStringPtr address )
{
	return _false;
}

_dword winBluetoothAdapter::GetBondedDevicesNumber( )
{
	return 0;
}

IBluetoothDevicePassRef winBluetoothAdapter::GetBondedDeviceByIndex( _dword index )
{
	return _null;
}

_ubool winBluetoothAdapter::StartDiscovery( )
{
	return _true;
}

_void winBluetoothAdapter::CancelDiscovery( )
{

}

_ubool winBluetoothAdapter::IsDiscovering( ) const
{
	return _true;
}

IBluetoothServerSocketPassRef winBluetoothAdapter::CreateServerSocket( const UID128& uuid )
{
	return new winBluetoothServerSocket( );
}
