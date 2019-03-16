//! @file     NetworkDownloader.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkStreamReaderNotifier Implementation
//----------------------------------------------------------------------------

NetworkStreamReaderNotifier::NetworkStreamReaderNotifier( NetworkDownloader* downloader )
{
	mDownloader = downloader;
}

NetworkStreamReaderNotifier::~NetworkStreamReaderNotifier( )
{

}

_void NetworkStreamReaderNotifier::OnReading( _dword read_size, _dword total_read_size )
{
	DwordRange&			size_range = mDownloader->GetDownloadSizeRange( );
	const DwordRange&	item_range = mDownloader->GetDownloadItemRange( );

	// Update the current download size
	size_range.mMinValue = read_size;
	size_range.mMaxValue = total_read_size;

	// Notify outside
	mDownloader->GetNotifier( )->OnDownloading( size_range.mMinValue, size_range.mMaxValue, item_range.mMinValue, item_range.mMaxValue );
}

//----------------------------------------------------------------------------
// NetworkDownloaderTask Implementation
//----------------------------------------------------------------------------

NetworkDownloaderTask::NetworkDownloaderTask( INetworkConnection* connection, WStringPtr relative_file_name, IArchive* local_archive, WStringPtr local_file_name, const MD5Code& md5_code, _dword connect_timeout, _dword timeout )
{
	mConnection			= connection;
	mRelativeFileName	= relative_file_name;
	mLocalArchive		= local_archive;
	mLocalFileName		= local_file_name;
	mMD5Code			= md5_code;
	mConnectTimeout		= connect_timeout;
	mTimeout			= timeout;

	// Auto start it
	SetFlags( _FLAG_AUTO_START );
}

NetworkDownloaderTask::~NetworkDownloaderTask( )
{
}

_ubool NetworkDownloaderTask::IsSameResource( ) const
{
	// Open the local resource
	IStreamReaderRef local_stream_reader = mLocalArchive->LoadResourceByPath( mLocalFileName );
	if ( local_stream_reader.IsNull( ) )
		return _false;

	// Build local MD5 code
	MD5Code local_md5_code = MD5Code::cNull;
	if ( GetInterfaceFactory( )->BuildMD5Code( local_stream_reader, local_md5_code ) == _false )
		return _false;

	// Compare with remote MD5 code
	if ( local_md5_code != mMD5Code )
		return _false;

	return _true;
}

_ubool NetworkDownloaderTask::DownloadFile( NetworkDownloader* downloader )
{
	WLOG_TRACE_2( L"Downloading '%s' remote file (timeout:%d) ...", mRelativeFileName.Str( ), mTimeout );

	// The download progression notifier
	NetworkStreamReaderNotifier notifier( downloader );

	// Set timeout
	mConnection->SetConnectTimeout( mConnectTimeout );
	mConnection->SetTimeout( mTimeout );

	// Open the remote stream resource
	INetworkStreamReaderRef remote_stream_reader = mConnection->OpenRemoteFile( mRelativeFileName, &notifier );
	if ( remote_stream_reader.IsNull( ) )
	{
		downloader->GetNotifier( )->OnError( INetworkDownloaderNotifier::_ERROR_REMOTE_RESOURCE_IS_NOT_EXISTING );
		return _false;
	}

	// Get the resource size
	_dword res_size = remote_stream_reader->GetSize( );
	if ( res_size == 0 )
	{
		downloader->GetNotifier( )->OnError( INetworkDownloaderNotifier::_ERROR_REMOTE_RESOURCE_IS_EMPTY );
		return _false;
	}

	// Open the resource file
	IStreamWriterRef local_stream_writer = mLocalArchive->CreateResource( mLocalFileName, res_size );
	if ( local_stream_writer.IsNull( ) )
	{
		downloader->GetNotifier( )->OnError( INetworkDownloaderNotifier::_ERROR_LOCAL_RESOURCE_CREATE_FAILED );
		return _false;
	}

	// Create stream processor
	IStreamProcessorRef stream_processor = GetInterfaceFactory( )->CreateStreamWriterProcessor( mMD5Code );
	if ( stream_processor.IsNull( ) )
		return _false;

	// Write to local resource and validate MD5 code
	_dword output_size = 0;
	if ( stream_processor->Process( remote_stream_reader, res_size, local_stream_writer, res_size, output_size ) == _false )
	{
		downloader->GetNotifier( )->OnError( INetworkDownloaderNotifier::_ERROR_REMOTE_RESOURCE_IS_INVALID );
		return _false;
	}

	// Finish file download
	downloader->GetNotifier( )->OnFinishFile( mRelativeFileName, mLocalFileName );

	WLOG_TRACE_1( L"Download and create '%s' local file OK", mRelativeFileName.Str( ) );

	return _true;
}

