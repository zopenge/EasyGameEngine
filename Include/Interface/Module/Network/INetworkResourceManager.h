//! @file     INetworkResourceManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkResourceManager
//----------------------------------------------------------------------------

class INetworkResourceManager : public IObject
{
public:
	//!	Create network notifier.
	//!	@param		none.
	//!	@return		The network notifier.
	virtual INetworkConnectionNotifierPassRef CreateNetworkConnectionNotifier( INetworkConnectionNotifier* notifier ) PURE;

	//!	Create TCP connection.
	//!	@param		remote_address		The remote address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkTCPConnectionPassRef CreateTCPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create TCP station.
	//!	@param		port					The port number.
	//! @param		max_connection_number	The max connections number.
	//!	@param		recv_block_size			The size of recv block.
	//! @return		The network station interface.
	virtual INetworkStationPassRef CreateTCPStation( _dword port, _dword max_connection_number, _dword recv_block_size = 64 KB ) PURE;

	//!	Create HTTP connection.
	//!	@param		remote_address	The remote address.
	//!	@param		notifier		The notifier.
	//! @return		The network connection interface.
	virtual INetworkHTTPConnectionPassRef CreateHTTPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create HTTP connection.
	//!	@param		url_address			The URL address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkHTTPConnectionPassRef CreateHTTPConnection( AStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create HTTP connection.
	//!	@param		url_address			The URL address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkHTTPConnectionPassRef CreateHTTPConnection( WStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create FTP connection.
	//!	@param		remote_address		The remote address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkFTPConnectionPassRef CreateFTPConnection( const Address& remote_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create FTP connection.
	//!	@param		url_address			The URL address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkFTPConnectionPassRef CreateFTPConnection( AStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create FTP connection.
	//!	@param		url_address			The URL address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkFTPConnectionPassRef CreateFTPConnection( WStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;

	//!	Create named pipe connection.
	//!	@param		name				The unique pipe name.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkNamedPipeConnectionPassRef CreateNamedPipeConnection( WStringPtr pipename, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create named pipe station.
	//!	@param		name	The unique pipe name.
	//!	@param		type	The pipe type, @see _PIPE_TYPE.
	//!	@param		size	The number of bytes to reserve for the output and input buffer. 
	//!	@param		timeout	The default time-out value, in milliseconds.
	//! @return		The network station interface.
	virtual INetworkStationPassRef CreateNamedPipeStation( WStringPtr pipename, _dword type, _dword size, _dword timeout ) PURE;

	//!	Create bluetooth connection.
	//!	@param		address				The remote server address.
	//!	@param		uid					The remote server UID.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkBluetoothConnectionPassRef CreateBluetoothConnection( AStringPtr address, const UID128& uid, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create bluetooth station.
	//!	@param		uid		The server UID.
	//! @return		The network station interface.
	virtual INetworkStationPassRef CreateBluetoothStation( const UID128& uid ) PURE;

	//!	Create protocol buffer connection in TCP mode.
	//!	@param		remote_address		The remote address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkProtoBufTCPConnectionPassRef CreateProtoBufTCPConnection( const Address& remote_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create HTTP connection in HTTP mode.
	//!	@param		url_address			The URL address.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkProtoBufHTTPConnectionPassRef CreateProtoBufHTTPConnection( WStringPtr url_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;
	//!	Create protocol buffer connection in TCP mode.
	//!	@param		name				The unique pipe name.
	//!	@param		notifier			The notifier.
	//!	@param		thread_alone_mode	True indicates use single thread to process connection.
	//! @return		The network connection interface.
	virtual INetworkProtoBufNamedPipeConnectionPassRef CreateProtoBufNamedPipeConnection( WStringPtr pipename, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode = _false ) PURE;

	//!	Create network HTTP archive.
	//!	@param		remote_path		The remote path.
	//!	@param		use_whole_path	True indicates use the whole path to access/load resource.
	//!	@return		The archive interface.
	virtual IArchivePassRef CreateHTTPArchive( WStringPtr remote_path, _ubool use_whole_path ) PURE;
};

}