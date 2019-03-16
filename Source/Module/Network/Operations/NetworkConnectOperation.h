//! @file     NetworkConnectOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkConnectOperation
//----------------------------------------------------------------------------

class NetworkConnectOperation : public TNetworkOperation< INetworkOperation >
{
private:
	typedef TNetworkOperation< INetworkOperation > BaseClass;

private:
	//!	The start time in milliseconds to execute connection operation
	_dword mStartTime;

// TNetworkOperation Interface
private:
	virtual _PROCESS_STATE			OnProcess( ) override;

public:
	NetworkConnectOperation( INetworkConnection* connection );
	virtual ~NetworkConnectOperation( );

// IActionRecord Interface
public:
	virtual _NETWORK_OPERATION_TYPE GetType( ) const override;
};

//----------------------------------------------------------------------------
// NetworkConnectOperation Implementation
//----------------------------------------------------------------------------

}