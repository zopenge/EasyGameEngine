//! @file     winBluetooth.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winBluetoothSocket
//----------------------------------------------------------------------------

class winBluetoothSocket : public TObject< IBluetoothSocket >
{
private:
	AString			mRemoteAddress;
	SOCKADDR_BTH	mRemoteBthSocketAddress;

public:
	winBluetoothSocket( );
	virtual ~winBluetoothSocket( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr remote_address );

// IBluetoothSocket Interface
public:
	virtual _void		Connect( ) override;

	virtual AString	GetRemoteDeviceAddress( ) override;

	virtual _dword		GetAvailableBytes( ) override;

	virtual _dword		Send( const _byte* buffer, _dword size ) override;
	virtual _dword		Recv( _byte* buffer, _dword size ) override;
};

//----------------------------------------------------------------------------
// winBluetoothServerSocket
//----------------------------------------------------------------------------

class winBluetoothServerSocket : public TObject< IBluetoothServerSocket >
{
private:

public:
	winBluetoothServerSocket( );
	virtual ~winBluetoothServerSocket( );

// IBluetoothServerSocket Interface
public:
	virtual IBluetoothSocketPassRef Accept( _dword timeout ) override;
};

//----------------------------------------------------------------------------
// winBluetoothDevice
//----------------------------------------------------------------------------

class winBluetoothDevice : public TBluetoothDevice< IBluetoothDevice >
{
private:
	AString	mAddress;

public:
	winBluetoothDevice( );
	virtual ~winBluetoothDevice( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr address );

// IBluetoothDevice Interface
public:
	virtual _STATE					GetState( ) const override;
	virtual _TYPE					GetType( ) const override;

	virtual IBluetoothSocketPassRef	CreateClientSocket( const UID128& uuid ) override;
};

//----------------------------------------------------------------------------
// winBluetoothAdapter
//----------------------------------------------------------------------------

class winBluetoothAdapter : public TBluetoothAdapter< IBluetoothAdapter >
{
private:

public:
	winBluetoothAdapter( );
	virtual ~winBluetoothAdapter( );

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
// winBluetoothAdapter Implementation
//----------------------------------------------------------------------------

}