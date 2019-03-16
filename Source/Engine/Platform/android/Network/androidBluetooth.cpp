//! @file     androidBluetoothAdapter.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnACLConnected, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnACLConnected( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnACLDisconnected, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnACLDisconnected( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnACLDisconnectRequested, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnACLDisconnectRequested( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnBondStateChanged, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnBondStateChanged( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnClassChanged, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnClassChanged( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnNameChanged, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnNameChanged( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnFoundDevice, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnFoundDevice( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnPairingRequest, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnPairingRequest( &device );
}

JNI_FUNC_1( void, AndroidBluetoothAdapter, OnUUID, jobject js_device )
{
	androidBluetoothDevice device;
	device.Initialize( js_device );

	GetBluetoothAdapter( )->GetNotifier( )->OnUUID( &device );
}

//----------------------------------------------------------------------------
// androidBluetoothSocket Implementation
//----------------------------------------------------------------------------

androidBluetoothSocket::androidBluetoothSocket( )
{
}

androidBluetoothSocket::~androidBluetoothSocket( )
{

}

_ubool androidBluetoothSocket::Initialize( jobject socket )
{
	if ( mBluetoothSocket.Initialize( _true, "com/ege/android/AndroidBluetoothSocket", socket ) == _false )
		return _false;

	return _true;
}

_void androidBluetoothSocket::Connect( )
{
	// Get the remote device address
	AString remote_device_address = GetRemoteDeviceAddress( );

	// Connect to remote device
	ALOG_TRACE_1( "Connecting to '%s' bluetooth remote server ...", remote_device_address.Str( ) );
	mBluetoothSocket.CallVoidMethod( "connect", "()V" );
	ALOG_TRACE_1( "Connected to '%s' bluetooth remote server OK", remote_device_address.Str( ) );
}

AStringR androidBluetoothSocket::GetRemoteDeviceAddress( )
{
	jstring js_address = (jstring) mBluetoothSocket.CallObjectMethod( "getRemoteDeviceAddress", "()Ljava/lang/String;" );
	if ( js_address == _null )
	{
		ALOG_ERROR( "Get BT remote device address failed" );
		return AString( "" );
	}

	return J2CString( js_address ).ToStringA( );
}

_dword androidBluetoothSocket::GetAvailableBytes( )
{
	return mBluetoothSocket.CallIntMethod( "getAvailableBytes", "()I" );
}

_dword androidBluetoothSocket::Send( const _byte* buffer, _dword size )
{
	C2JArray js_buffer( size, buffer );

	_dword send_size = mBluetoothSocket.CallIntMethod( "send", "([B)I", js_buffer.ToJArray( ) );
	return send_size;
}

_dword androidBluetoothSocket::Recv( _byte* buffer, _dword size )
{
	C2JArray js_buffer( size );

	_dword recv_size = mBluetoothSocket.CallIntMethod( "recv", "([B)I", js_buffer.ToJArray( ) );
	if ( recv_size != size )
	{
		ALOG_TRACE_2( "androidBluetoothSocket::recv( ) recv_size : %d, size : %d", recv_size, size );
		return -1;
	}

	js_buffer.ReadBuffer( 0, recv_size, buffer );

	return recv_size;
}

//----------------------------------------------------------------------------
// androidBluetoothServerSocket Implementation
//----------------------------------------------------------------------------

androidBluetoothServerSocket::androidBluetoothServerSocket( )
{
}

androidBluetoothServerSocket::~androidBluetoothServerSocket( )
{

}

_ubool androidBluetoothServerSocket::Initialize( jobject socket )
{
	if ( mBluetoothServerSocket.Initialize( _true, "com/ege/android/AndroidBluetoothServerSocket", socket ) == _false )
		return _false;

	return _true;
}

IBluetoothSocketPassRef androidBluetoothServerSocket::Accept( _dword timeout )
{
	jobject js_socket = (jobject) mBluetoothServerSocket.CallObjectMethod( "accept", "(I)Lcom/ege/android/AndroidBluetoothSocket;", jint( timeout ) );
	if ( js_socket == _null )
		return _null;

	androidBluetoothSocket* socket = new androidBluetoothSocket( );
	if ( socket->Initialize( js_socket ) == _false )
		{ EGE_RELEASE( socket ); return _null; }

	return socket;
}

//----------------------------------------------------------------------------
// androidBluetoothDevice Implementation
//----------------------------------------------------------------------------

androidBluetoothDevice::androidBluetoothDevice( )
{

}

androidBluetoothDevice::~androidBluetoothDevice( )
{

}

