//! @file     NetworkNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullNetworkProtoBufConnectionNotifier
//----------------------------------------------------------------------------

class NullNetworkProtoBufConnectionNotifier : public INTERFACE_OBJECT_IMPL( INetworkProtoBufConnectionNotifier )
{
public:
	NullNetworkProtoBufConnectionNotifier( ) { }
	virtual ~NullNetworkProtoBufConnectionNotifier( ) { }

// INetworkProtoBufConnectionNotifier Interface
public:
	virtual _void OnUpdateState( _CONNECTION_STATE state ) { }

	virtual _void OnErrorOccurs( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) { }

	virtual _void OnHandleBinaryMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, const QwordParameters4& parameters ) { }
};

//----------------------------------------------------------------------------
// NullNetworkConnectionNotifier
//----------------------------------------------------------------------------

class NullNetworkConnectionNotifier : public INTERFACE_OBJECT_IMPL( INetworkConnectionNotifier )
{
public:
	NullNetworkConnectionNotifier( ) { }
	virtual ~NullNetworkConnectionNotifier( ) { }

// INetworkConnectionNotifier Interface
public:
	virtual _void	OnUpdateState( _CONNECTION_STATE state ) { }
	virtual _void	OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) { }

	virtual _void	OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters ) { }
	virtual _dword	OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) { return size; }
	virtual _void	OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) { }
	virtual _void	OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters ) { }
	virtual _void	OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters ) { }
	virtual _void	OnFinishBuffer( const QwordParameters4& parameters ) { }
};

//----------------------------------------------------------------------------
// NullNetworkFTPConnectionNotifier
//----------------------------------------------------------------------------

class NullNetworkFTPConnectionNotifier : public INTERFACE_OBJECT_IMPL( INetworkFTPConnectionNotifier )
{
public:
	NullNetworkFTPConnectionNotifier( ) { }
	virtual ~NullNetworkFTPConnectionNotifier( ) { }

// INetworkFTPConnectionNotifier Interface
public:
	virtual _void OnUploadFileCompleted( WStringPtr local_filename, WStringPtr remote_filename ) { }
};

//----------------------------------------------------------------------------
// NullNetworkStationNotifier
//----------------------------------------------------------------------------

class NullNetworkStationNotifier : public INTERFACE_OBJECT_IMPL( INetworkStationNotifier )
{
public:
	NullNetworkStationNotifier( ) { }
	virtual ~NullNetworkStationNotifier( ) { }

// INetworkStationNotifier Interface
public:
	virtual _void	OnAcceptClient( _dword client_id ) { }
	virtual _void	OnLostClient( _dword client_id ) { }

	virtual _dword	OnRecvBuffer( _dword client_id, _dword size, const _byte* buffer, IStreamWriter* stream_writer ) { return 0; }
};

//----------------------------------------------------------------------------
// NullNetworkStreamReaderNotifier
//----------------------------------------------------------------------------

class NullNetworkStreamReaderNotifier : public INTERFACE_OBJECT_IMPL( INetworkStreamReaderNotifier )
{
public:
	NullNetworkStreamReaderNotifier( ) { }
	virtual ~NullNetworkStreamReaderNotifier( ) { }

// INetworkStreamReaderNotifier Interface
public:
	virtual _void OnReading( _dword read_size, _dword total_read_size ) { }
};

//----------------------------------------------------------------------------
// NullNetworkResourceManager
//----------------------------------------------------------------------------

class NullNetworkResourceManager : public INTERFACE_OBJECT_IMPL( INetworkResourceManager )
{
public:
	NullNetworkResourceManager( ) { }
	virtual ~NullNetworkResourceManager( ) { }

// INetworkResourceManager Interface
public:
	virtual INetworkConnectionNotifierPassRef			CreateNetworkConnectionNotifier( INetworkConnectionNotifier* notifier ) { return _null; }

	virtual INetworkConnectionThread*					GetTCPConnectionThread( ) { return _null; }
	virtual INetworkConnectionThread*					GetHTTPConnectionThread( ) { return _null; }
	virtual INetworkConnectionThread*					GetFTPConnectionThread( ) { return _null; }
	virtual INetworkConnectionThread*					GetBTConnectionThread( ) { return _null; }
	virtual INetworkConnectionThread*					GetNamePipeConnectionThread( ) { return _null; }

