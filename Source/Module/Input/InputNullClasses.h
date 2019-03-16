//! @file     InputNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullKeyboardDevice
//----------------------------------------------------------------------------

class NullKeyboardDevice : public TInputDevice< INTERFACE_OBJECT_IMPL( IKeyboardDevice ) >
{
private:
	typedef TInputDevice< INTERFACE_OBJECT_IMPL( IKeyboardDevice ) > BaseClass;

public:
	NullKeyboardDevice( ) : BaseClass( _DEVICE_KEYBOARD ) { }
	virtual ~NullKeyboardDevice( ) { }

// IKeyboardDevice Interface
public:
	virtual _ubool	IsKeyDown( _dword keycode ) const { return _false; }
};

//----------------------------------------------------------------------------
// NullMouseDevice
//----------------------------------------------------------------------------

class NullMouseDevice : public TInputDevice< INTERFACE_OBJECT_IMPL( IMouseDevice ) >
{
private:
	typedef TInputDevice< INTERFACE_OBJECT_IMPL( IMouseDevice ) > BaseClass;

public:
	NullMouseDevice( ) : BaseClass( _DEVICE_MOUSE ) { }
	virtual ~NullMouseDevice( ) { }

// IMouseDevice Interface
public:
	virtual const MouseData&	GetMouseData( ) const { static MouseData sMouseData; return sMouseData; }
};

//----------------------------------------------------------------------------
// NullInputModule
//----------------------------------------------------------------------------

class NullInputModule : public INTERFACE_MODULE_IMPL( IInputModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IInputModule ) BaseClass;

public:
	NullInputModule( ) : BaseClass( L"InputModule", Version( INPUT_FILEVER ) ) { }
	virtual ~NullInputModule( ) { }
};

}