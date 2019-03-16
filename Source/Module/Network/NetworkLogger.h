//! @file     NetworkLogger.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkLogger
//----------------------------------------------------------------------------

class NetworkLogger : public TLogger< INetworkLogger >
{
private:
	typedef TLogger< INetworkLogger > BaseClass;

private:
	//!	The interval of sending log
	_dword						mInterval;
	//!	The last tickcount
	_dword						mLastTickcount;
	//!	The string what will be sent
	WString						mString;

	//!	True indicates enable compression feature
	_ubool						mEnableCompression;

	//!	The protocol buffer processor
	IProtoBufProcessorRef		mProtocolBufProcessor;
	//!	The connection
	INetworkConnectionRef		mConnection;

private:
	//!	Send message in protocol buffer format.
	_void SendMessage( _dword id, const google::protobuf::MessageLite& message );
	//!	Send log string.
	_void SendLogString( );

// TLogger Interface
private:
	virtual _void	OnPreWriteLogString( _LOG type, WString& string ) override;
	virtual _void	OnWriteLogString( _LOG type, WStringPtr string ) override;

public:
	NetworkLogger( );
	virtual ~NetworkLogger( );

public:
	//!	Initialize.
	_ubool Initialize( INetworkConnection* connection );

// INetworkLogger Interface
public:
	virtual _void	LogIn( ) override;
	virtual _void	LogOut( ) override;

	virtual _void	SetInterval( _dword interval ) override;
	virtual _dword	GetInterval( ) const override;

	virtual _void	EnableCompression( _ubool enable ) override;
	virtual _ubool	IsEnabledCompression( ) const override;
};

//----------------------------------------------------------------------------
// NetworkLogger Implementation
//----------------------------------------------------------------------------

}