_ubool androidBluetoothDevice::GetDeviceName( )
{
	jstring js_name = (jstring) mBluetoothDevice.CallObjectMethod( "getName", "()Ljava/lang/String;" );
	if ( js_name == _null )
	{
		ALOG_ERROR( "Get BT device name failed" );
		return _false;
	}

	mName = J2CString( js_name ).ToStringA( );

	ALOG_TRACE_1( "Device name: %s", mName.Str( ) );

	return _true;
}

_ubool androidBluetoothDevice::GetDeviceAddress( )
{
	jstring js_address = (jstring) mBluetoothDevice.CallObjectMethod( "getAddress", "()Ljava/lang/String;" );
	if ( js_address == _null )
	{
		ALOG_ERROR( "Get BT device address failed" );
		return _false;
	}

	mAddress = J2CString( js_address ).ToStringA( );

	ALOG_TRACE_1( "Device address: %s", mAddress.Str( ) );

	return _true;
}

_ubool androidBluetoothDevice::Initialize( jobject device )
{
	if ( mBluetoothDevice.Initialize( _true, "com/ege/android/AndroidBluetoothDevice", device ) == _false )
		return _false;

	// Get name
	if ( GetDeviceName( ) == _false )
		return _false;

	// Get address
	if ( GetDeviceAddress( ) == _false )
		return _false;

	return _true;
}

IBluetoothDevice::_STATE androidBluetoothDevice::GetState( ) const
{
	_dword state = mBluetoothDevice.CallIntMethod( "getBondState", "()I" );
	switch ( state )
	{
		case 0x0000000A: return _STATE_BOND_NONE;
		case 0x0000000B: return _STATE_BOND_BONDING;
		case 0x0000000C: return _STATE_BOND_BONDED;
		default:
			break;
	}

	return _STATE_BOND_NONE;
}

IBluetoothDevice::_TYPE androidBluetoothDevice::GetType( ) const
{
	_dword type = mBluetoothDevice.CallIntMethod( "getType", "()I" );
	switch ( type )
	{
		case 0x00000000: return _TYPE_UNKNOWN;
		case 0x00000001: return _TYPE_CLASSIC;
		case 0x00000002: return _TYPE_LE;
		case 0x00000003: return _TYPE_DUAL;
		default:
			break;
	}

	return _TYPE_UNKNOWN;
}

IBluetoothSocketPassRef androidBluetoothDevice::CreateClientSocket( const UID128& uuid )
{
	C2JString js_uuid( uuid.ToStringU( ) );

	jobject js_socket = (jobject) mBluetoothDevice.CallObjectMethod( "createClientSocket", "(Ljava/lang/String;)Lcom/ege/android/AndroidBluetoothSocket;", js_uuid.ToJString( ) );
	if ( js_socket == _null )
		return _null;

	androidBluetoothSocket* socket = new androidBluetoothSocket( );
	if ( socket->Initialize( js_socket ) == _false )
		{ EGE_RELEASE( socket ); return _null; }

	return socket;
}

//----------------------------------------------------------------------------
// androidBluetoothAdapter Implementation
//----------------------------------------------------------------------------

androidBluetoothAdapter::androidBluetoothAdapter( )
{
	mBluetoothAdapter.Initialize( "com/ege/android/AndroidBluetoothAdapter", _false );
	mBluetoothAdapter.CallStaticVoidMethod( "init", "()V" );
}

androidBluetoothAdapter::~androidBluetoothAdapter( )
{
	mBluetoothAdapter.CallStaticVoidMethod( "uninit", "()V" );
}

IBluetoothAdapter::_STATE androidBluetoothAdapter::GetState( ) const
{
	_dword state = mBluetoothAdapter.CallStaticIntMethod( "getState", "()I" );
	switch ( state )
	{
		case 0x0000000A: return _STATE_OFF;
		case 0x0000000B: return _STATE_TURNING_ON;
		case 0x0000000C: return _STATE_ON;
		case 0x0000000D: return _STATE_TURNING_OFF;
		default:
			break;
	}

	return _STATE_OFF;
}

_ubool androidBluetoothAdapter::Enable( _ubool enable )
{
	if ( mBluetoothAdapter.CallStaticBooleanMethod( "enable", "(Z)Z", jboolean( enable ) ) == _false )
		return _false;

	// Get address
	jstring js_address = (jstring) mBluetoothAdapter.CallStaticObjectMethod( "getAddress", "()Ljava/lang/String;" );
	if ( js_address == _null )
		return _false;

	mAddress = J2CString( js_address ).ToStringA( );

	// Get name
	jstring js_name = (jstring) mBluetoothAdapter.CallStaticObjectMethod( "getName", "()Ljava/lang/String;" );
	if ( js_name == _null )
		return _false;

	mName = J2CString( js_name ).ToStringA( );

	return _true;
}

