//! @file     TTask.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TTask
//----------------------------------------------------------------------------

template< typename Type >
class TTask : public TObservable< TFlagsObject< Type > >
{
protected:
	typedef TObservable< TFlagsObject< Type > > TBaseClass;

protected:
	//!	The last error ID
	_dword			mLastErrorID;

	//!	The state of task
	_PROCESS_STATE	mTaskState;

protected:
	//!	Set state.
	virtual _void SetState( _PROCESS_STATE state );

protected:
	TTask( );
	virtual ~TTask( );

// ITask Interface
public:
	virtual _void			SetLastErrorID( _dword errorid ) override;
	virtual _dword			GetLastErrorID( ) const override;

	virtual _PROCESS_STATE	GetState( ) const override;

	virtual _ubool			Wait( ) override;
	virtual _ubool 			Start( ) override;
	virtual _ubool 			Resume( ) override;
	virtual _ubool 			Suspend( ) override;
	virtual _ubool 			Abort( ) override;
	virtual _ubool			Finish( ) override;
};

//----------------------------------------------------------------------------
// TTask Implementation
//----------------------------------------------------------------------------

template< typename Type >
TTask< Type >::TTask( )
{
	mLastErrorID	= 0;

	mTaskState		= _PS_WAITING;
}

template< typename Type >
TTask< Type >::~TTask( )
{
	// We are releasing it
	SetState( _PS_RELEASING );
}

template< typename Type >
_void TTask< Type >::SetState( _PROCESS_STATE state )
{
	mTaskState = state;
}

template< typename Type >
_void TTask< Type >::SetLastErrorID( _dword errorid )
{
	mLastErrorID = errorid;

	if ( mLastErrorID != 0 )
		this->SetState( _PS_ERROR );
}

template< typename Type >
_dword TTask< Type >::GetLastErrorID( ) const
{
	return mLastErrorID;
}

template< typename Type >
_PROCESS_STATE TTask< Type >::GetState( ) const
{
	return mTaskState;
}

template< typename Type >
_ubool TTask< Type >::Wait( )
{
	SetState( _PS_WAITING );

	return _true;
}

template< typename Type >
_ubool TTask< Type >::Start( )
{
	SetState( _PS_RUNNING );

	return _true;
}

template< typename Type >
_ubool TTask< Type >::Resume( )
{
	_PROCESS_STATE state = GetState( );

	// Only work for 'Aborted' and 'Suspending' states
	if ( state != _PS_ABORTED && state != _PS_SUSPENDING )
		return _false;

	SetState( _PS_RUNNING );

	return _true;
}

template< typename Type >
_ubool TTask< Type >::Suspend( )
{
	_PROCESS_STATE state = GetState( );

	// Only work for 'Running' state
	if ( state != _PS_RUNNING )
		return _false;

	SetState( _PS_SUSPENDING );

	return _true;
}

template< typename Type >
_ubool TTask< Type >::Abort( )
{
	SetState( _PS_ABORTED );

	return _true;
}

template< typename Type >
_ubool TTask< Type >::Finish( )
{
	SetState( _PS_FINISHED );

	return _true;
}

}