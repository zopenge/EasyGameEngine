//! @file     IInputRecorder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInputRecorder
//----------------------------------------------------------------------------

class IInputRecorder : public IObject
{
public:
	virtual _void ClearInput( ) PURE;

	//!	Record input message.
	//!	@param		message		The input message.
	//!	@return		The record trace info.
	virtual IInputRecordTraceRef Record( const EventBase& event ) PURE;

	//! Get valid record traces.
	//! @param		none.
	//! @return		The record traces array.
	virtual const Array< IInputRecordTraceRef >& GetValidRecordTraces( ) const PURE;
	//!	Get record trace info by channel ID.
	//!	@param		channel_id	The channel ID.
	//!	@return		The record trace info.
	virtual IInputRecordTraceRef GetRecordTraceByChannelID( _dword channel_id ) const PURE;
	//!	Get record trace info by binding object.
	//!	@param		object		The object.
	//!	@return		The record trace info.
	virtual IInputRecordTraceRef GetRecordTraceByObject( const IObject* object ) const PURE;

	//!	Increments the reference count for pause state.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword Pause( ) PURE;
	//!	Decrements the reference count for pause state.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword Resume( ) PURE;

	//!	Enable/Disable multiple touch.
	//!	@param		enable		True indicates enable multiple touch.
	//!	@return		none.
	virtual _void EnableMultiTouch( _ubool enable ) PURE;
	//!	Check whether enable multiple touch.
	//!	@param		none.
	//!	@return		True indicates enable multiple touch.
	virtual _ubool IsEnableMultiTouch( ) const PURE;

	//!	Enable/Disable always record it without care pause state.
	//!	@param		enable		True indicates enable multiple touch.
	//!	@return		none.
	virtual _void EnableAlwaysRecord( _ubool enable ) PURE;
	//!	Check whether enable record it without care pause state.
	//!	@param		none.
	//!	@return		True indicates enable it.
	virtual _ubool IsEnableAlwaysRecord( ) const PURE;

	virtual _ubool IsPausingInput( ) const PURE;
};

}