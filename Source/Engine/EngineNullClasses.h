//! @file     EngineNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullCSVFile
//----------------------------------------------------------------------------

class NullCSVFile : public INTERFACE_BASEFILE_IMPL( ICSVFile )
{
public:
	NullCSVFile( ) { }
	virtual ~NullCSVFile( ) { }

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const { return _FF_CSV; }

// ICSVFile Interface
public:
	virtual _dword			GetRows( ) const { return 0; }
	virtual _dword			GetColumns( ) const { return 0; }

	virtual WStringPtr		GetGridString( _dword column, _dword row ) const { return L""; }
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
	virtual _ubool	OnDo( _ubool is_undo, WStringPtr key, IStreamReader* stream_reader ) { return _true; }
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
// NullJoystickNotifier
//----------------------------------------------------------------------------

class NullJoystickNotifier : public TObject< IJoystickNotifier >
{
public:
	NullJoystickNotifier( )
	{
	}
	virtual ~NullJoystickNotifier( ) 
	{
	}

// IJoystickNotifier Interface
public:
	virtual _void OnCombKeyEventStart( AStringPtr token, _dword id ) { }
	virtual _void OnCombKeyEventEnd( AStringPtr token, _dword id ) { }

	virtual _void OnKeyUp( _dword id, _dword key_code ) { }
	virtual _void OnKeyDown( _dword id, _dword key_code ) { }

	virtual _void OnLeftStickChanged( _dword id, const PointF& pos ) { }
	virtual _void OnRightStickChanged( _dword id, const PointF& pos ) { }
	virtual _void OnZMoved( _dword id, _float pos ) { }
};

//----------------------------------------------------------------------------
// NullBluetoothAdapterNotifier
//----------------------------------------------------------------------------

class NullBluetoothAdapterNotifier : public INTERFACE_OBJECT_IMPL( IBluetoothAdapterNotifier )
{
public:
	NullBluetoothAdapterNotifier( ) { }
	virtual ~NullBluetoothAdapterNotifier( ) { }

// IBluetoothAdapterNotifier Interface
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
// NullWebViewNotifier
//----------------------------------------------------------------------------

class NullWebViewNotifier : public INTERFACE_OBJECT_IMPL( IWebViewNotifier )
{
public:
	NullWebViewNotifier( ) { }
	virtual ~NullWebViewNotifier( ) { }

// IWebViewNotifier Interface
public:
	virtual _void	OnPageKeyUp( _dword key_id ) { }
	virtual _void	OnPageKeyDown( _dword key_id ) { }

	virtual _void	OnPageFinished( WStringPtr url ) { }
	virtual _void	OnProgressChanged( _dword progress ) { }
	virtual _void	OnReceivedError( _dword err_code, WStringPtr description, WStringPtr url ) { }
};

//----------------------------------------------------------------------------
// NullProtoBufSender
//----------------------------------------------------------------------------

class NullProtoBufSender : public INTERFACE_OBJECT_IMPL( IProtoBufSender )
{
public:
	NullProtoBufSender( ) { }
	virtual ~NullProtoBufSender( ) { }

	virtual _dword 				AddRef( )
	{
		return INTERFACE_OBJECT_IMPL( IProtoBufSender )::AddRef( );
	}

// IProtoBufSender Interface
public:
	virtual _void	Send( const _byte* buffer, _dword size ) { }
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& params ) { return _false; }
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
	virtual _ubool			IsLaunchingApp( ) const { return _false; }
	virtual _ubool			HasLoadedApp( ) const { return _false; }

	virtual _ubool			ResetResources( ) { return _false; }
	virtual _void			UnloadResources( ) { }

	virtual _void			RegisterAppDelegate( IAppDelegate* app_delegate ) { }
	virtual IAppDelegate*	GetRegisteredAppDelegate( ) { return _null; }

	virtual _void			RegisterModule( IModule* module, _dword priority ) { }
	virtual _void			UnregisterModule( IModule* module ) { }

	virtual _void			OutputString( _LOG type, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) { }
	virtual _void			OutputString( _LOG type, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) { }
	virtual _void			OutputString( _LOG type, AStringPtr module_name, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) { }
	virtual _void			OutputString( _LOG type, WStringPtr module_name, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) { }

	virtual _void			AddDelayEvent( const EventBase& event ) { }
	virtual _void			ProcessDelayEvents( ) { }
	virtual _void			ProcessEvent( EventBase& event ) { }
};

//----------------------------------------------------------------------------
// NullEngine
//----------------------------------------------------------------------------

class NullEngine
{
	SINGLETON( NullEngine )

private:
	NullCSVFile						mCSVFile;
	NullBluetoothAdapterNotifier	mBluetoothAdapterNotifier;
	NullMessageBoxNotifier			mMessageBoxNotifier;
	NullJoystickNotifier			mJoystickNotifier;
	NullOperationRecordPerformer	mOperationRecordPerformer;
	NullWebViewNotifier				mWebViewNotifier;
	NullProtoBufSender				mProtoBufSender;
	NullModuleManager				mModuleManager;

public:
	EGE_GETR_ACCESSOR( NullCSVFile, CSVFile )
	EGE_GETR_ACCESSOR( NullBluetoothAdapterNotifier, BluetoothAdapterNotifier )
	EGE_GETR_ACCESSOR( NullMessageBoxNotifier, MessageBoxNotifier )
	EGE_GETR_ACCESSOR( NullJoystickNotifier, JoystickNotifier )
	EGE_GETR_ACCESSOR( NullOperationRecordPerformer, OperationRecordPerformer )
	EGE_GETR_ACCESSOR( NullWebViewNotifier, WebViewNotifier )
	EGE_GETR_ACCESSOR( NullProtoBufSender, ProtoBufSender )
	EGE_GETR_ACCESSOR( NullModuleManager, ModuleManager )
};

}