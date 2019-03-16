//! @file     TNetworkOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkOperation
//----------------------------------------------------------------------------

template< typename Type >
class TNetworkOperation : public TObject< Type >
{
protected:
	//!	The thread locker
	Lock				mLocker;

	//!	The connection
	INetworkConnection*	mConnection;

protected:
	//!	When processing.
	virtual _PROCESS_STATE OnProcess( ) PURE;

protected:
	TNetworkOperation( INetworkConnection* connection );
	virtual ~TNetworkOperation( );

// IActionRecord Interface
public:
	virtual _PROCESS_STATE	Process( ) override;

// INetworkOperation Interface
public:
	virtual _ubool			CombineBuffer( _dword size, const _byte* buffer ) override;

	virtual _void			RemoveProcessingBuffers( ) override;
};

//----------------------------------------------------------------------------
// TNetworkOperation Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNetworkOperation< Type >::TNetworkOperation( INetworkConnection* connection )
{
	mConnection	= connection;
}

template< typename Type >
TNetworkOperation< Type >::~TNetworkOperation( )
{

}

template< typename Type >
_PROCESS_STATE TNetworkOperation< Type >::Process( )
{
	LockOwner lock_owner( mLocker );

	return OnProcess( );
}

template< typename Type >
_ubool TNetworkOperation< Type >::CombineBuffer( _dword size, const _byte* buffer )
{
	return _false;
}

template< typename Type >
_void TNetworkOperation< Type >::RemoveProcessingBuffers( )
{

}

}