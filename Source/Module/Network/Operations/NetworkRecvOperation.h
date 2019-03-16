//! @file     NetworkRecvOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkRecvOperation
//----------------------------------------------------------------------------

class NetworkRecvOperation : public TNetworkOperation< INetworkOperation >
{
private:
	typedef TNetworkOperation< INetworkOperation > BaseClass;

private:
	//!	The default stream buffer size
	enum { _DEFAULT_STREAM_BUFFER_SIZE = 256 KB };

private:
	//!	The stream writer
	IStreamWriterRef	mStreamWriter;

// TNetworkOperation Interface
private:
	virtual _PROCESS_STATE			OnProcess( ) override;

public:
	NetworkRecvOperation( INetworkConnection* connection );
	virtual ~NetworkRecvOperation( );

// IActionRecord Interface
public:
	virtual _NETWORK_OPERATION_TYPE GetType( ) const override;
};

//----------------------------------------------------------------------------
// NetworkRecvOperation Implementation
//----------------------------------------------------------------------------

}