	virtual INetworkTCPConnectionPassRef				CreateTCPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkStationPassRef						CreateTCPStation( _dword port, _dword max_connection_number, _dword recv_block_size ) { return _null; }

	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( AStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( WStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( const Address& remote_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( AStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( WStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }

	virtual INetworkNamedPipeConnectionPassRef			CreateNamedPipeConnection( WStringPtr pipename, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkStationPassRef						CreateNamedPipeStation( WStringPtr pipename, _dword type, _dword size, _dword timeout ) { return _null; }

	virtual INetworkBluetoothConnectionPassRef			CreateBluetoothConnection( AStringPtr address, const UID128& uid, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkStationPassRef						CreateBluetoothStation( const UID128& uid ) { return _null; }

	virtual INetworkProtoBufTCPConnectionPassRef		CreateProtoBufTCPConnection( const Address& remote_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkProtoBufHTTPConnectionPassRef		CreateProtoBufHTTPConnection( WStringPtr url_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }
	virtual INetworkProtoBufNamedPipeConnectionPassRef	CreateProtoBufNamedPipeConnection( WStringPtr pipename, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode ) { return _null; }

	virtual IArchivePassRef								CreateHTTPArchive( WStringPtr remote_path, _ubool use_whole_path ) { return _null; }
};

//----------------------------------------------------------------------------
// NullNetworkModule
//----------------------------------------------------------------------------

class NullNetworkModule : public INTERFACE_MODULE_IMPL( INetworkModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( INetworkModule ) BaseClass;

public:
	NullNetworkModule( ) : BaseClass( L"", Version::cZero ) { }
	virtual ~NullNetworkModule( ) { }

// INetworkModule Interface
public:
	virtual _void				EnableOptions( _dword options, _ubool enable ) { }
	virtual _ubool				IsEnableOptions( _dword options ) const { return _false; }

	virtual _ubool				GetRemoteSiteTime( WStringPtr url, _dword time_out, Time& time ) { return _false; }

	virtual _void				UpdateTotalDownloadBytes( _qword size ) { }
	virtual _void				UpdateTotalUploadBytes( _qword size ) { }

	virtual _qword				GetTotalDownloadBytes( ) const { return 0; }
	virtual _qword				GetTotalUploadBytes( ) const { return 0; }

	virtual _void				SetSimulatingLag( _dword min_lag, _dword max_lag ) { }
	virtual const DwordRange&	GetSimulatingLag( ) const { return DwordRange::cNull; }
};

//----------------------------------------------------------------------------
// NullNetwork
//----------------------------------------------------------------------------

class NullNetwork
{
	SINGLETON( NullNetwork )

private:
	NullNetworkProtoBufConnectionNotifier	mNetworkProtoBufConnectionNotifier;
	NullNetworkFTPConnectionNotifier		mNetworkFTPConnectionNotifier;
	NullNetworkConnectionNotifier			mNetworkConnectionNotifier;
	NullNetworkStationNotifier				mNetworkStationNotifier;
	NullNetworkStreamReaderNotifier			mNetworkStreamReaderNotifier;
	NullNetworkResourceManager				mNetworkResourceManager;
	NullNetworkModule						mNetworkModule;

public:
	EGE_GETR_ACCESSOR( NullNetworkProtoBufConnectionNotifier, NetworkProtoBufConnectionNotifier )
	EGE_GETR_ACCESSOR( NullNetworkFTPConnectionNotifier, NetworkFTPConnectionNotifier )
	EGE_GETR_ACCESSOR( NullNetworkConnectionNotifier, NetworkConnectionNotifier )
	EGE_GETR_ACCESSOR( NullNetworkStationNotifier, NetworkStationNotifier )
	EGE_GETR_ACCESSOR( NullNetworkStreamReaderNotifier, NetworkStreamReaderNotifier )
	EGE_GETR_ACCESSOR( NullNetworkResourceManager, NetworkResourceManager )
	EGE_GETR_ACCESSOR( NullNetworkModule, NetworkModule )
};

}