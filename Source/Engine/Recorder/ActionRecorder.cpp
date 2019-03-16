//! @file     ActionRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ActionRecorder Implementation
//----------------------------------------------------------------------------

ActionRecorder::ActionRecorder( )
{
	mIsClearing = _false;
}

ActionRecorder::~ActionRecorder( )
{
	ClearAllActions( _false );
}

_ubool ActionRecorder::IsRemovableStatus( _PROCESS_STATE state ) const
{
	switch ( state )
	{
		case _PS_ERROR:
		case _PS_ABORTED:
		case _PS_FINISHED:
			return _true;

		default:
			break;
	}

	return _false;
}

_void ActionRecorder::ProcessActions( )
{
	// Copy the actions
	mLock.Enter( );
	mProcessingActions = mActions;
	mLock.Leave( );

	// Process actions
	for ( _dword i = 0; i < mProcessingActions.Number( ); i ++ )
	{
		IActionRecord* action_record = mProcessingActions[i];
		EGE_ASSERT( action_record != _null );

		// Process it
		_PROCESS_STATE state = action_record->Process( );

		// Remove action if it's needed
		if ( mIsClearing || IsRemovableStatus( state ) )
		{
			mLock.Enter( );
			mActions.Remove( action_record );
			mLock.Leave( );
		}
	}

	// Clear processing actions
	mLock.Enter( );
	mProcessingActions.Clear( );
	mLock.Leave( );
}

_dword ActionRecorder::GetActionsNumber( ) const
{
	LockOwner lock_owner( mLock );

	return mActions.Number( );
}

IActionRecord* ActionRecorder::GetActionByIndex( _dword index )
{
	LockOwner lock_owner( mLock );

	if ( index >= mActions.Number( ) )
		return _null;

	return mActions[ index ];
}

IActionRecord* ActionRecorder::GetLastAction( )
{
	LockOwner lock_owner( mLock );

	if ( mActions.Number( ) == 0 )
		return _null;

	return mActions.GetTailElement( );
}

_void ActionRecorder::ClearAllActions( _ubool wait_for_all )
{
	mIsClearing = _true;

	mLock.Enter( );
	mActions.Clear( );
	mLock.Leave( );

	if ( wait_for_all )
	{
		ProcessActions( );

		while ( mProcessingActions.Number( ) != 0 )
			Platform::Sleep( 100 );
	}

	mIsClearing = _false;
}

_void ActionRecorder::AddAction( IActionRecord* action )
{
	if ( action == _null )
		return;

	LockOwner lock_owner( mLock );

	mActions.Append( action );
}

_void ActionRecorder::InsertAction( _dword index, IActionRecord* action )
{
	LockOwner lock_owner( mLock );

	if ( index >= mActions.Number( ) && action == _null )
		return;

	mActions.Insert( action, index );
}