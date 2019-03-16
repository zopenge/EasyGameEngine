//! @file     NetworkNamedPipeStation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkNamedPipeStation Implementation
//----------------------------------------------------------------------------

NetworkNamedPipeStation::NetworkNamedPipeStation( )
{
}

NetworkNamedPipeStation::~NetworkNamedPipeStation( )
{
	Stop( );
}

_dword NetworkNamedPipeStation::OnGetAvailableBytes( const SocketInfo& socket_info )
{
	return socket_info.mSocket->GetTotalAvailableSize( );
}

_dword NetworkNamedPipeStation::OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size )
{
	_dword read_size = 0;
	if ( socket_info.mSocket->Read( buffer, size, &read_size ) == _false )
		return -1;

	return read_size;
}

_dword NetworkNamedPipeStation::OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size )
{
	_dword send_size = 0;
	if ( socket_info.mSocket->Write( buffer, size, &send_size ) == _false )
		return -1;

	return send_size;
}

_void NetworkNamedPipeStation::OnClose( SocketInfo& socket_info )
{
	EGE_DELETE( socket_info.mSocket );
}

_void NetworkNamedPipeStation::OnDownload( )
{
	for ( _dword i = 0; i < mSockets.Number( ); i ++ )
	{
		// Get the pipe
		Pipe* pipe = mSockets[i].mSocket;

		// Build connection
		if ( pipe->IsConnected( ) == _false )
		{
			// Wait for the client connect
			if ( pipe->WaitConnection( ) == _false )
			{
				continue;
			}
			// Establish a client connection successful
			else
			{
				// Now we add a candidate pipe at the tail for the future client connection
				Pipe* candidate_pipe = new Pipe( );
				if ( candidate_pipe->CreateServer( pipe->GetName( ), pipe->GetType( ), pipe->GetSize( ), pipe->GetTimeout( ) ) == _false )
					{ EGE_DELETE( candidate_pipe ); continue; }

				AppendSocket( candidate_pipe );
			}
		}

		// Process pipe
		if ( ProcessSocketDownload( mSockets[i] ) == _false )
		{
			// It's disconnected, remove it
			EGE_DELETE( pipe ); 
			mSockets.RemoveByIndex( i -- );
			continue;
		}
	}
}

_void NetworkNamedPipeStation::OnUpload( )
{

}

_ubool NetworkNamedPipeStation::Initialize( WStringPtr pipename, _dword type, _dword size, _dword timeout )
{
	// Create the first pipe
	Pipe* pipe = new Pipe( );
	if ( pipe->CreateServer( pipename, type, size, timeout ) == _false )
		{ EGE_DELETE( pipe ); return _false; }

	// Append the first pipe
	if ( AppendSocket( pipe ) == _false )
		return _false;

	// Initialize base core
	if ( BaseClass::Initialize( L"PipeNet:" + pipename ) == _false )
		return _false;

	// Set the station name
	SetName( pipename );

	return _true;
}