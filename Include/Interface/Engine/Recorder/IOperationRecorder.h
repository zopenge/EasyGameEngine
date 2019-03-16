//! @file     IOperationRecorder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IOperationRecorder
//----------------------------------------------------------------------------

class IOperationRecorder : public IObject
{
public:
	//!	Set performer.
	//!	@param		performer	The operation performer.
	//!	@return		none.
	virtual _void SetPerformer( IOperationRecordPerformer* performer ) PURE;
	//!	Get performer.
	//!	@param		none.
	//!	@return		The performer.
	virtual IOperationRecordPerformerRef GetPerformer( ) PURE;

	//!	Check whether has changed or not.
	//!	@param		none.
	//!	@return		True indicates has changed, it means we has reached the original point(history record reaches the first element or hasn't any records).
	virtual _ubool HasChanged( ) const PURE;
	//!	Clear has changed flag.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearHasChangedFlag( ) PURE;

	//!	Undo.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Undo( ) PURE;
	//!	Redo.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Redo( ) PURE;

	//!	Get the current record index.
	//!	@param		none.
	//!	@return		The current record index.
	virtual _dword GetCurRecordIndex( ) const PURE;

	//!	Clear all records.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllRecords( ) PURE;
	//!	Record.
	//!	@param		key					The record key.
	//!	@param		old_stream_reader	The old record stream info.
	//!	@param		new_stream_reader	The new record stream info.
	//!	@param		can_combine			True indicates can combine it.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Record( WStringPtr key, IStreamReader* old_stream_reader, IStreamReader* new_stream_reader, _ubool can_combine_by_key, _ubool can_continue_do ) PURE;
};

}