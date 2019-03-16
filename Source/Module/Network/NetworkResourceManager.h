//! @file     NetworkResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkResourceManager
//----------------------------------------------------------------------------

class NetworkResourceManager : public TObject< INetworkResourceManager >
{
private:
	typedef Array< INetworkConnectionThreadRef > NetworkConnectionThreadArray;

private:
	Lock							mLock;

	_dword							mMaxConnectionNumber;

	NetworkConnectionThreadArray	mConnectionThreads;

private:
	template< typename Type >
	_void PauseConnectionThreads( Type& threads );
	template< typename Type >
	_void ResumeConnectionThreads( Type& threads );

	//!	Get TCP/HTTP/FTP/BT/NamePipe connection thread.
	INetworkConnectionThread* GetConnectionThread( _ubool thread_alone_mode, WStringPtr thread_name );
	//!	Find connection thread by name.
	INetworkConnectionThread* FindConnectionThreadByName( WStringPtr thread_name );

public:
	NetworkResourceManager( );
	virtual ~NetworkResourceManager( );

public:
	//!	Initialize.
	_ubool Initialize( _dword max_connection_number );
	//!	Finalize.
	_void Finalize( );

	//!	Pause.
	_void Pause( );
	//!	Resume.
	_void Resume( );

// IObject Interface
public:
	virtual _void									Tick( _dword limited_elapse, _dword elapse ) override;

// INetworkResourceManager Interface
public:
	virtual INetworkConnectionNotifierPassRef			CreateNetworkConnectionNotifier( INetworkConnectionNotifier* notifier ) override;

	virtual INetworkTCPConnectionPassRef				CreateTCPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkStationPassRef						CreateTCPStation( _dword port, _dword max_connection_number, _dword recv_block_size ) override;

	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( AStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkHTTPConnectionPassRef				CreateHTTPConnection( WStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( const Address& remote_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( AStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkFTPConnectionPassRef				CreateFTPConnection( WStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;

	virtual INetworkNamedPipeConnectionPassRef			CreateNamedPipeConnection( WStringPtr pipename, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkStationPassRef						CreateNamedPipeStation( WStringPtr pipename, _dword type, _dword size, _dword timeout ) override;

	virtual INetworkBluetoothConnectionPassRef			CreateBluetoothConnection( AStringPtr address, const UID128& uid, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkStationPassRef						CreateBluetoothStation( const UID128& uid ) override;

	virtual INetworkProtoBufTCPConnectionPassRef		CreateProtoBufTCPConnection( const Address& remote_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkProtoBufHTTPConnectionPassRef		CreateProtoBufHTTPConnection( WStringPtr url_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;
	virtual INetworkProtoBufNamedPipeConnectionPassRef	CreateProtoBufNamedPipeConnection( WStringPtr pipename, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) override;

	virtual IArchivePassRef								CreateHTTPArchive( WStringPtr remote_path, _ubool use_whole_path ) override;
};

//----------------------------------------------------------------------------
// NetworkResourceManager Implementation
//----------------------------------------------------------------------------

}