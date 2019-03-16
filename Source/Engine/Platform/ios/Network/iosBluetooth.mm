//! @file     iosBluetoothAdapter.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

static iosBluetoothAdapter* gBluetoothAdapter	= _null;
static CBCentralManager*	gCentralManager		= _null;
static CBPeripheralManager*	gPeripheralManager	= _null;

//----------------------------------------------------------------------------
// iosCBPeripheralManagerDelegate Implementation
//----------------------------------------------------------------------------

@interface iosCBPeripheralManagerDelegate : NSObject< CBPeripheralManagerDelegate >

@property (nonatomic, assign) iosBluetoothSocket*	mSocket;

@end

@implementation iosCBPeripheralManagerDelegate

// Invoked when a remote central device subscribes to a characteristic¡¯s value.
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    NSLog(@"Central subscribed to characteristic");

    // Start sending
	self.mSocket->SendData( );
}

// Invoked when a remote central device unsubscribes from a characteristic¡¯s value.
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{	
    NSLog(@"Central unsubscribed from characteristic");
}

// Invoked when you publish a service, and any of its associated characteristics and characteristic descriptors, to the local Generic Attribute Profile (GATT) database.
- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error
{
}

// Invoked when a local peripheral device receives an Attribute Protocol (ATT) read request for a characteristic that has a dynamic value.
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request
{
}

// Invoked when a local peripheral device receives an Attribute Protocol (ATT) write request for a characteristic that has a dynamic value.
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests
{
}

// Invoked when you start advertising the local peripheral device¡¯s data.
- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error
{
}

// Invoked when the peripheral manager's state is updated. (required)
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    // Opt out from any other state
    if (peripheral.state != CBPeripheralManagerStatePoweredOn)
        return;
    
    // We're in CBPeripheralManagerStatePoweredOn state...
    NSLog(@"self.peripheralManager powered on.");
    
    // ... so build our service.
	self.mSocket->StartService( );
}

// Invoked when a local peripheral device is again ready to send characteristic value updates. (required)
- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    // Start sending again
	self.mSocket->SendData( );
}

@end

//----------------------------------------------------------------------------
// iosCBCentralManagerDelegate Implementation
//----------------------------------------------------------------------------

@interface iosCBCentralManagerDelegate : NSObject< CBCentralManagerDelegate, CBPeripheralDelegate >

@property (nonatomic, assign) NSString*		mServiceUUID;
@property (nonatomic, assign) NSString*		mCharacteristicUUID;
@property (nonatomic, strong) CBPeripheral*	mDiscoveredPeripheral;

@end

@implementation iosCBCentralManagerDelegate

// CBCentralManagerDelegate

// Invoked when a connection is successfully created with a peripheral.
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
{
	NSLog(@"Peripheral Connected"); 

	// Stop scanning 
	[gCentralManager stopScan];
	NSLog(@"Scanning stopped"); 

    // Clear the data that we may already have
//    [self.data setLength:0];

	// Make sure we get the discovery callbacks 
	peripheral.delegate = self; 

	// Search only for services that match our UUID 
	[peripheral discoverServices:@[[CBUUID UUIDWithString:[self mServiceUUID]]]];
}

// Invoked when an existing connection with a peripheral is torn down.
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"Peripheral Disconnected");
}

// Invoked when the central manager discovers a peripheral while scanning.
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
    // Reject any where the value is above reasonable range
    if (RSSI.integerValue > -15)
        return;
        
    // Reject if the signal strength is too low to be close enough (Close is around -22dB)
    if (RSSI.integerValue < -35)
        return;

    NSLog(@"Discovered %@ at %@", peripheral.name, RSSI);

	// Ok, it's in range - have we already seen it? 
	if ([self mDiscoveredPeripheral] != peripheral)
	{
		// Save a local copy of the peripheral, so CoreBluetooth doesn't get rid of it 
		self.mDiscoveredPeripheral = peripheral;
	}
}

// Invoked when the central manager fails to create a connection with a peripheral.
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"Failed to connect to %@. (%@)", peripheral, [error localizedDescription]);
    [self cleanup];
}

// Invoked when the central manager retrieves a list of peripherals currently connected to the system.
- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals
{
}

// Invoked when the central manager retrieves a list of known peripherals.
- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals
{
}

// Invoked when the central manager¡¯s state is updated. (required)
- (void)centralManagerDidUpdateState:(CBCentralManager *)central
{
}

// CBPeripheralDelegate