_ubool androidBluetoothAdapter::IsEnabled( ) const
{
	return mBluetoothAdapter.CallStaticBooleanMethod( "isEnabled", "()Z" );
}

IBluetoothDevicePassRef androidBluetoothAdapter::GetRemoteDevice( AStringPtr address )
{
	C2JString js_address( address );

	jobject js_device = (jobject) mBluetoothAdapter.CallStaticObjectMethod( "getRemoteDevice", "(Ljava/lang/String;)Lcom/ege/android/AndroidBluetoothDevice;", js_address.ToJString( ) );
	if ( js_device == _null )
	{
		ALOG_ERROR_1( "The '%s' remote BT device is not existing when get remote device", address.Str( ) );
		return _null;
	}

	androidBluetoothDevice* device = new androidBluetoothDevice( );
	if ( device->Initialize( js_device ) == _false )
		{ EGE_RELEASE( device ); return _null; }

	return device;
}

_ubool androidBluetoothAdapter::CreateBondOfRemoteDevice( AStringPtr address )
{
	C2JString js_address( address );

	jobject js_device = (jobject) mBluetoothAdapter.CallStaticObjectMethod( "getRemoteDevice", "(Ljava/lang/String;)Lcom/ege/android/AndroidBluetoothDevice;", js_address.ToJString( ) );
	if ( js_device == _null )
	{
		ALOG_ERROR_1( "The '%s' remote BT device is not existing when create bond of it", address.Str( ) );
		return _false;
	}

	if ( mBluetoothAdapter.CallStaticBooleanMethod( "createBond", "(Lcom/ege/android/AndroidBluetoothDevice;)Z", js_device ) == _false )
	{
		ALOG_ERROR_1( "Create bond of '%s' remote BT device failed", address.Str( ) );
		return _false;
	}

	return _true;
}

_ubool androidBluetoothAdapter::RemoveBondOfRemoteDevice( AStringPtr address )
{
	C2JString js_address( address );

	jobject js_device = (jobject) mBluetoothAdapter.CallStaticObjectMethod( "getRemoteDevice", "(Ljava/lang/String;)Lcom/ege/android/AndroidBluetoothDevice;", js_address.ToJString( ) );
	if ( js_device == _null )
	{
		ALOG_ERROR_1( "The '%s' remote BT device is not existing when remove bond of it", address.Str( ) );
		return _false;
	}

	if ( mBluetoothAdapter.CallStaticBooleanMethod( "removeBond", "(Lcom/ege/android/AndroidBluetoothDevice;)Z", js_device ) == _false )
	{
		ALOG_ERROR_1( "Remove bond of '%s' remote BT device failed", address.Str( ) );
		return _false;
	}

	return _true;
}

_dword androidBluetoothAdapter::GetBondedDevicesNumber( )
{
	return mBluetoothAdapter.CallStaticIntMethod( "getBondedDevicesNumber", "()I" );
}

IBluetoothDevicePassRef androidBluetoothAdapter::GetBondedDeviceByIndex( _dword index )
{
	jobject js_device = (jobject) mBluetoothAdapter.CallStaticObjectMethod( "getBondedDeviceByIndex", "(I)Lcom/ege/android/AndroidBluetoothDevice;", jint( index ) );
	if ( js_device == _null )
		return _null;

	androidBluetoothDevice* device = new androidBluetoothDevice( );
	if ( device->Initialize( js_device ) == _false )
		{ EGE_RELEASE( device ); return _null; }

	return device;
}

_ubool androidBluetoothAdapter::StartDiscovery( )
{
	return mBluetoothAdapter.CallStaticBooleanMethod( "startDiscovery", "()Z" );
}

_void androidBluetoothAdapter::CancelDiscovery( )
{
	mBluetoothAdapter.CallStaticBooleanMethod( "cancelDiscovery", "()Z" );
}

_ubool androidBluetoothAdapter::IsDiscovering( ) const
{
	return mBluetoothAdapter.CallStaticBooleanMethod( "isDiscovering", "()Z" );
}

IBluetoothServerSocketPassRef androidBluetoothAdapter::CreateServerSocket( const UID128& uuid )
{
	C2JString js_uuid( uuid.ToStringU( ) );

	jobject js_socket = (jobject) mBluetoothAdapter.CallStaticObjectMethod( "createServerSocket", "(Ljava/lang/String;)Lcom/ege/android/AndroidBluetoothServerSocket;", js_uuid.ToJString( ) );
	if ( js_socket == _null )
		return _null;

	androidBluetoothServerSocket* socket = new androidBluetoothServerSocket( );
	if ( socket->Initialize( js_socket ) == _false )
		{ EGE_RELEASE( socket ); return _null; }

	return socket;
}
