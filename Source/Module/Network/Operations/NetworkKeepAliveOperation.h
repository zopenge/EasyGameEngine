//! @file     NetworkKeepAliveOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkKeepAliveOperation
//----------------------------------------------------------------------------

class NetworkKeepAliveOperation : public TNetworkOperation< INetworkOperation >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( NetworkKeepAliveOperation, INetworkOperation, INetworkConnection* )

private:
	typedef TNetworkOperation< INetworkOperation > BaseClass;

private:
	//!	The last sending tickcount
	_dword					mLastTickcount;
	//!	The sending counter
	_dword					mCounter;

	//!	The protocol buffer processor
	IProtoBufProcessorRef	mProtocolBufProcessor;

// TNetworkOperation Interface
private:
	virtual _PROCESS_STATE			OnProcess( ) override;

public:
	NetworkKeepAliveOperation( INetworkConnection* connection );
	virtual ~NetworkKeepAliveOperation( );

// IActionRecord Interface
public:
	virtual _NETWORK_OPERATION_TYPE GetType( ) const override;
};

//----------------------------------------------------------------------------
// NetworkKeepAliveOperation Implementation
//----------------------------------------------------------------------------

}