// Invoked when you discover the characteristics of a specified service.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
{
    // Deal with errors (if any)
    if (error) 
	{
        NSLog(@"Error discovering characteristics: %@", [error localizedDescription]);
        [self cleanup];
        return;
    }
    
    // Again, we loop through the array, just in case.
    for (CBCharacteristic *characteristic in service.characteristics) 
	{
        // And check if it's the right one
        if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:self.mCharacteristicUUID]])
		{
            // If it is, subscribe to it
            [peripheral setNotifyValue:YES forCharacteristic:characteristic];
        }
    }
    
    // Once this is complete, we just need to wait for the data to come in.
}

// Invoked when you discover the descriptors of a specified characteristic.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

// Invoked when you discover the included services of a specified service.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(NSError *)error
{
}

// Invoked when you discover the peripheral¡¯s available services.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error
{
	if (error) 
	{ 
		NSLog(@"Error discovering services: %@", [error localizedDescription]); 
		[self cleanup]; 
		return;
	}

	// Discover the characteristic we want... 

	// Loop through the newly filled peripheral.services array, just in case there's more than one. 
	for (CBService *service in peripheral.services) 
		[peripheral discoverCharacteristics:@[[CBUUID UUIDWithString:self.mCharacteristicUUID]] forService:service];
}

// Invoked when a peripheral¡¯s services have changed.
- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray *)invalidatedServices
{
}

// Invoked when the peripheral receives a request to start or stop providing notifications for a specified characteristic¡¯s value.
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    if (error) 
	{
        NSLog(@"Error changing notification state: %@", error.localizedDescription);
    }
    
    // Exit if it's not the transfer characteristic
    if (![characteristic.UUID isEqual:[CBUUID UUIDWithString:self.mCharacteristicUUID]])
	{
        return;
    }
    
    // Notification has started
    if (characteristic.isNotifying) 
	{
        NSLog(@"Notification began on %@", characteristic);
    }
    // Notification has stopped
    else 
	{
        // so disconnect from the peripheral
        NSLog(@"Notification stopped on %@.  Disconnecting", characteristic);
        [gCentralManager cancelPeripheralConnection:peripheral];
    }
}

// Invoked when you retrieve a specified characteristic¡¯s value, or when the peripheral device notifies your app that the characteristic¡¯s value has changed.
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    if (error) 
	{
        NSLog(@"Error discovering characteristics: %@", [error localizedDescription]);
        return;
    }
    
    NSString *stringFromData = [[NSString alloc] initWithData:characteristic.value encoding:NSUTF8StringEncoding];
    
    // Have we got everything we need?
    if ([stringFromData isEqualToString:@"EOM"]) {
        
        // We have, so show the data, 
//        [self.textview setText:[[NSString alloc] initWithData:self.data encoding:NSUTF8StringEncoding]];
        
        // Cancel our subscription to the characteristic
        [peripheral setNotifyValue:NO forCharacteristic:characteristic];
        
        // and disconnect from the peripehral
        [gCentralManager cancelPeripheralConnection:peripheral];
    }

    // Otherwise, just add the data on to what we already have
//    [self.data appendData:characteristic.value];
    
    // Log it
    NSLog(@"Received: %@", stringFromData);
}

// Invoked when you retrieve a specified characteristic descriptor¡¯s value.
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
{
}

// Invoked when you write data to a characteristic¡¯s value.
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

// Invoked when you write data to a characteristic descriptor¡¯s value.
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
{
}

// Invoked when a peripheral¡¯s name changes.
- (void)peripheralDidUpdateName:(CBPeripheral *)peripheral
{
}

// Invoked when you retrieve the value of the peripheral¡¯s current RSSI while it is connected to the central manager.
- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(NSError *)error
{
}

/** Call this when things either go wrong, or you're done with the connection.
 *  This cancels any subscriptions if there are any, or straight disconnects if not.
 *  (didUpdateNotificationStateForCharacteristic will cancel the connection if a subscription is involved)
 */
- (void)cleanup
{
    // Don't do anything if we're not connected
    if (self.mDiscoveredPeripheral.state != CBPeripheralStateConnected) {
        return;
    }
    
    // See if we are subscribed to a characteristic on the peripheral
    if (self.mDiscoveredPeripheral.services != nil) {
        for (CBService *service in self.mDiscoveredPeripheral.services) {
            if (service.characteristics != nil) {
                for (CBCharacteristic *characteristic in service.characteristics) {
                    if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:self.mCharacteristicUUID]]) {
                        if (characteristic.isNotifying) {
                            // It is notifying, so unsubscribe
                            [self.mDiscoveredPeripheral setNotifyValue:NO forCharacteristic:characteristic];
                            
                            // And we're done.
                            return;
                        }
                    }
                }
            }
        }
    }
    
    // If we've got this far, we're connected, but we're not subscribed, so we just disconnect
    [gCentralManager cancelPeripheralConnection:self.mDiscoveredPeripheral];
}