ITask::_OPERATION_TYPE NetworkDownloaderTask::OnProcess( _thread_id threadid, _dword& err_id )
{
	NetworkDownloader* downloader = _null;//(NetworkDownloader*) user_data;
	EGE_ASSERT( downloader != _null );

	// Download file if it's different with remote resource
	if ( IsSameResource( ) == _false )
	{
		if ( DownloadFile( downloader ) == _false )
		{
			err_id = INetworkDownloaderNotifier::_ERROR_REMOTE_RESOURCE_DOWNLOAD_FAILED;
			downloader->SetLastErrID( (INetworkDownloaderNotifier::_ERROR) err_id );
			return _OPT_ERR;
		}
	}

	// Get the item range
	DwordRange&	size_range = downloader->GetDownloadSizeRange( );
	DwordRange&	item_range = downloader->GetDownloadItemRange( );

	// Update the current item number
	item_range.mMinValue ++;

	// Notify outside
	downloader->GetNotifier( )->OnDownloading( size_range.mMinValue, size_range.mMaxValue, item_range.mMinValue, item_range.mMaxValue );

	// No Error
	return _OPT_FINISH;
}

//----------------------------------------------------------------------------
// NetworkDownloader Implementation
//----------------------------------------------------------------------------

NetworkDownloader::NetworkDownloader( )
{
	mMaxDownloadSpeed		= -1;

	mEncryptionType			= _ENCRYPTION_UNKNOWN;

	mLastErrID				= INetworkDownloaderNotifier::_ERROR_NO;
	mLatestManifestVersion	= Version::cInitial;

	mDownloadSizeRange		= DwordRange::cNull;
	mDownloadItemRange		= DwordRange::cNull;

	mNotifier				= &NullNetwork::GetInstance( ).GetNetworkDownloaderNotifier( );
}

NetworkDownloader::~NetworkDownloader( )
{
	Finalize( );
}

_ubool NetworkDownloader::ParseURLAddress( WStringPtr url_address, _NETWORK_CONNECTION_TYPE& type, WString& username, WString& password, WString& root_url_address, WString& relative_file_name )
{
	// TCP
	if ( url_address.StartsWith( L"tcp://" ) )
	{

	}
	// HTTP
	else if ( url_address.StartsWith( L"http://" ) )
	{
		type = _NETWORK_CONNECTION_HTTP;

		WStringArgParser root_url_address_parser( root_url_address );
		WStringArgParser relative_file_name_parser( relative_file_name );
		if ( StringFormatter::ParseString( url_address.Str( ), L"http://%s/%s", root_url_address_parser, relative_file_name_parser ) != 2 )
		{
			WLOG_ERROR_1( L"The HTTP '%s' URL address is invalid, we must have root and relative file name both", url_address.Str( ) );
			return _false;
		}
	}
	// FTP
	else if ( url_address.StartsWith( L"ftp://" ) )
	{
		type = _NETWORK_CONNECTION_FTP;

		WStringArgParser username_parser( username );
		WStringArgParser password_parser( password );
		WStringArgParser root_url_address_parser( root_url_address );
		WStringArgParser relative_file_name_parser( relative_file_name );
		if ( StringFormatter::ParseString( url_address.Str( ), L"ftp://%s:%s@%s/%s", username_parser, password_parser, root_url_address_parser, relative_file_name_parser ) != 4 )
		{
			WLOG_ERROR_1( L"The FTP '%s' URL address is invalid, we must have root and relative file name both", url_address.Str( ) );
			return _false;
		}
	}
	// Unknown
	else
	{
		WLOG_ERROR_1( L"The '%s' URL address is invalid", url_address.Str( ) );
		return _false;
	}

	return _true;
}

