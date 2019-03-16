//! @file     InputRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// InputRecorder
//----------------------------------------------------------------------------

class InputRecorder : public INTERFACE_OBJECT_IMPL( IInputRecorder )
{
private:
	typedef Array< IInputRecordTraceRef > InputTraceArray;

private:
	//!	The flags
	enum _FLAG
	{
		_FLAG_ENABLE_MULTIPLE_TOUCH = 1 << 0,
		_FLAG_ENABLE_ALWAYS_RECORD	= 1 << 1,
	};

private:
	//!	The valid traces what do not contain working trace info, except finished traces.
	InputTraceArray	mValidTraces;
	//!	The discard traces what will be removed on the next message input
	InputTraceArray mDiscardTraces;

	//!	The pause referenced count
	_dword			mPauseRefCount;
	//!	The flags
	FlagsObject		mFlags;

private:
	//!	Handle messages.
	IInputRecordTraceRef HandleTouchMessage( const EventTouch& message );

public:
	InputRecorder( );
	virtual ~InputRecorder( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IInputRecorder Interface
public:
	virtual _void					ClearInput( ) override;

	virtual IInputRecordTraceRef	Record( const EventBase& event ) override;

	virtual const InputTraceArray&	GetValidRecordTraces( ) const override;
	virtual IInputRecordTraceRef	GetRecordTraceByChannelID( _dword channel_id ) const override;
	virtual IInputRecordTraceRef	GetRecordTraceByObject( const IObject* object ) const override;
	virtual _dword					Pause( ) override;
	virtual _dword					Resume( ) override;

	virtual _void					EnableMultiTouch( _ubool enable ) override;
	virtual _ubool					IsEnableMultiTouch( ) const override;

	virtual _void					EnableAlwaysRecord( _ubool enable ) override;
	virtual _ubool					IsEnableAlwaysRecord( ) const override;

	virtual _ubool					IsPausingInput( ) const override;
};

//----------------------------------------------------------------------------
// InputRecorder Implementation
//----------------------------------------------------------------------------

}