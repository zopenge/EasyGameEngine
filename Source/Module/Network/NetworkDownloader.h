//! @file     NetworkDownloader.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class NetworkDownloader;

//----------------------------------------------------------------------------
// NetworkStreamReaderNotifier
//----------------------------------------------------------------------------

class NetworkStreamReaderNotifier : public TObject< INetworkStreamReaderNotifier >
{
private:
	NetworkDownloader*	mDownloader;

public:
	NetworkStreamReaderNotifier( NetworkDownloader* downloader );
	virtual ~NetworkStreamReaderNotifier( );

// INetworkStreamReaderNotifier Interface
public:
	virtual _void OnReading( _dword cur_read_size, _dword total_read_size ) override;
};

//----------------------------------------------------------------------------
// NetworkDownloaderTask
//----------------------------------------------------------------------------

class NetworkDownloaderTask : public INTERFACE_TASK_IMPL( IThreadTask )
{
private:
	INetworkConnectionRef	mConnection;
	WString					mRelativeFileName;
	IArchiveRef				mLocalArchive;
	WString					mLocalFileName;
	MD5Code					mMD5Code;
	_dword					mConnectTimeout;
	_dword					mTimeout;

private:
	//!	Check whether it's same resource with remote server.
	_ubool IsSameResource( ) const;
	//!	Download file.
	_ubool DownloadFile( NetworkDownloader* downloader );

public:
	NetworkDownloaderTask( INetworkConnection* connection, WStringPtr relative_file_name, IArchive* local_archive, WStringPtr local_file_name, const MD5Code& md5_code, _dword connect_timeout, _dword timeout );
	virtual ~NetworkDownloaderTask( );

// IThreadTask Interface
public:
	virtual _OPERATION_TYPE OnProcess( _thread_id threadid, _dword& err_id ) override;
};

//----------------------------------------------------------------------------
// NetworkDownloader
//----------------------------------------------------------------------------

class NetworkDownloader : public INTERFACE_FLAGSOBJECT_IMPL( TObject< INetworkDownloader > )
{
private:
	//!	Use the 'RootURLAddress:PortNumber' as key
	typedef Map< INetworkConnectionRef, WString > ConnectionInfoMap;

private:
	//!	The download manifest file info.
	struct DownloadManifestFileInfo
	{
		INetworkDownloaderNotifier::_ERROR	mLastErrID;

		_dword								mConnectTimeout;
		_dword								mTimeout;

		WString								mRootURLAddress;
		IArchiveRef							mLocalArchive;

		NetworkDownloader*					mDownloader;

		DownloadManifestFileInfo( _dword connect_timeout, _dword timeout, WStringPtr root_url_address, IArchive* local_archive, NetworkDownloader* downloader )
		{
			mLastErrID		= INetworkDownloaderNotifier::_ERROR_NO;

			mConnectTimeout	= connect_timeout;
			mTimeout		= timeout;

			mRootURLAddress	= root_url_address;
			mLocalArchive	= local_archive;

			mDownloader		= downloader;
		}
	};

private:
	//!	The thread locker
	Lock								mLocker;
	//! The thread pool
	IThreadPoolRef						mThreadPool;

	//!	The encryption type
	_ENCRYPTION							mEncryptionType;
	//!	The encryption key
	AString								mEncryptionKey;

	//!	The last error ID
	INetworkDownloaderNotifier::_ERROR	mLastErrID;
	//!	The last download file resource name
	WString								mLastDownloadFileResName;
	//!	The last manifest file version
	Version								mLatestManifestVersion;

	//!	The max download speed bytes
	_dword								mMaxDownloadSpeed;

	//!	The download size range
	DwordRange							mDownloadSizeRange;
	//!	The download item range
	DwordRange							mDownloadItemRange;

	//!	The notifier
	INetworkDownloaderNotifierRef		mNotifier;

	//!	The connections
	ConnectionInfoMap					mConnections;

private:
	//!	Parse URL address, relative file name and connection type.
	static _ubool ParseURLAddress( WStringPtr url_address, _NETWORK_CONNECTION_TYPE& type, WString& username, WString& password, WString& root_url_address, WString& relative_file_name );

	//!	Download manifest file and all resources from it.
	static _thread_ret OnDownloadManifestFile( _void* user_data );

private:
	//!	Download files by manifest file.
	_ubool DownloadFiles( WStringPtr root_url_address, IArchive* local_archive, IManifestFile* manifest_file, _dword connect_timeout, _dword timeout );

	//!	Download manifest file.
	_ubool DownloadManifestFile( WStringPtr temp_manifest_file_name, DownloadManifestFileInfo& info );
	//!	Parse manifest file.
	IManifestFileRef ParseManifestFile( WStringPtr file_name, DownloadManifestFileInfo& info );
	//!	Replace manifest file.
	_ubool ReplaceManifestFile( IArchive* local_archive );

	//!	Download files.
	_ubool DownloadFiles( IManifestFile* manifest_file, DownloadManifestFileInfo& info );
	//!	Replace files.
	_ubool ReplaceFiles( WStringPtr temp_dir, WStringPtr local_res_dir );

	//!	Get the connection by root URL address.
	INetworkConnectionRef GetConnection( _NETWORK_CONNECTION_TYPE type, WStringPtr username, WStringPtr password, WStringPtr url_address_with_port );

	//!	Add download task.
	_ubool AddDownloadTask( INetworkConnection* connection, WStringPtr relative_file_name, IArchive* local_archive, WStringPtr local_file_name, const MD5Code& md5_code, _dword connect_timeout, _dword timeout );

public:
	NetworkDownloader( );
	virtual ~NetworkDownloader( );

public:
	EGE_GET_SET_ACCESSOR( INetworkDownloaderNotifier::_ERROR, LastErrID )
	EGE_GET_SET_ACCESSOR( DwordRange&, DownloadSizeRange )
	EGE_GET_SET_ACCESSOR( DwordRange&, DownloadItemRange )

public:
	//!	Initialize.
	_ubool Initialize( _dword downloader_thread_number );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void							Tick( _time_t tick, _dword elapse ) override;

// INetworkDownloader Interface
public:
	virtual _void							SetNotifier( INetworkDownloaderNotifier* notifier ) override;
	virtual INetworkDownloaderNotifierRef	GetNotifier( ) override;

	virtual _void							SetEncryptionType( _ENCRYPTION type ) override;
	virtual _void							SetEncryptionKey( AStringPtr key ) override;

	virtual _void							SetLastDownloadFileResName( WStringPtr res_name ) override;
	virtual WStringPtr						GetLastDownloadFileResName( ) const override;

	virtual _void							SetMaxDownloadSpeed( _dword max_recv_bytes ) override;
	virtual _dword							GetMaxDownloadSpeed( ) const override;

	virtual const Version&					GetLatestManifestVersion( ) const override;

	virtual _void							Start( ) override;
	virtual _void							Pause( ) override;

	virtual _ubool							DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, _dword connect_timeout = -1, _dword timeout = -1 ) override;
	virtual _ubool							DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, const MD5Code& md5_code, _dword connect_timeout = -1, _dword timeout = -1 ) override;

	virtual _ubool							DownloadFiles( WStringPtr root_url_address, IArchive* local_archive, _dword connect_timeout = -1, _dword timeout = -1 ) override;

	virtual _ubool							StartUpgrade( IArchive* local_archive, const Version& version ) override;
};

//----------------------------------------------------------------------------
// NetworkDownloader Implementation
//----------------------------------------------------------------------------

}