_thread_ret NetworkDownloader::OnDownloadManifestFile( _void* user_data )
{
	MemPtr< DownloadManifestFileInfo > info = (DownloadManifestFileInfo*) user_data;
	EGE_ASSERT( info.IsValid( ) );

	// Get the downloader
	NetworkDownloader* downloader = info->mDownloader;
	EGE_ASSERT( downloader != _null );

	// Build the temporary manifest file name
#pragma _NOTE_TODO( "Provide the manifest file name" )
	WString temp_manifest_file_name = L"";//Path::GetFileName( GetAppDelegate( )->OnGetManifestFileName( ), _false );
	
	// Download manifest file
	downloader->DownloadManifestFile( temp_manifest_file_name, *info );

	// Notify outside we have finished if no any errors
	if ( info->mLastErrID == INetworkDownloaderNotifier::_ERROR_NO )
	{
		// Parse manifest file
		IManifestFileRef manifest_file = downloader->ParseManifestFile( temp_manifest_file_name, *info );
		if ( manifest_file.IsValid( ) )
		{
			// Download files by manifest file
			downloader->DownloadFiles( manifest_file, *info );

			// Update the latest manifest file version
			downloader->mLatestManifestVersion = manifest_file->GetVersion( );
		}

		// Finished all download tasks
		downloader->GetNotifier( )->OnFinishAll( );
	}

	return EXIT_SUCCESS;
}

_ubool NetworkDownloader::DownloadFiles( WStringPtr root_url_address, IArchive* local_archive, IManifestFile* manifest_file, _dword connect_timeout, _dword timeout )
{
	if ( root_url_address.IsEmpty( ) )
		return _false;

	if ( local_archive == _null || manifest_file == _null )
		return _false;

	// Create manifest file walker
	IManifestWalkerRef walker = manifest_file->CreateWalker( L"" );
	if ( walker.IsNull( ) )
		return _false;

	// Check whether we hit the last download file request
	_ubool has_last_download_file = _false;

	// Start to download files from manifest 
	ManifestWalkerItemInfo item_info;
	while ( walker->Walk( item_info, L"", _FILE_FINDER_ENUMERATION_FILE_ONLY ) )
	{
		EGE_ASSERT( item_info.mItem != _null );

		// Build URL address
		WString url_address = Path::BuildFilePath( root_url_address, item_info.mAbsolutePath );

		// Check the MD5 code to determine to download or skip it
		if ( item_info.mItem->mMD5Code == GetNotifier( )->OnQueryMD5Code( item_info.mAbsolutePath ) )
			continue;

		// Check whether it's last download file
		if ( (mLastDownloadFileResName.IsEmpty( ) == _false) && mLastDownloadFileResName == item_info.mItem->mName )
		{
			has_last_download_file	= _true;
			continue;
		}

		// Start to download file
		if ( DownloadFile( url_address, local_archive, item_info.mAbsolutePath, item_info.mItem->mMD5Code, connect_timeout, timeout ) == _false )
			return _false;
	}

	// Start to download the last resource file
	if ( has_last_download_file )
	{
		// Get the last resource info from manifest
		ManifestItemNodeInfoArray last_items_info;
		manifest_file->GetRootDir( )->GetSubItems( mLastDownloadFileResName, _false, last_items_info );

		// The last item must be unique
		if ( last_items_info.Number( ) != 1 )
			return _false;

		// Get the last item info
		const ManifestItemNodeInfo& last_item_node = last_items_info[0];

		// Build URL address
		WString relative_path	= Path::BuildFilePath( last_item_node.mParentDir->GetPath( ), last_item_node.mName );
		WString url_address		= Path::BuildFilePath( root_url_address, relative_path );

		// Start to download file
		if ( DownloadFile( url_address, local_archive, relative_path, last_item_node.mMD5Code, connect_timeout, timeout ) == _false )
			return _false;
	}

	return _true;
}

