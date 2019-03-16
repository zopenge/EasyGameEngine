//! @file     MouseDevice.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MouseDevice
//----------------------------------------------------------------------------

class MouseDevice : public TInputDevice< INTERFACE_OBJECT_IMPL( IMouseDevice ) >
{
private:
	typedef TInputDevice< INTERFACE_OBJECT_IMPL( IMouseDevice ) > BaseClass;

private:
	//!	The window handle
	_handle		mWindowHandle;
	//!	The mouse data
	MouseData	mMouseData;

public:
	MouseDevice( _handle windowhandle );
	virtual ~MouseDevice( );

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

// IMouseDevice Interface
public:
	virtual const MouseData&	GetMouseData( ) const override;
};

}