//! @file     iosBluetooth.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosBluetoothSocketBase
//----------------------------------------------------------------------------

template< typename Type >
class iosBluetoothSocketBase : public TObject< Type >
{
protected:
	IStreamWriterRef	mStreamWriter;

protected:
	iosBluetoothSocketBase( ) 
	{
		mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( 64 KB );
	}
	virtual ~iosBluetoothSocketBase( ) 
	{
	}

public:
	//!	Write received stream data.
	_void WriteReceivedStreamData( const _byte* data, _dword size )
	{
		mStreamWriter->WriteBuffer( data, size );
	}
};

//----------------------------------------------------------------------------
// iosBluetoothSocket
//----------------------------------------------------------------------------

class iosBluetoothSocket : public iosBluetoothSocketBase< IBluetoothSocket >
{
	INTERNAL_HANDLER_DECL( );

public:
	iosBluetoothSocket( );
	virtual ~iosBluetoothSocket( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr remote_address, const UID128& remote_uuid, _handle device );

	//!	Start service.
	_ubool StartService( );
	//!	Send data.
	_void SendData( );

// IBluetoothSocket Interface
public:
	virtual _void		Connect( ) override;

	virtual AStringR	GetRemoteDeviceAddress( ) override;

	virtual _dword		GetAvailableBytes( ) override;

	virtual _dword		Send( const _byte* buffer, _dword size ) override;
	virtual _dword		Recv( _byte* buffer, _dword size ) override;
};

//----------------------------------------------------------------------------
// iosBluetoothServerSocket
//----------------------------------------------------------------------------

class iosBluetoothServerSocket : public iosBluetoothSocketBase< IBluetoothServerSocket >
{
	INTERNAL_HANDLER_DECL( );

private:
	typedef Queue< IBluetoothSocketPassRef > SocketArray;

private:
	Lock		mLocker;

	SocketArray	mClients;

public:
	iosBluetoothServerSocket( );
	virtual ~iosBluetoothServerSocket( );

public:
    //! Initialize.
    _ubool Initialize( const UID128& uuid );
    
	//!	Accept client.
	_void AcceptClient( _void* peer_id );

// IBluetoothServerSocket Interface
public:
	virtual IBluetoothSocketPassRef Accept( _dword timeout ) override;
};

//----------------------------------------------------------------------------
// iosBluetoothDevice
//----------------------------------------------------------------------------

class iosBluetoothDevice : public TBluetoothDevice< IBluetoothDevice >
{
	INTERNAL_HANDLER_DECL( );

public:
	iosBluetoothDevice( );
	virtual ~iosBluetoothDevice( );

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
// iosBluetoothAdapter
//----------------------------------------------------------------------------

class iosBluetoothAdapter : public TBluetoothAdapter< IBluetoothAdapter >
{
	INTERNAL_HANDLER_DECL( );

private:
	//!	True indicates it's discovering.
	_ubool	mIsDiscovering;

public:
	iosBluetoothAdapter( );
	virtual ~iosBluetoothAdapter( );

public:
	//!	Update the match peripheral.
	_void UpdateMatchPeripheral( _handle peripheral );
	//!	Scan the peripheral.
	_handle ScanPeripheral( const UID128& uuid );
	//!	Connect the peripheral.
	_void ConnectPeripheral( _handle peripheral );

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
// iosBluetoothAdapter Implementation
//----------------------------------------------------------------------------

}
