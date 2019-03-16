//! @file     NetworkSendOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkSendOperation
//----------------------------------------------------------------------------

class NetworkSendOperation : public TNetworkOperation< INetworkOperation >
{
private:
	typedef TNetworkOperation< INetworkOperation > BaseClass;

private:
	//!	The data chunk info
	struct DataChunkInfo
	{
		//!	The stream reader
		IStreamReaderRef	mStreamReader;
		//!	The stream writer
		IStreamWriterRef	mStreamWriter;

		DataChunkInfo( )
		{

		}
		DataChunkInfo( _dword size, const _byte* buffer )
		{
			// Create stream writer and reader
			mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( size );

			// Write the initial buffer data
			mStreamWriter->WriteBuffer( buffer, size );

			// Create stream reader
			mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mStreamWriter->GetBuffer( ), mStreamWriter->GetSize( ), _STREAM_SHARE_MODE_READ_ONLY );
			EGE_ASSERT( mStreamReader.IsValid( ) );
		}
	};
	typedef Array< DataChunkInfo > DataChunkInfoArray;

private:
	//!	The data chunks
	DataChunkInfoArray	mDataChunks;

private:
	//!	Check whether need to remove data chunk.
	_ubool IsNeedRemoveDataChunk( _PROCESS_STATE state ) const;

// TNetworkOperation Interface
private:
	virtual _PROCESS_STATE			OnProcess( ) override;

public:
	NetworkSendOperation( INetworkConnection* connection, _dword size, const _byte* buffer );
	virtual ~NetworkSendOperation( );

// IActionRecord Interface
public:
	virtual _NETWORK_OPERATION_TYPE GetType( ) const override;

// INetworkOperation Interface
public:
	virtual _ubool					CombineBuffer( _dword size, const _byte* buffer ) override;

	virtual _void					RemoveProcessingBuffers( ) override;
};

//----------------------------------------------------------------------------
// NetworkSendOperation Implementation
//----------------------------------------------------------------------------

}