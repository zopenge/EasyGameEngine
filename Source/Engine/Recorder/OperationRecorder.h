//! @file     OperationRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// OperationRecorder
//----------------------------------------------------------------------------

class OperationRecorder : public INTERFACE_OBJECT_IMPL( IOperationRecorder )
{
private:
	//!	The record info
	struct RecordInfo
	{
		_ubool				mContinueDo;
		WString				mKey;
		IStreamReaderRef	mOldStreamReader;
		IStreamReaderRef	mNewStreamReader;

		RecordInfo( )
		{
			mContinueDo = _false;
		}
	};
	typedef Array< RecordInfo > RecordInfoArray;

private:
	//!	The index of records for changed point
	_dword							mRecordIndexOfChangedPoint;

	//!	The max buffer number
	_dword							mMaxBufferNumber;
	//!	The current record index
	_dword							mCurRecordIndex;
	//!	The operation records
	RecordInfoArray					mRecords;

	//!	The operation performer
	IOperationRecordPerformerRef	mPerformer;

private:

public:
	OperationRecorder( _dword max_buffer_number, IOperationRecordPerformer* performer );
	virtual ~OperationRecorder( );

public:

// IOperationRecorder Interface
public:
	virtual _void							SetPerformer( IOperationRecordPerformer* performer ) override;
	virtual IOperationRecordPerformerRef	GetPerformer( ) override;

	virtual _void							ClearHasChangedFlag( ) override;
	virtual _ubool							HasChanged( ) const override;

	virtual _ubool							Undo( ) override;
	virtual _ubool							Redo( ) override;

	virtual _dword							GetCurRecordIndex( ) const override;

	virtual _void							ClearAllRecords( ) override;
	virtual _ubool							Record( WStringPtr key, IStreamReader* old_stream_reader, IStreamReader* new_stream_reader, _ubool can_combine_by_key, _ubool can_continue_do ) override;
};

//----------------------------------------------------------------------------
// OperationRecorder Implementation
//----------------------------------------------------------------------------

}