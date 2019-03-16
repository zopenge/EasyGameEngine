//! @file     INetworkConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkConnectionNotifier
//----------------------------------------------------------------------------

class INetworkConnectionNotifier : public IObject
{
public:
	//!	When update connection state.
	//!	@param		state		The current connection state.
	//!	@return		none.
	virtual _void OnUpdateState( _CONNECTION_STATE state ) PURE;
	//!	When network connection error occurred.
	//!	@param		err_desc	The error description.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) PURE;

	//!	The debug string buffer will be received when we enable the debug mode, we can register the callback function to process debug info here.
	//!	@param		type		The debug type.
	//!	@param		buffer		The debug buffer data.
	//!	@param		size		The debug buffer size.
	//!	@param		parameters	The user defined parameters.
	//! @return		none.
	virtual _void OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters ) PURE;
	//!	When receive buffer on connection.
	//!	@param		size		The buffer size, if it's equal to 0 then indicates we finish it.
	//!	@param		buffer		The buffer data.
	//!	@param		parameters	The user defined parameters.
	//!	@return		The processed buffer size what you have processed.
	virtual _dword OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) PURE;
	//!	When send buffer on connection.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) PURE;
	//!	When receive header info on connection.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters ) PURE;
	//!	When transferring data on connection.
	//!	@param		dltotal		The total download bytes.
	//!	@param		dlnow		The current download bytes.
	//!	@param		ultotal		The total upload bytes.
	//!	@param		ulnow		The current upload bytes.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters ) PURE;
	//!	When finished request on connection.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnFinishBuffer( const QwordParameters4& parameters ) PURE;
};

//----------------------------------------------------------------------------
// INetworkConnection
//----------------------------------------------------------------------------

