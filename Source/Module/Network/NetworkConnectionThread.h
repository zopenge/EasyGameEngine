//! @file     NetworkConnectionThread.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkConnectionThread
//----------------------------------------------------------------------------

class NetworkConnectionThread : public TObject< INetworkConnectionThread >
{
private:
	typedef Array< INetworkConnectionRef > ConnectionArray;

public:
	//!	The state flag
	enum _FLAG
	{
		_FLAG_CONNECT	= 1 << 0,
		_FLAG_SEND		= 1 << 1,
		_FLAG_RECV		= 1 << 2,
		_FLAG_ALL		= _FLAG_CONNECT | _FLAG_SEND | _FLAG_RECV,
	};

private:
	//!	The locker
	Lock				mLocker;
	//!	The thread
	PersistenceThread	mThread;

	//!	The flags
	FlagsObject			mFlags;

	//!	The connections
	ConnectionArray		mConnections;

private:
	//!	The connection update callback function.
	static _dword OnUpdateConnectionCallback( const QwordParameters2& parameters );

public:
	NetworkConnectionThread( _dword flags );
	virtual ~NetworkConnectionThread( );

public:
	//!	Initialize.
	_ubool Initialize( _dword max_connection_number, _dword interval, WStringPtr thread_name );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void		Tick( _dword limited_elapse, _dword elapse ) override;

// INetworkConnectionThread Interface
public:
	virtual WStringPtr	GetName( ) const override;

	virtual _void		Stop( ) override;
	virtual _void		Pause( ) override;
	virtual _void		Resume( ) override;

	virtual _void		AddConnection( INetworkConnection* connection ) override;
	virtual _dword		GetConnectionsNumber( ) const override;

	virtual _void		ProcessConnectionOperations( INetworkConnection* connection ) override;
};

//----------------------------------------------------------------------------
// NetworkConnectionThread Implementation
//----------------------------------------------------------------------------

}