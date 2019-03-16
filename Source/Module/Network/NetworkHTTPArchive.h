//! @file     NetworkHTTPArchive.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class NetworkHTTPArchive;

//----------------------------------------------------------------------------
// NetworkStorageArchiveConnectionNotifier
//----------------------------------------------------------------------------

class NetworkStorageArchiveConnectionNotifier : public TObject< INetworkConnectionNotifier >
{
private:
	NetworkHTTPArchive*	mArchive;

public:
	NetworkStorageArchiveConnectionNotifier( NetworkHTTPArchive* archive );
	virtual ~NetworkStorageArchiveConnectionNotifier( );

// INetworkConnectionNotifier Interface
public:
	virtual _void	OnUpdateState( _CONNECTION_STATE state ) override;
	virtual _void	OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) override;

	virtual _void	OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters ) override;
	virtual _dword	OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters ) override;
	virtual _void	OnFinishBuffer( const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkHTTPArchive
//----------------------------------------------------------------------------

class NetworkHTTPArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	typedef NetworkStorageArchiveConnectionNotifier ConnectionNotifier;

private:
	//!	The remote path
	WString						mRemotePath;
	//!	True indicates use the whole path to access/load resource
	_ubool						mUseWholePath;

	//!	The remote connection notifier
	ConnectionNotifier*			mConnectionNotifier;
	//!	The remote connection
	INetworkHTTPConnectionRef	mConnection;

private:
	//!	Get the temporary directory.
	WStringR GetTempDir( ) const;

	//!	Get local cache file path.
	WStringR GetLocalCacheFilePath( WStringPtr filename );
	//!	Save to local cache.
	_ubool SaveLocalCache( WStringPtr filename, IStreamReader* stream_reader );

public:
	NetworkHTTPArchive( );
	virtual ~NetworkHTTPArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr remote_path, _ubool use_whole_path );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
	virtual IStreamReaderPassRef	LoadResourceByPath( WStringPtr file_name ) override;

	virtual _void					ClearCaches( ) override;
};

//----------------------------------------------------------------------------
// NetworkHTTPArchive Implementation
//----------------------------------------------------------------------------

}