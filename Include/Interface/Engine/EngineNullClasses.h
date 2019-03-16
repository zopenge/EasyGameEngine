//! @file     EngineNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullProperties
//----------------------------------------------------------------------------

class NullProperties : public TObject< TClonableObject< NullProperties, IProperties > >
{
public:
	NullProperties( ) { }
	virtual ~NullProperties( ) { }

// IClonableObject Interface
public:
	virtual _ubool	CloneFrom( const IProperties* properties ) { return _false; }

// IProperties Interface
public:
	#define DEFINE_PROPERTIES_METHOD(Type,Name,ParameterTypesAndNames,Parameters,NullImplementation) virtual Type Name ParameterTypesAndNames { NullImplementation }
	#include "Interface/Engine/Utils/IPropertiesMehods.h"
	#undef DEFINE_PROPERTIES_METHOD
};

//----------------------------------------------------------------------------
// NullOperationRecordPerformer
//----------------------------------------------------------------------------

class NullOperationRecordPerformer : public TObject< IOperationRecordPerformer >
{
public:
	NullOperationRecordPerformer( ) { }
	virtual ~NullOperationRecordPerformer( ) { }

// IOperationRecordPerformer Interface
public:
	virtual _ubool	OnDo( _dword index, IStreamReader* stream ) { return _true; }

	virtual _void	OnBeforeRemoveRecord( IStreamReader* stream ) { }
	virtual _ubool	OnRecordCompleted( IStreamReader* stream ) { return _true; }
};

//----------------------------------------------------------------------------
// NullAnalyticsCenter
//----------------------------------------------------------------------------

class NullAnalyticsCenter : public TObject< IAnalyticsCenter >
{
public:
	NullAnalyticsCenter( ) { }
	virtual ~NullAnalyticsCenter( ) { }

// IAnalyticsCenter Interface
public:
	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) { }
    virtual _void LogEvent( UStringPtr event_ID, UStringPtr desc ) { }
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) { }
};

//----------------------------------------------------------------------------
// NullFlurry
//----------------------------------------------------------------------------

class NullFlurry : public TObject< IFlurry >
{
public:
	NullFlurry( ) { }
	virtual ~NullFlurry( ) { }

// IAnalyticsCenter Interface
public:
	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) { }
	virtual _void LogEvent( UStringPtr event_ID, UStringPtr desc ) { }
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) { }

// IFlurry Interface
public:
	virtual _void SetUserID( UStringPtr user_id ) { }
	virtual _void SetAge( _dword age ) { }
	virtual _void SetGender( _GENDER gender ) { }
	virtual _void Enable( _ubool enable ) { }
};

//----------------------------------------------------------------------------
// NullHailstoneNotifier
//----------------------------------------------------------------------------

class NullHailstoneNotifier : public TObject< IHailstoneNotifier >
{
public:
	NullHailstoneNotifier( ) { }
	virtual ~NullHailstoneNotifier( ) { }

// IHailstoneNotifier Interface
public:
	virtual _void OnRedeem( AStringPtr message ) { }
};

//----------------------------------------------------------------------------
// NullHailstone
//----------------------------------------------------------------------------

class NullHailstone : public TObject< IHailstone >
{
public:
	NullHailstone( ) { }
	virtual ~NullHailstone( ) { }

// IAnalyticsCenter Interface
public:
	virtual _void					LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) { }
	virtual _void					LogEvent( UStringPtr event_ID, UStringPtr desc ) { }
	virtual _void					Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) { }

// IHailstone Interface
public:
	virtual IHailstoneNotifierRef	SetNotifier( IHailstoneNotifier* notifier ) { return _null; }
	virtual IHailstoneNotifierRef	GetNotifier() { return _null; }

	virtual _ubool					Initialize( UStringPtr accountName, UStringPtr server, UStringPtr channel ) { return _true; }

	virtual _ubool					AddCash( _long paytype, _long addaftermoney, _long addmoney ) { return _false; }
	virtual _ubool					UserLogin( UStringPtr accountID ) { return _false; }
	virtual _ubool					RedeemWithCode( UStringPtr code ) { return _false; }
	virtual _ubool					ShopTrade(UStringPtr order_id,UStringPtr item_id,int item_count, int buytype,int cash_left,int delta) { return _false; }
};

