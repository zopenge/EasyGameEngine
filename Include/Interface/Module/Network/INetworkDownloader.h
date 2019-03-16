//! @file     INetworkDownloader.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkDownloaderNotifier
//----------------------------------------------------------------------------

class INetworkDownloaderNotifier : public IObject
{
public:
	//!	The error ID
	enum _ERROR
	{
		_ERROR_NO,

		_ERROR_INVALID_PROTOCOL,
		_ERROR_REMOTE_MANIFEST_IS_NOT_EXISTING,
		_ERROR_LOCAL_MANIFEST_IS_NOT_EXISTING,
		_ERROR_LOCAL_MANIFEST_DECRYPT_INVALID,
		_ERROR_LOCAL_MANIFEST_IS_INVALID,
		_ERROR_DOWNLOAD_RESOURCES_FROM_MANIFEST_FAILED,
		_ERROR_REMOTE_RESOURCE_IS_NOT_EXISTING,
		_ERROR_REMOTE_RESOURCE_IS_EMPTY,
		_ERROR_REMOTE_RESOURCE_DOWNLOAD_FAILED,
		_ERROR_REMOTE_RESOURCE_IS_INVALID,
		_ERROR_LOCAL_RESOURCE_CREATE_FAILED,
		_ERROR_LOCAL_RESOURCE_WRITE_FAILED,
	};

public:
	//!	Get the item range.
	//!	@param		none.
	//!	@return		The item range.
	virtual const DwordRange& GetItemRange( ) const PURE;
	//!	Get the percentage in [0.0, 1.0].
	//!	@param		none.
	//!	@return		The percentage.
	virtual _float GetPercentage( ) const PURE;

	//!	When error occurred.
	//!	@param		err_id				The error ID.
	//!	@return		none.
	virtual _void OnError( _ERROR err_id ) PURE;

	//!	When query the MD5 code of local resource.
	//!	@param		res_file_name		The resource file name.
	//!	@return		The MD5 code of local resource.
	virtual MD5Code	OnQueryMD5Code( WStringPtr res_file_name ) PURE;
	//!	When downloading.
	//!	@param		cur_dl_size			The current download size in bytes.
	//!	@param		total_dl_size		The total download size in bytes.
	//!	@param		cur_item_number		The current processed items number.
	//!	@param		total_item_number	The total processed items number.
	//!	@return		none.
	virtual _void OnDownloading( _qword cur_dl_size, _qword total_dl_size, _dword cur_item_number, _dword total_item_number ) PURE;
	//!	When replacing.
	//!	@param		cur_size			The current size in bytes.
	//!	@param		total_size			The total size in bytes.
	//!	@param		cur_item_number		The current processed items number.
	//!	@param		total_item_number	The total processed items number.
	//!	@return		none.
	virtual _void OnReplacing( _qword cur_size, _qword total_size, _dword cur_item_number, _dword total_item_number ) PURE;
	//!	When finish file download.
	//!	@param		remote_relative_filename	The file URL address.
	//!	@param		local_relative_filename		The local file name of archive.
	//!	@return		none.
	virtual _void OnFinishFile( WStringPtr remote_relative_filename, WStringPtr local_relative_filename ) PURE;
	//!	When finish all.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnFinishAll( ) PURE;

	//!	When replace manifest file.
	//!	@param		stream_reader		The manifest stream reader.
	//!	@param		encryption_type		The encryption type.
	//!	@param		encryption_key		The encryption key.
	//!	@param		manifest_filename	The manifest file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnReplaceManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key, WStringPtr manifest_filename ) PURE;
};

//----------------------------------------------------------------------------
// INetworkDownloader
//----------------------------------------------------------------------------

class INetworkDownloader : public IFlagsObject< IObject >
{
public:
	//!	The flags
	enum _FLAG
	{
	};

public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier( INetworkDownloaderNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual INetworkDownloaderNotifierRef GetNotifier( ) PURE;

	//!	Set the encryption type.
	//!	@param		type		The encryption type.
	//!	@return		none.
	virtual _void SetEncryptionType( _ENCRYPTION type ) PURE;
	//!	Set the encryption key.
	//!	@param		key			The encryption key.
	//!	@return		none.
	virtual _void SetEncryptionKey( AStringPtr key ) PURE;

	//!	Set the last download file resource name.
	//!	@param		res_name	The resource name.
	//!	@return		none.
	virtual _void SetLastDownloadFileResName( WStringPtr res_name ) PURE;
	//!	Get the last download file resource name.
	//!	@param		none.
	//!	@return		The resource name.
	virtual WStringPtr GetLastDownloadFileResName( ) const PURE;

	//!	Set the max download speed in bytes.
	//!	@param		max_recv_bytes	The max receive bytes, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetMaxDownloadSpeed( _dword max_recv_bytes ) PURE;
	//!	Get the max download speed in bytes.
	//!	@param		none.
	//!	@return		The max receive bytes, -1 indicates unlimited.
	virtual _dword GetMaxDownloadSpeed( ) const PURE;

	//!	Get the latest manifest version.
	//!	@param		none.
	//!	@return		The latest manifest version.
	virtual const Version& GetLatestManifestVersion( ) const PURE;

	//!	Start.
	//!	@param		none.
	//! @return		none.
	virtual _void Start( ) PURE;
	//!	Pause.
	//!	@param		none.
	//! @return		none.
	virtual _void Pause( ) PURE;

	//!	Download file.
	//!	@param		url_address		The file URL address.
	//!	@param		local_archive	The local archive.
	//!	@param		local_filename	The local file name of archive.
	//!	@param		connect_timeout	The connect timeout in milliseconds, -1 indicates unlimited.
	//!	@param		timeout			The transfer timeout in milliseconds, -1 indicates unlimited.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, _dword connect_timeout = -1, _dword timeout = -1 ) PURE;
	//!	Download file with MD5 validation.
	//!	@param		url_address		The file URL address.
	//!	@param		local_archive	The local archive.
	//!	@param		local_filename	The local file name of archive.
	//!	@param		md5_code		The md5 code to validate.
	//!	@param		connect_timeout	The connect timeout in milliseconds, -1 indicates unlimited.
	//!	@param		timeout			The transfer timeout in milliseconds, -1 indicates unlimited.
	//!	@param		parameters		The user defined parameters
	//! @return		True indicates success, false indicates failure.
	virtual _ubool DownloadFile( WStringPtr url_address, IArchive* local_archive, WStringPtr local_filename, const MD5Code& md5_code, _dword connect_timeout = -1, _dword timeout = -1 ) PURE;

	//!	Download files by manifest file.
	//!	@param		root_url_address	The root URL address.
	//!	@param		local_archive		The local archive.
	//!	@param		connect_timeout		The connect timeout in milliseconds, -1 indicates unlimited.
	//!	@param		timeout				The transfer timeout in milliseconds, -1 indicates unlimited.
	//!	@param		parameters			The user defined parameters
	//! @return		True indicates success, false indicates failure.
	virtual _ubool DownloadFiles( WStringPtr root_url_address, IArchive* local_archive, _dword connect_timeout = -1, _dword timeout = -1 ) PURE;

	//!	Start upgrade.
	//!	@param		local_archive		The local archive.
	//!	@param		version				The version.
	//!	@param		parameters			The user defined parameters
	//! @return		True indicates success, false indicates failure.
	virtual _ubool StartUpgrade( IArchive* local_archive, const Version& version ) PURE;
};

}