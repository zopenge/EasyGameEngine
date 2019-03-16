//! @file     KeyboardDevice.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// KeyboardDevice
//----------------------------------------------------------------------------

class KeyboardDevice : public TInputDevice< INTERFACE_OBJECT_IMPL( IKeyboardDevice ) >
{
private:
	typedef TInputDevice< INTERFACE_OBJECT_IMPL( IKeyboardDevice ) > BaseClass;

public:
	KeyboardDevice( );
	virtual ~KeyboardDevice( );

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
	virtual _void	Tick( _time_t tick, _dword elapse ) override;

// IKeyboardDevice Interface
public:
	virtual _ubool	IsKeyDown( _dword keycode ) const override;
};

}