class INetworkConnection : public ITFlagsObject< IConnection >
{
public:
	//!	The features flags
	enum _FLAGS
	{
		//!	True indicates with certificate
		_FLAG_WITH_CERTIFICATE					= 1 << 0,
		//!	True indicates enable auto-connection feature
		_FLAG_AUTO_CONNECTION					= 1 << 1,
		//!	True indicates enable resend all data when reconnect happen
		_FLAG_RESEND_ALL_DATA_WHEN_RECONNECT	= 1 << 2,
		//!	Run in block mode
		_FLAG_BLOCK_MODE						= 1 << 3,
		//!	Run in async parallel mode
		_FLAG_ASYNC_PARALLEL_MODE				= 1 << 4,
	};

public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier( INetworkConnectionNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual INetworkConnectionNotifier* GetNotifier( ) PURE;

	//!	Get the connection type.
	//!	@param		none.
	//!	@return		The connection type.
	virtual _NETWORK_CONNECTION_TYPE GetType( ) const PURE;

	//!	Get the root URL.
	//!	@param		none.
	//!	@return		The root URL.
	virtual AStringPtr GetRootURL( ) const PURE;

	//!	Check whether it's busy or not.
	//!	@param		none.
	//!	@return		True indicates it's busy.
	virtual _ubool IsBusy( ) const PURE;

	//!	Set the connect timeout in milliseconds.
	//!	@param		timeout		The time out in milliseconds, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetConnectTimeout( _dword timeout ) PURE;
	//!	Get the connect timeout in milliseconds.
	//!	@param		none.
	//!	@return		The time out in milliseconds, -1 indicates unlimited.
	virtual _dword GetConnectTimeout( ) const PURE;

	//!	Set the low speed limit in bytes.
	//!	@param		limit_speed_bytes	The bytes of limit speed.
	//!	@return		none.
	virtual _void SetLowSpeedLimit( _dword limit_speed_bytes ) PURE;
	//!	Get the low speed limit in bytes.
	//!	@param		none.
	//!	@return		The low speed limit in bytes, -1 indicates unlimited.
	virtual _dword GetLowSpeedLimit( ) const PURE;

	//!	Set the max upload speed in bytes.
	//!	@param		max_send_bytes	The max send bytes, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetMaxUploadSpeed( _qword max_send_bytes ) PURE;
	//!	Get the max upload speed in bytes.
	//!	@param		none.
	//!	@return		The max send bytes, -1 indicates unlimited.
	virtual _qword GetMaxUploadSpeed( ) const PURE;

	//!	Set the max download speed in bytes.
	//!	@param		max_recv_bytes	The max receive bytes, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetMaxDownloadSpeed( _qword max_recv_bytes ) PURE;
	//!	Get the max download speed in bytes.
	//!	@param		none.
	//!	@return		The max receive bytes, -1 indicates unlimited.
	virtual _qword GetMaxDownloadSpeed( ) const PURE;

	//!	Get the port.
	//!	@param		none.
	//! @return		The port ID.
	virtual _dword GetPort( ) const PURE;
	//!	Get the local address.
	//!	@param		none.
	//! @return		The local address.
	virtual const Address& GetLocalAddress( ) const PURE;
	//!	Get the remote address.
	//!	@param		none.
	//! @return		The remote address.
	virtual const Address& GetRemoteAddress( ) const PURE;

	//!	Set the request time.
	//!	@param		time	The request time.
	//!	@return		none.
	virtual _void SetRequestTime( const Time& time ) PURE;
	//!	Get the request time.
	//!	@param		none.
	//!	@return		The request time.
	virtual const Time& GetRequestTime( ) const PURE;

	//!	Set the auto-reconnection info.
	//!	@param		enable		True indicates enable auto-reconnection.
	//!	@param		interval	The interval of auto-reconnection in milliseconds.
	//!	@return		none.
	virtual _void SetAutoReconnection( _ubool enable, _dword interval ) PURE;
	//!	Get the auto-reconnection interval.
	//!	@param		none.
	//!	@return		The interval of auto-reconnection in milliseconds.
	virtual _dword GetAutoReconnectionInterval( ) const PURE;

	//!	Connect.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Connect( ) PURE;
	//!	Disconnect.
	//!	@param		none.
	//! @return		none.
	virtual _void Disconnect( ) PURE;

	//!	Stop all operations.
	//!	@param		none.
	//!	@return		none.
	virtual _void Stop( ) PURE;

	//!	Send.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Send( _dword size, const _byte* buffer ) PURE;
	//!	Send instantly.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SendInstant( _dword size, const _byte* buffer ) PURE;

	//!	Check whether remote file is existing or not.
	//!	@param		filename	The relative remote file name of the host.
	//!	@return		True indicates it's existing.
	virtual _ubool IsRemoteFileExist( WStringPtr filename ) PURE;
	//!	Get the last modified time of remote file.
	//!	@param		filename	The relative remote file name of the host.
	//!	@param		time		The last modified time.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time ) PURE;
	//!	Open the remote file.
	//!	@param		filename	The relative remote file name of the host.
	//! @return		The remote file stream reader interface.
	virtual INetworkStreamReaderPassRef OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) PURE;

	//!	Get connect action record.
	//!	@param		none.
	//! @return		The action record interface.
	virtual IActionRecorder* GetConnectActionRecord( ) PURE;
	//!	Get send action record.
	//!	@param		none.
	//! @return		The action record interface.
	virtual IActionRecorder* GetSendActionRecord( ) PURE;
	//!	Get recv action record.
	//!	@param		none.
	//! @return		The action record interface.
	virtual IActionRecorder* GetRecvActionRecord( ) PURE;

	//!	Process delay connect operations.
	//!	@param		none.
	//! @return		none.
	virtual _void ProcessDelayConnectOperations( ) PURE;
	//!	Process delay send operations.
	//!	@param		none.
	//! @return		none.
	virtual _void ProcessDelaySendOperations( ) PURE;
	//!	Process delay recv operations.
	//!	@param		none.
	//! @return		none.
	virtual _void ProcessDelayRecvOperations( ) PURE;

	//!	Process connection action.
	//!	@param		none.
	//! @return		The process state.
	virtual _PROCESS_STATE ProcessConnectAction( ) PURE;
	//!	Process recv action.
	//!	@param		stream_writer	The stream writer.
	//! @return		The process state.
	virtual _PROCESS_STATE ProcessRecvAction( IStreamWriter* stream_writer ) PURE;
	//!	Process send action.
	//!	@param		stream_reader	The stream reader.
	//! @return		The process state.
	virtual _PROCESS_STATE ProcessSendAction( IStreamReader* stream_reader ) PURE;
};

}