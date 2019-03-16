//! @file     InputRecordTrace.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// InputRecordTrace
//----------------------------------------------------------------------------

class InputRecordTrace : public INTERFACE_OBJECT_IMPL( IInputRecordTrace )
{
private:
	//!	The channel ID ( no meaning, just for user to mark it )
	_dword					mChannelID; 
	//!	The binding object
	IObjectRef				mBindObject;
	//!	The input records
	InputRecordInfoArray	mInputRecords;

public:
	InputRecordTrace( _dword channel_id );
	virtual ~InputRecordTrace( );

// IInputRecordTrace Interface
public:
	virtual _dword						GetChannelID( ) const override;

	virtual _void						SetObject( IObject* object ) override;
	virtual IObjectRef					GetObject( ) const override;

	virtual const InputRecordInfoArray& GetInputRecords( ) const override;

	virtual _void						ClearTraces( ) override;
	virtual _void						AddTrace( _dword time_stamp, const EventBase& event ) override;
	virtual _void						RemoveTraceByIndex( _dword index ) override;

	virtual Vector2						GetLastOffset( ) const override;
	virtual Vector2						GetTotalOffset( ) const override;
};

//----------------------------------------------------------------------------
// InputRecordTrace Implementation
//----------------------------------------------------------------------------

}