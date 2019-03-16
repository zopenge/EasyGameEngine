//! @file     OperationRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// OperationRecorder Implementation
//----------------------------------------------------------------------------

OperationRecorder::OperationRecorder( _dword max_buffer_number, IOperationRecordPerformer* performer )
{
	mRecordIndexOfChangedPoint	= -1;

	mMaxBufferNumber			= max_buffer_number;

	mCurRecordIndex				= -1;

	SetPerformer( performer );
}

OperationRecorder::~OperationRecorder( )
{
}

_void OperationRecorder::SetPerformer( IOperationRecordPerformer* performer )
{
	if ( performer == _null )
		mPerformer = &NullEngine::GetInstance( ).GetOperationRecordPerformer( );
	else
		mPerformer = performer;
}

IOperationRecordPerformerRef OperationRecorder::GetPerformer( )
{
	return mPerformer;
}

_void OperationRecorder::ClearHasChangedFlag( )
{
	mRecordIndexOfChangedPoint = mCurRecordIndex;
}

_ubool OperationRecorder::HasChanged( ) const
{
	return mRecordIndexOfChangedPoint != mCurRecordIndex;
}

_ubool OperationRecorder::Undo( )
{
	if ( mCurRecordIndex == -1 )
		return _false;

	// continue do
	_ubool continue_do = mRecords[mCurRecordIndex].mContinueDo;

	// Get the index
	_dword index = mCurRecordIndex --;

	// Get the stream reader and reset pointer
	IStreamReader* stream_reader = mRecords[ index ].mOldStreamReader;
	stream_reader->Seek( _SEEK_BEGIN, 0 );

	// Do it
	_ubool ret = mPerformer->OnDo( _true, mRecords[ index ].mKey, stream_reader );

	if ( continue_do )
		ret = ret && Undo( );
	
	return ret;
}

_ubool OperationRecorder::Redo( )
{
	if ( mCurRecordIndex == mRecords.Number( ) - 1 )
		return _false;

	// Get the index
	_dword index = ++ mCurRecordIndex;

	// continue do
	_ubool continue_do = mRecords[mCurRecordIndex].mContinueDo;

	// Get the stream reader and reset pointer
	IStreamReader* stream_reader = mRecords[ index ].mNewStreamReader;
	stream_reader->Seek( _SEEK_BEGIN, 0 );

	// Do it
	_ubool ret = mPerformer->OnDo( _false, mRecords[ index ].mKey, stream_reader );

	if ( continue_do )
		ret = ret && Redo( );

	return ret;
}

_dword OperationRecorder::GetCurRecordIndex( ) const
{
	return mCurRecordIndex;
}

_void OperationRecorder::ClearAllRecords( )
{
	mRecordIndexOfChangedPoint	= -1;

	mCurRecordIndex				= -1;

	mRecords.Clear( );
}

_ubool OperationRecorder::Record( WStringPtr key, IStreamReader* old_stream_reader, IStreamReader* new_stream_reader, _ubool can_combine_by_key, _ubool can_continue_do )
{
	if ( old_stream_reader == _null || new_stream_reader == _null )
		return _false;

	// Try to combine it
	if ( can_combine_by_key && mCurRecordIndex != -1 )
	{
		// Check key
		if ( mRecords[ mCurRecordIndex ].mKey == key )
		{
			// Combine OK
			mRecords[ mCurRecordIndex ].mNewStreamReader = new_stream_reader;
			return _true;
		}
	}

	// Remove the first record when buffer is full
	if ( mMaxBufferNumber != -1 && mCurRecordIndex == mMaxBufferNumber - 1 )
	{
		mRecords.RemoveByIndex( 0 );

		mCurRecordIndex = mMaxBufferNumber - 1;
	}
	// Remove all records after the current record 
	else
	{
		for ( _dword i = mCurRecordIndex + 1; i < mRecords.Number( ); i ++ )
			mRecords.RemoveByIndex( i -- );

		// -1 -> 0 also, so ++ is safe operation
		mCurRecordIndex ++; 
	}

	// Add record
	RecordInfo record_info;
	record_info.mContinueDo			= can_continue_do;
	record_info.mKey				= key;
	record_info.mOldStreamReader	= old_stream_reader;
	record_info.mNewStreamReader	= new_stream_reader;
	mRecords.Append( record_info );

	return _true;
}