_ubool NetworkDownloader::DownloadManifestFile( WStringPtr temp_manifest_file_name, DownloadManifestFileInfo& info )
{
	// Disable the notifier
	INetworkDownloaderNotifierRef notifier_backup = mNotifier;
	SetNotifier( &NullNetwork::GetInstance( ).GetNetworkDownloaderNotifier( ) );

	// Build the URL address
#pragma _NOTE_TODO( "Provide the manifest file name" )
	WString url_address = L"";//Path::BuildFilePath( info.mRootURLAddress, GetAppDelegate( )->OnGetManifestFileName( ) );

	// Start to download manifest file
	_ubool result = DownloadFile( url_address, info.mLocalArchive, temp_manifest_file_name, info.mConnectTimeout, info.mTimeout );
	if ( result == _false )
		GetNotifier( )->OnError( info.mLastErrID = INetworkDownloaderNotifier::_ERROR_REMOTE_MANIFEST_IS_NOT_EXISTING );

	// Resume the notifier
	SetNotifier( notifier_backup );

	return info.mLastErrID == INetworkDownloaderNotifier::_ERROR_NO;
}

IManifestFileRef NetworkDownloader::ParseManifestFile( WStringPtr file_name, DownloadManifestFileInfo& info )
{
	WLOG_TRACE_1( L"Loading local temporary '%s' manifest file ...", file_name.Str( ) );

	// Open the manifest file resource
	IStreamReaderRef stream_reader = info.mLocalArchive->LoadResource( file_name );
	if ( stream_reader.IsNull( ) )
	{
		GetNotifier( )->OnError( info.mLastErrID = INetworkDownloaderNotifier::_ERROR_LOCAL_MANIFEST_IS_NOT_EXISTING );
		return _null;
	}

	WLOG_TRACE_1( L"Load local temporary '%s' manifest file OK", file_name.Str( ) );

	WLOG_TRACE_1( L"Decrypting local temporary '%s' manifest file ...", file_name.Str( ) );

	// Decrypt manifest file resource
	IStreamReaderRef decrypt_stream_reader = GetInterfaceFactory( )->DecryptStream( stream_reader, mEncryptionType, mEncryptionKey );
	if ( decrypt_stream_reader.IsNull( ) )
	{
		GetNotifier( )->OnError( info.mLastErrID = INetworkDownloaderNotifier::_ERROR_LOCAL_MANIFEST_DECRYPT_INVALID );
		return _null;
	}

	WLOG_TRACE_1( L"Decrypt local temporary '%s' manifest file OK", file_name.Str( ) );

	WLOG_TRACE_1( L"Parsing local temporary '%s' manifest file ...", file_name.Str( ) );

	// Open the manifest file
	IManifestFileRef manifest_file = GetInterfaceFactory( )->ParseManifestFile( decrypt_stream_reader );
	if ( manifest_file.IsNull( ) )
	{
		GetNotifier( )->OnError( info.mLastErrID = INetworkDownloaderNotifier::_ERROR_LOCAL_MANIFEST_IS_INVALID );
		return _null;
	}

	WLOG_TRACE_1( L"Parse local temporary '%s' manifest file OK", file_name.Str( ) );

	return manifest_file;
}