//----------------------------------------------------------------------------
// NullTrackingCenter
//----------------------------------------------------------------------------

class NullTrackingCenter : public TObject< ITrackingCenter >
{
public:
	NullTrackingCenter( )
	{
	}
	virtual ~NullTrackingCenter( ) 
	{
	}

// ITrackingCenter Interface
public:
	virtual _void	Start( ) { }
};

//----------------------------------------------------------------------------
// NullUserSystemNotifier
//----------------------------------------------------------------------------

class NullUserSystemNotifier : public TObject< IUserSystemNotifier >
{
public:
	NullUserSystemNotifier( ) { }
	virtual ~NullUserSystemNotifier( ) { }

// IUserSystemNotifier Interface
public:
	virtual _void OnLogin( WStringPtr message ) { }
	virtual _void OnLogout( WStringPtr message ) { }
};

//----------------------------------------------------------------------------
// NullUserSystem
//----------------------------------------------------------------------------

class NullUserSystem : public TUserSystem< IUserSystem >
{
public:
	NullUserSystem( ) { }
	virtual ~NullUserSystem( ) { }

// IUserSystem Interface
public:
	virtual _ubool	GetUserInfo( ) { return _false; }

	virtual _void	ShowLoginUI( ) { }

	virtual _ubool	OpenURL( WStringPtr url ) { return _false; }
	virtual _ubool	Share( WStringPtr message ) { return _false; }

	virtual _ubool	InviteFriend( WStringPtr message ) { return _false; }
	virtual _ubool	GetFriends( ) { return _false; }
};

//----------------------------------------------------------------------------
// NullMessageBoxNotifier
//----------------------------------------------------------------------------

class NullMessageBoxNotifier : public TObject< IMessageBoxNotifier >
{
public:
	NullMessageBoxNotifier( )
	{
	}
	virtual ~NullMessageBoxNotifier( ) 
	{
	}

// IMessageBoxNotifier Interface
public:
	virtual _void OnClickButton( _MESSAGE_BOX_BUTTON_ID button_id ) { }
};

//----------------------------------------------------------------------------
// NullBluetoothAdapterNotitifer
//----------------------------------------------------------------------------

class NullBluetoothAdapterNotitifer : public INTERFACE_OBJECT_IMPL( IBluetoothAdapterNotitifer )
{
public:
	NullBluetoothAdapterNotitifer( ) { }
	virtual ~NullBluetoothAdapterNotitifer( ) { }

// IBluetoothAdapterNotitifer Interface
public:
	virtual _void OnACLConnected( IBluetoothDevice* device ) { }
	virtual _void OnACLDisconnected( IBluetoothDevice* device ) { }
	virtual _void OnACLDisconnectRequested( IBluetoothDevice* device ) { }

	virtual _void OnBondStateChanged( IBluetoothDevice* device ) { }
	virtual _void OnClassChanged( IBluetoothDevice* device ) { }
	virtual _void OnNameChanged( IBluetoothDevice* device ) { }

	virtual _void OnFoundDevice( IBluetoothDevice* device ) { }

	virtual _void OnPairingRequest( IBluetoothDevice* device ) { }
	virtual _void OnUUID( IBluetoothDevice* device ) { }
};

//----------------------------------------------------------------------------
// NullStringTable
//----------------------------------------------------------------------------

class NullStringTable : public INTERFACE_OBJECT_IMPL( IStringTable )
{
public:
	NullStringTable( ) { }
	virtual ~NullStringTable( ) { }

// IStringTable Interface
public:
	virtual AStringObj	GetNullAString( ) const { static AStringObj sNull; return sNull; }
	virtual UStringObj	GetNullUString( ) const { static UStringObj sNull; return sNull; }
	virtual WStringObj	GetNullWString( ) const { static WStringObj sNull; return sNull; }

	virtual AStringObj	GetRefString( ARawString string ) { static AStringObj sNull; return sNull; }
	virtual AStringObj	GetRefString( AStringPtr string ) { static AStringObj sNull; return sNull; }
	virtual AStringObj	SearchRefAStringByID( _dword id ) const { static AStringObj sNull; return sNull; }
	virtual AStringObj	SearchRefString( ARawString string ) const { static AStringObj sNull; return sNull; }
	virtual AStringObj	SearchRefString( AStringPtr string ) const { static AStringObj sNull; return sNull; }

