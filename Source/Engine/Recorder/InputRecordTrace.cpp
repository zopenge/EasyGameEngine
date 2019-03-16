//! @file     InputRecordTrace.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// InputRecordTrace Implementation
//----------------------------------------------------------------------------

InputRecordTrace::InputRecordTrace( _dword channel_id )
{
	mChannelID	= channel_id;
}

InputRecordTrace::~InputRecordTrace( )
{
	ClearTraces( );
}

_dword InputRecordTrace::GetChannelID( ) const
{
	return mChannelID;
}

_void InputRecordTrace::SetObject( IObject* object )
{
	mBindObject = object;
}

IObjectRef InputRecordTrace::GetObject( ) const
{
	return mBindObject;
}

const InputRecordInfoArray& InputRecordTrace::GetInputRecords( ) const
{
	return mInputRecords;
}

_void InputRecordTrace::ClearTraces( )
{
	for ( _dword i = 0; i < mInputRecords.Number( ); i ++ )
	{
		EGE_DELETE( mInputRecords[i].mEvent );
	}
}

_void InputRecordTrace::AddTrace( _dword time_stamp, const EventBase& event )
{
	// Add input record
	InputRecordInfo inputinfo;
	inputinfo.mTimeStamp	= time_stamp;
	inputinfo.mEvent		= event.CloneTo( );
	mInputRecords.Append( inputinfo );
}

_void InputRecordTrace::RemoveTraceByIndex( _dword index )
{
	if ( index >= mInputRecords.Number( ) )
		return;

	// Free message buffer
	EGE_DELETE( mInputRecords[ index ].mEvent );

	// Remove it
	mInputRecords.RemoveByIndex( index );
}

Vector2 InputRecordTrace::GetLastOffset( ) const
{
	if ( mInputRecords.Number( ) <= 1 )
		return Vector2::cOrigin;

	const InputRecordInfo& cur	= mInputRecords[ mInputRecords.Number( ) - 1 ];
	const InputRecordInfo& last	= mInputRecords[ mInputRecords.Number( ) - 2 ];

	return cur.GetPosition( ) - last.GetPosition( );
}

Vector2 InputRecordTrace::GetTotalOffset( ) const
{
	if ( mInputRecords.Number( ) <= 1 )
		return Vector2::cOrigin;

	const InputRecordInfo& begin	= mInputRecords[ 0 ];
	const InputRecordInfo& end		= mInputRecords[ mInputRecords.Number( ) - 1 ];

	return end.GetPosition( ) - begin.GetPosition( );
}