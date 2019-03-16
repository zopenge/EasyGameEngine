//! @file     NetworkHTTPConnection.chrome.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkHTTPConnection
//----------------------------------------------------------------------------

class NetworkHTTPConnection : public TNetworkHTTPConnection< INetworkHTTPConnection >
{
private:
	typedef TNetworkHTTPConnection< INetworkHTTPConnection > BaseClass;

private:
	//!	The request info.
	struct RequestInfo : public BaseInfo
	{
		//!	The receive data from server
		PP_Var		mRecvData;

		//!	The PPB connection
		PP_Resource	mPPBConnection;

		RequestInfo( )
		{
			this->mType = _TYPE_REQUEST;

			// Create recv data
			mRecvData = GetPPResourceModule( )->CreateVar( );

			// Create PPB connection
			mPPBConnection = GetPPResourceModule( )->GetPPBWebSocket( )->Create( GetPPResourceModule( )->GetPPInstance( ) );
			EGE_ASSERT( mPPBConnection != _null );
		}
		~RequestInfo( )
		{
			GetPPResourceModule( )->ReleaseVar( mRecvData );

			GetPPResourceModule( )->ReleaseResource( mPPBConnection );
		}
	};
	typedef Array< RequestInfo* > RequestInfoPtrArray;

private:
	//!	The thread locker
	Lock				mLocker;

	//!	The requests
	RequestInfoPtrArray	mRequests;

private:
	//!	When connection finished callback function.
	static _void OnConnectionFinished( _void* user_data, _int result );
	//!	When receive data from server.
	static _void OnRecv( _void* user_data, _int result );

public:
	NetworkHTTPConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkHTTPConnection( );

// INetworkConnection Interface
public:
	virtual _void						Stop( ) override;

	virtual _ubool						IsRemoteFileExist( WStringPtr filename ) override;
	virtual INetworkStreamReaderPassRef	OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual _void						ProcessDelayConnectOperations( ) override;
	virtual _void						ProcessDelaySendOperations( ) override;
	virtual _void						ProcessDelayRecvOperations( ) override;

// INetworkHTTPConnection Interface
public:
	virtual _ubool						Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool						GetWithNoBody( AStringPtr url_name ) override;

	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters ) override;
	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
};

//----------------------------------------------------------------------------
// NetworkHTTPConnection Implementation
//----------------------------------------------------------------------------

}