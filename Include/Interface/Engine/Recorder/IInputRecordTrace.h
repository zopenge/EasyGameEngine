//! @file     IInputRecordTrace.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInputRecordTrace
//----------------------------------------------------------------------------

class IInputRecordTrace : public IObject
{
public:
	//!	Get the channel ID ( no meaning, just for user to mark it )
	//!	@param		none.
	//!	@return		The channel ID.
	virtual _dword GetChannelID( ) const PURE;

	//!	Bind object.
	//!	@param		object		The object what you want to bind.
	//!	@return		none.
	virtual _void SetObject( IObject* object ) PURE;
	//!	Get binding object.
	//!	@param		none.
	//!	@return		The object interface.
	virtual IObjectRef GetObject( ) const PURE;

	//!	Get the input records.
	//!	@param		none.
	//!	@return		The input records.
	virtual const InputRecordInfoArray& GetInputRecords( ) const PURE;

	//!	Clear traces.
	virtual _void ClearTraces( ) PURE;
	//!	Add trace.
	virtual _void AddTrace( _dword time_stamp, const EventBase& event ) PURE;
	//!	Remove trace by index.
	virtual _void RemoveTraceByIndex( _dword index ) PURE;

	//!	Get the offset position of last 2 input records.
	//!	@param		none.
	//!	@return		The offset position.
	virtual Vector2 GetLastOffset( ) const PURE;

	virtual Vector2 GetTotalOffset( ) const PURE;
};

}