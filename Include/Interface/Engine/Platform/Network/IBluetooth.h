//! @file     IBluetooth.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBluetoothSocket
//----------------------------------------------------------------------------

class IBluetoothSocket : public IObject
{
public:
	//!	Connect.
	//!	@param		none.
	//! @return		none.
	virtual _void Connect( ) PURE;

	//!	Get remote device address.
	//!	@param		none.
	//!	@return		The remote device address.
	virtual AString GetRemoteDeviceAddress( ) PURE;

	//!	Get the available bytes what can recv.
	//!	@param		none.
	//!	@return		The available bytes.
	virtual _dword GetAvailableBytes( ) PURE;

	//!	Send.
	//!	@param		buffer	The buffer data.
	//!	@param		size	The buffer size.
	//! @return		The send bytes.
	virtual _dword Send( const _byte* buffer, _dword size ) PURE;
	//!	Recv.
	//!	@param		buffer	The buffer data.
	//!	@param		size	The buffer size.
	//! @return		The received bytes.
	virtual _dword Recv( _byte* buffer, _dword size ) PURE;
};

//----------------------------------------------------------------------------
// IBluetoothServerSocket
//----------------------------------------------------------------------------

class IBluetoothServerSocket : public IObject
{
public:
	//!	Accept.
	//!	@param		timeout	The time out in milliseconds.
	//! @return		The socket interface.
	virtual IBluetoothSocketPassRef Accept( _dword timeout ) PURE;
};

//----------------------------------------------------------------------------
// IBluetoothDevice
//----------------------------------------------------------------------------

class IBluetoothDevice : public IObject
{
public:
	//!	The state
	enum _STATE
	{
		_STATE_BOND_NONE, 
		_STATE_BOND_BONDING, 
		_STATE_BOND_BONDED
	};

	//!	The type
	enum _TYPE
	{
		_TYPE_UNKNOWN,	//!	Unknown
		_TYPE_CLASSIC,  //! Classic - BR/EDR devices
		_TYPE_LE,		//!	Low Energy - LE-only
		_TYPE_DUAL,		//!	Dual Mode - BR/EDR/LE
	};

public:
	//!	Get the state.
	//!	@param		none.
	//!	@return		The state.
	virtual _STATE GetState( ) const PURE;
	//!	Get the type.
	//!	@param		none.
	//!	@return		The type.
	virtual _TYPE GetType( ) const PURE;
	//!	Get the address.
	//!	@param		none.
	//!	@return		The address.
	virtual AStringPtr GetAddress( ) const PURE;
	//!	Get the device name.
	//!	@param		none.
	//!	@return		The device name.
	virtual AStringPtr GetName( ) const PURE;

	//!	Create client socket.
	//!	@param		uuid		The UUID for server.
	//! @return		The socket interface.
	virtual IBluetoothSocketPassRef CreateClientSocket( const UID128& uuid ) PURE;
};

//----------------------------------------------------------------------------
// IBluetoothAdapterNotifier
//----------------------------------------------------------------------------

class IBluetoothAdapterNotifier : public IObject
{
public:
	//! When a low level (ACL) connection has been established with a remote device.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnACLConnected( IBluetoothDevice* device ) PURE;
	//! When a low level (ACL) disconnection from a remote device.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnACLDisconnected( IBluetoothDevice* device ) PURE;
	//! When that a low level (ACL) disconnection has been requested for a remote device, and it will soon be disconnected.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnACLDisconnectRequested( IBluetoothDevice* device ) PURE;

	//! When a change in the bond state of a remote device.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnBondStateChanged( IBluetoothDevice* device ) PURE;
	//! When bluetooth class of a remote device has changed.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnClassChanged( IBluetoothDevice* device ) PURE;
	//! When the friendly name of a remote device has been retrieved for the first time, or changed since the last retrieval.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnNameChanged( IBluetoothDevice* device ) PURE;

	//! When remote device discovered.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnFoundDevice( IBluetoothDevice* device ) PURE;

	//! When intent is used to broadcast PAIRING REQUEST Requires BLUETOOTH_ADMIN to receive.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnPairingRequest( IBluetoothDevice* device ) PURE;
	//! When intent is used to broadcast the UUID wrapped as a ParcelUuid of the remote device after it has been fetched.
	//!	@param		device		The bluetooth device.
	//!	@return		none.
	virtual _void OnUUID( IBluetoothDevice* device ) PURE;
};

//----------------------------------------------------------------------------
// IBluetoothAdapter
//----------------------------------------------------------------------------

class IBluetoothAdapter : public IObject
{
public:
	//!	The state
	enum _STATE
	{
		_STATE_OFF,			//! Indicates the local Bluetooth adapter is off.
		_STATE_TURNING_ON,	//!	Indicates the local Bluetooth adapter is on, and ready for use.
		_STATE_ON,			//!	Indicates the local Bluetooth adapter is turning off. Local clients should immediately attempt graceful disconnection of any remote links.
		_STATE_TURNING_OFF,	//!	Indicates the local Bluetooth adapter is turning on. However local clients should wait for STATE_ON before attempting to use the adapter.
	};

public:
	//! Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IBluetoothAdapterNotifier* notifier ) PURE;
	//! Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IBluetoothAdapterNotifierRef GetNotifier( ) PURE;

	//! Get the state.
	//!	@param		none.
	//!	@return		The state.
	virtual _STATE GetState( ) const PURE;

	//!	Enable/Disable.
	//!	@param		enable		True indicates enable bluetooth.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Enable( _ubool enable ) PURE;
	//!	Check whether enable or not.
	//!	@param		none.
	//! @return		True indicates enable it.
	virtual _ubool IsEnabled( ) const PURE;

	//!	Get the local bluetooth address.
	//!	@param		none.
	//!	@return		The address.
	virtual AStringPtr GetAddress( ) const PURE;
	//!	Get the local bluetooth device name.
	//!	@param		none.
	//!	@return		The device name.
	virtual AStringPtr GetName( ) const PURE;

	//!	Get remote device by address.
	//!	@param		address		The remote address.
	//!	@return		The bluetooth device.
	virtual IBluetoothDevicePassRef GetRemoteDevice( AStringPtr address ) PURE;
	//!	Create bond of remote device.
	//!	@param		address		The remote address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool CreateBondOfRemoteDevice( AStringPtr address ) PURE;
	//!	Remove bond of remote device.
	//!	@param		address		The remote address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool RemoveBondOfRemoteDevice( AStringPtr address ) PURE;

	//!	Get bonded remote devices number.
	//!	@param		none.
	//!	@return		The number of bluetooth devices.
	virtual _dword GetBondedDevicesNumber( ) PURE;
	//!	Get bonded remote device.
	//!	@param		index		The remote device index.
	//!	@return		The bluetooth device.
	virtual IBluetoothDevicePassRef GetBondedDeviceByIndex( _dword index ) PURE;

	//!	Start discovery.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool StartDiscovery( ) PURE;
	//!	Cancel discovery.
	//!	@param		none.
	//! @return		none.
	virtual _void CancelDiscovery( ) PURE;
	//!	Check whether it's discovering.
	//!	@param		none.
	//!	@return		True indicates it's discovering.
	virtual _ubool IsDiscovering( ) const PURE;

	//!	Create server socket.
	//!	@param		uuid		The UUID for server.
	//! @return		The socket interface.
	virtual IBluetoothServerSocketPassRef CreateServerSocket( const UID128& uuid ) PURE;
};

}