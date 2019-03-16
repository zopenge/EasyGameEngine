//! @file     NetworkHTTPArchive.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkStorageArchiveConnectionNotifier Implementation
//----------------------------------------------------------------------------

NetworkStorageArchiveConnectionNotifier::NetworkStorageArchiveConnectionNotifier( NetworkHTTPArchive* archive )
{
	mArchive = archive;
}

NetworkStorageArchiveConnectionNotifier::~NetworkStorageArchiveConnectionNotifier( )
{

}

_void NetworkStorageArchiveConnectionNotifier::OnUpdateState( _CONNECTION_STATE state )
{

}

_void NetworkStorageArchiveConnectionNotifier::OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters )
{
}

_void NetworkStorageArchiveConnectionNotifier::OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters )
{

}

_dword NetworkStorageArchiveConnectionNotifier::OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{
	return size;
}

_void NetworkStorageArchiveConnectionNotifier::OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{

}

_void NetworkStorageArchiveConnectionNotifier::OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters )
{

}

_void NetworkStorageArchiveConnectionNotifier::OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters )
{

}

_void NetworkStorageArchiveConnectionNotifier::OnFinishBuffer( const QwordParameters4& parameters )
{

}

//----------------------------------------------------------------------------
// NetworkHTTPArchive Implementation
//----------------------------------------------------------------------------

NetworkHTTPArchive::NetworkHTTPArchive( )
{
	mUseWholePath		= _false;

	mConnectionNotifier = new NetworkStorageArchiveConnectionNotifier( this );
}

NetworkHTTPArchive::~NetworkHTTPArchive( )
{
	mConnection.Clear( );

	EGE_RELEASE( mConnectionNotifier );
}

WStringR NetworkHTTPArchive::GetTempDir( ) const
{
	WString temp_dir = GetPlatform( )->GetTempDirectory( );
	return FORMAT_WSTRING_2( L"%s/%d", temp_dir.Str( ), mRemotePath.GetCRCValue( ) );
}

WStringR NetworkHTTPArchive::GetLocalCacheFilePath( WStringPtr filename )
{
	// Get the temporary directory
	WString temp_dir = GetTempDir( );

	// Build the file path of the temporary directory
	WString local_filepath = FORMAT_WSTRING_2( L"%s/%d", temp_dir.Str( ), filename.GetCRCValue( ) );

	return local_filepath;
}

_ubool NetworkHTTPArchive::SaveLocalCache( WStringPtr filename, IStreamReader* stream_reader )
{
	if ( FileSystem::CreateFile( filename, stream_reader->GetSize( ), stream_reader->GetBuffer( ) ) == _false )
		return _false;

	return _true;
}

_ubool NetworkHTTPArchive::Initialize( WStringPtr remote_path, _ubool use_whole_path )
{
	mRemotePath		= remote_path;
	mUseWholePath	= use_whole_path;

	// Build remote connection 
	mConnection = GetNetworkResourceManager( )->CreateHTTPConnection( remote_path, mConnectionNotifier );
	if ( mConnection.IsNull( ) )
		return _false;

	return _true;
}

WStringPtr NetworkHTTPArchive::GetPath( ) const
{
	return mRemotePath;
}

_ubool NetworkHTTPArchive::HasResourceByPath( WStringPtr file_name ) const
{
	WString url_address = Path::GetSubURLAddress( file_name, L"http://|https://" );
	if ( url_address.IsEmpty( ) )
	{
		if ( mUseWholePath )
			return _false;

		url_address = file_name;
	}

	// Check the remote file
	if ( mConnection->IsRemoteFileExist( url_address ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef NetworkHTTPArchive::LoadResourceByPath( WStringPtr file_name )
{
	WString url_address = Path::GetSubURLAddress( file_name, L"http://|https://" );
	if ( url_address.IsEmpty( ) )
	{
		if ( mUseWholePath )
			return _null;

		url_address = file_name;
	}

	// Try to load from patch archives
	IStreamReaderPassRef stream_reader = BaseClass::LoadResourceByPath( url_address );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// Try to load from local cache
	WString local_cache_file_path = GetLocalCacheFilePath( url_address );
	if ( local_cache_file_path.IsEmpty( ) == _false )
	{
		IStreamReaderPassRef local_stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( local_cache_file_path );
		if ( local_stream_reader.IsValid( ) )
		{
			WLOG_TRACE_2( L"Load '%s' HTTP stream from '%s' local", url_address.Str( ), local_cache_file_path.Str( ) );
			return local_stream_reader;
		}
	}

	// Open the remote file
	INetworkStreamReaderPassRef network_stream_reader = mConnection->OpenRemoteFile( url_address );
	if ( network_stream_reader.IsValid( ) )
	{
		WLOG_TRACE_1( L"Load '%s' HTTP stream from remote", url_address.Str( ) );

		// Save local cache file
		SaveLocalCache( local_cache_file_path, network_stream_reader.GetPtr( ) );

		return network_stream_reader;
	}

	return _null;
}

_void NetworkHTTPArchive::ClearCaches( )
{
	// Clear the temporary directory
	WString temp_dir = GetTempDir( );
	FileSystem::CleanDir( temp_dir );
}