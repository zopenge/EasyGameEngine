//! @file     NetworkHTTPStreamReader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class NetworkHTTPStreamReader;

//----------------------------------------------------------------------------
// NetworkHTTPStreamReaderNotifier
//----------------------------------------------------------------------------

class NetworkHTTPStreamReaderNotifier : public TObject< INetworkConnectionNotifier >
{
private:
	NetworkHTTPStreamReader*	mStreamReader;

public:
	NetworkHTTPStreamReaderNotifier( NetworkHTTPStreamReader* stream_reader );
	virtual ~NetworkHTTPStreamReaderNotifier( );

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
// NetworkHTTPStreamReader
//----------------------------------------------------------------------------

class NetworkHTTPStreamReader : public TNetworkStreamReader< INetworkStreamReader >
{
private:
	typedef TNetworkStreamReader< INetworkStreamReader > BaseClass;

private:
	//!	The HTTP connection notifier
	NetworkHTTPStreamReaderNotifier*	mConnectionNotifier;

	//!	The HTTP connection for remote file
	INetworkHTTPConnectionRef			mConnection;

public:
	NetworkHTTPStreamReader( INetworkStreamReaderNotifier* notifier );
	virtual ~NetworkHTTPStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr remote_filename, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename );

	//!	Write buffer.
	_void WriteBuffer( const _byte* buffer, _dword size );
	//!	Receive header info.
	_void RecvHeaderInfo( const _chara* buffer, _dword size );
	//!	Update progression.
	_void UpdateProgression( _dword dlnow, _dword dltotal );

// INetworkStreamReader Interface
public:
};

//----------------------------------------------------------------------------
// NetworkHTTPStreamReader Implementation
//----------------------------------------------------------------------------

}