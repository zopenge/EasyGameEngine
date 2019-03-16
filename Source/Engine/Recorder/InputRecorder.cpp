//! @file     InputRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// InputRecorder Implementation
//----------------------------------------------------------------------------

InputRecorder::InputRecorder( )
	: mPauseRefCount( 0 )
{
}

InputRecorder::~InputRecorder( )
{
}

_void InputRecorder::ClearInput( )
{
	mValidTraces.Clear( _true );
	mDiscardTraces.Clear( _true );
	mPauseRefCount = 0;
}

IInputRecordTraceRef InputRecorder::HandleTouchMessage( const EventTouch& message )
{
	// Build trace info and link the input record info
	switch ( message.mEvent )
	{
		case EventTouch::_EVENT_BEGAN:
		{
			if ( IsPausingInput( ) )
				return _null;

			if ( !IsEnableMultiTouch( ) && mValidTraces.Number( ) != 0 )
				return _null;

			// Build trace info ( make touch ID as channel ID )
			IInputRecordTracePassRef trace = new InputRecordTrace( message.mTouchID );
			trace->AddTrace( message.mTimestamp, message );

			// Append trace info
			mValidTraces.Append( trace );

			return trace;
		}
		break;
	
		case EventTouch::_EVENT_MOVED:
		case EventTouch::_EVENT_ENDED:
		{
			for ( _dword i = 0; i < mValidTraces.Number( ); ++ i )
			{
				IInputRecordTrace* trace = mValidTraces[i];
				EGE_ASSERT( trace != _null );

				// Check the touch ID
				if ( trace->GetChannelID( ) != message.mTouchID )
					continue;

				// Append input record into trace
				trace->AddTrace( message.mTimestamp, message );

				// If the input record finished then put it into discard traces and wait for the next touch begin event to remove it
				if ( message.mEvent == EventTouch::_EVENT_ENDED )
				{
					mDiscardTraces.Append( trace );
					mValidTraces.RemoveByIndex( i );
				}

				return trace;
			}
		}
		break;

		default:
			break;
	}

	return _null;
}

_ubool InputRecorder::Initialize( )
{
	return _true;
}

IInputRecordTraceRef InputRecorder::Record( const EventBase& event ) 
{
	switch ( event.mEventID )
	{
		case _EVENT_TOUCH:
			return HandleTouchMessage( (const EventTouch&) event ); 

		default:
			return _null;
	}
}

IInputRecordTraceRef InputRecorder::GetRecordTraceByChannelID( _dword channel_id ) const
{
    for ( _dword i = 0; i < mDiscardTraces.Number( ); ++ i )
	{
		IInputRecordTrace* trace = mDiscardTraces[i].GetPtr( );
		if ( trace == _null )
			continue;
        
		if ( trace->GetChannelID( ) == channel_id )
			return trace;
	}
    
	for ( _dword i = 0; i < mValidTraces.Number( ); ++ i )
	{
		IInputRecordTrace* trace = mValidTraces[i].GetPtr( );
		if ( trace == _null )
			continue;

		if ( trace->GetChannelID( ) == channel_id )
			return trace;
	}

	return _null;
}

IInputRecordTraceRef InputRecorder::GetRecordTraceByObject( const IObject* object ) const
{
    for ( _dword i = 0; i < mDiscardTraces.Number( ); ++ i )
	{
		IInputRecordTrace* trace = mDiscardTraces[i].GetPtr( );
		if ( trace == _null )
			continue;
        
		if ( trace->GetObject( ) == object )
			return trace;
	}
    
	for ( _dword i = 0; i < mValidTraces.Number( ); ++ i )
	{
		IInputRecordTrace* trace = mValidTraces[i].GetPtr( );
		if ( trace == _null )
			continue;

		if ( trace->GetObject( ) == object )
			return trace;
	}

	return _null;
}

const Array< IInputRecordTraceRef >& InputRecorder::GetValidRecordTraces( ) const
{
	return mValidTraces;
}

_dword InputRecorder::Pause( )
{
	WLOG_TRACE_1( L"InputRecorder: pause ref : %d", mPauseRefCount );

	++ mPauseRefCount;
	return mPauseRefCount;
}

_dword InputRecorder::Resume( )
{
	WLOG_TRACE_1( L"InputRecorder: resume ref : %d", mPauseRefCount );

	if ( mPauseRefCount == 0 )
		return mPauseRefCount;

	-- mPauseRefCount;
	return mPauseRefCount;
}

_void InputRecorder::EnableMultiTouch( _ubool enable )
{
	mFlags.EnableFlags( _FLAG_ENABLE_MULTIPLE_TOUCH, enable );
}

_ubool InputRecorder::IsEnableMultiTouch( ) const
{
	return mFlags.HasFlags( _FLAG_ENABLE_MULTIPLE_TOUCH );
}

_void InputRecorder::EnableAlwaysRecord( _ubool enable )
{
	mFlags.EnableFlags( _FLAG_ENABLE_ALWAYS_RECORD, enable );
}

_ubool InputRecorder::IsEnableAlwaysRecord( ) const
{
	return mFlags.HasFlags( _FLAG_ENABLE_ALWAYS_RECORD );
}

_ubool InputRecorder::IsPausingInput( ) const
{
	return !IsEnableAlwaysRecord( ) && mPauseRefCount != 0;
}