	virtual UStringObj	GetRefString( URawString string ) { static UStringObj sNull; return sNull; }
	virtual UStringObj	GetRefString( UStringPtr string ) { static UStringObj sNull; return sNull; }
	virtual UStringObj	SearchRefUStringByID( _dword id ) const { static UStringObj sNull; return sNull; }
	virtual UStringObj	SearchRefString( URawString string ) const { static UStringObj sNull; return sNull; }
	virtual UStringObj	SearchRefString( UStringPtr string ) const { static UStringObj sNull; return sNull; }

	virtual WStringObj	GetRefString( WRawString string ) { static WStringObj sNull; return sNull; }
	virtual WStringObj	GetRefString( WStringPtr string ) { static WStringObj sNull; return sNull; }
	virtual WStringObj	SearchRefWStringByID( _dword id ) const { static WStringObj sNull; return sNull; }
	virtual WStringObj	SearchRefString( WRawString string ) const { static WStringObj sNull; return sNull; }
	virtual WStringObj	SearchRefString( WStringPtr string ) const { static WStringObj sNull; return sNull; }

	virtual _ubool		LoadFromStream( IStreamReader* stream_reader ) { return _false; }
	virtual _ubool		SavetToStream( IStreamWriter* stream_writer ) { return _false; }
};

//----------------------------------------------------------------------------
// NullAdWebBrowserDelegate
//----------------------------------------------------------------------------

class NullAdWebBrowserDelegate : public INTERFACE_OBJECT_IMPL( IAdWebBrowserDelegate )
{
public:
	NullAdWebBrowserDelegate( ) { }
	virtual ~NullAdWebBrowserDelegate( ) { }

// IAdWebBrowserDelegate Interface
public:
	virtual _void OnWillAppear( ) { }
	virtual _void OnDidAppear( ) { }

	virtual _void OnWillClosed( ) { }
	virtual _void OnDidClosed( ) { }

	virtual _void OnShare( WStringPtr url ) { }
};

//----------------------------------------------------------------------------
// NullStreamProcessorNotifier
//----------------------------------------------------------------------------

class NullStreamProcessorNotifier : public INTERFACE_OBJECT_IMPL( IStreamProcessorNotifier )
{
public:
	NullStreamProcessorNotifier( ) { }
	virtual ~NullStreamProcessorNotifier( ) { }

// IStreamProcessorNotifier Interface
public:
	virtual _void OnProcessing( _dword total_size, _dword offset, _dword processed_size ) { }
};

//----------------------------------------------------------------------------
// NullStackAllocator
//----------------------------------------------------------------------------

class NullStackAllocator : public INTERFACE_OBJECT_IMPL( IStackAllocator )
{
public:
	NullStackAllocator( ) { }
	virtual ~NullStackAllocator( ) { }

// IAllocator Interface
public:
	virtual _ubool	Cleanup( ) { return _false; }

	virtual _ubool	CanAlloc( _dword size ) const { return _false; }

	virtual _byte*	Alloc( _dword size ) { return _null; }
	virtual _byte*	Alloc( _dword size, const _byte* buffer ) { return _null; }
	virtual _byte*	ReAlloc( _void* pointer, _dword size ) { return _null; }
	virtual _byte*	ReAlloc( _void* pointer, _dword size, const _byte* buffer ) { return _null; }
	virtual _void	Free( _void* pointer ) { }
	virtual _void	FreeAll( ) { }

// IStackAllocator Interface
public:
	virtual _dword	GetOffset( ) const { return 0; }
	virtual _void	SetOffset( _dword offset ) { }
};

//----------------------------------------------------------------------------
// NullGarbageCollector
//----------------------------------------------------------------------------

class NullGarbageCollector : public INTERFACE_OBJECT_IMPL( IGarbageCollector )
{
public:
	NullGarbageCollector( ) { }
	virtual ~NullGarbageCollector( ) { }

// IGarbageCollector Interface
public:
	virtual _void	Enable( _ubool enable ) { }
	virtual _ubool	IsEnabled( ) const { return _false; }

