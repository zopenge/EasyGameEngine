//! @file     TProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TProcessor
//----------------------------------------------------------------------------

template< typename Type >
class TProcessor : public Type
{
protected:
	//!	The state of task
	_PROCESS_STATE	mTaskState;

protected:
	//!	Set state.
	virtual _void SetState( _PROCESS_STATE state );

protected:
	TProcessor( );
	virtual ~TProcessor( );

// IProcessor Interface
public:
	virtual _PROCESS_STATE	GetState( ) const override;

	virtual _ubool			Wait( ) override;
	virtual _ubool 			Start( ) override;
	virtual _ubool 			Resume( ) override;
	virtual _ubool 			Suspend( ) override;
	virtual _ubool 			Abort( ) override;
	virtual _ubool			Finish( ) override;
};

//----------------------------------------------------------------------------
// TProcessor Implementation
//----------------------------------------------------------------------------

template< typename Type >
TProcessor< Type >::TProcessor( )
{
	mTaskState	= _PS_WAITING;
}

template< typename Type >
TProcessor< Type >::~TProcessor( )
{
	// We are releasing it
	SetState( _PS_RELEASING );
}

template< typename Type >
_void TProcessor< Type >::SetState( _PROCESS_STATE state )
{
	mTaskState = state;
}

template< typename Type >
_PROCESS_STATE TProcessor< Type >::GetState( ) const
{
	return mTaskState;
}

template< typename Type >
_ubool TProcessor< Type >::Wait( )
{
	SetState( _PS_WAITING );

	return _true;
}

template< typename Type >
_ubool TProcessor< Type >::Start( )
{
	SetState( _PS_RUNNING );

	return _true;
}

template< typename Type >
_ubool TProcessor< Type >::Resume( )
{
	_PROCESS_STATE state = GetState( );

	// Only work for 'Aborted' and 'Suspending' states
	if ( state != _PS_ABORTED && state != _PS_SUSPENDING ) 
		return _false;

	SetState( _PS_RUNNING );

	return _true;
}

template< typename Type >
_ubool TProcessor< Type >::Suspend( )
{
	_PROCESS_STATE state = GetState( );

	// Only work for 'Running' state
	if ( state != _PS_RUNNING )
		return _false;

	SetState( _PS_SUSPENDING );

	return _true;
}

template< typename Type >
_ubool TProcessor< Type >::Abort( )
{
	SetState( _PS_ABORTED );

	return _true;
}

template< typename Type >
_ubool TProcessor< Type >::Finish( )
{
	SetState( _PS_FINISHED );

	return _true;
}

}