@end

//----------------------------------------------------------------------------
// iosBluetoothSocket Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( iosBluetoothSocket )
	AString						mRemoteAddress;
	UID128						mRemoteUUID;

	NSString*					mServiceUUID;
	NSString*					mCharacteristicUUID;

	CBMutableCharacteristic*	mTransferCharacteristic;

	CBPeripheral*				mDevice;

	Lock						mLocker;
	IStreamWriterRef			mSender;
	IStreamWriterRef			mRecver;

    INTERNAL_HANDLER_CONSTRUCTOR( )
    {
		mServiceUUID			= nil;
		mCharacteristicUUID		= nil;

		mTransferCharacteristic	= nil;

		mDevice					= nil;
	}
INTERNAL_HANDLER_IMPL_END( )

iosBluetoothSocket::iosBluetoothSocket( )
{
	INTERNAL_HANDLER_CREATE( );
}

iosBluetoothSocket::~iosBluetoothSocket( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool iosBluetoothSocket::Initialize( AStringPtr remote_address, const UID128& remote_uuid, _handle device )
{
	INTERNAL_HANDLER( )->mRemoteAddress			= remote_address;
	INTERNAL_HANDLER( )->mRemoteUUID			= remote_uuid;
	INTERNAL_HANDLER( )->mDevice				= (__bridge CBPeripheral*) device;
	INTERNAL_HANDLER( )->mServiceUUID			= NSPlatform::Utf8ToNSString( remote_uuid.ToStringU( ) );
	INTERNAL_HANDLER( )->mCharacteristicUUID	= NSPlatform::Utf8ToNSString( remote_uuid.Negation( ).ToStringU( ) );
	INTERNAL_HANDLER( )->mSender				= GetInterfaceFactory( )->CreateMemStreamWriter( 64 KB );
	INTERNAL_HANDLER( )->mRecver				= GetInterfaceFactory( )->CreateMemStreamWriter( 64 KB );

	return _true;
}

_ubool iosBluetoothSocket::StartService( )
{
    // Start with the CBMutableCharacteristic
    INTERNAL_HANDLER( )->mTransferCharacteristic = [[CBMutableCharacteristic alloc] initWithType: [CBUUID UUIDWithString:INTERNAL_HANDLER( )->mCharacteristicUUID] 
		properties:CBCharacteristicPropertyNotify 
		value:nil 
		permissions:CBAttributePermissionsReadable];

    // Then the service
    CBMutableService *transferService	= [[CBMutableService alloc] initWithType:[CBUUID UUIDWithString:INTERNAL_HANDLER( )->mServiceUUID] primary:YES];
    transferService.characteristics		= @[INTERNAL_HANDLER( )->mTransferCharacteristic];
    
    // And add it to the peripheral manager
    [gPeripheralManager addService:transferService];

	return _true;
}

_void iosBluetoothSocket::SendData( )
{
	// Prepare to send data
	INTERNAL_HANDLER( )->mLocker.Enter( );
	// Get the total size what will send
	_dword total_size = INTERNAL_HANDLER( )->mSender->GetOffset( );
	// Copy the buffer what will send
	MemArrayPtr< _byte > buffer; buffer.Create( total_size, INTERNAL_HANDLER( )->mSender->GetBuffer( ) );
	INTERNAL_HANDLER( )->mLocker.Leave( );

    // Start to send
	_dword send_size = 0;
	while ( send_size < total_size )
	{
        _dword size = total_size - send_size;
		size = Math::Min< _dword >( 4 KB, size );
        
        // Copy out the data we want
        NSData *chunk = [NSData dataWithBytes:buffer.GetPointer( ) + send_size length:size];
        
        // Send it
        if (![gPeripheralManager updateValue:chunk forCharacteristic:INTERNAL_HANDLER( )->mTransferCharacteristic onSubscribedCentrals:nil])
			break;
        
        // It did send, so update our index
        send_size += size;
    }

	// Remove send buffer
	INTERNAL_HANDLER( )->mLocker.Enter( );
	INTERNAL_HANDLER( )->mSender->RemoveBuffer( send_size );
	INTERNAL_HANDLER( )->mLocker.Leave( );
}

_void iosBluetoothSocket::Connect( )
{
	gBluetoothAdapter->ConnectPeripheral( (__bridge _handle) INTERNAL_HANDLER( )->mDevice );
}

AStringR iosBluetoothSocket::GetRemoteDeviceAddress( )
{
	return INTERNAL_HANDLER( )->mRemoteAddress;
}

_dword iosBluetoothSocket::GetAvailableBytes( )
{
	return mStreamWriter->GetOffset( );
}

_dword iosBluetoothSocket::Send( const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return -1;

	LockOwner lock_owner( INTERNAL_HANDLER( )->mLocker );

	return INTERNAL_HANDLER( )->mSender->WriteBuffer( buffer, size );
}

_dword iosBluetoothSocket::Recv( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return -1;

	LockOwner lock_owner( INTERNAL_HANDLER( )->mLocker );

	IStreamWriter* stream_writer = INTERNAL_HANDLER( )->mRecver;
	EGE_ASSERT( stream_writer != _null );

	_dword recv_size = Math::Min< _dword >( size, stream_writer->GetOffset( ) );
	if ( recv_size != 0 )
	{
		EGE_MEM_CPY( buffer, stream_writer->GetBuffer( ), recv_size );
		stream_writer->RemoveBuffer( recv_size );
	}

	return recv_size;
}

//----------------------------------------------------------------------------
// iosBluetoothServerSocket Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( iosBluetoothServerSocket )
    INTERNAL_HANDLER_CONSTRUCTOR( )
	{
	}
INTERNAL_HANDLER_IMPL_END( )

iosBluetoothServerSocket::iosBluetoothServerSocket( )
{
	INTERNAL_HANDLER_CREATE( );
}

iosBluetoothServerSocket::~iosBluetoothServerSocket( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool iosBluetoothServerSocket::Initialize( const UID128& uuid )
{
    return _true;
}

_void iosBluetoothServerSocket::AcceptClient( _void* peer_id )
{
}

IBluetoothSocketPassRef iosBluetoothServerSocket::Accept( _dword timeout )
{
	return _null;
}

//----------------------------------------------------------------------------
// iosBluetoothDevice Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( iosBluetoothDevice )
	AString	mAddress;

    INTERNAL_HANDLER_CONSTRUCTOR( )
	{
	}
    INTERNAL_HANDLER_DESTRUCTOR( )
	{
	}
INTERNAL_HANDLER_IMPL_END( )

iosBluetoothDevice::iosBluetoothDevice( )
{
	INTERNAL_HANDLER_CREATE( );
}

iosBluetoothDevice::~iosBluetoothDevice( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool iosBluetoothDevice::Initialize( AStringPtr address )
{
	INTERNAL_HANDLER( )->mAddress = address;

	return _true;
}

IBluetoothDevice::_STATE iosBluetoothDevice::GetState( ) const
{
	return _STATE_BOND_NONE;
}

IBluetoothDevice::_TYPE iosBluetoothDevice::GetType( ) const
{
	return _TYPE_UNKNOWN;
}

IBluetoothSocketPassRef iosBluetoothDevice::CreateClientSocket( const UID128& uuid )
{
	_handle peripheral = gBluetoothAdapter->ScanPeripheral( uuid );
	if ( peripheral == _null )
		return _null;

	iosBluetoothSocket* socket = new iosBluetoothSocket( );
	if ( socket->Initialize( mAddress, uuid, peripheral ) == _false )
		{ EGE_RELEASE( socket ); return _null; }

	return socket;
}

//----------------------------------------------------------------------------
// iosBluetoothAdapter Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( iosBluetoothAdapter )
	EventObject						mMatchEvent;
	CBPeripheral* 					mMatchDevice;

	CBCentralManager*				mCentralManager;
	iosCBCentralManagerDelegate*	mCentralDelegate;

	CBPeripheralManager*			mPeripheralManager;
	iosCBPeripheralManagerDelegate*	mPeripheralDelegate;

    INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mMatchEvent.Create( _true, _false );
		mMatchDevice		= nil;

		mCentralManager		= nil;
		mCentralDelegate	= nil;

		mPeripheralManager	= nil;
		mPeripheralDelegate	= nil;
	}
INTERNAL_HANDLER_IMPL_END( )

iosBluetoothAdapter::iosBluetoothAdapter( )
{
	mIsDiscovering	= _false;

    mNotifier		= &NullEngine::GetInstance( ).GetBluetoothAdapterNotifier( );

	INTERNAL_HANDLER_CREATE( );

	// Start up the CBCentralManager
    dispatch_queue_t centralQueue = dispatch_queue_create("central", DISPATCH_QUEUE_SERIAL);
	INTERNAL_HANDLER( )->mCentralDelegate		= [iosCBCentralManagerDelegate alloc];
	INTERNAL_HANDLER( )->mCentralManager		= [[CBCentralManager alloc] initWithDelegate:INTERNAL_HANDLER( )->mCentralDelegate queue:centralQueue];

    // Start up the CBPeripheralManager
	INTERNAL_HANDLER( )->mPeripheralDelegate    = [iosCBPeripheralManagerDelegate alloc];
    INTERNAL_HANDLER( )->mPeripheralManager		= [[CBPeripheralManager alloc] initWithDelegate:INTERNAL_HANDLER( )->mPeripheralDelegate queue:nil];

	// Update the global variables
	gBluetoothAdapter	= this;
	gCentralManager		= INTERNAL_HANDLER( )->mCentralManager;
	gPeripheralManager	= INTERNAL_HANDLER( )->mPeripheralManager;
}

iosBluetoothAdapter::~iosBluetoothAdapter( )
{
	// Remove bluetooth notifications
	CFNotificationCenterRemoveEveryObserver( CFNotificationCenterGetLocalCenter( ), this );

	INTERNAL_HANDLER_RELEASE( );

	gBluetoothAdapter = _null;
}

_void iosBluetoothAdapter::UpdateMatchPeripheral( _handle peripheral )
{
	EGE_ASSERT( peripheral != _null );

	INTERNAL_HANDLER( )->mMatchDevice = (__bridge CBPeripheral*) peripheral;
	INTERNAL_HANDLER( )->mMatchEvent.Set( );
}

_handle iosBluetoothAdapter::ScanPeripheral( const UID128& uuid )
{
	NSString* ns_uuid = NSPlatform::Utf8ToNSString( uuid.ToStringU( ) );

	[INTERNAL_HANDLER( )->mCentralManager scanForPeripheralsWithServices:@[[CBUUID UUIDWithString:ns_uuid]]
		options:@{ CBCentralManagerScanOptionAllowDuplicatesKey : @YES }]; 

	// Wait for the match result freeback
	if ( INTERNAL_HANDLER( )->mMatchEvent.Wait( 10 SEC ) == _false )
	{
		// Timeout
		return _null;
	}

	return (__bridge _handle) INTERNAL_HANDLER( )->mMatchDevice;
}

_void iosBluetoothAdapter::ConnectPeripheral( _handle peripheral )
{
	CBPeripheral* ns_peripheral = (__bridge CBPeripheral*) peripheral;
	EGE_ASSERT( ns_peripheral != _null );

	NSLog(@"Connecting to peripheral %@", ns_peripheral); 
	[INTERNAL_HANDLER( )->mCentralManager connectPeripheral:ns_peripheral options:nil];
}

IBluetoothAdapter::_STATE iosBluetoothAdapter::GetState( ) const
{
	return _STATE_OFF;
}

_ubool iosBluetoothAdapter::Enable( _ubool enable )
{
	return _true;
}

_ubool iosBluetoothAdapter::IsEnabled( ) const
{
	return _true;
}

IBluetoothDevicePassRef iosBluetoothAdapter::GetRemoteDevice( AStringPtr address )
{
	iosBluetoothDevice* device = new iosBluetoothDevice( );
	if ( device->Initialize( address ) == _false )
		{ EGE_RELEASE( device ); return _null; }

	return device;
}

_ubool iosBluetoothAdapter::CreateBondOfRemoteDevice( AStringPtr address )
{
	return _false;
}

_ubool iosBluetoothAdapter::RemoveBondOfRemoteDevice( AStringPtr address )
{
	return _false;
}

_dword iosBluetoothAdapter::GetBondedDevicesNumber( )
{
	return 0;
}

IBluetoothDevicePassRef iosBluetoothAdapter::GetBondedDeviceByIndex( _dword index )
{
	return _null;
}

_ubool iosBluetoothAdapter::StartDiscovery( )
{
	mIsDiscovering = _true;

	return _true;
}

_void iosBluetoothAdapter::CancelDiscovery( )
{
	mIsDiscovering = _false;
}

_ubool iosBluetoothAdapter::IsDiscovering( ) const
{
	return mIsDiscovering;
}

IBluetoothServerSocketPassRef iosBluetoothAdapter::CreateServerSocket( const UID128& uuid )
{
	iosBluetoothServerSocket* server = new iosBluetoothServerSocket( );
	if ( server->Initialize( uuid ) == _false )
        { EGE_RELEASE( server ); return _null; }
    
	return server;
}
