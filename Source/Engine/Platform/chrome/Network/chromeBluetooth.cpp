//! @file     chromeBluetoothAdapter.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromeBluetoothSocket Implementation
//----------------------------------------------------------------------------

chromeBluetoothSocket::chromeBluetoothSocket( )
{
}

chromeBluetoothSocket::~chromeBluetoothSocket( )
{

}

_void chromeBluetoothSocket::Connect( )
{
}

AString chromeBluetoothSocket::GetRemoteDeviceAddress( )
{
	return "";
}

_dword chromeBluetoothSocket::GetAvailableBytes( )
{
	return 0;
}

_dword chromeBluetoothSocket::Send( const _byte* buffer, _dword size )
{
	return -1;
}

_dword chromeBluetoothSocket::Recv( _byte* buffer, _dword size )
{
	return -1;
}

//----------------------------------------------------------------------------
// chromeBluetoothServerSocket Implementation
//----------------------------------------------------------------------------

chromeBluetoothServerSocket::chromeBluetoothServerSocket( )
{
}

chromeBluetoothServerSocket::~chromeBluetoothServerSocket( )
{

}

IBluetoothSocketPassRef chromeBluetoothServerSocket::Accept( _dword timeout )
{
	return _null;
}

//----------------------------------------------------------------------------
// chromeBluetoothDevice Implementation
//----------------------------------------------------------------------------

chromeBluetoothDevice::chromeBluetoothDevice( )
{

}

chromeBluetoothDevice::~chromeBluetoothDevice( )
{

}

IBluetoothDevice::_STATE chromeBluetoothDevice::GetState( ) const
{
	return _STATE_BOND_NONE;
}

IBluetoothDevice::_TYPE chromeBluetoothDevice::GetType( ) const
{
	return _TYPE_UNKNOWN;
}

IBluetoothSocketPassRef chromeBluetoothDevice::CreateClientSocket( const UID128& uuid )
{
	return _null;
}

//----------------------------------------------------------------------------
// chromeBluetoothAdapter Implementation
//----------------------------------------------------------------------------

chromeBluetoothAdapter::chromeBluetoothAdapter( )
{
}

chromeBluetoothAdapter::~chromeBluetoothAdapter( )
{
}

IBluetoothAdapter::_STATE chromeBluetoothAdapter::GetState( ) const
{
	return _STATE_OFF;
}

_ubool chromeBluetoothAdapter::Enable( _ubool enable )
{
	return _true;
}

_ubool chromeBluetoothAdapter::IsEnabled( ) const
{
	return _false;
}

IBluetoothDevicePassRef chromeBluetoothAdapter::GetRemoteDevice( AStringPtr address )
{
	return _null;
}

_ubool chromeBluetoothAdapter::CreateBondOfRemoteDevice( AStringPtr address )
{
	return _true;
}

_ubool chromeBluetoothAdapter::RemoveBondOfRemoteDevice( AStringPtr address )
{
	return _true;
}

_dword chromeBluetoothAdapter::GetBondedDevicesNumber( )
{
	return 0;
}

IBluetoothDevicePassRef chromeBluetoothAdapter::GetBondedDeviceByIndex( _dword index )
{
	return _null;
}

_ubool chromeBluetoothAdapter::StartDiscovery( )
{
	return _false;
}

_void chromeBluetoothAdapter::CancelDiscovery( )
{
}

_ubool chromeBluetoothAdapter::IsDiscovering( ) const
{
	return _false;
}

IBluetoothServerSocketPassRef chromeBluetoothAdapter::CreateServerSocket( const UID128& uuid )
{
	return _null;
}
