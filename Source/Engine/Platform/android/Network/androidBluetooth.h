//! @file     androidBluetooth.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidBluetoothSocket
//----------------------------------------------------------------------------

class androidBluetoothSocket : public TObject< IBluetoothSocket >
{
private:
	JNIObject mBluetoothSocket;

public:
	androidBluetoothSocket( );
	virtual ~androidBluetoothSocket( );

public:
	//!	Initialize.
	_ubool Initialize( jobject socket );

// IBluetoothSocket Interface
public:
	virtual _void		Connect( ) override;

	virtual AStringR	GetRemoteDeviceAddress( ) override;

	virtual _dword		GetAvailableBytes( ) override;

	virtual _dword		Send( const _byte* buffer, _dword size ) override;
	virtual _dword		Recv( _byte* buffer, _dword size ) override;
};

//----------------------------------------------------------------------------
// androidBluetoothServerSocket
//----------------------------------------------------------------------------

class androidBluetoothServerSocket : public TObject< IBluetoothServerSocket >
{
private:
	JNIObject mBluetoothServerSocket;

public:
	androidBluetoothServerSocket( );
	virtual ~androidBluetoothServerSocket( );

public:
	//!	Initialize.
	_ubool Initialize( jobject socket );

// IBluetoothServerSocket Interface
public:
	virtual IBluetoothSocketPassRef Accept( _dword timeout ) override;
};

//----------------------------------------------------------------------------
// androidBluetoothDevice
//----------------------------------------------------------------------------

class androidBluetoothDevice : public TBluetoothDevice< IBluetoothDevice >
{
private:
	JNIObject mBluetoothDevice;

private:
	//!	Get device name.
	_ubool GetDeviceName( );
	//!	Get device address.
	_ubool GetDeviceAddress( );

public:
	androidBluetoothDevice( );
	virtual ~androidBluetoothDevice( );

public:
	//!	Initialize.
	_ubool Initialize( jobject device );

// IBluetoothDevice Interface
public:
	virtual _STATE					GetState( ) const override;
	virtual _TYPE					GetType( ) const override;

	virtual IBluetoothSocketPassRef	CreateClientSocket( const UID128& uuid ) override;
};

//----------------------------------------------------------------------------
// androidBluetoothAdapter
//----------------------------------------------------------------------------

class androidBluetoothAdapter : public TBluetoothAdapter< IBluetoothAdapter >
{
private:
	JNIObject	mBluetoothAdapter;

public:
	androidBluetoothAdapter( );
	virtual ~androidBluetoothAdapter( );

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
// androidBluetoothAdapter Implementation
//----------------------------------------------------------------------------

}