_ubool NetworkDownloader::ReplaceManifestFile( IArchive* local_archive )
{
	// Get the manifest file
#pragma _NOTE_TODO( "Provide the manifest file name" )
	WString manifest_file_name = L"";//GetAppDelegate( )->OnGetManifestFileName( );
	if ( manifest_file_name.IsEmpty( ) )
		return _false;

	WLOG_TRACE_1( L"Replacing '%s' manifest file ...", manifest_file_name.Str( ) );

	// Build the temporary manifest file name
	WString temp_manifest_file_name = Path::GetFileName( manifest_file_name, _false );

	// Get the absolute of temporary manifest file
	WString abs_src_manifest_file_name = Path::BuildFilePath( local_archive->GetPath( ), temp_manifest_file_name );
	WString abs_des_manifest_file_name = abs_src_manifest_file_name + L".xml";

	// Replace the manifest file
	if ( FileSystem::MoveFile( abs_des_manifest_file_name, abs_src_manifest_file_name ) == _false )
		return _false;

	WLOG_TRACE_1( L"Replaced '%s' manifest file OK", manifest_file_name.Str( ) );

	// Open the manifest stream reader
	IFileStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( abs_des_manifest_file_name );
	if ( stream_reader.IsNull( ) )
		return _false;

	// Notify replace manifest file
	if ( GetNotifier( )->OnReplaceManifestFile( stream_reader, mEncryptionType, mEncryptionKey, manifest_file_name ) == _false )
		return _false;

	return _true;
}

_ubool NetworkDownloader::DownloadFiles( IManifestFile* manifest_file, DownloadManifestFileInfo& info )
{
	if ( manifest_file == _null )
		return _false;

	// Get the version manifest file
	const Version& manifest_ver = manifest_file->GetVersion( );

	// Create temporary directory
	WString temp_dir = Path::BuildFilePath( info.mLocalArchive->GetPath( ), L"v" + manifest_ver.ToWString( ) );
	if ( FileSystem::CreateDir( temp_dir ) == _false )
		return _false;

	// Create temporary archive
	IArchiveRef temp_archive = GetInterfaceFactory( )->CreateFileArchive( temp_dir );
	if ( temp_archive.IsNull( ) )
		return _false;

	// Download files from manifest file
	if ( DownloadFiles( info.mRootURLAddress, temp_archive, manifest_file, info.mConnectTimeout, info.mTimeout ) == _false )
	{
		GetNotifier( )->OnError( info.mLastErrID = INetworkDownloaderNotifier::_ERROR_DOWNLOAD_RESOURCES_FROM_MANIFEST_FAILED );
		return _false;
	}

	return _true;
}

_ubool NetworkDownloader::ReplaceFiles( WStringPtr temp_dir, WStringPtr local_res_dir )
{
	FileFinder file_finder;
	if ( file_finder.Open( temp_dir ) == _false )
		return _false;

	// The file info
	FileInfo file_info;

	// The size info
	_qword cur_size = 0, total_size = 0;
	_dword cur_item_number = 0, total_item_number = 0;

	// Get the size info
	while ( file_finder.Walk( file_info, L"", _FILE_FINDER_ENUMERATION_FILE_ONLY ) )
	{
		total_size			+= file_info.mSize;
		total_item_number	++;
	}

	// Reopen it again
	if ( file_finder.Open( temp_dir ) == _false )
		return _false;

	// Start to move files
	while ( file_finder.Walk( file_info, L"", _FILE_FINDER_ENUMERATION_FILE_ONLY ) )
	{
		WString des_file_name = Path::BuildFilePath( local_res_dir, file_info.mRelativePath );
		WString src_file_name = file_info.mAbsolutePath;

		if ( FileSystem::MoveFile( des_file_name, src_file_name ) == _false )
			return _false;

		cur_size		+= file_info.mSize;
		cur_item_number ++;

		GetNotifier( )->OnReplacing( cur_size, total_size, cur_item_number, total_item_number );
	}

	return _true;
}