	virtual _void	Cleanup( _dword timeout ) { }
	virtual _void	SetCleanupMaxTime( _dword time ) { }

	virtual _void	AddObject( IObject* object ) { object->DeleteThis( ); }
};

//----------------------------------------------------------------------------
// NullTickableObjectManager
//----------------------------------------------------------------------------

class NullTickableObjectManager : public INTERFACE_OBJECT_IMPL( ITickableObjectManager )
{
public:
	NullTickableObjectManager( ) { }
	virtual ~NullTickableObjectManager( ) { }

// ITickableObjectManager Interface
public:
	virtual _void AddObject( IObject* object ) { }
	virtual _void RemoveObject( IObject* object ) { }
};

//----------------------------------------------------------------------------
// NullAppDelegate
//----------------------------------------------------------------------------

class NullAppDelegate : public INTERFACE_OBSERVER_IMPL( IAppDelegate )
{
public:
	NullAppDelegate( ) { }
	virtual ~NullAppDelegate( ) { }

// IAppDelegate Interface
public:
	virtual _ubool	OnLoad( IApplication* application, const ICommandLineParser* cmd_parser ) { return _false; }
	virtual _void	OnUnload( ) { }

	virtual _void	OnTick( _time_t tick, _dword elapse ) { }
	virtual _void	OnHandleMessage( MessageBase& message ) { }

	virtual _ubool	GetRestartFlag( ) const { return _false; }
};

//----------------------------------------------------------------------------
// NullModuleManager
//----------------------------------------------------------------------------

class NullModuleManager : public INTERFACE_OBSERVABLE_IMPL( TPowerable< IModuleManager > )
{
public:
	NullModuleManager( ) { }
	virtual ~NullModuleManager( ) { }

// IModuleManager Interface
public:
	virtual _ubool			ResetResources( IApplication* application ) { return _false; }
	virtual _void			UnloadResources( ) { }

	virtual _void			RegisterAppDelegate( IAppDelegate* app_delegate ) { }
	virtual IAppDelegateRef GetRegisteredAppDelegate( ) { return _null; }

	virtual _void			RegisterModule( IModule* module, _dword priority ) { }
	virtual _void			UnregisterModule( IModule* module ) { }

	virtual _void			OutputString( _LOG type, AStringPtr string ) { }
	virtual _void			OutputString( _LOG type, WStringPtr string ) { }
	virtual _void			OutputString( _LOG type, AStringPtr module_name, AStringPtr string ) { }
	virtual _void			OutputString( _LOG type, WStringPtr module_name, WStringPtr string ) { }

	virtual _void			HandleMessage( MessageBase& message ) { }

	virtual _void			ProcessDelayMessages( ) { }
	virtual _void			AddDelayMessage( const MessageBase& message ) { }
};

//----------------------------------------------------------------------------
// NullResourceFactory
//----------------------------------------------------------------------------

class NullResourceFactory : public INTERFACE_OBJECT_IMPL( IResourceFactory )
{
public:
	NullResourceFactory( ) { }
	virtual ~NullResourceFactory( ) { }

// IResourceFactory Interface
public:
	virtual IInterpolatorRef CreateInterpolator( WStringPtr name ) { return _null; }

	virtual ISerializableRef CreateSerializableResource( _dword res_type, WStringPtr res_name ) { return _null; }
};

//----------------------------------------------------------------------------
// NullPurchaseNotifier
//----------------------------------------------------------------------------

class NullPurchaseNotifier : public TObject< IPurchaseNotifier >
{
public:
	NullPurchaseNotifier( ) { }
	virtual ~NullPurchaseNotifier( ) { }

// IPurchaseNotifier Interface
public:
	virtual _void OnSucceed( WStringPtr id ) { }
	virtual _void OnFailed( WStringPtr id ) { }
	virtual _void OnCanceled( WStringPtr id ) { }
};

//----------------------------------------------------------------------------
// NullPurchase
//----------------------------------------------------------------------------

class NullPurchase : public TPurchase< IPurchase >
{
public:
	NullPurchase( ) { }
	virtual ~NullPurchase( ) { }

// IPurchase Interface
public:
	virtual _ubool Pay( WStringPtr id ) { return _false; }
};

}