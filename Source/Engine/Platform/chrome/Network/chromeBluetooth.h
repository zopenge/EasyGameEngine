//! @file     chromeBluetooth.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeBluetoothSocket
//----------------------------------------------------------------------------

class chromeBluetoothSocket : public TObject< IBluetoothSocket >
{
private:

public:
	chromeBluetoothSocket( );
	virtual ~chromeBluetoothSocket( );

// IBluetoothSocket Interface
public:
	virtual _void	Connect( ) override;

	virtual AString	GetRemoteDeviceAddress( ) override;

	virtual _dword	GetAvailableBytes( ) override;

	virtual _dword	Send( const _byte* buffer, _dword size ) override;
	virtual _dword	Recv( _byte* buffer, _dword size ) override;
};

//----------------------------------------------------------------------------
// chromeBluetoothServerSocket
//----------------------------------------------------------------------------

class chromeBluetoothServerSocket : public TObject< IBluetoothServerSocket >
{
private:

public:
	chromeBluetoothServerSocket( );
	virtual ~chromeBluetoothServerSocket( );

// IBluetoothServerSocket Interface
public:
	virtual IBluetoothSocketPassRef Accept( _dword timeout ) override;
};

//----------------------------------------------------------------------------
// chromeBluetoothDevice
//----------------------------------------------------------------------------

class chromeBluetoothDevice : public TBluetoothDevice< IBluetoothDevice >
{
private:

public:
	chromeBluetoothDevice( );
	virtual ~chromeBluetoothDevice( );

// IBluetoothDevice Interface
public:
	virtual _STATE					GetState( ) const override;
	virtual _TYPE					GetType( ) const override;

	virtual IBluetoothSocketPassRef	CreateClientSocket( const UID128& uuid ) override;
};

//----------------------------------------------------------------------------
// chromeBluetoothAdapter
//----------------------------------------------------------------------------

class chromeBluetoothAdapter : public TBluetoothAdapter< IBluetoothAdapter >
{
private:

public:
	chromeBluetoothAdapter( );
	virtual ~chromeBluetoothAdapter( );

// IBluetoothAdapter Interface
public:
	virtual _STATE							GetState( ) const override;

	virtual _ubool							Enable( _ubool enable ) override;
	virtual _ubool							IsEnabled( ) const override;

	virtual IBluetoothDevicePassRef			GetRemoteDevice( AStringPtr address ) override;
	virtual _ubool							CreateBondOfRemoteDevice( AStringPtr address ) override;
	virtual _ubool							RemoveBondOfRemoteDevice( AStringPtr address ) override;

	virtual _dword							GetBondedDevicesNumber( ) override;
	virtual IBluetoothDevicePassRef			GetBondedDeviceByIndex( _dword index ) override;

	virtual _ubool							StartDiscovery( ) override;
	virtual _void							CancelDiscovery( ) override;
	virtual _ubool							IsDiscovering( ) const override;

	virtual IBluetoothServerSocketPassRef	CreateServerSocket( const UID128& uuid ) override;
};

//----------------------------------------------------------------------------
// chromeBluetoothAdapter Implementation
//----------------------------------------------------------------------------

}