INetworkConnectionRef NetworkDownloader::GetConnection( _NETWORK_CONNECTION_TYPE type, WStringPtr username, WStringPtr password, WStringPtr url_address_with_port )
{
	mLocker.Enter( );
	INetworkConnectionRef& connection = mConnections[ url_address_with_port ];
	mLocker.Leave( );

	// Create connection if needed
	if ( connection.IsNull( ) )
	{
		switch ( type )
		{
			case _NETWORK_CONNECTION_HTTP:
			{
				connection = GetNetworkResourceManager( )->CreateHTTPConnection( url_address_with_port, _null ).cast_static< INetworkConnection >( );
				if ( connection.IsValid( ) )
				{
					WLOG_TRACE_1( L"Create '%s' HTTP connection for downloader", url_address_with_port.Str( ) );
				}
			}
			break;

			case _NETWORK_CONNECTION_FTP:
			{
				INetworkFTPConnectionRef ftp_connection = GetNetworkResourceManager( )->CreateFTPConnection( url_address_with_port, _null );
				if ( ftp_connection.IsValid( ) )
				{
					ftp_connection->SetUserName( AString( ).FromString( username ) );
					ftp_connection->SetPassword( AString( ).FromString( password ) );

					connection = ftp_connection;

					WLOG_TRACE_1( L"Create '%s' FTP connection for downloader", url_address_with_port.Str( ) );
				}
			}
			break;

			default:
				break;
		}
	}

	return connection;
}

_ubool NetworkDownloader::AddDownloadTask( INetworkConnection* connection, WStringPtr relative_file_name, IArchive* local_archive, WStringPtr local_file_name, const MD5Code& md5_code, _dword connect_timeout, _dword timeout )
{
	// Create download task
	IThreadTaskPassRef task = new NetworkDownloaderTask( connection, relative_file_name, local_archive, local_file_name, md5_code, connect_timeout, timeout );
	if ( mThreadPool->AddTask( task.GetPtr( ) ) == _false )
		return _false;

	return _true;
}

_ubool NetworkDownloader::Initialize( _dword downloader_thread_number )
{
	WLOG_TRACE_1( L"Initialize network downloader (thread:%d) ...", downloader_thread_number );

	if ( downloader_thread_number == 0 )
		return _false;

	// Create thread pool
	mThreadPool = GetInterfaceFactory( )->CreateThreadPool( downloader_thread_number, L"NetDownloader" );
	if ( mThreadPool.IsNull( ) )
		return _false;

	WLOG_TRACE( L"Initialize network downloader OK" );

	return _true;
}

_void NetworkDownloader::Finalize( )
{
	WLOG_TRACE( L"Release network downloader ..." );

	mThreadPool.Clear( );

	WLOG_TRACE( L"Release network downloader DONE" );
}

_void NetworkDownloader::Tick( _time_t tick, _dword elapse )
{
	mThreadPool->Tick( tick, elapse );
}

_void NetworkDownloader::SetNotifier( INetworkDownloaderNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullNetwork::GetInstance( ).GetNetworkDownloaderNotifier( );
	else
		mNotifier = notifier;
}

INetworkDownloaderNotifierRef NetworkDownloader::GetNotifier( )
{
	return mNotifier;
}

_void NetworkDownloader::SetEncryptionType( _ENCRYPTION type )
{
	mEncryptionType = type;
}

_void NetworkDownloader::SetEncryptionKey( AStringPtr key )
{
	mEncryptionKey = key;
}

_void NetworkDownloader::SetLastDownloadFileResName( WStringPtr res_name )
{
	mLastDownloadFileResName = res_name;
}

WStringPtr NetworkDownloader::GetLastDownloadFileResName( ) const
{
	return mLastDownloadFileResName;
}

_void NetworkDownloader::SetMaxDownloadSpeed( _dword max_recv_bytes )
{
	mMaxDownloadSpeed = max_recv_bytes;
}

