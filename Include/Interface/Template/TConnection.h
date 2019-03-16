//! @file     TConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TConnection
//----------------------------------------------------------------------------

template< typename Type >
class TConnection : public TPriorityObject< Type >
{
protected:
	typedef TPriorityObject< Type > TBaseClass;

protected:
	//!	The connection state
	_CONNECTION_STATE	mConnectionState;

protected:
	//!	Get the connection state string.
	WStringPtr GetConnectionStateString( _CONNECTION_STATE state ) const;

protected:
	//!	Change the state.
	virtual _void SetConnectionState( _CONNECTION_STATE state );

protected:
	TConnection( );
	virtual ~TConnection( );

// IConnection Interface
public:
	virtual _CONNECTION_STATE	GetConnectionState( ) const override;

	virtual _ubool				IsConnecting( ) const override;
	virtual _ubool				IsConnected( ) const override;
	virtual _ubool				IsConnectionLost( ) const override;
};

//----------------------------------------------------------------------------
// TConnection Implementation
//----------------------------------------------------------------------------

template< typename Type >
TConnection< Type >::TConnection( )
{
	mConnectionState = _CS_UNKNOWN;
}

template< typename Type >
TConnection< Type >::~TConnection( )
{
}

template< typename Type >
WStringPtr TConnection< Type >::GetConnectionStateString( _CONNECTION_STATE state ) const
{
	switch ( state )
	{
		case _CS_UNKNOWN:		return L"Unknown";
		case _CS_CONNECTING:	return L"Connecting";
		case _CS_CONNECTED:		return L"Connected";
		case _CS_DISCONNECTED:	return L"Disconnected";
		default:
			return L"";
	}
}

template< typename Type >
_void TConnection< Type >::SetConnectionState( _CONNECTION_STATE state )
{
	mConnectionState = state;
}

template< typename Type >
_CONNECTION_STATE TConnection< Type >::GetConnectionState( ) const
{
	return mConnectionState;
}

template< typename Type >
_ubool TConnection< Type >::IsConnecting( ) const
{
	return mConnectionState == _CS_CONNECTING;
}

template< typename Type >
_ubool TConnection< Type >::IsConnected( ) const
{
	return mConnectionState == _CS_CONNECTED;
}

template< typename Type >
_ubool TConnection< Type >::IsConnectionLost( ) const
{
	return mConnectionState == _CS_DISCONNECTED;
}

}
