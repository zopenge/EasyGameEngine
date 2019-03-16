//! @file     JoystickDevice.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// JoystickDevice
//----------------------------------------------------------------------------

class JoystickDevice : public TInputDevice< INTERFACE_OBJECT_IMPL( IJoystickDevice ) >
{
private:
	typedef TInputDevice< INTERFACE_OBJECT_IMPL( IJoystickDevice ) > BaseClass;

private:
	JoystickData	mJoystickData;

public:
	JoystickDevice( );
	virtual ~JoystickDevice( );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( );
	//!	Handle message.
	//!	@param		message		The message info.
	//!	@return		none.
	_void HandleMessage( const MessageBase& message );

// IObject Interface
public:
	virtual _void				Tick( _time_t tick, _dword elapse ) override;

// IJoystickDevice Interface
public:
	virtual const JoystickData& GetJoystickData( ) const override;
};

//----------------------------------------------------------------------------
// JoystickDevice Implementation
//----------------------------------------------------------------------------

}