_dword NetworkDownloader::GetMaxDownloadSpeed( ) const
{
	return mMaxDownloadSpeed;
}

const Version& NetworkDownloader::GetLatestManifestVersion( ) const
{
	return mLatestManifestVersion;
}

_void NetworkDownloader::Start( )
{
	mThreadPool->Wakeup( );
}

_void NetworkDownloader::Pause( )
{
	mThreadPool->Sleep( );
}

_ubool NetworkDownloader::DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, _dword connect_timeout, _dword timeout )
{
	return DownloadFile( url_address, local_archive, local_filename, MD5Code::cNull, connect_timeout, timeout );
}

_ubool NetworkDownloader::DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, const MD5Code& md5_code, _dword connect_timeout, _dword timeout )
{
	if ( url_address.IsEmpty( ) )
		return _false;

	if ( local_archive == _null || local_filename.IsEmpty( ) )
		return _false;

	// Parse URL address
	_NETWORK_CONNECTION_TYPE type = _NETWORK_CONNECTION_UNKNOWN; WString username, password, root_url_address, relative_file_name;
	if ( ParseURLAddress( url_address, type, username, password, root_url_address, relative_file_name ) == _false )
		return _false;

	// Get connection
	INetworkConnectionRef connection = GetConnection( type, username, password, root_url_address );
	if ( connection.IsNull( ) )
	{
		WLOG_ERROR_1( L"Download file failed due to '%s' connection create failed", root_url_address.Str( ) )
		return _false;
	}

	// Add download task
	if ( AddDownloadTask( connection, relative_file_name, local_archive, local_filename, md5_code, connect_timeout, timeout ) == _false )
		return _false;

	// Increase the item number
	mDownloadItemRange.mMaxValue ++;

	return _true;
}

_ubool NetworkDownloader::DownloadFiles( WStringPtr root_url_address, IArchive* local_archive, _dword connect_timeout, _dword timeout )
{
	if ( root_url_address.IsEmpty( ) || local_archive == _null )
		return _false;

	WLOG_TRACE_1( L"Start to download files from '%s' URL address", root_url_address.Str( ) );

	// Create manifest file download task
	DownloadManifestFileInfo* download_manifest_file_info = new DownloadManifestFileInfo( connect_timeout, timeout, root_url_address, local_archive, this );
	if ( Platform::CreateThread( OnDownloadManifestFile, 0, download_manifest_file_info, _false, _null ) == _null )
		return _false;

	// Check whether it's successful
	if ( download_manifest_file_info->mLastErrID != INetworkDownloaderNotifier::_ERROR_NO )
		return _false;

	return _true;
}

_ubool NetworkDownloader::StartUpgrade( IArchive* local_archive, const Version& version )
{
	if ( local_archive == _null )
		return _false;

	WLOG_TRACE( L"Start upgrading ..." );

	// Create temporary directory
	WString temp_dir = Path::BuildFilePath( local_archive->GetPath( ), L"v" + version.ToWString( ) );
	if ( FileSystem::IsDirectoryExist( temp_dir ) == _false )
	{
		WLOG_ERROR_1( L"Start upgrade failed due to '%s' temporary directory it not existing", temp_dir.Str( ) );
		return _false;
	}

	// Replace files
	if ( ReplaceFiles( temp_dir, local_archive->GetPath( ) ) == _false )
	{
		WLOG_ERROR( L"Start upgrading failed due to replace files failed" );
		return _false;
	}

	// Replace manifest file
	if ( ReplaceManifestFile( local_archive ) == _false )
	{
		WLOG_ERROR( L"Start upgrading failed due to replace manifest file failed" );
		return _false;
	}

	// Delete temporary directory
	if ( FileSystem::DeleteDir( temp_dir ) == _false )
	{
		WLOG_ERROR( L"Start upgrading failed due to delete directory failed" );
		return _false;
	}

	return _true;
}